#include "Level_Logo.h"

#include "GameInstance.h"
#include "Level_Loading.h"
#include "BackGround.h"

CLevel_Logo::CLevel_Logo(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CLevel { pDevice, pContext }
{
}

HRESULT CLevel_Logo::Initialize()
{
    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;

   

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

HRESULT CLevel_Logo::Ready_Layer_BackGround(const wstring_t& strLayerTag)
{
    /* 원형 백그라운드를 찾아서 복제한다. */
   CBackGround::BACKGROUND_DESC		Desc{};
   /*  auto    pGameObject = CGameInstance::Get().Clone_Prototype(ETOUI(LEVEL::LOGO), TEXT("Prototype_GameObject_BackGround"), &Desc);*/

   if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::LOGO), TEXT("Prototype_GameObject_BackGround"), ETOUI(LEVEL::LOGO), strLayerTag, &Desc)))
       return E_FAIL;

   /* 복제본에게 필요한 데이터 CBackGround::BACKGROUND_DESC를 셋팅해서 넘긴다. */
   //BACKGROUND_DESC		Desc{};
   //Desc.vColor = ;
   //Desc.fX = ;
   //Desc.fY = ;
   //Desc.fSizeX = ;
   //Desc.fSizeY = ;
   //Desc.iData = ;


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
