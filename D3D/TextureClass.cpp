////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
//构造函数将贴图资源指针初始化为空

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
//初始化函数利用Direct3D设备加载给定文件名的文件到shader资源变量m_texture里。加载后，贴图就可以用于渲染了。

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
//清理函数释放已加载的贴图资源并将指针设为空。

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
//当其它对象需要使用贴图进行渲染时，可以调用GetTexture函数来获取贴图资源。

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
