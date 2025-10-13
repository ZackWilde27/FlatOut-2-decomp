#pragma once
#include <windows.h>
#include "BasicTypes.h"

class ScriptHost
{
public:
	void** vftable_0x0;
	//BYTE pad_0x4[4];
	LuaStateStruct2* stateStruct_0x8;

	ScriptHost* Destructor(byte bFree);
	ScriptHost* ConstructorThenDestructor(byte bFree);
};