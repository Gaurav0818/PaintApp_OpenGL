#include "Input.h"

bool Input::isButtonDown(int keycode)
{
	return GetAsyncKeyState(keycode) & 0x0001;
}

bool Input::isButtonPressed(int keycode)
{
	SHORT state = GetAsyncKeyState(keycode);
	return state & 0x8000 || state & 0x0001 ;
}

std::pair<float, float> Input::getMousePos()
{
	double xPos, yPos;
	glfwGetCursorPos(s_Instance->m_window, &xPos, &yPos);

	return { (float)xPos, (float)yPos };
}