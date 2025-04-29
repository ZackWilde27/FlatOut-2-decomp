/////////////////////////////////////////////////
// 
// SCRAP Engine
// 
/////////////////////////////////////////////////

// My on-going recreation of ROMU based on decompiling FlatOut 2

// ROMU is always spelled with capitals, so I assumed it was an acronym, but it turns out it's the finnish word for scrap metal.
// SCRAP it is.
#include "SCRAP.h"

// It's extremely similar to 1 and UC's ROMU but there are enough changes, especially in the locations of things that it would make more sense to re-write it to match each game.

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// I checked, and they forgot to update the string, unless they considered the changes to be that small.
// SCRAP v0.28b
const char* verString_00698b4c = "Version 0.28 build 2004.09.20";


/////////////////////////////////////////////////
//
// Strings
// 
/////////////////////////////////////////////////

// It used to be called neverReferencedAgain, because this next function checks if it's 0,
// and that's the only time it's ever referenced.
// Cheat Engine says this value is initialized to 0, so it always overrides.
int g_slashOverride = 0;

// NormalizeFilePath: (Formerly SlashConvertString)
//
// This function copies the in_string to the out_string, returning the length of the in_string.
// It'll also convert uppercase to lowercase.

// If mode is 0:
//
// Starts at the location of the out_string pointer
// Convert backslashes to slashes
// By the end, in_string and out_string will point at the character after the NULL

// If mode is not 0:
//
// Starts at the location after the first NULL in the out_string
// If mode is 3, or g_slashOverride is 0, it'll convert slashes to backslashes and vise-versa
// By the end, in_string will point at the character after the ending NULL
int NormalizeFilePath(uchar* in_string, int mode, uchar* out_string)
{
	uchar* tempPtr;
	uchar currentChar;
	int lenOfData;
	uchar* pcVar2;

	if (mode == 0)
	{
		tempPtr = in_string;

		// Counts the length of the string.
		do
		{
			currentChar = *tempPtr;
			tempPtr = tempPtr + 1;
		} while (currentChar != NULL);

		lenOfData = (int)tempPtr - ((int)in_string + 1);

		if (lenOfData)
		{
			for (int x = lenOfData; x != 0; x--)
			{
				// Converts backslashes to forward slashes, and uppercase to lowercase
				currentChar = *in_string;
				in_string = in_string + 1;
				if (currentChar == '\\')
					currentChar = '/';
				else
				{
					if (isupper(currentChar))
					{
						// Convert to lowercase. I love how odd yet simple it is.
						currentChar += ' ';
					}
				}
				out_string = &currentChar;
				out_string = out_string + 1;
			}
			return lenOfData;
		}
	}
	else
	{
		// If mode is not 0, replace the first character of the out_string with NULL
		*out_string = NULL;
		tempPtr = out_string;
		// Steps through the output string until a NULL, and starts the copy process from there.
		do
		{
			pcVar2 = tempPtr;
			tempPtr = pcVar2 + 1;
		} while (*pcVar2 != NULL);

		currentChar = *in_string;

		while (currentChar != NULL)
		{
			in_string = in_string + 1;
			if (g_slashOverride == 0 || mode == 3)
			{
				if (currentChar == '/')
					currentChar = '\\';
				else if (currentChar == '\\')
					currentChar = '/';
			}

			// Converting to lowercase
			lenOfData = isupper(currentChar);
			if (lenOfData != 0)
				currentChar += ' ';

			*pcVar2 = currentChar;
			pcVar2 = pcVar2 + 1;
			currentChar = *in_string;
		}
		lenOfData = (int)pcVar2 - (int)out_string;
	}
	*pcVar2 = NULL;
	return lenOfData;
}

// Goes along the string until it reaches the end or finds a difference and returns the difference between the characters in integer value.
int String_Compare(char* string1, char* string2)
{
	char char1, char2;
	do
	{
		char1 = *string1;
		char2 = *string2;
		string1 += 1;
		string2 += 1;
		if (char1 == NULL) break;
	} while (char1 == char2);
	return char1 - char2;
}

// The same as String_Compare except safer.
// but if string2's length is less than maxLength, it'll produce an unintended result.
int String_Compare_s(char* string1, char* string2, int maxLength)
{
	char char1, char2;
	int iVar3 = 0;

	do
	{
		char1 = *string1;
		char2 = *string2;
		string1++;
		string2++;
		iVar3++;

		if (char1 == NULL || char1 != char2) break;

	} while (iVar3 < maxLength);

	return char1 - char2;
}

// Honestly not too sure about the why
// Same as Compare_s, it sweeps through until it finds a difference and then returns the difference in value between the characters.
char String_CompareEnd(char* out_string, char* in_string, int length)
{
	if (length > 0)
	{
		int difference = in_string - out_string;
		do
		{
			if (*out_string != out_string[difference])
				return *out_string - out_string[difference];

			out_string++;
			length--;
		} while (length > 0);
	}
	return NULL;
}

// So, all of the places that counted the string manually was Ghidra's fault
// It seems like strlen is an inline function where it just copy-pastes the code instead of a call/return.
int String_GetLength(const char* in_string)
{
	char* tempPtr = (char*)in_string;
	while (*tempPtr != NULL)
		tempPtr++;

	return tempPtr - in_string;
}

// Simple copy from one string to another.
// Both pointers will end up pointing at the end of the string, so it returns
// the original pointer to the out_string.
char* String_SimpleCopy(char* out_string, const char* in_string)
{
	char* original = out_string;
	char current;
	do
	{
		current = *in_string;
		*out_string = current;
		out_string++;
		in_string++;
	} while (current != NULL);
	return original;
}

// Just like SimpleCopy except has a length, makes it a bit safer too.
char* String_CopySubstring(char* out_string, char* in_string, int length)
{
	char* original = out_string;
	char current;
	do
	{
		if (!length)
			return original;

		current = *in_string;
		*out_string = current;
		out_string++;
		in_string++;
		length--;
	} while (current != NULL);
	return original;
}

// Appends the in_string to the end of the out_string.
// Finds the first NULL in the out_string and starts copying from there.
// It returns the starting pointer to the out_string, but my own experimenting tells me that the original isn't modified anyways, the function is given a copy of the pointer.
char* String_Append(char* out_string, const char* in_string)
{
	char* original = out_string;
	// Sweep through the first string.
	for (; *out_string != NULL; out_string++) {}

	char current;
	do
	{
		current = *in_string;
		*out_string = current;
		out_string++;
		in_string++;
	} while (current != NULL);
	return original;
}


// Same as String_Append except with a length
char* String_AppendSubstring(char* out_string, char* in_string, int length)
{
	char* original = out_string;
	if (length)
	{
		// Skips to the end of the string
		for (; out_string != NULL; out_string++) {}

		char current;
		do
		{
			current = *in_string;
			*out_string = current;
			if (current == NULL)
				return original;

			out_string++;
			in_string++;
		} while (--length);
		*out_string = NULL;
	}
	return original;
}

