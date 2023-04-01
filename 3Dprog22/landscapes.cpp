#include "landscapes.h"

Landscape::Landscape()
{
}

Landscape::Landscape(QVector2D bottomLeft, QVector2D topRight)
{
    height = 0;

    float minX = bottomLeft.x();
    float maxX = topRight.x();

    float minY = bottomLeft.y();
    float maxY = topRight.y();


    float step = 0.05f;

    Color color;
    for (auto y = minY; y < maxY; y += step)
    {
        height++;
        for (auto x = minX; x < maxX; x += step)
        {

            float z = f(x,y);
            QVector3D pos1 = QVector3D(x,y,z);
            z = f(x+step,y);
            QVector3D pos2 = QVector3D(x + step,y,z);
            z = f(x,y+step);
            QVector3D pos3 = QVector3D(x,y + step,z);

            QVector3D normal1 = QVector3D::crossProduct(pos2-pos1, pos3-pos1);
            QVector3D normal2 = QVector3D::crossProduct(pos3-pos2, pos1-pos2);
            QVector3D normal3 = QVector3D::crossProduct(pos1-pos3, pos2-pos3);


            mVertices.push_back(Vertex(pos1, normal1, UV(pos1.x(),pos1.y())));
            mVertices.push_back(Vertex(pos2, normal2, UV(pos2.x(),pos2.y())));
            mVertices.push_back(Vertex(pos3, normal3, UV(pos3.x(),pos3.y())));

            z = f(x+step,y);
            pos1 = QVector3D(x + step,y,z);
            z = f(x+step,y+step);
            pos2 = QVector3D(x + step,y + step,z);
            z = f(x,y+step);
            pos3 = QVector3D(x,y + step,z);

            normal1 = QVector3D::crossProduct(pos2-pos1, pos3-pos1);
            normal2 = QVector3D::crossProduct(pos3-pos2, pos1-pos2);
            normal3 = QVector3D::crossProduct(pos1-pos3, pos2-pos3);

            mVertices.push_back(Vertex(pos1, normal1, UV(pos1.x(),pos1.y())));
            mVertices.push_back(Vertex(pos2, normal2, UV(pos2.x(),pos2.y())));
            mVertices.push_back(Vertex(pos3, normal3, UV(pos3.x(),pos3.y())));
        }
    }

    int length1D = height - 1;
    int currentIndex = 0;
    for (int y{}; y < length1D; y++)
    {
        for (int x {}; x < length1D; x++)
        {
            // Fixing per square

            // First Vertex / Six Vertex's
            QVector3D normal1 = mVertices[currentIndex].GetNormal();

            // One Square to the left
            if (x - 1 > 0)
            {
                normal1 += mVertices[currentIndex - 3].GetNormal();
                normal1 += mVertices[currentIndex - 5].GetNormal();
            }
            // One Square to the left, One Square Down
            if (x - 1 > 0 && y - 1 > 0)
            {
                normal1 += mVertices[currentIndex - (length1D * 6) - 2].GetNormal();
            }

            // One Square Down
            if (y - 1 > 0)
            {
                normal1 += mVertices[currentIndex - (length1D * 6) + 2].GetNormal();
                normal1 += mVertices[currentIndex - (length1D * 6) + 5].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal1.normalized());


            // Second Vertex / Six Vertex's
            currentIndex++;
            QVector3D normal2 = mVertices[currentIndex].GetNormal();

            // Same Square
            normal2 += mVertices[currentIndex + 2].GetNormal();

            // One Square to the right
            if (x + 1 < length1D)
            {
                normal2 += mVertices[currentIndex + 5].GetNormal();
            }

            // One Square to the right, One Square down
            if (x + 1 < length1D && y - 1 > 0)
            {
                normal2 += mVertices[currentIndex - (length1D * 6) + 1].GetNormal();
                normal2 += mVertices[currentIndex - (length1D * 6) + 4].GetNormal();
            }

            // One Square down
            if (y - 1 > 0)
            {
                normal2 += mVertices[currentIndex - (length1D * 6) - 4].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal2.normalized());


            // Third Vertex / Six Vertex's
            currentIndex++;
            QVector3D normal3 = mVertices[currentIndex].GetNormal();

            // Same Square
            normal3 += mVertices[currentIndex + 3].GetNormal();

            // One Square to the left
            if (x - 1 > 0)
            {
                normal3 += mVertices[currentIndex - 3].GetNormal();
            }

            // One Square to the left, One Square Up
            if (x - 1 > 0 && y + 1 < length1D)
            {
                normal3 += mVertices[currentIndex + (length1D * 6) - 5].GetNormal();
                normal3 += mVertices[currentIndex + (length1D * 6) - 7].GetNormal();
            }

            // One Square Up
            if (y + 1 < length1D)
            {
                normal3 += mVertices[currentIndex + (length1D * 6) - 2].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal3.normalized());

            // Fourth Vertex / Six Vertex's
            currentIndex++;
            QVector3D normal4 = mVertices[currentIndex].GetNormal();

            // Same Square
            normal4 += mVertices[currentIndex - 2].GetNormal();

            // One Square to the Right
            if (x + 1 < length1D)
            {
                normal4 += mVertices[currentIndex + 3].GetNormal();
            }

            // One Square to the Right, One Square Down
            if (x + 1 < length1D && y - 1 > 0)
            {
                normal4 += mVertices[currentIndex - (length1D * 6) + 5].GetNormal();
                normal4 += mVertices[currentIndex - (length1D * 6) + 8].GetNormal();
            }

            // One Square Down
            if (y - 1 > 0)
            {
                normal4 += mVertices[currentIndex - (length1D * 6) + 1].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal4.normalized());

            // Fifth Vertex / Six Vertex's
            currentIndex++;
            QVector3D normal5 = mVertices[currentIndex].GetNormal();

            // Same Square
            normal5 += mVertices[currentIndex - 3].GetNormal();

            // One Square to the left
            if (x - 1 > 0)
            {
                normal5 += mVertices[currentIndex - 7].GetNormal();
            }
            // One Square to the left, One Square Up
            if (x - 1 > 0 && y + 1 < length1D)
            {
                normal5 += mVertices[currentIndex + (length1D * 6) - 7].GetNormal();
                normal5 += mVertices[currentIndex + (length1D * 6) - 9].GetNormal();
            }
            // One Square Up
            if (y + 1 < length1D)
            {
                normal5 += mVertices[currentIndex + (length1D * 6) - 5].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal5.normalized());

            // Last Vertex
            currentIndex++;
            QVector3D normal6 = mVertices[currentIndex].GetNormal();

            // One Square to the Right
            if (x + 1 < length1D)
            {
                normal6 += mVertices[currentIndex + 4].GetNormal();
                normal6 += mVertices[currentIndex + 7].GetNormal();
            }
            // One Square Up
            if (y + 1 < length1D)
            {
                normal6 += mVertices[currentIndex + (length1D * 6) - 1].GetNormal();
                normal6 += mVertices[currentIndex + (length1D * 6) - 3].GetNormal();
            }
            // One Square to the Right, One Square Up
            if (x + 1 < length1D && y + 1 < length1D)
            {
                normal6 += mVertices[currentIndex + (length1D * 6) + 2].GetNormal();
            }
            mVertices[currentIndex].SetNormal(normal6.normalized());
            currentIndex++;
        }
    }
}

