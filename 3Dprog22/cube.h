#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"

class Cube : public VisualObject
{
public:
    Cube();
    Cube(float x, float y, float z, float r, float g,float b);
    Cube(float x, float y, float z, float r, float g,float b, float u, float v);
    ~Cube() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

private:
    float mx, my, mz;
    float colourX, colourY, colourZ;
};

#endif // CUBE_H
