#ifndef PICKUP_H
#define PICKUP_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class PickUp : public GameObject
{
public:
    PickUp();
    ~PickUp();

    virtual void awake();
    virtual void update();

    virtual void collission(GameObject* other);

    VisualObjectComponent* Mesh;
    VisualObjectComponent* TextureMesh;
    SphereCollider* collider;
};

#endif // PICKUP_H
