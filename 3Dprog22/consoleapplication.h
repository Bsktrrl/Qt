#ifndef CONSOLEAPPLICATION_H
#define CONSOLEAPPLICATION_H

#include <vector>
#include "vertex.h"


class ConsoleApplication
{
public:
    ConsoleApplication();

    class Logger *mLogger{nullptr};

    float SinCurve(float x, float y);
    float PointsCurve(float a);

    void InsertInfoFile(std::string fileName, std::vector<Vertex> fileText);

    void MakeFile_Lines();
    void MakeFile_Points();
    void Integrate();

    std::vector<Vertex> mVertices;
};

#endif // CONSOLEAPPLICATION_H
