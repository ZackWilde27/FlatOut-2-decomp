/////////////////////////////////////////////////
// 
// SCRAP Engine
// 
/////////////////////////////////////////////////

// My on-going recreation of ROMU based on decompiling FlatOut 2

// ROMU is always spelled with capitals, so I assumed it was an acronym, but it turns out it's the finnish word for scrap metal.
// SCRAP it is.

// It's extremely similar to 1 and UC's ROMU but there are enough changes, especially in the locations of things that it would make more sense to re-write it to match each game.

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// I checked, and they forgot to update the string, unless they considered the changes to be that small.
// SCRAP v0.28b
const char* verString_00698b4c = "Version 0.28 build 2004.09.20";

float g_GlobalFontScale_006993f8;


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

		pcVar2 = in_string;

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

const char* StringList_00681888[256] =
{
	"\0",
	"hostname",
	"gamename",
	"gamever",
	"hostport",
	"mapname",
	"gametype",
	"gamevariant",
	"numplayers",
	"numteams",
	"maxplayers",
	"gamemode",
	"teamplay",
	"fraglimit",
	"teamfraglimit",
	"timeelapsed",
	"timelimit",
	"roundtime",
	"roundelapsed",
	"password",
	"groupid",
	"player_",
	"score_",
	"skill_",
	"ping_",
	"team_",
	"deaths_",
	"pid_",
	"team_t",
	"score_t"
	// ... null pointers to fill the rest of the array, 256 entries long.
};


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

// So far I've found 7 copies of this function in different spots, maybe they are different types of empty PROC functions?
void DoNothing()
{
	return;
}
void DoNothingAgain()
{
	return;
}
void DoNothingTheThird()
{
	return;
}
void DoNothing4()
{
	return;
}
void DoNothing5()
{
	return;
}
void DoNothing6()
{
	return;
}
// There were so many I lost count when I named this one
void DoNothing8()
{
	return;
}

void noerror()
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

struct MemoryManager
{
	void (**vftable_0x0)();
	CRITICAL_SECTION criticalSection_0x4;
	void* ptr_0x1c;
	//BYTE pad_0x20;
	bool bCriticalSectionActive_0x21;
};

MemoryManager g_MemoryManager_0069c8f0;

void FreeInCriticalSection(void* block)
{
	if (block)
	{
		if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
			EnterCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);

		free(block);//IsThatACustomMadeFree(&g_MemoryManager_0069c8f0, block)

		if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
			LeaveCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);
	}
}

void* AllocateInCriticalSection(int size)
{
	if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
		EnterCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);

	void* ptr = malloc(size);//IsThatACustomMadeMalloc(size, &g_MemoryManager_0069c8f0);

	if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
		LeaveCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);

	return ptr;
}

// Never mind, Ghidra did not see the new size parameter
void* ReAllocateInCriticalSection(void* block, int nsize)
{
	if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
		EnterCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);

	void* ptr = realloc(block, nsize);// IsThatACustomMadeRealloc(&g_MemoryManager_0069c8f0, block, nsize);

	if (g_MemoryManager_0069c8f0.bCriticalSectionActive_0x21)
		LeaveCriticalSection(&g_MemoryManager_0069c8f0.criticalSection_0x4);

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

		FreeInCriticalSection(block);

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
			newBlock = ReAllocateInCriticalSection(block, nsize);

		if (!newBlock)
		{
			if (L)
				luaD_throw(L, 4);

			return NULL;
		}
	}

	return newBlock;
}

int __stdcall GetScriptParameterInt(register LuaStateStruct* lss_EAX)
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

BOOL __stdcall GetScriptParameterBool(register LuaStateStruct* lss_ESI)
{
	if (lua_type(lss_ESI->L_0x0, lss_ESI->index_0x4) == LUA_TNIL)
		return FALSE;

	if (lua_isnumber(lss_ESI->L_0x0, lss_ESI->index_0x4))
		return (BOOL)(bool)GetScriptParameterInt(lss_ESI);

	return lua_toboolean(lss_ESI->L_0x0, lss_ESI->index_0x4);
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

/////////////////////////////////////////////////
//
// lua_CFunctions
// 
/////////////////////////////////////////////////

// I thought these returned error codes, I was wrong about that.

void FileObject_DoNothing()
{
	return;
}

int SignalDeviceChanged()
{
	FileObject_DoNothing();
	return 0;
}

// Instead of an sRGBA, it's treated as an array of integers.
// I'll just change it to sRGBAs to make things easier
sRGBA Palettes_008dd040[1]; // No idea how big the array is

int GetPaletteColour(lua_State* L)
{
	int rounded = (int)(ulonglong)roundf(luaL_checknumber(L, 1));
	sRGBA palette = Palettes_008dd040[rounded];
	lua_createtable(L, 0, 0);
	int index = lua_gettop(L);

	lua_pushnumber(L, palette.r);
	lua_rawseti(L, index, 1);

	lua_pushnumber(L, palette.g);
	lua_rawseti(L, index, 2);

	lua_pushnumber(L, palette.b);
	lua_rawseti(L, index, 3);

	lua_pushnumber(L, palette.a);
	lua_rawseti(L, index, 4);

	return 1;
}

CupManager* g_pCupManager_008e8480;

static int IsCupRaceCompleted(lua_State* L)
{
	LuaStateStruct lss{ L, 1 };
	uint index = GetScriptParameterInt(&lss);

	BOOL isCompleted;
	if ((index < 1) || (index > g_pCupManager_008e8480->m_nCupRaceLength_0x5a8))
		isCompleted = FALSE;
	else
		isCompleted = g_pCupManager_008e8480->m_aCupRaces_0x8[index - 1].m_bCompleted_0x6c;

	lua_pushboolean(L, isCompleted);
	return 1;
}

int IsCupRaceLocked(lua_State* L)
{
	LuaStateStruct lss{ L, 1 };
	int index = GetScriptParameterInt(&lss);

	if (!g_pCupManager_008e8480->m_nActiveIndex_0x588)
	{
		lua_pushboolean(L, index != 1);
		return 1;
	}

	if (index > 0 && index <= g_pCupManager_008e8480->m_nCupRaceLength_0x5a8)
	{
		lua_pushboolean(L, g_pCupManager_008e8480->m_aCupRaces_0x8[index - 1].m_bLocked_0x68);
		return 1;
	}

	lua_pushboolean(L, FALSE);
	return 1;
}

int GetCupSize(lua_State* L)
{
	lua_pushnumber(L, (lua_Number)g_pCupManager_008e8480->m_nCupRaceLength_0x5a8);
	return 1;
}

int IsCupActive(lua_State* L)
{
	lua_pushboolean(L, g_pCupManager_008e8480->m_nActiveIndex_0x588 != 0);
	return 1;
}

// So many functions did pretty much the exact same thing, so I made it a macro
#define luaboilerplate_checkudata(index, type, name) luaL_checktype(L, index, LUA_TUSERDATA); \
																			   type* data = (type*)luaL_checkudata(L, index, name); \
																			   if (data == NULL) luaL_typerror(L, index, name)

#define luaboilerplate_touserdata(index, type, name) luaL_checktype(L, index, LUA_TUSERDATA); \
																			  type* data = (type*)lua_touserdata(L, index); \
																			  if (data == NULL) luaL_typerror(L, index, name)



static int CupManager_IsCupActive(lua_State* L)
{
	// They use variables to point at each string, but it always points at the same string (when its not NULL), so I just directly referenced the constant
	// It points at the PlayerProfile string, but it doesn't line up with another struct that uses the same name,
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	lua_pushboolean(L, (*data)->m_nActiveIndex_0x588);

	return 1;
}

static int CupManager_IsCupFinished(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");
	
	CupManager* cupManager = *data;

	bool isFinished;

	int activeIndex = cupManager->m_nActiveIndex_0x588;

	if (cupManager->unkn_0x4 == 0)
	{
		if (activeIndex < 1 || activeIndex > cupManager->m_nCupRaceLength_0x5a8 || cupManager->m_aCupRaces_0x8[activeIndex - 1].unkn_0x34== 0)
		{
			if (cupManager->GetNextRaceIndex(1) == 0)
			{
				isFinished = true;
				goto IsCupFinished_Exit;
			}
		}
	}
	isFinished = false;

IsCupFinished_Exit:
	lua_pushboolean(L, isFinished);
	return 1;
}

static int CupManager_GetCurrentRaceIndex(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_nActiveIndex_0x588);
	return 1;
}

static int CupManager_GetNextRaceIndex(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	CupManager* cupManager = *data;
	LuaStateStruct lss{ L, 2 };

	int shouldBe1 = GetScriptParameterInt(&lss);
	int raceIndex = cupManager->m_nActiveIndex_0x588;

	int nextRaceIndex;
	if (raceIndex < 1 || raceIndex > cupManager->m_nCupRaceLength_0x5a8)
		nextRaceIndex = 0;
	else
		nextRaceIndex = cupManager->m_aCupRaces_0x8[raceIndex - 1].m_nNextRaceIndex_0x38;

	lua_pushnumber(L, nextRaceIndex);
	return 1;
}

static int CupManager_GetCupSize(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	lua_pushnumber(L, (lua_Number)(*data)->m_nCupRaceLength_0x5a8);

	return 1;
}

static int CupManager_IsRaceLocked(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	CupManager* cupManager = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	BOOL isLocked;
	if (index < 1 || index > cupManager->m_nCupRaceLength_0x5a8)
		isLocked = FALSE;
	else
		isLocked = cupManager->m_aCupRaces_0x8[index - 1].m_bLocked_0x68;

	lua_pushboolean(L, isLocked);
	return 1;
}

static int CupManager_IsRaceCompleted(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	CupManager* cupManager = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	BOOL isCompleted;
	if (index < 1 || index > cupManager->m_nCupRaceLength_0x5a8)
		isCompleted = FALSE;
	else
		isCompleted = cupManager->m_aCupRaces_0x8[index - 1].m_bCompleted_0x6c;

	lua_pushboolean(L, isCompleted);
	return 1;
}

