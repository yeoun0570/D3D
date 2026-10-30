#include "Level_Logo.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CLevel_Logo::CLevel_Logo(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CLevel { pDevice, pContext }
{
}

HRESULT CLevel_Logo::Initialize()
{
	return S_OK;
}

void CLevel_Logo::Update(f32_t fTimeDelta)
{
    if (GetKeyState(VK_RETURN) & 0x8000)
    {
        if (FAILED(CGameInstance::Get().Change_Level(ETOUI(LEVEL::LOADING),
            CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL::GAMEPLAY))))
            return;
    }
}

HRESULT CLevel_Logo::Render()
{
#ifdef _DEBUG
    SetWindowText(g_hWnd, TEXT("로고레벨입니다."));
#endif

	return S_OK;
}

shared_ptr<CLevel_Logo> CLevel_Logo::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto    pInstance = shared_ptr<CLevel_Logo>(new CLevel_Logo(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CLevel_Logo");
        pInstance.reset();
    }

    return pInstance;
}
