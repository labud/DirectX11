#include "GraphicsClass.h"


GraphicsClass::GraphicsClass(void)
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;

}

GraphicsClass::GraphicsClass(const GraphicsClass&)
{

}
GraphicsClass::~GraphicsClass(void)
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//如果对象已经存在，先释放掉它们 
	Shutdown();

	// 创建一个D3DClass对象. 
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// 调用D3DClass初始化函数 
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	//创建摄像机对象 
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// 设置摄像机位置. 
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// 创建模型对象. 
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// 初始化模型对象. 
	result = m_Model->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// 创建shader对象 
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// 初始化shader对象 
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// 释放shader对象. 
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// 释放模型对象. 
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// 释放摄像机对象 
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//销毁m_D3D对象 
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// 调用Render函数，渲染3D场景 
	// Render是GraphicsClass的私有函数. 
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{

	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;


	// 设置framebuffer.为浅蓝色 
	m_D3D->BeginScene(0.0f, 0.0f, 0.5f, 1.0f);

	// 得到view矩阵. 
	m_Camera->Render();

	// 得到3个矩阵. 
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// 把模型顶点和索引缓冲放入管线，准备渲染. 
	m_Model->Render(m_D3D->GetDeviceContext());

	// 用shader渲染. 
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	//把framebuffer中的图像present到屏幕上. 
	m_D3D->EndScene();

	return true;
}
