#include "spherecollider.h"
#include "gameobject.h"
#include "renderwindow.h"

SphereCollider::SphereCollider(GameObject* _owner, float _radius)
{
    owner = _owner;
    offset = QVector3D(0,0,0);
    radius = _radius;
    owner->SetCollissionActive(true);
    owner->setCollider(this);
    owner->AddComponent(this);
}

SphereCollider::SphereCollider(GameObject* _owner, float _radius, QVector3D relativePos)
{
    owner = _owner;
    offset = relativePos;
    radius = _radius;
    owner->SetCollissionActive(true);
    owner->setCollider(this);
    owner->AddComponent(this);
}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::awake()
{

}

void SphereCollider::update()
{
    std::vector<GameObject*> objects = RenderWindow::instance->GetColliderObjects(owner->getScene());

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if ((*it) != owner)
        {

            float distance = (owner->getPosition3D() + offset).distanceToPoint((*it)->getPosition3D());

            Collider* col = (*it)->getCollider();
            SphereCollider* sphere = (SphereCollider*)col;
            float otherRadius = sphere->radius;

            if (distance < radius + otherRadius)
            {
                owner->collission((*it));
                (*it)->collission(owner);
            }
        }
    }
}
