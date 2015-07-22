#pragma once


#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

#include <assimp/Importer.hpp>      // 导入器在该头文件中定义
#include <assimp/scene.h>           // 读取到的模型数据都放在scene中
#include <assimp/postprocess.h>     // 该头文件中包含后处理的标志位定义


#include "textureclass.h"

class AssimpModelClass
{
	struct VertexType{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal; //法向
		D3DXVECTOR2 texture; //纹理坐标
		//D3DXVECTOR4 Kd;  //材质漫反射系数
		//D3DXVECTOR4 Ks;  //材质的高光系数
	};
public:
	AssimpModelClass();
	AssimpModelClass(const AssimpModelClass&);
	~AssimpModelClass();

	bool Initialize(ID3D11Device*, std::string, WCHAR*);
	void Render(ID3D11DeviceContext*);
	void Shutdown();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();


	void SetPosition(float, float, float);
	void GetPosition(float&, float&, float&);

private:
	bool LoadModel(ID3D11Device*, std::string);
	void RenderBuffers(ID3D11DeviceContext*);
	void ShutdownBuffers();

	bool LoadTexture(ID3D11Device* , WCHAR* );
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	float m_positionX, m_positionY, m_positionZ;
};

