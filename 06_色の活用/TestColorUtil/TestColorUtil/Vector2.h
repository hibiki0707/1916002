#pragma once
class Vector2
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2();

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// ���`���
	// ����(�J�n���W�A�I�����W�A����(0.0f�`1.0f))
	static Vector2 Lerp(Vector2 start, Vector2 end, float t);

};

