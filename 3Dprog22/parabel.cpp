#include "parabel.h"
#include <cmath>
#include "logger.h"

Parabel::Parabel()
{
}

Parabel::Parabel(float Ax, float Ay, float Bx, float By, float Cx, float Cy, float Dx, float Dy, float Ex, float Ey, float Fx, float Fy, float Gx, float Gy)
{
    // 1) - Make a Matrix with the y-values
    float* Ymatrix = new float [1*7]
    {
            Ay, By, Cy, Dy, Ey, Fy, Gy
    };



//--------------------



    // 2) - Make a Matrix with the x-values
    float* Amatrix = new float [7*3]
    {
            Ax * Ax, Ax, 1.f,
            Bx * Bx, Bx, 1.f,
            Cx * Cx, Cx, 1.f,
            Dx * Dx, Dx, 1.f,
            Ex * Ex, Ex, 1.f,
            Fx * Fx, Fx, 1.f,
            Gx * Gx, Gx, 1.f
    };

    float* ATmatrix = new float [3*7]
    {
            Ax * Ax, Bx * Bx, Cx * Cx, Dx * Dx, Ex * Ex, Fx * Fx, Gx * Gx,
            Ax, Bx, Cx, Dx, Ex, Fx, Gx,
            1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f
    };



//--------------------



    // 4) - Calculate B (A^t * A)
    float* B = new float[3*3]
    {
        ((ATmatrix[0] * Amatrix[0]) + (ATmatrix[1] * Amatrix[3]) + (ATmatrix[2] * Amatrix[6]) + (ATmatrix[3] * Amatrix[9]) + (ATmatrix[4] * Amatrix[12]) + (ATmatrix[5] * Amatrix[15]) + (ATmatrix[6] * Amatrix[18])),
        ((ATmatrix[0] * Amatrix[1]) + (ATmatrix[1] * Amatrix[4]) + (ATmatrix[2] * Amatrix[7]) + (ATmatrix[3] * Amatrix[10]) + (ATmatrix[4] * Amatrix[13]) + (ATmatrix[5] * Amatrix[16]) + (ATmatrix[6] * Amatrix[19])),
        ((ATmatrix[0] * Amatrix[2]) + (ATmatrix[1] * Amatrix[5]) + (ATmatrix[2] * Amatrix[8]) + (ATmatrix[3] * Amatrix[11]) + (ATmatrix[4] * Amatrix[14]) + (ATmatrix[5] * Amatrix[17]) + (ATmatrix[6] * Amatrix[20])),

        ((ATmatrix[7] * Amatrix[0]) + (ATmatrix[8] * Amatrix[3]) + (ATmatrix[9] * Amatrix[6]) + (ATmatrix[10] * Amatrix[9]) + (ATmatrix[11] * Amatrix[12]) + (ATmatrix[12] * Amatrix[15]) + (ATmatrix[13] * Amatrix[18])),
        ((ATmatrix[7] * Amatrix[1]) + (ATmatrix[8] * Amatrix[4]) + (ATmatrix[9] * Amatrix[7]) + (ATmatrix[10] * Amatrix[10]) + (ATmatrix[11] * Amatrix[13]) + (ATmatrix[12] * Amatrix[16]) + (ATmatrix[13] * Amatrix[19])),
        ((ATmatrix[7] * Amatrix[2]) + (ATmatrix[8] * Amatrix[5]) + (ATmatrix[9] * Amatrix[8]) + (ATmatrix[10] * Amatrix[11]) + (ATmatrix[11] * Amatrix[14]) + (ATmatrix[12] * Amatrix[17]) + (ATmatrix[13] * Amatrix[20])),

        ((ATmatrix[14] * Amatrix[0]) + (ATmatrix[15] * Amatrix[3]) + (ATmatrix[16] * Amatrix[6]) + (ATmatrix[17] * Amatrix[9]) + (ATmatrix[18] * Amatrix[12]) + (ATmatrix[19] * Amatrix[15]) + (ATmatrix[20] * Amatrix[18])),
        ((ATmatrix[14] * Amatrix[1]) + (ATmatrix[15] * Amatrix[4]) + (ATmatrix[16] * Amatrix[7]) + (ATmatrix[17] * Amatrix[10]) + (ATmatrix[18] * Amatrix[13]) + (ATmatrix[19] * Amatrix[16]) + (ATmatrix[20] * Amatrix[19])),
        ((ATmatrix[14] * Amatrix[2]) + (ATmatrix[15] * Amatrix[5]) + (ATmatrix[16] * Amatrix[8]) + (ATmatrix[17] * Amatrix[11]) + (ATmatrix[18] * Amatrix[14]) + (ATmatrix[19] * Amatrix[17]) + (ATmatrix[20] * Amatrix[20])),
    };


//--------------------



    // 5) - Calculate adj[B]
    float a = B[0];
    float b = B[1];
    float c = B[2];
    float d = B[3];
    float e = B[4];
    float f = B[5];
    float g = B[6];
    float h = B[7];
    float i = B[8];

    float detA = (e * i) - (f * h);    float detB = (d * i) - (g * f);     float detC = (d * h) - (g * e);
    float detD = (b * i) - (h * c);    float detE = (a * i) - (g * c);     float detF = (a * h) - (g * b);
    float detG = (b * f) - (e * c);    float detH = (a * f) - (d * c);     float detI = (a * e) - (d * b);

    float det = (a * detA) - (b * detB) + (c * detC);

    float* B_inverted = new float [3*3]
    {
            detA / det, detB / det, detC / det,
            detD / det, detE / det, detF / det,
            detG / det, detH / det, detI / det
    };



//--------------------



    // 8) - Calculate A^t * y
    //const float* At_data = At.constData();

    float* At_Y = new float [3*1]
    {
            (ATmatrix[0] * Ymatrix[0]) + (ATmatrix[1] * Ymatrix[1]) + (ATmatrix[2] * Ymatrix[2]) + (ATmatrix[3] * Ymatrix[3]) + (ATmatrix[4] * Ymatrix[4]) + (ATmatrix[5] * Ymatrix[5]) + (ATmatrix[6] * Ymatrix[6]),
            (ATmatrix[7] * Ymatrix[0]) + (ATmatrix[8] * Ymatrix[1]) + (ATmatrix[9] * Ymatrix[2]) + (ATmatrix[10] * Ymatrix[3]) + (ATmatrix[11] * Ymatrix[4]) + (ATmatrix[12] * Ymatrix[5]) + (ATmatrix[13] * Ymatrix[6]),
            (ATmatrix[14] * Ymatrix[0]) + (ATmatrix[15] * Ymatrix[1]) + (ATmatrix[16] * Ymatrix[2]) + (ATmatrix[17] * Ymatrix[3]) + (ATmatrix[18] * Ymatrix[4]) + (ATmatrix[19] * Ymatrix[5]) + (ATmatrix[20] * Ymatrix[6]),
    };



//--------------------



    // 9) - Calculate X
    //const float* B_Inverted_data = B_inverted.constData();

    float* X = new float [3*1]
    {
            (B_inverted[0] * At_Y[0]) + (B_inverted[1] * At_Y[1]) + (B_inverted[2] * At_Y[2]),
            (B_inverted[3] * At_Y[0]) + (B_inverted[4] * At_Y[1]) + (B_inverted[5] * At_Y[2]),
            (B_inverted[6] * At_Y[0]) + (B_inverted[7] * At_Y[1]) + (B_inverted[8] * At_Y[2]),
    };



//--------------------



    // 10) - Get Xa, Xb and Xc, to be used to make a polynom of 2nd order f(x) = Xa*x^2 - Xb*x + Xc
    Xa = X[0];
    Xb = X[1];
    Xc = X[2];



 //--------------------


    // make mVertecies
    float n = 100;
    float start = Ax;
    float end = Gx;

    float hi = (end-start)/n;

    Color blue = Color(1.f, 1.f, 1.f);
    for (auto x = start; x < end; x += hi)
    {
        float y = (Xa * x * x) + (Xb * x) + Xc;
        mVertices.push_back(Vertex(Position(x,y,1), blue));
    }
}

Parabel::~Parabel()
{

}


void Parabel::init(GLint matrixUniform)
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

       //const float* arr = B_inverted.constData();

       //float vc = arr[0];

       Logger* logger = Logger::getInstance();
       //logger->logText("a in B_inverted: " + std::to_string(vc));
       logger->logText("Xa: " + std::to_string(Xa));
       logger->logText("Xb: " + std::to_string(Xb));
       logger->logText("Xc: " + std::to_string(Xc));
}

void Parabel::draw()
{
    if (!isActive)
          return;

    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
}
void Parabel::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
    }
}
