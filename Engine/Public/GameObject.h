#pragma once


#include "GameInstance.h"

NS_BEGIN(Engine)

class ENGINE_DLL CGameObject abstract : public CPrototype
{
public:
	typedef struct tagGameObjectDesc : public CTransform::TRANSFORM_DESC
	{
		/* CGameObject생성시에 필요한 데이터를 받아온다. */
		uint32_t	iData = {};		
	}GAMEOBJECT_DESC;
protected:
	CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CGameObject() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta);
	virtual void Update(f32_t fTimeDelta);
	virtual void Late_Update(f32_t fTimeDelta);
	virtual HRESULT Render();

public:
	shared_ptr<CComponent> Find_Component(const wstring_t& strComponentTag);


protected:
	uint32_t					m_iData = {};
	shared_ptr<CTransform>		m_pTransformCom = { nullptr };

protected:
	map<const wstring_t, shared_ptr<CComponent>>		m_Components;

protected:
	template<typename T>
	HRESULT Add_Component(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag,
		const wstring_t& strComponentTag, shared_ptr<T>& pOut, void* pArg = nullptr)
	{
		if (nullptr != Find_Component(strComponentTag))
			return E_FAIL;

		auto	pComponent = dynamic_pointer_cast<T>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
		if (nullptr == pComponent)
			return E_FAIL;

		m_Components.emplace(strComponentTag, pComponent);

		pOut = pComponent;

		return S_OK;
	}

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END