#include "DxLib.h"
#include "Utility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "GameCommon.h"
#include "Star.h"
#include "Sphere.h"
#include "Unit.h"
#include "StarDustManager.h"
#include "TestScene.h"

TestScene::TestScene(SceneManager* manager) : SceneBase(manager)
{
	mWidth = SCREEN_SIZE_X / SPLIT_X;
	mHeight = SCREEN_SIZE_Y / SPLIT_Y;
}

void TestScene::Init(void)
{

	mPage = 1;

	mImgBackGround = LoadGraph("Image/BackGround.png");

	// �u���b�N�摜�̓ǂݍ���
	LoadDivGraph(
		"Image/Blocks.png",
		IMG_NUM_ALL,
		IMG_NUM_X, IMG_NUM_Y,
		BLOCK_IMG_SIZE_X, BLOCK_IMG_SIZE_Y,
		&mImages[0],
		true);

	// �z��̏�����
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			mData[y][x] = 0;
		}
	}

	// �u���b�N�`��Ɏg�p����
	mImgBlockGreen	= mImages[0];
	mImgBlockBlue	= mImages[104];
	mImgPlanePurple = mImages[528];
	mImgPlaneRed	= mImages[425];
	mImgPlaneGreen	= mImages[8];
	mImgPlaneWhite	= mImages[739];

	// ���|�C���^�p�ϐ�
	mPower = 120;
	mSpeedPtr = &mSpeed;
	*mSpeedPtr = 881;
	mData[1][3] = 777;

	mStar = new Star();
	mStar->Init();
	mStar->SetSizeRate(0.5f);

	for (int i = 0; i < 3; i++)
	{
		mStarChildren[i] = new Star();
		mStarChildren[i]->Init();
		mStarChildren[i]->SetSizeRate(0.2f);
	}

	mSphere = new Sphere();
	mSphere->Init();

	mMoveStep = 0.0f;

	// �������p
	mUnitsVec.push_back(Unit(80, "��m", { 15, 15 }));
	mUnitsVec.push_back(Unit(20, "���@�g��", { 10, 10 }));
	mUnitsVec.push_back(Unit(50, "������", { 20, 20 }));
	mUnitsVec.push_back(Unit(10, "���E", { 50, 50 }));
	mUnitsVec.push_back(Unit(70, "�E��", { 5, 5 }));

	mUnitsMap.emplace(0, Unit(80, "��m", { 15, 15 }));
	mUnitsMap.emplace(1, Unit(20, "���@�g��", { 10, 10 }));
	mUnitsMap.emplace(2, Unit(50, "������", { 20, 20 }));
	mUnitsMap.emplace(3, Unit(10, "���E", { 50, 50 }));
	mUnitsMap.emplace(4, Unit(70, "�E��", { 5, 5 }));

	// ���F
	mStep = 0.0f;
	mEnemy.Init();
	mJumpMan.Init();
	int img = LoadGraph("Image/Smoke.png");

	int cx = SCREEN_SIZE_X / 4;
	int cy = SCREEN_SIZE_Y / 2;
	int max = 200;
	int r = 0;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 20; i++)
	{
		x = cx + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecL.push_back(Smoke(img, { x, y }));
	}
	for (int i = 0; i < 20; i++)
	{
		x = (cx * 3) + (max / 2) - GetRand(max);
		y = cy + (max / 2) - GetRand(max);
		mSmokesVecR.push_back(Smoke(img, { x, y }));
	}

	mStarDustManager = new StarDustManager(mSceneManager);
	mStarDustManager->Init();

}

void TestScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mStep = 0.0f;
		mMoveStep = 0.0f;
		mPage += 1;
		if (mPage > MAX_PAGES)
		{
			mPage = 1;
		}
		switch (mPage)
		{
		case 5:
			mStarDustManager->Create(
				{ SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2 }, 2.0f, 25);
			break;
		}
	}

	switch (mPage)
	{
	case 1:
		// ���K�@
		UpdateTest01(1);
		break;
	case 2:
		// ���K�A
		UpdateTest02(1);
		break;
	case 3:
		// ���K�B
		UpdateTest03(1);
		break;
	case 4:
		// ���K�C
		UpdateTest04(1);
		break;
	case 5:
		// ���K�D
		UpdateTest05(1);
		break;
	case 6:
		// ���K�E
		UpdateTest06(1);
		break;
	default:
		break;
	}

}

