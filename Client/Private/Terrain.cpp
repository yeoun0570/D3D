#include "Terrain.h"

#include "GameInstance.h"

CTerrain::CTerrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CGameObject { pDevice, pContext }
{
}

HRESULT CTerrain::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CTerrain::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CTerrain::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);


}

void CTerrain::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);


	CGameInstance::Get().Add_RenderGroup(RENDERGROUP::NONBLEND, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CTerrain::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(Bind_Shader_Resources()))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	if (FAILED(Release_Shader_Resources()))
		return E_FAIL;


	return S_OK;
}

HRESULT CTerrain::Ready_Components()
{
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Terrain"),
		TEXT("Com_Texture"), m_pTextureCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Terrain"),
		TEXT("Com_VIBuffer"), m_pVIBufferCom)))
		return E_FAIL;	

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VertexShader_Terrain"),
		TEXT("Com_VS"), m_pShaderCom[ETOUI(SHADER::VERTEX)])))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PixelShader_Terrain"),
		TEXT("Com_PS"), m_pShaderCom[ETOUI(SHADER::PIXEL)])))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Bind_Shader_Resources()
{
	for (auto& pShaderCom : m_pShaderCom)
		pShaderCom->Begin();

	if (FAILED(m_pTransformCom->Bind_VertexShader(0)))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_PixelShader(0)))
		return E_FAIL;	

	if (FAILED(m_pVIBufferCom->Begin()))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Release_Shader_Resources()
{
	if (FAILED(m_pVIBufferCom->End()))
		return E_FAIL;

	for (auto& pShaderCom : m_pShaderCom)
		pShaderCom->End();

	return S_OK;
}

shared_ptr<CTerrain> CTerrain::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto    pInstance = shared_ptr<CTerrain>(new CTerrain(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTerrain");
		pInstance.reset();
	}

	return pInstance;
}


shared_ptr<CPrototype> CTerrain::Clone(void* pArg)
{
	auto    pInstance = shared_ptr<CTerrain>(new CTerrain(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain");
		pInstance.reset();
	}

	return pInstance;
}