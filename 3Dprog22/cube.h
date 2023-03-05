#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"

class Cube : public VisualObject
{
public:
    Cube();
    ~Cube() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;
};

#endif // CUBE_H
