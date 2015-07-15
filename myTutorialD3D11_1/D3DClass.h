#pragma once

//链接程序使用的一些D3D库 
#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "d3d11.lib") 
#pragma comment(lib, "d3dx11.lib") 
#pragma comment(lib, "d3dx10.lib")

//D3D的一些头文件 
#include <dxgi.h> 
#include <d3dcommon.h> 
#include <d3d11.h> 
#include <d3dx10math.h>


class D3DClass
{
public:
	D3DClass(void);
	D3DClass(const D3DClass&);
	~D3DClass(void);

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(D3DXMATRIX&);
	void GetWorldMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

	void GetVideoCardInfo(char*, int&);

private:
	bool m_vsync_enabled; //是否启用垂直同步 
	int m_videoCardMemory; //显存大小 
	char m_videoCardDescription[128]; //显卡名字 
	IDXGISwapChain* m_swapChain; //交换链对象 
	ID3D11Device* m_device;  //设备对象 
	ID3D11DeviceContext* m_deviceContext; //设备上下文对象 
	ID3D11RenderTargetView* m_renderTargetView; //渲染目标视图 
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView; //深度目标视图 
	ID3D11RasterizerState* m_rasterState; //渲染状态 
	D3DXMATRIX m_projectionMatrix; //投影矩阵 
	D3DXMATRIX m_worldMatrix; //世界坐标系矩阵 
	D3DXMATRIX m_orthoMatrix; //正交投影矩阵


};
