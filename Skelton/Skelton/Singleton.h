#pragma once
/// <summary>
/// �V���O���g���N���X
/// ���̃N���X�́u�I�u�W�F�N�g��1�����Ȃ��v����
/// �ۏ؂���N���X
/// </summary>
class Singleton
{
private:
	/// �R���X�g���N�^��private�ɒu�����Ƃ�
	/// �N���C�A���g�������ł��Ȃ��悤�ɂ���
	Singleton() {};
	// �R�s�[�Ƒ���̋֎~
	Singleton(const Singleton&)=delete;
	void operator=(const Singleton&)=delete; //	���
	 int counter = 0;

public:
	// �C���X�^���X�擾�֐�
	static Singleton& Instance() {
		static Singleton instance;	// ���ꂪ�B��̃I�u�W�F�N�g
		return instance;
	}
	void Out();
};

