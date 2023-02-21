#include "door.h"
#include "spherecollider.h"
#include "logger.h"
#include "renderwindow.h"

Door::Door(std::string name)
{
    setName(name);

    collider = new SphereCollider(this, 0.5f, QVector3D(0, 0, -1));


    // -y veggen
    mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
    mVertices.push_back(Vertex{1,-1,1,1,0,0});
    mVertices.push_back(Vertex{-1,-1,1,1,0,0});
    mVertices.push_back(Vertex{-1,-1,-1,1,0,0});
    mVertices.push_back(Vertex{1,-1,-1,1,0,0});
    mVertices.push_back(Vertex{1,-1,1,1,0,0});

    // -z veggen
    mVertices.push_back(Vertex{-1,-1,-1,0,1,0});
    mVertices.push_back(Vertex{1,-1,-1,0,1,0});
    mVertices.push_back(Vertex{-1,1,-1,0,1,0});
    mVertices.push_back(Vertex{1,-1,-1,0,1,0});
    mVertices.push_back(Vertex{1,1,-1,0,1,0});
    mVertices.push_back(Vertex{-1,1,-1,0,1,0});

    // -x veggen
    mVertices.push_back(Vertex{-1,1,-1,0,0,1});
    mVertices.push_back(Vertex{-1,-1,-1,0,0,1});
    mVertices.push_back(Vertex{-1,-1,1,0,0,1});
    mVertices.push_back(Vertex{-1,1,-1,0,0,1});
    mVertices.push_back(Vertex{-1,-1,1,0,0,1});
    mVertices.push_back(Vertex{-1,1,1,0,0,1});

    // +y veggen
    mVertices.push_back(Vertex{1,1,1,1,0,1});
    mVertices.push_back(Vertex{-1,1,1,1,0,1});
    mVertices.push_back(Vertex{-1,1,-1,1,0,1});
    mVertices.push_back(Vertex{1,1,1,1,0,1});
    mVertices.push_back(Vertex{-1,1,-1,1,0,1});
    mVertices.push_back(Vertex{1,1,-1,1,0,1});

    // + z veggen
    mVertices.push_back(Vertex{-1,-1,1,1,1,0});
    mVertices.push_back(Vertex{1,1,1,1,1,0});
    mVertices.push_back(Vertex{-1,1,1,1,1,0});
    mVertices.push_back(Vertex{-1,-1,1,1,1,0});
    mVertices.push_back(Vertex{1,-1,1,1,1,0});
    mVertices.push_back(Vertex{1,1,1,1,1,0});

    // + x veggen
    mVertices.push_back(Vertex{1,-1,-1,0,1,1});
    mVertices.push_back(Vertex{1,1,1,0,1,1});
    mVertices.push_back(Vertex{1,-1,1,0,1,1});
    mVertices.push_back(Vertex{1,-1,-1,0,1,1});
    mVertices.push_back(Vertex{1,1,-1,0,1,1});
    mVertices.push_back(Vertex{1,1,1,0,1,1});

    scale(QVector3D(0.1f, 1.5f, 3.5f));
    doorAnim = false;
}

Door::~Door()
{

}

void Door::init(GLint matrixUniform)
{
    doorClosedPos = getPosition3D();
    doorOpenPos = getPosition3D() + QVector3D(0, 0, -5);

    doorPos = doorClosedPos;


    //-----


    mMatrixUniform = matrixUniform;

    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

    // 1rst attribute buffer : vertices
     glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

     //enable the matrixUniform
     // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    glBindVertexArray(0);
}

void Door::draw()
{
    if(doorAnim)
    {
        doorPos += QVector3D(0, 0, -0.1f);
        setPosition(doorPos.x(), doorPos.y(),doorPos.z());
        if(doorPos.z() < doorOpenPos.z())
        {
            RenderWindow::instance->ChangeScene(2);
            doorIsOpen = false;
        }
    }

    if (!isActive)
       return;

    collider->OnUpdate();

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void Door::collission(VisualObject *other)
{
    if (other->getName() == "Player")
    {
        if (RenderWindow::Keymap[Qt::Key_X])
        {
            doorAnim = true;
            Logger::getInstance()->logText("Door Open");
        }

        Logger::getInstance()->logText("Door Collider  Available");
    }
}
