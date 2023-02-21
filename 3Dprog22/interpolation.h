#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "visualobject.h"

class Interpolation : public VisualObject
{
public:
    Interpolation(std::string name);
    Interpolation(std::string name, QVector2D a, QVector2D b, QVector2D c, QVector2D d);

    ~Interpolation() override;

    void init(GLint matrixUniform) override;
    void draw() override;

private:
    QMatrix4x4 A;
    QMatrix4x4 IA;

    QVector4D B;
    QVector4D X;
};

#endif // INTERPOLATION_H