static int CupManager_GetCupPoints(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	CupManager* cupManager = *data;
	LuaStateStruct lss{ L, 2 };
	int indexOrId = GetScriptParameterInt(&lss);

	int points;
	int i = 0;
	do
	{
		if (cupManager->m_aCupPoints_0x548[i].m_nIndexOrId_0x0 == indexOrId)
		{
			points = cupManager->m_aCupPoints_0x548[i].m_nPoints_0x4;
			goto GetCupPoints_Exit;
		}
	} while (++i < 8);
	
	points = 0;
GetCupPoints_Exit:
	lua_pushnumber(L, points);
	return 1;
}

static int __fastcall GetCupPositionForReal(CupManager* cupManager_EDX, int index_EAX)
{
	int points;
	int i = 0;
	do
	{
		if (cupManager_EDX->m_aCupPoints_0x548[i].m_nIndexOrId_0x0 == index_EAX)
		{
			points = cupManager_EDX->m_aCupPoints_0x548[i].m_nPoints_0x4;
			goto GetCupPositionForReal_FoundPoints;
		}
	} while (++i < 8);

	points = 0;
GetCupPositionForReal_FoundPoints:
	int position = 1;

	// I'm rolling this into a loop
	for (i = 0; i < 8; i++)
	{
		if (points < cupManager_EDX->m_aCupPoints_0x548[i].m_nPoints_0x4)
			position += 1;
	}

	return position;
}

static int CupManager_GetCupPosition(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");
	CupManager* cupManager = *data;

	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushnumber(L, GetCupPositionForReal(cupManager, index));
	return 1;
}

static int CupManager_GetRacePosition(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	// posIndex is apparently always 0
	int posIndex = GetScriptParameterInt(&lss);
	lss = { L, 3 };
	int raceIndex = GetScriptParameterInt(&lss);

	// The math done to calculate the offset is weird
	// Instead of (0x8 + (raceIndex - 1) * sizeof(CupRace) + 0x48 + posIndex * sizeof(int))
	// It is ((raceIndex * (sizeof(CupRace) / sizeof(int)) + posIndex) * sizeof(int) - 0x30)
	// Figuring out what it was actually doing took way too long
	lua_pushnumber(L, (*data)->m_aCupRaces_0x8[raceIndex - 1].m_nPosition_0x40);
	return 1;
}

static int CupManager_GetNumDrivers(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_nNumDrivers_0x5ac);
	return 1;
}

static int CupManager_IsCupPositionVisible(lua_State* L)
{
	luaboilerplate_checkudata(1, CupManager*, "PlayerProfile");
	CupManager* cupManager = *data;
	
	LuaStateStruct lss{ L, 2 };
	int requiredPositionMaybe = GetScriptParameterInt(&lss);

	bool isVisible;
	int numDrivers = cupManager->m_nNumDrivers_0x5ac;
	int i = 0;
	if (numDrivers > 0)
	{
		do
		{
			if (GetCupPositionForReal(cupManager, i) == requiredPositionMaybe)
			{
				isVisible = true;
				goto IsCupPositionVisible_Exit;
			}
		} while (++i < numDrivers);
	}
	isVisible = false;

IsCupPositionVisible_Exit:
	lua_pushboolean(L, isVisible);
	return 1;
}

luaL_reg g_CupManagerLibrary_00696e40[] = {
	//{ "PrepareFromScript", CupManager_PrepareFromScript },
	//{ "Clear", CupManager_Clear },
	{ "IsCupActive", CupManager_IsCupActive },
	{ "IsCupFinished", CupManager_IsCupFinished },
	{ "GetCurrentRaceIndex", CupManager_GetCurrentRaceIndex },
	{ "GetNextRaceIndex", CupManager_GetNextRaceIndex },
	{ "GetCupSize", CupManager_GetCupSize },
	{ "IsRaceLocked", CupManager_IsRaceLocked },
	{ "IsRaceCompleted", CupManager_IsRaceCompleted },
	{ "GetCupPoints", CupManager_GetCupPoints },
	{ "GetCupPosition", CupManager_GetCupPosition },
	{ "GetRacePosition", CupManager_GetRacePosition },
	{ "GetNumDrivers", CupManager_GetNumDrivers },
	{ "IsCupPositionVisible", CupManager_IsCupPositionVisible }
};

static int GetActiveControllers(lua_State* L)
{
	luaboilerplate_checkudata(1, void, "GUI");

	lua_createtable(L, 0, 0);
	int index = lua_gettop(L);
	lua_pushboolean(L, 1);
	lua_rawseti(L, index, 1);
	return 1;
}

static int GetCameraTargetOffset(lua_State* L)
{
	// This pointer stays NULL the entire time, So there's no indication which struct this is
	// Is that allowed in checkudata?
	luaboilerplate_checkudata(1, BCORE_Camera*, NULL);

	BCORE_Camera* camera = *data;

	lua_createtable(L, 0, 0);
	int index = lua_gettop(L);

	// Whatever struct it is, it's over 8,000 bytes large, it's 8 times larger than even a PlayerCamera, Maybe it's an array of cameras?
	//lua_pushnumber(L, camera[0x22].float_0x10);
	lua_rawseti(L, index, 1);
	//lua_pushnumber(L, camera[0x22].float_0x14);
	lua_rawseti(L, index, 2);
	//lua_pushnumber(L, camera[0x22].float_0x18);
	lua_rawseti(L, index, 3);

	return 1;
}

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
	return 0;
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

// Global pointers to the various instances
GameSettings* g_pGameSettings_008e8410;

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
#define luaboilerplate_checkudata(index, type, name) luaL_checktype(L, index, LUA_TUSERDATA); \
															 type* data = (type*)luaL_checkudata(L, index, name); \
															 if (data == NULL) luaL_typerror(L, index, name)

#define luaboilerplate_touserdata(index, type, name) luaL_checktype(L, index, LUA_TUSERDATA); \
																			  type* data = (type*)lua_touserdata(L, index); \
																			  if (!data) luaL_typerror(L, index, name);

int Disable(lua_State* L)
{
	luaboilerplate_checkudata(1, MenuMap*, "MenuMap");

	(*data)->m_bEnabled_0x4 = FALSE;
	return 0;
}

// This is just a guess as to how it's laid out
struct Phrase
{
	wchar_t** wstring_0x0;
	void* unkn_0x4;
};

struct PhraseList
{
	uint size;
	Phrase list[];
};

PhraseList* PTR_008da574;

static int GetPhrase(lua_State* L)
{
	wchar_t buffer[256];
	int bufferLength;

	if (!lua_isnumber(L, 1))
	{
		swprintf(buffer, L"NO_TEXTID");
		bufferLength = WString_GetLength(buffer);
		lua_pushlstring(L, (char*)buffer, bufferLength * 2 + 2);
		return 1;
	}

	uint index = (uint)(long long)roundf(luaL_checknumber(L, 1));
	if (index > -1 && index < PTR_008da574->size)
	{
		WCHAR* in_wstring = *PTR_008da574->list[index].wstring_0x0;
		bufferLength = WString_GetLength(in_wstring);
		lua_pushlstring(L, (char*)in_wstring, bufferLength * 2 + 2);
		return 1;
	}

	swprintf(buffer, L"INVALID_ID%d", index);
	bufferLength = WString_GetLength(buffer);
	lua_pushlstring(L, (char*)buffer, bufferLength * 2 + 2);
	return 1;
}

static int GetPhrase2(lua_State* L)
{
	LuaStateStruct lss{ L, 1 };
	uint index = GetScriptParameterInt(&lss);
	WCHAR* in_wstring = (WCHAR*)u"NO_TEXT";

	if (PTR_008da574 && index < PTR_008da574->size)
		WCHAR* in_wstring = *PTR_008da574->list[index].wstring_0x0;

	int length = WString_GetLength(in_wstring);
	lua_pushlstring(L, (char*)in_wstring, length * 2 + 2);
	return 1;
}

static int GetPlayerName(lua_State* L)
{
	LuaStateStruct lss{ L, 1 };
	uint index = GetScriptParameterInt(&lss);

	// The way it's arranged is that each name is one after the other, each 17 characters long.
	wchar_t* ptr = g_pGameSettings_008e8410->m_aPlayerNames_0x5b0;
	int length = WString_GetLength(&ptr[index * 0x22]);

	lua_pushlstring(L, (char*)&ptr[index * 0x22], length * 2 + 2);
	return 1;
}

// Inline functions to make the next one easier to read
static inline int PlayersList_CurrentPlayersLength(PlayersList* list)
{
	return ((int)list->m_pLastCurrentPlayer_0x8 - (int)list->m_aCurrentPlayers_0x4) >> 2;
}

static inline int PlayersList_RecentPlayersLength(PlayersList* list)
{
	return ((int)list->m_pLastRecentPlayer_0x14 - (int)list->m_aRecentPlayers_0x10) >> 2;
}

Player* __fastcall GetPlayerFromPlayersList(int index_ECX, PlayersList* list_EAX)
{
	if (PlayersList_RecentPlayersLength(list_EAX) + PlayersList_CurrentPlayersLength(list_EAX) <= index_ECX)
		return NULL;

	if (index_ECX < PlayersList_CurrentPlayersLength(list_EAX))
		return list_EAX->m_aCurrentPlayers_0x4[index_ECX];

	return list_EAX->m_aRecentPlayers_0x10[index_ECX - PlayersList_CurrentPlayersLength(list_EAX)];
}

static int PlayersList_IsResultsUpdated(lua_State* L)
{
	luaboilerplate_touserdata(1, PlayersList*, "PlayersList");

	uint bResultsUpdated = ((uint(*)())(*data)->vftable_0x0[6])();
	lua_pushboolean(L, bResultsUpdated & 0xFF);
	return 1;
}