// It's the same as Microsoft's tolower() except 'A' - 'a' is precalculated, happens to be the space character.
char Char_ToLowercase(char theChar)
{
	if (theChar > 64 && theChar < 91)
		theChar += ' ';
	return theChar;
}

void AddStringToList(int index, const char* newString)
{
	if ((0x31 < index) && (index < 0xFF))
		StringList_00681888[index] = newString;
	return;
}

// Apparently these aren't strings, but they are treated like them.
// Sweeps through as if it's a string, but when it does the comparison it casts both of them to integer pointers, so it'll compare 4 characters each time.
bool String_CompareAsIntegers(int* ints1, int* ints2)
{
	bool equal = true;
	int iVar1 = 4;
	do
	{
		if (iVar1 == 0)
			return equal;

		iVar1--;
		equal = *ints1 == *ints2;
		ints1++;
		ints2++;
	} while (equal);
	return equal;
}

// StringToNum
// Converts the string into a float, unless it ends with an x or X character,
// then it will be treated as a hex string
// Returns whether or not the given string ended with a null.
bool StringToNum(char* stringFloat, float* outFloat)
{
	bool nullTerminated;
	char* EndPtr;

	*outFloat = (float)strtod(stringFloat, &EndPtr);

	if (EndPtr == stringFloat)
		nullTerminated = false;
	else
	{
		if (*EndPtr == 'x' || *EndPtr == 'X')
			*outFloat = (float)(ulonglong)strtoul(stringFloat, &EndPtr, 16);

		if (*EndPtr == NULL)
			nullTerminated = true;
		else
		{
			while (isspace(*EndPtr))
				EndPtr++;

			nullTerminated = *EndPtr == NULL;
		}
	}

	return nullTerminated;
}

BOOL StrStrIsh(char* string, char* stringToFind, char* param_3, int iterations)
{
	char firstLetter = *stringToFind;

	char* ptr = strstr(string, stringToFind);
	if (!ptr)
		return FALSE;

	char ch;
	char* tempPtr = stringToFind + 1;
	do
	{
		ch = *stringToFind;
		stringToFind++;
	} while (ch);

	int i = 0;
	if ((iterations - 1) > 0)
	{
		char* tempPtr2 = param_3;
		do
		{
			ch = tempPtr2[(int)(ptr + (int)(stringToFind + (-(int)param_3 - (int)tempPtr)))];
			if (ch == NULL || ch == firstLetter) break;
			
			i++;
			*tempPtr2 = ch;
			tempPtr2++;
		} while (i < (iterations - 1));
	}

	param_3[i] = NULL;
	return TRUE;
}

#define BYTE_STRING_LENGTH 32
// The buffer has a section at the start that is not changed by BytesToString,
// It's much larger than just a 0x would be, so maybe it's padded with zeros, like 0x0000000
char byteString[BYTE_STRING_LENGTH];

char* __fastcall BytesToString(BYTE* buffer)
{
	byteString[BYTE_STRING_LENGTH] = NULL;
	BYTE* startPtr = buffer + 1;
	BYTE* endPtr = (BYTE*)byteString + (BYTE_STRING_LENGTH - 2);

	BYTE b1;
	BYTE b2;

	int i = 4;
	do
	{
		b1 = startPtr[-1];
		endPtr[1] = "0123456789abcdef"[b1 & 0xF];
		endPtr[0] = "0123456789abcdef"[b1 >> 4];
		b2 = startPtr[0];
		endPtr[-1] = "0123456789abcdef"[b2 & 0xF];
		endPtr[-2] = "0123456789abcdef"[b2 >> 4];
		b1 = startPtr[1];
		endPtr[-3] = "0123456789abcdef"[b1 & 0xF];
		endPtr[-4] = "0123456789abcdef"[b1 >> 4];
		b2 = startPtr[2];
		endPtr[-5] = "0123456789abcdef"[b2 & 0xF];
		endPtr[-6] = "0123456789abcdef"[b2 >> 4];

		startPtr += 4;
		endPtr -= 8;

	} while (--i);
	return byteString;
}

int WString_GetLength(const wchar_t* in_wstring)
{
	wchar_t c;
	wchar_t* tempstring = (wchar_t*)in_wstring;

	do
	{
		c = *tempstring;
		tempstring += 2;
	} while (c != NULL);

	return ((tempstring - in_wstring) >> 1) - 1;
}

wchar_t* WString_SimpleCopy(wchar_t* Dst, wchar_t* Src)
{
	wchar_t* tempPtr = Dst;
	wchar_t current;

	do
	{
		current = *Src;
		*tempPtr = current;
		tempPtr += 2;
		Src += 2;
	} while (current != NULL);

	return Dst;
}

HGLOBAL GlobalAllocGPTR(SIZE_T dwBytes)
{
	return GlobalAlloc(GPTR, dwBytes);
}


/////////////////////////////////////////////////
//
// Debug
// 
/////////////////////////////////////////////////


void CreateErrorMessageAndDie(const char* message, ...)
{
	char temp[1024];
	char body[1024];

	// The list of arguments to put into the message is the rest of the CPU stack, meaning the inputs of the last-called function.
	va_list list;
	va_start(list, message);

	vsprintf(temp, message, list);
	sprintf(body, "%s", temp);
	MessageBoxA(NULL, (LPCSTR)body, "Fatal error", MB_ICONERROR);
	ExitProcess(0);
}

void CaptionlessTaskModalMessageBox(LPCSTR lpText)
{
	MessageBoxA(NULL, lpText, NULL, MB_TASKMODAL | MB_ICONWARNING);
}


void (*FUNC_006a2c28)();

// My guess is, this is where bugbear's bug-tearing debugger would take over.
void ExitWithCode25()
{
	if (FUNC_006a2c28 != NULL)
		(*FUNC_006a2c28)();

	// This function emits the runtime error message to stderr for console applications,
	// or displays the message in a message box for Windows applications.
	// In debug mode, you can choose to invoke the debugger before exiting.
	// - Documentation
	// It also needs an internal.h file, but I don't have it.
	//_amsg_exit(25);
}

void DoNothing()
{
	return;
}

// The normal jumptable
// In FO2 Ghidra did not find a name for it,
// but in FOUC it's apparently a LiteDb void function table.
// The oldest mention of LiteDb I can find is from 2014, and the oldest release I can find is from 2015.
// Was it just a false positive on Ghidra's part?
void (*LiteDb_vftable_0067b1c0[])() = {
	//FUN_00558390
	//AutoClass9::AddMappedTable,
	//FUN_005585e0
	DoNothing,
	//FUN_005585f0
};

