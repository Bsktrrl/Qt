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
#include "light.h"
#include "houseobject.h"

#include "uniforms.h"
#include "barysentrisk.h"

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


    pAx = -3; pAy = 3;
    pBx = -2; pBy = 2;
    pCx = -1; pCy = 1;
    pDx = 0; pDy = 0;
    pEx = 1; pEy = 1;
    pFx = 2; pFy = 2;
    pGx = 3; pGy = 3;


    //--------------------


    // Scene 1 //

    //XYZ
    mObjects.push_back(new XYZ());

    //Player
    mGameObjects.insert(std::pair<std::string, GameObject*>{"Player", new Player()});
    mGameObjects["Player"]->move(-8, -8, 1);
    mCamera->setFollowGameObject(mGameObjects["Player"]);

    //Landscape
    mPhongObjects.insert(std::pair<std::string, VisualObject*>{"Landscape", new Landscape(QVector2D(-10, -10), QVector2D(10, 10))});

    //Ball
    mMap.insert(std::pair<std::string, VisualObject*>{"Ball", new OctahedronBall(4)});
    mMap["Ball"]->move(-10, 0, 1);

    //Parabel
    mMap.insert(std::pair<std::string, VisualObject*>{"Parabel", new Parabel(pAx, pAy,   pBx, pBy,   pCx, pCy,   pDx, pDy,   pEx, pEy,   pFx, pFy,   pGx, pGy)});
    mMap["Parabel"]->move(0, 0, 10);

    //House
    mPhongObjects.insert(std::pair<std::string, VisualObject*>{"House", new House()});
    mPhongObjects["House"]->move(10, 0, 4);
    mPhongObjects["House"]->scale(5);
    mPhongObjects["House"]->rotate(270, QVector3D(0, 0, 1));

//    textureObjects.push_back(new House());
//    textureObjects[0]->setPosition(QVector3D(10, 0, 4));
//    textureObjects[0]->scale(QVector3D(5, 5, 5));
//    textureObjects[0]->rotate(270, QVector3D(0, 0, 1));

