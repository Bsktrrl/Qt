#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>

#include <string>
#include <vector>

#include "shader.h"
#include "mainwindow.h"
#include "logger.h"
#include "xyz.h"
#include "trianglesurface.h"
#include "octahedronball.h"
#include "tetraeder.h"
#include "disc.h"
#include "parabel.h"
#include "points.h"
#include "interpolation.h"
#include "landscapes.h"
#include "house.h"
#include "door.h"
#include "cube.h"
#include "gameobject.h"
#include "player.h"
#include "transform.h"
#include "pickup.h"

RenderWindow* RenderWindow::instance;

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)
{
    if (instance == nullptr)
    {
        instance = this;
    }

    activeScene = 1;

    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);

    //Make the OpenGL context
    mContext = new QOpenGLContext(this);

    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());

    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    mCamera = new Camera();

    mPmatrix = new QMatrix4x4();
    mVmatrix = new QMatrix4x4();

    mPmatrix->setToIdentity();
    mVmatrix->setToIdentity();

    mPmatrix->perspective(60, 4.0/3.0, 0.1, 10.0);
    mPmatrix->translate(0, 0, -4.f);

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);


    //--------------------


    //Make The Window appear
    mObjects.push_back(new XYZ());

    mMap.insert(std::pair<std::string, VisualObject*>{"Landscape", new Landscape(QVector2D(-10, -10), QVector2D(10, 10))});

    mMap.insert(std::pair<std::string, VisualObject*>{"PickUp1", new OctahedronBall(0)});
    mMap["PickUp1"]->move(4.f, 0.f, 0.f);

    pAx = -3; pAy = 3;
    pBx = -2; pBy = 2;
    pCx = -1; pCy = 1;
    pDx = 0; pDy = 0;
    pEx = 1; pEy = 1;
    pFx = 2; pFy = 2;
    pGx = 3; pGy = 3;

    mMap.insert(std::pair<std::string, VisualObject*>{"Parabel", new Parabel(pAx, pAy,   pBx, pBy,   pCx, pCy,   pDx, pDy,   pEx, pEy,   pFx, pFy,   pGx, pGy)});


    //Scene 1
    mMap.insert(std::pair<std::string, VisualObject*>{"House", new House()});
    mMap["House"]->move(10.f, 0.f, 4);
    mMap["House"]->scale(5);
    mMap["House"]->rotate(270, QVector3D(0, 0, 1));

    mGameObjects.insert(std::pair<std::string, GameObject*>{"Door", new Door()});

    mGameObjects.insert(std::pair<std::string, GameObject*>{"Player", new Player()});
    mCamera->setFollowGameObject(mGameObjects["Player"]);

    for (int i = 0; i < 8; i++)
    {
        mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp" + std::to_string(i), new PickUp()});
    }

    //Scene 2
    mObjectMapScene2.insert(std::pair<std::string, VisualObject*>{"HouseInside", new Cube()});
    mObjectMapScene2["HouseInside"]->move(0, 0, 19);
    mObjectMapScene2["HouseInside"]->scale(20);



    //mObjects.push_back(new Tetraeder(Position(2.2f, 0, 0), QVector3D(2, 2, 2)));

    //mObjects.push_back(new TriangleSurface("Data.txt"));
    //mObjects.push_back(new TriangleSurface("DataPoints.txt"));

    //mObjects.push_back(new Disc());

    //Run Matrix Calculation - Math Oblig 2 - Task 1
//    pAx = -3; pAy = 3;
//    pBx = -2; pBy = 2;
//    pCx = -1; pCy = 1;
//    pDx = 0; pDy = 0;
//    pEx = 1; pEy = 1;
//    pFx = 2; pFy = 2;
//    pGx = 3; pGy = 3;
    //mObjects.push_back(new Parabel(pAx, pAy,   pBx, pBy,   pCx, pCy,   pDx, pDy,   pEx, pEy,   pFx, pFy,   pGx, pGy));
    //mObjects.push_back(new Points(pAx, pAy,   pBx, pBy,   pCx, pCy,   pDx, pDy,   pEx, pEy,   pFx, pFy,   pGx, pGy));

    //Run Interpolation Calculation - Math Oblig 2 - Task 2
