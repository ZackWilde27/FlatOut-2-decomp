/////////////////////////////////////////////////
// 
// SCRAP Engine
// 
/////////////////////////////////////////////////

// My on-going recreation of ROMU based on decompiling FlatOut 2

// ROMU is always spelled with capitals, so I assumed it was an acronym, but it turns out it's the finnish word for scrap metal.
// SCRAP it is.
#include "SCRAP.h"

// Code will be moved here when I find the same functions, structs, or classes in the other games, or when it depends on functions, structs, or classes already in here.
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
// then it will treated as a hex string
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

// This is apparently strchr(), which makes it's oddities even more confusing.
static char* String_IndexOfAlmost(char* string, char theChar)
{
	// This function has 3 stages:
	// The first stage is a strange indexOf where it only checks a few characters based on the location of the string in memory.
	// The second stage makes no sense to me, it's both heavily obfuscated and probably needs more context.
	// The third stage is a standard indexOf, but it only checks 4 characters
	DWORD parityish = (DWORD)string & 3;
	while (parityish != 0)
	{
		if (*string == theChar)
			return string;

		if (*string == NULL)
			return NULL;

		string++;
		parityish = (DWORD)string & 3;
	}


	uint uVar1, uVar3, uVar4;
	char* pcVar5;
	char tempChar;
	while (true)
	{
		while (true)
		{
			// What is even going on in this first loop
			uVar1 = *(uint*)string;
			// Checks if the string has 4 of theChar in a row
			uVar4 = uVar1 ^ (theChar << 24 | theChar << 16 | theChar << 8 | theChar);

			// (x XOR y XOR x) gives you y. This could have just been 0x7EFEFEFE
			//uVar3 = uVar1 ^ ((uint)-1) ^ uVar1 + 0x7EFEFEFF;
			uVar3 = 0x7EFEFEFE;

			pcVar5 = string + 4;

			// Same thing here, it's just 0x7EFEFEFE again
			//if ((uVar4 ^ ((uint)-1) ^ uVar4 + 0x7EFEFEFF) & 0x81010100) break;
			// Considering that was the only break, is it possible to reach the third stage?
			if (false) break;

			string = pcVar5;
			if (uVar3 & 0x81010100)
			{
				if (uVar3 & 0x1010100)
					return NULL;

				if (uVar1 + 0x7EFEFEFF & 0x80000000)
					return NULL;
			}	
		}

		// Changed this to a loop
		for (uVar1 = 0; uVar1 < 4; uVar1++)
		{
			if (string[uVar1] == theChar)
				return string + uVar1;

			if (string[uVar1] == NULL)
				return NULL;
		}

		string = pcVar5;
	}

	// Considering the outer while loop doesn't have any breaks, I don't think it's possible to reach here.
	return NULL;
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
// DoNotCallEver is the destructor for PropertyDb. It tells you not to call it for obvious reasons.
// I do wonder though, why not just put an empty function there? I guess it was to catch more bugs in development.
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

// Thanks to Sewer56 for helping me get their disassembly opening

uint __fastcall GetScriptParameterInt(LuaStateStruct* lss, int unaff_ESI)
{
	int type = lua_type(lss->L_0x0, lss->index_0x4);
	if (type == LUA_TBOOLEAN)
		return lua_toboolean(lss->L_0x0, lss->index_0x4);

	float data = lua_tonumber(lss->L_0x0, lss->index_0x4);

	// Some intense bit manipulation is about to happen
	uint intForm = *(uint*)&data;
	type = intForm >> 23;
	type &= 0xFF;
	type -= 0x7F;

	// What
	//return (((intForm | 0xFF800000) << 8) >> (0x1F - (uchar)type & 0x1F) ^ intForm >> 31) - intForm >> 31 & ~(type >> 31);
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

int Lua_KickPlayer(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);

	void* pUserData = lua_touserdata(L, 1);
	if (pUserData == NULL)
		// a type rror? a typ error?
		luaL_typerror(L, 1, LUA_TUSERDATA);

	// Function pointers have nothing on function pointers inside function pointers
	void (**vftable1)(void(***)()) = pUserData->vftable;

	// This one is not checked to see if it's null
	pUserData = lua_touserdata(L, 2);
	void (**vftable2)() = (void (**)())pUserData->vftable;

	undefined4 local_4 = pUserData->unkn_0x4;
	vftable1[12](&vftable2);
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
		luaL_typerror(L, 1, STRING_008e8504);

	// The 4th item in the vftable is a code** so it's either a struct with the first field being a jump table, or the jump table in the current struct contains pointers to pointers
	// (*(pUserData->vftable_0x0[4]))();
	return 0;
}

// Functions that are called from Lua
// The first item in the table is the input to functions, while outputs are added to the end of the table, almost like it's a print output or something.

int len(lua_State* L)
{
	UINT length;
	luaL_checklstring(L, 1, &length);
	lua_pushinteger(L, length);
	return LUA_OK;
}

int GetNumWStringLines(lua_State* L)
{
	lua_State* LCopy = L;
	wchar_t* in_wstring = (wchar_t*)lua_tolstring(L, 1, NULL);

	int plVar2 = 1;
	L = (lua_State*)1;
	uint length = WString_GetLength(in_wstring);
	if (length)
	{
		// It was originally a do while but it's structured exactly like a for so why not
		for (int i = 0; i < length; i++)
		{
			if (in_wstring[i] == L'\n')
				plVar2++;

			L = (lua_State*)plVar2;
		}
	}
	lua_pushnumber(LCopy, (float)(int)L);
	return LUA_OK;
}

int getplatform(lua_State* L)
{
	lua_pushlstring(L, "PC", 2);
	return LUA_OK;
}

int StartKickVote(lua_State* L)
{
	luaL_checktype(L, 1, LUA_TUSERDATA);
	void* pUserData = lua_touserdata(L, 1);
	if (pUserData == NULL)
		luaL_typerror(L, 1, "userdata");

	/*
	int* piVar1 = *(int**)(pUserData->vftable);
	pUserData = lua_touserdata(L, 2);
	int local_8 = *(int*)pUserData->vftable;

	//FUN_004f0f20(piVar1, &local_8);
	*/

	return LUA_OK;
}

int deg(lua_State* L)
{
	float rad = luaL_checknumber(L, 1);

	lua_pushnumber(L, rad * 57.29578f);

	return LUA_OK;
}

// FormatMemoryCard will call this function, but given the lack of formatting going on I'd say that's unintentional.
int FormatMemoryCardForRealMaybe(undefined* param_1)
{
	return param_1->unkn_0x4;
}


// Left-over from the PS2 version, it still tries to call the formatting function, but it's been removed.
// It still updates something in the settings, so maybe something strange will happen if this is triggered on the PC version?
int FormatMemoryCard(lua_State* L)
{
	sGameSettings* pSettings = g_pGameSettings_008e8410;
	FormatMemoryCardForRealMaybe();
	pSettings->field1088_0x44c = 7;
	return 0;
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

		for (int d = bytesToWrite; d != 0; d -= tempToWrite)
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


bool MWFileObject::IsFilePosBeyond()
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
	//this->vtable = &JMPTABLE_0067b6f8;
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
#define ReadAsIntP(buf, offset) (*(int**)(&buf[offset]))
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

			// The ghidra code uses a second comparison like a trick to set j during the if. I chose to do it afterwards, is it any different?
			// && (j = 0, bfsFile[1] != NULL)
			// If that's all it was for I can probably just remove it
			if ((bfsFile[1] != NULL))
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


/////////////////////////////////////////////////
//
// Input
// 
/////////////////////////////////////////////////

BYTE lpKeyState_008d7d60[0x40];
BYTE lpKeyState_008d7e60[0x40];
HHOOK HHOOK_008da738;

HKL HKL_008d7c44;

LRESULT Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam);

HOOKPROC nextHook = (HOOKPROC)Keyboard_HookProc;

LRESULT KeyboardController::Keyboard_Hook(uint param_1)
{
	// Ghidra shows the STOSD.REP instruction as a for loop
	__stosd((unsigned long*)lpKeyState_008d7e60, 0, 0x10);
	__stosd((unsigned long*)lpKeyState_008d7d60, 0, 0x10);

	if (HHOOK_008da738 == NULL)
	{
		DWORD dwThreadId = GetCurrentThreadId();
		HHOOK_008da738 = SetWindowsHookExA(2, nextHook, NULL, dwThreadId);
		if (HHOOK_008da738 == NULL)
		{
			//uStack_2c = 0xF;
			//uStack_30 = 0;
			//uStack_40 = 0;
			//FUN_0055b050(auStack_44, "KeyboardController::Unable to hook keyboard", 0x2B);
			//appuStack_28[0] = &PTR_FUN_006578c4;
			//uStack_4 = 0xF;
			//uStack_8 = 0;
			//uStack_18 = 0;
			//FUN_0055ae50(auStack_1c, auStack_44, 0, 0xFFFFFFFF);

			// Some kind of exception code, I'll just do this for now.
			throw EXCEPTION_INVALID_HANDLE;
		}
	}

	HKL_008d7c44 = GetKeyboardLayout(0);

	/*
	__stosd(UINT_008d7c48, 0, 0x40);
	DAT_008d7d58 = 0;
	DAT_008da740 = 0;
	this->field_0x12c = 1;
	this->field_0x130 = 1;
	*/
	int iVar1 = 0;//FUN_00553220();
	if (iVar1 == 0)
	{
		//this->vftable_0x0[17]();
		//FUN_00553360();
	}
	iVar1 = 0;
	do
	{
		//FUN_00553120();
		iVar1++;
	} while (iVar1 < 20);

	return 1;
}

int DAT_008da740;
uint DAT_008da734;
int* PTR_008e844c;

LRESULT Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
		return 0;
	}

	uint wVirtKey = wParam & 0xFF;
	if (lParam < 0)
	{
		if (lpKeyState_008d7e60[wVirtKey] < 0)
			DAT_008da740--;

		lpKeyState_008d7e60[wVirtKey] &= 0x7F;
	}
	else
	{
		// In Binary: 0?00 0000 0000 0000 0000 0000 0000 0000
		if (DAT_008da734 || ((lParam & 0x40000000U) == 0))
		{
			if (lpKeyState_008d7e60[wVirtKey] > -1)
				DAT_008da740++;

			lpKeyState_008d7e60[wVirtKey] ^= 1;
			lpKeyState_008d7e60[wVirtKey] |= 0x80;

			lpKeyState_008d7d60[wVirtKey] += 1;
		}
		if (PTR_008e844c[11] != 0)
		{
			if (((lParam & 0x40000000U) != 0) && (PTR_008e844c[5] == 0))
			{
				CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
				return 0;
			}

			WCHAR convertedKey = 0;
			// local_4 is AND'd before it's even initialized.
			uint local_4;
			local_4 &= 0xFFFF0000;
			int iVar1 = ToUnicode(wVirtKey, lParam, lpKeyState_008d7e60, &convertedKey, 8, 0);
			if (iVar1 == 1)
				// Treat local_4 as an array of 2 shorts, take the second one and concatentate with local_20.
				local_4 = (((short*)&local_4)[1] << 16) | (short)convertedKey;

			LPARAM LVar4;
			uint uVar3;
			iVar1 = ToAscii(wVirtKey, lParam, lpKeyState_008d7e60, (LPWORD)&convertedKey, 0);
			if (iVar1 == -1)
			{
				uVar3 = convertedKey & 0xFFFF;
				wVirtKey = 0;
				LVar4 = 0;
			}
			else
			{
				if (iVar1 != 0)
				{
					if (iVar1 > 0)
					{
						int iVar2 = 0;
						do
						{
							//FUN_00550350(&local_20 + (iVar2 * 2), wVirtKey, 0, local_4);
							iVar2++;
						} while (iVar2 < iVar1);
					}
					goto hookExit;
				}
				uVar3 = 0;
				LVar4 = lParam;
			}
			//FUN_00550350(uVar3, wVirtKey, LVar4, local_4);
		}
	}
hookExit:
	CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
	return 0;
}

// Another function that looks suspicously like DoNotCallEver.
void* KeyboardController::Keyboard_Unhook(BYTE bFree)
{
	//this->vftable_0x0 = JMPTABLE_0067b818;
	if (this->int_0x12c)
	{
		if (HHOOK_008da738 != NULL)
			UnhookWindowsHookEx(HHOOK_008da738);

		HHOOK_008da738 = NULL;
		//DAT_008da73c = NULL;
		this->int_0x12c = 0;
		this->byte_0x130 = 0;
	}
	//this->vftable_0x0 = JMPTABLE_0067b738;
	if (bFree & 1)
		delete this;

	return this;
}