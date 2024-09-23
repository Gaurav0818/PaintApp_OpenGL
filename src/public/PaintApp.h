#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <functional>

#include "glew.h"
#include "glfw3.h"
#include "Input.h"
#include "Color.h"

enum eToolType
{
	PencilTool,
	EraserTool
};

class PaintApp
{
public:
	PaintApp();
	~PaintApp();

	void run();

private:
	bool init();
	void getPlayerInput();

	std::pair<float, float> getMousePos();

	void pencilTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr);
	void eraserTool(const std::vector<std::pair<float, float>>& points, const float brushSize);

private:
	GLFWwindow* m_window;
	int m_bufferHeight, m_bufferWidth;
	
	eToolType m_selectedTool;
	float m_brushSize;
	std::unique_ptr<Color> m_clearColor;
	eColor m_selectedColor;
	std::vector<std::pair<float, float>> m_points;
	std::vector<std::function<void()>> m_linesToDraw;
};