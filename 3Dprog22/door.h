#ifndef DOOR_H
#define DOOR_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class Door : public GameObject
{
public:
    Door();
    ~Door() override;

    VisualObjectComponent* Mesh;
    SphereCollider* Collider;

    virtual void awake() override;
    virtual void update() override;
    void collission(GameObject* other) override;

private:
    bool openDoor;
    QVector3D doorClosedPos;
    QVector3D doorOpenPos;

    QVector3D pos;

};

#endif // DOOR_H
