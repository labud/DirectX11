///////////// 
// GLOBALS // 
//shader��ʹ�õ�ȫ�ֱ������ڶ�����const buffer�� 
//����shader�������Щ��������gpu��const buffer�� 
///////////// 
cbuffer MatrixBuffer 
{ 
    matrix worldMatrix; 
    matrix viewMatrix; 
    matrix projectionMatrix; 
};

////////////// 
// TYPEDEFS // 
//ע�⣺POSITION, COLOR���������ڶ��嶥�㲼���ж������֡� 
////////////// 
struct VertexInputType 
{ 
    float4 position : POSITION; 
    float4 color : COLOR; 
};

struct PixelInputType 
{ 
    float4 position : SV_POSITION; //SV��ʾϵͳ�Զ�����ĸ�ʽ�� 
    float4 color : COLOR; 
};

//////////////////////////////////////////////////////////////////////////////// 
// Vertex Shader 
//////////////////////////////////////////////////////////////////////////////// 
PixelInputType ColorVertexShader(VertexInputType input) 
{ 
    PixelInputType output; 
    

    //����������չ���ĸ�������������Ϊ1���Ա�������� 
    input.position.w = 1.0f;

    // ����3�����󣬵õ�clip�ռ�����ꡣ 
    output.position = mul(input.position, worldMatrix); 
    output.position = mul(output.position, viewMatrix); 
    output.position = mul(output.position, projectionMatrix); 
    
    //ֱ������������ɫ(.����֮�����ɫ������ò�ֵ�ķ�ʽ���㣩 
    output.color = input.color; 
    
    return output; 
}
