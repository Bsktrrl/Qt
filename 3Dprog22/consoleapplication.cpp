#include "consoleapplication.h"
#include <cmath>
#include <fstream>
#include "logger.h"
#include <qDebug>

ConsoleApplication::ConsoleApplication()
{

}

void ConsoleApplication::InsertInfoFile(std::string fileName, std::vector<Vertex> fileText)
{
    //Insert data into textFile
    std::ofstream file;
    file.open(fileName, std::ofstream::out | std::ofstream::trunc);

    //Insert lineCount into textFile
    file << fileText.size() << std::endl << std::endl;

    //Insert xyz coordinates into textFile
    for (size_t i = 0; i < fileText.size(); i++)
    {
        file << fileText[i] << std::endl;
        std::cout << std::endl;
    }

    file.close();
}

float ConsoleApplication::SinCurve(float x, float y)
{
    return sin(M_PI * x) * sin(M_PI * y);
}

float ConsoleApplication::PointsCurve(float a)
{
    return sin(M_PI * a);
}

void ConsoleApplication::MakeFile_Lines()
{
    mVertices.clear();

    //Calculate the triangles
    float xmin = -10.f, xmax = 10.f, ymin = -10.f, ymax = 10.f, h = 0.15f;

    for (auto x = xmin; x < xmax; x += h)
    {
        for (auto y = ymin; y < ymax; y += h)
        {
            float z = SinCurve(x, y);

            mVertices.push_back(Vertex(Position(x, y, z), Color(abs(x),abs(y),abs(z))));

            z = SinCurve(x + h, y);
            mVertices.push_back(Vertex(Position(x + h, y, z), Color(abs(x + h),abs(y),abs(z))));

            z = SinCurve(x, y + h);
            mVertices.push_back(Vertex(Position(x, y + h, z), Color(abs(x),abs(y + h),abs(z))));
            mVertices.push_back(Vertex(Position(x, y + h, z), Color(abs(x),abs(y + h),abs(z))));

            z = SinCurve(x + h, y);
            mVertices.push_back(Vertex(Position(x + h, y, z), Color(abs(x + h),abs(y),abs(z))));

            z = SinCurve(x + h, y + h);
            mVertices.push_back(Vertex(Position(x + h, y + h, z), Color(abs(x + h),abs(y + h),abs(z))));
        }
    }

    InsertInfoFile("Data.txt", mVertices);
}

void ConsoleApplication::MakeFile_Points()
{
    mVertices.clear();

    int n = 500;
    float xmin = -1.0f, xmax = 1.0f, ymin = -1.0f, ymax = 1.0f, h = 0.25f;
    float deltaX = (xmax - xmin) / n;

    for (auto x = xmin; x < xmax; x += deltaX)
    {
        mVertices.push_back(Vertex(Position(x, PointsCurve(x), 0), Color(0.0f, 1.0f, 0.1f)));
    }

    InsertInfoFile("DataPoints.txt", mVertices);
}

void ConsoleApplication::Integrate()
{
    float h = 0.0625f / 2;
    float A = 0.f;

    for (float x = 0.f; x < 1.f; x += h)
    {
        for (float y = 0.f; y < 1.0 - x; y += h)
        {
            float z = SinCurve(x, y);
            mVertices.push_back(Vertex(Position(x, y, z), Color(0,0,z)));

            z = SinCurve(x + h ,y);
            mVertices.push_back(Vertex(Position(x + h, y, z), Color(0,0,z)));

            z = SinCurve(x, y + h);
            mVertices.push_back(Vertex(Position(x, y + h, z), Color(0,0,z)));


            z = SinCurve(x + h, y);
            mVertices.push_back(Vertex(Position(x + h, y, z), Color(0 + h, 0 + h, z + h)));

            z = SinCurve(x + h, y + h);
            mVertices.push_back(Vertex(Position(x + h, y + h, z), Color(0 + h, 0 + h, z + h)));

            z = SinCurve(x, y + h);
            mVertices.push_back(Vertex(Position(x, y + h, z), Color(0 + h, 0 + h, z + h)));

            // Numeric integration
            z = SinCurve(x, y);
            A += h * h * z;
        }
    }

    InsertInfoFile("Data_Numerisk.txt", mVertices);
}

