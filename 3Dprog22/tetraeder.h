#ifndef TETRAEDER_H
#define TETRAEDER_H

#include "visualobject.h"

class Tetraeder : public VisualObject
{
public:
    Tetraeder(std::string name);
    Tetraeder(std::string name, Position pos, QVector3D scale);
    ~Tetraeder();

    void init(GLint matrixUniform) override;
    void draw() override;

private:
    QVector2D rotatePoint(QVector2D point, float angle);
};

#endif // TETRAEDER_H
