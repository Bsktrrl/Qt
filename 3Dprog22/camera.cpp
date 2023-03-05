#include "camera.h"
#include "gameobject.h"


Camera::Camera()
    : mPosition(0,0,0)
{
    mVmatrix.setToIdentity();
    mPmatrix.setToIdentity();


    mPosition = QVector3D(-15, 0, 10);
    mForward = (QVector3D(0, 0, 0) - mPosition).normalized();
    mUp = QVector3D(0,0,1);
    mRight = QVector3D::crossProduct(mUp,mForward).normalized();

    follow = nullptr;
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{
    mVmatrix.setToIdentity();
    mPmatrix.setToIdentity();
    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;

    lookAt(mPosition,mPosition + mForward, mUp);
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.setToIdentity();
    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.setToIdentity();
    mVmatrix.lookAt(eye, at, up);
}

void Camera::update()
{
    if (follow != nullptr)
    {
        lookAt(follow->getPosition3D() - (mForward * 5), follow->getPosition3D(), mUp);
    }

    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());

}

void Camera::translate(float dx, float dy, float dz)
{
    if (follow == nullptr)
    {
        mPosition += mForward * dx;
        mPosition -= mRight * dy;
        mPosition += mUp * dz;

        lookAt(mPosition, mPosition + mForward, mUp);
    }

    if (follow != nullptr)
    {
        follow->setPosition(follow->getPosition3D() + (QVector3D(mForward.x(), mForward.y(), 0.f)) * dx);
        follow->setPosition(follow->getPosition3D() - (mRight * dy));
        follow->setPosition(follow->getPosition3D() + (mUp * dz));

        lookAt(follow->getPosition3D() - (mForward * 5), follow->getPosition3D(), mUp);
        mPosition = follow->getPosition3D() - (mForward * 5);
    }
}

void Camera::rotate(float pitch, float yaw, float roll)
{
    if (follow == nullptr)
    {
        QMatrix4x4 matrix;

        matrix.setToIdentity();
        matrix.rotate(yaw,mUp);
        mForward = matrix.map(mForward);
        mRight = QVector3D::crossProduct(mUp,mForward).normalized();

        matrix.rotate(pitch,mRight);
        mForward = matrix.map(mForward);
        //mUp = QVector3D::crossProduct(mForward, mRight).normalized();
        mUp = QVector3D(0,0,1);

        // call look at
        lookAt(mPosition, mPosition + mForward, mUp);
    }
    else
    {
        QMatrix4x4 matrix;

        matrix.setToIdentity();
        matrix.rotate(yaw,mUp);
        mForward = matrix.map(mForward);
        mRight = QVector3D::crossProduct(mUp,mForward).normalized();

        matrix.rotate(pitch,mRight);
        mForward = matrix.map(mForward);
        //mUp = QVector3D::crossProduct(mForward, mRight).normalized();
        mUp = QVector3D(0,0,1);

        // call look at
        lookAt(follow->getPosition3D() - (mForward * 5), follow->getPosition3D(), mUp);
        mPosition = follow->getPosition3D() - (mForward * 5);
    }


}


void Camera::setPosition(QVector3D position)
{
    mPosition = position;
    lookAt(mPosition, mPosition + mForward, mUp);
}

void Camera::setForward(QVector3D at)
{
    mForward = (at - mPosition).normalized();
    mRight = QVector3D::crossProduct(mUp,mForward).normalized();
    lookAt(mPosition, mPosition + mForward, mUp);
}
