#include "PaintApp.h"

Input* Input::s_Instance = new Input();

//template <typename T>
float clamp(float& value, float min, float max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

PaintApp::PaintApp()
{
	if (!init())
	{
		m_window = nullptr;
	}
	else
	{
		Input::setActiveWindow(m_window);
	}

	m_brushSize = 1;
	m_linesToDraw.clear();
	m_selectedColor = eColor::White;
	m_selectedTool = eToolType::PencilTool;
	isDrawing = false;
	m_clearColor = std::make_unique<Color>(0.12);
}

PaintApp::~PaintApp()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool PaintApp::init()
{
	// init glfw
	if (!glfwInit())
	{
		std::cout << "Error Initializing GLFW!";
		return false;
	}

	// set opengl version using glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, 0);

	// set openGL backwords & forword compatibitity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Create Window
	m_window = glfwCreateWindow(1200,1000, "Paint-App", nullptr, nullptr);

	if (!m_window)
	{
		std::cout << "Error Creating GLFW window!";
		return false;
	}

	// get frame buffer size
	glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

	// set context for glfw to use
	glfwMakeContextCurrent(m_window);
	// allow modern extension features 
	//glewExperimental = true;
	// init glew 
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error Initializing GLFW";
		return false;
	}
	// enable feature 
	//glEnable(GL_DEPTH_TEST);

	// set viewport properties 
	glViewport(0, 0, m_bufferWidth, m_bufferHeight);

	return true;
}

