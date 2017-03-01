#ifndef EDGE_H
#define EDGE_H

#include "point.h"

class Point;
class Edge
{
    public:
        Edge(Point *p1, Point* p2) : p1(p1), p2(p2) {}
        Edge(const Edge &e) : p1(e.p1), p2(e.p2) {}

        Point* p1;
        Point* p2;
};

inline bool operator == (const Edge &e1, const Edge &e2)
{
    return 	(e1.p1 == e2.p1 && e1.p2 == e2.p2) ||
            (e1.p1 == e2.p2 && e1.p2 == e2.p1);
}

#endif // EDGE_H
