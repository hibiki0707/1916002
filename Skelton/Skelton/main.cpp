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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	SetWindowText(L"1916002_荒木響稀");
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	Rect rcA = { 200,200,50,50 };
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
#if defined(_DEBUG) && defined(_CONSOLE)
		DrawBox(rcA.Left(), rcA.Top(), rcA.Right(), rcA.Bottom(), 0xffffff, true);
		DrawFormatString(10, 10, 0xffffaa, L"x=%d,y=%d", (int)rcA.center.x, (int)rcA.center.y);
		
		int srcX = 51 * (frame / 10);
		int srcY = 0;
		//DrawRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50, 49,36,3.0f,0.0f,graphH, true);
#ifdef DEBUG
#elif defined(CONSOLE) 
#else
#endif
		
		DrawRotaGraph(rcA.Right() + 50, rcA.Bottom() + 50, 3.0f, 0.0f, graphH[frame/10], true);
		std::ostringstream oss;
		
		oss << L"x=" << rcA.center.x << L",y=" << rcA.center.y << std::endl;
		OutputDebugStringA(oss.str().c_str());
#endif
		ScreenFlip();
		frame = (frame + 1) % 60;
	}

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
	singleton2.Out();
	auto& singleton3 = Singleton::Instance();
	Singleton& singleton4 = singleton3;
	singleton3.Out();
	singleton4.Out();

	DxLib_End();
	return 0;
}