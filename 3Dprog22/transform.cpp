#include "transform.h"
#include "gameobject.h"

Transform::Transform(GameObject* owner)
{
    mOwner = owner;
    mMatrix.setToIdentity();

}

Transform::~Transform()
{

}


std::pair<float, float> Transform::getPosition()
{
    auto col = mMatrix.column(3);
    return std::pair<float,float>(col.x(), col.y());
}

QVector3D Transform::getPosition3D()
{
    auto col = mMatrix.column(3);
    return QVector3D(col.x(), col.y(), col.z());
}



void Transform::move(float x, float y, float z)
{
    mMatrix.translate(x,y,z);
}
void Transform::move(QVector3D direction)
{
    mMatrix.translate(direction);
}


void Transform::setPosition(float x, float y, float z)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(x,y,z,position.w());
    mMatrix.setColumn(3, position);
}

void Transform::setPosition(QVector3D pos)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(pos.x(),pos.y(),pos.z(),position.w());
    mMatrix.setColumn(3, position);
}

void Transform::rotate(float angle, QVector3D vector)
{
    mMatrix.rotate(angle, vector);
}

float Transform::scale(float _scale)
{
    mMatrix.scale(_scale);
    return _scale;
}

void Transform::scale(QVector3D _scale)
{
    mMatrix.scale(_scale);
}
