#include "trianglesurface.h"
#include "fstream"
#include "logger.h"

#include "stb_image.h"


TriangleSurface::TriangleSurface() : VisualObject()
{
  //         x    y    z       r    g    b       U   V
  Vertex v0{0.0, 0.0, 0.0,    1.0, 0.0, 0.0,    0.0, 0.0};    mVertices.push_back(v0);
  Vertex v1{0.5, 0.0, 0.0,    0.0, 1.0, 0.0,    1.0, 0.0};    mVertices.push_back(v1);
  Vertex v2{0.5, 0.5, 0.0,    0.0, 0.0, 1.0,    1.0, 1.0};    mVertices.push_back(v2);
  Vertex v3{0.0, 0.0, 0.0,    0.0, 0.0, 1.0,    0.0, 0.0};    mVertices.push_back(v3);
  Vertex v4{0.5, 0.5, 0.0,    0.0, 1.0, 0.0,    1.0, 1.0};    mVertices.push_back(v4);
  Vertex v5{0.0, 0.5, 0.0,    1.0, 0.0, 0.0,    0.0, 1.0};    mVertices.push_back(v5);
}

TriangleSurface::TriangleSurface(std::string filnavn) : VisualObject()
{
    readFile(filnavn);
}

TriangleSurface::~TriangleSurface()
{

}

//--------------------


void TriangleSurface::readFile(std::string filnavn)
{
   std::ifstream inn;
   inn.open(filnavn.c_str());

   if (inn.is_open())
   {
       int n;
       Vertex vertex;
       inn >> n;
       mVertices.reserve(n);

       for (int i = 0; i < n; i++)
       {
            inn >> vertex;
            mVertices.push_back(vertex);
       }

       inn.close();
   }
}

void TriangleSurface::init(GLint matrixUniform)
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

       // 3nd attribute buffer : UV
          glVertexAttribPointer(2,
                                2,
                                GL_FLOAT,
                                GL_FALSE,
                                sizeof( Vertex ),
                                (GLvoid*)(6 * sizeof(GLfloat)) );
          glEnableVertexAttribArray(2);

       //enable the matrixUniform
       // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

       glBindVertexArray(0);


       //--------------------


       //Texture ID
       glGenTextures(1, &texture);
       glBindTexture(GL_TEXTURE_2D, texture);

       // set the texture wrapping/filtering options (on the currently bound texture object)
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

       // load and generate the texture
       int width, height, nrChannels;
       unsigned char *data = stbi_load("../container.jpg", &width, &height, &nrChannels, 0);

       if (data)
       {
           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
           glGenerateMipmap(GL_TEXTURE_2D);
       }
       else
       {
           std::cout << "Failed to load texture" << std::endl;
       }

       stbi_image_free(data);

       Logger::getInstance()->logText("Init");
}

void TriangleSurface::draw()
{
    if (!isActive)
          return;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void TriangleSurface::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

void TriangleSurface::draw(GLint textureUniform)
{
    if (!isActive)
          return;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUniform , 0); // 0 referer til glActiveTexture(GL_TEXTURE0);

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void TriangleSurface::draw(GLint textureUniform, QMatrix4x4 &transformMatrix)
{
    if (!isActive)
          return;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureUniform , 0); // 0 referer til glActiveTexture(GL_TEXTURE0);

    transformMatrix *= mMatrix;
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}
