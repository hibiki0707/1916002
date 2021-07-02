//#pragma once
#include "TestScene.h"
class SceneBase;
class Fader;
class Support;

// �V�[���Ǘ��p
enum class SCENE_ID
{
	NONE
	, TITLE
	, GAME
	, GAMEOVER
};

class SceneManager
{

public:

	void Init(void);
	void Update(void);
	void Release(void);

	void ChangeScene(SCENE_ID nextId, bool isFading);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void);

private:

	SCENE_ID mSceneID;
	SCENE_ID mWaitSceneID;

	SceneBase* mScene;
	Fader* mFader;
	Support* mSupport;

	bool mIsSceneChanging;

	// �f���^�^�C��
	float mTickCount;
	float mDeltaTime;

	void DoChangeScene(void);

};