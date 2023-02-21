#include "points.h"

Points::Points(std::string name)
{
    setName(name);
}

Points::Points(std::string name, float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Dx, float Dy, float Ex, float Ey, float Fx, float Fy, float Gx, float Gy, float Hx, float Hy, float Ix, float Iy, float Jx, float Jy)
{
    setName(name);

    mVertices.push_back(Vertex(Position(0, Ax, Ay), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Bx, By), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Cx, Cy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Dx, Dy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Ex, Ey), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Fx, Fy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Gx, Gy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Hx, Hy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Ix, Iy), Color(1.f, 0, 1.f)));
    mVertices.push_back(Vertex(Position(0, Jx, Jy), Color(1.f, 0, 1.f)));
}

Points::~Points()
{

}

void Points::init(GLint matrixUniform)
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

void Points::draw()
{
    if (!isActive)
          return;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glPointSize(4.f);
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}
