#ifndef PARABEL_H
#define PARABEL_H

#include "visualobject.h"

class Parabel : public VisualObject
{
public:
    Parabel();
    Parabel(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Dx, float Dy, float Ex, float Ey, float Fx, float Fy, float Gx, float Gy);
    ~Parabel();

    float Xa;
    float Xb;
    float Xc;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

    float f(float z) {return (Xa * z * z) + (Xb * z) + Xc; };

private:
    //QGenericMatrix<7, 3, float> A;
    //QGenericMatrix<3, 7, float> At;
    //QMatrix3x3 B;
    //QGenericMatrix<3, 3, float> B_inverted;
};

#endif // PARABEL_H
