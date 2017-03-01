#include "graphicsscene.h"

GraphicsScene::GraphicsScene()
{

}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(flagVertices)
    {
        points.push_back(Point(event->scenePos().x(), event->scenePos().y()));
        addEllipse(event->scenePos().x() - 3,
                   event->scenePos().y() - 3,
                   6,
                   6,
                   QPen(Qt::NoPen),
                   QBrush(Qt::blue));
    }
    else
    {
        point.set(event->scenePos().x(), event->scenePos().y());
        if(pointItem != nullptr) removeItem(pointItem);
        pointItem = addEllipse(event->scenePos().x() - 3,
                               event->scenePos().y() - 3,
                               6,
                               6,
                               QPen(Qt::NoPen),
                               QBrush(Qt::red));
    }
}

void GraphicsScene::slotRandomPoints()
{
    double x;
    double y;
    int num = rand() % 30 + 6;
    for(int i = 0; i < num; ++i)
    {
        x = rand() % 600 + 50;
        y = rand() % 300 + 50;
        points.push_back(Point(x, y));
        addEllipse(x - 3,
                   y - 3,
                   6,
                   6,
                   QPen(Qt::NoPen),
                   QBrush(Qt::blue));
    }
}

void GraphicsScene::slotStart()
{
    clear();
    for(auto &p : points)
    {
        addEllipse(p.x - 3,
                   p.y - 3,
                   6,
                   6,
                   QPen(Qt::NoPen),
                   QBrush(Qt::blue));
    }
    if(!flagVertices)
        pointItem = addEllipse(point.x - 3,
                               point.y - 3,
                               6,
                               6,
                               QPen(Qt::NoPen),
                               QBrush(Qt::red));
    DelaunayTrisngulation triangulation(points);
    std::vector<Edge> edges = triangulation.getEdges();
    for(auto &e : edges)
    {
        addLine(e.p1->x,
                e.p1->y,
                e.p2->x,
                e.p2->y,
                QPen(QBrush(Qt::blue), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
}

void GraphicsScene::slotLookFor()
{
    clear();
    for(auto &p : points)
    {
        addEllipse(p.x - 3,
                   p.y - 3,
                   6,
                   6,
                   QPen(Qt::NoPen),
                   QBrush(Qt::blue));
    }

    pointItem = addEllipse(point.x - 3,
                           point.y - 3,
                           6,
                           6,
                           QPen(Qt::NoPen),
                           QBrush(Qt::red));
    DelaunayTrisngulation triangulation(points);

    std::pair<Triangle*, std::list<Triangle*>> pair = triangulation.getTriangle(point);
    Triangle* triangle = pair.first;
    std::list<Triangle*> triangles = pair.second;
    for(auto &t : triangles)
    {
        addLine(t->p1->x,
                t->p1->y,
                t->p2->x,
                t->p2->y,
                QPen(QBrush(Qt::blue), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        addLine(t->p2->x,
                t->p2->y,
                t->p3->x,
                t->p3->y,
                QPen(QBrush(Qt::blue), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        addLine(t->p1->x,
                t->p1->y,
                t->p3->x,
                t->p3->y,
                QPen(QBrush(Qt::blue), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    addLine(triangle->p1->x,
            triangle->p1->y,
            triangle->p2->x,
            triangle->p2->y,
            QPen(QBrush(Qt::green), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    addLine(triangle->p2->x,
            triangle->p2->y,
            triangle->p3->x,
            triangle->p3->y,
            QPen(QBrush(Qt::green), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    addLine(triangle->p1->x,
            triangle->p1->y,
            triangle->p3->x,
            triangle->p3->y,
            QPen(QBrush(Qt::green), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

void GraphicsScene::slotVertices()
{
    flagVertices = true;
}

void GraphicsScene::slotPointLookFor()
{
    flagVertices = false;
    if(pointItem != nullptr)
    {
        removeItem(pointItem);
        pointItem = addEllipse(point.x - 3,
                               point.y - 3,
                               6,
                               6,
                               QPen(Qt::NoPen),
                               QBrush(Qt::red));
    }
}
