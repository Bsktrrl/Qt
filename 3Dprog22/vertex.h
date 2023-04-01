#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>
#include "Math.h"
#include <QVector3D>

class Vertex {
   //! Overloaded ostream operator which writes all vertex data on an open textfile stream
   friend std::ostream& operator<< (std::ostream&, const Vertex&);

   //! Overloaded ostream operator which reads all vertex data from an open textfile stream
   friend std::istream& operator>> (std::istream&, Vertex&);

public:
   //Vertex overloads
   Vertex();
   Vertex(float x, float y, float z, float r, float g, float b, float u, float v);
   Vertex(float x, float y, float z, float r, float g, float b);
   Vertex(Position position, Color color, UV uv);
   Vertex(Position position, Normal color, UV uv);
   Vertex(Position position, Color color);
   Vertex(Position position, Normal color);
   Vertex(QVector3D position, QVector3D normal);
   Vertex(QVector3D position, QVector3D normal, UV uv);

   //Get Full
   Position GetPosition() { return mPosition; }
   Color GetColor() { return mColor; }
   UV GetUV() { return mUV; }

   //Return variables
   float GetX() { return mPosition.x; }
   float GetY() { return mPosition.y; }
   float GetZ() { return mPosition.z; }

   float GetR() { return mColor.r; }
   float GetG() { return mColor.g; }
   float GetB() { return mColor.b; }

   float GetU() { return mUV.u; }
   float GetV() { return mUV.v; }

   //Set Variables
   void SetPosition(float x, float y, float z) { mPosition = Position(x, y, z); }
   void SetPosition(Position position) { mPosition = position; }

   void SetColor(float r, float g, float b) { mColor = Color(r, g, b); }
   void SetColor(Color color) { mColor = color; }

   void SetUV(float u, float v) { mUV = UV(u, v); }
   void SetUV(UV uv) { mUV = uv; }

   void SetX(float x) { mPosition.x = x; }
   void SetY(float y) { mPosition.y = y; }
   void SetZ(float z) { mPosition.z = z; }

   void SetR(float r) { mColor.r = r; }
   void SetG(float g) { mColor.g = g; }
   void SetB(float b) { mColor.b = b; }

   void SetU(float u) { mUV.u = u; }
   void SetV(float v) { mUV.v = v; }

   void SetNormal(QVector3D normal)
   {
       mColor = Color(normal.x(), normal.y(), normal.z());
   }

   QVector3D GetNormal() { return QVector3D(mColor.r, mColor.g, mColor.b); }

private:
   Position mPosition;
   Color mColor;
   UV mUV;
};

#endif // VERTEX_H
