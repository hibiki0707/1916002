#include <DxLib.h>
#include "Debug.h"

int test = 10;

void Debug::Output(const char* str){
	OutputDebugStringA(str);
	test++;
}
