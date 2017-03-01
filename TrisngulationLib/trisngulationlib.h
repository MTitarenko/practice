#ifndef TRISNGULATIONLIB_H
#define TRISNGULATIONLIB_H

#include "trisngulationlib_global.h"

#include "triangle.h"
#include "quadtree.h"

#include <vector>
#include <memory>

class TRISNGULATIONLIBSHARED_EXPORT DelaunayTrisngulation
{
public:
    DelaunayTrisngulation(std::vector<Point> &vertices);
    ~DelaunayTrisngulation();
    const std::vector<std::shared_ptr<Triangle>>& getTriangles() const { return _triangles; }
    const std::vector<Edge>& getEdges() const { return _edges; }
    const std::vector<Point>& getVertices() const { return *_vertices; }
    std::pair<Triangle *, std::list<Triangle *> > getTriangle(const Point &p);
    double getDepth(const Point &p);

private:
    std::vector<std::shared_ptr<Triangle>> _triangles;
    std::vector<Edge> _edges;
    std::vector<Point>* _vertices;
    QuadTree* quadTree;
};

#endif // TRISNGULATIONLIB_H
