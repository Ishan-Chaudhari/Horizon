#pragma once
#include "DxMath.h"
#include "DirectX/Buffer.h"
#include <utility>

class Camera
{
	struct WvpBuffer
	{
		HzMath::Matrix Wvp;
	};
public:
	void Create();
	void Update();
	void SetProjection();
	void CalculateWvp(HzMath::Matrix& WorldMatrix);
	HzMath::Matrix GetViewProjection();
private:
	HzMath::Matrix Projection;
	HzMath::Matrix View;
	HzMath::Vector Position;
	HzMath::Vector Front;
	HzMath::Vector Up;
	Buffer WvpBuff;
	WvpBuffer buf;
private:
	void KeyBoardInput();
	void MouseInput();
	void UpdateBuffer();
private:
	static bool FirstMouse;
	static double lastX, lastY;
	static double MouseSensitivity;
	double xOff, yOff, yaw, pitch;
	std::pair<double, double> MousePos;
	DirectX::XMFLOAT3 TempVector;
};

