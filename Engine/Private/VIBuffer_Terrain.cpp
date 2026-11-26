#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CVIBuffer { pDevice, pContext }
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(const wchar_t* pHeightMapFilePath)
{
    BITMAPFILEHEADER            fh = {};
    BITMAPINFOHEADER            ih = {};
    shared_ptr<uint32_t[]>      pPixel = {};

    DWORD       dwByte = {};
    HANDLE      hFile = CreateFile(pHeightMapFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (0 == hFile)
        return E_FAIL;

    ReadFile(hFile, &fh, sizeof fh, &dwByte, nullptr);
    ReadFile(hFile, &ih, sizeof ih, &dwByte, nullptr);

    m_iNumVerticesX = ih.biWidth;
    m_iNumVerticesZ = ih.biHeight;

    m_iNumVertices = m_iNumVerticesX * m_iNumVerticesZ;

    pPixel = make_shared<uint32_t[]>(m_iNumVertices);

    ReadFile(hFile, pPixel.get(), sizeof uint32_t * m_iNumVertices, &dwByte, nullptr);

#pragma region PUBLIC
    m_iNumVertexBuffers = 1;
    m_iVertexStride = sizeof VTXNORTEX;   
    m_iIndexStride = 4;
    m_iNumIndices = (m_iNumVerticesX - 1) * (m_iNumVerticesZ - 1) * 2 * 3;
    m_eIndexFormat = DXGI_FORMAT_R32_UINT;
    m_ePrimitiveTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
         
#pragma endregion

#pragma region VERTEXBUFFER
    D3D11_BUFFER_DESC       VertexBufferDesc{};
    VertexBufferDesc.ByteWidth = m_iVertexStride * m_iNumVertices;
    VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = 0;
    VertexBufferDesc.MiscFlags = 0;
    VertexBufferDesc.StructureByteStride = m_iVertexStride;

    shared_ptr<VTXNORTEX[]> pVertices = make_shared<VTXNORTEX[]>(m_iNumVertices);

    for (uint32_t i = 0; i < m_iNumVerticesZ; i++)
    {
        for (uint32_t j = 0; j < m_iNumVerticesX; j++)
        {
            uint32_t    iIndex = i * m_iNumVerticesX + j;


            /*
            pPixel[iIndex] : 11111111 11011111 11011111 11011111
        &                    00000000 00000000 00000000 11111111
                             00000000 00000000 00000000 11011111
                             */


            pVertices[iIndex].vPosition = float3_t(j, (pPixel[iIndex] & 0x000000ff) / 10.f, i);
            pVertices[iIndex].vNormal = float3_t(0.f, 0.f, 0.f);
            pVertices[iIndex].vTexcoord = float2_t(j / (m_iNumVerticesX - 1.f), i / (m_iNumVerticesZ - 1.f));
        }
    }


#pragma endregion

#pragma region INDEXBUFFER
    D3D11_BUFFER_DESC       IndexBufferDesc{};
    IndexBufferDesc.ByteWidth = m_iIndexStride * m_iNumIndices;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    IndexBufferDesc.CPUAccessFlags = 0;
    IndexBufferDesc.MiscFlags = 0;
    IndexBufferDesc.StructureByteStride = m_iIndexStride;

    shared_ptr<uint32_t[]> pIndices = make_shared<uint32_t[]>(m_iNumIndices);

    uint32_t        iNumIndices = {};

    for (uint32_t i = 0; i < m_iNumVerticesZ - 1; i++)
    {
        for (uint32_t j = 0; j < m_iNumVerticesX - 1; j++)
        {
            uint32_t    iIndex = i * m_iNumVerticesX + j;

            uint32_t    iIndices[4] = {
                iIndex + m_iNumVerticesX, 
                iIndex + m_iNumVerticesX + 1,
                iIndex + 1,
                iIndex
            };

            vector_t    vSour, vDest, vNormal;

            pIndices[iNumIndices++] = iIndices[0];
            pIndices[iNumIndices++] = iIndices[1];
            pIndices[iNumIndices++] = iIndices[2];

            vSour = XMLoadFloat3(&pVertices[iIndices[1]].vPosition) - XMLoadFloat3(&pVertices[iIndices[0]].vPosition);
            vDest = XMLoadFloat3(&pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&pVertices[iIndices[1]].vPosition);
            vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

            XMStoreFloat3(&pVertices[iIndices[0]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[0]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[1]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[1]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[2]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[2]].vNormal) + vNormal);



            pIndices[iNumIndices++] = iIndices[0];
            pIndices[iNumIndices++] = iIndices[2];
            pIndices[iNumIndices++] = iIndices[3];

            vSour = XMLoadFloat3(&pVertices[iIndices[2]].vPosition) - XMLoadFloat3(&pVertices[iIndices[0]].vPosition);
            vDest = XMLoadFloat3(&pVertices[iIndices[3]].vPosition) - XMLoadFloat3(&pVertices[iIndices[2]].vPosition);
            vNormal = XMVector3Normalize(XMVector3Cross(vSour, vDest));

            XMStoreFloat3(&pVertices[iIndices[0]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[0]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[2]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[2]].vNormal) + vNormal);
            XMStoreFloat3(&pVertices[iIndices[3]].vNormal,
                XMLoadFloat3(&pVertices[iIndices[3]].vNormal) + vNormal);
        }
    }

    for (uint32_t i = 0; i < m_iNumVertices; i++)
    {
        XMStoreFloat3(&pVertices[i].vNormal,
            XMVector3Normalize(XMLoadFloat3(&pVertices[i].vNormal)));
    }


    D3D11_SUBRESOURCE_DATA          VertexInitialData{
        .pSysMem = pVertices.get(),
    };

    if (FAILED(m_pDevice->CreateBuffer(&VertexBufferDesc, &VertexInitialData, &m_pVB)))
        return E_FAIL;

 
    D3D11_SUBRESOURCE_DATA          IndexInitialData{
      .pSysMem = pIndices.get(),
    };

    if (FAILED(m_pDevice->CreateBuffer(&IndexBufferDesc, &IndexInitialData, &m_pIB)))
        return E_FAIL;

#pragma endregion

    CloseHandle(hFile);

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CVIBuffer_Terrain> CVIBuffer_Terrain::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const wchar_t* pHeightMapFilePath)
{
    auto    pInstance = shared_ptr<CVIBuffer_Terrain>(new CVIBuffer_Terrain(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pHeightMapFilePath)))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Terrain");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_Terrain::Clone(void* pArg)
{
    auto    pInstance = shared_ptr<CVIBuffer_Terrain>(new CVIBuffer_Terrain(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Terrain");
        pInstance.reset();
    }

    return pInstance;
}


