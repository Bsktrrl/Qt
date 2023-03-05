#include "xyz.h"

XYZ::XYZ() : VisualObject()
{
    mVertices.push_back(Vertex{0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f});
    mVertices.push_back(Vertex{1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f});
    mVertices.push_back(Vertex{0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f});
    mVertices.push_back(Vertex{0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f});
    mVertices.push_back(Vertex{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 1.0f});
    mVertices.push_back(Vertex{0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f});
}

XYZ::~XYZ()
{

}

void XYZ::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

       initializeOpenGLFunctions();

       //Vertex Array Object - VAO
       glGenVertexArrays( 1, &mVAO );
       glBindVertexArray( mVAO );

       //Vertex Buffer Object to hold vertices - VBO
       glGenBuffers( 1, &mVBO );
       glBindBuffer( GL_ARRAY_BUFFER, mVBO );

       glBufferData( GL_ARRAY_BUFFER,
                     mVertices.size() * sizeof( Vertex ),
                     mVertices.data(),
                     GL_STATIC_DRAW );

       // 1rst attribute buffer : vertices
       glBindBuffer(GL_ARRAY_BUFFER, mVBO);
       glVertexAttribPointer(0,
                             3,
                             GL_FLOAT,GL_FALSE,
                             sizeof(Vertex),
                             (GLvoid*)0);
       glEnableVertexAttribArray(0);

       // 2nd attribute buffer : colors
       glVertexAttribPointer(1,
                             3,
                             GL_FLOAT,
                             GL_FALSE,
                             sizeof( Vertex ),
                             (GLvoid*)(3 * sizeof(GLfloat)));
       glEnableVertexAttribArray(1);

       //enable the matrixUniform
       // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

       glBindVertexArray(0);
}

void XYZ::draw()
{
   if (!isActive)
         return;

   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINES, 0, mVertices.size());
}

void XYZ::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINES, 0, mVertices.size());
    }
}