// The no jumptable
void (*NOJMPTABLE_0067ad08[58])() = {};

// Instead of writing all that out I'll replace it with code that would do the same thing
// 56 of them are ExitWithCode25, and the last one is a duplicate of DoNotCallEver except without the error message
void CreateThatWeirdJumpTable()
{
	for (int i = 0; i < 57; i++)
		NOJMPTABLE_0067ad08[i] = ExitWithCode25;

	//NOJMPTABLE_0067ad08[57] = (void (*)())PropertyDb::Destructor;
}


PropertyDb* PropertyDb::Destructor(int bDestruct)
{
	this->vftable_0x0 = NOJMPTABLE_0067ad08;
	if (bDestruct & 1)
		delete this;
	
	return this;
}


// The "Must not be called - ever" error message can be triggered in fo2, fouc, and even ridge racer unbounded. The locations in memory are different for each game though.
// FO2: Change 0x0067ADFC to 0x00558350 and it should crash immediately in-game or when loading into the menus
// FOUC: Change 0x006F3DD0 to 0x005B2FB0 while the intro is playing and it'll crash on the title card
// RR: Change 0x00C8C428 to  0x006E2CE0 while the intro is playing and it'll crash before the title is shown.

// This function is under AutoClass8, it doesn't show up in Ghidra's Functions tree for some reason.
// I guess their method system requires it to have a destructor, but they didn't actually want that.
PropertyDb* PropertyDb::DoNotCallEver(int bFree)
{
	// Seems like a default value maybe.
	this->vftable_0x0 = LiteDb_vftable_0067b1c0;
	CreateErrorMessageAndDie("Must not be called - ever.");

	// If you bypassed the error message in FO2, this jump table would be replaced with one where every function except for one will exit with code 25
	// I checked, and bypassing the error message just silently crashes anyways
	this->vftable_0x0 = NOJMPTABLE_0067ad08;
	if (bFree & 1)
		delete this;

	return this;
}



/////////////////////////////////////////////////
// 
// Lua
//
/////////////////////////////////////////////////

// Thanks to Sewer56 for helping me get their disassembly opening (why did hexrays stop offering the 32-bit version of IDA?)

int DEBUGLOG(lua_State* L)
{
	return 0;
}

uchar UCHAR_00h_0069c911 = NULL;
CRITICAL_SECTION criticalSection_0069c8f4;

void* AllocateInCriticalSection(int size)
{
	if (UCHAR_00h_0069c911)
		EnterCriticalSection(&criticalSection_0069c8f4);

	void* ptr = malloc(size);//IsThatACustomMadeMalloc(size);

	if (UCHAR_00h_0069c911)
		LeaveCriticalSection(&criticalSection_0069c8f4);

	return ptr;
}

// It would make sense for this to be a realloc, but the new size isn't given
void* ReAllocateInCriticalSection(void* block)
{
	if (UCHAR_00h_0069c911)
		EnterCriticalSection(&criticalSection_0069c8f4);

	void* ptr = NULL;// IsThatACustomMadeRealloc(PTR_PTR_FUN_0069c8f0, block);

	if (UCHAR_00h_0069c911)
		LeaveCriticalSection(&criticalSection_0069c8f4);

	return ptr;
}

// The most basic allocator possible (to get an idea what bugbear's version is doing)
/*
void* basic_lua_allocator(void* ud, void* block, int osize, int nsize)
{
	if (!nsize)
	{
		free(block);
		return NULL;
	}

	// Note that realloc turns into a malloc if block is NULL, which is a requirement for the allocator.
	return realloc(block, nsize);
}
*/

void* bugbear_lua_allocator(void* ud, void* block, int osize, int nsize)
{
	void* newBlock;

	lua_State* L = *(lua_State**)ud;
	if (!nsize)
	{
		if (!block)
			return NULL;

		newBlock = NULL;
	}
	else
	{
		if (nsize > 0xFFFFFFFC)
		{
			luaG_runerror(L, "memory allocation error: block too big");
			return block;
		}

		if (!block)
			newBlock = AllocateInCriticalSection(nsize);
		else
			newBlock = ReAllocateInCriticalSection(block);

		if (!newBlock)
		{
			if (L)
				luaD_throw(L, 4);

			return NULL;
		}
	}

	return newBlock;
}

int __fastcall GetScriptParameterInt(LuaStateStruct* lss_EAX)
{
	int type = lua_type(lss_EAX->L_0x0, lss_EAX->index_0x4);
	if (type == LUA_TBOOLEAN)
		return lua_toboolean(lss_EAX->L_0x0, lss_EAX->index_0x4);

	lua_Number data = lua_tonumber(lss_EAX->L_0x0, lss_EAX->index_0x4);

	// Some intense bit manipulation is about to happen
	/*
	uint intForm = *(uint*)&data;
	type = intForm >> 23;
	type &= 0xFFU;
	type -= 127;

	// What
	return (((intForm | 0xFF800000) << 8) >> (0x1F - (uchar)type & 0x1F) ^ intForm >> 31) - intForm >> 31 & ~(type >> 31);
	*/

	// I did some testing to figure out what that does, and I'm still not sure
	// In the version I wrote above, I read the float as an integer with no conversion, since it looks like that in the assembly, but the ghidra code suggests there's a conversion.

	// As written above it works like this
	return data >= 1.0f && !isinf(data);

	// If I copy and paste the p-code directly from Ghidra it works like this
	return data >= 0.0f ? 0 : -1;

	// I don't think either of those are right, this function is treated like it returns a regular integer
	// I think it would make the most sense if it was doing this
	return (int)data;
}

BYTE* unmakemask(UINT mask, BYTE* out_result)
{
	bool bitSet = mask & 1;
	if (bitSet)
		out_result[0] = 99;

	uint i = (uint)bitSet;

	if (mask & 2)
	{
		out_result[i] = 0x72;
		i++;
	}
		
	if (mask & 4)
	{
		out_result[i++] = 0x6c;
		i++;
	}

	out_result[i] = 0;
	return out_result;
}

void __fastcall Lua_PadTableIfNeeded(int newLength_EAX, lua_State** unaff_EDI)
{
	int length = lua_gettop(unaff_EDI[1]);
	if (length < newLength_EAX)
	{
		length = newLength_EAX - length;
		do
			lua_pushnil(unaff_EDI[1]);
		while (--length);
	}
}

// Functions that are called from Lua

int Lua_KickPlayer(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);

	void* pUserData = lua_touserdata(L, 1);
	if (pUserData == NULL)
		luaL_typerror(L, 1, "SessionClass");

	// Function pointers have nothing on function pointers inside function pointers
	/*
	void (**vftable1)(void(***)()) = pUserData->vftable;

	// This one is not checked to see if it's null
	pUserData = lua_touserdata(L, 2);
	void (**vftable2)() = (void (**)())pUserData->vftable;

	undefined4 local_4 = pUserData->unkn_0x4;
	vftable1[12](&vftable2);
	*/
}

