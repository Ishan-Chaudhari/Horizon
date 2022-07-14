#include "Camera.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Logger.h"

bool Camera::FirstMouse = true;
double Camera::lastX;
double Camera::lastY;
double Camera::MouseSensitivity = 0.1;

void Camera::Create()
{
	Position = DirectX::XMVectorSet(0.0f, 0.f, -3.f, 0.f);
	Front = DirectX::XMVectorSet(0.f, 0.f, 1.f, 0.f);
	Up = DirectX::XMVectorSet(0.f, 1.f, 0.f, 0.f);

	View = DirectX::XMMatrixLookAtLH(Position, DirectX::XMVectorAdd(Position, Front), Up);
	SetProjection();
	
	DirectX::XMStoreFloat3(&CamPosition, Position);

	WvpBuff.Create(sizeof(buf), &buf);
	WvpBuff.BindtoVertexShader(0);

	CamBuff.Create(sizeof(cbuf), &cbuf);
	CamBuff.BindtoPixelShader(2);

	yaw = 90.f;
	pitch = 0.f;


}

void Camera::Update()
{
	KeyBoardInput();
	MouseInput();
	View = DirectX::XMMatrixLookAtLH(Position, DirectX::XMVectorAdd(Position, Front), Up);
}

HzMath::Vector3 Camera::GetCameraPosition()
{
	return CamPosition;
}

void Camera::SetProjection()
{
	auto [x, y, t] = Application::GetWindowProps();
	Projection = DirectX::XMMatrixPerspectiveFovLH(45.f * 3.14f / 180.f, (float)x / y, 0.5f, 1000.f);
}

void Camera::SetWvpBuffer(HzMath::Matrix& WorldMatrix)
{
	buf.World = WorldMatrix;
	buf.Wvp = DirectX::XMMatrixTranspose(WorldMatrix * View * Projection);
	UpdateBuffer();
}

void Camera::UpdateBuffer()
{
	WvpBuff.Update(&buf);
	CamBuff.Update(&cbuf);
}

HzMath::Matrix Camera::GetViewProjection()
{
	return View * Projection;
}

void Camera::KeyBoardInput()
{
	float CameraSpeed = 0.05f;

	if (Input::IsKeyPressed(VK_KEY_W))
	{
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Front, CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	if (Input::IsKeyPressed(VK_KEY_S))
	{
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(Front, CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	if (Input::IsKeyPressed(VK_KEY_A))
	{
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(DirectX::XMVector3Cross(Front, Up), CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	if (Input::IsKeyPressed(VK_KEY_D))
	{
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(DirectX::XMVector3Cross(Front, Up), CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	if (Input::IsKeyPressed(VK_KEY_Q))
	{
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Up, CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	if (Input::IsKeyPressed(VK_KEY_E))
	{
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(Up, CameraSpeed));
		DirectX::XMStoreFloat3(&CamPosition, Position);
	}
	
}

void Camera::MouseInput()
{
	if (FirstMouse)
	{
		auto [x, y] = Input::GetMousePosition();
		lastX = x; lastY = y;
		FirstMouse = false;
	}

	MousePos = Input::GetMousePosition();

	xOff = lastX - MousePos.first;
	yOff = lastY - MousePos.second;

	lastX = MousePos.first; lastY = MousePos.second;

	if (Input::IsMouseKeyPressed(VK_RBUTTON))
	{
		xOff *= MouseSensitivity;
		yOff *= MouseSensitivity;

		yaw += xOff;
		pitch += yOff;

		if (pitch > 89.f)pitch = 89.f;
		if (pitch < -89.f)pitch = -89.f;

		TempVector.x = (float)(cos(yaw * 0.017445) * cos(pitch * 0.017445));
		TempVector.y = (float)(sin(pitch * 0.017445));
		TempVector.z = (float)(sin(yaw * 0.017445) * cos(pitch * 0.017445));

		Front = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&TempVector));
	}

}


