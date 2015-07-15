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
//我们以后不在顶点类型使用颜色了，取而代之使用了纹理坐标。由于纹理坐标仅使用UV两个浮点数，我们采用了float2类型来存储。vertex shander和pixel shader中纹理坐标的语义为TEXCOORD0。我们可以使用多纹理坐标，所以你可以把0更换为任何数字来使用另一组纹理坐标。

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
    //与上一节中的color vertex shader相比，texture vertex shader唯一的区别是不再保存输入顶点的颜色，而保存纹理坐标并传递给pixel shader

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    return output;
}
