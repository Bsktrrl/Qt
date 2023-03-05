#include "pickup.h"
#include "octahedronball.h"
#include "spherecollider.h"
#include "visualobjectcomponent.h"

PickUp::PickUp()
{
    setName("PickUp");

    Mesh = new VisualObjectComponent(new OctahedronBall(), this);
    setRootComponent(Mesh);

    collider = new SphereCollider(this, 1, QVector3D(0, 1, -1));
    collider->setupAttachment(Mesh);

    //Set Position
    int angle = std::rand() % 361;
    float radian = angle * (M_PI / 180);

    QVector3D randomVector = QVector3D(cos(radian), sin(radian), 0);

    int amp = 1 + std::rand() % 3;
    randomVector *= amp;

    setPosition(randomVector);
}

PickUp::~PickUp()
{

}

void PickUp::awake()
{
    GameObject::awake();
}

void PickUp::update()
{
    GameObject::update();
}

void PickUp::collission(GameObject *other)
{
    if(other->getName() == "Player")
    {
        this->setActive(false);
    }
}