static int PlayersList_SetPlayerMuted(lua_State* L)
{
	luaboilerplate_touserdata(1, PlayersList*, "PlayersList");

	PlayersList* list = *data;
	lua_touserdata(L, 2);
	LuaStateStruct lss{ L, 3 };

	BOOL bMuted = lua_type(L, 3);

	if (bMuted != LUA_TNIL)
	{
		if (!lua_isnumber(L, 3))
			bMuted = lua_toboolean(L, 3);
		else
			bMuted = (bool)GetScriptParameterInt(&lss);
	}

	//SetPlayerMuted(list, bMuted);
	return 0;
}

static int PlayersList_SetListShowing(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayersList*, "PlayersList");

	PlayersList* list = *data;
	LuaStateStruct lss{ L, 2 };
	if (lua_type(L, 2) == LUA_TNIL)
	{
		list->m_bListShowing_0x93d = false;
		return 0;
	}

	if (lua_isnumber(L, 2))
	{
		list->m_bListShowing_0x93d = (bool)GetScriptParameterInt(&lss);
		return 0;
	}

	list->m_bListShowing_0x93d = lua_toboolean(L, 2);
	return 0;
}

static int PlayersList_GetNumCurrentPlayers(lua_State* L)
{
	luaboilerplate_touserdata(1, PlayersList*, "PlayersList");

	lua_pushnumber(L, (lua_Number)PlayersList_CurrentPlayersLength(*data));
	return 1;
}

static int PlayersList_GetNumRecentPlayers(lua_State* L)
{
	luaboilerplate_touserdata(1, PlayersList*, "PlayersList");

	lua_pushnumber(L, (lua_Number)PlayersList_RecentPlayersLength(*data));
	return 1;
}

static int PlayersList_Update(lua_State* L)
{
	luaboilerplate_touserdata(1, PlayersList*, "PlayersList");
	PlayersList* list = *data;

	BOOL that = 0;
	//if (lua_gettop(L) > 1)
		//that = (bool)FUN_005234b0();

	((void (*)(int))list->vftable_0x0[1])(that);
	return 0;
}

luaL_Reg luaL_Reg_ARRAY_00697ff0[10] = {
	{ "Update", PlayersList_Update, },
	{ "IsResultsUpdated", PlayersList_IsResultsUpdated },
	//{ "SetUserIndex", PlayersList_SetUserIndex },
	{ "GetNumCurrentPlayers", PlayersList_GetNumCurrentPlayers },
	{ "GetNumRecentPlayers", PlayersList_GetNumRecentPlayers },
	//{ "GetPlayerInfo", PlayersList_GetPlayerInfo },
	{ "SetPlayerMuted", PlayersList_SetPlayerMuted },
	//{ "Init", PlayersList_Init },
	//{ "DeInit", PlayersList_DeInit },
	{ "SetListShowing", PlayersList_SetListShowing }
};

static int PlayerProfile_EnoughMoney(lua_State* L)
{
	// Uses a different pointer to reference the PlayerProfile string, it also never changes so it may as well directly reference the constant.
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;

	LuaStateStruct lss{ L, 2 };
	int requiredMoney = GetScriptParameterInt(&lss);

	lua_pushboolean(L, profile->m_nMoney_0xe58 >= requiredMoney);

	return 1;
}

static int PlayerProfile_GetMoney(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_nMoney_0xe58);
	return 1;
}

static int PlayerProfile_SetMoney(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;

	LuaStateStruct lss{ L, 2 };
	int newMoney = GetScriptParameterInt(&lss);
	profile->m_nMoney_0xe58 = newMoney;

	return 0;
}

int PlayerProfile_AddMoney(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	LuaStateStruct lss{ L, 2 };
	int newMoney = GetScriptParameterInt(&lss);
	newMoney += profile->m_nMoney_0xe58;
	profile->m_nMoney_0xe58 = newMoney;

	uint local_24 = 0xBDF;
	//PostEvent_(newMoney, &local_24, 0);
	lua_pushnumber(L, profile->m_nMoney_0xe58);
	return 1;
}

static int __fastcall SubtractMoneyCarsForReal(int cost, PlayerProfile* in_EAX)
{
	int newBalance = in_EAX->m_nMoney_0xe58 - cost;
	// Some kind of moneySpent property?
	//in_EAX->uint_0xef8 += cost;
	in_EAX->m_nMoney_0xe58 = newBalance;

	uint local_24 = 0xBDF;
	//PostEvent_(cost, &local_24, 0);

	return newBalance;
}

static int PlayerProfile_SubtractMoneyCars(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	int cost = GetScriptParameterInt(&lss);
	int newBalance = SubtractMoneyCarsForReal(cost, *data);
	lua_pushnumber(L, (lua_Number)newBalance);

	return 1;
}

static int __fastcall SubtractMoneyUpgradesForReal(uint cost, PlayerProfile* in_EAX)
{
	int newBalance = in_EAX->m_nMoney_0xe58 - cost;
	//in_EAX->uint_0xefc += cost;
	in_EAX->m_nMoney_0xe58 = newBalance;

	uint local_24 = 0xBDF;
	//PostEvent_(cost, &local_24, 0);

	return newBalance;
}

static int PlayerProfile_SubtractMoneyUpgrades(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	int cost = GetScriptParameterInt(&lss);
	int newBalance = SubtractMoneyUpgradesForReal(cost, *data);
	lua_pushnumber(L, (lua_Number)newBalance);

	return 1;
}

static void __stdcall PlayerProfile_UnlockClassLevelsForReal(PlayerProfile* profile, int param_2, register int in_EAX)
{
	int iVar4 = param_2;
	// Ghidra's version isn't very good, I translated this part myself
	// EAX *= 0x38;
	// ECX = param_2 * 0xF0;
	// ECX = &(profile + ECX);
	// EAX = &ECX[EAX - 1]
}

static int PlayerProfile_UnlockClassLevels(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	auto profile = *data;
	LuaStateStruct lss{ L, 2 };
	int indexMaybe = GetScriptParameterInt(&lss);
	PlayerProfile_UnlockClassLevelsForReal(profile, indexMaybe, 1);
	return 0;
}

static BOOL _stdcall PlayerProfile_CanBuyCarFromClassForReal(int carClass, register PlayerProfile* profile_EDI)
{
	char buffer[256];
	int numCars = profile_EDI->m_sGarage_0x3c4.m_nNumCars_0x4;

	if (numCars > 0)
	{
		BYTE* classes = profile_EDI->m_sGarage_0x3c4.pCarClasses_0xc;
		int i = 0;
		do
		{
			if (classes[i] == carClass)
			{
				// At this point it checks if you have enough money to buy it, but I don't have PropertyDb implemented
				return TRUE;
			}
		} while (++i < numCars);
	}

	return FALSE;
}

static int PlayerProfile_CanBuyCarFromClass(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	LuaStateStruct lss{ L, 2 };
	int classMaybe = GetScriptParameterInt(&lss);
	lua_pushboolean(L, PlayerProfile_CanBuyCarFromClassForReal(classMaybe, *data));
	return 1;
}

static int PlayerProfile_SetDifficulty(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	auto profile = *data;

	LuaStateStruct lss{ L, 2 };
	int newDifficulty = GetScriptParameterInt(&lss);
	profile->m_bDifficulty_0xe54 = (BYTE)newDifficulty;

	return 0;
}

static int PlayerProfile_GetName(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");
	PlayerProfile* profile = *data;

	int length = WString_GetLength(profile->m_sProfileName_0xe34);
	lua_pushlstring(L, (char*)profile->m_sProfileName_0xe34, length * 2 + 2);
	return 1;
}

static int PlayerProfile_SetName(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	wchar_t* newName = (wchar_t*)lua_tolstring(L, 2, NULL);

	int i = 0;
	if (*newName)
	{
		wchar_t* writePtr = profile->m_sProfileName_0xe34;
		do
		{
			*writePtr = *newName;
			i++;
			writePtr++;
		} while (*newName);
	}
	profile->m_sProfileName_0xe34[i] = NULL;

	return 0;
}

static int PlayerProfile_GetActiveCup(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	uint index;
	if ((*data)->m_bActiveEvent_0xe60 < 128)
		index = (*data)->m_bActiveEvent_0xe60;
	else
		index = 0;

	lua_pushnumber(L, (lua_Number)index);
	return 1;
}

static int PlayerProfile_SetActiveCup(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");
	auto profile = *data;

	LuaStateStruct lss{ L, 2 };
	profile->m_bActiveEvent_0xe60 = GetScriptParameterInt(&lss);

	return 0;
}

static int PlayerProfile_GetActiveEvent(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	int index;
	if ((*data)->m_bActiveEvent_0xe60 < 128)
		index = 0;
	else
		index = (*data)->m_bActiveEvent_0xe60 - 127;

	lua_pushnumber(L, (lua_Number)index);
	return 1;
}

static int PlayerProfile_SetActiveEvent(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	LuaStateStruct lss{ L, 2 };
	int eventIndex = GetScriptParameterInt(&lss);
	profile->m_bActiveEvent_0xe60 = eventIndex + 127;
	return 0;
}

static int PlayerProfile_IsAutosaveEnabled(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");
	lua_pushboolean(L, (*data)->m_bAutosaveEnabled_0xedc);
	return 1;
}

static int PlayerProfile_SetAutosaveEnabled(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;

	if (lua_type(L, 2) == LUA_TNIL)
	{
		profile->m_bAutosaveEnabled_0xedc = FALSE;
		return 0;
	}

	if (lua_isnumber(L, 2))
	{
		LuaStateStruct lss{ L, 2 };
		profile->m_bAutosaveEnabled_0xedc = GetScriptParameterInt(&lss);
		return 0;
	}

	profile->m_bAutosaveEnabled_0xedc = lua_toboolean(L, 2);
	return 0;
}

static int PlayerProfile_GetNumCupRestart(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");
	lua_pushnumber(L, (lua_Number)(*data)->m_nNumCupRestarts_0xf14);
	return 1;
}

static int PlayerProfile_GetNumRagdolled(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_nNumTimesRagdolled_0xf18);
	return 1;
}

