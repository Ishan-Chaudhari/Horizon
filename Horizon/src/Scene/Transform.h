#pragma once
#include "Math/DxMath.h"

class Transform
{
public:
	Transform();
	void SetPosition(float x,float y,float z);
	void SetScale(float x,float y,float z);
	void SetRotation(float AxisX, float AxisY, float AxisZ, float angle);
	void TranslateBy(float x,float y,float z);
	void ScaleBy(float x,float y,float z);
	void RotateBy(float AxisX, float AxisY, float AxisZ, float angle);
public:
	void SetPosition(HzMath::Vector3 Position);
	void SetScale(HzMath::Vector3 Scale);
	void SetRotation(HzMath::Vector3 RotationAxis, float angle);
	void TranslateBy(HzMath::Vector3 Position);
	void ScaleBy(HzMath::Vector3 Scale);
	void RotateBy(HzMath::Vector3 RotationAxis, float angle);
	HzMath::Matrix* GetTransform();
private:
	HzMath::Matrix World;
};

