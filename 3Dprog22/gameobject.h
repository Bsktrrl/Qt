#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <iostream>
#include <QVector3D>
#include "transform.h"

class Component;
class Collider;
class PhysicsComponent;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject() {};

    virtual void awake();
    virtual void update();

    void AddComponent(Component* component);
    void Instantiate(GameObject* objectToSpawn, int scene, std::string name);
    void Instantiate(GameObject* objectToSpawn, QVector3D position, int scene, std::string name);
    void setRootComponent(Component* comp) { rootComponent = comp; }
    Component* getRootComponent() { return rootComponent; }

    Transform* transform;

private:
    std::vector<Component*> mComponents;
    Component* rootComponent;
    std::string name;

    bool hasCollission;
    Collider* mCollider;
    PhysicsComponent* physics;

    int scene;
    bool isActive;
    bool simulatePhysics;


public:
    void setScene(int _scene){ scene = _scene; }
    int getScene() const { return scene; }

    void setName(std::string _name) { name = _name; }
    std::string getName() const { return name; }

    void setActive(bool active);

    template<class T>
    T* GetComponent();

    bool CollissionActive() const { return hasCollission; }
    void SetCollissionActive(bool active) { hasCollission = active; }
    Collider* getCollider() { return mCollider; }
    void setCollider(Collider* col) { mCollider = col; }

    void setSimulatePhysics(bool input) { simulatePhysics = true; }
    bool simulatingPhysics() { return simulatePhysics; }
    void setPhysicsComponent(PhysicsComponent* _physics) { physics = _physics; }
    PhysicsComponent* getPhysicsComponent() { return physics; }

    virtual void collission(GameObject* other) {}

    QVector3D getPosition3D();
    void setPosition(float x, float y, float z);
    void setPosition(QVector3D pos);
    void move(float x, float y, float z);

    void addForce(QVector3D force);

};



template<class T>
T* GameObject::GetComponent()
{
    for (auto it = mComponents.begin(); it != mComponents.end();it++)
    {
        if ((T*)(*it))
        {
            T* returnValue = (T*)(*it);
            return returnValue;
        }
    }
    return nullptr;
}


#endif // GAMEOBJECT_H
