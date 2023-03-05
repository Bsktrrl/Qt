#include "player.h"
#include "octahedronball.h"
#include "visualobjectcomponent.h"
#include "spherecollider.h"

#include "logger.h"

Player::Player()
{
    setName("Player");

    Mesh = new VisualObjectComponent(new OctahedronBall(), this);
    setRootComponent(Mesh);

    Collider = new SphereCollider(this, 1, QVector3D(0, 1, -1));
    Collider->setupAttachment(Mesh);
}

Player::~Player()
{

}

void Player::awake()
{
    GameObject::awake();
}

void Player::update()
{
    GameObject::update();
}

void Player::collission(GameObject *other)
{
    Logger::getInstance()->logText("PlayerDColliding");
}