static int PlayerProfile_IsCareerWelcome1Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushboolean(L, (*data)->m_bCareerWelcome1Displayed_0xee4);
	return 1;
}

static int PlayerProfile_IsCareerWelcome2Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushboolean(L, (*data)->m_bCareerWelcome2Displayed_0xee8);
	return 1;
}

static int PlayerProfile_IsCareerWelcome3Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");
	lua_pushboolean(L, (*data)->m_bCareerWelcome3Displayed_0xeec);
	return 1;
}

static int PlayerProfile_SetCareerWelcome1Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	auto profile = *data;
	if (lua_type(L, 2) == LUA_TNIL)
	{
		profile->m_bCareerWelcome1Displayed_0xee4 = FALSE;
		return 0;
	}

	LuaStateStruct lss{ L, 2 };
	if (lua_isnumber(L, 2))
	{
		profile->m_bCareerWelcome1Displayed_0xee4 = (BOOL)(bool)GetScriptParameterInt(&lss);
		return 0;
	}

	profile->m_bCareerWelcome1Displayed_0xee4 = lua_toboolean(L, 2);
	return 0;
}

static int PlayerProfile_SetCareerWelcome2Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	auto profile = *data;
	if (lua_type(L, 2) == LUA_TNIL)
	{
		profile->m_bCareerWelcome2Displayed_0xee8 = FALSE;
		return 0;
	}

	LuaStateStruct lss{ L, 2 };
	if (lua_isnumber(L, 2))
	{
		profile->m_bCareerWelcome2Displayed_0xee8 = (BOOL)(bool)GetScriptParameterInt(&lss);
		return 0;
	}

	profile->m_bCareerWelcome2Displayed_0xee8 = lua_toboolean(L, 2);
	return 0;
}

static int PlayerProfile_SetCareerWelcome3Displayed(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	auto profile = *data;
	if (lua_type(L, 2) == LUA_TNIL)
	{
		profile->m_bCareerWelcome3Displayed_0xeec = FALSE;
		return 0;
	}

	LuaStateStruct lss{ L, 2 };
	if (lua_isnumber(L, 2))
	{
		profile->m_bCareerWelcome3Displayed_0xeec = (BOOL)(bool)GetScriptParameterInt(&lss);
		return 0;
	}

	profile->m_bCareerWelcome3Displayed_0xeec = lua_toboolean(L, 2);
	return 0;
}

static int PlayerProfile_GetTotalRagdollFlyDistance(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushnumber(L, (lua_Number)(int)(long long)roundf((*data)->m_fTotalRagdollFlyDistance_0xf1c));
	return 1;
}

static int PlayerProfile_GetGender(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_bFemale_0xe31);
	return 1;
}

static int PlayerProfile_SetGender(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	LuaStateStruct lss{ L, 2 };
	int bFemale = GetScriptParameterInt(&lss);
	profile->m_bFemale_0xe31 = bFemale;
	return 0;
}

static int PlayerProfile_SetSuit(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	LuaStateStruct lss{ L, 2 };
	profile->m_bSuit_0xe33 = (BYTE)GetScriptParameterInt(&lss);
	return 0;
}

static int PlayerProfile_GetHelmet(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	lua_pushnumber(L, (*data)->m_bHelmet_0xe32);
	return 1;
}

static int PlayerProfile_SetHelmet(lua_State* L)
{
	luaboilerplate_checkudata(1, PlayerProfile*, "PlayerProfile");

	PlayerProfile* profile = *data;
	LuaStateStruct lss{ L, 2 };
	profile->m_bHelmet_0xe32 = GetScriptParameterInt(&lss);
	return 0;
}

luaL_Reg MappedTable_00697158[79] = {
	//{ "StartCareer", PlayerProfile_StartCareer },
	{ "GetName", PlayerProfile_GetName },
	{ "SetName", PlayerProfile_SetName },
	{ "GetGender", PlayerProfile_GetGender },
	{ "SetGender", PlayerProfile_SetGender },
	//{ "GetHelmet", PlayerProfile_GetHelmet },
	{ "SetHelmet", PlayerProfile_SetHelmet },
	//{ "GetSuit", PlayerProfile_GetSuit },
	{ "SetSuit", PlayerProfile_SetSuit },
	//{ "GetDifficulty", PlayerProfile_GetDifficulty },
	{ "SetDifficulty", PlayerProfile_SetDifficulty },
	{ "GetMoney", PlayerProfile_GetMoney },
	{ "SetMoney", PlayerProfile_SetMoney },
	{ "AddMoney", PlayerProfile_AddMoney },
	{ "SubtractMoneyCars", PlayerProfile_SubtractMoneyCars },
	{ "SubtractMoneyUpgrades", PlayerProfile_SubtractMoneyUpgrades },
	//{ "Defaults", PlayerProfile_StartCareer },
	{ "EnoughMoney", PlayerProfile_EnoughMoney },
	{ "CanBuyCarFromClass", PlayerProfile_CanBuyCarFromClass },
	{ "SetName", PlayerProfile_SetName },
	//{ "GetLevelPosition", PlayerProfile_GetLevelPosition },
	//{ "SetLevelPosition", PlayerProfile_SetLevelPosition },
	//{ "IsLevelLocked", PlayerProfile_IsLevelLocked },
	//{ "SetLevelLocked", PlayerProfile_SetLevelLocked },
	//{ "IsClassLocked", PlayerProfile_IsClassLocked },
	//{ "SetClassLocked", PlayerProfile_SetClassLocked },
	//{ "IsSubClassLocked", PlayerProfile_IsSubClassLocked },
	//{ "GetCupPosition", PlayerProfile_GetCupPosition },
	//{ "SetCupPosition", PlayerProfile_SetCupPosition },
	//{ "IsCupLocked", PlayerProfile_IsCupLocked },
	//{ "SetCupLocked", PlayerProfile_SetCupLocked },
	//{ "GetEventPosition", PlayerProfile_GetEventPosition },
	//{ "SetEventPosition", PlayerProfile_SetEventPosition },
	//{ "IsEventLocked", PlayerProfile_IsEventLocked },
	//{ "SetEventLocked", PlayerProfile_SetEventLocked },
	//{ "GetCupSubClass", PlayerProfile_GetCupSubClass },
	//{ "GetEventSubClass", PlayerProfile_GetEventSubClass },
	//{ "GetWorstSubClassPosition", PlayerProfile_GetWorstSubClassPosition },
	//{ "ResetActiveCup", PlayerProfile_ResetActiveCup },
	//{ "GetNumDrivers", PlayerProfile_GetNumDrivers },
	//{ "GetNumClasses", PlayerProfile_GetNumClasses },
	//{ "GetNumCups", PlayerProfile_GetNumCups },
	//{ "GetNumEvents", PlayerProfile_GetNumEvents },
	//{ "GetNumTotalCups", PlayerProfile_GetNumTotalCups },
	//{ "GetNumTotalEvents", PlayerProfile_GetNumTotalEvents },
	//{ "GetNumTotalLevels", PlayerProfile_GetNumTotalLevels },
	//{ "IsCarSelected", PlayerProfile_IsCarSelected },
	//{ "GetActiveCar", PlayerProfile_GetActiveCar },
	//{ "SetActiveCar", PlayerProfile_SetActiveCar },
	//{ "GetActiveClass", PlayerProfile_GetActiveClass },
	//{ "SetActiveClass", PlayerProfile_SetActiveClass },
	{ "GetActiveCup", PlayerProfile_GetActiveCup },
	{ "SetActiveCup", PlayerProfile_SetActiveCup },
	{ "GetActiveEvent", PlayerProfile_GetActiveEvent },
	{ "SetActiveEvent", PlayerProfile_SetActiveEvent },
	//{ "GetPreviousRaceClass", PlayerProfile_GetPreviousRaceClass },
	//{ "GetPreviousRaceCup", PlayerProfile_GetPreviousRaceCup },
	//{ "GetPreviousRaceEvent", PlayerProfile_GetPreviousRaceEvent },
	//{ "GetPreviousRaceIndex", PlayerProfile_GetPreviousRaceIndex },
	{ "IsAutosaveEnabled", PlayerProfile_IsAutosaveEnabled },
	{ "SetAutosaveEnabled", PlayerProfile_SetAutosaveEnabled },
	//{ "GetAutosaveSlot", PlayerProfile_GetAutosaveSlot },
	//{ "SetAutosaveSlot", PlayerProfile_SetAutosaveSlot },
	{ "UnlockClassLevels", PlayerProfile_UnlockClassLevels },
	//{ "GetMoneySpentCars", PlayerProfile_GetMoneySpentCars },
	//{ "GetMoneySpentUpgrades", PlayerProfile_GetMoneySpentUpgrades },
	//{ "GetNumGoldPosition", PlayerProfile_GetNumGoldPosition },
	//{ "GetNumSilverPosition", PlayerProfile_GetNumSilverPosition },
	//{ "GetNumBronzePosition", PlayerProfile_GetNumBronzePosition },
	//{ "GetAverageRaceRank", PlayerProfile_GetAverageRaceRank },
	{ "GetNumCupRestart", PlayerProfile_GetNumCupRestart },
	{ "GetNumRagdolled", PlayerProfile_GetNumRagdolled },
	{ "GetTotalRagdollFlyDistance", PlayerProfile_GetTotalRagdollFlyDistance },
	{ "IsCareerWelcome1Displayed", PlayerProfile_IsCareerWelcome1Displayed },
	{ "IsCareerWelcome2Displayed", PlayerProfile_IsCareerWelcome2Displayed },
	{ "IsCareerWelcome3Displayed", PlayerProfile_IsCareerWelcome3Displayed },
	{ "SetCareerWelcome1Displayed", PlayerProfile_SetCareerWelcome1Displayed },
	{ "SetCareerWelcome2Displayed", PlayerProfile_SetCareerWelcome2Displayed },
	{ "SetCareerWelcome3Displayed", PlayerProfile_SetCareerWelcome3Displayed },
};

