#include "barysentrisk.h"
#include "logger.h"

barysentrisk::barysentrisk()
{

}

float barysentrisk::T_ABC(Vertex vA, Vertex vB, Vertex vC)
{
    //Hele trekanten
    QVector3D AB = QVector3D(vB.GetX() - vA.GetX(), vB.GetY() - vA.GetY(), vB.GetZ() - vA.GetZ());
    QVector3D AC = QVector3D(vC.GetX() - vA.GetX(), vC.GetY() - vA.GetY(), vC.GetZ() - vA.GetZ());

    float t_abc = (AB.x() * AC.y()) + (AB.y() * AC.x());

    return t_abc;
}

float barysentrisk::T_ABX(Vertex vA, Vertex vB, QVector3D x, float t_abc)
{
    //Trekant ABX
    QVector3D AB = QVector3D(vB.GetX() - vA.GetX(), vB.GetY() - vA.GetY(), vB.GetZ() - vA.GetZ());
    QVector3D AX = QVector3D(x.x() - vA.GetX(),     x.y() - vA.GetY(),     x.z() - vA.GetZ());

    float u = (AB.x() * AX.y()) + (AB.y() * AX.x());

    return u / t_abc;
}

float barysentrisk::T_BCX(Vertex vB, Vertex vC, QVector3D x, float t_abc)
{
    //Trekant BCX
    QVector3D BC = QVector3D(vC.GetX() - vB.GetX(), vC.GetY() - vB.GetY(), vC.GetZ() - vB.GetZ());
    QVector3D BX = QVector3D(x.x() - vB.GetX(),     x.y() - vB.GetY(),     x.z() - vB.GetZ());

    float v = (BC.x() * BX.y()) + (BC.y() * BX.x());

    return v / t_abc;
}

float barysentrisk::T_CAX(Vertex vC, Vertex vA, QVector3D x, float t_abc)
{
    //Trekant CAX
    QVector3D CA = QVector3D(vA.GetX() - vC.GetX(), vA.GetY() - vC.GetY(), vA.GetZ() - vC.GetZ());
    QVector3D CX = QVector3D(x.x() - vC.GetX(),     x.y() - vC.GetY(),     x.z() - vC.GetZ());

    float w = (CA.x() * CX.y()) + (CA.y() * CX.x());

    return w / t_abc;
}

float barysentrisk::bary(GameObject* playerPos, VisualObject* landscape)
{
    for (int i = 0; i < landscape->getmVerticesSize() - 2; i++)
    {
        float t_abc = T_ABC(landscape->getVertex(i), landscape->getVertex(i + 1), landscape->getVertex(i + 2));

        float u = T_ABX(landscape->getVertex(i),     landscape->getVertex(i + 1), playerPos->getPosition3D(), t_abc);
        float v = T_BCX(landscape->getVertex(i + 1), landscape->getVertex(i + 2), playerPos->getPosition3D(), t_abc);
        float w = T_CAX(landscape->getVertex(i + 2), landscape->getVertex(i),     playerPos->getPosition3D(), t_abc);

        if (u < 0)
        {

        }
        else if (v < 0)
        {

        }
        else if (w < 0)
        {

        }
        else if ((u + v) > 1)
        {

        }
        else
        {
            //Logger::getInstance()->logText("playerPos: x:" + std::to_string(playerPos->getPosition3D().x()) + " | y:" + std::to_string(playerPos->getPosition3D().y()) + " | z:" + std::to_string(playerPos->getPosition3D().z()));
            //Logger::getInstance()->logText("u: " + std::to_string(u) + " | v: " + std::to_string(v)+ " | w: " + std::to_string(w));

            //Logger::getInstance()->logText("u + v + w = " + std::to_string((u + v + w)));
            //Logger::getInstance()->logText("Vertex no: " + std::to_string(i));

            return (landscape->getVertex(i).GetZ() + 1);
        }
    }
}
