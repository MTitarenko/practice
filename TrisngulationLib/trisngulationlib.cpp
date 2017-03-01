#include "trisngulationlib.h"
#include <algorithm>

DelaunayTrisngulation::DelaunayTrisngulation(std::vector<Point> &vertices)
{
    _vertices = &vertices;

    double minX = vertices[0].x;
    double minY = vertices[0].y;
    double maxX = minX;
    double maxY = minY;


    for(std::size_t i = 0; i < vertices.size(); ++i)
    {
        if (vertices[i].x < minX) minX = vertices[i].x;
        if (vertices[i].y < minY) minY = vertices[i].y;
        if (vertices[i].x > maxX) maxX = vertices[i].x;
        if (vertices[i].y > maxY) maxY = vertices[i].y;
    }

    double dx = maxX - minX;
    double dy = maxY - minY;
    double deltaMax = std::max(dx, dy);
    double midx = (minX + maxX) / 2.0;
    double midy = (minY + maxY) / 2.0;

    Point* p1 = new Point(midx - 20 * deltaMax, midy - deltaMax);
    Point* p2 = new Point(midx, midy + 20 * deltaMax);
    Point* p3 = new Point(midx + 20 * deltaMax, midy - deltaMax);

    _triangles.push_back(std::shared_ptr<Triangle>(new Triangle(p1, p2, p3)));
    quadTree = new QuadTree(Point(midx, midy), dx / 2.0, dy / 2.0);

    for(std::vector<Point>::iterator p = vertices.begin(); p != vertices.end(); ++p)
    {
        quadTree->insert(&(*p));
        std::vector<std::shared_ptr<Triangle>> badTriangles;
        std::vector<Edge> polygon;

        for(auto t = begin(_triangles); t != end(_triangles); ++t)
        {
            if((*t)->circumCircleContains(*p))
            {
                badTriangles.push_back(*t);
                polygon.push_back((*t)->e1);
                polygon.push_back((*t)->e2);
                polygon.push_back((*t)->e3);
            }
        }

        _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [badTriangles](std::shared_ptr<Triangle> &t){
            for(auto bt = begin(badTriangles); bt != end(badTriangles); ++bt)
            {
                if(*bt == t)
                {
                    return true;
                }
            }
            return false;
        }), end(_triangles));

        std::vector<Edge> badEdges;
        for(auto e1 = begin(polygon); e1 != end(polygon); ++e1)
        {
            for(auto e2 = begin(polygon); e2 != end(polygon); ++e2)
            {
                if(e1 == e2)
                    continue;

                if(*e1 == *e2)
                {
                    badEdges.push_back(*e1);
                    badEdges.push_back(*e2);
                }
            }
        }

        polygon.erase(std::remove_if(begin(polygon), end(polygon), [badEdges](Edge &e){
            for(auto it = begin(badEdges); it != end(badEdges); ++it)
            {
                if(*it == e)
                    return true;
            }
            return false;
        }), end(polygon));

        for(auto e = begin(polygon); e != end(polygon); ++e)
            _triangles.push_back(std::shared_ptr<Triangle>(new Triangle(e->p1, e->p2, &(*p))));
    }

    _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](std::shared_ptr<Triangle> &t){
        return t->containsVertex(p1) || t->containsVertex(p2) || t->containsVertex(p3);
    }), end(_triangles));

    delete p1;
    delete p2;
    delete p3;

    for(auto t = _triangles.begin(); t != _triangles.end(); ++t)
    {
        _edges.push_back((*t)->e1);
        _edges.push_back((*t)->e2);
        _edges.push_back((*t)->e3);
    }
}

DelaunayTrisngulation::~DelaunayTrisngulation()
{
    delete quadTree;
}

std::pair<Triangle*, std::list<Triangle*>> DelaunayTrisngulation::getTriangle(const Point &p)
{
    std::vector<Point*>* points = &(quadTree->getNearestPoint(p));
    size_t j = 0;
    double minDist = (*points)[0]->dist2(p);
    double nextDist;
    for(size_t i = 1; i < points->size(); ++i)
    {
        nextDist = (*points)[i]->dist2(p);
        if (nextDist < minDist)
        {
            minDist = nextDist;
            j = i;
        }
    }

    std::list<Triangle*>::const_iterator it = ((*points)[j])->getTriangles().cbegin();
    std::list<Triangle*>::const_iterator trueTriangle = it;
    for(; it != ((*points)[j])->getTriangles().cend(); ++it)
    {
        if ((*it)->insideTriangle(p))
        {
            trueTriangle = it;
            goto L0;
        }
    }

    it = ((*points)[j])->getTriangles().cbegin();
    minDist = (*it)->distToMid2(p);
    for(; it != ((*points)[j])->getTriangles().cend(); ++it)
    {
        nextDist = (*it)->distToMid2(p);
        if (nextDist < minDist)
        {
            minDist = nextDist;
            trueTriangle = it;
        }
    }
    L0:
    return std::make_pair(*trueTriangle, ((*points)[j])->getTriangles());
}

double DelaunayTrisngulation::getDepth(const Point &p)
{
    std::vector<Point*>* points = &(quadTree->getNearestPoint(p));
    size_t j = 0;
    double minDist = (*points)[0]->dist2(p);
    double nextDist;
    for(size_t i = 1; i < points->size(); ++i)
    {
        nextDist = (*points)[i]->dist2(p);
        if (nextDist < minDist)
        {
            minDist = nextDist;
            j = i;
        }
    }

    std::list<Triangle*>::const_iterator it = ((*points)[j])->getTriangles().cbegin();
    std::list<Triangle*>::const_iterator trueTriangle = it;
    for(; it != ((*points)[j])->getTriangles().cend(); ++it)
    {
        if ((*it)->insideTriangle(p))
        {
            trueTriangle = it;
            goto L1;
        }
    }

    it = ((*points)[j])->getTriangles().cbegin();
    minDist = (*it)->distToMid2(p);
    for(; it != ((*points)[j])->getTriangles().cend(); ++it)
    {
        nextDist = (*it)->distToMid2(p);
        if (nextDist < minDist)
        {
            minDist = nextDist;
            trueTriangle = it;
        }
    }
    L1:
    double x1 = (*trueTriangle)->p1->x;
    double x2 = (*trueTriangle)->p2->x;
    double x3 = (*trueTriangle)->p3->x;
    double y1 = (*trueTriangle)->p1->y;
    double y2 = (*trueTriangle)->p2->y;
    double y3 = (*trueTriangle)->p3->y;
    double z1 = (*trueTriangle)->p1->z;
    double z2 = (*trueTriangle)->p2->z;
    double z3 = (*trueTriangle)->p3->z;
    double A = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    double B = x1 * (z3 - z2) + x2 * (z1 - z3) + x3 * (z2 - z1);
    double C = x1 * (y3 - y2) + x2 * (y1 - y3) + x3 * (y2 - y1);
    double D = x1 * (y3 * z2 - y2 * z3) + y1 * (x2 * z3 - x3 * z2) + z1 * (x3 * y2 - x2 * y3);
    return (A * p.x + B * p.y + D) / C;
}
