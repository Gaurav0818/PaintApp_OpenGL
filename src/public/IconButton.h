#pragma once

#include "UiButton.h"

enum eToolType
{
	PencilTool,
	EraserTool,
	LineTool,
	RectTool,
	BucketTool,
	CircleTool
};

class IconButton : public UiButton
{
public:
	IconButton(float a1, float a2, float b1, float b2, eColor color, std::function<void()> onClickEvent, eToolType toolType)
		: UiButton(a1, a2, b1, b2, color, onClickEvent) 
	{
		this->m_tool = toolType;
	};

	void DrawIcon();
	void Draw() override;

private:
	eToolType m_tool;
	void drawPencilIcon(float x, float y, float width, float height);
	void drawLineIcon(float x, float y, float length);
	void drawEraserIcon(float x, float y, float width, float height);
	void drawBucketIcon(float x, float y, float width, float height);
	void drawRectangleIcon(float x, float y, float width, float height);
};