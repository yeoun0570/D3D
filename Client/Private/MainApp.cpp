#include "MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
    CGameInstance::Get().Release_Engine();
}

HRESULT CMainApp::Initialize()
{
    ENGINE_DESC     EngineDesc
    {
        .hWnd = g_hWnd,
        .eWinMode = WINMODE::WIN,
        .iWinSizeX = g_iWinSizeX,
        .iWinSizeY = g_iWinSizeY,
        .iNumLevels = ETOUI(LEVEL::END),
    };

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;

    if (FAILED(Ready_Statics()))
        return E_FAIL;    

    if (FAILED(Start_Level(LEVEL::LOGO)))
        return E_FAIL;

    return S_OK;
}

void CMainApp::Update(f32_t fTimeDelta)
{
    CGameInstance::Get().Update_Engine(fTimeDelta);

}

HRESULT CMainApp::Render()
{
    float4_t        vClearColor = float4_t(0.f, 0.f, 1.f, 1.f);

    if (FAILED(CGameInstance::Get().Draw(&vClearColor)))
        return E_FAIL;

    return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eStartLevel)
{
    if (FAILED(CGameInstance::Get().Change_Level(ETOUI(LEVEL::LOADING),
        CLevel_Loading::Create(m_pDevice, m_pContext, eStartLevel))))
        return E_FAIL;

    return S_OK;
}

HRESULT CMainApp::Ready_Statics()
{
    /* Prototype_Component_VIBuffer_Rect */
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
        CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    /* 
    LPCSTR SemanticName;
    UINT SemanticIndex;
    DXGI_FORMAT Format;
    UINT InputSlot;
    UINT AlignedByteOffset;
    D3D11_INPUT_CLASSIFICATION InputSlotClass;
    UINT InstanceDataStepRate;
    */
    
    /* Prototype_Component_VS_PosTex */
    D3D11_INPUT_ELEMENT_DESC        Elements[2] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },        
    };

    /* Prototype_Component_VS_PosTex */
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), TEXT("Prototype_Component_VS_PosTex"),
        CVertexShader::Create(m_pDevice, m_pContext, TEXT("Bin/ShaderFiles/VertexShader/VS_PosTex.hlsl"), Elements, 2))))
        return E_FAIL;

    /* Prototype_Component_VS_PosTex_Ortho */
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), TEXT("Prototype_Component_VS_PosTex_Ortho"),
        CVertexShader::Create(m_pDevice, m_pContext, TEXT("Bin/ShaderFiles/VertexShader/VS_PosTex.hlsl"), Elements, 2, "main_ortho"))))
        return E_FAIL;

    /* Prototype_Component_PS_PosTex*/
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), TEXT("Prototype_Component_PS_PosTex"),
        CPixelShader::Create(m_pDevice, m_pContext, TEXT("Bin/ShaderFiles/PixelShader/PS_PosTex.hlsl")))))
        return E_FAIL;
        

    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    // uto        pInstance = make_unique<CMainApp>();
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CMainApp");
        pInstance.reset();
    }

    return pInstance;
}
