#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	//タイトル画像の読み込み
	mImage = LoadGraph("Image/Scene/Title.png");
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAME, true);
	}

}

void TitleScene::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// タイトル画像の描画
	DrawGraph(0, 0, mImage, true);
}

void TitleScene::Release(void)
{
	// 画像の開放
	DeleteGraph(mImage);
}
