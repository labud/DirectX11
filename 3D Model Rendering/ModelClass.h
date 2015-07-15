////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

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

	// The next change is the addition of a new structure to represent the model format. It is called ModelType. It contains position, texture, and normal vectors the same as our file format does.
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	
	//The Initialize function will now take as input the character string file name of the model to be loaded.
	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	
	//������GetTexture���������ڻ���ʱ�����ṩ��Ҫʹ�õ���ͼ��Դ��
	ID3D11ShaderResourceView* GetTexture();

	// We also have two new functions to handle loading and unloading the model data from the text file.

	bool LoadModel(char*);
	void ReleaseModel();


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

	//The final change is a new private variable called m_model which is going to be an array of the new private structure ModelType. This variable will be used to read in and hold the model data before it is placed in the vertex buffer.

	ModelType* m_model;
};