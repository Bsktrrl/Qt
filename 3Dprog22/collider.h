#ifndef COLLIDER_H
#define COLLIDER_H
#include "component.h"

class GameObject;

class Collider : public Component
{
public:
    Collider();
    virtual ~Collider() {};
    virtual void awake() = 0;
    virtual void update() = 0;

    GameObject* owner;
};

#endif // COLLIDER_H
