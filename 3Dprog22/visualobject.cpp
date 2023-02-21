// VisualObject.cpp
#include "visualobject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();

    //Collision
    isActive = true;
    hasCollission = false;
}

VisualObject::~VisualObject()
{
   glDeleteVertexArrays( 1, &mVAO );
   glDeleteBuffers( 1, &mVBO );
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
}

void VisualObject::rotate(float x, float y, float z, float w)
{
    mMatrix.rotate(x, y, z, w);
}

void VisualObject::rotate(float x, QVector3D q)
{
    mMatrix.rotate(x, q);
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::scale(QVector3D s)
{
    mMatrix.scale(s);
}

void VisualObject::setPosition(float x, float y, float z)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(x, y, z, position.w());
    mMatrix.setColumn(3, position);
}

std::pair<float, float> VisualObject::getPosition()
{
    auto col = mMatrix.column(3);

    return std::pair<float, float>(col.x(), col.y());
}

QVector3D VisualObject::getPosition3D()
{
    auto col = mMatrix.column(3);

    return QVector3D(col.x(), col.y(), col.z());
}
