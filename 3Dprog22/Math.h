#ifndef MATH_H
#define MATH_H

struct Position
{
    Position()
    {
        x = 0.f;
        y = 0.f;
        z = 0.f;
    };

    Position(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) {}

    float x, y, z;
};

struct Normal
{
    Normal()
    {
        r = 0.f;
        g = 0.f;
        b = 0.f;
    }

    Normal(float _r, float _g, float _b)
        : r(_r), g(_g), b(_b)
    {

    }

    float r, g, b;
};

struct Color
{
    Color()
    {
        r = 0.f;
        g = 0.f;
        b = 0.f;
    }

    Color(float _r, float _g, float _b)
        : r(_r), g(_g), b(_b)
    {

    }

    float r, g, b;

    Color operator*=(const float& factor)
        {
            this->r *= factor;
            this->g *= factor;
            this->b *= factor;

            return *this;
        }
};


struct UV
{
    UV()
    {
        u = 0.f;
        v = 0.f;
    }

    UV(float _u, float _v)
        : u(_u), v(_v)
    {

    }

    float u, v;
};

#endif
