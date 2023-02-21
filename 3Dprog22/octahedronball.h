#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H

#include "visualobject.h"

class SphereCollider;

class OctahedronBall : public VisualObject
{
public:
   OctahedronBall(std::string name, int n=0);
   ~OctahedronBall();

   void init(GLint matrixUniform) override;
   void draw() override;

   SphereCollider* collider;
   void collission(VisualObject* other) override;

private:
   int m_recursions;
   int m_indeks;               // brukes i rekursjon, til å bygge m_vertices

   void MakeTriangle(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
   void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);

   void oktaederUnitBall();
};

#endif // OCTAHEDRONBALL_H
