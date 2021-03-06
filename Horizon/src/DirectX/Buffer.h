#pragma once
#include "Resource.h"

class Buffer
{
public:
	void Create(int bufferSize, void* bufferData, int stride, BufferType type);
	void Bind(unsigned int cbSlot = 0);
	void Update(void* bufferData);
	inline UINT GetCount() { return Count; }
private:
	BufferType Type;
	HzBuffer buffer;
	UINT Stride;
	UINT Count;
	UINT Offset;
};