//    mGameObjects.insert(std::pair<std::string, GameObject*>{"HouseObject", new HouseObject()});
//    mGameObjects["HouseObject"]->move(10, 0, 4);
    //mGameObjects["HouseObject"]->scale(5);
    //mGameObjects["HouseObject"]->rotate(270, QVector3D(0, 0, 1));

    mGameObjects.insert(std::pair<std::string, GameObject*>{"Door", new Door()});

    //Pickups
    mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp1", new PickUp()});
    mGameObjects["PickUp1"]->move(-6, -9, 1);
    mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp2", new PickUp()});
    mGameObjects["PickUp2"]->move(-5, -1, 1);
    mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp3", new PickUp()});
    mGameObjects["PickUp3"]->move(-4, -4, 1);
    mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp4", new PickUp()});
    mGameObjects["PickUp4"]->move(-3, -3, 1);
    mGameObjects.insert(std::pair<std::string, GameObject*>{"PickUp5", new PickUp()});
    mGameObjects["PickUp5"]->move(-2, -7, 1);

    //Image on the ground
    //textureObjects.push_back(new TriangleSurface());
    //textureObjects[0]->scale(QVector3D(100, 100, 0));


    //-----


    //Scene 2
    mObjectMapScene2.insert(std::pair<std::string, VisualObject*>{"HouseInside", new Cube()});
    mObjectMapScene2["HouseInside"]->move(0, 0, 19);
    mObjectMapScene2["HouseInside"]->scale(20);

    //Alternativ: bygger en scene - legger inn objekter
    mObjectMapScene2.insert(std::pair<std::string, VisualObject*>{"xyz", new XYZ()});



    //-----


    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        (*it)->setScene(1);
    }

    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        (*it).second->setScene(1);
    }
    for (auto it = mPhongObjects.begin(); it != mPhongObjects.end(); it++)
    {
        (*it).second->setScene(1);
    }
    for (auto it = mTextureObjects.begin(); it != mTextureObjects.end(); it++)
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

    for (auto it = textureObjects.begin(); it != textureObjects.end(); it++)
    {
        (*it)->setScene(1);
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

    mShaderProgram = new Shader("../3Dprog22/plainshader.vert", "../3Dprog22/plainshader.frag");
    shaders.insert(std::pair<std::string, Shader*>{"PlainShader", mShaderProgram});

    Uniforms* plainUniform = new Uniforms(glGetUniformLocation(shaders["PlainShader"]->getProgram(), "matrix"),
                                          glGetUniformLocation(shaders["PlainShader"]->getProgram(), "vmatrix"),
                                          glGetUniformLocation(shaders["PlainShader"]->getProgram(), "pmatrix"));
    shaders["PlainShader"]->setUniform(plainUniform);


    //-----


    Shader* shader1 = new Shader("../3Dprog22/textureshader.vert", "../3Dprog22/textureshader.frag");
    shaders.insert(std::pair<std::string, Shader*>{"TextureShader", shader1});

    Uniforms* textureUniform = new Uniforms(glGetUniformLocation(shaders["TextureShader"]->getProgram(), "matrix"),
                                            glGetUniformLocation(shaders["TextureShader"]->getProgram(), "vmatrix"),
                                            glGetUniformLocation(shaders["TextureShader"]->getProgram(), "pmatrix"),
                                            glGetUniformLocation(shaders["TextureShader"]->getProgram(), "textureSampler"));
    shaders["TextureShader"]->setUniform(textureUniform);


    //-----


    Shader* PhongShader = new Shader("../3Dprog22/PhongShader.vert", "../3Dprog22/PhongShader.frag");
    shaders.insert(std::pair<std::string, Shader*>{"PhongShader", PhongShader});

    Uniforms* phongUniform = new Uniforms(glGetUniformLocation(shaders["PhongShader"]->getProgram(), "mMatrix"),
                                            glGetUniformLocation(shaders["PhongShader"]->getProgram(), "vMatrix"),
                                            glGetUniformLocation(shaders["PhongShader"]->getProgram(), "pMatrix"));

    phongUniform->mObjectColor = glGetUniformLocation(shaders["PhongShader"]->getProgram(), "Color");
    phongUniform->mViewPosition = glGetUniformLocation(shaders["PhongShader"]->getProgram(), "viewPos");
    phongUniform->mLightPosition = glGetUniformLocation(shaders["PhongShader"]->getProgram(), "lightPosition");

    shaders["PhongShader"]->setUniform(phongUniform);

    // Get the matrixUniform location from the shader
    // This has to match the "matrix" variable name in the vertex shader
    // The uniform is used in the render() function to send the model matrix to the shader
    //mCamera.init(mMatrixUniform, mVmatrixUniform);

    glUseProgram(shaders["PlainShader"]->getProgram());
    for (auto it = mObjects.begin(); it != mObjects.end(); it++)
    {
        (*it)->init(shaders["PlainShader"]->getUniform()->mMmatrixUniform);
    }
    for (auto it = mMap.begin(); it != mMap.end(); it++)
    {
        (*it).second->init(shaders["PlainShader"]->getUniform()->mMmatrixUniform);
    }
    for (auto it = mObjectMapScene2.begin(); it != mObjectMapScene2.end(); it++)
    {
        (*it).second->init(shaders["PlainShader"]->getUniform()->mMmatrixUniform);
    }
    for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
    {
        (*it).second->awake();
    }

    glUseProgram(shaders["TextureShader"]->getProgram());
    for (auto it = textureObjects.begin(); it != textureObjects.end(); it++)
    {
        (*it)->init(shaders["TextureShader"]->getUniform()->mMmatrixUniform);
    }
    for (auto it = mTextureObjects.begin(); it != mTextureObjects.end(); it++)
    {
        (*it).second->init(shaders["TextureShader"]->getUniform()->mMmatrixUniform);
    }

    glUseProgram(shaders["PhongShader"]->getProgram());
    for (auto it = mPhongObjects.begin(); it != mPhongObjects.end(); it++)
    {
        (*it).second->init(shaders["PhongShader"]->getUniform()->mMmatrixUniform);
    }

    mCamera->init(shaders["TextureShader"]->getUniform()->mPmatrixUniform, shaders["TextureShader"]->getUniform()->mVmatrixUniform);
    mCamera->perspective(80, 1.6f, 0.1f, 1000);

    glBindVertexArray(0);       //unbinds any VertexArray - good practice
}

