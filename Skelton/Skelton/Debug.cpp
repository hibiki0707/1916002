#include <DxLib.h>
#include "Singleton.h"
#include "Debug.h"

int test = 0;

void Debug::Output(const char* str){
	
	OutputDebugStringA(str);
	test++;
}
