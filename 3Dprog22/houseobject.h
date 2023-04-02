#ifndef HOUSEOBJECT_H
#define HOUSEOBJECT_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class HouseObject : public GameObject
{
public:
    HouseObject();
    ~HouseObject();

    virtual void awake();
    virtual void update();

    virtual void collission(GameObject* other);

    VisualObjectComponent* Mesh;
    VisualObjectComponent* TextureMesh;
    SphereCollider* collider;
};

#endif // HOUSEOBJECT_H
