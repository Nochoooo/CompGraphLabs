#include "SimpleManager.h"
#include "D3DInclude.h"


HRESULT SimpleILManager::loadIL(const std::string& key, const D3D11_INPUT_ELEMENT_DESC* desc, UINT numElements, ID3D10Blob* VSBuffer) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    ID3D11InputLayout* inputLayout;
    HRESULT result = device_->CreateInputLayout(desc, numElements, VSBuffer->GetBufferPointer(), VSBuffer->GetBufferSize(), &inputLayout);
    if (SUCCEEDED(result)) {
        load(key, inputLayout);
    }
    return result;
}


HRESULT SimpleVSManager::loadVS(LPCWSTR filePath, const D3D_SHADER_MACRO* macros, const std::string& key,
                                SimpleILManager* ILManager, const D3D11_INPUT_ELEMENT_DESC* desc, UINT numElements) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    D3DInclude includeObj;
    ID3D11VertexShader* vertexShader = nullptr;
    ID3D10Blob* vertexShaderBuffer = nullptr;
    int flags = 0;
#ifdef _DEBUG // ���������/���������� ���������� ���������� ��� �������� � ����������� �� ������������ ������
    flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
    HRESULT result = D3DCompileFromFile(filePath, macros, &includeObj, "main", "vs_5_0", flags, 0, &vertexShaderBuffer, nullptr);
    if (SUCCEEDED(result)) {
        result = device_->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, &vertexShader);
    }
    if (SUCCEEDED(result) && ILManager != nullptr && desc != nullptr) {
        result = ILManager->loadIL(key, desc, numElements, vertexShaderBuffer);
    }
    if (!SUCCEEDED(result)) { // ��� ������������ ��������, ���� �� ������� ������� InputLayout
        SAFE_RELEASE(vertexShader);
    }
    if (SUCCEEDED(result)) {
        load(key, vertexShader);
    }
    SAFE_RELEASE(vertexShaderBuffer);
    return result;
}


HRESULT SimplePSManager::loadPS(LPCWSTR filePath, const D3D_SHADER_MACRO* macros, const std::string& key) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    D3DInclude includeObj;
    ID3D11PixelShader* pixelShader = nullptr;
    ID3D10Blob* pixelShaderBuffer = nullptr;
    int flags = 0;
#ifdef _DEBUG // ���������/���������� ���������� ���������� ��� �������� � ����������� �� ������������ ������
    flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
    HRESULT result = D3DCompileFromFile(filePath, macros, &includeObj, "main", "ps_5_0", flags, 0, &pixelShaderBuffer, nullptr);
    if (SUCCEEDED(result)) {
        result = device_->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, &pixelShader);
    }
    if (SUCCEEDED(result)) {
        load(key, pixelShader);
    }
    SAFE_RELEASE(pixelShaderBuffer);
    return result;
}


HRESULT SimpleSamplerManager::loadSampler(D3D11_FILTER filter, const std::string& key) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    D3D11_SAMPLER_DESC desc = {};
    desc.Filter = filter;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    desc.MipLODBias = 0.0f;
    desc.MaxAnisotropy = 16;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = desc.BorderColor[1] = desc.BorderColor[2] = desc.BorderColor[3] = 1.0f;

    ID3D11SamplerState* sampler = nullptr;
    HRESULT result = device_->CreateSamplerState(&desc, &sampler);
    if (SUCCEEDED(result)) {
        load(key, sampler);
    }
    return result;
}


HRESULT SimpleGeometryManager::loadGeometry(const void* vertices, UINT verticesBytes, const UINT* indices,
                                            UINT indicesBytes, const std::string& key) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = verticesBytes;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA data;
    data.pSysMem = vertices;
    data.SysMemPitch = verticesBytes;
    data.SysMemSlicePitch = 0;

    HRESULT result = device_->CreateBuffer(&desc, &data, &vertexBuffer);

    if (SUCCEEDED(result)) {
        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = indicesBytes;
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA data;
        data.pSysMem = indices;
        data.SysMemPitch = indicesBytes;
        data.SysMemSlicePitch = 0;

        result = device_->CreateBuffer(&desc, &data, &indexBuffer);
    }

    if (SUCCEEDED(result)) {
        objects_.emplace(key, std::make_shared<Geometry>(vertexBuffer, indexBuffer, indicesBytes / sizeof(UINT)));
    }

    return result;
};


HRESULT SimpleTextureManager::loadTexture(LPCWSTR filePath, const std::string& key, const std::string& annotationText) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    ID3D11Resource* texture;
    ID3D11ShaderResourceView* SRV;
    HRESULT result = CreateDDSTextureFromFile(device_.get(), deviceContext_.get(), filePath, &texture, &SRV);
    if (SUCCEEDED(result) && annotationText != "") {
        result = texture->SetPrivateData(WKPDID_D3DDebugObjectName, annotationText.size(), annotationText.c_str());
    }
    if (SUCCEEDED(result)) {
        objects_.emplace(key, std::make_shared<SimpleTexture>(texture, SRV));
    }
    return result;
}


HRESULT SimpleTextureManager::loadCubeMapTexture(LPCWSTR filePath, const std::string& key, const std::string& annotationText) {
    if (check(key))
        return E_FAIL; // �� ��������� ���������� �������� ��� �����

    ID3D11Resource* texture;
    ID3D11ShaderResourceView* SRV;
    HRESULT result = CreateDDSTextureFromFileEx(device_.get(), deviceContext_.get(), filePath,
        0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, D3D11_RESOURCE_MISC_TEXTURECUBE,
        DDS_LOADER_DEFAULT, &texture, &SRV);
    if (SUCCEEDED(result) && annotationText != "") {
        result = texture->SetPrivateData(WKPDID_D3DDebugObjectName, annotationText.size(), annotationText.c_str());
    }
    if (SUCCEEDED(result)) {
        objects_.emplace(key, std::make_shared<SimpleTexture>(texture, SRV));
    }
    return result;
}