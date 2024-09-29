#pragma once

#include <functional>
#include <tuple>
#include "glew.h"
#include "Color.h"

class UiButton
{
public:
	UiButton(float x, float y, float sizeX, float sizeY, eColor color, std::function<void()> onClickEvent);
	
	std::function<void()> onButtonClick;
	virtual void Draw();
	void isClicked(const float posX, const float posY);
	void selectedValue(const Color& clr);
protected:
	Color m_clr;
	float m_x, m_y, m_width, m_height;
	bool isSelected;

private:
	void DrawSelectUI();
};