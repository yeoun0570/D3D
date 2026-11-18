#include "Pipeline.h"

#include "GameInstance.h"

CPipeline::CPipeline(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice { pDevice }
    , m_pContext { pContext }
{

}

HRESULT CPipeline::Initialize()
{
    for (uint32_t i = 0; i < ETOUI(D3DTS::END); i++)
    {
        XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrix[i], XMMatrixIdentity());
        XMStoreFloat4x4(&m_PipeLineDesc.TransformMatrix[i], XMMatrixIdentity());
        XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrix_Inverse[i], XMMatrixIdentity());
        XMStoreFloat4x4(&m_PipeLineDesc.TransformMatrix_Inverse[i], XMMatrixIdentity());
    }

    m_PipeLineDesc.vCamPosition = XMFLOAT4(0.f, 0.f, 0.f, 1.f);

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_PipeLineDesc, sizeof m_PipeLineDesc);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

void CPipeline::Update()
{
    for (uint32_t i = 0; i < ETOUI(D3DTS::END); i++)
    {
        XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrix_Inverse[i],
            XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_PipeLineDesc.OrthoTransformMatrix[i])));
        XMStoreFloat4x4(&m_PipeLineDesc.TransformMatrix_Inverse[i],
            XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_PipeLineDesc.TransformMatrix[i])));
    }

    memcpy(&m_PipeLineDesc.vCamPosition, &m_PipeLineDesc.TransformMatrix_Inverse[ETOUI(D3DTS::VIEW)].m[3], sizeof float4_t);

}

HRESULT CPipeline::Bind_VertexShader(uint32_t iSlot)
{
    if (FAILED(m_pCB->Update(&m_PipeLineDesc, sizeof m_PipeLineDesc)))
        return E_FAIL;

    m_pCB->Bind_VertexShader(iSlot);

    return S_OK;
}

HRESULT CPipeline::Bind_PixelShader(uint32_t iSlot)
{
    if (FAILED(m_pCB->Update(&m_PipeLineDesc, sizeof m_PipeLineDesc)))
        return E_FAIL;

    m_pCB->Bind_PixelShader(iSlot);

    return S_OK;
}

unique_ptr<CPipeline> CPipeline::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto    pInstance = unique_ptr<CPipeline>(new CPipeline(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CPipeline");
        pInstance.reset();
    }

    return pInstance;
}
