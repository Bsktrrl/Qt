#include "houseobject.h"
#include "trianglesurface.h"
#include "spherecollider.h"
#include "visualobjectcomponent.h"
#include "house.h"

HouseObject::HouseObject()
{
    setName("HouseObject");

    Mesh = new VisualObjectComponent(new House(), this);
    Mesh->setIsActive(false);
    //Mesh->getObject()->setPosition(0, 0, 0);
    //Mesh->getObject()->scale(QVector3D(1, 1, 1));
    //Mesh->getObject()->rotate(270, QVector3D(0, 0, 1));
    setRootComponent(Mesh);

    TextureMesh = new VisualObjectComponent(new House(), this, "TextureShader"); // - Sjekk denne etterpå
    TextureMesh->getObject()->scale(QVector3D(1, 1, 1));

    collider = new SphereCollider(this, 0.5, QVector3D(0, 1, -1));
    collider->setupAttachment(Mesh);

    //Set Position
    int angle = std::rand() % 361;
    float radian = angle * (M_PI / 180);

    QVector3D randomVector = QVector3D(cos(radian), sin(radian), 0);

    int amp = 1 + std::rand() % 3;
    randomVector *= amp;

    setPosition(randomVector);
}

HouseObject::~HouseObject()
{

}

void HouseObject::awake()
{
    GameObject::awake();
}

void HouseObject::update()
{
    GameObject::update();
}

void HouseObject::collission(GameObject *other)
{
    //No collission
}
