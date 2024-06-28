#pragma once

#include <stdio.h>
#include <math.h>

// WINMM.DLL
// USER32.DLL
// SHELL32.DLL
// KERNEL32.DLL
// GDI32.DLL
// ADVAPI32.DLL
// OLE32.DLL
#include <windows.h>
// I'll start adding them back if I discover that it's not included in windows.h
/*
#include <combaseapi.h>
#include <shellapi.h>
#include <fileapi.h>
#include <libloaderapi.h>
#include <process.h>
#include <synchapi.h>
#include <winbase.h>
#include <winsock.h>
#include <timeapi.h>
#include <memoryapi.h>
#include <WinUser.h>
#include <winreg.h>
*/

#include <setjmp.h>

#include <stdlib.h>
#include <string>


// Wait a minute, Microsoft already did this
#define uint UINT
#define ulong ULONG
#define ushort USHORT
#define uchar UCHAR
#define ulonglong ULONGLONG
#define cchar const char // This was my idea though, I can at least claim that.

// I didn't know that wide strings were unicode, but in my defence, if they are interchangable why is there both wchar_t and char16_t? both u"String" and L"String"?
#define LPUSTR LPWSTR



#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
// I thought a long was 8 bytes, but that's not the case on Windows.
// long and int are the same size? Why is it a 'long' then?
#define undefined8 unsigned long long

// Doesn't end there, putting aside the missed opportunity to call it a double double, it turns out a long double is the same size as a double.
// I couldn't find much information about what ghidra's float10 actually is.
// I've heard it's an 80-bit float but 64 is the best we're going to get without some other solution.
#define float10 long double

// Can't do += sizeof() but you can with this workaround.
#define size_of(type) (1 * sizeof(type))


void CreateErrorMessageAndDie(const char* message, ...);
void* DoNotCallEver(void* jmpTable, int bFree);



// It used to be called neverReferencedAgain, because this next function checks if it's 0,
// and that's the only time it's ever referenced.
// Cheat Engine says this value is initialized to 0, so it always overrides.
int g_slashOverride = 0;


int SlashConvertString(uchar* in_string, int mode, uchar* out_string);

int String_Compare(char* string1, char* string2);

int String_Compare_s(char* string1, char* string2, int maxLength);

char String_CompareEnd(char* out_string, char* in_string, int length);

int String_GetLength(const char* in_string);

char* String_SimpleCopy(char* out_string, const char* in_string);

char* String_CopySubstring(char* out_string, char* in_string, int length);

char* String_Append(char* out_string, const char* in_string);

char* String_AppendSubstring(char* out_string, char* in_string, int length);

void __cdecl ComplicatedCopyString(char** out_string, uint param_2, const char* in_string);

void static CopyStringToPointerToString(char** out_string, const char* in_string);

char Char_ToLowercase(char theChar);

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

void AddStringToList(int index, const char* newString);

bool String_CompareAsIntegers(int* ints1, int* ints2);

bool StringToNum(char* stringFloat, float* outFloat);




// My own addition, It's leaning a bit towards inaccuracy, but it'll make it much easier to read the code
// The lua table stores items as pairs of void*, where the second pointer is actually an int describing the type
// My guess is that because an int is the same size, they could just cast with no issues.
// I originally put it as a DWORD but I'm going to keep it 32-bit so I can properly understand things before going back and making 64-bit changes
// In FlatOut 1, The LuaItem is reversed, the first pointer is type, the second is the data
struct LuaItem
{
	void* data;
	int type;
};

// And here's the table of lua types
// The first and second userdata are very different, probably have the same name for security
// technically -1 has an entry, it'll return "no value" when calling Lua_StringTypeFromInt
const char* LuaTypes_0065284c[] =
{
	"nil" // data is not defined, could be anything
	"boolean", // boolean inside data
	"userdata", // I think it's just a char*, still need to confirm that
	"number", // float inside data, so it's as percise as the word size is large.
	"string", // pointer to struct containing a wide string.
	"table", // I'm still confirming whether this is a LuaTable or some other table
	"function", // data is the pointer to the function
	"userdata", // data is a struct, still haven't figured it out yet
	"thread",
	"proto",
	"upval"
};

// I'll make an enum so I can use the type names instead of numbers
enum LT
{
	nil,
	boolean,
	userdata,
	number,
	string,
	table,
	function,
	userdata_s,
	thread,
	proto,
	upval
};

