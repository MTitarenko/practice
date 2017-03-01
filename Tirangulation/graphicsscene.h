#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include "trisngulationlib.h"

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

public slots:
    void slotStart();
    void slotLookFor();
    void slotVertices();
    void slotPointLookFor();
    void slotRandomPoints();

private:
    std::vector<Point> points;
    Point point;
    bool flagVertices = true;
    QGraphicsItem* pointItem = nullptr;
};

#endif // GRAPHICSSCENE_H
