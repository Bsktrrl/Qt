#include "visualobjectcomponent.h"
#include "visualobject.h"
#include "renderwindow.h"
#include "gameobject.h"
#include "transform.h"
#include "uniforms.h"

VisualObjectComponent::VisualObjectComponent(VisualObject *object, GameObject* owner, std::string shader)
    : mObject(object), shaderName(shader)
{
    if (shader == "TextureShader")
    {
        isUsingTexture = true;
    }
    else
    {
        isUsingTexture = false;
    }

    SetOwner(owner);
    owner->AddComponent(this);

}

VisualObjectComponent::~VisualObjectComponent()
{

}

void VisualObjectComponent::awake()
{
    GLint mUniform;

    Shader* shader = RenderWindow::instance->GetShader(shaderName);
    mUniform = shader->getUniform()->mMmatrixUniform;
    init(mUniform);
}

void VisualObjectComponent::update()
{
    RenderWindow::instance->runProgram(shaderName);

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
    if (isUsingTexture)
    {
        Shader* shader = RenderWindow::instance->GetShader(shaderName);
        GLint mUniform = shader->getUniform()->mMmatrixUniform;

        if(mObject != nullptr)
        {
            mObject->draw(mUniform, transformMatrix);
        }
    }
    else
    {
        if(mObject != nullptr)
        {
            mObject->draw(transformMatrix);
        }
    }
}
