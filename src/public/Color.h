#pragma once

enum class eColor
{
    White,
    Black,
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    Gray,
    Orange,
    Purple,
    Pink,
    Brown
};

class Color
{
public:
    Color(float a) : r(a), g(a), b(a) {}
    Color(float a, float b, float c) : r(a), g(b), b(c) {}

    float r, g, b;
};


Color getColorFromEnum(eColor colorEnum);