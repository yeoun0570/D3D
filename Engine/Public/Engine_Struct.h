#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagEngineDesc
	{
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
	}VTXPOSTEX;


}


#endif // Engine_Struct_h__