int Garage_GetFunnyCarCarIndex(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;

	LuaStateStruct lss{ L, 2 };
	int skipAmount = GetScriptParameterInt(&lss);

	int numCars = garage->m_nNumCars_0x4;
	int skipped = 0;
	int i = 0;
	if (numCars > 0)
	{
		do
		{
			if (garage->pCarClasses_0xc[i] == 101)
			{
				if (skipped == skipAmount)
					goto GetFunnyCarCarIndex_Exit;

				skipped++;
			}
		} while (++i < numCars);
	}
	i = -1;

GetFunnyCarCarIndex_Exit:
	lua_pushnumber(L, i);
	return 1;
}

int Garage_GetNumUpgrades(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, 128.0f);
	return 1;
}

int Garage_GetNumCars(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, (lua_Number)(*data)->m_nNumCars_0x4);
	return 1;
}

int Garage_GetNumFunnyCars(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, (lua_Number)(*data)->m_nNumFunnyCars_0x8);
	return 1;
}

static int Garage_GetCarOwned(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, (lua_Number)(*data)->nCarsOwned_0x64);
	return 1;
}

static int Garage_GetNumCarsPurchased(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	int purchased = 0;
	int numCars = (*data)->m_nNumCars_0x4;
	if (numCars > 0)
	{
		// I guess that's one way to go through the array
		BOOL* ptr = &(*data)->pDatabase_0x54[0].bOwned_0x4;
		do
		{
			if (*ptr)
				purchased++;

			// Oh hey, it let me do += sizeof(), I don't know what happened last time
			ptr += sizeof(CarDatabaseItem);
		} while (--numCars);
	}

	lua_pushnumber(L, (lua_Number)purchased);
	return 1;
}

int Garage_GetCarUpgradesValue(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushnumber(L, garage->pDatabase_0x54[index].nMoneySpentUpgrades_0x1c);
	return 1;
}

static int Garage_SetCarUpgradesValue(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int carIndex = GetScriptParameterInt(&lss);
	lss = { L, 3 };
	int upgradesValue = GetScriptParameterInt(&lss);

	garage->pDatabase_0x54[carIndex].nMoneySpentUpgrades_0x1c = upgradesValue;
	return 0;
}

static int Garage_AddCarUpgradesValue(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int carIndex = GetScriptParameterInt(&lss);
	lss = { L, 3 };

	garage->pDatabase_0x54[carIndex].nMoneySpentUpgrades_0x1c += GetScriptParameterInt(&lss);

	lua_pushnumber(L, garage->pDatabase_0x54[carIndex].nMoneySpentUpgrades_0x1c);
	return 1;
}

static int Garage_GetDistanceTravelled(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, (lua_Number)(int)(long long)roundf((*data)->fCareerOdometer_0x60 * 0.01f));
	return 1;
}

static int Garage_GetCarClass(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushnumber(L, (lua_Number)garage->pCarClasses_0xc[index]);
	return 1;
}

static int Garage_GetCarAIClass(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushnumber(L, garage->pAIClasses_0x18[index]);
	return 1;
}

static int Garage_GetCarSkinIndex(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushnumber(L, (lua_Number)garage->pDatabase_0x54[index].nSkinIndex_0x8);
	return 1;
}

static int Garage_SetCarSkinIndex(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int carIndex = GetScriptParameterInt(&lss);
	lss = { L, 3 };
	int skinIndex = GetScriptParameterInt(&lss);

	garage->pDatabase_0x54[carIndex].nSkinIndex_0x8 = skinIndex;
	return 0;
}

static int Garage_GetCarUnlocked(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	lua_pushnumber(L, (lua_Number)(*data)->nCarsUnlocked_0x68);
	return 1;
}

static int Garage_IsCarLocked(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushboolean(L, garage->pDatabase_0x54[index].bLocked_0x0);
	return 1;
}

static int Garage_IsCarPurchased(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);

	lua_pushboolean(L, garage->pDatabase_0x54[index].bOwned_0x4);
	return 1;
}

static int Garage_SetCarLocked(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	auto garage = *data;
	LuaStateStruct lss{ L, 2 };
	int index = GetScriptParameterInt(&lss);
	lss = { L, 3 };

	// The lua_type call stores its value in 'locked', so if the condition fails, it'll be LUA_TNIL / FALSE
	BOOL locked = FALSE;

	if (lua_type(L, 3) != LUA_TNIL)
	{
		if (!lua_isnumber(L, 3))
			locked = lua_toboolean(L, 3);
		else
			locked = (bool)GetScriptParameterInt(&lss);
	}

	auto entry = &garage->pDatabase_0x54[index];
	if (entry->bLocked_0x0 && !locked)
		garage->nCarsUnlocked_0x68++;

	entry->bLocked_0x0 = locked;
	return 0;
}

static BOOL __fastcall HasCarFromClassForReal(Garage* garage_ESI, int class_EBX)
{
	int i = 0;
	if (garage_ESI->m_nNumCars_0x4 > 0)
	{
		do
		{
			if ((garage_ESI->pCarClasses_0xc[i] == class_EBX) && garage_ESI->pDatabase_0x54[i].bOwned_0x4)
				return TRUE;

			i++;
		} while (i < garage_ESI->m_nNumCars_0x4);
	}
	return FALSE;
}

static int Garage_HasCarFromClass(lua_State* L)
{
	luaboilerplate_checkudata(1, Garage*, "Garage");

	LuaStateStruct lss{ L, 2 };
	lua_pushboolean(L, (bool)HasCarFromClassForReal(*data, GetScriptParameterInt(&lss)));
	return 1;
}

luaL_Reg luaL_Reg_ARRAY_00696ef8[] = {
	//{ "Defaults", Garage_Defaults },
	{ "GetNumCars", Garage_GetNumCars },
	{ "GetNumFunnyCars", Garage_GetNumFunnyCars },
	{ "GetNumUpgrades", Garage_GetNumUpgrades },
	{ "GetCarClass", Garage_GetCarClass },
	{ "GetCarAIClass", Garage_GetCarAIClass },
	{ "GetFunnyCarCarIndex", Garage_GetFunnyCarCarIndex },
	{ "IsCarLocked", Garage_IsCarLocked },
	{ "IsCarPurchased", Garage_IsCarPurchased },
	{ "GetCarSkinIndex", Garage_GetCarSkinIndex },
	//{ "IsCarUpgraded", Garage_IsCarUpgraded },
	//{ "IsCarUpgradeAvailable", Garage_IsCarUpgradeAvailable },
	//{ "IsCarUpgradeDisabled", Garage_IsCarUpgradeDisabled },
	//{ "GetCarValue", Garage_GetCarValue },
	{ "GetCarUpgradesValue", Garage_GetCarUpgradesValue },
	{ "HasCarFromClass", Garage_HasCarFromClass },
	{ "SetCarLocked", Garage_SetCarLocked },
	//{ "SetCarPurchased", Garage_SetCarPurchased },
	{ "SetCarSkinIndex", Garage_SetCarSkinIndex },
	//{ "SetCarUpgraded", Garage_SetCarUpgraded },
	{ "SetCarUpgradesValue", Garage_SetCarUpgradesValue },
	{ "AddCarUpgradesValue", Garage_AddCarUpgradesValue },
	{ "GetNumCarsPurchased", Garage_GetNumCarsPurchased },
	//{ "GetMaxUpgradeGroupLevel", Garage_GetMaxUpgradeGroupLevel },
	{ "GetDistanceTravelled", Garage_GetDistanceTravelled },
	{ "GetCarOwned", Garage_GetCarOwned },
	{ "GetCarUnlocked", Garage_GetCarUnlocked },
	//{ "GetCarPerformanceLevel", Garage_GetCarPerformanceLevel },
	//{ "GetCarPerformanceLevelFromProfile", Garage_GetCarPerformanceLevelFromProfile },
	//{ "GetCarPerformanceLevelFromProfileWithUpgrades", Garage_GetCarPerformanceLevelFromProfileWithUpgrades }
};

static int ButtonBar_EnableMovement(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	(*data)->bEnableMovement_0x174 = TRUE;
	return 0;
}

static int ButtonBar_DisableMovement(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	(*data)->bEnableMovement_0x174 = FALSE;
	return 0;
}

static int ButtonBar_GetFirstEmptySlot(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	lua_pushnil(L);
	return 1;
}

static inline int ButtonBar_NumButtons(ButtonBar* buttonBar)
{
	return ((int)buttonBar->pNextButton_0x190 - (int)buttonBar->pButtons_0x18c) >> 2;
}

static int ButtonBar_GetNumButtons(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	lua_pushnumber(L, ButtonBar_NumButtons(*data));
	return 1;
}

static int ButtonBar_GetNumSlots(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	lua_pushnumber(L, (lua_Number)(*data)->nNumSlots_0x164);
	return 1;
}

static int ButtonBar_GetNumVisibleButtons(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	lua_pushnumber(L, 0.0);
	return 1;
}

static int ButtonBar_GetSelectedButton(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	lua_pushnumber(L, (lua_Number)(*data)->nSelectedButton_0x19c);
	return 1;
}

static int ButtonBar_HighlightSelectedSlot(lua_State* L)
{
	luaboilerplate_touserdata(1, ButtonBar*, "ButtonBar");

	auto buttonBar = *data;
	int num = (int)(long long)roundf(luaL_checknumber(L, 2));
	//buttonBar->int_0x170 = num;
	if (!num)
	{
		if (buttonBar->nSelectedButton_0x19c < ButtonBar_NumButtons(buttonBar) && buttonBar->pButtons_0x18c[buttonBar->nSelectedButton_0x19c])
			buttonBar->pButtons_0x18c[buttonBar->nSelectedButton_0x19c]->pActualButton_0x8->vftable_0x0[39]();
	}
	return 0;
}

