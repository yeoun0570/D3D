#pragma once

#include "Engine_Defines.h"
#include "ConstantBuffer.h"

NS_BEGIN(Engine)

class CPipeline final
{
private:
	CPipeline(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPipeline() = default;

public:
	const float4x4_t* Get_Transform(D3DTS eTransformState) const {
		return &m_PipeLineDesc.TransformMatrix[ETOUI(eTransformState)];
	}
	const float4x4_t* Get_Ortho_Transform(D3DTS eTransformState) const {
		return &m_PipeLineDesc.OrthoTransformMatrix[ETOUI(eTransformState)];
	}
	const float4x4_t* Get_Transform_Inverse(D3DTS eTransformState) const {
		return &m_PipeLineDesc.TransformMatrix_Inverse[ETOUI(eTransformState)];
	}
	const float4x4_t* Get_Ortho_Transform_Inverse(D3DTS eTransformState) const {
		return &m_PipeLineDesc.OrthoTransformMatrix_Inverse[ETOUI(eTransformState)];
	}
	const float4_t* Get_CamPosition() const {
		return &m_PipeLineDesc.vCamPosition;
	}

	void Set_Transform(D3DTS eTransformState, fmatrix_t TransformMatrix) {
		XMStoreFloat4x4(&m_PipeLineDesc.TransformMatrix[ETOUI(eTransformState)], TransformMatrix);
	}
	void Set_Ortho_Transform(D3DTS eTransformState, fmatrix_t TransformMatrix) {
		XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrix[ETOUI(eTransformState)], TransformMatrix);
	}

public:
	HRESULT Initialize();
	void Update();
	HRESULT Bind_VertexShader(uint32_t iSlot);
	HRESULT Bind_PixelShader(uint32_t iSlot);



private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };


private:
	PIPELINE_DESC			m_PipeLineDesc{};

private:
	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };

public:
	static unique_ptr<CPipeline> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);


};

NS_END