#pragma once

#include "Client_Defines.h"
#include "Engine_Defines.h"

NS_BEGIN(Client)

class CLoader final 
{
private:
	CLoader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLoader();

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	HRESULT Loading();
	bool_t isFinished() const {
		return m_isFinished;
	}

#ifdef _DEBUG
public:
	void Print_Text();

#endif


private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };
	LEVEL							m_eNextLevelID = { LEVEL::END };
	bool_t							m_isFinished = { false };
	wchar_t							m_szLoadingText[MAX_PATH] = {};

private:
	HANDLE							m_hThread = {};
	CRITICAL_SECTION				m_CriticalSection = {};

private:
	HRESULT Loading_For_LogoLV();
	HRESULT Loading_For_GamePlayLV();

public:
	static shared_ptr<CLoader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
};

NS_END
