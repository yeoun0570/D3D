#pragma once

#include "VIBuffer.h"

NS_BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Terrain final : public CVIBuffer
{
protected:
	CVIBuffer_Terrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CVIBuffer_Terrain() = default;
public:
	virtual HRESULT Initialize_Prototype(const wchar_t* pHeightMapFilePath);
	virtual HRESULT Initialize(void* pArg) override;

private:
	uint32_t		m_iNumVerticesX{}, m_iNumVerticesZ{};

public:
	static shared_ptr<CVIBuffer_Terrain> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const wchar_t* pHeightMapFilePath);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END