void TestScene::Draw(void)
{

	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	// �w�i�̕`��
	DrawBackGround();

	switch (mPage)
	{
	case 1:
		// ���K�@
		DrawTest01(1);
		break;
	case 2:
		// ���K�A
		DrawTest02(1);
		break;
	case 3:
		// ���K�B
		DrawTest03(1);
		break;
	case 4:
		// ���K�C
		DrawTest04(1);
		break;
	case 5:
		// ���K�D
		DrawTest05(1);
		break;
	case 6:
		// ���K�E
		DrawTest06(1);
		break;
	case 7:
		break;
	default:
		break;
	}

	// �^�C�g���̕\��
	DrawFormatString(
		0, 0,
		0x000000,
		"�F�̊��p");

}

void TestScene::DrawBackGround(void)
{

	// ��
	//DrawBox(
	//	0, 0, 
	//	SCREEN_SIZE_X, SCREEN_SIZE_Y, 
	//	0xFFFFFF, true
	//);
	DrawGraph(0, 0, mImgBackGround, false);

	for (int x = 0; x < SPLIT_X; x++)
	{
		for (int y = 0; y < SPLIT_Y; y++)
		{

			DrawBox(
				DRAW_AREA_X + (x * mWidth), DRAW_AREA_Y + (y * mHeight),
				DRAW_AREA_X + ((x + 1) * mWidth), DRAW_AREA_Y + ((y + 1) * mHeight),
				0x000000, false
			);

		}
	}

}

void TestScene::Release(void)
{

	// �摜�̉��
	for (int i = 0; i < (IMG_NUM_X * IMG_NUM_Y); i++)
	{
		DeleteGraph(mImages[i]);
	}

	mStar->Release();
	delete mStar;

}

int TestScene::GetPage(void)
{
	return mPage;
}

void TestScene::DrawTest01(int no)
{

	DrawTitle(no, "���K�@���������`���A�E�ɕ`�悷��ɘA��āA���X�ɓ��������܂��傤�B");
	DrawAnsString(no, 0, "%s", "�@�@�@Hint : SetDrawBlendMode��DX_BLENDMODE_ALPHA���g�p");

	int startY = 200;
	int boxSize = 60;
	int num = 15;

	for (int i = 1; i < (num + 1); i++)
	{

		int alpha = 255 - (255 / num * i);

		// ��������R�[�f�B���O���Ă�����
		//------------------------------------------
		// �`���Ԃ��쐬
		int img01 = MakeScreen(boxSize, boxSize, false);
		// �`���Ԃ��쐬
		int img02 = MakeScreen(boxSize, boxSize, false);
		// �������̇@�@�F�̏�Z
		int imgMix01 = MakeScreen(boxSize, boxSize, false);
		SetDrawScreen(imgMix01);
		DrawGraph(0, 0, img01, true);

		// DxLib�̐F�̏�Z
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawGraph(0, 0, img02, true);

		// �u�����h���[�h���I�t
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//------------------------------------------

		int x = (boxSize * i);
		DrawBox(x, startY, x + boxSize, startY + boxSize, 0x000000, true);

	}
}

