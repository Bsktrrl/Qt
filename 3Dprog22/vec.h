#ifndef VEC_H
#define VEC_H

class Vec3;


//-----


class Vec2
{
public:
    Vec2();

    float x;
    float y;

    Vec2 operator + (Vec2 v2);
    Vec2 operator - (Vec2 v2);
    Vec3 operator ^ (Vec2 v2);
    Vec2 operator * (Vec2 v2);
};


//--------------------


class Vec3
{
public:
    Vec3();

    float x;
    float y;
    float z;

    Vec3 operator + (Vec3 v3);
    Vec3 operator - (Vec3 v3);
    Vec3 operator ^ (Vec3 v3);
    Vec3 operator * (Vec3 v3);

    Vec3 barycentricCoordinates(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 x);

    float length(float x, float y, float z);
};

#endif // VEC_H