void StructThing(lua_State* self, astruct_169* tableStruct)
{
	tableStruct->end_0x0 = tableStruct + 3;
	tableStruct->unkn_0x4 = NULL;
	tableStruct->state_0x8 = self;
}

int JoinCurrentSession(lua_State* L)
{
	if (lua_type(L, 1) != LUA_TNIL)
		lua_touserdata(L, 1);

	return 0;
}

const char* STRING_008e8504;

int JoinSessionFromCommandLine(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	void* pUserData = lua_touserdata(L, 1);
	if (pUserData != NULL)
		luaL_typerror(L, 1, "SessionClass");

	// The 4th item in the vftable is a code** so it's either a struct with the first field being a jump table, or the jump table in the current struct contains pointers to pointers
	// (*(pUserData->vftable_0x0[4]))();
	return 0;
}

int len(lua_State* L)
{
	size_t length;
	luaL_checklstring(L, 1, &length);
	lua_pushinteger(L, length);
	return 0;
}

int GetNumWStringLines(lua_State* L)
{
	wchar_t* in_wstring = (wchar_t*)lua_tolstring(L, 1, NULL);

	int totalLines = 1;
	uint length = WString_GetLength(in_wstring);
	if (length)
	{
		// It was originally a do while but it's structured exactly like a for so why not
		for (int i = 0; i < length; i++)
		{
			if (in_wstring[i] == L'\n')
				totalLines++;
		}
	}

	lua_pushnumber(L, (lua_Number)totalLines);
	return 1;
}

int GetSaveFlowResult(lua_State* L)
{
	lua_pushnumber(L, (lua_Number)g_pGameSettings_008e8410->m_nSaveFlowResult_0x2c);
	return 1;
}

int GetSaveFlowState(lua_State* L)
{
	lua_pushnumber(L, (lua_Number)g_pGameSettings_008e8410->m_nSaveFlowState_0x434);
	return 1;
}

int GetSaveGameInfoValid(lua_State* L)
{
	lua_pushboolean(L, (uint)(bool)g_pGameSettings_008e8410->bSaveGameInfoValid_0x44);
	return 1;
}

int GetSaveStatus(lua_State* L)
{
	lua_pushnumber(L, (lua_Number)g_pGameSettings_008e8410->m_nSaveStatus_0x44c);
	return 1;
}

// So many functions did pretty much the exact same thing, so I made it a macro
#define luaboilerplate(index, type, name) luaL_checktype(L, index, LUA_TUSERDATA); \
															 type* data = (type*)luaL_checkudata(L, index, name); \
															 if (data == NULL) luaL_typerror(L, index, name)

// Nothing about this function makes sense.
static int EnoughMoney(lua_State* L)
{
	// Uses a different pointer to reference the PlayerProfile string, it also never changes so it may as well directly reference the constant.
	// That combined with the cup manager making no sense here makes me think they accidentally used the PlayerProfile string.
	luaboilerplate(1, PlayerProfile*, "PlayerProfile");

	// Points at a struct with the first item pointing at a player profile, or it's just a PlayerProfile**
	PlayerProfile* profile = *data;

	LuaStateStruct lss{ L, 2 };
	int requiredMoney = GetScriptParameterInt(&lss);

	lua_pushboolean(L, profile->m_nMoney_0xe58 >= requiredMoney);

	return 1;
}

