#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "visualobject.h"

class TriangleSurface : public VisualObject
{

public:
   TriangleSurface(std::string name);
   TriangleSurface(std::string name, std::string filnavn);
   ~TriangleSurface() override;

   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
};

#endif //TRIANGLESURFACE_H
