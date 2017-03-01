#include <iostream>
#include "trisngulationlib.h"
#include "time.h"
#include "Windows.h"

using namespace std;

int main()
{
    srand (time(0));
    double border_x = 3000;
    double border_y = 1000;
    double x;
    double y;
    double z;
    std::vector<Point> points;
    points.push_back(Point(0, 0));
    points.push_back(Point(border_x, 0));
    points.push_back(Point(border_x, border_y));
    points.push_back(Point(0, border_y));
    for(int i = 0; i < 2996; ++i)
    {
        x = (static_cast<double>(rand()) / RAND_MAX) * border_x;
        y = (static_cast<double>(rand()) / RAND_MAX) * border_y;
        z = (static_cast<double>(rand()) / RAND_MAX) * 100;
        points.push_back(Point(x, y, z));
    }
    DWORD time1 = GetTickCount();
    DelaunayTrisngulation triangulation(points);
    DWORD time2 = GetTickCount();
    printf("Preparation time: %.3f s\n", static_cast<double>(time2 - time1) / 1000);
    Point point;
    int num = 1000;
    time1 = GetTickCount();
    for(int j = 0; j < num; ++j)
    {
        for(int i = 0; i < 10000; ++i)
        {
            x = (static_cast<double>(rand()) / RAND_MAX) * border_x;
            y = (static_cast<double>(rand()) / RAND_MAX) * border_y;
            point.set(x, y);
            triangulation.getDepth(point);
        }
    }
    time2 = GetTickCount();
    printf("Work time: %.3f ms\n", static_cast<double>(time2 - time1) / num);
    return 0;
}
