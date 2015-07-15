////////////////////////////////////////////////////////////////////////////////
// Filename: texture.vs
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};
//�����Ժ��ڶ�������ʹ����ɫ�ˣ�ȡ����֮ʹ�����������ꡣ�������������ʹ��UV���������������ǲ�����float2�������洢��vertex shander��pixel shader���������������ΪTEXCOORD0�����ǿ���ʹ�ö��������꣬��������԰�0����Ϊ�κ�������ʹ����һ���������ꡣ

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType TextureVertexShader(VertexInputType input)
{
    PixelInputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    //����һ���е�color vertex shader��ȣ�texture vertex shaderΨһ�������ǲ��ٱ������붥�����ɫ���������������겢���ݸ�pixel shader

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    return output;
}
