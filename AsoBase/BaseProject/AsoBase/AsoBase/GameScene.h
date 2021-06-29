#pragma once
#include <vector>
#include<string>
#include "GameCommon.h"
#include "Vector2.h"
#include "SceneBase.h"
class SceneManager;
class Stage;
class Unit;
class Box;
class Storage;
class Fader;

class GameScene : public SceneBase
{

public:

	// 最大ステージ数
	static constexpr int MAX_STAGE_NO = 5;

	// 状態
	enum  class STATE
	{
		GAME,
		CLEAR,
		CHANGE_STAGE
	};

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void UpdateGame(void);
	void UpdateClear(void);
	void UpdateChangeStge(void);
	void Draw(void) override;
	void Release(void) override;
	
	Stage* GetStage(void);

	// 荷物との衝突判定
	Box* GetCollisionBox(Vector2 pos);

	// 荷物置き場との衝突判定
	Storage* GetCollisionStorage(Vector2 pos);

	// 演出用のフェードクラス
	Fader* mFader;

	// ステージ構成のファイルパスを取得
	std::string GetCsvPathGround(int StageNo);

	// ギミック構成のファイルパスを取得
	std::string GetCsvPathGimmick(int StageNo);

private:
	Stage* mStage;
	Unit* mUnit;
	Storage* mStorage;
	

	// 動的配列
	std::vector<Box*> mBoxes;

	std::vector<Storage*> mStorages;

	// ステージ番号
	int mStageNo;

	STATE mState;

	// ステージ遷移
	void ChangeStage(void);

	// コードでステージ設定
	void SetStage(void);

	// 外部ファイルを使用し、ステージ設定
	void LoadGimmickData(void);

	// 状態遷移
	void ChangeState(STATE state);
};
