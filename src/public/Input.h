#pragma once

#include <Windows.h>
#include <tuple>
#include "glfw3.h"

class Input
{
public:
	static void setActiveWindow(GLFWwindow* window){ s_Instance->m_window = window; }
	static bool isButtonDown(int keycode);
	static bool isButtonPressed(int keycode);
	static std::pair<float, float> getMousePos();

private:
	GLFWwindow* m_window;
public:
	static Input* s_Instance;
};

namespace Key
{
    // Alphabet keys
    constexpr char A = 'A';
    constexpr char B = 'B';
    constexpr char C = 'C';
    constexpr char D = 'D';
    constexpr char E = 'E';
    constexpr char F = 'F';
    constexpr char G = 'G';
    constexpr char H = 'H';
    constexpr char I = 'I';
    constexpr char J = 'J';
    constexpr char K = 'K';
    constexpr char L = 'L';
    constexpr char M = 'M';
    constexpr char N = 'N';
    constexpr char O = 'O';
    constexpr char P = 'P';
    constexpr char Q = 'Q';
    constexpr char R = 'R';
    constexpr char S = 'S';
    constexpr char T = 'T';
    constexpr char U = 'U';
    constexpr char V = 'V';
    constexpr char W = 'W';
    constexpr char X = 'X';
    constexpr char Y = 'Y';
    constexpr char Z = 'Z';

    // Number keys
    constexpr char NUM_0 = '0';
    constexpr char NUM_1 = '1';
    constexpr char NUM_2 = '2';
    constexpr char NUM_3 = '3';
    constexpr char NUM_4 = '4';
    constexpr char NUM_5 = '5';
    constexpr char NUM_6 = '6';
    constexpr char NUM_7 = '7';
    constexpr char NUM_8 = '8';
    constexpr char NUM_9 = '9';

    // Function keys
    constexpr int F1 = VK_F1;
    constexpr int F2 = VK_F2;
    constexpr int F3 = VK_F3;
    constexpr int F4 = VK_F4;
    constexpr int F5 = VK_F5;
    constexpr int F6 = VK_F6;
    constexpr int F7 = VK_F7;
    constexpr int F8 = VK_F8;
    constexpr int F9 = VK_F9;
    constexpr int F10 = VK_F10;
    constexpr int F11 = VK_F11;
    constexpr int F12 = VK_F12;

    // Arrow keys
    constexpr int ARROW_UP = VK_UP;
    constexpr int ARROW_DOWN = VK_DOWN;
    constexpr int ARROW_LEFT = VK_LEFT;
    constexpr int ARROW_RIGHT = VK_RIGHT;

    // Modifier keys
    constexpr int SHIFT = VK_SHIFT;
    constexpr int CTRL = VK_CONTROL;
    constexpr int ALT = VK_MENU;
    constexpr int CAPS_LOCK = VK_CAPITAL;
    constexpr int TAB = VK_TAB;
    constexpr int SPACE = VK_SPACE;
    constexpr int ENTER = VK_RETURN;
    constexpr int BACKSPACE = VK_BACK;
    constexpr int ESCAPE = VK_ESCAPE;

    // Mouse buttons
    constexpr int MOUSE_LEFT = VK_LBUTTON;
    constexpr int MOUSE_RIGHT = VK_RBUTTON;
    constexpr int MOUSE_MIDDLE = VK_MBUTTON;

    // Additional keys
    constexpr int INSERT = VK_INSERT;
    constexpr int DELETEKEY = VK_DELETE;
    constexpr int HOME = VK_HOME;
    constexpr int END = VK_END;
    constexpr int PAGE_UP = VK_PRIOR;
    constexpr int PAGE_DOWN = VK_NEXT;
    constexpr int PAUSE = VK_PAUSE;
    constexpr int PRINT_SCREEN = VK_SNAPSHOT;
    constexpr int NUM_LOCK = VK_NUMLOCK;
    constexpr int SCROLL_LOCK = VK_SCROLL;
}