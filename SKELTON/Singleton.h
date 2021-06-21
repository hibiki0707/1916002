#pragma once

/// <summary>
/// �V���O���`���N���X
/// ���̃N���X�́u�I�u�W�F�N�g��������Ȃ��v����
/// �ۏ؂���N���X
/// </summary>
class Singleton
{
private:
	Singleton() {};
	// �R�s�[�Ƒ���̋֎~
	Singleton(const Singleton&)=delete; // �R�s�[�R���X�g���N�^
	void operator=(const Singleton&)=delete; // ���
	int counter = 0;
public:
	// �C���X�^���X�擾�֐�
	static Singleton& Instance() {
		static Singleton instance;	// �B��̃I�u�W�F�N�g
		return instance;
	}
	void Out();
};