int __fastcall ButtonBar_GetIndexFromIDMaybe(ButtonBar* buttonBar, int IDMaybe)
{
	ButtonStruct** buttons = buttonBar->pButtons_0x18c;
	int i = 0;
	if (ButtonBar_NumButtons(buttonBar) > 0)
	{
		do
		{
			if ((*buttons)->pActualButton_0x8->nIDMaybe_0x164 == IDMaybe)
				return i;

			i++;
			buttons += sizeof(ButtonStruct*);
		} while (i < ButtonBar_NumButtons(buttonBar));
	}

	return 0;
}


void __fastcall GetLuaClassMaybe(char* name_EAX, lua_State* L_ESI)
{
	if (!name_EAX)
	{
		lua_setglobal(L_ESI, "Class name not given!");
		lua_error(L_ESI);
	}

	lua_createtable(L_ESI, 0, 0);
	int classIndex = lua_gettop(L_ESI);

	luaL_newmetatable(L_ESI, name_EAX);
	int tableIndex = lua_gettop(L_ESI);

	lua_pushlstring(L_ESI, "__index", 7);
	lua_pushvalue(L_ESI, classIndex);

	lua_settable(L_ESI, tableIndex);

	lua_pushlstring(L_ESI, "__newindex", 10);
	lua_pushvalue(L_ESI, classIndex);

	lua_settable(L_ESI, tableIndex);

	lua_settop(L_ESI, -3);
}

ScriptHost* g_pScriptHost_008e8418;

void CalledWhenReloadingMenus()
{
	lua_State* L = g_pScriptHost_008e8418->stateStruct_0x8->L_0x4;

	// Sets the PlayersList string

	GetLuaClassMaybe((char*)"PlayersList", L);

	lua_getfield(L, LUA_REGISTRYINDEX, "PlayersList");
	int index = lua_gettop(L);

	lua_pushlstring(L, "__index", 7);
	lua_rawget(L, index);
	luaL_openlib(L, NULL, luaL_Reg_ARRAY_00697ff0, 0);
	lua_settop(L, -3);
}

int getplatform(lua_State* L)
{
	lua_pushlstring(L, "PC", 2);
	return 1;
}

