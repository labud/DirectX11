#pragma once

#include <d3dx10math.h>

class CameraClass
{
public:
	CameraClass(void);
	CameraClass(const CameraClass&);
	~CameraClass(void);
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);
private:
	float m_positionX, m_positionY, m_positionZ; //摄像机在世界坐标系中的位置 
	float m_rotationX, m_rotationY, m_rotationZ; //摄像机的欧拉旋转角度 
	D3DXMATRIX m_viewMatrix;


};
