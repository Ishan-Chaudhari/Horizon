#include "Transform.h"

Transform::Transform()
{
	World = DirectX::XMMatrixIdentity();
}

void Transform::SetPosition(float x, float y, float z)
{
	World = DirectX::XMMatrixTranslation(x, y, z);
}

void Transform::SetScale(float x, float y, float z)
{
	World = DirectX::XMMatrixScaling(x, y, z);
}

void Transform::SetRotation(float AxisX, float AxisY, float AxisZ, float angle)
{
	World = DirectX::XMMatrixRotationAxis({ AxisX,AxisY,AxisZ }, DirectX::XMConvertToRadians(angle));
}

void Transform::TranslateBy(float x, float y, float z)
{
	World += DirectX::XMMatrixTranslation(x, y, z);
}

void Transform::ScaleBy(float x, float y, float z)
{
	World += DirectX::XMMatrixScaling(x, y, z);
}

void Transform::RotateBy(float AxisX, float AxisY, float AxisZ, float angle)
{
	World += DirectX::XMMatrixRotationAxis({ AxisX,AxisY,AxisZ }, DirectX::XMConvertToRadians(angle));
}

void Transform::SetPosition(HzMath::Vector3 Position)
{
	World = DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&Position));
}

void Transform::SetScale(HzMath::Vector3 Scale)
{
	World = DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&Scale));	
}

void Transform::SetRotation(HzMath::Vector3 RotationAxis, float angle)
{
	World = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&RotationAxis), DirectX::XMConvertToRadians(angle));
}

void Transform::TranslateBy(HzMath::Vector3 Position)
{
	World += DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&Position));
}

void Transform::ScaleBy(HzMath::Vector3 Scale)
{
	World += DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&Scale));
}

void Transform::RotateBy(HzMath::Vector3 RotationAxis, float angle)
{
	World += DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&RotationAxis), DirectX::XMConvertToRadians(angle));
}

HzMath::Matrix* Transform::GetTransform()
{
	return &World;
}
