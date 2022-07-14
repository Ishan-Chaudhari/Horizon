#include "ConstantBuffer.h"
#include "DirectX11.h"

void ConstantBuffer::Create(int buffersize, void* buffer)
{
	D3D11_BUFFER_DESC bdesc = {};

	bdesc.ByteWidth = buffersize;
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bdesc.CPUAccessFlags = 0;
	bdesc.MiscFlags = 0;
	bdesc.StructureByteStride = 0;
	
	D3D11_SUBRESOURCE_DATA subdata = {};
	subdata.pSysMem = buffer;

	DirectX11::GetDevice()->CreateBuffer(&bdesc, &subdata, &Buffer);

}

void ConstantBuffer::Update(void* buffer)
{
	DirectX11::GetContext()->UpdateSubresource(Buffer.Get(), 0, nullptr, buffer, 0, 0);
}

void ConstantBuffer::BindtoVertexShader(int slot)
{
	DirectX11::GetContext()->VSSetConstantBuffers(slot, 1, Buffer.GetAddressOf());
}

void ConstantBuffer::BindtoPixelShader(int slot)
{
	DirectX11::GetContext()->PSSetConstantBuffers(slot, 1, Buffer.GetAddressOf());
}
