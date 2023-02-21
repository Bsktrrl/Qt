#ifndef DOOR_H
#define DOOR_H

#include "visualobject.h"

class SphereCollider;

class Door : public VisualObject
{
public:
    Door(std::string name);
    ~Door() override;

    void init(GLint matrixUniform) override;
    void draw() override;

    void collission(VisualObject* other) override;

    SphereCollider* collider;



private:
    bool doorAnim;
    bool doorIsOpen;

    QVector3D doorPos;
    QVector3D doorClosedPos;
    QVector3D doorOpenPos;
};

#endif // DOOR_H
