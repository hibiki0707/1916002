#include<DxLib.h>
#include<cassert>
#include<string>
#include<sstream>
#include<iomanip>
#include"Singleton.h"
#include"Debug.h"
#include"Game.h"
#include"Scene.h"
#include"Player.h"
#include"Enemy.h"
#include"Common/Geometry.h"

// ��`�\����
struct Rect{
	Position2 centor;
	float w, h;	// w/h���ꂼ�ꕝ�A�����̔���

	float Left()const {
		return centor.x - w;
	}
	float Right()const {
		return centor.x + w;
	}
	float Top()const {
		return centor.y - h;
	}
	float Bottom()const {
		return centor.y + h;
	}
	
	float Width()const {
		return w * 2.0f;
	}
	float Height()const {
		return h * 2.0f;
	}
};

Position2 GetCurrentMousePosition2() {
	int mx, my;
	GetMousePoint(&mx, &my);
	return { static_cast<float>(mx),
		static_cast<float>(my) };
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetWindowText(L"1916002_�r�؋��H");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int groundH = LoadGraph(L"img/ground.png");
	assert(groundH >= 0);

	int assetsH = LoadGraph(L"img/ground2.png");
	assert(assetsH >= 0);

	Rect rcA = { {200,200},50,50 };
	char keystate[256];

	//auto graphH=DxLib::LoadGraph(L"");
	int graphH[6] = {};
	//wchar_t path[100];

	for (int i = 0; i < 6; ++i) {
		std::wostringstream pathOss;
		pathOss << L"";
		pathOss << std::setw(2) << std::setfill(L'0');
		pathOss << i << L".png";
		//wsprintf(path, L"png", i);
		//graphH[i] = DxLib::LoadGraph(path);
		graphH[i] = DxLib::LoadGraph(pathOss.str().c_str());
		//*assert(graphH[i] != -1);
	}

	unsigned int frame = 0;

	int lastMouseInput=GetMouseInput();
	bool flipFlg = false;
	int freameForAngle = 0;
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		DrawString(100, 100, L"Hello World", 0xffffff);

		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.centor.x -= speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.centor.x += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			rcA.centor.y -= speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.centor.y += speed;
		}
		 
		constexpr size_t block_size = 32;
		const auto count = 720 / block_size;
		float theta = (float)(freameForAngle)*DX_PI_F / 180.0f;
		int x = 0;
		int y = 240; //+ 100 * sinf(theta);
		Position2 lastPos(x, y);
		Position2 p0(x, y);
		// �ߋ��P�ߋ��Q�B�ߋ��Q�̕������ߋ��B�`��Ώۂ͉ߋ��P
		Vector2 last90DeltaVectors[2] = { {0.0f,0.0f },{0.0f,0.0f} };
		
		for (int i = 1; i < count; ++i) {
			theta += 0.1f;
			/*auto nextX = block_size * i;
			auto nextY = 140 + 100 * sinf((float)(0.5*nextX+freameForAngle) * DX_PI_F / 180.0f);*/
			
			//DrawModiGraph(
			//	x, y,	// ����
			//	nextX, nextY,	// �E��
			//	nextX, nextY+block_size,	// �E��
			//	x, y+block_size,	// ����
			//	groundH,
			//	true
			//);
			//
			////constexpr int offstY = 100;
			//DrawModiGraph(
			//	x, y+100,	// ����
			//	nextX, nextY+100,	// �E��
			//	nextX, nextY + block_size+100,	// �E��
			//	x, y + block_size+100,	// ����
			//	assetsH,
			//	true
			//);
			////DrawRectModiGraph(
			////	x, y + 100,	// ����
			////	nextX, nextY + 100,	// �E��
			////	nextX, nextY + block_size + 100,	// �E��
			////	x, y + block_size + 100,	// ����
			////	48,0,	// ���摜�̍���
			////	16,16,	// ���摜��؂蔲�����A����
			////	assetsH,
			////	true
			////);

			//// 4�ӂ����C���ŕ\��
			//// ���
			//DrawLineAA(
			//	x, y,	// ����
			//	nextX, nextY,	// �E��
			//	0xffffff, 3.0f
			//);
			//// �E��
			//DrawLineAA(
			//	nextX, nextY,	// ����
			//	nextX, nextY+block_size,	// �E��
			//	0xffffff, 3.0f
			//);
			//// ����
			//DrawLineAA(
			//	nextX, nextY+block_size,	// ����
			//	x, y+block_size,	// �E��
			//	0xffffff, 3.0f
			//);
			//// ����
			//DrawLineAA(
			//	x, y+block_size,	// ����
			//	x, y,	// �E��
			//	0xffffff, 3.0f
			//);
			
			/*x = nextX;
			y = nextY;*/

			auto p1 = p0;
			auto deltaVec = Vector2(block_size, 40.0f *
				sinf(0.5f * (float)(freameForAngle + block_size * i) * DX_PI_F / 180.0f)
			);
			deltaVec = deltaVec.Normalized() * block_size;
			p1=p0+deltaVec;
			auto delta90Vec = deltaVec.Rotated90();

			auto middleVecR = delta90Vec;
			if (!(last90DeltaVectors[0] == Vector2(0.0f, 0.0f))) {
				middleVecR = (delta90Vec + last90DeltaVectors[0]).Normalized()*block_size;
			}
			
			auto middleVecL = delta90Vec;
			if (!(last90DeltaVectors[1] == Vector2(0.0f, 0.0f))) {
				middleVecL = (last90DeltaVectors[0] + last90DeltaVectors[1]).Normalized() * block_size;
			}
			last90DeltaVectors[1] = last90DeltaVectors[0];
			last90DeltaVectors[0] = deltaVec.Rotated90();

			// �n�ʂ̕\��
			// ���
			DrawLineAA(p0.x, p0.y,	// �n�_
				p1.x, p1.y,		// �I�_
				0xffffff, 5.0f);
			DrawCircle(p0.x, p0.y, 5, 0xffaaaa);

			auto LightPos = p0 + middleVecL;
			/*auto MiddlePos = LightPos;
			if (lastDeltaVec90 == Vector2(0.0f, 0.0f)) {
				auto halfVec = deltaVec.Rotated90() + lastDeltaVec90;

				MiddlePos = p0 + halfVec.Normalized() * block_size;
			}*/
			//lastDeltaVec90 = deltaVec.Rotated90();
			auto RightPos = p1 + middleVecR;

			DrawLineAA(p0.x, p0.y,	// �n�_
				p0.x, p0.y+block_size,		// �I�_
				0xffffff, 5.0f);

			auto leftPos = p0 + middleVecL;

			auto rightPos = p1 + middleVecR;
			
			//auto middlePos = p0 + middleVecR;
			//DrawLineAA(p0.x, p0.y,	// �n�_
			//	middlePos.x, middlePos.y,		// �I�_
			//	0xff8888, 4.0f);

			//DrawRectModiGraph(
			//	p0.x,p0.y,	// ����
			//	p1.x,p1.y,	// �E��
			//	rightPos.x,rightPos.y,	// �E��
			//	leftPos.x,leftPos.y,	// ����
			//	48,0,
			//	16,16,
			//	groundH,
			//	true
			//);

			// �E��
			DrawLineAA(p1.x, p1.y,	// �n�_
				RightPos.x, RightPos.y,		// �I�_
				0x888ff, 3.0f);

			// ����
			DrawLineAA(p0.x, p0.y,	// �n�_
				LightPos.x, LightPos.y,		// �I�_
				0xff8888, 3.0f);

			// 
			//DrawLineAA(p0.x, p0.y,	// �n�_
			//	MiddlePos.x, MiddlePos.y,		// �I�_
			//	0x88ff88, 3.0f);

			DrawModiGraph(p0.x, p0.y,
				p1.x, p1.y,
				RightPos.x, RightPos.y,
				LightPos.x, LightPos.y,
				groundH,
				true);

			p0 = p1;

		}

		freameForAngle = (freameForAngle + 1) % 720;
		DrawBox(rcA.Left(), rcA.Top(),
			rcA.Right(), rcA.Bottom(), 0xffffff, true);
		DrawFormatString(10, 10, 0xffffaa, L"x=%d,y=%d", (int)rcA.centor.x, (int)rcA.centor.y);
		
		int srcX = 51 * (frame / 10);
		int srcY = 0;
		/*DrawRectRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50, 
			srcX,srcY,49,36,3.0f,0.0f,graphH, true);*/

		int mx, my;
		GetMousePoint(&mx, &my);

		auto currentMouseInput = GetMouseInput();
		if ((currentMouseInput & MOUSE_INPUT_LEFT) &&
			!(lastMouseInput & MOUSE_INPUT_LEFT)) {
			flipFlg = !flipFlg;
		}
		lastMouseInput = currentMouseInput;

		Vector2 dir = GetCurrentMousePosition2() - rcA.centor;
	
		float angle = atan2(dir.y, dir.x);

		int cx = 32;
		int gw, gh;
		GetGraphSize(graphH[frame/10],&gw, &gh);
		if (flipFlg) {
			cx = gw - cx;
		}
		
		DrawRotaGraph2(rcA.centor.x, rcA.centor.y,
			cx,35,
			5.0f, angle, graphH[frame/10], true,flipFlg);
		DrawCircleAA(rcA.centor.x, rcA.centor.y, 5, 16, 0xff4444);
		std::wostringstream oss;
		
		//wchar_t out[32];
		//wsprintf(out, L"x=%d,y=%d\n", (int)rcA.centor.x, (int)rcA.centor.y);
		oss << L"x=" << rcA.centor.x << L",y=" << rcA.centor.y << std::endl;
		OutputDebugString(oss.str().c_str());

		ScreenFlip();
		frame = (frame + 1) % 40;
	}

	char outstr[8];
	sprintf_s(outstr,"test=%d\n",test);
	Debug::Output("Main Loop is end");
	sprintf_s(outstr, "test=%d\n", test);
	Debug::Output("Main Loop is end");
	sprintf_s(outstr, "test=%d\n", test);
	Debug::Output("Main Loop is end");
	sprintf_s(outstr, "test=%d\n", test);
	OutputDebugStringA(outstr);

	Singleton& singleton = Singleton::Instance();
	singleton.Out();
	Singleton& singleton2 = Singleton::Instance();
	auto& singleton3 = singleton2;
	singleton2.Out();
	singleton2.Out();
	singleton2.Out();
	singleton2.Out();
	singleton2.Out();
	singleton3.Out();

	DxLib_End();
	return 0;
}