Landscape::~Landscape()
{

}

void Landscape::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;
    initializeOpenGLFunctions();


    //Vertex Array Object - VAO
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );


    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );


    glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW );


    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  (GLvoid*)(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
}

void Landscape::draw()
{
    if (isActive)
    {
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}
void Landscape::draw(QMatrix4x4& transformMatrix)
{
    if (isActive)
    {
        transformMatrix *= mMatrix;
        glBindVertexArray( mVAO );
        glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, transformMatrix.constData());
        glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
    }
}

float Landscape::f(float x, float y)
{
    float noiseHeight = 0;
    int octaves = 4;
    float scale = 4;
    float amplitude = 1;
    float frequency = 1;
    float persitence = 0.5;
    float lacunarity = 2;
    PerlinNoise mPerlin = PerlinNoise();
    for (int i{}; i < octaves; i++)
    {
        double xP = (double)x /scale;
        double yP = (double)y /scale;

        xP *= frequency;
        yP *= frequency;

        float perlinValue = mPerlin.noise(xP,yP,1) * 2 - 1;
        noiseHeight += perlinValue * amplitude;

        amplitude *= persitence;
        frequency *= lacunarity;
    }

    return noiseHeight;

}

Color Landscape::recalc(float z)
{
    Color color;
    float blue = -0.5;
    float green = 0.6;


    if (z < blue)
    {
        color = Color(0.f, 0.f, 1.f);
        color *= abs(z) + 0.1;
    }
    else if (z < green)
    {
        color = Color(0.f, 1.f, 0.f);
        color *= abs(z);
    }
    else
    {
        color = Color(1.f, 1.f, 1.f);
        color *= z;
    }
    return color;
}
