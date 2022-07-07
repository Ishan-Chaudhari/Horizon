#include "Input.h"
#include "Logger.h"

std::pair<double, double> Input::MousePosition;
std::bitset<256> Input::KeyBuffer;
std::bitset<6> Input::MouseBuffer;

bool Input::IsKeyPressed(int key)
{
	return KeyBuffer[key];
}

bool Input::IsMouseKeyPressed(int key)
{
	return MouseBuffer[key];
}

std::pair<double, double> Input::GetMousePosition()
{
	return MousePosition;
}

void Input::SetKeyboardState(int key, bool state)
{
	KeyBuffer[key] = state;
}

void Input::SetMouseState(int key, bool state)
{
	MouseBuffer[key] = state;
}

void Input::SetMousePosition(double x, double y)
{
	MousePosition = std::make_pair(x, y);
}
