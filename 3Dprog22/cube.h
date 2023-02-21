#ifndef CUBE_H
#define CUBE_H

#include "visualobject.h"

class Cube : public VisualObject
{
public:
    Cube(std::string name);
    ~Cube() override;

    void init(GLint matrixUniform) override;
    void draw() override;
};

#endif // CUBE_H