// This item is never used, it represents a null LuaItem.
// This had to be done because data is checked
LuaItem LuaItem_None_0065271c;

// astruct_157
// I thought it was a generic Lua Data struct but it turns out it's only used on strings and maybe userdata. Numbers and booleans are just stored as is.
struct LuaString
{
	char* (**jmptable_0x0)(void);
	// 7 undefined bytes at offset 0x0
	int int_0x4;
	BYTE byte_0x7;
	// 4 undefined bytes at offset 0x8
	UINT length_0xc;
	wchar_t* theString_0x10;
};

struct LuaUserData
{
	// The parameter to the function is another LuaUserData's vftable
	void (**vftable)(void (***)());
	// So the parameter is a function whose first parameter is a function whose first parameter is a function whose first parameter...
	//void (**vftable)(void (**)(void (**)(void (**)(void (**)(void (**)(...))))));
	undefined4 unkn_0x4;
	undefined4 unkn_0x8;
	char* string_0x10;
};

// I think this is lua's userdata_s struct, or maybe it's the other way around and this is the string
struct UnknownStruct
{
	// 20 undefined bytes at offset 0x0
	char char_0x15;
	// 29 undefined bytes at offset 0x16
	uint uint_0x40;
	int int_0x44;
	uint uint_0x4c;
	int int_0x50;
	int int_0x54;
};

// LuaTable's StructThing
struct astruct_169
{
	void* end_0x0; // Pointer to the last byte of itself, don't know why just yet.
	void* unkn_0x4;
	LuaTable* table_0x8;
};


// In the original code these are structs that have a function table as their first property, but to make things easier I changed them to C++ classes.

class LuaTable
{
public:
	// 8 undefined bytes at 0x0
	BYTE field7_0x6;
	BYTE byte_0x7;
	LuaItem* next_0x8; // Stores a pointer to the next blank item in table_0xc, for adding new ones
	LuaItem* table_0xc; // The current table
	UnknownStruct* field10_0x10;
	int** field11_0x14;
	LuaItem* endOfTable_0x1c;
	// 4 undefined bytes at 0x18
	int field17_0x20;
	// 24 undefined bytes at offset 0x24
	short bDebug_0x34; // Flag wether or not to enable debug logging.
	// 16 undefined bytes at 0x36
	LuaItem* table_0x44; // Some other table, maybe it's the main one or something?
	// 4 undefined bytes at 0x48
	int field61_0x4c;
	int field62_0x50;

	uint AttemptToYield(int param_2);

	void Lua_AddNilProperty();
	void Lua_ActuallyAddStringProperty(const char* in_wstring, size_t length);
	void Lua_AddStringProperty(const char* in_string);
	void Lua_AddStringProperty2(char* in_string);
	void Lua_AddBoolProperty(bool in_bool);
	void Lua_AddUserDataProperty(void* userdata);

	void Lua_AddNumberPropertyFromInt(int in_number);
	void Lua_AddNumberPropertyFromFloat(float in_number);
	void Lua_Add3ItemsAndCopy1(LuaItem* out_pItem1, LuaItem* pItem1, LuaItem* pItem2, LuaItem* pItem3);
	void CopyItemFromTableItem(int tableIndex, int itemIndex);

	LuaItem* Lua_GetItem(int index);
	int Lua_GetItemType(int index);
	void Lua_DuplicateItem(int index);

	void Lua_RemoveItem(int index);
	void Lua_InsertLastItem(int index);

	void Lua_SeekNextPtr(int newIndex);

	bool Lua_StringFromNumber(LuaItem* pItem);

	bool Lua_IsNumber(int index);

	BOOL Lua_IsNumber_s(int index, LuaTable* otherTable);

	bool Lua_IsUserData(int index);

	LuaItem* Lua_NumberFromString(LuaItem* pStringItem, LuaItem* pNewNumberItem);

	float Lua_GetNumberAsFloat(int index);
	long Lua_GetNumberAsInt(int index);
	LuaItem* Lua_GetNumberItem(int index);
	bool Lua_GetBool(int index);
	void* Lua_GetThread(int index);
	LuaUserData* Lua_GetUserdata(int index);

	wchar_t* Lua_GetStringItem(int index, UINT* out_length);
	wchar_t* Lua_GetStringItem_s(int index, UINT* out_length);

	char* Lua_GetItemStringLength(int index);

	const char* Lua_StringTypeFromInt(int type);

	

	void Lua_gettable(LuaItem* pItem, LuaItem* pLastItem1, LuaItem* pNewItem);

