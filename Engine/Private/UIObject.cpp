#include "UIObject.h"

CUIObject::CUIObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}

HRESULT CUIObject::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CUIObject::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto		pDesc = static_cast<UIOBJECT_DESC*>(pArg);

        m_fX = pDesc->fX;
        m_fY = pDesc->fY;
        m_fSizeX = pDesc->fSizeX;
        m_fSizeY = pDesc->fSizeY;
    }

    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    Update_Transform();
    
    return S_OK;
}

void CUIObject::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CUIObject::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    Update_Transform();
}

void CUIObject::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
}

HRESULT CUIObject::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    return S_OK;
}

void CUIObject::Update_Transform()
{
    m_pTransformCom->SetUp_Scale(m_fSizeX, m_fSizeY, 1.f);
    m_pTransformCom->Set_State(STATE::POSITION,
        XMVectorSet(m_fX - CGameInstance::Get().ViewportSize().x * 0.5f, -m_fY + CGameInstance::Get().ViewportSize().y * 0.5f, 0.f, 1.f));

}
