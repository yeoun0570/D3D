#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HINSTANCE		hInstance;
		HWND			hWnd;
		WINMODE			eWinMode;
		uint32_t		iWinSizeX;
		uint32_t		iWinSizeY;
		uint32_t		iNumLevels;
	}ENGINE_DESC;

	typedef struct tagPipelineDesc
	{
		XMFLOAT4X4		OrthoTransformMatrix[ETOUI(D3DTS::END)];
		XMFLOAT4X4		OrthoTransformMatrix_Inverse[ETOUI(D3DTS::END)];
		XMFLOAT4X4		TransformMatrix[ETOUI(D3DTS::END)];
		XMFLOAT4X4		TransformMatrix_Inverse[ETOUI(D3DTS::END)];
		XMFLOAT4		vCamPosition;		
	}PIPELINE_DESC;

	typedef struct tagVertexPositionTexcoord
	{
		XMFLOAT3			vPosition;
		XMFLOAT2			vTexcoord;

		static const unsigned int			   iNumElements = { 2 };

		static constexpr D3D11_INPUT_ELEMENT_DESC        Elements[2] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}VTXPOSTEX;

	typedef struct tagVertexPositionNormalTexcoord
	{
		XMFLOAT3			vPosition;
		XMFLOAT3			vNormal;
		XMFLOAT2			vTexcoord;

		static const unsigned int			   iNumElements = { 3 };

		static constexpr D3D11_INPUT_ELEMENT_DESC        Elements[iNumElements] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}VTXNORTEX;


}


#endif // Engine_Struct_h__
