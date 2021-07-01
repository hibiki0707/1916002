#include<DxLib.h>
#include "TimeLimit.h"

TimeLimit::TimeLimit(SceneManager* manager){
	mSceneManager = manager;
}

void TimeLimit::Start(float sec){
	mLimitTime = sec;
}

void TimeLimit::Update(void){
	// mLimitTimを減らす
	if (mLimitTime > 0) {
		mLimitTime--;
	}
}

void TimeLimit::Draw(void){
	// mLimitTimeを表示
	DrawBox(850, 20, 900, 20, 0x000000, true);
	DrawString(900, 10, "%s = 60.00", 0xffffff);

}

bool TimeLimit::IsTimeOver(void){

	return mLimitTime <= 0;
}
