#include "triangle.h"

#include <math.h>

Triangle::Triangle(Point* _p1, Point* _p2, Point *_p3)
    :	p1(_p1), p2(_p2), p3(_p3),
        e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1)
{
    p1->push_back(this);
    p2->push_back(this);
    p3->push_back(this);
    AB = sqrt(((p1->x - p2->x) * (p1->x - p2->x)) + ((p1->y - p2->y) * (p1->y - p2->y)));
    BC = sqrt(((p2->x - p3->x) * (p2->x - p3->x)) + ((p2->y - p3->y) * (p2->y - p3->y)));
    AC = sqrt(((p1->x - p3->x) * (p1->x - p3->x)) + ((p1->y - p3->y) * (p1->y - p3->y)));
    double p = (AB + BC + AC) / 2.0;
    square = sqrt(p * (p - AB) * (p - BC) * (p - AC));
}

Triangle::~Triangle()
{
    p1->erase(this);
    p2->erase(this);
    p3->erase(this);
}

bool Triangle::containsVertex(Point *p)
{
    return p1 == p || p2 == p || p3 == p;
}

bool Triangle::circumCircleContains(const Point &p)
{
    double ab = (p1->x * p1->x) + (p1->y * p1->y);
    double cd = (p2->x * p2->x) + (p2->y * p2->y);
    double ef = (p3->x * p3->x) + (p3->y * p3->y);

    double circum_x = (ab * (p3->y - p2->y) + cd * (p1->y - p3->y) + ef * (p2->y - p1->y)) / (p1->x * (p3->y - p2->y) + p2->x * (p1->y - p3->y) + p3->x * (p2->y - p1->y)) / 2.0;
    double circum_y = (ab * (p3->x - p2->x) + cd * (p1->x - p3->x) + ef * (p2->x - p1->x)) / (p1->y * (p3->x - p2->x) + p2->y * (p1->x - p3->x) + p3->y * (p2->x - p1->x)) / 2.0;
    double circum_radius = sqrt(((p1->x - circum_x) * (p1->x - circum_x)) + ((p1->y - circum_y) * (p1->y - circum_y)));

    double dist = sqrt(((p.x - circum_x) * (p.x - circum_x)) + ((p.y - circum_y) * (p.y - circum_y)));
    return dist <= circum_radius;
}

double triangleSquare(const double &a, const double &b, const double &c){
   double p = (a + b + c) / 2.0;
   return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool Triangle::insideTriangle(const Point &point)
{
    double AP = sqrt(((p1->x - point.x) * (p1->x - point.x)) + ((p1->y - point.y) * (p1->y - point.y)));
    double BP = sqrt(((p2->x - point.x) * (p2->x - point.x)) + ((p2->y - point.y) * (p2->y - point.y)));
    double CP = sqrt(((p3->x - point.x) * (p3->x - point.x)) + ((p3->y - point.y) * (p3->y - point.y)));
    double diff = triangleSquare(AP, BP, AB) + triangleSquare(AP, CP, AC) + triangleSquare(BP, CP, BC) - square;
    return abs(diff) < 1E-10 ? true : false;
}

double Triangle::distToMid2(const Point &point)
{
    double circum_x = (p1->x + p2->x + p3->x) / 3.0;
    double circum_y = (p1->y + p2->y + p3->y) / 3.0;
    return (point.x - circum_x) * (point.x - circum_x) + (point.y - circum_y) * (point.y - circum_y);
}
