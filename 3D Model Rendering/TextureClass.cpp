////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
//���캯������ͼ��Դָ���ʼ��Ϊ��

TextureClass::TextureClass()
{
	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}
//��ʼ����������Direct3D�豸���ظ����ļ������ļ���shader��Դ����m_texture����غ���ͼ�Ϳ���������Ⱦ�ˡ�

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}
//�������ͷ��Ѽ��ص���ͼ��Դ����ָ����Ϊ�ա�

void TextureClass::Shutdown()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}
//������������Ҫʹ����ͼ������Ⱦʱ�����Ե���GetTexture��������ȡ��ͼ��Դ��

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
