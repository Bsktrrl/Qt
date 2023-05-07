#ifndef MOVEMENTBALL_H
#define MOVEMENTBALL_H
#include "visualobject.h"

class MovementBall : public VisualObject
{
public:
    MovementBall(int n=4);
    ~MovementBall();

    void init(GLint matrixUniform) override;
    void draw() override;
    void draw(QMatrix4x4& transformMatrix) override;
    void draw(GLint textureUniform) override;
    void draw(GLint textureUniform, QMatrix4x4& transformMatrix) override;

 private:
    int m_recursions;
    int m_indeks;               // brukes i rekursjon, til å bygge m_vertices

    void MakeTriangle(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
    void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);

    void oktaederUnitBall();

     unsigned int texture;
};

#endif // MOVEMENTBALL_H
