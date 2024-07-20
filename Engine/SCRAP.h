#pragma once

#include <stdio.h>
#include <memory.h>
#include <intrin.h>
#pragma intrinsic(__stosd)
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

// Lua 5.1
// I don't know the exact version that was used, but 5.1.5 can be downloaded from here.
// https://www.lua.org/versions.html#5.1
// It's from 2012 but it's the only version of 5.1 available.
// According to 5.1.5's code there should be a full version string somewhere but there isn't one.
#include "lua-5.1.5/src/lapi.h"
#include "lua-5.1.5/src/lauxlib.h"
#include "lua-5.1.5/src/lcode.h"
#include "lua-5.1.5/src/ldebug.h"
#include "lua-5.1.5/src/ldo.h"
#include "lua-5.1.5/src/lfunc.h"
#include "lua-5.1.5/src/lgc.h"
#include "lua-5.1.5/src/llex.h"
#include "lua-5.1.5/src/llimits.h"


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

// Formerly SlashConvertString
int NormalizeFilePath(uchar* in_string, int mode, uchar* out_string);

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

int WString_GetLength(wchar_t* in_wstring);

wchar_t* WString_SimpleCopy(wchar_t* Dst, wchar_t* Src);



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


struct TableItemStructThing
{
	// 6 undefined bytes at offset 0x0
	BYTE byte_0x6;
};


// LuaTable's StructThing
struct astruct_169
{
	void* end_0x0; // Pointer to the last byte of itself, don't know why just yet.
	void* unkn_0x4;
	lua_State* state_0x8;
};

struct LuaStateStruct
{
	lua_State* L_0x0;
	int index_0x4;
};

struct LuaStateStruct2
{
	char* nameMaybe_0x0;
	lua_State* L_0x4;
	void* unkn_0x8;
};


// In the original code these are structs that have a function table as their first property, but to make things easier I changed them to C++ classes.

// Turns out, I spent a ton of time decompiling a lua struct I could have looked up
// At the very least it's a lot of code that I don't have to decompile anymore.

// Functions that are called from lua

// Error Codes
// Lua does not define an ok macro 
#define LUA_OK 0

int len(lua_State* L);
int GetNumWStringLines(lua_State* L);
int getplatform(lua_State* L);
int StartKickVote(lua_State* L);
int deg(lua_State* L);
int FormatMemoryCard(lua_State* L);
int Lua_KickPlayer(lua_State* L);
int JoinCurrentSession(lua_State* L);
int JoinSessionFromCommandLine(lua_State* L);


// This jump table thing is making me think it's not a class but like a bugbear-made method system. But maybe that's just how classes are implemented in machine code and Ghidra is right?
/*
void (*JMPTABLE_0067b6f8[])() = {
	FileObject::Close2,
	FileObject::NotSureYet2,
	FileObject::WriteFileToHandle,
	FileObject::Create,
	FileObject::Close,
	FileObject::AddToFilePos,
	FileObject::IsFilePosValid,
	FileObject::GetSize,
	FileObject::GetFilePosButLikeWhy,
	FileObject::FlushBuffers,
};
*/

// Thanks to mrwonko on GitHub for their file object reverse engineering
// There's more than one file object, so this one is the MrWonkoFileObject
class MWFileObject
{
public:
	void (**vtable)();
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

	DWORD WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite);

	void bbSetFilePointer(int newLoc);

	void Create(LPCSTR lpFilename, uint flags);

	void SetFilePos(int newPos, int mode);

	void FlushBuffers();

	char* GetFilePosButLikeWhy();

	bool IsFilePosBeyond();

	int GetSize();

	void Clear();

	void __fastcall Close();

	void DoNothing();

	MWFileObject* ResetMaybe(int bFree);
};

MWFileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX);
void __fastcall FileObject_ClearEAX(MWFileObject* in_EAX);

// there's another class based off the original one.
class MW2FileObject : MWFileObject
{
private:
	undefined4 unkn_0x4028;
	undefined4 unkn_0x402c;
	undefined4 unkn_0x4030;
	// 0x72 undefined bytes at offset 0x4034
	undefined4 unkn_0x407c;
	undefined4 unkn_0x4084;

public:
};


// Used for OpenBFS
struct YetAnotherFileObject
{
	HANDLE handle_0x0;
	int size_0x4;
	// 516 undefined bytes at offset 0x8
	char* string_0x20c;
	int sizeAgain_0x210;
	int int_0x214;
	char* string_0x218;
	char* string_0x21c;
	int int_0x220;
};



void OpenBFS(LPCSTR filename, register YetAnotherFileObject* unaff_EDI);


// Thanks to Sewer56 on GitHub for figuring out these structs.

struct sRGBA
{
	char b, g, r, a;
};

struct Vector3_pad
{
	float x, y, z, pad;
};

