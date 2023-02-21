#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"

class Collider;

class VisualObject : public QOpenGLFunctions_4_1_Core {

public:
   VisualObject();
   virtual ~VisualObject() = 0;

   virtual void init(GLint matrixUniform) = 0;
   virtual void draw() = 0;

   virtual void collission(VisualObject* other) {}

   void setActive(bool active) { isActive = active; }
   bool CollissionActive() const { return hasCollission; }
   void SetCollissionActive(bool active) { hasCollission = active; }

   Collider* getCollider() { return mCollider; }
   void setCollider(Collider* col) { mCollider = col; }

   void move(float x, float y, float z);
   void rotate(float x, float y, float z, float w);
   void rotate(float x, QVector3D q);
   void scale(float s);
   void scale(QVector3D s);


   void setPosition(float x, float y, float z);

   std::pair<float,float> getPosition();
   QVector3D getPosition3D();

   void setScene(int _sceneBelongingness) {sceneBelongingness = _sceneBelongingness;}
   int getScene() const {return sceneBelongingness;}

   void setName(std::string _name) {name = _name;}
   std::string getName() const {return name;}


protected:
   std::vector<Vertex> mVertices;

   GLuint mVAO{0};
   GLuint mVBO{0};
   GLint mMatrixUniform{0};
   QMatrix4x4 mMatrix;

   // Velger å lagre posisjon, rotasjon og translasjon
   // i hver sin 4x4 matrise
   QMatrix4x4 mPosition;
   QMatrix4x4 mRotation;
   QMatrix4x4 mScale;

   // Legger til rette for simulering
   QVector3D mVelocity;

   //Collider
   bool isActive;
   bool hasCollission;
   Collider* mCollider;

   int sceneBelongingness;
   std::string name;
};

#endif // VISUALOBJECT_H
