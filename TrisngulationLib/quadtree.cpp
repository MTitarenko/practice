#include "quadtree.h"

bool QuadTree::Rectangle::containsPoint(const Point &p)
{
    if((p.x < center.x - halfWidth) || (p.x > center.x + halfWidth)
    || (p.y < center.y - halfLength) || (p.y > center.y + halfLength))
        return false;
    return true;
}

QuadTree::~QuadTree()
{
    if (northWest != nullptr)
    {
        delete northWest;
        delete northEast;
        delete southWest;
        delete southEast;
    }
}

bool QuadTree::insert(Point *p)
{
    if (!boundary.containsPoint(*p))
      return false;
    if (points.size() < QT_NODE_CAPACITY)
    {
      points.push_back(p);
      return true;
    }
    if (northWest == nullptr)
      subdivide();
    if (northWest->insert(p)) goto L;
    if (northEast->insert(p)) goto L;
    if (southWest->insert(p)) goto L;
    southEast->insert(p);
    L:
    if(!(northWest->enough() && northEast->enough() && southWest->enough() && southEast->enough()))
        points.push_back(p);
    return true;
}

void QuadTree::subdivide()
{
    northWest = new QuadTree(Point(boundary.center.x - boundary.halfWidth / 2,
                                   boundary.center.y - boundary.halfLength / 2),
                             boundary.halfWidth / 2,
                             boundary.halfLength / 2);
    northEast = new QuadTree(Point(boundary.center.x + boundary.halfWidth / 2,
                                   boundary.center.y - boundary.halfLength / 2),
                             boundary.halfWidth / 2,
                             boundary.halfLength / 2);
    southWest = new QuadTree(Point(boundary.center.x - boundary.halfWidth / 2,
                                   boundary.center.y + boundary.halfLength / 2),
                             boundary.halfWidth / 2,
                             boundary.halfLength / 2);
    southEast = new QuadTree(Point(boundary.center.x + boundary.halfWidth / 2,
                                   boundary.center.y + boundary.halfLength / 2),
                             boundary.halfWidth / 2,
                             boundary.halfLength / 2);
    for(auto p = begin(points); p != end(points); p++)
    {
        if (northWest->insert(*p)) continue;
        if (northEast->insert(*p)) continue;
        if (southWest->insert(*p)) continue;
        southEast->insert(*p);
    }
}

std::vector<Point*>& QuadTree::getNearestPoint(const Point &p)
{
    if (northWest != nullptr)
    {
        if (northWest->boundary.containsPoint(p) && northWest->enough())
                return northWest->getNearestPoint(p);
        if (northEast->boundary.containsPoint(p) && northEast->enough())
                return northEast->getNearestPoint(p);
        if (southWest->boundary.containsPoint(p) && southWest->enough())
                return southWest->getNearestPoint(p);
        if (southEast->boundary.containsPoint(p) && southEast->enough())
                return southEast->getNearestPoint(p);
    }
    return points;
}
