#include "vec.h"
#include <cmath>


Vec2::Vec2()
{
    float x;
    float y;
}

Vec2 Vec2::operator + (Vec2 v2)
{
    Vec2 vec;

    vec.x = x + v2.x;
    vec.y = y + v2.y;

    return vec;
}

Vec2 Vec2::operator - (Vec2 v2)
{
    Vec2 vec;

    vec.x = x - v2.x;
    vec.y = y - v2.y;

    return vec;
}

Vec3 Vec2::operator ^ (Vec2 v2)
{
    Vec3 vec3;

    vec3.x = 0;
    vec3.y = 0;
    vec3.z = x * v2.y - y * v2.x;

    return vec3;
}

Vec2 Vec2::operator * (Vec2 v2)
{
    Vec2 vec;

    vec.x = x * v2.x;
    vec.y = y * v2.y;

    return vec;
}


//--------------------


Vec3::Vec3()
{

}

Vec3 Vec3::operator + (Vec3 v3)
{
    Vec3 vec;

    vec.x = x + v3.x;
    vec.y = y + v3.y;
    vec.z = z + v3.z;

    return vec;
}

Vec3 Vec3::operator - (Vec3 v3)
{
    Vec3 vec;

    vec.x = x - v3.x;
    vec.y = y - v3.y;
    vec.z = z - v3.z;

    return vec;
}

Vec3 Vec3::operator ^ (Vec3 v3)
{
    Vec3 vec;

    vec.x = 0;
    vec.y = 0;
    vec.z = x * v3.y - y * v3.x;

    return vec;
}

Vec3 Vec3::operator * (Vec3 v3)
{
    Vec3 vec;

    vec.x = x * v3.x;
    vec.y = y * v3.y;
    vec.z = z * v3.z;

    return vec;
}


//--------------------


Vec3 Vec3::barycentricCoordinates(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 x)
{
    Vec2 p1_2 = p2 - p1;
    Vec2 p1_3 = p3 - p1;
    Vec3 n = p1_2 ^ p1_3;

    float areal_123 = n.length(n.x, n.y, n.z); // dobbelt areal
    Vec3 baryc; // til retur. Husk

    // u
    Vec2 p = p2 - x;
    Vec2 q = p3 - x;
    n = p ^ q;
    baryc.x = n.z/areal_123;

    // v
    p = p3 - x;
    q = p1 - x;
    n = p ^ q;
    baryc.y = n.z/areal_123;

    // w
    p = p1 - x;
    q = p2 - x;
    n = p ^ q;
    baryc.z = n.z/areal_123;

    return baryc;
}

float Vec3::length(float x, float y, float z)
{
    float sum = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return sum;
}
