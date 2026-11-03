#pragma once

#include "GameObject.h"

NS_BEGIN(Engine)

class CLayer final 
{
private:
	CLayer();

public:
	~CLayer() = default;

public:
	HRESULT Add_GameObject(shared_ptr<CGameObject> pGameObject);
	virtual void Priority_Update(f32_t fTimeDelta);
	virtual void Update(f32_t fTimeDelta);
	virtual void Late_Update(f32_t fTimeDelta);
private:
	list<shared_ptr<CGameObject>>			m_GameObjects;

public:
	static shared_ptr<CLayer> Create();
};

NS_END