//    pAx = -2; pAy = 2;
//    pBx = -1; pBy = 1;
//    pCx = 0; pCy = 0;
//    pDx = 2; pDy = 2;
    //mObjects.push_back(new Interpolation(QVector2D(pAx, pAy), QVector2D(pBx, pBy), QVector2D(pCx, pCy), QVector2D(pDx, pDy)));
    //mObjects.push_back(new Points(pAx, pAy,   pBx, pBy,   pCx, pCy,   pDx, pDy));


    //Alternativ: bygger en scene - legger inn objekter
    //Erstatter std::vector<VisualObject*> med unordered map
    mObjectMapScene2.insert(std::pair<std::string, VisualObject*>{"xyz", new XYZ()});
    //mMap.insert(std::pair<std::string, VisualObject*>{"triangleSurface", new TriangleSurface("Data.txt")});
    //mMap.insert(std::pair<std::string, VisualObject*> {"mia", mia});
    //std::pair<std::string, VisualObject*> par{"disc", mDisc};
    //mMap.insert(par);

    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        (*it)->setScene(1);
    }

    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        (*it).second->setScene(1);
    }

    for (auto it = mObjectMapScene2.begin(); it != mObjectMapScene2.end(); it++)
    {
        (*it).second->setScene(2);
    }

    //Update all GameObjects to scene 1
    for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
    {
        (*it).second->setScene(1);
    }
}

RenderWindow::~RenderWindow()
{

}

// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));


    //********************** General OpenGL stuff **********************


    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this))
    {
        mLogger->logText("makeCurrent() failed", LogType::REALERROR);
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
    {
        mInitialized = true;
    }

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    mLogger->logText("The active GPU and API:", LogType::HIGHLIGHT);
    std::string tempString;
    tempString += std::string("  Vendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n" +
            std::string("  Renderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" +
            std::string("  Version: ") + std::string((char*)glGetString(GL_VERSION));
    mLogger->logText(tempString);

    //Start the Qt OpenGL debugger
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:
    //NB: hardcoded path to files! You have to change this if you change directories for the project.
    //Qt makes a build-folder besides the project folder. That is why we go down one directory
    // (out of the build-folder) and then up into the project folder.
    mShaderProgram = new Shader("../3Dprog22/plainshader.vert", "../3Dprog22/plainshader.frag");

    // Get the matrixUniform location from the shader
    // This has to match the "matrix" variable name in the vertex shader
    // The uniform is used in the render() function to send the model matrix to the shader
    mMatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "matrix" );
    mPmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "pmatrix" );
    mVmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "vmatrix" );
    //mCamera.init(mMatrixUniform, mVmatrixUniform);

    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        (*it)->init(mMatrixUniform);
    }

    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        (*it).second->init(mMatrixUniform);
    }

    for (auto it = mObjectMapScene2.begin(); it != mObjectMapScene2.end(); it++)
    {
        (*it).second->init(mMatrixUniform);
    }

    for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
    {
        (*it).second->awake();
    }

    mCamera->init(mPmatrixUniform, mVmatrixUniform);
    mCamera->perspective(80, 1.6f, 0.1f, 1000);

    glBindVertexArray(0);       //unbinds any VertexArray - good practice
}

// Called each frame
void RenderWindow::render()
{
   mTimeStart.restart(); //restart FPS clock

   input();
   mContext->makeCurrent(this);

   //initializeOpenGLFunctions();

   //Clear the screen for each re-draw
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //What shader to use
   glUseProgram(mShaderProgram->getProgram());

   //Camera
   mCamera->update();

   for (auto it = mObjects.begin(); it != mObjects.end(); it++)
   {
       if((*it)->getScene() == activeScene)
       {
           (*it)->draw();
       }
   }

   for (auto it = mMap.begin(); it != mMap.end(); it++)
   {
       if((*it).second->getScene() == activeScene)
       {
           (*it).second->draw();
       }
   }

   for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
   {
       if((*it).second->getScene() == activeScene)
       {
           (*it).second->update();
       }
   }

   for (auto it = mObjectMapScene2.begin(); it != mObjectMapScene2.end(); it++)
   {
       if((*it).second->getScene() == activeScene)
       {
           (*it).second->draw();
       }
   }

   calculateFramerate();
   mContext->swapBuffers(this);
}

void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}

void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)            //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30)    //once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }
}

