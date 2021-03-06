#include <DxLib.h>
#include<vector>
#include<string>
#include<fstream>
#include<stack>
#include "KeyCheck.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Unit.h"
#include "Box.h"
#include "Storage.h"
#include "Vector2.h"
#include"Fader.h"
#include"Utility.h"
#include"TimeLimit.h"
#include "GameScene.h"

GameScene::GameScene(SceneManager* manager) : SceneBase(manager){
	mStageNo = 1;
	ChangeState(STATE::GAME);
	mFader = new Fader();
	mFader->Init();

	mTimeLimit = new TimeLimit(manager);
	
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
	//SetStage();

	// 外部ファイルを使用し、ステージ設定
	LoadGimmickData();

	mImageClear = LoadGraph("Image/Congratulations.png");
	mStepClear = 0.0f;

	// 時間制限
	mTimeLimit->Start(mStageNo * 60);
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

	switch (mState)
	{
	case GameScene::STATE::GAME: 
		UpdateGame();
		break;
	case GameScene::STATE::CLEAR:
		UpdateClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		UpdateChangeStge();
		break;
	
	}
}

void GameScene::UpdateGame(void){
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

	// 操作を戻すNキー
	if (keyTrgDown[ KEY_P1_A ] && mHistoryBack.size() > 0
		&& mUnit->IsEnableBack() && mBox->IsEnableBack()) {

		// 最後の操作情報を取得
		History his = mHistoryBack.top();

		// 最後の操作情報をユニットに渡して巻き戻し処理をさせる
		mUnit->BackMove(his);

		// 最後の操作情報を削除
		mHistoryBack.pop();
	}


	// 時間制限
	mTimeLimit->Update();
	if (mTimeLimit->IsTimeOver() == true) {
		mSceneManager->ChangeScene(SCENE_ID::GAMEOVER,true);
		return;
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
			//ChangeStage();
			ChangeState(STATE::CLEAR);
			return;
		}

	}
}

void GameScene::UpdateClear(void){
	mStepClear+= mSceneManager->GetDeltaTime();
	if (mStepClear > TIME_CLEAR_) {
		
		ChangeState(STATE::CHANGE_STAGE);
		return;
	}
}

void GameScene::UpdateChangeStge(void){
	mFader->Update();

	Fader::FADE_STATE state = mFader->GetState();

	switch (state)
	{
	case Fader::FADE_STATE::FADE_OUT:
		// 段々暗くする
		if (mFader->IsEnd() == true) {
			// ステージ切り替え
			ChangeStage();
			// 徐々に明るくする
			mFader->SetFade(Fader::FADE_STATE::FADE_IN);
		}

		break;
	case Fader::FADE_STATE::FADE_IN:
		// 段々明るくする
		if (mFader->IsEnd() == true) {
			mFader->SetFade(Fader::FADE_STATE::NONE);
			ChangeState(STATE::GAME);
		}
		break;
	
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

	switch (mState)
	{
	case GameScene::STATE::GAME:
		DrawGame();
		break;
	case GameScene::STATE::CLEAR:
		DrawClear();
		break;
	case GameScene::STATE::CHANGE_STAGE:
		DrawChangeStge();
		break;

	}
}

void GameScene::DrawGame(void){
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

	// 時間制限
	mTimeLimit->Draw();


}

void GameScene::DrawClear(void) {
	DrawGame();

	// ステージクリアの画面表示
	DrawGraph(SCREEN_SIZE_X / 2 - (500 / 2)
		, SCREEN_SIZE_Y / 2
		, mImageClear, true);

}

void GameScene::DrawChangeStge(void){

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

	DeleteGraph(mImageClear);
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

std::string GameScene::GetCsvPathGimmick(int StageNo){
	std::string ret = "";

	ret += FILE_PATH_CSV;
	ret += std::to_string(StageNo);
	ret += "/";
	ret += FILE_NAME_GIMMICK;

	return ret;
}

void GameScene::RegisHistory(DIR dir, Vector2 pos, Box* box){
	Vector2 boxPos = { 0,0 };
	if (box != nullptr) {
		boxPos = box->GetPos();

	}

	History his = {dir,pos,box,boxPos};
	mHistoryBack.push(his);
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

void GameScene::LoadGimmickData(void){
	
	// ファイルパスを取得
	std:: string filePath = GetCsvPathGimmick(mStageNo);

	// ファイルを読み込む
	std::ifstream ifs(filePath);

	// 1行ずつ読み込む
	int y = 0;
	std::string line;

	// 荷物
	Box* tmpBox;

	// 荷物置き場
	Storage* tmpStorage;

	while (getline(ifs, line)) {

		// Yで分割されたline
		std::vector<std::string> strvec = Utility::Split(line, ',');

		// Xで分割されたstrvec

		// mMapに値を代入して、
		// ステージを作成
		for (int x = 0; x < strvec.size(); x++) {
			int chipNo = stoi(strvec[x]);
			switch (chipNo)
			{

			case 4:
				// 荷物
				tmpBox = new Box(this);
				tmpBox->Init({ x,y });
				mBoxes.push_back(tmpBox);
				break;

			case 5:
				// 荷物置き場
				tmpStorage = new Storage(this);
				tmpStorage->Init({ x,y });
				mStorages.push_back(tmpStorage);
				break;
			case 6:
				// ユニット
				// Unit
				mUnit = new Unit(this);
				mUnit->Init({ x,y });
				break;
			}
		}
		y++;
	}

	if (true) {}
}

void GameScene::ChangeState(STATE state){
	mState = state;
	switch (state)
	{
	case GameScene::STATE::GAME:
		break;
	case GameScene::STATE::CLEAR:
		mStepClear = 0.0f;
		break;
	case GameScene::STATE::CHANGE_STAGE:
		// だんだん暗くする
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		break;

	}

}

