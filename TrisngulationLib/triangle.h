#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "edge.h"

class Triangle
{
    public:
        Triangle(Point *_p1, Point *_p2, Point *_p3);
        ~Triangle();

        bool containsVertex(Point *p);
        bool circumCircleContains(const Point &p);
        bool insideTriangle(const Point &point);
        double distToMid2(const Point &point);

        Point *p1;
        Point *p2;
        Point *p3;

        Edge e1;
        Edge e2;
        Edge e3;

        double AB;
        double BC;
        double AC;
        double square;
};

inline bool operator == (const Triangle &t1, const Triangle &t2)
{
    return	(t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3) &&
            (t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3) &&
            (t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3);
}

#endif // TRIANGLE_H