void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
        {
            if (!(message.type() == message.OtherType)) // get rid of uninteresting "object ...
                                                        // will use VIDEO memory as the source for
                                                        // buffer object operations"
                // valid error message:
                mLogger->logText(message.message().toStdString(), LogType::REALERROR);
        }
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            mLogger->logText("glGetError returns " + std::to_string(err), LogType::REALERROR);
            switch (err) {
            case 1280:
                mLogger->logText("GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.");
                break;
            case 1281:
                mLogger->logText("GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.");
                break;
            case 1282:
                mLogger->logText("GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.");
                break;
            }
        }
    }
}

void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            mLogger->logText("This system can not use QOpenGLDebugLogger, so we revert to glGetError()",
                             LogType::HIGHLIGHT);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            mLogger->logText("This system can log extended OpenGL errors", LogType::HIGHLIGHT);
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                mLogger->logText("Started Qt OpenGL debug logger");
        }
    }
}


//-----


std::vector<GameObject *> RenderWindow::GetAllObjects()
{
    std::vector<GameObject*> objects;
    for (auto it = mGameObjects.begin(); it!= mGameObjects.end();it++)
    {
        objects.push_back((*it).second);
    }

//    for (auto it = mMap.begin(); it!= mMap.end();it++)
//    {
//        objects.push_back(it->second);
//    }

    return objects;
}

std::vector<GameObject*> RenderWindow::GetColliderObjects(int scene)
{
    std::vector<GameObject*> objects;

    for (auto it = mGameObjects.begin(); it!= mGameObjects.end();it++)
    {
        if ((*it).second->CollissionActive())
        {
            if(it->second->getScene() == scene)
            {
                objects.push_back((*it).second);
            }
        }
    }

    return objects;
}

void RenderWindow::ChangeScene(int scene)
{
    if (scene == 1)
    {
        mCamera->setPosition(QVector3D(10, 0, 10));
        mCamera->setForward(QVector3D(0, 0, 0));

        mGameObjects["Player"]->setScene(1);
        activeScene = 1;
    }
    if (scene == 2)
    {
        mCamera->setPosition(QVector3D(10, 0, 10));
        mCamera->setForward(QVector3D(0, 0, 0));

        mGameObjects["Player"]->setScene(2);
        activeScene = 2;
    }
}

void RenderWindow::AddGameObject(GameObject *object, std::string name)
{
    mGameObjects.insert(std::pair<std::string, GameObject*> {name, object});
    object->awake();
}


//-----


void RenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(Keymap[Qt::MouseButton(1)] == true)
    {
        float xDelta = event->pos().x() - mousePos.x();
        xDelta /= 10;

        float yDelta = event->pos().y() - mousePos.y();
        yDelta /= 10;

        mCamera->rotate(yDelta, -xDelta, 0);
    }

    mousePos = QVector2D(event->pos().x(), event->pos().y());
}

void RenderWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton(1))
    {
        Keymap[Qt::MouseButton(1)] = false;
    }
}

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton(1))
    {
        Keymap[Qt::MouseButton(1)] = true;
    }
}

void RenderWindow::input()
{
    //Move Camera
    if (Keymap[Qt::Key_W] == true)
    {
        mCamera->translate(0.2f, 0, 0);
    }
    if (Keymap[Qt::Key_S] == true)
    {
        mCamera->translate(-0.2f, 0, 0);
    }
    if (Keymap[Qt::Key_A] == true)
    {
        mCamera->translate(0, -0.2f, 0);
    }
    if (Keymap[Qt::Key_D] == true)
    {
        mCamera->translate(0, 0.2f, 0);
    }

    //Rotate Object
    if(Keymap[Qt::Key_Q] == true)
    {
        mCamera->translate(0, 0, -0.2f);
    }
    if(Keymap[Qt::Key_E] == true)
    {
        mCamera->translate(0, 0, 0.2f);
    }
    if(Keymap[Qt::Key_Z] == true)
    {

    }
    if(Keymap[Qt::Key_X] == true)
    {

    }

    //Move Map
    if (Keymap[Qt::Key_Up] == true)
    {
    }
    if (Keymap[Qt::Key_Down] == true)
    {
    }
    if (Keymap[Qt::Key_Right] == true)
    {
    }
    if (Keymap[Qt::Key_Left] == true)
    {
    }

    if (Keymap[Qt::Key_K] == true)
    {
    }
    if (Keymap[Qt::Key_L] == true)
    {
    }

    //Scene swap
    if (Keymap[Qt::Key_1] == true)
    {
        ChangeScene(1);
    }
    if (Keymap[Qt::Key_2] == true)
    {
        ChangeScene(2);
    }
}