int SetMoney(lua_State* L)
{
	luaboilerplate(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;

	LuaStateStruct lss{ L, 2 };
	int newMoney = GetScriptParameterInt(&lss);
	profile->m_nMoney_0xe58 = newMoney;

	return 0;
}

int __fastcall SubtractMoneyCarsForReal(int cost, PlayerProfile* in_EAX)
{
	int newBalance = in_EAX->m_nMoney_0xe58 - cost;
	// Some kind of moneySpent property?
	//in_EAX->uint_0xef8 += cost;
	in_EAX->m_nMoney_0xe58 = newBalance;

	uint local_24 = 0xBDF;
	//PostEvent_(cost, &local_24, 0);

	return newBalance;
}

int SubtractMoneyCars(lua_State* L)
{
	luaboilerplate(1, PlayerProfile*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	int cost = GetScriptParameterInt(&lss);
	int newBalance = SubtractMoneyCarsForReal(cost, *data);
	lua_pushnumber(L, (lua_Number)newBalance);

	return 1;
}

int __fastcall SubtractMoneyUpgradesForReal(uint cost, PlayerProfile* in_EAX)
{
	int newBalance = in_EAX->m_nMoney_0xe58 - cost;
	//in_EAX->uint_0xefc += cost;
	in_EAX->m_nMoney_0xe58 = newBalance;

	uint local_24 = 0xBDF;
	//PostEvent_(cost, &local_24, 0);

	return newBalance;
}

int SubtractMoneyUpgrades(lua_State* L)
{
	luaboilerplate(1, PlayerProfile*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	int cost = GetScriptParameterInt(&lss);
	int newBalance = SubtractMoneyUpgradesForReal(cost, *data);
	lua_pushnumber(L, (lua_Number)newBalance);

	return 1;
}

int getplatform(lua_State* L)
{
	lua_pushlstring(L, "PC", 2);
	return 1;
}

int GetTitle(lua_State* L)
{
	void* data = lua_touserdata(L, 1);

}

int GetTotalRagdollFlyDistance(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PlayerProfile** data = (PlayerProfile**)luaL_checkudata(L, 1, "PlayerProfile");
	if (!data)
		luaL_typerror(L, 1, "PlayerProfile");

	lua_pushnumber(L, (lua_Number)(int)(long long)roundf((*data)->m_fTotalRagdollFlyDistance_0xf1c));
	return 1;
}

int StartKickVote(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	void* pUserData = lua_touserdata(L, 1);
	if (pUserData == NULL)
		luaL_typerror(L, 1, "SessionClass");

	/*
	int* piVar1 = *(int**)(pUserData->vftable);
	pUserData = lua_touserdata(L, 2);
	int local_8 = *(int*)pUserData->vftable;

	//FUN_004f0f20(piVar1, &local_8);
	*/

	return 0;
}

int deg(lua_State* L)
{
	float rad = luaL_checknumber(L, 1);
	lua_pushnumber(L, rad * 57.29578f);

	return 1;
}

// FormatMemoryCard will call this function, but given the lack of formatting going on I'd say that's unintentional.
int FormatMemoryCardForRealMaybe(undefined4* param_1)
{
	return param_1[1];
}

sGameSettings* g_pGameSettings_008e8410;

// Left-over from the PS2 version, it still tries to call the formatting function, but it's been removed.
// If called it will mess up the CPU stack, since the current function will pop a parameter, but this code doesn't push one.
int FormatMemoryCard(lua_State* L)
{
	sGameSettings* pSettings = g_pGameSettings_008e8410;

	((void (*)())FormatMemoryCardForRealMaybe)();
	//pSettings->field1088_0x44c = 7;
	return 0;
}

int SetGlobalFontScale(lua_State* L)
{
	g_GlobalFontScale_006993f8 = luaL_checknumber(L, 1);
	return 0;
}

const char* UserDataName_008e8488;

int GetNumUpgrades(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);

	void* udata = luaL_checkudata(L, 1, "Garage");
	if (udata == NULL)
		luaL_typerror(L, 1, "Garage");

	lua_pushnumber(L, 128.0f);
	return 1;
}

int GetNumVisibleButtons(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);

	void* data = lua_touserdata(L, 1);
	if (!data)
		luaL_typerror(L, 1, "ButtonBar");

	lua_pushnumber(L, 0.0);
}



// Isn't it push then set global?
#define AddLuaFunction(fn, name)  lua_setglobal(L, name); \
												    lua_pushcclosure(L, fn, 0); \
													lua_settable(L, idx)

#define AddLuaGlobal(name, value) lua_setglobal(L, name); \
													 lua_pushnumber(L, value); \
													 lua_settable(L, idx)

void Lua_AddLoadAndSaveGlobals(int param_1)
{
	lua_State* L = g_pScriptHost_008e8418->stateStruct_0x8->L_0x4;
	int index = lua_gettop(L);
	lua_createtable(L, 0, 0);
	int idx = lua_gettop(L);

	lua_setglobal(L, "Save");
	lua_pushvalue(L, idx);
	lua_settable(L, LUA_GLOBALSINDEX);

	AddLuaFunction(GetSaveFlowResult, "GetSaveFlowResult");
	AddLuaFunction(GetSaveFlowState, "GetSaveFlowState");
	//AddLuaFunction(GetSaveFlowDeviceStatus, "GetSaveFlowDeviceStatus");
	//AddLuaFunction(UpdateSaveFlow, "UpdateSaveFlow");
	//AddLuaFunction(UpdateSaveGameInfo, "UpdateSaveGameInfo");
	//AddLuaFunction(LoadPlayerProfile, "LoadPlayerProfile");
	AddLuaFunction(SavePlayerProfile, "SavePlayerProfile");
	AddLuaFunction(GetSaveGameInfoValid, "GetSaveGameInfoValid");
	//AddLuaFunction(CheckSaveDevice, "CheckSaveDevice");
	//AddLuaFunction(CheckSaveDeviceNetwork, "CheckSaveDeviceNetwork");
	AddLuaFunction(SignalDeviceChanged, "SignalDeviceChanged");
	//AddLuaFunction(LoadOptions, "LoadOptions");
	//AddLuaFunction(SaveOptions, "SaveOptions");
	//AddLuaFunction(RefreshSaves, "RefreshSaves");
	//AddLuaFunction(GetLastError, "GetLastError");
	//AddLuaFunction(DeleteSave, "DeleteSave");
	AddLuaFunction(FormatMemoryCard, "FormatMemoryCard");
	//AddLuaFunction(LoadPlayerData, "LoadPlayerData");
	//AddLuaFunction(SavePlayerData, "SavePlayerData");
	//AddLuaFunction(LoadSystemData, "LoadSystemData");
	//AddLuaFunction(SaveSystemData, "SaveSystemData");
	//AddLuaFunction(GetNumExistingSaves, "GetNumExistingSaves");
	//AddLuaFunction(GetNumFreeSlots, "GetNumFreeSlots");
	//AddLuaFunction(GetNumSlots, "GetNumSlots");
	//AddLuaFunction(GetNumUsableSlots, "GetNumUsableSlots");
	//AddLuaFunction(GetSaveGameInfo, "GetSaveGameInfo");
	//AddLuaFunction(GetSaveDeviceInfo, "GetSaveDeviceInfo");
	//AddLuaFunction(GetLastSaveSlotUsed, "GetLastSaveSlotUsed");
	AddLuaFunction(GetSaveStatus, "GetSaveStatus");
	//AddLuaFunction(ResetSaveStatus, "ResetSaveStatus");
	AddLuaFunction(DEBUGLOG, "LaunchDashboard");
	AddLuaFunction(DEBUGLOG, "SetSaveDevicePoll");

	AddLuaGlobal("SAVEFLOW_OK", 0.0);
	AddLuaGlobal("SAVEFLOW_ERROR", 1.0);
	AddLuaGlobal("SAVEFLOW_USER_BACK", 2.0);

	AddLuaGlobal("SAVE_DEVICE_OK", 0.0);
	AddLuaGlobal("SAVE_DEVICE_CHANGED", 1.0);
	AddLuaGlobal("SAVE_DEVICE_NOT_ENOUGH_SPACE", 2.0);
	AddLuaGlobal("SAVE_DEVICE_NOT_AVAILABLE", 3.0);
	AddLuaGlobal("SAVE_DEVICE_UNFORMATTED", 4.0);

	AddLuaGlobal("SAVEFLOW_NONE", 0.0);
	AddLuaGlobal("SAVEFLOW_GETSAVEINFO", 1.0);
	AddLuaGlobal("SAVEFLOW_SAVEPLAYERPROFILE", 2.0);
	AddLuaGlobal("SAVEFLOW_LOADPLAYERPROFILE", 3.0);
	AddLuaGlobal("SAVEFLOW_LOADOPTIONS", 4.0);
	AddLuaGlobal("SAVEFLOW_SAVEOPTIONS", 5.0);
	AddLuaGlobal("SAVEFlOW_CHECKSAVEDEVICE", 6.0);

	//param_1->unkn_0x44c = 0;
	lua_settop(L, index);
}

int exists(lua_State* L)
{
	luaL_checklstring(L, 1, NULL);


	//if (DoesFileExistWrapper_AndDoesSomeMoreStateStuff(NULL))
	{
		lua_pushboolean(L, TRUE);
		return 1;
	}


	lua_pushnil(L);
	return 1;
}

uint UINT_008da690;

int getid(lua_State* L)
{
	char buffer[32];
	uint uVar1 = UINT_008da690++;

	sprintf(buffer, "%x", uVar1);
	lua_setglobal(L, buffer);
	return 1;
}

int getref(lua_State* L)
{
	int n = (int)(long long)roundf(lua_tonumber(L, 1));
	lua_rawgeti(L, LUA_REGISTRYINDEX, n);

	return 1;
}

void Lua_ClassBinding(int index, void* userdata, register lua_State* unaff_ESI)
{
	lua_pushlstring(unaff_ESI, "ClassBind", 9);
	lua_rawget(unaff_ESI, LUA_REGISTRYINDEX);
	lua_pushvalue(unaff_ESI, index);
	lua_rawseti(unaff_ESI, -2, (int)userdata);
	lua_pop(unaff_ESI, 1);
}

void Lua_CreateClassMaybe(char* name, lua_CFunction constructorMaybe, lua_CFunction gc, lua_CFunction newindex, register lua_State* L_ESI, register lua_CFunction index_EAX)
{
	if (!name)
	{
		lua_setglobal(L_ESI, "Class name not given!");
		lua_error(L_ESI);
	}

	luaL_newmetatable(L_ESI, name);
	int index = lua_gettop(L_ESI);

	if (!index_EAX || !newindex)
	{
		lua_createtable(L_ESI, 0, 0);
		int tempIndex = lua_gettop(L_ESI);
		lua_pushlstring(L_ESI, "__index", 7);
		lua_pushvalue(L_ESI, tempIndex);
		lua_settable(L_ESI, index);
		lua_pushlstring(L_ESI, "__newindex", 10);
		lua_pushvalue(L_ESI, tempIndex);
		lua_settable(L_ESI, index);
		lua_pop(L_ESI, 1);
	}
	else
	{
		lua_pushlstring(L_ESI, "__index", 7);
		lua_pushcclosure(L_ESI, index_EAX, 0);
		lua_settable(L_ESI, index);
		lua_pushlstring(L_ESI, "__newindex", 10);
		lua_pushcclosure(L_ESI, newindex, 0);
		lua_settable(L_ESI, index);
	}

	if (gc)
	{
		lua_pushlstring(L_ESI, "__gc", 4);
		lua_pushcclosure(L_ESI, gc, 0);
		lua_settable(L_ESI, index);
	}

	lua_pop(L_ESI, 1);
	if (constructorMaybe)
	{
		lua_pushcclosure(L_ESI, constructorMaybe, 0);
		lua_setfield(L_ESI, LUA_GLOBALSINDEX, name);
	}
}

int SavePlayerProfile(lua_State* L)
{
	uint num = (uint)(long long)roundf(luaL_checknumber(L, 1));

	if (g_pGameSettings_008e8410->m_nSaveFlowState_0x434 != 2 && g_pGameSettings_008e8410->m_nSaveFlowState_0x434 != 3)
	{
		g_pGameSettings_008e8410->unkn_0x43c = 0;
		//g_pGameSettings_008e8410->unkn_0x3c = 1;
		g_pGameSettings_008e8410->uint_0x20 = num;
		g_pGameSettings_008e8410->m_nSaveFlowState_0x434 = 2;
		g_pGameSettings_008e8410->unkn_0x438 = 10;
		g_pGameSettings_008e8410->unkn_0x24 = 0;
	}

	return 0;
}

int ScriptHost_NewIndex(lua_State* L)
{
	luaL_getmetafield(L, -3, "__luavars");
	lua_insert(L, -3);
	lua_rawset(L, -3);
	lua_pop(L, 1);

	return 0;
}

int FUN_00524ca0(lua_State* L, int param_2, register char* in_EAX, register int unaff_EBX)
{
	char* pcVar2 = in_EAX + 1;

	do; while (*in_EAX++);

	//pcVar2 = FUN_0054fd60(in_EAX - pcVar2, NULL);

	lua_CFunction fn;
	// It was originally a while but it's structured like a for so why not
	for (int i = param_2 - 1; true; i--)
	{
		if (i < 0)
		{
			lua_pushnil(L);
			return 1;
		}

		//fn = FUN_00524c20(*unaff_EBX[i], pcVar2);
		if (fn) break;
	}

	lua_pushcclosure(L, fn, 0);
	return 1;
}

uint UINT_008e8564;

int ScriptHost_Index(lua_State* L)
{
	luaL_getmetafield(L, -2, "__luavars");
	lua_pushvalue(L, -2);
	lua_rawget(L, -2);
	lua_remove(L, -2);

	if (lua_type(L, -1) == LUA_TNIL)
	{
		lua_pop(L, 1);
		const char* string = luaL_checklstring(L, -1, NULL);
		//if (string)
			//FUN_00524ca0(L, UINT_008e8564, (char*)string);
	}

	return 1;
}

void Lua_AddRegistryFieldAsItem(int index, register lua_State* L_ESI, register char* in_EAX)
{
	lua_getfield(L_ESI, LUA_REGISTRYINDEX, in_EAX);
	lua_setmetatable(L_ESI, index);
}

void Lua_PushScriptHost(ScriptHost* pScriptHost, register lua_State* L_EAX, register char* name_EDI)
{
	Lua_CreateClassMaybe(name_EDI, NULL, NULL, ScriptHost_NewIndex, L_EAX, ScriptHost_Index);
	lua_setglobal(L_EAX, name_EDI);

	auto newData = (ScriptHost**)lua_newuserdata(L_EAX, sizeof(ScriptHost*));
	*newData = pScriptHost;

	int index = lua_gettop(L_EAX);
	Lua_AddRegistryFieldAsItem(index, L_EAX, name_EDI);
	Lua_ClassBinding(index, pScriptHost, L_EAX);
	lua_getfield(L_EAX, LUA_REGISTRYINDEX, name_EDI);
	lua_pushlstring(L_EAX, "__luavars", 9);
	lua_createtable(L_EAX, 0, 0);
	lua_rawset(L_EAX, -3);
	lua_pop(L_EAX, 1);
	lua_settable(L_EAX, LUA_GLOBALSINDEX);
}

int Garage_Index(lua_State* L)
{

}

static void Lua_PushGarage(Garage* pGarage, register lua_State* L_EAX, register char* name_unaff_EDI)
{
	//UINT_008e8484 = 0;
	//UINT_008e9960 = 0;
	//UINT_008e9964 = 0;
	//UINT_008e9968 = 0;
	//UINT_008e996c = 0;
	//UINT_008e9970 = 0;

	UserDataName_008e8488 = name_unaff_EDI;
	Lua_CreateClassMaybe(name_unaff_EDI, NULL, NULL, ScriptHost_NewIndex, L_EAX, Garage_Index);
	lua_setglobal(L_EAX, name_unaff_EDI);

	void* garage = lua_newuserdata(L_EAX, 4);
	*(Garage**)garage = pGarage;
	int lastIndex = lua_gettop(L_EAX);
	Lua_AddRegistryFieldAsItem(lastIndex, L_EAX, name_unaff_EDI);
	Lua_ClassBinding(lastIndex, pGarage, L_EAX);
	lua_getfield(L_EAX, LUA_REGISTRYINDEX, name_unaff_EDI);
	lua_pushlstring(L_EAX, "__luavars", 9);
	lua_createtable(L_EAX, 0, 0);
	lua_rawset(L_EAX, -3);
	lua_pop(L_EAX, 1);
	lua_settable(L_EAX, LUA_GLOBALSINDEX);
}

int NextRaceUpdated(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	int* piVar1 = (int*)lua_touserdata(L, 1);
	if (!piVar1)
		luaL_typerror(L, 1, "SessionClass");

	//lua_pushboolean(L, (piVar1->byte_0x216c & 0x20) >> 5);
	return 1;
}


BYTE byteArray_00652728[256] =
{
	0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, //...
};

// Instead of writing all that out, I'm going to replace it with code that would do the same thing
// Each item is duplicated by a factor of 2, so it only goes to 8
void CreateThatByteArray()
{
	byteArray_00652728[0] = 0;
	int num, innerLoops, index;
	num = innerLoops = index = 1;
	while (index < 256)
	{
		for (int j = 0; j < innerLoops; j++)
			byteArray_00652728[index + j] = num;

		index += innerLoops;
		num++;
		innerLoops *= 2;
	}
}

int FUN_005bb8a0(uint indexKinda)
{
	uint i = -1;
	for (; indexKinda > 255; indexKinda >>= 8)
		i += 8;

	return (uint)byteArray_00652728[indexKinda] + i;
}


void vector2IntToVector4Int(Vector4Int* vector, int x, int y)
{
	vector->w = -1;
	vector->a = -1;
	vector->x = x;
	vector->y = y;
}



/////////////////////////////////////////////////
// 
// File System
//
/////////////////////////////////////////////////

// Writes a section of the file to it's handle, given the buffer and desired bytes to write. Returns the number of bytes actually written for comparison.
// Updates realFilePos and filePos to point after the written bytes.
DWORD MWFileObject::WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite)
{
	DWORD bytesWritten;
	DWORD totalBytesWritten = 0;
	HANDLE hFile;
	DWORD tempToWrite;

	if (bytesToWrite != 0)
	{
		hFile = this->handle;

		for (int d = bytesToWrite; d; d -= tempToWrite)
		{
			// Writes in 64 KB chunks
			tempToWrite = 0xFFFF;
			if (d < 0x10000)
				tempToWrite = d;

			WriteFile(hFile, buffer, tempToWrite, &bytesWritten, NULL);
			buffer = (LPCVOID)((int)buffer + tempToWrite);
			totalBytesWritten += bytesWritten;
		}
	}

	// Advance the pointers
	// I just noticed, it uses bytesToWrite instead of totalBytesWritten, so it'll skip too far if it couldn't write everything.
	this->realFilePos += bytesToWrite;
	this->filePos += bytesToWrite;
	return totalBytesWritten;
}

