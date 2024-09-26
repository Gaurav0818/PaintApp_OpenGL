#pragma once

#define MAX_COLOR 13
enum class eColor
{
    White = 0,
    Black = 1,
    Red = 2,
    Green = 3,
    Blue = 4,
    Yellow = 5,
    Cyan = 6,
    Magenta = 7,
    Gray = 8,
    Orange = 9,
    Purple = 10,
    Pink = 11,
    Brown = 12
};

class Color
{
public:
    Color() = default;
    Color(float a) : r(a), g(a), b(a) {}
    Color(float a, float b, float c) : r(a), g(b), b(c) {}
    ~Color() = default;

    float r, g, b;
};


Color getColorFromEnum(eColor colorEnum);