void TestScene::DrawTest02(int no)
{

	DrawTitle(no, "���K�A�G�L�����N�^�[���A����(�R�b)���i�ނɘA��ď��X�ɓ��������܂��傤�B");
	DrawAnsString(no, 0, "%s", "�@�@�@Hint : SetDrawBlendMode��DX_BLENDMODE_ALPHA���g�p");

	float sec = 3.0f;

	// �f���^�^�C��
	mStep += mSceneManager->GetDeltaTime();

	float t = mStep / sec;
	
	// ��������R�[�f�B���O���Ă�����
	//------------------------------------------
	sec += 3.0f;
		// DxLib�̐F�̏�Z
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//------------------------------------------

	// �G�L�����N�^�[�̕`��
	mEnemy.Draw();

	// �u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TestScene::DrawTest03(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "���K�B����W�����v�̃C���[�W�ŁA�c���𓧖��������Ă݂悤�B");
	DrawAnsString(no, 0, "%s", "�@�@�@Hint : SetDrawBlendMode��DX_BLENDMODE_ALPHA���g�p");
	DrawAnsString(no, 1, "%s", "�@�@�@��JumpMan�N���X��DrawJump�֐����ɋL�q���Ă��������B");
	
	// �L�����N�^�[
	mJumpMan.Draw();

	//mJumpMan.DrawJump();

	// DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	// �u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TestScene::DrawTest04(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "���K�C�E���̉_�����A�F�̉��Z�������g�p���ė��_�̂悤�ɖ��邭���Ă݂悤�B");
	DrawAnsString(no, 0, "%s", "�@�@�@Hint : SetDrawBlendMode��DX_BLENDMODE_ADD���g�p");

	int size;

	// ��������R�[�f�B���O���Ă�����
	//------------------------------------------
	// ����
	size = mSmokesVecL.size();
	for (int i = 0; i < size; i++)
	{
		mSmokesVecL[i].Draw();
	}

	// �E��
	size = mSmokesVecR.size();
	for (int i = 0; i < size; i++)
	{
		mSmokesVecR[i].Draw();

		// �`���Ԃ��쐬
		int img01 = MakeScreen(size, size, false);
		// �`���Ԃ��쐬
		int img02 = MakeScreen(size, size, false);

		int imgMix03 = MakeScreen(size, size, false);
		SetDrawScreen(imgMix03);
		DrawGraph(0, 0, img01, true);

		// DxLib�̐F�̏�Z
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawGraph(0, 0, img02, true);

		// �u�����h���[�h���I�t
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//------------------------------------------
	
}

void TestScene::DrawTest05(int no)
{

	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0x000000, true);
	DrawBox(0, 0, SCREEN_SIZE_X, 100, 0xffffff, true);

	DrawTitle(no, "���K�D�~�̒��ɓ����������݂̂𖾂邭���Ă݂悤�B");
	DrawAnsString(no, 0, "%s", "�@�@�@Hint : SetDrawBlendMode��DX_BLENDMODE_ADD���g�p");
	DrawAnsString(no, 1, "%s", "�@�@�@��StarDustManager�N���X��Draw�֐����ɋL�q���Ă��������B");

	// �~
	mSphere->SetPos({ 350, 300 });
	mSphere->SetSize(100);
	mSphere->SetColor(0x696969);
	mSphere->Draw();

	// ��������R�[�f�B���O���Ă�����
	//------------------------------------------
	mStarDustManager->Draw(mSphere);
	//------------------------------------------

	// DxLib�̐F�̏�Z
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// �u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void TestScene::DrawTest06(int no)
{

	DrawTitle(no, "���K�E�X�|�b�g���C�g�̂悤�ȃC���[�W�ŁA");
	DrawAnsString(no, 0, "%s", "�@�@�@�N���b�N�����ӏ��𓧉߂ŉ����ł���悤�ɂ��܂��傤�B");

	// �V�����`��̈�����A�`��Ώۂɂ���
	int startY = 80;
	int screen = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y - startY, true);
	SetDrawScreen(screen);
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y - startY, 0x000000, true);

	// �~
	mSphere->SetSize(100);
	mSphere->SetColor(GetColor(255, 0, 255));
	
	// ���N���b�N
	if (GetMouseInput() == MOUSE_INPUT_LEFT)
	{

		// �N���b�N���ꂽ���W
		int x, y;
		GetMousePoint(&x, &y);

		mSphere->SetPos({ x, y });

	}

	// ��������R�[�f�B���O���Ă�����
	//------------------------------------------


	//DX_BLENDMODE_NOBLEND      �`���̐F =  Src * 1.0 + Dest * 0.0
	//DX_BLENDMODE_ALPHA        �`���̐F =  Src * SrcAlpha + Dest * InvSrcAlpha
	//DX_BLENDMODE_ADD          �`���̐F =  Src * SrcAlpha + Dest * 1.0
	//DX_BLENDMODE_SUB          �`���̐F = -Src * SrcAlpha + Dest * 1.0
	//DX_BLENDMODE_MUL          �`���̐F =  Src * 0.0 + Dest * Src
	//DX_BLENDMODE_DESTCOLOR    �`���̐F =  Src * 0.0 + Dest * 1.0
	//DX_BLENDMODE_INVDESTCOLOR �`���̐F =  Src * InvDestColor + Dest * 0.0
	//
	//Src�@�@�@�@�@: �`�挳�̂q�f�a�l(0�`255 �� 0.0�`1.0 �ƍl����)
	//SrcAlpha�@�@ : �`�挳�̃A���t�@�l(0�`255 �� 0.0�`1.0 �ƍl����)
	//InvSrcAlpha�@: �`�挳�̃A���t�@�l�𔽓](1.0 - SrcAlpha)��������
	//Dest�@�@�@�@ : �`���̂q�f�a�l(0�`255 �� 0.0�`1.0 �ƍl����)
	//InvDestColor : �`���̂q�f�a�l�𔽓](1.0 - Dest)��������(RGB�e�v�f�P��)
	//------------------------------------------

	// �~��`��
	mSphere->Draw();

	// �u�����h���[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �`��Ώۂ����ɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);

	// �~�`�ɂ��蔲����Ă���(�͂�)�摜��`��
	DrawGraph(0, startY, screen, true);

	// �`��̈���
	DeleteGraph(screen);

}


