#include <DxLib.h>
#include<vector>
#include<string>
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Unit.h"
#include "Box.h"
#include "Storage.h"
#include "Vector2.h"
#include"Fader.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager){
	mStageNo = 1;
	ChangeState(STATE::GAME);
	mFader = new Fader();
	mFader->Init();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Init(void){

	// ステージ
	mStage = new Stage(this);
	mStage->Init(mStageNo);
	
	// ステージ
	SetStage();

	
}

/// <summary>
/// 更新ステップ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Update(void){

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
	}

	// ステージ
	mStage->Update();
	// Unit
	mUnit->Update();
	
	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Update();
	}

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Update();
	}

	// クリア判定
	bool isClear = true;
	size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		if (mBoxes[i]->IsStayStorage() == false) {
			isClear = false;
			break;
		}
	}

	if (isClear == true) {
		if (mStageNo >= MAX_STAGE_NO) {
			// ゲームオーバー画面へ遷移
			mSceneManager->ChangeScene(SCENE_ID::GAMEOVER, true);
		}
		else {
			// 次のステージへ
			ChangeStage();
		}
	
	}

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name=""></param>
void GameScene::Draw(void){

	SetDrawScreen(DX_SCREEN_BACK);

	// 画面のクリア
	ClearDrawScreen();

	// ステージ
	mStage->Draw();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Draw();
	}
	// Unit
	mUnit->Draw();

	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Draw();
	}

}

/// <summary>
/// リソース解放
/// </summary>
/// <param name=""></param>
/// <returns></returns>
void GameScene::Release(void){
	// ステージ
	mStage->Release();
	delete mStage;
	// Unit
	mUnit->Release();
	delete mUnit;

	// 動的配列
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		mBoxes[i]->Release();
		delete mBoxes[i];
	}
	// 動的配列のサイズをゼロにする
	mBoxes.clear();

	int sizes = mStorages.size();
	for (int i = 0; i < sizes; i++) {
		mStorages[i]->Release();
		delete mStorages[i];
	}
	mStorages.clear();
}

Stage* GameScene::GetStage(void){

	return mStage;
}

Box* GameScene::GetCollisionBox(Vector2 pos){
	Box* ret = nullptr;

	Vector2 boxPos;
	int size = mBoxes.size();
	for (int i = 0; i < size; i++) {
		boxPos = mBoxes[i]->GetPos();
		// 座標の比較
		if (pos.x == boxPos.x && pos.y == boxPos.y) {
			// 座標が一致したらBoxを戻り値にする
			ret = mBoxes[i];
			break;
		}
		
	}

	return ret;
}

Storage* GameScene::GetCollisionStorage(Vector2 pos){
	// 引数の座標と一致する荷物置き場を検索
	// 見つからなければ、nullptrを返す
	Storage* ret = nullptr;

	Vector2 storagePos;
	int size = mStorages.size();
	for (int i = 0; i < size; i++) {
		storagePos = mStorages[i]->GetPos();
		// 座標の比較
		if (pos.x == storagePos.x && pos.y == storagePos.y) {
			// 座標が一致したらBoxを戻り値にする
			ret = mStorages[i];
			break;
		}

	}
	return ret;
}

std::string GameScene::GetCsvPathGround(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GROUND;

	return ret;
}

void GameScene::ChangeStage(void){
	Release();
	// 次のステージへ行くため
	mStageNo++;
	Init();
}

void GameScene::SetStage(void){

	// 荷物
	Box* tmpBox;
	// 荷物置き場
	Storage* tmpStorage;


	switch (mStageNo)
	{
	case 1:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,10 });

		tmpBox = new Box(this);
		tmpBox->Init({ 11,10 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,10 });
		mBoxes.push_back(tmpBox);
		
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 11,11 });
		mStorages.push_back(tmpStorage);
		break;
	case 2:
		// Unit
		mUnit = new Unit(this);
		mUnit->Init({ 10,6 });

		// 荷物
		tmpBox = new Box(this);
		tmpBox->Init({ 11,7 });
		mBoxes.push_back(tmpBox);

		tmpBox = new Box(this);
		tmpBox->Init({ 18,8 });
		mBoxes.push_back(tmpBox);

		// 荷物置き場
		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,10 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,11 });
		mStorages.push_back(tmpStorage);

		tmpStorage = new Storage(this);
		tmpStorage->Init({ 16,12 });
		mStorages.push_back(tmpStorage);
		break;
	default:
		break;
	}
}

void GameScene::ChangeState(STATE state){

}

