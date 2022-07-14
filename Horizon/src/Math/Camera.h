#pragma once
#include "DxMath.h"
#include "DirectX/ConstantBuffer.h"
#include <utility>

class Camera
{
	struct WvpBuffer
	{
		HzMath::Matrix Wvp;
		HzMath::Matrix World;
	};
	struct CamBuffer
	{
		HzMath::Vector3 Pos;
		float null = 0.f;
	};
public:
	void Create();
	void Update();
	HzMath::Vector3 GetCameraPosition();
	void SetProjection();
	void SetWvpBuffer(HzMath::Matrix& WorldMatrix);
	HzMath::Matrix GetViewProjection();
private:
	HzMath::Vector3 CamPosition;
	HzMath::Matrix Projection;
	HzMath::Matrix View;
	HzMath::Vector Position;
	HzMath::Vector Front;
	HzMath::Vector Up;
	ConstantBuffer WvpBuff;
	ConstantBuffer CamBuff;
	WvpBuffer buf;
	CamBuffer cbuf;
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

