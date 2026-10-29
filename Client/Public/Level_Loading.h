#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Loader.h"

/* 
1. 기존 일반적인 레벨로서의 역활. (레벨안에서 생성된 객체들의 반복적인 업데이트와 렌더를 수행)
2. 다음 레벨에대한 자원준비. 
*/

NS_BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevelID);
	virtual void Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL				m_eNextLevelID = { LEVEL::END };
	shared_ptr<CLoader>	m_pLoader = { nullptr };

public:
	static shared_ptr<CLevel_Loading> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
};

NS_END