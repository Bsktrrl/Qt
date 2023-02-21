#ifndef HOUSE_H
#define HOUSE_H

#include "visualobject.h"

class House : public VisualObject
{
public:
    House(std::string name);
    ~House() override;

    void init(GLint matrixUniform) override;
    void draw() override;
};

#endif // HOUSE_H
