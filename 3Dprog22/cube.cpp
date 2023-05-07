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

Cube::Cube(float x, float y, float z, float r, float g,float b)
{
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});   // 1st
    mVertices.push_back(Vertex{x, -y, -z, r, g, b});
    mVertices.push_back(Vertex{x, y, -z, r, g, b});
    mVertices.push_back(Vertex{x, y, -z, r, g, b});     // 2nd
    mVertices.push_back(Vertex{-x, y, -z, r, g, b});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});

    // Back plane
    mVertices.push_back(Vertex{-x, -y, z, r, g, b});    // 3rd
    mVertices.push_back(Vertex{x, -y, z, r, g, b});
    mVertices.push_back(Vertex{x, y, z, r, g, b});
    mVertices.push_back(Vertex{x, y, z, r, g, b});      // 4th
    mVertices.push_back(Vertex{-x, y, z, r, g, b});
    mVertices.push_back(Vertex{-x, -y, z, r, g, b});

    // Left plane
    mVertices.push_back(Vertex{-x, y, z, r, g, b});     // 5th
    mVertices.push_back(Vertex{-x, y, -z, r, g, b});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});   // 6th
    mVertices.push_back(Vertex{-x, -y, z, r, g, b});
    mVertices.push_back(Vertex{-x, y, z, r, g, b});

    // Right plane
    mVertices.push_back(Vertex{x, y, z, r, g, b});      // 7th
    mVertices.push_back(Vertex{x, y, -z, r, g, b});
    mVertices.push_back(Vertex{x, -y, -z, r, g, b});
    mVertices.push_back(Vertex{x, -y, -z, r, g, b});    // 8th
    mVertices.push_back(Vertex{x, -y, z, r, g, b});
    mVertices.push_back(Vertex{x, y, z, r, g, b});

    // Bottom plane
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});   // 9th
    mVertices.push_back(Vertex{x, -y, -z, r, g, b});
    mVertices.push_back(Vertex{x, -y, z, r, g, b});
    mVertices.push_back(Vertex{x, -y, z, r, g, b});     // 10th
    mVertices.push_back(Vertex{-x, -y, z, r, g, b});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b});

    // Top plane
    mVertices.push_back(Vertex{-x, y, -z, r, g, b});   // 11th
    mVertices.push_back(Vertex{x, y, -z, r, g, b});
    mVertices.push_back(Vertex{x, y, z, r, g, b});
    mVertices.push_back(Vertex{x, y, z, r, g, b});   //12th
    mVertices.push_back(Vertex{-x, y, z, r, g, b});
    mVertices.push_back(Vertex{-x, y, -z, r, g, b});


    mMatrix.setToIdentity();

    colourX = r;
    colourY = g;
    colourZ =b;
}

Cube::Cube(float x, float y, float z, float r, float g, float b, float u, float v)
{
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 0*u, 0*v});   // 1st
    mVertices.push_back(Vertex{x, -y, -z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{x, y, -z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{x, y, -z, r, g, b, 1*u, 1*v});     // 2nd
    mVertices.push_back(Vertex{-x, y, -z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 0*u, 0*v});

    // Back plane
    mVertices.push_back(Vertex{-x, -y, z, r, g, b, 0*u, 0*v});    // 3rd
    mVertices.push_back(Vertex{x, -y, z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{x, y, z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{x, y, z, r, g, b, 1*u, 1*v});      // 4th
    mVertices.push_back(Vertex{-x, y, z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{-x, -y, z, r, g, b, 0*u, 0*v});

    // Left plane
    mVertices.push_back(Vertex{-x, y, z, r, g, b, 0*u, 0*v});     // 5th
    mVertices.push_back(Vertex{-x, y, -z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 1*u, 1*v});   // 6th
    mVertices.push_back(Vertex{-x, -y, z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{-x, y, z, r, g, b, 0*u, 0*v});

    // Right plane
    mVertices.push_back(Vertex{x, y, z, r, g, b, 0*u, 0*v});      // 7th
    mVertices.push_back(Vertex{x, y, -z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{x, -y, -z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{x, -y, -z, r, g, b, 1*u, 1*v});    // 8th
    mVertices.push_back(Vertex{x, -y, z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{x, y, z, r, g, b, 0*u, 0*v});

    // Bottom plane
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 0*u, 0*v});   // 9th
    mVertices.push_back(Vertex{x, -y, -z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{x, -y, z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{x, -y, z, r, g, b, 1*u, 1*v});     // 10th
    mVertices.push_back(Vertex{-x, -y, z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{-x, -y, -z, r, g, b, 0*u, 0*v});

    // Top plane
    mVertices.push_back(Vertex{-x, y, -z, r, g, b, 0*u, 0*v});   // 11th
    mVertices.push_back(Vertex{x, y, -z, r, g, b, 1*u, 0*v});
    mVertices.push_back(Vertex{x, y, z, r, g, b, 1*u, 1*v});
    mVertices.push_back(Vertex{x, y, z, r, g, b, 1*u, 1*v});   //12th
    mVertices.push_back(Vertex{-x, y, z, r, g, b, 0*u, 1*v});
    mVertices.push_back(Vertex{-x, y, -z, r, g, b, 0*u, 0*v});


    mMatrix.setToIdentity();

    colourX = r;
    colourY = g;
    colourZ =b;
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
