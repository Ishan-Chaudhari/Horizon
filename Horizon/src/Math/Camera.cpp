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

	WvpBuff.Create(sizeof(buf), &buf, 0, BufferType::HzVertexConstantBuffer);
	WvpBuff.Bind();

	yaw = 90.f;
	pitch = 0.f;
}

void Camera::Update()
{
	UpdateBuffer();
	KeyBoardInput();
	MouseInput();
	View = DirectX::XMMatrixLookAtLH(Position, DirectX::XMVectorAdd(Position, Front), Up);
}

void Camera::SetProjection()
{
	auto [x, y, t] = Application::GetWindowProps();
	Projection = DirectX::XMMatrixPerspectiveFovLH(45.f * 3.14f / 180.f, (float)x / y, 0.5f, 1000.f);
}

void Camera::CalculateWvp(HzMath::Matrix& WorldMatrix)
{
	buf.Wvp = DirectX::XMMatrixTranspose(WorldMatrix * View * Projection);
}

void Camera::UpdateBuffer()
{
	WvpBuff.Bind();
	WvpBuff.Update(&buf);
}

HzMath::Matrix Camera::GetViewProjection()
{
	return View * Projection;
}

void Camera::KeyBoardInput()
{
	if (Input::IsKeyPressed(VK_KEY_W))
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Front, 0.01f));
	if (Input::IsKeyPressed(VK_KEY_S))
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(Front, 0.01f));
	if (Input::IsKeyPressed(VK_KEY_A))
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(DirectX::XMVector3Cross(Front, Up), 0.01f));
	if (Input::IsKeyPressed(VK_KEY_D))
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(DirectX::XMVector3Cross(Front, Up), 0.01f));
	if (Input::IsKeyPressed(VK_KEY_Q))
		Position = DirectX::XMVectorAdd(Position, DirectX::XMVectorScale(Up, 0.01f));
	if (Input::IsKeyPressed(VK_KEY_E))
		Position = DirectX::XMVectorSubtract(Position, DirectX::XMVectorScale(Up, 0.01f));
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

		TempVector.x = cos(yaw * 0.017445) * cos(pitch * 0.017445);
		TempVector.y = sin(pitch * 0.017445);
		TempVector.z = sin(yaw * 0.017445) * cos(pitch * 0.017445);

		Front = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&TempVector));
	}

}