// My guess is that on the PS2 you had to submit a save operation, and then wait for it to finish
// but there's no such thing on the PC so it just always returns true
bool SaveOperationDoneYet()
{
	return true;
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

int SignalDeviceChanged(lua_State* L)
{
	//FileObject_DoNothing();
	return 0;
}


/*
int DeleteSave(lua_State* L)
{
	int saveIndex = (int)(long long)roundf(luaL_checknumber(L, 1));

	DeleteSaveForReal(1, saveIndex);

	// I'm guessing back on the PS2 you had to wait until that's done
	do; while (!SaveOperationDoneYet());

	g_pGameSettings_008e8410->bSaveGameInfoValid_0x44 = FALSE;

	// It's not a pointer, the array is in the struct.
	// Each item is 124 bytes large
	g_pGameSettings_008e8410->array_0xc0[saveIndex] = 0;
	g_pGameSettings_008e8410->array_0x48[saveIndex] = 0;
}
*/

int StartKickVote(lua_State* L)
{
	luaboilerplate_touserdata(1, void, "SessionClass");

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

// Left-over from the PS2 version, it still tries to call the formatting function, but it's been removed.
// If called it will mess up the CPU stack, since the current function will pop a parameter, but this code doesn't push one.
int FormatMemoryCard(lua_State* L)
{
	GameSettings* settings = g_pGameSettings_008e8410;

	((void (*)())FormatMemoryCardForRealMaybe)();
	//settings->field1088_0x44c = 7;
	return 0;
}

int SetGlobalFontScale(lua_State* L)
{
	g_GlobalFontScale_006993f8 = luaL_checknumber(L, 1);
	return 0;
}

const char* UserDataName_008e8488;

struct GUI
{
	BOOL bAllowCarRotate_0x58c;
};

// If either of them are nan, the condition becomes true even if they aren't equal
#define SafeEquals(a, b) isnan(b) || isnan(a) || a == b

static int AllowCarRotate(lua_State* L)
{
	luaboilerplate_checkudata(1, GUI*, "GUI");

	auto gui = *data;
	lua_Number num = luaL_checknumber(L, 2);

	// Another case of assuming it's a macro because I don't think they would intentionally write isnan(0)
	if (SafeEquals(num, 0.0))
	{
		gui->bAllowCarRotate_0x58c = TRUE;
		return 0;
	}

	gui->bAllowCarRotate_0x58c = FALSE;
	return 0;
}

LoadingBar* g_LoadingBar_008e8448;
uint UINT_008e8444;

void InitLoadingBar()
{
	if (!g_LoadingBar_008e8448 && !UINT_008e8444)
	{
		LoadingBar* bar = (LoadingBar*)malloc(sizeof(LoadingBar));
		if (bar)
		{
			//g_LoadingBar_008e8448 = LoadingBar_LoadingBar(bar);
			UINT_008e8444++;
			return;
		}
		g_LoadingBar_008e8448 = NULL;
	}

	// Does this mean if it fails to allocate, it won't be able to create another one?
	UINT_008e8444++;
}

// The register keyword doesn't actually do anything anymore, because it's already applied to everything.
// But I'm still leaving them in, so it should work with an older compiler.
void AddToLoadingBar(lua_Number progress, register LoadingBar* loadingBar_unaff_ESI)
{
	loadingBar_unaff_ESI->vftable_0x2c0[1]();
	int iVar1 = ((int (*)())loadingBar_unaff_ESI->vftable_0x2c0[4])();

	float newProgress = loadingBar_unaff_ESI->progress_0x210 + progress;
	loadingBar_unaff_ESI->progress_0x210 = newProgress;

	if ((loadingBar_unaff_ESI->int_0x2f4 || loadingBar_unaff_ESI->index_0xc) && (iVar1 - loadingBar_unaff_ESI->int_0x2f4) < 40)
		return;

	loadingBar_unaff_ESI->int_0x2f4 = iVar1;
	if (newProgress >= 1.0f)
		loadingBar_unaff_ESI->progress_0x210 = 1.0f;

	//FUN_0057cd90(iVar1, loadingBar_unaff_ESI->float_array2_0x110[loadingBar_unaff_ESI->index_0xc] * loadingBar_unaff_ESI->progress_0x210 + loadingBar_unaff_ESI->float_array1_0x10[]);
}


static int UpdateLoadingBar(lua_State* L)
{
	if (g_LoadingBar_008e8448)
		AddToLoadingBar(luaL_checknumber(L, 1), g_LoadingBar_008e8448);

	return 0;
}

sVehicle* Car_Car(sVehicle* vehicle, Player* player, uint flags, int param_4)
{
	return vehicle;
}

uint UINT_006b21d8;
Player* PTR_006b21f8[1]; // I don't know how large the array is
uchar UCHAR_008da516;

void Player_AddCar(Player* player, char param_2, register LoadingBar* unaff_EBX)
{
	sVehicle* newCar;

	if (!player->m_pVehicle_0x33c)
	{
		uint flags = 0;
		if (player->m_nPlayerType_0x36c == PLAYER_LOCAL)
		{
			if (!UCHAR_008da516)
			{
				// It multiplies the index by 7, I'm guessing either it's an array of PlayerArrays, or a new structure
				PTR_006b21f8[UINT_006b21d8 * 7] = player;
				UINT_006b21d8++;
			}

			flags = 1;
			if (!player->m_nSkin_0x344)
				player->m_nSkin_0x344 = 1;
		}

		if (!param_2)
			flags |= 0x40;

		if (player->m_nUnknown_0x388)
			flags |= 0x10;

		newCar = (sVehicle*)malloc(sizeof(sVehicle));
		if (!newCar)
			newCar = NULL;
		else
			newCar = Car_Car(newCar, player, flags, (int)unaff_EBX);

		int iVar1 = player->m_nUnknown_0x4e8;
		bool godMode = player->m_bGodMode_0x348;
		newCar->m_pPlayer = player;
		newCar->m_bGodMode = godMode;

		//FUN_0042eff0(unaff_EBX);

		//FUN_00423a00();
		if (unaff_EBX)
			AddToLoadingBar(0.05, unaff_EBX);

		//FUN_00477c20();
		if (unaff_EBX)
			AddToLoadingBar(0.05, unaff_EBX);

	}
}

int StartGame(lua_State* L)
{
	//StartGameForReal(L, g_pGameSettings_008e8410);
	return 0;
}

int IsGameStarted2(lua_State* L)
{
	lua_pushboolean(L, g_pGameSettings_008e8410->m_bStarted_0xa0c);
	return 1;
}

int CableDisconnected(lua_State* L)
{
	lua_pushboolean(L, FALSE);
	return 1;
}

/////////////////////////////////////////////////
//
// Startup Sequence
// 
/////////////////////////////////////////////////

#define VERSION_EUROPE 0
#define VERSION_US 1
#define VERSION_GERMANY 2
// Germany got its own version (after doing some more research and looking at the game files, I see they had to censor it over there.)
// Looks like I've got the European version
uint version_0069c13c = VERSION_EUROPE;
// I don't know if it's possible to change the value fast enough that the german intro video plays, but you can wait on the title screen to see the german version of the attract video.
// If set to Germany in a US or European copy, the game will crash when loading into a map because it can't find the ragdoll models.

// There's already a function that is internally called StartGame so I had to change this one
void StartStartingGame(int param_1)
{
	const char* version_string;
	lua_State* L = g_pScriptHost_008e8418->stateStruct_0x8->L_0x4;
	int originalTop = lua_gettop(L);

	// So glad they used text
	if (version_0069c13c == VERSION_US)
	{
		version_string = "VERSION_US";
	}
	else if (version_0069c13c == VERSION_GERMANY)
	{
		version_string = "VERSION_GERMANY";
	}
	else
	{
		version_string = "VERSION_EUROPE";
	}

	lua_setglobal(L, version_string);

	lua_pushboolean(L, TRUE);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushcclosure(L, StartGame, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "StartGame");

	lua_pushcclosure(L, IsGameStarted2, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "IsGameStarted");

	/*
	lua_pushcclosure(L, LoadReplay, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "LoadReplay");

	lua_pushcclosure(L, SaveReplay, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "SaveReplay");
	*/

	lua_pushcclosure(L, DEBUGLOG, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "DebugConsolePrint");

	lua_pushcclosure(L, GetPaletteColour, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "GetPaletteColor");

	//lua_pushcclosure(L, UpdateLoadingBar, 0);
	//lua_setfield(L, LUA_GLOBALSINDEX, "UpdateLoadingBar");

	lua_setglobal(L, "CompileDate");
	lua_setglobal(L, "Version 0.28 build 2004.09.20");
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_pushcclosure(L, GetPhrase, 0);
	lua_setfield(L, LUA_GLOBALSINDEX, "GetPhrase");

	lua_createtable(L, 0, 0);
	int idx = lua_gettop(L);
	lua_setglobal(L, "GameFlow");

	lua_pushvalue(L, idx);
	lua_settable(L, LUA_GLOBALSINDEX);

	/*
	lua_setglobal(L, "PrepareCupFromProfile");
	lua_pushcclosure(L, PrepareCupFromProfile, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetNumResults");
	lua_pushcclosure(L, GetNumResults, 0);
	lua_settable(L, idx);
	*/

	lua_setglobal(L, "GetPlayerName");
	lua_pushcclosure(L, GetPlayerName, 0);
	lua_settable(L, idx);

	/*
	lua_setglobal(L, "GetPlayerPosition");
	lua_pushcclosure(L, GetPlayerPosition, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetPlayerIdByPosition");
	lua_pushcclosure(L, GetPlayerIdByPosition, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetPlayerRacePoints");
	lua_pushcclosure(L, GetPlayerRacePoints, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "ClearRace");
	lua_pushcclosure(L, ClearRace, 0);
	lua_settable(L, idx);
	*/
	lua_setglobal(L, "IsCupRaceLocked");
	lua_pushcclosure(L, IsCupRaceLocked, 0);
	lua_settable(L, idx);
	/*
	lua_setglobal(L, "GetStuntScoreType");
	lua_pushcclosure(L, GetStuntScoreType, 0);
	lua_settable(L, idx);
	*/
	lua_setglobal(L, "GetCupSize");
	lua_pushcclosure(L, GetCupSize, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "IsCupActive");
	lua_pushcclosure(L, IsCupActive, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "IsCupRaceCompleted");
	lua_pushcclosure(L, IsCupRaceCompleted, 0);
	lua_settable(L, idx);

	/*
	lua_setglobal(L, "IsCupFinished");
	lua_pushcclosure(L, IsCupFinished, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "ClearCup");
	lua_pushcclosure(L, ClearCup, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetPlayerCupPoints");
	lua_pushcclosure(L, GetPlayerCupPoints, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetPlayerCupRacePosition");
	lua_pushcclosure(L, GetPlayerCupRacePosition, 0);
	lua_settable(L, idx);
	*/

	lua_setglobal(L, "GM_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_CAREER");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_TIMEATTACK");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_SINGLE_RACE");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_INSTANT_ACTION");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_CRASHTEST_DUMMY");
	lua_pushnumber(L, 5.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_ONLINE_MULTIPLAYER");
	lua_pushnumber(L, 6.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_PARTY");
	lua_pushnumber(L, 7.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_DEVELOPER");
	lua_pushnumber(L, 8.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_TOURNAMENT");
	lua_pushnumber(L, 9.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_SPLITSCREEN");
	lua_pushnumber(L, 10.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GM_TEST");
	lua_pushnumber(L, 11.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "GR_DEFAULT");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_RACE");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_STUNT");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_DERBY");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_HUNTER_PREY");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_ARCADE_ADVENTURE");
	lua_pushnumber(L, 5.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_PONGRACE");
	lua_pushnumber(L, 6.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_TIMEATTACK");
	lua_pushnumber(L, 7.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "GR_TEST");
	lua_pushnumber(L, 8.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "CLASS_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CLASS_C");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CLASS_B");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CLASS_A");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CLASS_FINALS");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CLASS_EXTRA");
	lua_pushnumber(L, 5.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "RESULT_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "RESULT_ABORTED");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "RESULT_FINISHED");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "STUNT_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_CURLING");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BULLSEYE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_HIGHJUMP");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_STONESKIPPING");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_RINGOFFIRE");
	lua_pushnumber(L, 5.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_DARTS");
	lua_pushnumber(L, 6.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BREAKDOWN");
	lua_pushnumber(L, 7.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BLACKDANNY");
	lua_pushnumber(L, 8.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_SKIJUMP");
	lua_pushnumber(L, 9.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_FIELDGOAL");
	lua_pushnumber(L, 10.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BOWLING");
	lua_pushnumber(L, 11.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BASKETBALL");
	lua_pushnumber(L, 12.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_BASEBALL");
	lua_pushnumber(L, 13.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "STUNT_SOCCER");
	lua_pushnumber(L, 14.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "DERBY_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "DERBY_LMS");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "DERBY_WRECKING");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "DERBY_FRAG");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "DERBY_END");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "UPGRADE_DEFAULT");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "UPGRADE_NONE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "UPGRADE_50");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "UPGRADE_100");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "STUNTCAR_CLASS");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "FUNNYCAR_CLASS");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "PLAYERTYPE_UNKNOWN");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "PLAYERTYPE_LOCAL");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "PLAYERTYPE_REMOTE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "PLAYERTYPE_OBSERVER");
	lua_pushnumber(L, 3.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "PLAYERTYPE_AI");
	lua_pushnumber(L, 4.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "PLAYERTYPE_SIMULATED");
	lua_pushnumber(L, 5.f);
	lua_settable(L, LUA_GLOBALSINDEX);

	lua_setglobal(L, "CHARACTERTYPE_MALE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, LUA_GLOBALSINDEX);
	lua_setglobal(L, "CHARACTERTYPE_FEMALE");
	lua_pushnumber(L, 1.f);
	lua_settable(L, LUA_GLOBALSINDEX);


	//LoadAndSave(param_1);
	//RunLUAFromFile("data/Scripts/Levels.bed", auVar1);
	//RunLUAFromFile("data/Scripts/Classes.bed", auVar2);
	lua_settop(L, originalTop);
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
	AddLuaGlobal("SAVEFLOW_CHECKSAVEDEVICE", 6.0);

	//param_1->unkn_0x44c = 0;
	lua_settop(L, index);
}

void __stdcall LoadRaceInfo(int levelID, register GameSettings* raceInfo_EBX)
{
	ScriptHost* scriptHost = g_pScriptHost_008e8418;

	raceInfo_EBX->m_nGameRules_0x4ac = GR_DEFAULT;
	raceInfo_EBX->m_nStuntType_0x4b0 = STUNT_NONE;
	raceInfo_EBX->m_nDerbyType_0x4b4 = DERBY_NONE;
	raceInfo_EBX->m_pPositions_0x4b8 = NULL;
	raceInfo_EBX->m_bNitroRegen_0x4bc = FALSE;

	lua_State* L = scriptHost->stateStruct_0x8->L_0x4;
	int baseIndex = lua_gettop(L);

	lua_getfield(L, LUA_GLOBALSINDEX, "Levels");
	int levelIndex = lua_gettop(L);

	lua_rawgeti(L, levelIndex, levelID);
	levelIndex = lua_gettop(L);
	lua_setglobal(L, "Rules");

	lua_gettable(L, levelIndex);

	LuaStateStruct lss{ L, lua_gettop(L) };
	if (raceInfo_EBX->m_nGameRulesOverride_0x468 == GR_DEFAULT && lua_isnumber(L, lss.index_0x4))
		raceInfo_EBX->m_nGameRules_0x4ac = (GameRules)GetScriptParameterInt(&lss);
	else
		raceInfo_EBX->m_nGameRules_0x4ac = raceInfo_EBX->m_nGameRulesOverride_0x468;

	if (raceInfo_EBX->m_nGameRules_0x4ac == GR_STUNT)
	{
		lua_setglobal(L, "StuntType");
		lua_gettable(L, levelIndex);
		lss = { L, lua_gettop(L) };

		StuntType stuntID = (StuntType)GetScriptParameterInt(&lss);
		raceInfo_EBX->m_nStuntType_0x4b0 = stuntID;

		lua_setglobal(L, "StartPosition");
		lua_gettable(L, levelIndex);
		lss = { L, lua_gettop(L) };

		//raceInfo_EBX->m_pPositions_0x4b8 = GetScriptParameterInt(&lss);
	}

	if (raceInfo_EBX->m_nGameRules_0x4ac == GR_DERBY)
	{
		DerbyType derbyType = raceInfo_EBX->m_nDerbyTypeOverride_0x46c;
		if (derbyType == DERBY_NONE)
		{
			lua_setglobal(L, "DerbyType");
			lua_gettable(L, levelIndex);
			lss = { L, lua_gettop(L) };

			if (lua_type(L, lss.index_0x4) == LUA_TNIL)
			{
				raceInfo_EBX->m_nDerbyType_0x4b4 = DERBY_WRECKING;
				goto SkipSettingDerby;
			}
				
			derbyType = (DerbyType)GetScriptParameterInt(&lss);
		}

		raceInfo_EBX->m_nDerbyType_0x4b4 = derbyType;
	}

SkipSettingDerby:

	int numLaps;
	if (raceInfo_EBX->m_nNumLaps_0x488 < 1)
	{
		lua_setglobal(L, "Laps");
		lua_gettable(L, levelIndex);

		lss = { L, lua_gettop(L) };

		if (!lua_isnumber(L, lss.index_0x4))
			numLaps = 1;
		else
			numLaps = GetScriptParameterInt(&lss);

		raceInfo_EBX->m_nNumLaps_0x488 = numLaps;
	}

	int weather;

	lua_setglobal(L, "Weather");
	lua_gettable(L, levelIndex);

	lss = { L, lua_gettop(L) };

	if (!lua_isnumber(L, lss.index_0x4))
		weather = 1;
	else
		weather = GetScriptParameterInt(&lss);

	raceInfo_EBX->m_nWeather_0x484 = weather;

	BOOL nitroRegen;
	lua_setglobal(L, "NitroRegen");
	lua_gettable(L, levelIndex);

	lss = { L, lua_gettop(L) };
	
	if (lua_isnil(L, lss.index_0x4))
		nitroRegen = FALSE;
	else
		nitroRegen = GetScriptParameterBool(&lss);

	raceInfo_EBX->m_bNitroRegen_0x4bc = nitroRegen;

	lua_settop(L, baseIndex);
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

uint nextLuaId_008da690;

int getid(lua_State* L)
{
	char buffer[32];
	uint id = nextLuaId_008da690++;

	sprintf(buffer, "%x", id);
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

	lua_CFunction fn = ButtonBar_GetNumVisibleButtons;
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
	luaL_getmetafield(L, -2, "__luavars");
	lua_pushvalue(L, -2);
	lua_rawget(L, -2);
	lua_remove(L, -2);

	if (lua_type(L, -1) == LUA_TNIL)
	{
		lua_settop(L, -2);
		const char* string = luaL_checklstring(L, -1, NULL);

		//if (string != NULL)
			//FUN_00524ca0(L, UINT_008e8484, string, DAT_008e9960);
	}

	return 0;
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
	luaboilerplate_touserdata(1, void, "SessionClass");

	//lua_pushboolean(L, (piVar1->byte_0x216c & 0x20) >> 5);
	return 1;
}

static int TextChat_Update(lua_State* L)
{
	luaboilerplate_touserdata(1, TextChat*, "TextChat");

	LuaStateStruct lss{ L, 2 };
	GetScriptParameterInt(&lss);

	return 0;
}

static int TextChat_LineIsEmpty(lua_State* L)
{
	luaboilerplate_touserdata(1, TextChat*, "TextChat");

	TextChat* chat = *data;
	LuaStateStruct lss{ L, 2 };
	int iVar1 = GetScriptParameterInt(&lss);
	lua_pushboolean(L, (chat->nNumLines_0x0 <= iVar1 - 1));
	return 1;
}

int TextChat_IsTextUpdated(lua_State* L)
{
	luaboilerplate_touserdata(1, TextChat*, "TextChat");

	TextChat* chat = *data;
	lua_pushboolean(L, chat->bTextUpdated_0x16c4);
	chat->bTextUpdated_0x16c4 = false;
	return 1;
}

static int TextChat_GetNumLines(lua_State* L)
{
	luaboilerplate_touserdata(1, TextChat*, "TextChat");

	lua_pushnumber(L, (*data)->nNumLines_0x0);
	return 1;
}


BYTE byteArray_00652728[256] = {
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

void (*FUNC_008da6f4)();
MWFileObject* PTR_008da72c;
// 1 = delete bfs file on closing, 0 = normal
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
	bfsFile = ptr;

	// The hash size located 16 bytes from the start, and must be 997.
	// If it has to be a known value, why include it in the file? Some kind of anti-tamper?
	if (ReadAsInt(bfsFile, 0x10) != 0x3E5)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

	// Only included in fo2a.bfs, b and c's is empty
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

void (*PTR_FUN_FUN_008da6f0)() = (void(*)())0x0057CE70;

// I called this one 'Again', but couldn't find the original one
void __stdcall BFSReadOverlapAgain(register BfsManager* unaff_ESI)
{
	if (unaff_ESI->byte_0x64)
	{
		DWORD bytesTransferred;
		BOOL bVar1 = GetOverlappedResult(unaff_ESI->fileHandle_0x68, unaff_ESI->lpOverlapped_0x6c, &bytesTransferred, FALSE);

		while (true)
		{
			if (bVar1)
			{
				unaff_ESI->byte_0x64 = NULL;
				return;
			}

			DWORD err = GetLastError();
			if (err != ERROR_IO_INCOMPLETE) break;

			if (PTR_FUN_FUN_008da6f0)
				PTR_FUN_FUN_008da6f0();

			bVar1 = GetOverlappedResult(unaff_ESI->fileHandle_0x68, unaff_ESI->lpOverlapped_0x6c, &bytesTransferred, FALSE);
		}

		if (FUNC_008da6f4)
			FUNC_008da6f4();

		GetLastError();
		CreateErrorMessageAndDie("BFS: Fatal read I/O error (%d) when reading %d bytes from offset %d (overlapped result).");
	}
}


FontNames* g_fontNames_008e8434;

Font* GetFontPointer(FontNames* fonts, char* name)
{
	int i = 0;
	FontEntry* entry = fonts->entries_0x0;

	int sign;

	if (fonts->numEntries_0x140 > 0)
	{
		do
		{
			char* entryName = entry->name_0x0;
			char* stringptr = name;
			do
			{
				bool less = ((BYTE)*entryName < (BYTE)*stringptr);
				if (*entryName != *stringptr)
				{
				GetFontPointer_CheckSign:
					sign = less ? -1 : 1;
					goto GetFontPointer_NoMatch;
				}

				if (*entryName == NULL) break;

				// Is there a reason it checks 2 characters at a time? Maybe to save on iterations
				// If the string 
				less = ((BYTE)entryName[1] < (BYTE)stringptr[1]);
				if (entryName[1] != stringptr[1]) goto GetFontPointer_CheckSign;

				entryName += 2;
				stringptr += 2;
			} while (*entryName);

			sign = 0;

		GetFontPointer_NoMatch:
			// This check could be skipped if it was put before the label
			if (sign == 0)
				return fonts->entries_0x0[i].font_0x8;

			entry += sizeof(FontEntry);
		} while (++i < fonts->numEntries_0x140);
	}

	return NULL;
}

char g_CurrentTextureFolder_008d79a0[260];

void __stdcall SetCurrentTextureFolder(register char* path_EAX)
{
	if (path_EAX == NULL)
	{
		g_CurrentTextureFolder_008d79a0[0] = NULL;
		return;
	}

	int i;
	for (i = 0; i < 260; i++)
	{
		if (path_EAX[i] == NULL) break;
		g_CurrentTextureFolder_008d79a0[i] = tolower(path_EAX[i]);
	}

	if (i > 0)
	{
		if (g_CurrentTextureFolder_008d79a0[i - 1] != '/' && g_CurrentTextureFolder_008d79a0[i - 1] != '\\')
			g_CurrentTextureFolder_008d79a0[i++] = '/';

		g_CurrentTextureFolder_008d79a0[i] = NULL;
		return;
	}

	g_CurrentTextureFolder_008d79a0[0] = NULL;
}

// Same setup as the texture folder, I think this one's for model filenames
char g_CurrentGeometryFolder_008d7aa8[260];

// It's a duplicate of the SetCurrentTextureFolder function
void __stdcall SetCurrentGeometryFolder(register char* path_EAX)
{
	if (path_EAX == NULL)
	{
		g_CurrentGeometryFolder_008d7aa8[0] = NULL;
		return;
	}

	int i;
	for (i = 0; i < 260; i++)
	{
		if (path_EAX[i] == NULL) break;
		g_CurrentGeometryFolder_008d7aa8[i] = tolower(path_EAX[i]);
	}

	if (i > 0)
	{
		if (g_CurrentGeometryFolder_008d7aa8[i - 1] != '/' && g_CurrentGeometryFolder_008d7aa8[i - 1] != '\\')
			g_CurrentGeometryFolder_008d7aa8[i++] = '/';
	}

	// Here's a simplification I thought could be made, assuming 'i' can't be negative here
	// SetCurrentTextureFolder() has the original version of this code
	g_CurrentGeometryFolder_008d7aa8[i] = NULL;
}


void __stdcall Player_UpdatePositionAndVelocity(register Player* player_ESI)
{
	float prevPosX = player_ESI->m_vPosition_0x428.x;
	float prevPosY = player_ESI->m_vPosition_0x428.y;
	float prevPosZ = player_ESI->m_vPosition_0x428.z;

	float vehiclePosX = player_ESI->m_pVehicle_0x33c->m_vPosition.x;
	float vehiclePosZ = player_ESI->m_pVehicle_0x33c->m_vPosition.z;

	player_ESI->m_vPosition_0x428.x = vehiclePosX;
	player_ESI->m_vPosition_0x428.y = 0.0f;
	player_ESI->m_vPosition_0x428.z = vehiclePosZ;

	float distance;
	// It checks if GameSettings is an invalid value after it's already dereferenced it
	if (player_ESI->m_nPlayerType_0x36c == PLAYER_LOCAL && g_pGameSettings_008e8410->m_nGameMode_0x464 == GM_CAREER && (uint)g_pGameSettings_008e8410 != 0xFFFFF020)
	{
		if (prevPosX || prevPosY || prevPosZ)
		{
			float dx = vehiclePosX - prevPosX;
			float dz = vehiclePosZ - prevPosZ;

			distance = sqrtf((dx * dx) + (-prevPosY * -prevPosY) + (dz * dz));
		}
		else
			distance = 0.0f;

		g_pGameSettings_008e8410->m_pPlayerProfile_0xfe0.m_sGarage_0x3c4.fCareerOdometer_0x60 += distance;
	}


	sVehicle* car = player_ESI->m_pVehicle_0x33c;
	float atX = car->m_mMatrix.at.x;
	float atZ = car->m_mMatrix.at.z;
	if (fabs(car->m_mMatrix.at.y) >= 0.99)
	{
		atX = car->m_mMatrix.up.x;
		if (car->m_mMatrix.at.y < 0)
			atZ = car->m_mMatrix.up.z;
		else
		{
			atX = -atX;
			atZ = -car->m_mMatrix.up.z;
		}
	}

	float that = 1.0 / sqrtf(atX * atX + atZ * atZ);
	player_ESI->m_vPosition_0x428.pad = that * atX;
}
