#include "ModelClass.h"


ModelClass::ModelClass(void)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

}

ModelClass::ModelClass(const ModelClass & others)
{

}

ModelClass::~ModelClass(void)
{
}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;


	// ��ʼ�����㻺��Ͷ�����������. 
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	// �ͷŶ������������. 
	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// �Ѷ���������������ͼ�ι��ߣ�׼����Ⱦ. 
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	//��������������� 
	return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//���ȣ����Ǵ���2����ʱ�����Ŷ�����������ݣ��Ա����ʹ�á�. 

	// ���ö��㻺���СΪ8��һ��������. 
	m_vertexCount = 8;

	// �������������С. 
	m_indexCount = 36;

	// ����������ʱ����. 
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// ������������. 
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}
	//����˳ʱ�뷽��������Σ����ֹ��� 
	// ���ö�������. 
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	vertices[0].color = WHITE;

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	vertices[1].color = BLACK;

	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	vertices[2].color = RED;

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	vertices[3].color = GREEN;

	vertices[4].position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vertices[4].color = BLUE;

	vertices[5].position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vertices[5].color = YELLOW;

	vertices[6].position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vertices[6].color = CYAN;

	vertices[7].position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vertices[7].color = MAGENTA;

	// ����������������. 
	indices[0] = 0;  // ǰ�� 
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	indices[6] = 4;  // ���� 
	indices[7] = 6;
	indices[8] = 5;
	indices[9] = 4;
	indices[10] = 7;
	indices[11] = 6;

	indices[12] = 4;  // ���� 
	indices[13] = 5;
	indices[14] = 1;
	indices[15] = 4;
	indices[16] = 1;
	indices[17] = 0;

	indices[18] = 3;  //���� 
	indices[19] = 2;
	indices[20] = 6;
	indices[21] = 3;
	indices[22] = 6;
	indices[23] = 7;

	indices[24] = 1;  // ���� 
	indices[25] = 5;
	indices[26] = 6;
	indices[27] = 1;
	indices[28] = 6;
	indices[29] = 2;

	indices[30] = 4; // ���� 
	indices[31] = 0;
	indices[32] = 3;
	indices[33] = 4;
	indices[34] = 3;
	indices[35] = 7;


	// ���ö��㻺������ 
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// ָ�򱣴涥�����ݵ���ʱ����. 
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// �������㻺��. 
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// ����������������. 
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// ָ�����ʱ��������. 
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// ������������. 
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// �ͷ���ʱ����. 
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::ShutdownBuffers()
{
	// �ͷŶ��㻺��. 
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// �ͷ��������� 
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// ���ö��㻺���Ⱥ�ƫ��. 
	stride = sizeof(VertexType);
	offset = 0;

	//��input assemberl�׶ΰ󶨶��㻺�壬�Ա��ܹ�����Ⱦ 
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//��input assemberl�׶ΰ��������壬�Ա��ܹ�����Ⱦ 
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// ������Ԫ���壬��Ⱦ�������б�. 
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
