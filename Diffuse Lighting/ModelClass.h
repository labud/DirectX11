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
	//VertexType��Ҳ�����������滻����ɫ��
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
	
	//������GetTexture���������ڻ���ʱ�����ṩ��Ҫʹ�õ���ͼ��Դ��
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	//��������˽�г�Ա����LoadTexture��ReleaseTexture�����ء�ж��ʹ�õ���ͼ��
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();


	//�����˽�б�����vertex buffer��index buffer��������¼���Ǵ�С��int��ע�����Ƕ�ʹ��ID3D11Buffer���ͣ����ڴ���ʱͨ��buffer description����ʽָ���÷�
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	//m_Texture������ء��ͷš��洢��ͼ��Դ��
	TextureClass* m_Texture;
};