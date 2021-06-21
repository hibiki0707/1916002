#include <DxLib.h>
#include <cassert>
#include <string>
#include <sstream>
#include <iomanip>
#include "Singleton.h"
#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Debug.h"
#include "Common/Geometry.h"

// ベクトル構造体
struct Vector2 {
	float x, y;
};

// 座標として使えるように
using Position2 = Vector2;

// 矩形構造体
struct Rect
{
	Position2 center;
	float w, h;

	float Left() const {
		return center.x - w;
	}
	float Right() const {
		return center.x + w;
	}
	float Top() const {
		return center.y - h;
	}
	float Bottom() const {
		return center.y + h;
	}

	float Width() const {
		return w * 2.0f;
	}
	float Height() const {
		return h * 2.0f;
	}
};

Position2 GetCurrentMousePosition2() {
	int mx, my;
	GetMousePoint(&mx, &my);
	return{ static_cast<float>(mx),static_cast<float>(my) };
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetWindowText(L"1916002_荒木響稀");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	Rect rcA = { { 200,200},50,50 };
	char keystate[256];

	//auto graphH = LoadGraph(L"");
	int graphH[6] = {};
	//wchar_t path[100];
	for (int i = 0; i < 6; ++i) {
		std::wostringstream pathOss;
		pathOss << L"";
		pathOss << std::setw(2) << std::setfill(L'0');
		pathOss << i << L" ";
		//wsprintf(path,L"01" , i);
		//graphH[i] = DxLib::LoadGraph(path);
		graphH[i] = DxLib::LoadGraph(pathOss.str().c_str());
		//assert(graphH[i] != -1);
	}

	unsigned int frame = 0;

	int lastMouseInput = GetMouseInput();
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		DrawString(100, 100, L"Hello World", 0xffffff);

		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_LEFT]) {
			rcA.center.x -= speed;
		}
		if (keystate[KEY_INPUT_RIGHT]) {
			rcA.center.x += speed;
		}
		if (keystate[KEY_INPUT_UP]) {
			rcA.center.y -= speed;
		}
		if (keystate[KEY_INPUT_DOWN]) {
			rcA.center.y += speed;
		}

		DrawBox(rcA.Left(), rcA.Top(), rcA.Right(), rcA.Bottom(), 0xffffff, true);
		DrawFormatString(10, 10, 0xffffaa, L"x=%d,y=%d", (int)rcA.center.x, (int)rcA.center.y);

		int srcX = 51 * (frame / 10);
		int srcY = 0;
		//DrawRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50, 49,36,3.0f,0.0f,graphH, true);

		int mx, my;
		GetMousePoint(&mx, &my);

		auto currentMouseInput = GetMouseInput();
		if ((currentMouseInput & MOUSE_INPUT_LEFT) &&
			!(currentMouseInput & MOUSE_INPUT_LEFT)) {
		}
		lastMouseInput = currentMouseInput;

		Vector2 dir = { static_cast<float>(mx) - rcA.center.x,
		static_cast<float>(my) - rcA.center.y };

		float angle = atan2(dir.y, dir.x);

		//constexpr size_t block_size = 32;
		//const auto count = 720 / block_size;
		//int x = 0;
		//int y = 240;
		//for (int i = 1; i < count; ++i) {
		//	auto Nextx = block_size * i;
		//	auto Nexty = 240 + 100 * sinf(0.5f * (float)Nextx * DX_PI_F / 180.0f);
		//	// 地面表示
		//	DrawLineAA(x, y,	// 始点
		//		Nextx, Nexty,		// 終点
		//		0xffffff, 5.0f);
		//	x = Nextx;
		//	y = Nexty;
		//}
		

		/*int cx = 32;
		int gw, gh;
		GetGraphSize(graphH[frame / 10], &gw, &gh);
		if (flipFlg) {
			cx = gw - cx;
		}*/

		DrawRotaGraph2(rcA.center.x, rcA.center.y,
			15,35,
			5.0f, 0.0f, graphH[frame/10], true);
		DrawCircleAA(rcA.center.x, rcA.center.y, 5, 16, 0xff4444);
		std::ostringstream oss;
		
		oss << L"x=" << rcA.center.x << L",y=" << rcA.center.y << std::endl;
		OutputDebugStringA(oss.str().c_str());
		ScreenFlip();
		frame = (frame + 1) % 60;
	}
	++test;
	//++test2;
	char outstr[16];
	sprintf_s(outstr, "test=%d", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d", test);
	OutputDebugStringA(outstr);
	Debug::Output("Main Loop is end\n");
	sprintf_s(outstr, "test=%d", test);
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
	/*auto& singleton3 = Singleton::Instance();
	Singleton& singleton4 = singleton3;
	singleton3.Out();
	singleton4.Out();*/

	DxLib_End();
	return 0;
}