#include "Buffer.h"
#include "Core/Logger.h"
#include "DirectX11.h"

void Buffer::Create(int bufferSize, void* bufferData, int stride, BufferType type)
{
	Type = type;
	Stride = stride;

	if (Type == BufferType::HzVertexBuffer)
		Count = bufferSize / Stride;
	else if (Type == BufferType::HzIndexBuffer)
		Count = bufferSize / sizeof(unsigned int);
	else
		Count = 0;

	Offset = 0;

	D3D11_BUFFER_DESC bufdesc = {};
	bufdesc.ByteWidth = bufferSize;
	bufdesc.Usage = D3D11_USAGE_DEFAULT;

	if (Type == BufferType::HzPixelConstantBuffer || Type == BufferType::HzVertexConstantBuffer)
	{
		bufdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	}
	else
		bufdesc.BindFlags = (UINT)type;
	
	bufdesc.CPUAccessFlags = 0;
	bufdesc.MiscFlags = 0;
	
	if(Type==BufferType::HzVertexBuffer)
	{
		bufdesc.StructureByteStride = Stride;
	}
	else
	{
		bufdesc.StructureByteStride = 0;
	}
	
	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = bufferData;

	DirectX11::GetDevice()->CreateBuffer(&bufdesc, &subdata, &buffer);
}

void Buffer::Bind()
{
	switch (Type)
	{
		case BufferType::HzVertexBuffer:
		{
			DirectX11::GetContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &Stride, &Offset);
			break;
		}
		case BufferType::HzIndexBuffer:
		{
			DirectX11::GetContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			break;
		}
		case BufferType::HzVertexConstantBuffer:
		{
			DirectX11::GetContext()->VSSetConstantBuffers(0, 1, buffer.GetAddressOf());
			break;
		}
		case BufferType::HzPixelConstantBuffer:
		{
			DirectX11::GetContext()->PSSetConstantBuffers(0, 1, buffer.GetAddressOf());
			break;
		}
		default:
		{
			break;
		}
	}
	
}

void Buffer::Update(void* bufferData)
{
	if (Type == BufferType::HzPixelConstantBuffer || Type == BufferType::HzVertexConstantBuffer)
	{
		DirectX11::GetContext()->UpdateSubresource(buffer.Get(), 0, nullptr, bufferData, 0, 0);
	}
}