void PaintApp::getPlayerInput()
{
	if (Input::isButtonDown(Key::P))
	{
		m_selectedTool = eToolType::PencilTool;
		std::cout << "Selected Pencil Tool\n";
	}
	if (Input::isButtonDown(Key::O))
	{
		m_selectedTool = eToolType::EraserTool;
		std::cout << "Selected Eraser Tool\n";
	}
	if (Input::isButtonDown(Key::L))
	{
		m_selectedTool = eToolType::LineTool;
		std::cout << "Selected Line Tool\n";
	}
	if (Input::isButtonDown(Key::K))
	{
		m_selectedTool = eToolType::RectTool;
		std::cout << "Selected Rect Tool\n";
	}	
	if (Input::isButtonDown(Key::B))
	{
		m_selectedTool = eToolType::BucketTool;
		std::cout << "Selected Bucket Tool\n";
	}

	if (Input::isButtonDown(Key::ARROW_UP))
	{
		m_brushSize += 1.0;
		m_brushSize = clamp(m_brushSize, 1, 20);
	}

	if (Input::isButtonDown(Key::ARROW_DOWN))
	{
		m_brushSize -= 1.0;
		m_brushSize = clamp(m_brushSize, 1, 20);
	}

	if (Input::isButtonPressed(Key::CTRL) && Input::isButtonDown(Key::Z))
	{
		std::cout << "Undo Called\n";
		m_linesToDraw.pop_back();
	}

	// Change color with number keys
	if (Input::isButtonDown(Key::NUM_1))
	{
		m_selectedColor = eColor::White;
		std::cout << "Selected White Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_2))
	{
		m_selectedColor = eColor::Black;
		std::cout << "Selected Black Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_3))
	{
		m_selectedColor = eColor::Red;
		std::cout << "Selected Red Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_4))
	{
		m_selectedColor = eColor::Green;
		std::cout << "Selected Green Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_5))
	{
		m_selectedColor = eColor::Blue;
		std::cout << "Selected Blue Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_6))
	{
		m_selectedColor = eColor::Yellow;
		std::cout << "Selected Yellow Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_7))
	{
		m_selectedColor = eColor::Cyan;
		std::cout << "Selected Cyan Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_8))
	{
		m_selectedColor = eColor::Magenta;
		std::cout << "Selected Magenta Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_9))
	{
		m_selectedColor = eColor::Gray;
		std::cout << "Selected Gray Color\n";
	}
	else if (Input::isButtonDown(Key::NUM_0))
	{
		m_selectedColor = eColor::Orange;
		std::cout << "Selected Orange Color\n";
	}
	else if (Input::isButtonDown(Key::Q))
	{
		m_selectedColor = eColor::Purple;
		std::cout << "Selected Purple Color\n";
	}
	else if (Input::isButtonDown(Key::W))
	{
		m_selectedColor = eColor::Pink;
		std::cout << "Selected Pink Color\n";
	}
	else if (Input::isButtonDown(Key::E))
	{
		m_selectedColor = eColor::Brown;
		std::cout << "Selected Brown Color\n";
	}

	if (Input::isButtonPressed(Key::MOUSE_LEFT))
	{
		isDrawing = true;
		if (m_selectedTool == eToolType::PencilTool || m_selectedTool == eToolType::EraserTool)
		{
			m_points.push_back(getMousePos());
		}
		else if (m_selectedTool == eToolType::LineTool)
		{
			if (m_points.empty())
			{
				m_points.push_back(getMousePos());
				m_points.push_back(getMousePos());
			}
			else
			{
				m_points.pop_back();
				m_points.push_back(getMousePos());
			}
		}
		else if (m_selectedTool == eToolType::RectTool)
		{
			if (m_points.empty())
			{
				auto [x1, y1] = getMousePos();
				m_points.push_back({ x1, y1 });
				auto [x2, y2] = getMousePos();
				m_points.push_back({ x1, y2 });
				m_points.push_back({ x2, y2 });
				m_points.push_back({ x2, y1 });
				m_points.resize(4);
			}
			else
			{
				const auto& [x1, y1] = m_points[0];
				auto [x2, y2] = getMousePos();
				m_points[1] = { x1, y2 };
				m_points[2] = { x2, y2 };
				m_points[3] = { x2, y1 };
			}
		}
		else if(m_selectedTool == eToolType::BucketTool || canFill)
		{
			canFill = false;
			floodFill();
		}
	}
	else if(isDrawing)
	{
		isDrawing = false;
		if (m_selectedTool == eToolType::PencilTool)
		{
			auto tempPoints = std::move(m_points);
			float tempSize = m_brushSize;
			eColor tempClr = m_selectedColor;

			m_linesToDraw.push_back([tempPoints, tempSize, tempClr, this]()
				{
					pencilTool(tempPoints, tempSize, tempClr);
				});
			m_points.clear();
		}
		else if (m_selectedTool == eToolType::EraserTool)
		{
			auto tempPoints = std::move(m_points);
			float tempSize = m_brushSize;

			m_linesToDraw.push_back([tempPoints, tempSize, this]()
				{
					eraserTool(tempPoints, tempSize);
				});
			m_points.clear();
		}
		else if (m_selectedTool == eToolType::LineTool)
		{
			auto tempPoints = std::move(m_points);
			float tempSize = m_brushSize;
			eColor tempclr = m_selectedColor;

			m_linesToDraw.push_back([tempPoints, tempSize, tempclr, this]()
				{
					lineTool(tempPoints, tempSize, tempclr);
				});
			m_points.clear();
		}
		else if (m_selectedTool == eToolType::RectTool)
		{
			auto tempPoints = std::move(m_points);
			float tempSize = m_brushSize;
			eColor tempclr = m_selectedColor;

			m_linesToDraw.push_back([tempPoints, tempSize, tempclr, this]()
				{
					rectTool(tempPoints, tempSize, tempclr);
				});
			m_points.clear();
		}
		else if (m_selectedTool == eToolType::BucketTool)
		{
			auto tempPoints = std::move(m_points);
			eColor tempclr = m_selectedColor;

			m_linesToDraw.push_back([tempPoints, tempclr, this]()
				{
					fillTool(tempPoints, tempclr);
				});
			m_points.clear();
		}
	}
}

void PaintApp::run()
{
	if (!m_window)
		return;
	
	while (!glfwWindowShouldClose(m_window))
	{
		canFill = true;
		getPlayerInput();

		glfwPollEvents();
		
		glClearColor(m_clearColor->r, m_clearColor->g, m_clearColor->b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		for (const auto& e : m_linesToDraw)
		{
			e();
		}

		if (m_selectedTool == eToolType::PencilTool)
		{
			pencilTool(m_points, m_brushSize, m_selectedColor);
		}
		else if (m_selectedTool == eToolType::EraserTool)
		{
			eraserTool(m_points, m_brushSize);
		}
		else if (m_selectedTool == eToolType::LineTool)
		{
			lineTool(m_points, m_brushSize, m_selectedColor);
		}
		else if (m_selectedTool == eToolType::RectTool)
		{
			rectTool(m_points, m_brushSize, m_selectedColor);
		}
		else if (m_selectedTool == eToolType::RectTool)
		{
			fillTool(m_points, m_selectedColor);
		}

		drawBorder();
		
		glfwSwapBuffers(m_window);
	}
}

void PaintApp::drawBorder()
{
	glColor3f(0.14, 0.1, 0.25);
	glBegin(GL_POLYGON);

	glVertex2f(-1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(-0.8, -1.0);
	glVertex2f(-0.8, 1.0);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex2f(1.0, 1.0);
	glVertex2f(1.0, -1.0);
	glVertex2f(0.8, -1.0);
	glVertex2f(0.8, 1.0);

	glEnd();
}


std::pair<float, float> PaintApp::getMousePos()
{
	auto [x, y] = Input::getMousePos();
	
	return getMappedPos({x,y});
}

std::pair<float, float> PaintApp::getMappedPos(std::pair<float, float> pair)
{
	auto [x, y] = pair;

	x = (2 * x / m_bufferWidth) - 1;
	y = 1 - (2 * y / m_bufferHeight);

	return { x, y };
}

bool PaintApp::isValueSame(const float& a, const float& b, float epsilon)
{
	return (fabs(a - b) < epsilon);
}

void PaintApp::pencilTool(const std::vector<std::pair<float, float>>& points,const float brushSize, eColor clr)
{
	const Color color = std::move(getColorFromEnum(clr));
	glColor3f(color.r, color.g, color.b);

	glLineWidth(brushSize);
	
	glBegin(GL_LINE_STRIP);
	for (const auto& pos : points)
	{
		glVertex2f(pos.first, pos.second);
	}

	glEnd();
}

void PaintApp::eraserTool(const std::vector<std::pair<float, float>>& points, const float brushSize)
{
	glColor3f(m_clearColor->r, m_clearColor->g, m_clearColor->b);

	glLineWidth(brushSize);

	glBegin(GL_LINE_STRIP);
	for (const auto& pos : points)
	{
		glVertex2f(pos.first, pos.second);
	}

	glEnd();
}

void PaintApp::lineTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr)
{
	const Color color = std::move(getColorFromEnum(clr));
	glColor3f(color.r, color.g, color.b);

	glLineWidth(brushSize);

	glBegin(GL_LINE_STRIP);

	for (const auto& pos : points)
		glVertex2f(pos.first, pos.second);

	glEnd();
}

void PaintApp::rectTool(const std::vector<std::pair<float, float>>& points, const float brushSize, eColor clr)
{
	const Color color = std::move(getColorFromEnum(clr));
	glColor3f(color.r, color.g, color.b);

	glLineWidth(brushSize);

	glBegin(GL_LINE_LOOP);

	for (const auto& pos : points)
		glVertex2f(pos.first, pos.second);

	glEnd();
}

void PaintApp::fillTool(const std::vector<std::pair<float, float>>& points, eColor clr)
{
	const Color color = std::move(getColorFromEnum(clr));
	glColor3f(color.r, color.g, color.b);

	glPointSize(1.0f);
	glBegin(GL_POINTS);

	for (const auto& pos : points)
		glVertex2f(pos.first, pos.second);

	glEnd();
}

int PaintApp::getColorBufferIndex(int x, int y)
{
	return ((y * m_bufferWidth) + x) * 3;
}

void PaintApp::floodFill()
{
	const Color targetClr = std::move(getColorFromEnum(m_selectedColor));
	auto [x, y] = Input::getMousePos();

	if (x < 0 || x >= m_bufferWidth || y < 0 || y >= m_bufferHeight) {
		return;
	}

	std::unordered_set<std::pair<int, int>, pair_hash> set;

	std::vector<float> pixelBuffer(m_bufferWidth * m_bufferHeight * 3);
	glReadPixels(0, 0, m_bufferWidth, m_bufferHeight, GL_RGB, GL_FLOAT, pixelBuffer.data());

	int replacementIndex = getColorBufferIndex(x, m_bufferHeight - y);

	auto queue = std::queue<std::pair<int, int>>();
	queue.push({ x, y});

	while (!queue.empty())
	{
		auto [a, b] = queue.front();
		queue.pop();
		if (a <= 0 || a >= m_bufferWidth || b <= 0 || b >= m_bufferHeight )
			continue;

		if (set.find({a,b}) != set.end())
			continue;

		float index = getColorBufferIndex(a, m_bufferHeight - b);

		if (isValueSame(pixelBuffer[index+0],pixelBuffer[replacementIndex+0]) &&
			isValueSame(pixelBuffer[index+1],pixelBuffer[replacementIndex+1]) &&
			isValueSame(pixelBuffer[index+2],pixelBuffer[replacementIndex+2]))
		{
			set.insert({ a,b });
			queue.push({ a+1,b });
			queue.push({ a,b+1 });
			queue.push({ a-1,b });
			queue.push({ a,b-1 });
		}
	}

	for (const auto& e : set)
	{
		m_points.push_back(getMappedPos(e));
	}
}