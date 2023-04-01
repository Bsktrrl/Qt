#ifndef BARYSENTRISK_H
#define BARYSENTRISK_H

#include <QVector3D>
#include "vertex.h"
#include "visualobject.h"
#include "gameobject.h"

class barysentrisk
{
public:
    barysentrisk();

    float w_1(Vertex vA, Vertex vB, Vertex vC, QVector3D p);
    float w_2(Vertex vA, Vertex vB, Vertex vC, QVector3D p, float w1);

    bool isOnTriangle(float w1, float w2);

    float triangleHeight(GameObject* playerPos, VisualObject* landscape);

    QVector3D setPlayerPosition();

    QVector3D baryCoords(Vertex a, Vertex b, Vertex c, QVector3D p);
};

#endif // BARYSENTRISK_H
