#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"

class VisualObjectComponent;
class SphereCollider;

class Player : public GameObject
{
public:
    Player();
    ~Player() override;

    VisualObjectComponent* Mesh;
    SphereCollider* Collider;

    virtual void awake() override;
    virtual void update() override;
    void collission(GameObject* other) override;
};

#endif // PLAYER_H
