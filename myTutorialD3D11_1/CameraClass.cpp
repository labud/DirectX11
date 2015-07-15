#include "CameraClass.h"


CameraClass::CameraClass(void)
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}

CameraClass::CameraClass(const CameraClass& other)
{
}

CameraClass::~CameraClass(void)
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}


D3DXVECTOR3 CameraClass::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// 设置up向量为(0,1,0). 
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// 设置摄像机的位置. 
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// 设置摄像机lookat的方向. 
	//lookAt.x = 0.0f; 
	//lookAt.y = 0.0f; 
	//lookAt.z = 1.0f; 
	//设置摄像机始终指向原点 
	D3DXVec3Normalize(&lookAt, &position);
	lookAt = lookAt * (-1);

	// 得到弧度单位的欧拉旋转 yaw (Y axis), pitch (X axis), 以及 roll (Z axis) . 
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// 得到旋转矩阵. 
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// 变换lookat和up向量，一般view能够在原点被正确旋转. 
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// 平移旋转后的摄像机位置. 
	lookAt = position + lookAt;

	// 创建view矩阵. 
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}


void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
