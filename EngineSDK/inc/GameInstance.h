#pragma once


#include "Texture.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "Transform.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Input_Device.h"
#include "Timer_Manager.h"
#include "VIBuffer_Rect.h"
#include "Level_Manager.h"
#include "Graphic_Device.h"
#include "Object_Manager.h"
#include "ConstantBuffer.h"
#include "Sampler_Manager.h"
#include "VIBuffer_Terrain.h"
#include "Prototype_Manager.h"

NS_BEGIN(Engine)

class ENGINE_DLL CGameInstance final 
{
	DECLARE_SINGLETON(CGameInstance);

private:
	CGameInstance();
public:
	~CGameInstance() = default;

public:
	/* 엔진을 사용하기 위해 초기화과정을 수행한다. */
	HRESULT Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext);
	void Update_Engine(f32_t fTimeDelta);
	HRESULT Draw_Begin(const float4_t* pClearColor);
	HRESULT Draw(const float4_t* pClearColor);
	HRESULT Draw_End();
	HRESULT Clear_Resources(uint32_t iClearLevelIndex);
	float2_t ViewportSize() const {
		return m_vViewportSize;
	}

#pragma region TIMER_MANAGER
public:
	f32_t Compute_TimeDelta(const wstring_t& strTimerTag);
	HRESULT	Add_Timer(const wstring_t& strTimerTag);
#pragma endregion
#pragma region LEVEL_MANAGER
public:
	HRESULT Change_Level(uint32_t iLevelIndex, shared_ptr<class CLevel> pNewLevel);

#pragma endregion
#pragma region PROTOTYPE_MANAGER
	HRESULT Add_Prototype(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<class CPrototype> pPrototype);
	shared_ptr<CPrototype> Clone_Prototype(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, void* pArg = nullptr);
#pragma endregion
#pragma region OBJECT_MANAGER
	HRESULT Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, void* pArg = nullptr);
#pragma endregion
#pragma region RENDERER
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, shared_ptr<class CGameObject> pRenderObject);
#pragma endregion
#pragma region PIPELINE
	const float4x4_t* Get_Transform(D3DTS eTransformState) const;
	const float4x4_t* Get_Ortho_Transform(D3DTS eTransformState) const;
	const float4x4_t* Get_Transform_Inverse(D3DTS eTransformState) const;
	const float4x4_t* Get_Ortho_Transform_Inverse(D3DTS eTransformState) const;
	const float4_t* Get_CamPosition() const;
	void Set_Transform(D3DTS eTransformState, fmatrix_t TransformMatrix);
	void Set_Ortho_Transform(D3DTS eTransformState, fmatrix_t TransformMatrix);	
#pragma endregion

#pragma region SAMPLER_MANAGER
	HRESULT Add_SamplerState(const wstring_t& strSamplerTag, const D3D11_SAMPLER_DESC& SamplerDesc);
	HRESULT Bind_PixelShader_Sampler(const wstring_t& strSamplerTag, uint32_t iSlot);
#pragma endregion

#pragma region INPUT_DEVICE
	int8_t	Get_DIKeyState(uint8_t byKeyID);
	int8_t	Get_DIMouseState(DIMK eMouse);
	int32_t Get_DIMouseMove(DIMM eMouseState);
#pragma endregion


private:
	unique_ptr<CTimer_Manager>				m_pTimer_Manager = { nullptr };
	unique_ptr<CLevel_Manager>				m_pLevel_Manager = { nullptr };
	unique_ptr<CGraphic_Device>				m_pGraphic_Device = { nullptr };
	unique_ptr<CPrototype_Manager>			m_pPrototype_Manager = { nullptr };
	unique_ptr<CObject_Manager>				m_pObject_Manager = { nullptr };
	unique_ptr<CRenderer>					m_pRenderer = { nullptr };
	unique_ptr<CPipeline>					m_pPipeline = { nullptr };
	unique_ptr<CSampler_Manager>			m_pSampler_Manager = { nullptr };
	unique_ptr<CInput_Device>				m_pInput_Device = { nullptr };

	

private:
	float2_t			m_vViewportSize = {};
	

public:
	void Release_Engine();
	
};

NS_END