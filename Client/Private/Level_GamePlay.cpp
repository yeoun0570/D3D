#include "Level_GamePlay.h"

#include "GameInstance.h"

#include "Camera_Free.h"

CLevel_GamePlay::CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CLevel { pDevice, pContext }
{
}

HRESULT CLevel_GamePlay::Initialize()
{
    if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
        return E_FAIL;
        

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Update(f32_t fTimeDelta)
{
}

HRESULT CLevel_GamePlay::Render()
{
#ifdef _DEBUG
    SetWindowText(g_hWnd, TEXT("게임플레이레벨입니다."));
#endif
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const wstring_t& strLayerTag)
{
    CCamera_Free::CAMERA_FREE_DESC       CameraFreeDesc{};
    CameraFreeDesc.vEye = float3_t(0.f, 20.f, -10.f);
    CameraFreeDesc.vAt = float3_t(0.f, 0.f, 0.f);
    CameraFreeDesc.fFovy = 65.f;
    CameraFreeDesc.fNear = 0.1f;
    CameraFreeDesc.fFar = 1000.f;
    CameraFreeDesc.fMouseSensor = 0.05f;
    CameraFreeDesc.fSpeedPerSec = 40.f;
    CameraFreeDesc.fRotationDegreePerSec = 180.f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Camera_Free"),
        ETOUI(LEVEL::GAMEPLAY), strLayerTag, &CameraFreeDesc)))
        return E_FAIL;

    return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const wstring_t& strLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Terrain"),
        ETOUI(LEVEL::GAMEPLAY), strLayerTag)))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto    pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CLevel_GamePlay");
        pInstance.reset();
    }

    return pInstance;
}