void MWFileObject::bbSetFilePointer(int newLoc)
{
	if (this->realFilePos != (char*)newLoc)
	{
		this->realFilePos = (char*)newLoc;
		SetFilePointer(this->handle, newLoc, NULL, FILE_BEGIN);
	}
	return;
}

// FileObject_New() is a more complicated version of FileObject_Create()
MWFileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX)
{
	MWFileObject* output = NULL;
	// Checking if it's reading an existing file or not
	if ((flags_unaff_EBX & 1) == 0)
	{
		MWFileObject* newFile = (MWFileObject*)malloc(sizeof(MWFileObject));
		if (newFile != NULL)
		{
			newFile->filePos = NULL;
			newFile->realFilePos = NULL;
			newFile->handle = NULL;
			newFile->filename1 = NULL;
			newFile->fileattributes = NULL;
			//piVar2->vtable = JMPTABLE_0067b6f8;
			newFile->usuallyNeg1 = -1;
			output = newFile;
		}
		// It's outside the if statement, which will try to access output even when it's NULL.
		output->Create(filename_unaff_EDI, flags_unaff_EBX);
	}
	else
	{
		struct _stat result;
		int iVar1 = _stat(filename_unaff_EDI, &result);

		if (iVar1 == 0)
		{
			MWFileObject* pAVar2 = (MWFileObject*)malloc(sizeof(MWFileObject));
			if (pAVar2 != NULL)
			{
				FileObject_ClearEAX(pAVar2);
				output = pAVar2;
			}
			// They did it again
			output->Create(filename_unaff_EDI, flags_unaff_EBX);
			void* pvStack_18;
			output->size = pvStack_18;
			return output;
		}
	}
	return output;
}

