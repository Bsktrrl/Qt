#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "visualobject.h"
#include "ppm.h"
#include "PerlinNoise.h"

class Landscape : public VisualObject
{
public:
    Landscape(std::string name);
    Landscape(std::string name, QVector2D bottomLeft, QVector2D topRight);
    ~Landscape() override;


    void init(GLint matrixUniform) override;
    void draw() override;

    static float f(float x, float y);
    Color recalc(float z);


};

#endif // LANDSCAPE_H
