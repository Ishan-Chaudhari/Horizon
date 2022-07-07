#pragma once
#include <DirectXMath.h>
#include <cstdint>

namespace HzMath
{
	typedef DirectX::XMFLOAT4 Vector4;
	typedef DirectX::XMFLOAT3 Vector3;
	typedef DirectX::XMFLOAT2 Vector2;
	typedef float Vector1;
	typedef DirectX::XMVECTOR Vector;

	typedef DirectX::XMFLOAT3X3 Matrix_3x3;
	typedef DirectX::XMFLOAT4X4 Matrix_4x4;
	typedef DirectX::XMFLOAT4X3 Matrix_4x3;
	typedef DirectX::XMMATRIX Matrix;
}
