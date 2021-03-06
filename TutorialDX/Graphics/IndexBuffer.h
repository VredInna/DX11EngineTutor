#ifndef IndexBuffer_h_
#define IndexBuffer_h_
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

class IndexBuffer
{
private:

    IndexBuffer(const IndexBuffer& rhs);

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
    UINT mBufferSize = 0;

public:
    IndexBuffer() {};

    ID3D11Buffer* Get() const
    {
        return mBuffer.Get();
    }

    ID3D11Buffer* const* GetAddressOf() const
    {
        return mBuffer.GetAddressOf();
    }

    UINT BufferSize() const
    {
        return this->mBufferSize;
    }

    HRESULT Initialize(ID3D11Device* device, DWORD* data, UINT numVertices)
    {
        this->mBufferSize = numVertices;

        //Load Index Data
        D3D11_BUFFER_DESC indexBufferDesc;
        ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDesc.ByteWidth = sizeof(DWORD) * numVertices;
        indexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        indexBufferDesc.CPUAccessFlags = 0;
        indexBufferDesc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA indexBufferData;
        ZeroMemory(&indexBufferData, sizeof(indexBufferData));
        indexBufferData.pSysMem = data;

        HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, this->mBuffer.GetAddressOf());
        return hr;
    }
};
#endif