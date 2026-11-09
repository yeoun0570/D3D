#include "VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CVIBuffer { pDevice, pContext }
{
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CVIBuffer_Rect> CVIBuffer_Rect::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto    pInstance = shared_ptr<CVIBuffer_Rect>(new CVIBuffer_Rect(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CVIBuffer_Rect");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVIBuffer_Rect::Clone(void* pArg)
{
    auto    pInstance = shared_ptr<CVIBuffer_Rect>(new CVIBuffer_Rect(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVIBuffer_Rect");
        pInstance.reset();
    }

    return pInstance;
}


