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

	// �ő�X�e�[�W��
	static constexpr int MAX_STAGE_NO = 5;

	// ���
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

	// �ו��Ƃ̏Փ˔���
	Box* GetCollisionBox(Vector2 pos);

	// �ו��u����Ƃ̏Փ˔���
	Storage* GetCollisionStorage(Vector2 pos);

	// ���o�p�̃t�F�[�h�N���X
	Fader* mFader;

	// �X�e�[�W�\���̃t�@�C���p�X���擾
	std::string GetCsvPathGround(int StageNo);

	// �M�~�b�N�\���̃t�@�C���p�X���擾
	std::string GetCsvPathGimmick(int StageNo);

private:
	Stage* mStage;
	Unit* mUnit;
	Storage* mStorage;
	

	// ���I�z��
	std::vector<Box*> mBoxes;

	std::vector<Storage*> mStorages;

	// �X�e�[�W�ԍ�
	int mStageNo;

	STATE mState;

	// �X�e�[�W�J��
	void ChangeStage(void);

	// �R�[�h�ŃX�e�[�W�ݒ�
	void SetStage(void);

	// �O���t�@�C�����g�p���A�X�e�[�W�ݒ�
	void LoadGimmickData(void);

	// ��ԑJ��
	void ChangeState(STATE state);
};
