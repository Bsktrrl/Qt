#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    Component();
    virtual ~Component() {};
    virtual void awake() = 0;
    virtual void update() = 0;

    void SetOwner(GameObject* owner) { mOwner = owner; }
    GameObject* GetOwner() { return mOwner; }

    virtual void setIsActive(bool active) { mActive = active; }
    bool IsActive() { return mActive; }

    void setupAttachment(Component* comp) { attachment = comp; }
    Component* parent() { return attachment; }

private:
    GameObject* mOwner;
    Component* attachment;
    bool mActive;
};

#endif // COMPONENT_H
