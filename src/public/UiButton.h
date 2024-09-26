#pragma once

#include <functional>
#include <tuple>
#include "glew.h"
#include "Color.h"

class UiButton
{
public:
	UiButton(float a1, float a2, float b1, float b2, eColor color, std::function<void()> onClickEvent);
	
	float x1, y1, x2, y2;
	Color clr;
	std::function<void()> onButtonClick;
	void Draw();
	void isClicked(const float posX, const float posY);
};