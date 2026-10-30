#include "Loader.h"

CLoader::CLoader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

CLoader::~CLoader()
{
    WaitForSingleObject(m_hThread, INFINITE);

    DeleteObject(m_hThread);

    CloseHandle(m_hThread);

    DeleteCriticalSection(&m_CriticalSection);
}

uint32_t APIENTRY ThreadMain(void* pArg)
{
    auto        pLoader = static_cast<CLoader*>(pArg);

    if(FAILED(pLoader->Loading()))
        return 1;

    return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevelID)
{
	m_eNextLevelID = eNextLevelID;

    InitializeCriticalSection(&m_CriticalSection);

	/* 스레드를 생성한다. */
    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain, this, 0, nullptr);
    if (0 == m_hThread)
        return E_FAIL;


	return S_OK;
}

HRESULT CLoader::Loading()
{
    EnterCriticalSection(&m_CriticalSection);

    CoInitializeEx(nullptr, 0);

    HRESULT     hr = {};

    switch (m_eNextLevelID)
    {
    case LEVEL::LOGO:
        hr = Loading_For_LogoLV();
        break;

    case LEVEL::GAMEPLAY:
        hr = Loading_For_GamePlayLV();
        break;
    }

    if (FAILED(hr))
        return E_FAIL;

    CoUninitialize();

    LeaveCriticalSection(&m_CriticalSection);

    return S_OK;
}

#ifdef _DEBUG

void CLoader::Print_Text()
{
    SetWindowText(g_hWnd, m_szLoadingText);
}

#endif

HRESULT CLoader::Loading_For_LogoLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("모델을 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("사운드를 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("원형을 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;

    return S_OK;
}

HRESULT CLoader::Loading_For_GamePlayLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("모델을 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("사운드를 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("원형을 로딩 중 입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;

    return S_OK;
}

shared_ptr<CLoader> CLoader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID)
{
    auto    pInstance = shared_ptr<CLoader>(new CLoader(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevelID)))
    {
        MSG_BOX("Failed to Created : CLoader");
        pInstance.reset();
    }

    return pInstance;
}
