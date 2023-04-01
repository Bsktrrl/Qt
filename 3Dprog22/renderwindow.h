#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "vertex0.h"
#include "vertex.h"
#include "visualobject.h"
#include "xyz.h"
#include "trianglesurface.h"
#include "camera.h"
#include "shader.h"
#include "texture.h"

#include <unordered_map>
//#include "barysentrisk.h"

class QOpenGLContext;
class Shader;
class MainWindow;
class GameObject;
class barysentrisk;

/// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    static RenderWindow* instance;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    bool mRotate{true};     //Check if triangle should rotate

    inline static std::unordered_map<int, bool> Keymap;

    std::vector<GameObject*> GetAllObjects();
    std::vector<GameObject*> GetColliderObjects(int scene);

//    GLint GetMatrixUniform() { return mMatrixUniform;}
//    GLint GetVMatrixUniform() { return mVmatrixUniform;}
//    GLint GetPMatrixUniform() { return mPmatrixUniform;}

    void ChangeScene(int scene);

    void AddGameObject(GameObject* object, std::string name);

    Shader* GetShader(std::string shaderName) {return shaders[shaderName];}
    void runProgram(std::string shader);

    //Shaders
//    void setupPlainShader(int shaderIndex);
//    GLint mMatrixUniform0{-1};
//    GLint vMatrixUniform0{-1};
//    GLint pMatrixUniform0{-1};

//    void setupTextureShader(int shaderIndex);
//    GLint mMatrixUniform1{-1};
//    GLint vMatrixUniform1{-1};
//    GLint pMatrixUniform1{-1};
//    GLint mTextureUniform1{-1};

//    void setupPhongShader(int shaderIndex);
//    GLint mMatrixUniform2{-1};
//    GLint vMatrixUniform2{-1};
//    GLint pMatrixUniform2{-1};

//    //other light shader variables
//    GLint mLightColorUniform{-1};
//    GLint mObjectColorUniform{-1};
//    GLint mAmbientLightStrengthUniform{-1};
//    GLint mLightPositionUniform{-1};
//    GLint mCameraPositionUniform{-1};
//    GLint mSpecularStrengthUniform{-1};
//    GLint mSpecularExponentUniform{-1};
//    GLint mLightPowerUniform{-1};
//    GLint mTextureUniform2{-1};

//    Texture *mTexture[4]{nullptr}; //We can hold 4 textures
//    Shader *mShaderProgram[4]{nullptr}; //We can hold 4 shaders

private slots:
    void render();          //the actual render - function

private:

    //Points
    float pAx;
    float pAy;
    float pBx;
    float pBy;
    float pCx;
    float pCy;
    float pDx;
    float pDy;
    float pEx;
    float pEy;
    float pFx;
    float pFy;
    float pGx;
    float pGy;
    float pHx;
    float pHy;
    float pIx;
    float pIy;
    float pJx;
    float pJy;

    //Vertex m_v;
    std::vector<VisualObject*> mObjects;
    std::vector<VisualObject*> textureObjects;

    std::unordered_map<std::string, GameObject*> mGameObjects;
    std::unordered_map<std::string, Shader*> shaders;    //holds pointer the GLSL shader program

    Camera* mCamera;
    barysentrisk* bary;

    void init();            //initialize things we need before rendering

    QOpenGLContext *mContext{nullptr};  //Our OpenGL context
    bool mInitialized{false};

    Shader *mShaderProgram{nullptr};    //holds pointer the GLSL shader program


//    GLint  mPmatrixUniform;
//    GLint  mVmatrixUniform;
//    GLint  mMatrixUniform;

    QMatrix4x4 *mPmatrix{nullptr};
    QMatrix4x4 *mVmatrix{nullptr};

    QTimer *mRenderTimer{nullptr};           //timer that drives the gameloop
    QElapsedTimer mTimeStart;               //time variable that reads the calculated FPS

    MainWindow *mMainWindow{nullptr};        //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};  //helper class to get some clean debug info from OpenGL
    class Logger *mLogger{nullptr};         //logger - Output Log in the application

    QVector2D mousePos;

    ///Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate();          //as name says

    ///Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();

    std::unordered_map<std::string, VisualObject*> mMap;    // alternativ container
    std::unordered_map<std::string, VisualObject*> mPhongObjects;    // alternativ container

    std::vector<VisualObject*> mObjectVectorScene1;
    std::unordered_map<std::string, VisualObject*> mObjectMapScene2;

    int activeScene;

protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;              //the only one we use now
    void keyReleaseEvent(QKeyEvent *event) override;
    //    void wheelEvent(QWheelEvent *event) override{}

    void input();

    void resizeEvent(QResizeEvent *) override;
};

#endif // RENDERWINDOW_H
