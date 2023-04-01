#include "cube.h"

Cube::Cube() : VisualObject()
{
   // -y veggen
   mVertices.push_back(Vertex{-1, -1, -1,    1, 0, 0});
   mVertices.push_back(Vertex{ 1, -1,  1,    1, 0, 0});
   mVertices.push_back(Vertex{-1, -1,  1,    1, 0, 0});
   mVertices.push_back(Vertex{-1, -1, -1,    1, 0, 0});
   mVertices.push_back(Vertex{ 1, -1, -1,    1, 0, 0});
   mVertices.push_back(Vertex{ 1, -1,  1,    1, 0, 0});

   // -z veggen
   mVertices.push_back(Vertex{-1, -1, -1,    1, 1, 0});
   mVertices.push_back(Vertex{ 1, -1, -1,    1, 1, 0});
   mVertices.push_back(Vertex{-1,  1, -1,    1, 1, 0});
   mVertices.push_back(Vertex{ 1, -1, -1,    1, 1, 0});
   mVertices.push_back(Vertex{ 1,  1, -1,    1, 1, 0});
   mVertices.push_back(Vertex{-1,  1, -1,    1, 1, 0});

   // -x veggen
   mVertices.push_back(Vertex{-1,  1, -1,    1, 0, 1});
   mVertices.push_back(Vertex{-1, -1, -1,    1, 0, 1});
   mVertices.push_back(Vertex{-1, -1,  1,    1, 0, 1});
   mVertices.push_back(Vertex{-1,  1, -1,    1, 0, 1});
   mVertices.push_back(Vertex{-1, -1,  1,    1, 0, 1});
   mVertices.push_back(Vertex{-1,  1,  1,    1, 0, 1});

   // +y veggen
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 1, 0});
   mVertices.push_back(Vertex{-1,  1,  1,    0, 1, 0});
   mVertices.push_back(Vertex{-1,  1, -1,    0, 1, 0});
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 1, 0});
   mVertices.push_back(Vertex{-1,  1, -1,    0, 1, 0});
   mVertices.push_back(Vertex{ 1,  1, -1,    0, 1, 0});

   // + z veggen
   mVertices.push_back(Vertex{-1, -1,  1,    0, 0, 1});
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 0, 1});
   mVertices.push_back(Vertex{-1,  1,  1,    0, 0, 1});
   mVertices.push_back(Vertex{-1, -1,  1,    0, 0, 1});
   mVertices.push_back(Vertex{ 1, -1,  1,    0, 0, 1});
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 0, 1});

   // + x veggen
   mVertices.push_back(Vertex{ 1, -1, -1,    0, 1, 1});
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 1, 1});
   mVertices.push_back(Vertex{ 1, -1,  1,    0, 1, 1});
   mVertices.push_back(Vertex{ 1, -1, -1,    0, 1, 1});
   mVertices.push_back(Vertex{ 1,  1, -1,    0, 1, 1});
   mVertices.push_back(Vertex{ 1,  1,  1,    0, 1, 1});

   for(size_t i{}; i < mVertices.capacity();i++)
   {
        // Bad name, set Normal
        QVector3D normal = QVector3D(mVertices[i].GetPosition().x,mVertices[i].GetPosition().y,mVertices[i].GetPosition().z);
        normal.normalize();
        mVertices[i].SetColor(normal.x(), normal.y(),normal.z());
   }
}

Cube::~Cube()
{

}

void Cube::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size() * sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(6 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(2);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    glBindVertexArray(0);
}

void Cube::draw()
{
    if (!isActive)
          return;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}
void Cube::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
