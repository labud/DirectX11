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
	float m_positionX, m_positionY, m_positionZ; //���������������ϵ�е�λ�� 
	float m_rotationX, m_rotationY, m_rotationZ; //�������ŷ����ת�Ƕ� 
	D3DXMATRIX m_viewMatrix;


};
