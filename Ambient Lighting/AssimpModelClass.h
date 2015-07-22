#pragma once


#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

#include <assimp/Importer.hpp>      // �������ڸ�ͷ�ļ��ж���
#include <assimp/scene.h>           // ��ȡ����ģ�����ݶ�����scene��
#include <assimp/postprocess.h>     // ��ͷ�ļ��а�������ı�־λ����


#include "textureclass.h"

class AssimpModelClass
{
	struct VertexType{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal; //����
		D3DXVECTOR2 texture; //��������
		//D3DXVECTOR4 Kd;  //����������ϵ��
		//D3DXVECTOR4 Ks;  //���ʵĸ߹�ϵ��
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

