#include "visualobjectcomponent.h"
#include "visualobject.h"
#include "renderwindow.h"
#include "gameobject.h"
#include "transform.h"

VisualObjectComponent::VisualObjectComponent(VisualObject *object, GameObject* owner)
    : mObject(object)
{
    SetOwner(owner);
    owner->AddComponent(this);
}

VisualObjectComponent::~VisualObjectComponent()
{

}

void VisualObjectComponent::awake()
{
    GLint mUniform = RenderWindow::instance->GetMatrixUniform();
    init(mUniform);
}

void VisualObjectComponent::update()
{
    if (IsActive())
    {
        render(GetOwner()->transform->getMatrix());
    }

}

void VisualObjectComponent::setIsActive(bool active)
{
    if (mObject != nullptr)
    {
        mObject->setActive(active);
    }
}

void VisualObjectComponent::init(GLint matrixUniform)
{
    if(mObject != nullptr)
    {
        mObject->init(matrixUniform);
    }
}

void VisualObjectComponent::render(QMatrix4x4& transformMatrix)
{
    if(mObject != nullptr)
    {
        mObject->draw(transformMatrix);
    }
}
