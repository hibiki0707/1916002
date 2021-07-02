#pragma once
#include "Vector2.h"
class Star
{
public:

	static constexpr int SPEED_SLOW_ROT = 4;

	// ��������
	void Init(void);

	// �X�V�X�e�b�v
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �������
	void Release(void);

	Vector2 GetPos(void);
	void SetPos(Vector2 pos);
	void SetSizeRate(float rate);

private:

	int mImage;

	Vector2 mPos;

	int mRot;

	float mSizeRate;

};

