#include "AssimpModelClass.h"


AssimpModelClass::AssimpModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
}


AssimpModelClass::~AssimpModelClass()
{
}

bool AssimpModelClass::Initialize(ID3D11Device* device, std::string modelFilename, WCHAR* textureFilename)
{
	bool result;


	// Load the model data,
	result = LoadModel(device, modelFilename);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}


void AssimpModelClass::Shutdown()
{
	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();
	
	return;
}


void AssimpModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int AssimpModelClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* AssimpModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool  AssimpModelClass::LoadModel(ID3D11Device* device, std::string filename)
{
	HRESULT result;

	//注意：首先我们会定义一个assimp导入器类，用该类读入模型文件，我们会做2趟循环，第一趟循环得到顶点和索引的数量，然后创建顶点和索引临时缓冲，用来保存顶点和索引数据，第二趟循环从模型文件中读取顶点和索引的数据，最后创建顶点和索引缓冲。
	Assimp::Importer importer;
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;


	const aiScene* scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Quality);

	if (!scene)
	{
		MessageBoxA(NULL, importer.GetErrorString(), "Error", MB_OK);
		return false;
	}

	int m = 0;
	//第一趟扫描，得到顶点和索引计数
	for (m = 0; m < scene->mNumMeshes; ++m)
	{
		//第m个mesh
		aiMesh* aiMesh = scene->mMeshes[m];

		m_vertexCount += aiMesh->mNumVertices;
		m_indexCount += aiMesh->mNumFaces * 3;
	}

	// 创建顶点临时缓冲.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 创建索引临时缓冲.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	//临时的顶点和索引指针
	int index1 = 0;
	int index2 = 0;
	int i = 0;

	//第二趟循环，得到每个顶点和索引的值
	for (m = 0; m<scene->mNumMeshes; ++m)
	{
		//第m个mesh
		aiMesh* aiMesh = scene->mMeshes[m];

		if (!aiMesh->HasNormals() || !aiMesh->HasTextureCoords(0))
		{
			MessageBox(NULL, L"模型文件中没有纹理坐标或者法向信息", L"Error", MB_OK);
			return false;
		}

		int vertexCount = aiMesh->mNumVertices;
		for (i = 0; i < vertexCount; ++i)
		{
			vertices[index1].position = D3DXVECTOR3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);
			vertices[index1].normal = D3DXVECTOR3(aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z);
			vertices[index1].texture = D3DXVECTOR2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
			//vertices[index1].Kd = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);
			//vertices[index1].Ks = D3DXVECTOR4(0.2, 0.2, 0.2, 1.0);
			index1++;
		}

		for (i = 0; i < aiMesh->mNumFaces; ++i)
		{
			const aiFace& Face = aiMesh->mFaces[i];
			//assert(Face.mNumIndices == 3);
			indices[index2] = Face.mIndices[0];
			index2++;
			indices[index2] = Face.mIndices[1];
			index2++;
			indices[index2] = Face.mIndices[2];
			index2++;

		}
	}
	// 设置顶点缓冲描述
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// 指向保存顶点数据的临时缓冲.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 创建顶点缓冲.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 设置索引缓冲描述.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// 指向存临时索引缓冲.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// 创建索引缓冲.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 释放临时缓冲.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;

}

bool AssimpModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, filename);
	if (!result)
	{
		return false;
	}

	return true;
}


void AssimpModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void AssimpModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void AssimpModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void AssimpModelClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void AssimpModelClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}