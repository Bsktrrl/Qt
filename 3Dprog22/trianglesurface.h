#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "visualobject.h"

class TriangleSurface : public VisualObject
{

public:
   TriangleSurface();
   TriangleSurface(std::string filnavn);
   ~TriangleSurface() override;

   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
   void draw(QMatrix4x4& transformMatrix) override;
   void draw(GLint textureUniform) override;
   void draw(GLint textureUniform, QMatrix4x4& transformMatrix) override;

   void DrawTexture();

private:
   unsigned int texture;
};

#endif //TRIANGLESURFACE_H
