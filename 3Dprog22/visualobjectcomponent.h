#ifndef VISUALOBJECTCOMPONENT_H
#define VISUALOBJECTCOMPONENT_H

#include "component.h"
#include <QMatrix4x4>

class VisualObject;

typedef int GLint;


class VisualObjectComponent : public Component
{
public:
    VisualObjectComponent(VisualObject* object, GameObject* owner, std::string shader = "PlainShader");
    virtual ~VisualObjectComponent() override;

    void awake() override;
    void update() override;

    void setIsActive(bool active) override;
    VisualObject* getObject() { return mObject; }

private:
    void init(GLint mMatrixUniform);
    void render(QMatrix4x4& transformMatrix);


private:
    VisualObject* mObject;
    std::string shaderName;
    bool isUsingTexture;
};

#endif // VISUALOBJECTCOMPONENT_H