struct Quaternion
{
	float y, z, x, w;
};

struct Matrix33
{
	Vector3_pad right;
	Vector3_pad up;
	Vector3_pad at;
};

struct sVehicle
{
	// 120 undefined bytes at offset 0x0
	char* m_sFolderPath;
	// 16 undefined bytes at offset 0x7c
	uint32_t m_nFolderPathLength;
	// 288 undefined bytes at offset 0x90
	Matrix33 m_mMatrix;
	Vector3_pad m_vPosition;
	// 128 undefined bytes at offset 0x1f0
	Quaternion m_qQuaternion;
	Vector3_pad m_vVelocity;
	Vector3_pad m_vRotationVelocity;
	// 812 undefined bytes at offset 0x2a0
	float m_fNitro;
	// 5824 undefined bytes at offset 0x5d0
	uint32_t m_nTireTextureID;
	uint32_t m_nTireModelID;
	// 8 undefined bytes at offset 0x1c98
	uint32_t m_nDriverHandsID;
	// 3228 undefined bytes at offset 0x1ca4
	uint32_t* m_pShadowTexture;
	// 364 undefined bytes at offset 0x2944
	uint32_t m_nRagdollState;
	// 6880 undefined bytes at offset 0x2ab4
	uint32_t* m_pSkinDamageTexture;
	uint32_t* m_pLightsDamagedTexture;
	uint32_t* m_pLightsGlowTexture;
	uint32_t* m_pLightsGlowLitTexture;
	// 152 undefined bytes at offset 0x45a4
	Player* m_pPlayer;
	// 9312 undefined bytes at offset 0x4640
	float m_fDamage;
	// 36 undefined bytes at offset 0x6aa4
	bool m_bGodMode;
	//
};

class Player
{
private:
	void (**m_pVFT_0x0)();
	// 12 undefined bytes at offset 0x4
	undefined4 unkn_0x10, unkn_0x14, unkn_0x18;
	// 16 undefined bytes at offset 0x1c
	undefined2 unkn_0x2c;
	// 644 undefined bytes at offset 0x2e
	undefined4 unkn_0x2b0, unkn_0x2b4;
	// 28 undefined bytes at offset 0x2b8
	sRGBA m_nBlipColor_0x2d0;
	int int_0x2d4;
	undefined4 unkn_0x2d8;
	// 100 undefined bytes at offset 0x2dc
	sVehicle* m_pVehicle_0x33c;
	uint32_t m_nCarID_0x340;
	uint32_t m_nSkin_0x344;
	// 4 undefined bytes at offset 0x348
	uint32_t m_bDriverFemale_0x34c;
	uint32_t m_nDriverSkin_0x350;
	// 20 undefined bytes at offset 0x354
	uint32_t m_nPlayerId_0x368;
	uint32_t m_nFlags_0x36c;
	// 16 undefined bytes at offset 0x370
	uint32_t m_bDisableControlAndReset_0x380;
	// 168 undefined bytes at offset 0x384
	Vector3_pad m_vPosition_0x428;
	// 116 undefined bytes at offset 0x42c
	float m_fReadOnlyDamage_0x49c;
	// 484 undefined bytes at offset 0x4a0
	float m_fSteerAngle_0x684;
	float m_fGasPedal_0x688;
	float m_fBrakePedal_0x68c;

public:

};


// PropertyDb

class PropertyDb
{
private:
	void (**vftable_0x0)();

public:
	PropertyDb* Destructor(int bDestruct); // "Real" destructor, so that the error does not show when exiting the game normally.
	PropertyDb* DoNotCallEver(int bDestruct); // Destructor included in the function tables, puts up the error message to catch bugs
};

struct PlayerProfile
{
	// 3636 undefined bytes at offset 0x0
	wchar_t m_wsPlayerName_0xe34[16];
};

struct sPlayerArray
{
	Player* m_aPlayers[8];
};

struct PlayerHost
{
	void (**vftable_0x0)();
	// 16 undefined bytes at offset 0x4
	sPlayerArray* m_pPlayerArray_0x14;
	// 2416 undefined bytes at offset 0x18
	uint32_t m_nNumCars_0x988;
	// 130,784 undefined bytes at offset 0x98c
	uint32_t m_nLevelID_0x2086c;
};

struct sGameSettings
{
	// 1152 undefined bytes at offset 0x0
	uint32_t m_nLevelID_0x480;
	// 4 undefined bytes at offset 0x484
	uint32_t m_nNumLaps_0x488;
	// 1324 undefined bytes at offset 0x48c
	PlayerHost* m_pHost_0x9b8;
	// 80 undefined bytes at offset 0x9bc
	BOOL m_bStarted_0xa0c;
	// 1488 undefined bytes at offset 0xa10
	PlayerProfile m_pPlayerProfile_0xfe0;
};


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
