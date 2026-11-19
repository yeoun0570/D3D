
texture2D g_Texture[2] : register(t0);

sampler g_LinearSampler : register(s0);

struct Pixel_In
{
    float4 vPosition : SV_POSITION;
    float2 vTexcoord : TEXCOORD0;
};

struct Pixel_Out
{
    float4 vColor : SV_TARGET0;
};

Pixel_Out main(Pixel_In In)
{
    Pixel_Out Out;
    
    Out.vColor = g_Texture[1].Sample(g_LinearSampler, In.vTexcoord);
    
    return Out;
}