void MWFileObject::Create(LPCSTR lpFilename, uint flags)
{
	DWORD desiredAccess = 0;
	DWORD creationDisposition = 0;
	bool bRead = flags & 1;
	if (bRead)
	{
		desiredAccess = GENERIC_READ;
		creationDisposition = OPEN_EXISTING;
	}
	DWORD shareMode = bRead;
	DWORD flagsAndAttributes = bRead;
	if (flags & 2)
	{
		desiredAccess |= GENERIC_WRITE;
		creationDisposition |= CREATE_ALWAYS;
		flagsAndAttributes |= FILE_ATTRIBUTE_NORMAL;
		shareMode = FILE_SHARE_READ;
	}
	HANDLE handle = CreateFileA(lpFilename, desiredAccess, shareMode, NULL, creationDisposition, flagsAndAttributes, NULL);
	this->fileattributes = flags;
	this->handle = handle;
	//if ((handle == NULL) && (FUNC_008da6f4 != NULL))
		//(*FUNC_008da6f4)();

	return;
}


// If mode is 1, It'll just set the file pos with no fuss.
// If mode is 2, It'll treat the file pos relative to the end.
// If mode is 0, checks a flag in the attributes and if it's cleared, read from the file in, a way.
void MWFileObject::SetFilePos(int newPos, int mode)
{
	switch (mode)
	{

	case 0:
		if ((this->fileattributes & 0x100) == 0)
		{
			char* pcVar1 = this->filePos;
			/*
			for (int iVar2 = this->usuallyNeg1; iVar2 < (int)(pcVar1 + newPos) >> 14; iVar2++)
				if (iVar2 > -1)
					this->FileObject_Read(iVar2);
			*/
		}
		break;

	case 1:
		this->filePos = (char*)newPos;
		break;

	case 2:
		this->filePos = (char*)((int)this->size - newPos);

	}
	return;
}

void MWFileObject::FlushBuffers()
{
	FlushFileBuffers(this->handle);
}

// This would make sense if the filePos was private, but it has to be public to be accessed by the FileObject_ClearEAX() function.
// It might not be a C++ class anyways so did they go through the trouble of integrating public/private distinction in their own class?
char* MWFileObject::GetFilePosButLikeWhy()
{
	return this->filePos;
}


bool MWFileObject::AtEndOfFile()
{
	return ((int)this->filePos > 0) && (this->size <= this->filePos);
}

int MWFileObject::GetSize()
{
	return (this->size == (void*)-1) ? (int)this->filePos : (int)this->size;
}

