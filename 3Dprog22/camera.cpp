#include "camera.h"

Camera::Camera()
    : mPosition{0, 0, -5}
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
    mRotation.setToIdentity();

    mPosition = QVector3D(-15, 0, 10);
    mForward = (QVector3D(0, 0, 0) - mPosition).normalized();
    mUp = QVector3D(0, 0, 1);
    mRight = QVector3D::crossProduct(mUp, mForward).normalized();
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
    mRotation.setToIdentity();

    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;

    lookAt(mPosition, mPosition + mForward, mUp);
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.setToIdentity();
    mVmatrix.lookAt(eye, at, up);
}

void Camera::translate(float dx, float dy, float dz)
{
    mPosition += (mForward/ 100.f) * dx;
    mPosition += (mRight/ 100.f) * dy;
    mPosition += (mUp/ 100.f) * dz;

    lookAt(mPosition, mPosition + mForward, mUp);
}

void Camera::rotate(float pitch, float yaw, float roll)
{
    QMatrix4x4 matrix;

    matrix.setToIdentity();
    matrix.rotate(yaw, mUp);
    mForward = matrix.map(mForward);
    mRight = QVector3D::crossProduct(mUp, mForward).normalized();

    matrix.rotate(pitch, mRight);
    mForward = matrix.map(mForward);

    mUp = QVector3D(0, 0, 1);


//    //Yaw
//    QVector3D newForward = QVector3D();
//    float yawRad = yaw * (M_PI / 180.f);

//    newForward.setX((mForward.x() * cos(yawRad)) - (mForward.y() * sin(yawRad)));
//    newForward.setY((mForward.x() * sin(yawRad)) + (mForward.y() * cos(yawRad)));
//    newForward.setZ(mForward.z());

//    mForward = newForward.normalized();
//    mRight = QVector3D::crossProduct(mUp, mForward).normalized();


//    //Pitch
//    QVector3D newForward2 = QVector3D();
//    float pitchRad = pitch * (M_PI / 180.f);

//    newForward2.setX((mForward.x() * cos(pitchRad)) - (mForward.z() * sin(pitchRad)));
//    newForward2.setY(mForward.y());
//    newForward2.setZ((mForward.x() * -sin(pitchRad)) + (mForward.z() * cos(pitchRad)));

//    mForward = newForward2.normalized();
//    mUp = QVector3D::crossProduct(mForward, mRight).normalized();


    //Update the view
    lookAt(mPosition, mPosition + mForward, mUp);
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::setPosition(QVector3D pos)
{
    mPosition = pos;
    lookAt(mPosition, mPosition * mForward, mUp);
}

void Camera::setForward(QVector3D pos)
{
    mForward = (pos - mPosition).normalized();
    mRight = QVector3D::crossProduct(mUp, mForward).normalized();
    lookAt(mPosition, mPosition * mForward, mUp);
}
