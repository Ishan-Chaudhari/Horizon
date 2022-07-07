#pragma once
#include <utility>
#include <bitset>
#include "KeyCodes.h"

class Input
{
public:
	static bool IsKeyPressed(int key);
	static bool IsMouseKeyPressed(int key);
	static std::pair<double, double> GetMousePosition();
	static void SetKeyboardState(int key, bool state);
	static void SetMouseState(int key, bool state);
	static void SetMousePosition(double x, double y);
private:
	static std::pair<double, double> MousePosition;
	static std::bitset<256> KeyBuffer;
	static std::bitset<6> MouseBuffer;
};

