////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	//VertexType中也用纹理坐标替换掉颜色。
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};


public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	
	//增加了GetTexture方法，用于绘制时可以提供需要使用的贴图资源。
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	//还有两个私有成员函数LoadTexture、ReleaseTexture来加载、卸载使用的贴图。
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();


	//下面的私有变量是vertex buffer和index buffer和两个记录它们大小的int。注意它们都使用ID3D11Buffer类型，并在创建时通过buffer description来显式指明用法
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	//m_Texture负责加载、释放、存储贴图资源。
	TextureClass* m_Texture;
};