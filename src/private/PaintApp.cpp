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
	m_selectedColor = eColor::White;
	m_selectedTool = eToolType::PencilTool;
	m_clearColor = std::make_unique<Color>(0);

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

	// set openGL backwords & forword compatibitity
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Create Window
	m_window = glfwCreateWindow(1000, 800, "Paint-App", nullptr, nullptr);

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

	if (Input::isButtonDown(Key::ARROW_UP))
	{
		m_brushSize += 1.0;
		m_brushSize = clamp(m_brushSize, 1, 10);
	}

	if (Input::isButtonDown(Key::ARROW_DOWN))
	{
		m_brushSize -= 1.0;
		m_brushSize = clamp(m_brushSize, 1, 10);

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
		if (m_selectedTool == eToolType::PencilTool || m_selectedTool == eToolType::EraserTool)
		{
			m_points.push_back(getMousePos());
		}
	}
	else
	{
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
	}
}

void PaintApp::run()
{
	if (!m_window)
		return;
	
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
		glClearColor(m_clearColor->r, m_clearColor->g, m_clearColor->b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		getPlayerInput();

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
		
		glfwSwapBuffers(m_window);
	}
}


std::pair<float, float> PaintApp::getMousePos()
{
	auto [x, y] = Input::getMousePos();

	x = (2 * x / m_bufferWidth) - 1;
	y = 1 - (2 * y / m_bufferHeight);
	
	return {x,y};
}

void PaintApp::pencilTool(const std::vector<std::pair<float, float>>& points,const float brushSize, eColor clr)
{
	Color color = std::move(getColorFromEnum(clr));
	glColor3f(color.r, color.g, color.b);

	glLineWidth(brushSize);
	
	glBegin(GL_LINE_STRIP);
	for (auto pos : points)
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
	for (auto pos : points)
	{
		glVertex2f(pos.first, pos.second);
	}

	glEnd();
}