void TestScene::DrawTitle(int no, const char* title)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;
	
	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	DrawFormatString(x, y, 0x000000, title);

}

void TestScene::DrawTestGround(int no, int meshSize)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x1 = DRAW_AREA_X + (mWidth * tmpX) + GROUND_MARGIN;
	int y1 = DRAW_AREA_Y + (mHeight * tmpY) + GROUND_MARGIN;
	int w = MAP_SIZE_X * BLOCK_IMG_SIZE_X;
	int h = MAP_SIZE_Y * BLOCK_IMG_SIZE_Y;
	int x2 = x1 + w;
	int y2 = y1 + h;
	DrawBox(
		x1, y1,
		x2, y2,
		0x696969, true);

	if (meshSize == 0)
	{
		return;
	}

	int cntY = h / meshSize;
	for (int y = 1; y < cntY; y++)
	{
		DrawLine(
			x1, y1 + (y * meshSize), 
			x2, y1 + (y * meshSize), 0x66cdaa, true);
	}

	int cntX = w / meshSize;
	for (int x = 1; x < cntX; x++)
	{
		DrawLine(
			x1 + (x * meshSize), y1,
			x1 + (x * meshSize), y2, 0x66cdaa, true);
	}

}

void TestScene::DrawData(int no, int imgHandle)
{

	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int marginX = (mWidth * tmpX) + GROUND_MARGIN;
	int marginY = (mHeight * tmpY) + GROUND_MARGIN;
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			if (mData[y][x] == 1)
			{
				DrawGraph(
					DRAW_AREA_X + marginX + (x * BLOCK_IMG_SIZE_X),
					DRAW_AREA_Y + marginY + (y * BLOCK_IMG_SIZE_Y),
					imgHandle, true);
			}
		}
	}

}

Vector2 TestScene::GetDrawAnsPos(int no, int lineY)
{
	int tmpX = (no - 1) % SPLIT_X;
	int tmpY = (no - 1) / SPLIT_X;

	int x = DRAW_AREA_X + (mWidth * tmpX) + TITLE_MARGIN;
	int y = DRAW_AREA_Y + (mHeight * tmpY) + TITLE_MARGIN;

	y += TestScene::CHR_HEIGHT;
	y += (lineY * TestScene::CHR_HEIGHT);

	return Vector2(x, y);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, int* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::DrawAnsString(int no, int lineY, const char* fmt, const char* value)
{
	Vector2 v = GetDrawAnsPos(no, lineY);
	DrawFormatString(v.x, v.y, 0x000000, fmt, value);
}

void TestScene::UpdateTest01(int no)
{
}

void TestScene::UpdateTest02(int no)
{
}

void TestScene::UpdateTest03(int no)
{
	mJumpMan.Update();
}

void TestScene::UpdateTest04(int no)
{
}

void TestScene::UpdateTest05(int no)
{
	mStarDustManager->Update();
}

void TestScene::UpdateTest06(int no)
{
}
