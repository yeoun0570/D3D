#include "Sampler_Manager.h"
#include "SamplerState.h"

CSampler_Manager::CSampler_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CSampler_Manager::Initialize()
{
	if (FAILED(Add_SamplerState(g_strLinearSamplerTag, g_LinearSampler)))
		return E_FAIL;
	if (FAILED(Add_SamplerState(g_strPointSamplerTag, g_PointSampler)))
		return E_FAIL;

	return S_OK;
}

HRESULT CSampler_Manager::Add_SamplerState(const wstring_t& strSamplerTag, const D3D11_SAMPLER_DESC& SamplerDesc)
{
	if(nullptr != Find_SamplerState(strSamplerTag))	
		return E_FAIL;

	auto		pSamplerState = CSamplerState::Create(m_pDevice, m_pContext, SamplerDesc);
	if (nullptr == pSamplerState)
		return E_FAIL;

	m_SamplerStates.emplace(strSamplerTag, pSamplerState);

	return S_OK;
}

HRESULT CSampler_Manager::Bind_PixelShader(const wstring_t& strSamplerTag, uint32_t iSlot)
{
	auto		pSamplerState = Find_SamplerState(strSamplerTag);
	if(nullptr == pSamplerState)
		return E_FAIL;

	pSamplerState->Bind_PixelShader(iSlot);

	return S_OK;
}

shared_ptr<class CSamplerState> CSampler_Manager::Find_SamplerState(const wstring_t& strSamplerTag)
{
	auto	iter = m_SamplerStates.find(strSamplerTag);
	if (iter == m_SamplerStates.end())
		return nullptr;		

	return iter->second;	
}

unique_ptr<CSampler_Manager> CSampler_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto    pInstance = unique_ptr<CSampler_Manager>(new CSampler_Manager(pDevice, pContext));

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CSampler_Manager");
		pInstance.reset();
	}

	return pInstance;
}
