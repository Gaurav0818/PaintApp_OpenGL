#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <functional>
#include <queue>
#include <unordered_set>
#include <sstream>

#include "glew.h"
#include "glfw3.h"
#include "Input.h"
#include "Color.h"
#include "UiButton.h"

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

enum eToolType
{
	PencilTool,
	EraserTool,
	LineTool,
	RectTool,
	BucketTool,
	CircleTool
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
	void drawBorder();

	std::pair<float, float> getMousePos();
	std::pair<float, float> getMappedPos(std::pair<float, float> pair);
	float getDistance(const std::pair<float, float> a, const std::pair<float, float> b);

	bool isValueSame(const float& a, const float& b, float epsilon = 0.01f);

	void showFPS();

	void createButtons();
	void drawButtons();
	void checkIfButtonClicked();

	void pencilTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr);
	void eraserTool(const std::vector<std::pair<float, float>>& points, const float brushSize);
	void lineTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr);
	void rectTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr);
	void fillTool(const std::vector<std::pair<float, float>>& points, eColor clr);
	void circleTool(const std::pair<float, float> center, float radius, const float brushSize, eColor clr);
	int getColorBufferIndex(int x, int y);
	void floodFill();

private:
	GLFWwindow* m_window;
	int m_bufferHeight, m_bufferWidth;
	
	eToolType m_selectedTool;
	float m_brushSize;
	std::unique_ptr<Color> m_clearColor;
	bool isDrawing;
	bool canFill;
	eColor m_selectedColor;
	double m_lastTime;
	int m_frameCount;

	std::vector<std::pair<float, float>> m_points;
	std::vector<std::function<void()>> m_linesToDraw;
	std::vector<UiButton*> m_Buttons;
};