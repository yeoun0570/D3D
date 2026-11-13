#include "BackGround.h"

#include "GameInstance.h"

CBackGround::CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CUIObject{ pDevice, pContext }
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
	if (nullptr != pArg)
	{
		auto		pDesc = static_cast<BACKGROUND_DESC*>(pArg);
		m_vColor = pDesc->vColor;
	}

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CBackGround::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CBackGround::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);
}

void CBackGround::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);


	CGameInstance::Get().Add_RenderGroup(RENDERGROUP::PRIORITY, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Begin()))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	//if (FAILED(m_pVIBufferCom->End()))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CBackGround::Ready_Components()
{
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOGO), TEXT("Prototype_Component_Texture_BackGround"),
		TEXT("Com_Texture"), m_pTextureCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), m_pVIBufferCom)))
		return E_FAIL;	

	return S_OK;
}

shared_ptr<CBackGround> CBackGround::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto    pInstance = shared_ptr<CBackGround>(new CBackGround(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBackGround");
		pInstance.reset();
	}

	return pInstance;
}


shared_ptr<CPrototype> CBackGround::Clone(void* pArg)
{
	auto    pInstance = shared_ptr<CBackGround>(new CBackGround(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBackGround");
		pInstance.reset();
	}

	return pInstance;
}