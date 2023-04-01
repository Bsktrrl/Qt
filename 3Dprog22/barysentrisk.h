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

    float T_ABC(Vertex vA, Vertex vB, Vertex vC);

    float T_ABX(Vertex vA, Vertex vB, QVector3D x, float t_abc);
    float T_BCX(Vertex vB, Vertex vC, QVector3D x, float t_abc);
    float T_CAX(Vertex vC, Vertex vA, QVector3D x, float t_abc);

    float bary(GameObject* playerPos, VisualObject* landscape);
};

#endif // BARYSENTRISK_H