	int Lua_GetTableLength();

	bool Lua_AddFunctionWithANameMatchingTheSecondItemInTheTable();

	bool Lua_IsItemAStringOrNumber(int index);

	bool Lua_ItemsEqual_s(int index1, int index2);

	void Lua_ThrowIfIndexIsNotGivenType(int index, int expectedType);
	void Lua_ReportError(int index, int expectedType);
	void Lua_ReportErrorForReal(int index, int expectedType);

	int Lua_Printf(char* format, ...);

	// Gameplay functions?
	uint Lua_KickPlayer();
	int JoinCurrentSession();
	int JoinSessionFromCommandLine();

	void StructThing(astruct_169* tableStruct);
};

bool Lua_ItemsEqual(LuaItem* pItem1, LuaItem* pItem2);

bool __fastcall Lua_IsFunction(LuaTable** in_EAX);

uint Lua_LongJump(void (*func)(LuaTable*, undefined4*), undefined4* scriptObject);
void Lua_ReturnFromLongJump(uint* param_2);



// Functions that I'm pretty sure are called from Lua

// Error Codes
typedef UINT LuaErrorCode;
#define BB_OK 1

LuaErrorCode len(LuaTable* table);
LuaErrorCode GetNumWStringLines(LuaTable* table);
LuaErrorCode ConvertToWString(LuaTable* table);
LuaErrorCode getplatform(LuaTable* table);
LuaErrorCode StartKickVote(LuaTable* table);
LuaErrorCode deg(LuaTable* table);
LuaErrorCode FormatMemoryCard();

// This jump table thing is making me think it's not a class but like a bugbear-made method system. But maybe that's just how classes are implemented in machine code and Ghidra is right?
/*
void (*JMPTABLE_0067b6f8[])() = {
	FileObject_Close2,
	FileObject_NotSureYet2,
	FileObject_WriteFileToHandle,
	FileObject_Create,
	FileObject_Close,
	FileObject_AddToFilePos,
	FileObject_IsFilePosValid,
	FileObject_GetSize,
	FileObject_GetFilePosButLikeWhy,
	FileObject_FlushBuffers,
};
*/

// Credit to mrwonko on GitHub for their file object reverse engineering
// AutoClass 25
class FileObject {
public:
	void (*vtable)();
	// Array of functions, methods if you will. unused in my implementation because I made it a class instead

	char buffer[0x4000]; // 0x4

	int usuallyNeg1;           // 0x4004 - is -1 on newly opened track_spvs.gen,
	// I've just discovered a function that changes it, I'm still figuring this one out.

	char* filePos;         // 0x4008 - "virtual" file pos - reads in 16kb blocks internally, but allows for arbitrary reads

	char* realFilePos;     // 0x400C - real file's filePos, gets increased by bytesRead
	void* size;        // 0x4010 - returned by BvhFile_Func8 unless it's -1 - *0x4008 otherwise
	HANDLE handle;      // 0x4014
	uint fileattributes;         // 0x4018 - flags describing the file

	char* filename1; // 0x401C
	char* filename2; // 0x4020
	// Two different filename properties, I'm thinking maybe it's for objects that need to load both a model and texture file?


	DWORD FileObject_WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite);

	void FileObject_SetFilePointer(int newLoc);

	void FileObject_Create(LPCSTR lpFilename, uint flags);

	void FileObject_SetFilePos(int newPos, int mode);

	void FileObject_FlushBuffers();

	char* FileObject_GetFilePosButLikeWhy();

	bool FileObject_IsFilePosBeyond();

	int FileObject_GetSize();

	void FileObject_Clear();

	void __fastcall FileObject_Close();

	FileObject* FileObject_ResetMaybe(int bFree);
};

FileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX);
void __fastcall FileObject_ClearEAX(FileObject* in_EAX);




// Used for OpenBFS
struct YetAnotherFileObject
{
	HANDLE handle_0x0;
	int size_0x4;

	char* string_0x20c;
	int sizeAgain_0x210;
	int int_0x214;
	char* string_0x218;
	char* string_0x21c;
	int int_0x220;
};

void OpenBFS(LPCSTR filename, YetAnotherFileObject* unaff_EDI);

// INPUT

// AutoClass23
class KeyboardController
{
private:
	void (*vftable_0x0)();

	int int_0x12c;
	BYTE byte_0x130;

	LRESULT Keyboard_Hook(uint param_1);
	void* Keyboard_Unhook(BYTE param_1);
};
