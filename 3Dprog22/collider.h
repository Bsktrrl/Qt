#ifndef COLLIDER_H
#define COLLIDER_H

class VisualObject;

class Collider
{
public:
    Collider();

    VisualObject* owner;
};

#endif // COLLIDER_H
