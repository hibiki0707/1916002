#include<DxLib.h>
#include"GameCommon.h"
#include"SceneManager.h"
#include "TimeLimit.h"

TimeLimit::TimeLimit(SceneManager* manager){
	mSceneManager = manager;
}

void TimeLimit::Start(float sec){
	mLimitTime = sec;
}

void TimeLimit::Update(void){
	// mLimitTim‚ðŒ¸‚ç‚·
	mLimitTime -= mSceneManager->GetDeltaTime();
	if (mLimitTime < 0) {
		mLimitTime = 0;
	}
	
}

void TimeLimit::Draw(void){
	// mLimitTime‚ð•\Ž¦
	int x2 = SCREEN_SIZE_X - BLOCK_SIZE;
	int width = 200;

	float time = mLimitTime;
	int color = 0x000000;
	if (time < 30.0f) {
		color = 0xff0000;
	}

	DrawBox(850, 20, 900, 20, 0x000000, true);
	SetFontSize(32);
	DrawFormatString(850, color, 0xffffff,"%5%.2f");
	
}

bool TimeLimit::IsTimeOver(void){

	return mLimitTime <= 0;
}
