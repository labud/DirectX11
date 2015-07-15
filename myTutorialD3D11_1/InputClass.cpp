#include "InputClass.h"


InputClass::InputClass(void)
{
}

InputClass::InputClass(const InputClass&)
{

}

InputClass::~InputClass(void)
{
}

void InputClass::Initialize()
{
	int i;

	// ��ʼ���еļ����Ƿǰ���״̬. 
	for (i = 0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	//��������. 
	m_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	//�ͷŰ���. 
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// �жϼ��Ƿ񱻰��£� 
	return m_keys[key];
}
