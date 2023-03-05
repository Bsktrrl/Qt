#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>
#include <QMatrix4x4>

class GameObject;

class Transform
{
public:
    Transform(GameObject* owner);
    ~Transform();


    void move(float x, float y, float z);
    void move(QVector3D direction);
    void setPosition(float x, float y, float z);
    void setPosition(QVector3D pos);
    void rotate(float angle, QVector3D vector);
    float scale(float _scale);
    void scale(QVector3D _scale);


    std::pair<float,float> getPosition();
    QVector3D getPosition3D();

    QMatrix4x4& getMatrix() { return mMatrix; }

private:
    QMatrix4x4 mMatrix;
    GameObject* mOwner;
};



#endif // TRANSFORM_H
