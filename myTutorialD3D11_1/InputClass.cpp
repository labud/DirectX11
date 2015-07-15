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

	// 初始所有的键都是非按下状态. 
	for (i = 0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void InputClass::KeyDown(unsigned int input)
{
	//键被按下. 
	m_keys[input] = true;
	return;
}


void InputClass::KeyUp(unsigned int input)
{
	//释放按键. 
	m_keys[input] = false;
	return;
}


bool InputClass::IsKeyDown(unsigned int key)
{
	// 判断键是否被按下？ 
	return m_keys[key];
}
