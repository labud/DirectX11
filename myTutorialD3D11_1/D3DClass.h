#pragma once

//���ӳ���ʹ�õ�һЩD3D�� 
#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "d3d11.lib") 
#pragma comment(lib, "d3dx11.lib") 
#pragma comment(lib, "d3dx10.lib")

//D3D��һЩͷ�ļ� 
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
	bool m_vsync_enabled; //�Ƿ����ô�ֱͬ�� 
	int m_videoCardMemory; //�Դ��С 
	char m_videoCardDescription[128]; //�Կ����� 
	IDXGISwapChain* m_swapChain; //���������� 
	ID3D11Device* m_device;  //�豸���� 
	ID3D11DeviceContext* m_deviceContext; //�豸�����Ķ��� 
	ID3D11RenderTargetView* m_renderTargetView; //��ȾĿ����ͼ 
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView; //���Ŀ����ͼ 
	ID3D11RasterizerState* m_rasterState; //��Ⱦ״̬ 
	D3DXMATRIX m_projectionMatrix; //ͶӰ���� 
	D3DXMATRIX m_worldMatrix; //��������ϵ���� 
	D3DXMATRIX m_orthoMatrix; //����ͶӰ����


};
