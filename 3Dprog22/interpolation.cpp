#include "interpolation.h"

Interpolation::Interpolation(std::string name)
{
    setName(name);
}

Interpolation::Interpolation(std::string name, QVector2D a, QVector2D b, QVector2D c, QVector2D d)
{
    setName(name);

    A.setRow(0, QVector4D(a.x() * a.x() * a.x(), a.x() * a.x(), a.x(), 1));
    A.setRow(1, QVector4D(b.x() * b.x() * b.x(), b.x() * b.x(), b.x(), 1));
    A.setRow(2, QVector4D(c.x() * c.x() * c.x(), c.x() * c.x(), c.x(), 1));
    A.setRow(3, QVector4D(d.x() * d.x() * d.x(), d.x() * d.x(), d.x(), 1));

    IA = A.inverted();

    B.setX(a.y());
    B.setY(b.y());
    B.setZ(c.y());
    B.setW(d.y());

    X = IA * B;


    float n = 100;
    float start = a.x();
    float end = d.x();

    float h = (end-start)/n;

    for (auto x = start; x < end; x += h)
    {
        float y = (X.x() * x * x * x) + (X.y() * x * x) + (X.z() * x) + X.w();
        mVertices.push_back(Vertex(Position(0, x, y), Color(0.f, 1.f, 1.f)));
    }
}

Interpolation::~Interpolation()
{

}

void Interpolation::init(GLint matrixUniform)
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

void Interpolation::draw()
{
    if (!isActive)
          return;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
}
