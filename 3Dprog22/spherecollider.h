#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include <QVector3D>

class SphereCollider : public Collider
{
public:
    SphereCollider(GameObject* owner, float radius);
    SphereCollider(GameObject* owner, float radius, QVector3D offset);
    virtual ~SphereCollider() override;

    void awake() override;
    void update() override;

    float radius;
    QVector3D offset;
};

#endif // SPHERECOLLIDER_H
