#include "GameInstance.h"

#include "Level_Manager.h"

CGameInstance::CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
    m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, pDevice, pContext);
    if (nullptr == m_pGraphic_Device)
        return E_FAIL;

    m_pTimer_Manager = CTimer_Manager::Create();
    if (nullptr == m_pTimer_Manager)
        return E_FAIL;

    m_pLevel_Manager = CLevel_Manager::Create();
    if (nullptr == m_pLevel_Manager)
        return E_FAIL;

    m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
    if (nullptr == m_pPrototype_Manager)
        return E_FAIL;


    return S_OK;
}

void CGameInstance::Update_Engine(f32_t fTimeDelta)
{
    m_pLevel_Manager->Update(fTimeDelta);
}

HRESULT CGameInstance::Draw_Begin(const float4_t* pClearColor)
{
    if (FAILED(m_pGraphic_Device->Clear_BackBuffer_View(pClearColor)))
        return E_FAIL;
    if (FAILED(m_pGraphic_Device->Clear_DepthStencil_View()))
        return E_FAIL;

    return S_OK;
}

HRESULT CGameInstance::Draw(const float4_t* pClearColor)
{
    if (FAILED(Draw_Begin(pClearColor)))
        return E_FAIL;

    /* ±×¸°´Ù. */

    if (FAILED(m_pLevel_Manager->Render()))
        return E_FAIL;
    
    if (FAILED(Draw_End()))
        return E_FAIL;   

    return S_OK;
}

HRESULT CGameInstance::Draw_End()
{
    if (FAILED(m_pGraphic_Device->Present()))
        return E_FAIL;

    return S_OK;
}

HRESULT CGameInstance::Clear_Resources(uint32_t iClearLevelIndex)
{

    return S_OK;
}
#pragma region TIMER_MANAGER
f32_t CGameInstance::Compute_TimeDelta(const wstring_t& strTimerTag)
{
    return m_pTimer_Manager->Compute_TimeDelta(strTimerTag);    
}

HRESULT CGameInstance::Add_Timer(const wstring_t& strTimerTag)
{
    return m_pTimer_Manager->Add_Timer(strTimerTag);
}

#pragma endregion

#pragma region LEVEL_MANAGER
HRESULT CGameInstance::Change_Level(uint32_t iLevelIndex, shared_ptr<class CLevel> pNewLevel)
{
    return m_pLevel_Manager->Change_Level(iLevelIndex, pNewLevel);;
}

#pragma endregion

void CGameInstance::Release_Engine()
{
    m_pPrototype_Manager.reset();

    m_pLevel_Manager.reset();
    
    m_pTimer_Manager.reset();

    m_pGraphic_Device.reset();
}
