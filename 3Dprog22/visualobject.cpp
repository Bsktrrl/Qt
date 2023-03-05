#include "visualobject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
    isActive = true;
}

VisualObject::~VisualObject()
{
   glDeleteVertexArrays( 1, &mVAO );
   glDeleteBuffers( 1, &mVBO );
}

void VisualObject::readFile(std::string filename, bool Indexing)
{
    if (Indexing)
    {
        std::ifstream inn;
        inn.open(filename.c_str());

        if (inn.is_open()) {
            int ni;
            int nv;

            inn >> ni;
            inn >> nv;
            mIndices.reserve(ni);
            mVertices.reserve(nv);
            GLuint index;
            for (int i=0; i<nv; i++) {
                inn >> index;
                mIndices.push_back(index);
            }

            Vertex vertex;
            for (int i=0; i<nv; i++) {
                inn >> vertex;
                mVertices.push_back(vertex);
            }
            inn.close();
        }
        return;
    }
    std::ifstream inn;
    inn.open(filename.c_str());

    if (inn.is_open()) {
        int n;
        Vertex vertex;
        inn >> n;
        mVertices.reserve(n);
        for (int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
        }
        inn.close();
    }
}

void VisualObject::writeFile(std::string filename, bool Indexing)
{
    if (Indexing)
    {
        std::ifstream inn;
        inn.open(filename.c_str());


        if (inn.is_open())
        {
            int ni, nv, indeks;
            inn >> ni;
            mIndices.reserve(ni);
            inn >> nv;
            mVertices.reserve(nv);

            for (int i=0; i<ni; i++) { inn >> indeks; mIndices.push_back(indeks); }
            Vertex vertex;
            for (int i=0; i<nv; i++) { inn >> vertex; mVertices.push_back(vertex); }


            inn.close();
        }
        return;
    }

    // Write mesh to file
    std::fstream data;
    data.open(filename.c_str(),  std::fstream::in | std::fstream::out | std::fstream::trunc);

    data << mVertices.size() << std::endl << std::endl;

    for(size_t i = 0; i < mVertices.size(); i++)
    {
        data << mVertices[i] << std::endl;
        std::cout << std::endl;
    }

    data.close();
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x,y,z);
}

void VisualObject::setPosition(float x, float y, float z)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(x,y,z,position.w());
    mMatrix.setColumn(3, position);
}

void VisualObject::setPosition(QVector3D pos)
{
    QVector4D position = mMatrix.column(3);
    position = QVector4D(pos.x(),pos.y(),pos.z(),position.w());
    mMatrix.setColumn(3, position);
}

void VisualObject::rotate(float angle, QVector3D vector)
{
    mMatrix.rotate(angle, vector);
}


void VisualObject::scale(float _scale)
{
    mMatrix.scale(_scale);
}

void VisualObject::scale(QVector3D scale)
{
    mMatrix.scale(scale);
}

std::pair<float, float> VisualObject::getPosition()
{
    auto col = mMatrix.column(3);
    return std::pair<float,float>(col.x(), col.y());
}

QVector3D VisualObject::getPosition3D()
{
    auto col = mMatrix.column(3);
    return QVector3D(col.x(), col.y(), col.z());
}