void RenderWindow::resizeEvent(QResizeEvent *)
{
    mCamera->perspective(80, width() / height(), 0.1f, 1000);
}

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();       //Shuts down the program
    }

    //Movement WASD
    if(event->key() == Qt::Key_W)
    {
        Keymap[Qt::Key_W] = true;
    }
    if(event->key() == Qt::Key_S)
    {
        Keymap[Qt::Key_S] = true;
    }
    if(event->key() == Qt::Key_A)
    {
        Keymap[Qt::Key_A] = true;
    }
    if(event->key() == Qt::Key_D)
    {
        Keymap[Qt::Key_D] = true;
    }

    //Movement QEZX
    if(event->key() == Qt::Key_Q)
    {
        Keymap[Qt::Key_Q] = true;
    }
    if(event->key() == Qt::Key_E)
    {
        Keymap[Qt::Key_E] = true;
    }
    if(event->key() == Qt::Key_Z)
    {
        Keymap[Qt::Key_Z] = true;
    }
    if(event->key() == Qt::Key_X)
    {
        Keymap[Qt::Key_X] = true;
    }

    //Map - Arrows
    if(event->key() == Qt::Key_Up)
    {
        Keymap[Qt::Key_Up] = true;
    }
    if(event->key() == Qt::Key_Down)
    {
        Keymap[Qt::Key_Down] = true;
    }
    if(event->key() == Qt::Key_Right)
    {
        Keymap[Qt::Key_Right] = true;
    }
    if(event->key() == Qt::Key_Left)
    {
        Keymap[Qt::Key_Left] = true;
    }

    if(event->key() == Qt::Key_K)
    {
        Keymap[Qt::Key_K] = true;
    }
    if(event->key() == Qt::Key_L)
    {
        Keymap[Qt::Key_L] = true;
    }

    //Active Scene
    if(event->key() == Qt::Key_1)
    {
        Keymap[Qt::Key_1] = true;
    }
    if(event->key() == Qt::Key_2)
    {
        Keymap[Qt::Key_2] = true;
    }
}

void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    //Movement WASD
    if(event->key() == Qt::Key_W)
    {
        Keymap[Qt::Key_W] = false;
    }
    if(event->key() == Qt::Key_S)
    {
        Keymap[Qt::Key_S] = false;
    }
    if(event->key() == Qt::Key_A)
    {
        Keymap[Qt::Key_A] = false;
    }
    if(event->key() == Qt::Key_D)
    {
        Keymap[Qt::Key_D] = false;
    }

    //Movement QEZX
    if(event->key() == Qt::Key_Q)
    {
        Keymap[Qt::Key_Q] = false;
    }
    if(event->key() == Qt::Key_E)
    {
        Keymap[Qt::Key_E] = false;
    }
    if(event->key() == Qt::Key_Z)
    {
        Keymap[Qt::Key_Z] = false;
    }
    if(event->key() == Qt::Key_X)
    {
        Keymap[Qt::Key_X] = false;
    }

    //Map - Arrows
    if(event->key() == Qt::Key_Up)
    {
        Keymap[Qt::Key_Up] = false;
    }
    if(event->key() == Qt::Key_Down)
    {
        Keymap[Qt::Key_Down] = false;
    }
    if(event->key() == Qt::Key_Right)
    {
        Keymap[Qt::Key_Right] = false;
    }
    if(event->key() == Qt::Key_Left)
    {
        Keymap[Qt::Key_Left] = false;
    }

    if(event->key() == Qt::Key_K)
    {
        Keymap[Qt::Key_K] = false;
    }
    if(event->key() == Qt::Key_L)
    {
        Keymap[Qt::Key_L] = false;
    }

    //Active Scene
    if(event->key() == Qt::Key_1)
    {
        Keymap[Qt::Key_1] = false;
    }
    if(event->key() == Qt::Key_2)
    {
        Keymap[Qt::Key_2] = false;
    }
}
