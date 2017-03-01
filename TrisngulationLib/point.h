#ifndef POINT_H
#define POINT_H

#include "triangle.h"

#include <cmath>
#include <list>

class Triangle;
class Point
{
    public:

        Point()
        {
            x = 0;
            y = 0;
            z = 0;
        }

        Point(double _x, double _y, double _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        Point(double _x, double _y)
        {
            x = _x;
            y = _y;
            z = 0;
        }

        Point(const Point &p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
        }

        ~Point()
        {
            if(triangles != nullptr)
                delete triangles;
        }

        void set(double _x, double _y, double _z)
        {
            x = _x;
            y = _y;
            z = _z;
        }

        void set(double _x, double _y)
        {
            x = _x;
            y = _y;
            z = 0;
        }

        void set(const Point &p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
        }

        double dist2(const Point &p)
        {
            double dx = x - p.x;
            double dy = y - p.y;
            return dx * dx + dy * dy;
        }

        double dist(const Point &p)
        {
            return sqrt(dist2(p));
        }

        void push_back(Triangle* t)
        {
            if(triangles == nullptr)
                triangles = new std::list<Triangle*>;
            triangles->push_back(t);
        }

        void erase(Triangle* t)
        {
            for(std::list<Triangle*>::const_iterator it = triangles->cbegin(); it != triangles->cend(); ++it)
            {
                if(*it == t)
                {
                    triangles->erase(it);
                    return;
                }
            }
        }

        std::list<Triangle*>& getTriangles()
        {
            return *triangles;
        }

        double x;
        double y;
        double z;

private:
        std::list<Triangle*>* triangles = nullptr;
};

inline bool operator == (const Point &p1, const Point &p2)
{
    return (p1.x == p2.x) && (p1.y == p2.y);
}

#endif // POINT_H
