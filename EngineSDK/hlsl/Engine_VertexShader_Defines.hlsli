


cbuffer Freq_Object : register(b0)
{
    row_major float4x4 g_WorldMatrix;
};

cbuffer Freq_Frame : register(b1)
{
    row_major float4x4 g_OrthoViewMatrix, g_OrthoProjMatrix;
    row_major float4x4 g_OrthoViewMatrixInv, g_OrthoProjMatrixInv;
    row_major float4x4 g_ViewMatrix, g_ProjMatrix;
    row_major float4x4 g_ViewMatrixInv, g_ProjMatrixInv;
    float4 g_vCamPosition;
};