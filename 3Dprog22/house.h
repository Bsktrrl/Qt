#ifndef HOUSE_H
#define HOUSE_H

#include "visualobject.h"

class House : public VisualObject
{
public:
    House();
    ~House() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;
    void draw(GLint textureUniform) override;
    void draw(GLint textureUniform, QMatrix4x4& transformMatrix) override;

private:
    unsigned int texture;
};

#endif // HOUSE_H
