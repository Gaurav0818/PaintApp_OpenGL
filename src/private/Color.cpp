#include "Color.h"

Color getColorFromEnum(eColor colorEnum)
{
    switch (colorEnum)
    {
    case eColor::White:
        return Color(1.0f, 1.0f, 1.0f);
    case eColor::Black:
        return Color(0.0f, 0.0f, 0.0f);
    case eColor::Red:
        return Color(1.0f, 0.0f, 0.0f);
    case eColor::Green:
        return Color(0.0f, 1.0f, 0.0f);
    case eColor::Blue:
        return Color(0.0f, 0.0f, 1.0f);
    case eColor::Yellow:
        return Color(1.0f, 1.0f, 0.0f);
    case eColor::Cyan:
        return Color(0.0f, 1.0f, 1.0f);
    case eColor::Magenta:
        return Color(1.0f, 0.0f, 1.0f);
    case eColor::Gray:
        return Color(0.5f, 0.5f, 0.5f);
    case eColor::Orange:
        return Color(1.0f, 0.5f, 0.0f);
    case eColor::Purple:
        return Color(0.5f, 0.0f, 0.5f);
    case eColor::Pink:
        return Color(1.0f, 0.75f, 0.8f);
    case eColor::Brown:
        return Color(0.6f, 0.3f, 0.0f);
    default:
        return Color(1.0f, 1.0f, 1.0f);
    }
}