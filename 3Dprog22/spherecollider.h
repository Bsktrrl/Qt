#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include "QVector3D"

class VisualObject;

class SphereCollider : public Collider
{
public:
    SphereCollider(VisualObject* owner, float radius);
    SphereCollider(VisualObject* owner, float radius, QVector3D relativePos);

    void OnUpdate();
    float radius;

    QVector3D offset;
};

#endif // SPHERECOLLIDER_H
