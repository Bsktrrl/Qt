#ifndef POINTS_H
#define POINTS_H

#include "visualobject.h"


class Points : public VisualObject
{
public:
    Points();
    Points(float Ax = 0.f, float Ay = 0.f, float Bx = 0.f, float By = 0.f, float Cx = 0.f, float Cy = 0.f, float Dx = 0.f, float Dy = 0.f, float Ex = 0.f, float Ey = 0.f, float Fx = 0.f, float Fy = 0.f, float Gx = 0.f, float Gy = 0.f, float Hx = 0.f, float Hy = 0.f, float Ix = 0.f, float Iy = 0.f, float Jx = 0.f, float Jy = 0.f);

    virtual ~Points();

    virtual void init(GLint matrixUniform);
    virtual void draw();
    void draw(QMatrix4x4& transformMatrix) override;
};

#endif // POINTS_H
