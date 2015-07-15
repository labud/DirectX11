#pragma once 
class InputClass
{
public:
	InputClass(void);
	InputClass(const InputClass&);
	~InputClass(void);

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];//�������256��������Ƿ񱻰��� 
};