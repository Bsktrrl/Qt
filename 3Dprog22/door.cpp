#include "door.h"
#include "visualobjectcomponent.h"
#include "cube.h"
#include "spherecollider.h"
#include "renderwindow.h"

Door::Door()
{
    setName("Door");

    Mesh = new VisualObjectComponent(new Cube(), this);
    setRootComponent(Mesh);

    Collider = new SphereCollider(this, 1, QVector3D(0, 1, -1));
    Collider->setupAttachment(Mesh);


    //-----


    openDoor = false;
    pos = QVector3D(5, 0, 2);
    transform->setPosition(pos);
    transform->scale(QVector3D(0.1f, 1.5f, 3.5f));
    doorOpenPos = pos - QVector3D(0, 0, 3);
}

Door::~Door()
{

}

void Door::awake()
{
    GameObject::awake();
}

void Door::update()
{
    GameObject::update();

    if (openDoor)
    {
        pos += QVector3D(0, 0, -0.1f);
        setPosition(pos);

        if(pos.z() < doorOpenPos.z())
        {
            RenderWindow::instance->ChangeScene(2);
            openDoor = false;
        }
    }
}

void Door::collission(GameObject *other)
{
    if(other->getName() == "Player")
    {
        if(RenderWindow::Keymap[Qt::Key_E])
        {
            openDoor = true;
        }
    }
}
