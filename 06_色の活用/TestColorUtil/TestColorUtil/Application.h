#pragma once
#include "SceneManager.h"

class Application
{
private:		//�����o�ϐ�
	//�C���X�^���X�̐���
	SceneManager mSceneManager;

public:			//�����o�֐�
	bool Init(void);
	void Run(void);
	bool Release(void);
};