// Called each frame
void RenderWindow::render()
{
   mTimeStart.restart(); //restart FPS clock

   for (auto it = shaders.begin(); it != shaders.end(); it++)
   {
       glUseProgram(it->second->getProgram());

       Uniforms* uni = it->second->getUniform();
       mCamera->bind(uni->mPmatrixUniform, uni->mVmatrixUniform);
       mCamera->uploadPos(uni->mViewPosition);
   }

   input();
   mContext->makeCurrent(this);

   //initializeOpenGLFunctions();

   //Clear the screen for each re-draw
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //What shader to use
   glUseProgram(shaders["PlainShader"]->getProgram());

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

   for (auto it = mObjectMapScene2.begin(); it != mObjectMapScene2.end(); it++)
   {
       if((*it).second->getScene() == activeScene)
       {
           (*it).second->draw();
       }
   }


   //-----

   glUseProgram(shaders["PhongShader"]->getProgram());

   if (mGameObjects["Player"] != nullptr)
   {
       //bary->triangleHeight(mGameObjects["Player"], mPhongObjects["Landscape"]);

       QVector3D lightPos = mGameObjects["Player"]->getPosition3D();

       shaders["PhongShader"]->UploadLightPos(lightPos);

       //mLogger->logText("lightPos: " + std::to_string(lightPos.x()) + " " + std::to_string(lightPos.y()) + " " + std::to_string(lightPos.z()));
   }


   for (auto it = mPhongObjects.begin(); it != mPhongObjects.end(); it++)
   {
       if ((*it).second != nullptr)
       {
           if((*it).second->getScene() == activeScene)
           {
               QVector3D objectColor = (*it).second->getObjectColor();

               shaders["PhongShader"]->UploadObjectColor(objectColor);
               (*it).second->draw();
           }
       }
   }


   //-----


   glUseProgram(shaders["TextureShader"]->getProgram());
   for (auto it = textureObjects.begin(); it != textureObjects.end(); it++)
   {
       if((*it)->getScene() == activeScene)
       {
           (*it)->draw(shaders["TextureShader"]->getUniform()->mMmatrixUniform);
       }
   }
   for (auto it = mTextureObjects.begin(); it != mTextureObjects.end(); it++)
   {
       if ((*it).second != nullptr)
       {
           if((*it).second->getScene() == activeScene)
           {
               QVector3D objectColor = (*it).second->getObjectColor();

               shaders["TextureShader"]->UploadObjectColor(objectColor);
               (*it).second->draw();
           }
       }
   }



   //-----


   for (auto it = mGameObjects.begin(); it != mGameObjects.end(); it++)
   {
       if((*it).second->getScene() == activeScene)
       {
           (*it).second->update();
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

void RenderWindow::runProgram(std::string shader)
{
    glUseProgram(shaders[shader]->getProgram());
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
    QVector3D oldPlayerPos = mGameObjects["Player"]->getPosition3D();
    float baryc = bary->bary(mGameObjects["Player"], mPhongObjects["Landscape"]);

    //mCamera->setPosition(QVector3D(oldPlayerPos.x(), oldPlayerPos.y(), baryc));
    mGameObjects["Player"]->setPosition(QVector3D(oldPlayerPos.x(), oldPlayerPos.y(), baryc));



    //Logger
    //mLogger->logText("Triangle height: " + std::to_string(baryc));
    //mLogger->logText("PlayerPos: x" + std::to_string(mGameObjects["Player"]->getPosition3D().x()) + " | y:" + std::to_string(mGameObjects["Player"]->getPosition3D().y()) + " | z:" + std::to_string(mGameObjects["Player"]->getPosition3D().z()));
    //mLogger->logText("----------------------------");
    //mLogger->logText("");



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
        //mCamera->translate(0, 0, -0.2f);
        mCamera->translate(0, 0, 0);
    }
    if(Keymap[Qt::Key_E] == true)
    {
        //mCamera->translate(0, 0, 0.2f);
        mCamera->translate(0, 0, 0);
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
