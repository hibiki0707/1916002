#pragma once
#include "Vector2.h"
class Sphere
{
public:

	// ��������
	void Init(void);

	// �X�V�X�e�b�v
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �������
	void Release(void);

	void SetSize(int size);
	Vector2 GetPos(void);
	void SetPos(Vector2 pos);
	void SetColor(int color);

	int Lerp(int start, int end, float t);

	bool InRange(Vector2 pos);

private:

	int mSize;
	Vector2 mPos;
	int mColor;

};

