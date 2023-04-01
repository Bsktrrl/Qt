#include "barysentrisk.h"
#include "logger.h"

barysentrisk::barysentrisk()
{

}

float barysentrisk::w_1(Vertex vA, Vertex vB, Vertex vC, QVector3D p)
{
    float w1 = ( (vA.GetX() * (vC.GetY() - vA.GetY())) + ((p.y() - vA.GetY()) * (vC.GetX() - vA.GetX())) - (p.x() * (vC.GetY() - vA.GetY())) ) /
            ( ((vB.GetY() - vA.GetY()) * (vC.GetX() - vA.GetX()))  -  ((vB.GetX() - vA.GetX()) * (vC.GetY() - vA.GetY())) );

    return w1;
}

float barysentrisk::w_2(Vertex vA, Vertex vB, Vertex vC, QVector3D p, float w1)
{
    float w2 = ( p.y() - vA.GetY() - (w1 * ((vB.GetY() - vA.GetY()))) ) / (vC.GetY() - vA.GetY());

    return w2;
}

bool barysentrisk::isOnTriangle(float w1, float w2)
{
    if ((w1 >= 0 && (w1 + w2) <= 1)  ||  (w2 >= 0 && (w1 + w2) <= 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

float barysentrisk::triangleHeight(GameObject* playerPos, VisualObject* landscape)
{
    //Logger::getInstance()->logText("PlayerPos: " + std::to_string(playerPos->getPosition3D().x()) + " | " + std::to_string(playerPos->getPosition3D().y()) + " | " + std::to_string(playerPos->getPosition3D().z()));

    for (int i = 0; i < landscape->getmVerticesSize() - 2; i++)
    {
        float w1 = w_1(landscape->getVertex(i), landscape->getVertex(i + 1), landscape->getVertex(i + 2), playerPos->getPosition3D());
        float w2 = w_2(landscape->getVertex(i), landscape->getVertex(i + 1), landscape->getVertex(i + 2), playerPos->getPosition3D(), w1);

        if (isOnTriangle(w1, w2))
        {
            Logger::getInstance()->logText("w1: " + std::to_string(w1) + " | w2: " + std::to_string(w2) + " | Vertex no " + std::to_string(i) + ": " + std::to_string(landscape->getVertex(i).GetZ()));

            return landscape->getVertex(i).GetZ();
        }
    }
}
