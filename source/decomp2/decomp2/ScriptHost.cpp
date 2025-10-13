#include "ScriptHost.h"
#include "Lua.h"

ScriptHost* ScriptHost::Destructor(byte bFree)
{
	//this->vftable_0x0 = JMPTABLE_ScriptHost_0067fe4;
	if (bFree)
		delete this;

	return this;
}

ScriptHost* ScriptHost::ConstructorThenDestructor(byte bFree)
{
	//this->vftable_0x0 = JMPTABLE_ScriptHost_0067fe4;

	LuaStateStruct2* lss2 = this->stateStruct_0x8;
	if (lss2 != NULL)
	{
		if (lss2->unkn_0x8 && lss2->L_0x4)
			lua_close(lss2->L_0x4);

		free(lss2);
		this->stateStruct_0x8 = NULL;
	}

	//this->vftable_0x0 = JMPTABLE_ScriptHost_00677fe0;
	if (bFree & 1)
		delete this;

	return this;
}