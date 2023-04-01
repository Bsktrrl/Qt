#ifndef LIGHT_H
#define LIGHT_H

#include "visualobject.h"

class Light : public VisualObject
{
public:
    Light();
    ~Light() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;

private:
    GLfloat mAmbientStrenght{0.3f};
    QVector3D mAmbientColor{0.3f, 0.3f, 0.3f};  //Grey

    GLfloat mLightStrenght{0.7f};
    QVector3D mLightColor{0.9f, 0.9f, 0.3f};    //Yellow

    GLfloat mSpecularStrenght{0.9f};
    GLint mSpecularExponent{4};
};

#endif // LIGHT_H