void MWFileObject::Clear()
{
	this->usuallyNeg1 = -1;
	this->filePos = NULL;
	this->realFilePos = NULL;
	this->handle = NULL;
	this->filename1 = NULL;
	this->filename2 = NULL;
	return;
}

void __fastcall MWFileObject::Close()
{
	if (this->handle != NULL)
	{
		CloseHandle(this->handle);
		this->handle = NULL;
	}
	return;
}

MWFileObject* MWFileObject::ResetMaybe(int bFree)
{
	//this->vtable = JMPTABLE_0067b6f8;
	if (this->handle != NULL)
	{
		CloseHandle(this->handle);
		this->handle = NULL;
	}
	if (bFree & 1)
		free(this);

	return this;
}

void __fastcall FileObject_ClearEAX(MWFileObject* in_EAX)
{
	//in_EAX->vtable = JMPTABLE_0067b6f8;
	in_EAX->usuallyNeg1 = -1;
	in_EAX->filePos = NULL;
	in_EAX->realFilePos = NULL;
	in_EAX->handle = NULL;
	in_EAX->filename1 = NULL;
	in_EAX->filename2 = NULL;
	return;
}

void MWFileObject::DoNothing()
{
	return;
}


void (*FUNC_008da6f4)();
MWFileObject* PTR_008da72c;
uint UINT_008da730;

// My own addition to make reading this next function much easier.
// Macros to read different types from a char buffer at an offset.
#define ReadAsInt(buf, offset) (*(int*)(&buf[offset]))
#define ReadAsIntP(buf, offset) ((int*)(&buf[offset]))
#define ReadAsByte(buf, offset) (*(BYTE*)(&buf[offset]))
#define ReadAsString(buf, offset) (&buf[offset])

void OpenBFS(LPCSTR filename, register YetAnotherFileObject* unaff_EDI)
{
	int aiStack_10[2];
	int iVar2;
	int iVar9;

	// The length of the filename is calculated, but it's never used.
	String_GetLength((char*)filename);

	// Very large structure
	//unaff_EDI[0x88] = NULL;

	DWORD fileFlags = FILE_ATTRIBUTE_NORMAL;

	if (UINT_008da730)
		fileFlags |= FILE_FLAG_DELETE_ON_CLOSE;

	// bfsFile seems to be an all-purpose variable, first it's the handle of the file, then it's used to contain the size of the file, then it's used to point at the file's data, then it's used as a temporary int.
	char* bfsFile = (char*)CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, fileFlags, NULL);

	unaff_EDI->handle_0x0 = bfsFile;
	if (bfsFile == NULL)
	{
		if (FUNC_008da6f4 != NULL)
			FUNC_008da6f4();

		CreateErrorMessageAndDie("Failed to open BFS archive: %s");
	}

	bfsFile = (char*)GetFileSize((HANDLE)bfsFile, NULL);
	if ((int)bfsFile == -1)
		CreateErrorMessageAndDie("Could not query file size for BFS archive: %s");

	MWFileObject* pAVar4 = PTR_008da72c;
	unaff_EDI->size_0x4 = (int)bfsFile;
	//FUN_0059b60(PTR_008da72c, unaff_EDI, aiStack_10, 0, 0x10);

	// The file must start with the characters "bfsl"
	if (aiStack_10[0] != 0x31736662)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid id");

	// I don't know how, but it ends up with bfsFile pointing to the contents of the file
	/*
	unaff_EDI->unkn_0x210 = uStack_8 & 0x7FFFFFFFF;
	uint uStack_8 = 0;
	size_t _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
	HANDLE pvStack_4;
	unaff_EDI[0x85] = (char*)pvStack_4;
	uint* puVar7 = (uint*)malloc(_Size);
	pAVar4 = PTR_008da72c;
	unaff_EDI[0x82] = (char*)puVar7;
	//FUN_00559b60(PTR_008da72c, unaff_EDI, puVar7, unaff_EDI[0x88], _Size);
	//pvVar6 = unaff_EDI[0x82];
	if ((int)uStack_8 < 0)
		FUN_005610f0((int)&DAT_0069bd10, _Size - 0x10 >> 2);
	*/

	// For now I'll just do it the standard way
	char* ptr = (char*)malloc((size_t)bfsFile);
	DWORD bytesRead;
	ReadFile(unaff_EDI->handle_0x0, ptr, (size_t)bfsFile, &bytesRead, NULL);
	bfsFile = (char*)ptr;

	// The hash size located 16 bytes from the start, and must be 997.
	// If it has to be a known value, why include it in the file? Some kind of anti-tamper?
	if (ReadAsInt(bfsFile, 0x10) != 0x3E5)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

	// Only included in fo2a.bfs, b and c's is NULL
	unaff_EDI->string_0x218 = ReadAsString(bfsFile, 0x14);

	int* piVar10 = ReadAsIntP(bfsFile, 0x1F3C);
	int* piVar7 = (int*)malloc(0x14);
	if (piVar7 != NULL)
	{
		iVar9 = ReadAsInt(bfsFile, 8000);
		*piVar7 = *piVar10;
		iVar2 = ReadAsInt(bfsFile, 0x1F44);
		piVar7[1] = iVar9 + (int)piVar10;
		iVar9 = ReadAsInt(bfsFile, 0x1F48);
		piVar7[2] = iVar2 + (int)piVar10;
		iVar2 = ReadAsInt(bfsFile, 0x1F4C);
		piVar7[3] = iVar9 + (int)piVar10;
		piVar7[4] = iVar2 + (int)piVar10;
	}

	unaff_EDI->string_0x21c = (char*)piVar7;

	bfsFile = (char*)((int)piVar10 + *piVar7);
	unaff_EDI->string_0x20c = bfsFile;

	int pvVar3 = unaff_EDI->int_0x220;
	if (pvVar3 != 0)
	{
		for (int i = unaff_EDI->int_0x214; i != 0; i--)
		{
			ReadAsInt(bfsFile, 4) += (int)pvVar3;

			// The p code uses a second comparison like a trick to set j during the if. I chose to do it afterwards, is it any different?
			// && (j = 0, bfsFile[1] != NULL)
			// If that's all it was for I can probably just remove it
			if (bfsFile[1] != NULL)
			{
				int j = 0;
				do
				{
					piVar7 = ReadAsIntP(bfsFile, j * 4 + 0x18);
					*piVar7 += (int)pvVar3;
					j++;
				} while (j < ReadAsByte(bfsFile, 1));
			}
			bfsFile += ReadAsByte(bfsFile, 1) * 4 + 0x18;
		}
	}
	return;
}

// I called this one 'Again', but couldn't find the original one
void BFSReadOverlapAgain()
{

}


int SignalDeviceChanged(lua_State* L)
{
	//FileObject_DoNothing();
	return 0;
}
