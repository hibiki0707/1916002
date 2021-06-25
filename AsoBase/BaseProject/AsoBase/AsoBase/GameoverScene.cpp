#include "DxLib.h"
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "GameoverScene.h"

GameoverScene::GameoverScene(SceneManager* manager) : SceneBase(manager)
{
}

void GameoverScene::Init(void)
{
	//�^�C�g���摜�̓ǂݍ���
	mImage = LoadGraph("Image/Scene/End.png");

}

void GameoverScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

}

void GameoverScene::Draw()
{

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// �摜�̕`��
	DrawGraph(0, 0, mImage, true);

}

void GameoverScene::Release(void)
{
	// �摜�̊J��
	DeleteGraph(mImage);
}
