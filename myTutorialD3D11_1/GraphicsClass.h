#pragma once

#include <windows.h> 
#include "d3dclass.h" 
#include "cameraclass.h" 
#include "modelclass.h" 
#include "colorshaderclass.h"

///////////// 
// GLOBALS // 
///////////// 
const bool FULL_SCREEN = true; //�Ƿ�ȫ�� 
const bool VSYNC_ENABLED = true; //�Ƿ�ֱͬ�� 
const float SCREEN_DEPTH = 1000.0f; //��ȣ�Զ�� 
const float SCREEN_NEAR = 0.1f; //��ȣ�����

class GraphicsClass
{
public:
	GraphicsClass(void);
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass(void);
	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

	//����һ��D3DClass���Ա���� 
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;

};
