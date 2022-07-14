#include "Buffer.h"
#include "Core/Logger.h"
#include "DirectX11.h"

void Buffer::Create(int bufferSize, void* bufferData, int stride, BufferType type)
{
	Type = type;
	Stride = stride;
	Offset = 0;

	if (Type == BufferType::HzVertexBuffer)
		Count = bufferSize / Stride;
	else if (Type == BufferType::HzIndexBuffer)
		Count = bufferSize / sizeof(unsigned int);

	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = bufferSize;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;
	bufdesc.BindFlags = (UINT)type;
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	bufdesc.StructureByteStride = (Type == BufferType::HzVertexBuffer) ? Stride : 0;
	
	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = bufferData;

	DirectX11::GetDevice()->CreateBuffer(&bufdesc, &subdata, &buffer);
}

void Buffer::Bind(unsigned int cbSlot)
{
	if(Type==BufferType::HzVertexBuffer)
		DirectX11::GetContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &Stride, &Offset);
	else	
		DirectX11::GetContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	
}