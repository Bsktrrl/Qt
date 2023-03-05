#ifndef XYZ_H
#define XYZ_H

#include "visualobject.h"

class XYZ : public VisualObject
{

public:
    XYZ();
    ~XYZ() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;
};

#endif // XYZ_H
