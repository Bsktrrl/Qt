#ifndef CAMERA_H
#define CAMERA_H

#include <QOpenGLFunctions_4_1_Core>
#include <QVector3D>
#include <QMatrix4x4>

class Camera : public QOpenGLFunctions_4_1_Core
{
private:
   GLint  mPmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   GLint  mVmatrixUniform;        //OpenGL reference to the Uniform in the shader program
   QVector3D mPosition;
   QMatrix4x4 mPmatrix{};
   QMatrix4x4 mVmatrix{};
   QMatrix4x4 mRotation{};

   //Camera Position
   QVector3D mForward;
   QVector3D mRight;
   QVector3D mUp;

public:
   Camera();
   ~Camera() { }

   void init(GLint pMatrixUniform, GLint vMatrixUniform);
   void perspective(int degrees, double aspect, double nearplane, double farplane);
   void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
   void translate(float dx, float dy, float dz);
   void rotate (float pitch, float yaw, float roll);

   void update();

   void setPosition(QVector3D pos);
   void setForward(QVector3D pos);
};

#endif // CAMERA_H
