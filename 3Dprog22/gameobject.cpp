#include "gameobject.h"
#include "component.h"
#include "renderwindow.h"
//#include "physicscomponent.h"

GameObject::GameObject()
{
    isActive = true;
    hasCollission = false;
    simulatePhysics = false;

    transform = new Transform(this);
}

void GameObject::awake()
{
    for (auto it = mComponents.begin(); it != mComponents.end();it++)
    {
        (*it)->awake();
    }
}

void GameObject::update()
{
    for (auto it = mComponents.begin(); it != mComponents.end();it++)
    {
        (*it)->update();
    }
}

void GameObject::AddComponent(Component *component)
{
    mComponents.push_back(component);
}

void GameObject::Instantiate(GameObject *objectToSpawn, int scene, std::string name)
{
    objectToSpawn->awake();
    objectToSpawn->setName(name);
    objectToSpawn->setScene(scene);
    RenderWindow::instance->AddGameObject(objectToSpawn, name);
}

void GameObject::Instantiate(GameObject *objectToSpawn, QVector3D position, int scene, std::string name)
{
    objectToSpawn->awake();
    objectToSpawn->setName(name);
    objectToSpawn->setPosition(position);
    objectToSpawn->setScene(scene);
    RenderWindow::instance->AddGameObject(objectToSpawn, name);
}

void GameObject::setActive(bool active)
{
    isActive = active;
    for (auto it = mComponents.begin(); it != mComponents.end();it++)
    {
        (*it)->setIsActive(active);
    }
}

QVector3D GameObject::getPosition3D()
{
    return transform->getPosition3D();
}

void GameObject::setPosition(float x, float y, float z)
{
    transform->setPosition(x,y,z);
}

void GameObject::setPosition(QVector3D pos)
{
    transform->setPosition(pos);
}

void GameObject::move(float x, float y, float z)
{
    transform->move(x,y,z);
}

void GameObject::addForce(QVector3D force)
{
//    if (simulatePhysics)
//    {
//        if (physics != nullptr)
//        {
//            physics->addForce(force);
//        }
//    }
}
