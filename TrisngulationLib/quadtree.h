#ifndef QUADTREE_H
#define QUADTREE_H

#include "point.h"

#include <vector>

class QuadTree
{

    class Rectangle
    {
    public:
        Rectangle(const Point &center_, double halfWidth_, double halfLength_):
            center(center_), halfWidth(halfWidth_), halfLength(halfLength_){}
        bool containsPoint(const Point &p);

        Point center;
        double halfWidth;
        double halfLength;
    };

public:
    QuadTree(const Point &center_, double halfWidth_, double halfLength_) : boundary(center_, halfWidth_, halfLength_){}
    ~QuadTree();
    bool insert(Point *p);
    std::vector<Point*>& getNearestPoint(const Point &p);

private:
    void subdivide();
    bool enough() { return points.size() > 3; }

private:
    const unsigned int QT_NODE_CAPACITY = 8;
    Rectangle boundary;
    std::vector<Point*> points;
    QuadTree* northWest = nullptr;
    QuadTree* northEast = nullptr;
    QuadTree* southWest = nullptr;
    QuadTree* southEast = nullptr;
};

#endif // QUADTREE_H
