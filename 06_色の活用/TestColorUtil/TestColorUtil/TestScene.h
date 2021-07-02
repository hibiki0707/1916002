#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <map>
#include "Vector2.h"
#include "Unit.h"
#include "Smoke.h"
#include "Enemy.h"
#include "JumpMan.h"
#include "SceneBase.h"
class SceneManager;
class Star;
class Sphere;
class StarDustManager;

// �`��̈�
#define DRAW_AREA_X 0
#define DRAW_AREA_Y 20

// �u���b�N�̉摜�T�C�Y
#define BLOCK_IMG_SIZE_X 16
#define BLOCK_IMG_SIZE_Y 16

// png�̉摜��
#define IMG_NUM_X 8
#define IMG_NUM_Y 106
#define IMG_NUM_ALL 848

// ��ʕ�����
#define SPLIT_X 1
#define SPLIT_Y 1

// �^�C�g���\���̗]��
#define TITLE_MARGIN 5

// �e�X�g�p�w�i�̗]��
#define GROUND_MARGIN 40

// �}�b�v�T�C�Y
#define MAP_SIZE_X 56
#define MAP_SIZE_Y 32

// �ő�y�[�W��
#define MAX_PAGES 6

class TestScene : public SceneBase
{

public:

	static constexpr int CHR_HEIGHT = 15;

	TestScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawBackGround(void);
	void Release(void) override;

	int GetPage(void);

private:

	// ���K�̃y�[�W�ԍ�
	int mPage;

	int mImgBlockGreen;
	int mImgBlockBlue;
	int mImgPlanePurple;
	int mImgPlaneRed;
	int mImgPlaneGreen;
	int mImgPlaneWhite;
	
	int mImages[IMG_NUM_ALL];
	int mWidth;
	int mHeight;

	int mImgBackGround;

	// ���`�悷��ۂɎg�p����Q�����z��
	int mData[MAP_SIZE_Y][MAP_SIZE_X];

	// ���|�C���^�p�ϐ�
	int mPower;
	int mSpeed;
	int* mSpeedPtr;

	// ��Lerp�p�ϐ�
	Star* mStar;
	Star* mStarChildren[3];
	Vector2 mMvSPos;
	Vector2 mMvEPos;
	float mMoveStep;
	Sphere* mSphere;
	
	// �������p�ϐ�
	int mArray01[5] = { 10, 30, 50, 80, 130 };
	
	int mArray02[5] = { 10, 30, 50, 80, 130 };
	std::vector<int> mAns02;

	Unit mUnits[4] = { 
		Unit(80, "��m", {15, 15}),
		Unit(20, "���@�g��", {10, 10}),
		Unit(50, "������", {20, 20}),
		Unit(10, "���E", {50, 50}),
	};
	std::vector<std::string> mAnsUnits;

	Vector2 mTraps[6] = {
		{10, 10},
		{15, 15},
		{20, 20},
		{25, 25},
		{30, 30},
		{35, 35},
	};

	std::vector<Unit> mUnitsVec;
	std::map<int, Unit> mUnitsMap;

	// ���F
	float mStep;
	Enemy mEnemy;
	JumpMan mJumpMan;
	std::vector<Smoke> mSmokesVecL;
	std::vector<Smoke> mSmokesVecR;
	StarDustManager* mStarDustManager;

	void UpdateTest01(int no);
	void UpdateTest02(int no);
	void UpdateTest03(int no);
	void UpdateTest04(int no);
	void UpdateTest05(int no);
	void UpdateTest06(int no);

	void DrawTest01(int no);
	void DrawTest02(int no);
	void DrawTest03(int no);
	void DrawTest04(int no);
	void DrawTest05(int no);
	void DrawTest06(int no);

	void DrawTitle(int no, const char* title);
	void DrawTestGround(int no, int meshSize);

	void DrawData(int no, int imgHandle);

	Vector2 GetDrawAnsPos(int no, int lineY);
	void DrawAnsString(int no, int lineY, const char* fmt, int value);
	void DrawAnsString(int no, int lineY, const char* fmt, int* value);
	void DrawAnsString(int no, int lineY, const char* fmt, const char* value);

};

