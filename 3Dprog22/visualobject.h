#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex.h"

class Collider;

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:
    VisualObject();
    virtual ~VisualObject()=0;
    virtual void init(GLint matrixUniform)=0;
    virtual void draw()=0;
    virtual void draw(QMatrix4x4& transformMatrix) = 0;

    void readFile(std::string filename, bool Indexing = false);
    void writeFile(std::string filename, bool Indexing = false);

    void setActive(bool active) { isActive = active; }

    void move(float x, float y, float z);
    void setPosition(float x, float y, float z);
    void setPosition(QVector3D pos);
    void rotate(float angle, QVector3D vector);
    void scale(float scale);
    void scale(QVector3D scale);
    std::pair<float,float> getPosition();
    QVector3D getPosition3D();

    void setScene(int _scene) { scene = _scene; }
    int getScene() { return scene; }


protected:
    std::vector<Vertex> mVertices;
    std::vector<GLuint> mIndices;   	// Til indeksering
    GLuint mVAO{0};
    GLuint mVBO{0};
    GLuint mIBO{0};                 		// for glDrawElements()
    GLint mMatrixUniform{0};

    QMatrix4x4 mMatrix;

    bool isActive;
    int scene;
};

#endif // VISUALOBJECT_H
