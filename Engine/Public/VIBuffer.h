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

private:
	ComPtr<ID3D11Buffer>				m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>				m_pIB = { nullptr };

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END