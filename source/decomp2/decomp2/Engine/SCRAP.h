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
#pragma comment(lib, "Winmm.lib")
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

#include <memoryapi.h>
#include <WinUser.h>
#include <winreg.h>
*/

#include <setjmp.h>

#include <stdlib.h>
//#include <string>

#include "../Lua.h"

// zlib 1.3.1
// Apparently the version used was 1.3.3, but 1.3.1 is the latest version on GitHub as of writing this, so that must have referred to something else
#include "zlib-1.3.1/zlib.h"
#include "zlib-1.3.1/zconf.h"

#include "../Macros.h"
#include "../BasicTypes.h"
#include "../MrWonkoFileObject.h"
#include "../ScriptHost.h"

//////////////////////////////
// Functions
//////////////////////////////

// Strings
void CaptionlessTaskModalMessageBox(LPCSTR lpText);
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

int WString_GetLength(const wchar_t* in_wstring);
wchar_t* WString_SimpleCopy(wchar_t* Dst, wchar_t* Src);

void AddStringToList(int index, const char* newString);
bool String_CompareAsIntegers(int* ints1, int* ints2);
bool StringToNum(char* stringFloat, float* outFloat);

// Lua CFunctions

int math_deg(lua_State* L);

int GetNumWStringLines(lua_State* L);
int GetSaveFlowResult(lua_State* L);
int GetSaveFlowState(lua_State* L);
int GetSaveGameInfoValid(lua_State* L);
int GetSaveStatus(lua_State* L);
int EnoughMoney(lua_State* L);
int SetMoney(lua_State* L);
int SubtractMoneyCars(lua_State* L);
int SubtractMoneyUpgrades(lua_State* L);
int getplatform(lua_State* L);
int GetTotalRagdollFlyDistance(lua_State* L);
int deg(lua_State* L);
int StartKickVote(lua_State* L);
int FormatMemoryCard(lua_State* L);
int Lua_KickPlayer(lua_State* L);
int JoinCurrentSession(lua_State* L);
int JoinSessionFromCommandLine(lua_State* L);

int SetGlobalFontScale(lua_State* L);
int DEBUGLOG(lua_State* L);

void __fastcall GetLuaClassMaybe(char* name_EAX, lua_State* L_ESI);

int __stdcall GetScriptParameterInt(register LuaStateStruct* lss_EAX);
BOOL __stdcall GetScriptParameterBool(register LuaStateStruct* lss_ESI);

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

MWFileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX);
void __fastcall FileObject_ClearEAX(MWFileObject* in_EAX);

void OpenBFS(LPCSTR filename, register YetAnotherFileObject* unaff_EDI);

void DoNothing();