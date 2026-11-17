
/* float2, float3, float4 == vector */
/* float2x2, float3x3, float4x4 == matrix */


cbuffer Freq_Object : register(b0)
{
    row_major matrix g_WorldMatrix;
};


cbuffer Freq_Frame : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
};


struct Vertex_In
{
    float3 vPosition : POSITION;
    float2 vTexcoord : TEXCOORD0;
};

struct Vertex_Out
{
    float4 vPosition : SV_POSITION;
    float2 vTexcoord : TEXCOORD0;
};

Vertex_Out main(Vertex_In In)
{
    Vertex_Out Out;
    
    matrix matWV, matWVP;
    
    //matWV = mul(g_WorldMatrix, g_ViewMatrix);
    //matWVP = mul(matWV, g_ProjMatrix);
    
    //Out.vPosition = mul(vector(In.vPosition, 1.f), matWVP);
    Out.vPosition = vector(In.vPosition, 1.f);
    Out.vTexcoord = In.vTexcoord;
    
    return Out;
}

/* SV_POSITION을 가진 데이터에 한해서 w나누기변환, 뷰포트변환. */
/* 래스터라이즈과정을 수행해서 픽셀을 만든다. */