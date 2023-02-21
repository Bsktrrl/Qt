#ifndef PLAYER_H
#define PLAYER_H

#include "visualobject.h"

class SphereCollider;

class Player : public VisualObject
{
public:
    Player(std::string name, int n = 0);
    ~Player() override;

    void init(GLint matrixUniform) override;
    void draw() override;

    SphereCollider* collider;
    void collission(VisualObject* other) override;

private:
    int m_recursions;
    int m_indeks;

    void MakeTriangle(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
    void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);

    void PlayerBuild();
};

#endif // PLAYER_H
