#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CVIBuffer() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

	virtual HRESULT Begin();
	virtual HRESULT Render();
	virtual HRESULT End();

protected:
	ComPtr<ID3D11Buffer>				m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>				m_pIB = { nullptr };

protected:
	uint32_t							m_iNumVertexBuffers = {};
	uint32_t							m_iNumVertices = {};
	uint32_t							m_iVertexStride = {};
	uint32_t							m_iNumIndices = {};
	uint32_t							m_iIndexStride = {};
	DXGI_FORMAT							m_eIndexFormat = {};
	D3D11_PRIMITIVE_TOPOLOGY			m_ePrimitiveTopology = {};

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END