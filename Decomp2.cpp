// FlatOut 2 Decompilation

// This is a decompilation of the GOG version of FO2.
// The DRM is the only difference between this and the Steam version, once launched the memory layout of the game is identical from what I can tell.
// The Epic Games executable is exactly the same as the GOG one, down to the checksum.

// Bugbear used Visual Studio 2003 aka Visual Studio 6, which means we know the IDE, compiler, all that. But finding a copy these days is difficult. I'm using 2022 for this recreation.
// To remove the warnings about the unsafe string functions, add _CRT_SECURE_NO_WARNINGS to the Preprocessor definitions under Properties -> C/C++ -> Preprocessor

// SCRAP Engine
#include "Engine/SCRAP.h"

// Standard Libraries
#include <stdarg.h>
#include <strsafe.h>
#include <math.h>
#include <string.h>

// Direct X
// D3D9.DLL
#include <d3d9.h>

// D3DX9_30.DLL
// Requires you to run this command in Visual Studio's NuGet console:
// NuGet\Install-Package Microsoft.DXSDK.D3DX -Version 9.29.952.8
//#include <d3dx9.h>
#include <D3DX9Effect.h>
#include <D3dx9tex.h>
#include <dinput.h>

//#pragma comment(lib, "dinput8.lib")

// IPHLPAPI.DLL
#include <iphlpapi.h>

// WS2_32.DLL
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")

// Misc.
#include <sys/stat.h>
#include <intrin.h>



/////////////////////////////////////////////////
// Variables
// These ones are sorted by address location, grouped by relevance when possible.
// I went back to placing variables next to relevant functions to make things easier, I'll add them here once they're figured out

DLGPROC g_dlgproc;

LPCSTR lpOperation_0066ab90;

const char16_t* u_NO_TEXT_0066b38c = u"NO_TEXT";

// These are treated like an array, AutoClass31s have an index into these DATs
uint DAT_0069ba70;
uint DAT_0069ba74;
uint DAT_0069ba78;
uint DAT_0069ba7c;
uint DAT_0069ba80;
uint DAT_0069ba84;
uint DAT_0069ba88;
uint DAT_0069ba8c;

uint UINT_0069c2d0;

const char16_t** PTR_u_NO_TEXT_0069df4 = &u_NO_TEXT_0066b38c;

DWORD TimePassed_006a32e8;

HGDIOBJ HGDIOBJ_006d67b8;
LRESULT DAT_006d68dc;
LRESULT DAT_006d68e0;
LRESULT DAT_006d68ec;
LRESULT UINT_006d6900;
uint UINT_006d6908;

uint UINT_006d690c;
uint UINT_006d68d0;
uint UINT_006d68d8;
uint UINT_006d68e8;
uint UINT_006d68f0;

void (*PTR_LAB_007a9e4[5])(void);

ushort FPUConW_008d781c;

uint UINT_008d780c;
uint UINT_008d7bb0;

uint UINT_008d7c30;

uint UINT_008da270;
HINSTANCE HINST_008da2dc;

void* MEM_008da568;

uint UINT_008da728;

// 1 = delete bfs file on opening, 0 = normal
uint UINT_008da730;


HWND HWND_008da79c;

HWND HWND_008da56c;

// It's an int, but used as a bool.
int setupFlag_008da684 = 0;

uint unkn_008da6a0;

// The handle of the .exe file
HINSTANCE HINST_008da564;

void (*FUNC_008da6f4)();

uint UINT_008da6fc;

LRESULT UINT_008db344[30];

uint UINT_008e5770;

uint UINT_008e5d70;

int* int_008e8420;

uint UINT_008e855c;

void* MemoryPointer;
size_t memAllocationSize;

int _Size;



const char* Funcs_00652918[] =
{
	"__index",
	"__newindex",
	(const char*)0x5F,
	"__mode",
	(const char*)0x5F,
	"__add",
	"__sub",
	"__mul",
	"__div",
	"__mod",
	"__pow",
	"__unm",
	"__len",
	(const char*)0x5F,
	(const char*)0x5F,
	"__concat",
	"__call"
};

/////////////////////////////////////////////////
// Structs

// astruct_1
struct ArrayMaybe
{
	INT count;
	// 4 undefined bytes at offset 0x4
	INT lenOfItem;
	// 8 undefined bytes at offset 0xC
	INT memLoc;
};

// Returns the memory address of an item in an array, or NULL.
int GetItem(ArrayMaybe* rray, int index)
{
	if ((index > -1) && (index < rray->count))
	{
		return rray->lenOfItem * index + rray->memLoc;
	}
	return NULL;
}

struct astruct_42 {
	void (*func_0x0)();
	uint field1_0x4;
	uint field2_0x8;
	uint field3_0x10;
	// Maybe this is all one buffer, I don't know
	DWORD dw1_0xc;
	// 4 undefined bytes at offset 0x10
	DWORD dwbuffer1_0x14[10];
	// 4 undefined bytes at offset 0x3c
	DWORD dwbuffer2_0x40[35];
	// 4 undefined bytes at offset 0xcc
	uint field4_0xd0;
	// 12 undefined bytes at offset 0xd4
	uint field5_0xe0;
	uint field6_0xe4;
};

struct astruct_97 {
	// 8 undefined bytes at offset 0x0
	uint** field_0x8[2];
	int* field_0x10;
};


struct astruct_110 {
	// 4 undefined bytes at 0x0
	int field0_0x4;
	uint field1_0x8;
	int field2_0xc;
	// 136 undefined bytes at 0x10
	undefined4 field3_0x98;
	undefined4 field4_0x9c;
	undefined4 field5_0xa0;
	uint field6_0xa4;
};

struct astruct_138
{
	// 100 undefined bytes at offset 0x0
	uint int_0x64;
	HANDLE handle_0x68;
	// 8 undefined bytes at offset 0x6C
	LONG long_0x74;
	void * unkn_0x78;
	// 4 undefined bytes at offset 0x7C
	DWORD dw_0x80;
};

struct astruct_140 {
	// 64 undefined bytes at offset 0x0
	uint field0_0x40;
	uint field1_0x44;
	// 16 undefined bytes at offset 0x48
	HINSTANCE hinst_0x58;
};

struct astruct_147 {
	int int1_0x0;
	int int2_0x4;
};

struct astruct_148 {
	// 4 undefined bytes at offset 0x0
	LPCRITICAL_SECTION critical_0x4;
	// 25 undefined bytes at offset 0x8
	char char_0x21;
};

// Settings Structures
// Got this info from the cfg files

struct Version {
	uint Settings = 15; // 0 - 1,000,000
};

struct Game {
	bool ImperialUnits = false;
	bool OverlayGauges = true;
	bool IngameMap = true;
	bool Ragdoll = true;
	bool ShowBonus = true;
	bool ShowTutorials = true;
	char DefaultPlayerName[7] = "PLAYER";
	BYTE Camera = 0; // 0 - 9
	BYTE Hud = 0;    // 0 - 4
};

struct Control {
	char ControllerGuid[33] = "00000000000000000000000000000000";
	BYTE Controller = 0;                     // 0 - 2
	BYTE ForceMagnitude = 100;               // 0 - 100
	BYTE ControllerSensitivity = 90;         // 0 - 100
	BYTE ControllerDeadzone = 0;             // 0 - 100
	BYTE ControllerSaturation = 90;          // 0 - 100
	BYTE ControllerLayout = 0;               // 0 - 10
	bool ForceFeedback = true;
	float DigitalCenteringSpeed = 0.999f;   // 0.0 - 100.0
	float DigitalSteeringMaxSpeed = 1.85f;  // 0.0 - 100.0
	float DigitalSteeringMinSpeed = 1.25f;  // 0.0 - 100.0
};

struct Visual {
	bool AlphaBlend = true;
	bool SunFlare = true;
	BYTE TextureQuality = 4;       // 0 - 4
	BYTE TrackDetail = 2;          // 0 - 2
	BYTE PS2MotionBlurIngame = 32; // 0 - 255
	BYTE Visibility = 100;         // 0 - 100
};

struct Audio {
	BYTE InterfaceMusicVolume = 50;  // 0 - 100
	BYTE InterfaceSfxVolume = 80;    // 0 - 100
	BYTE IngameMusicVolume = 50;     // 0 - 100
	BYTE IngameSfxVolume = 80;      // 0 - 100
	BYTE ChannelMode = 0;            // 0 - 2
	bool DopplerEffects = false;
};

struct Network {
	ushort Port = 23756;                     // 0 - 65536
	ushort BroadcastPort = 23757;            // 0 - 65536
	BYTE VoiceOutputVolume = 80;           // 0 - 100
	BYTE VoiceJitterMaxDelay = 10;         // 0 - 100
	BYTE VoiceJitterMaxVariation = 10;     // 0 - 100
	BYTE VoiceJitterInitialVariation = 2;  // 0 - 100
	float VoiceTalkingLevel = 15.f;       // 0.0 - 90.0
	bool MutePlayerVoice = true;
	bool MuteVoiceIngame = false;
};

struct Settings {
	struct Version Version;
	struct Game Game;
	struct Control Control;
	struct Visual Visual;
	struct Audio Audio;
	struct Network Network;
};

struct Settings Settings;



/////////////////////////////////////////////////
//
// lua_CFunctions
// 
/////////////////////////////////////////////////

sGameSettings* g_pGameSettings_008e8410;

int StartGame(lua_State* L)
{
	//StartGameForReal(L, g_pGameSettings_008e8410);
	return LUA_OK;
}

int IsGameStarted2(lua_State* L)
{
	lua_pushboolean(L, g_pGameSettings_008e8410->m_bStarted_0xa0c);
	return LUA_YIELD;
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

	return LUA_YIELD;
}

UINT LoadingTypeOrFlagsMaybe_008e8448;

int UpdateLoadingBar(lua_State* L)
{
	if (LoadingTypeOrFlagsMaybe_008e8448)
	{
		//AddToLoadingBar(luaL_checknumber(L, 1));
	}
}

/////////////////////////////////////////////////
//
// Startup Sequence
// 
/////////////////////////////////////////////////

// 1 = US, 2 = Germany, not 1 or 2 = Europe
// Germany got its own version (after doing some more research and looking at the game files, I see they had to censor it over there.)
// Also, my Canadian copy, which I thought would be the US version is apparently the European version.
uint version_0069c13c = 0;
// I don't know if it's possible to change the value fast enough that the german intro video plays, but you can wait on the title screen to see the german version of the attract video.
// If set to Germany in a US or European copy, the game will crash when loading into a map because it can't find the ragdoll models.


// There's already a function that is internally called StartGame so I had to change this one
void StartStartingGame(int param_1)
{
	const char* version_string;
	lua_State* L = g_pScriptHost->lss2_0x8->L_0x4;
	int originalTop = lua_gettop(L);

	// So glad they used text
	if (version_0069c13c == 1)
	{
		version_string = "VERSION_US";
	}
	else if (version_0069c13c == 2)
	{
		version_string = "VERSION_GERMANY";
	}
	else
	{
		version_string = "VERSION_EUROPE";
	}

	lua_setglobal(L, version_string);
	lua_pushboolean(L, TRUE);
	lua_settable(L, -0x2712);

	lua_pushcclosure(L, StartGame, 0);
	lua_setfield(L, -0x2712, "StartGame");

	lua_pushcclosure(L, IsGameStarted2, 0);
	lua_setfield(L, -0x2712, "IsGameStarted");

	/*
	lua_pushcclosure(L, LoadReplay, 0);
	lua_setfield(L, -0x2712, "LoadReplay");

	lua_pushcclosure(L, SaveReplay, 0);
	lua_setfield(L, -0x2712, "SaveReplay");
	*/

	lua_pushcclosure(L, DEBUGLOG, 0);
	lua_setfield(L, -0x2712, "DebugConsolePrint");

	lua_pushcclosure(L, GetPaletteColour, 0);
	lua_setfield(L, -0x2712, "GetPaletteColor");

	lua_pushcclosure(L, UpdateLoadingBar, 0);
	lua_setfield(L, -0x2712, "UpdateLoadingBar");

	lua_setglobal(L, "CompileDate");
	lua_setglobal(L, "Version 0.28 build 2004.09.20");
	lua_settable(L, -0x2712);

	lua_pushcclosure(L, GetPhrase, 0);
	lua_setfield(L, -0x2712, "GetPhrase");

	lua_createtable(L, 0, 0);
	int idx = lua_gettop(L);
	lua_setglobal(L, "GameFlow");
	lua_pushvalue(L, idx);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "PrepareCupFromProfile");
	lua_pushcclosure(L, PrepareCupFromProfile, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetNumResults");
	lua_pushcclosure(L, GetNumResults, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetPlayerName");
	lua_pushcclosure(L, GetPlayerName, 0);
	lua_settable(L, idx);

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

	lua_setglobal(L, "IsCupRaceLocked");
	lua_pushcclosure(L, IsCupRaceLocked, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetStuntScoreType");
	lua_pushcclosure(L, GetStuntScoreType, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "GetCupSize");
	lua_pushcclosure(L, GetCupSize, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "IsCupActive");
	lua_pushcclosure(L, IsCupActive, 0);
	lua_settable(L, idx);

	lua_setglobal(L, "IsCupRaceCompleted");
	lua_pushcclosure(L, IsCupRaceCompleted, 0);
	lua_settable(L, idx);

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

	lua_setglobal(L, "GM_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_CAREER");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_TIMEATTACK");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_SINGLE_RACE");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_INSTANT_ACTION");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_CRASHTEST_DUMMY");
	lua_pushnumber(L, 5.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_ONLINE_MULTIPLAYER");
	lua_pushnumber(L, 6.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_PARTY");
	lua_pushnumber(L, 7.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_DEVELOPER");
	lua_pushnumber(L, 8.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_TOURNAMENT");
	lua_pushnumber(L, 9.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_SPLITSCREEN");
	lua_pushnumber(L, 10.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GM_TEST");
	lua_pushnumber(L, 11.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "GR_DEFAULT");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_RACE");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_STUNT");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_DERBY");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_HUNTER_PREY");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_ARCADE_ADVENTURE");
	lua_pushnumber(L, 5.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_PONGRACE");
	lua_pushnumber(L, 6.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_TIMEATTACK");
	lua_pushnumber(L, 7.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "GR_TEST");
	lua_pushnumber(L, 8.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "CLASS_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CLASS_C");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CLASS_B");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CLASS_A");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CLASS_FINALS");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CLASS_EXTRA");
	lua_pushnumber(L, 5.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "RESULT_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "RESULT_ABORTED");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "RESULT_FINISHED");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "STUNT_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_CURLING");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BULLSEYE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_HIGHJUMP");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_STONESKIPPING");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_RINGOFFIRE");
	lua_pushnumber(L, 5.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_DARTS");
	lua_pushnumber(L, 6.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BREAKDOWN");
	lua_pushnumber(L, 7.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BLACKDANNY");
	lua_pushnumber(L, 8.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_SKIJUMP");
	lua_pushnumber(L, 9.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_FIELDGOAL");
	lua_pushnumber(L, 10.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BOWLING");
	lua_pushnumber(L, 11.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BASKETBALL");
	lua_pushnumber(L, 12.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_BASEBALL");
	lua_pushnumber(L, 13.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "STUNT_SOCCER");
	lua_pushnumber(L, 14.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "DERBY_NONE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "DERBY_LMS");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "DERBY_WRECKING");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "DERBY_FRAG");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "DERBY_END");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "UPGRADE_DEFAULT");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "UPGRADE_NONE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "UPGRADE_50");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "UPGRADE_100");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "STUNTCAR_CLASS");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "FUNNYCAR_CLASS");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "PLAYERTYPE_UNKNOWN");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "PLAYERTYPE_LOCAL");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "PLAYERTYPE_REMOTE");
	lua_pushnumber(L, 2.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "PLAYERTYPE_OBSERVER");
	lua_pushnumber(L, 3.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "PLAYERTYPE_AI");
	lua_pushnumber(L, 4.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "PLAYERTYPE_SIMULATED");
	lua_pushnumber(L, 5.f);
	lua_settable(L, -0x2712);

	lua_setglobal(L, "CHARACTERTYPE_MALE");
	lua_pushnumber(L, 0.f);
	lua_settable(L, -0x2712);
	lua_setglobal(L, "CHARACTERTYPE_FEMALE");
	lua_pushnumber(L, 1.f);
	lua_settable(L, -0x2712);


	LoadAndSave(param_1);
	RunLUAFromFile("data/Scripts/Levels.bed", auVar1);
	RunLUAFromFile("data/Scripts/Classes.bed", auVar2);
	lua_settop(L, originalTop);
}

void (*PTR_008e8418)(int);

int CheckDirectXVersion(LPBYTE expectedVersion);
HRESULT BasicDlgProc(HWND hWnd, UINT uMsg, short param_3);
UINT SetFPUCW(USHORT in_FPUControlWord);
void DoNothing();

// Turns out, this IS WinMain. IDA detected it immediately.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	HINST_008da564 = hInstance;

	// The random seed is set to the current time
	DWORD seed = timeGetTime();
	srand(seed);

	// Dealing with the setup flag
	setupFlag_008da684 = 0;
	if (lpCmdLine != NULL && (_stricmp(lpCmdLine, "-setup") || _stricmp(lpCmdLine, "setup")))
		setupFlag_008da684 = 1;

	CoInitializeEx(NULL, 0);

	int verCheck = CheckDirectXVersion((LPBYTE)"4.09.00.0904");
	if (verCheck == 0 && DialogBoxParamA(hInstance, (LPCSTR)0x83, NULL, (DLGPROC)BasicDlgProc, 0) == 1)
		return 0xffffffff;

	// Sets unkn_008da6a0 to 1
	SetFPUCW(FPUConW_008d781c);
	LoadBfsList();
	LoadBfsList();
	// Appears to be unused flags, but given the kind of register-passing other functions do, maybe this does some register manipulation that LoadBinaryDatabase picks up on?
	strstr(lpCmdLine, "-binarydb");
	strstr(lpCmdLine, "-bedit");
	//LoadBinaryDatabase(flags);

	UINT_0069c2d0 = (uint)&UINT_008d7bb0;
	// Allocating ~131 KB
	void* newMem = malloc(0x20044);
	if (newMem == NULL)
		UINT_008d780c = 0;
	else
		//UINT_008d780c = FUN_0051c520();
		DoNothing();

	// Allocating 8.2KB
	char** newMem2 = (char**)malloc(0x2008);

	if (newMem2 != NULL)
	{
		newMem2 = NULL;
		newMem2[0x801] = NULL;

		char** ppcVar3 = newMem2 + 0x401;
		// Sets every byte from offset 0x401 - 0x800 to NULL
		for (int i = 0x400; i != 0; i -= 1)
		{
			ppcVar3 = NULL;
			ppcVar3 = ppcVar3 + 1;
		}
		//FUN_00551090(newMem2);
	}
	MEM_008da568 = newMem2;
	//FUN_00550f90(newMem2);
	//FUN_0045lb70(&UINT_0069c128);
	//int iVar1 = FUN_00520cf0();
	int iVar1 = 1;


	// From here its starting to seem like a shutdown sequence.


	if (iVar1 != 0)
		//FreeALotOfMemory();

	CoUninitialize();
	if (UINT_008e855c != 0)
		UINT_008e855c--;

	if (PTR_008e8418 != NULL && UINT_008e855c == 0)
	{
		(*PTR_008e8418)(1);
		PTR_008e8418 = NULL;
	}

	//FUN_0051cdc0();
	newMem = MEM_008da568;
	if (MEM_008da568 != NULL)
	{
		free((void*)((int)MEM_008da568 + 0x2004));
		free(newMem);
	}
	MEM_008da568 = NULL;
	return 0;
}

// Direct Sound and Input

HMODULE DINPUTMODULE_008da744;
FARPROC PTR_DirectInput8Create_008da784;
void* PTR_008da74c;
typedef HRESULT(*dinputFunc)(HINSTANCE, DWORD, REFIID, LPVOID, LPUNKNOWN);

uint LoadDInputLibrary()
{
	DINPUTMODULE_008da744 = LoadLibraryA("dinput8.dll");
	PTR_DirectInput8Create_008da784 = GetProcAddress(DINPUTMODULE_008da744, "DirectInput8Create");
	LPVOID ppvOut = &PTR_008da74c;
	HINSTANCE hInst = GetModuleHandleA(NULL);
	HRESULT returnCode = ((dinputFunc)(*PTR_DirectInput8Create_008da784))(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8A, ppvOut, NULL);
	return returnCode & ((returnCode > -1) ? 0 : -1);
}

HMODULE DSoundModule_006a8598;
HMODULE DSound3DModule_006a859c;
FARPROC PTR_DirectSoundCreate8_006a85bc;
FARPROC PTR_DirectSoundEnumerateA_006a85b8;
uint UINT_00687984;
uint UINT_00684b20 = 0;
uint UINT_00684b24 = (uint)-1;
uint* PTR_UINT_00684570 = &UINT_00684b20;

// Loads the sound module and sets UINT_00687984 to either 7, 8, or 9 based on how much was done.
// If the sound library did not load, it'll try to load DirectDraw, and if that works, it'll be 7
// If the sound library loaded but D3D9 did not, it'll be 8
// If both the sound library and D3D9 loaded, it'll be 9
void LoadDirectSoundAndDrawLibrary()
{
	if (DSoundModule_006a8598 == NULL)
	{
		DSoundModule_006a8598 = LoadLibraryA("dsound.dll");
		if (((int)PTR_UINT_00684570 + 9) & 0x30)
			DSound3DModule_006a859c = LoadLibraryA("dsound3d.dll");

		PTR_DirectSoundCreate8_006a85bc = GetProcAddress(DSoundModule_006a8598, "DirectSoundCreate8");
		if (PTR_DirectSoundCreate8_006a85bc == NULL)
			PTR_DirectSoundCreate8_006a85bc = GetProcAddress(DSoundModule_006a8598, "DirectSoundCreate");

		PTR_DirectSoundEnumerateA_006a85b8 = GetProcAddress(DSoundModule_006a8598, "DirectSoundEnumerateA");
		//FUN_0063045d(DSoundModule_006a8598, PTR_DirectSoundCreate8_006a85bc);
		if (PTR_DirectSoundCreate8_006a85bc == NULL)
		{
			HMODULE hModule = LoadLibraryA("ddraw.dll");
			if (hModule != NULL)
			{
				FARPROC pFVar3 = GetProcAddress(hModule, "DirectDrawCreateEx");
				if (pFVar3 != NULL)
					UINT_00687984 = 7;

				FreeLibrary(hModule);
			}
		}
		else
		{
			UINT_00687984 = 8;
			char systemDir[0x104];
			if (GetSystemDirectoryA(systemDir, 0x104) != 0)
			{
				char fileDir[0x10C];
				String_SimpleCopy(fileDir, systemDir);
				String_Append(fileDir, "\\d3d9.dll");
				FILE** file = NULL;//FUN_0061f9bc(fileDir, NULL, 0);
				if (file != NULL)
				{
					//OpenDLLFile(file);
					UINT_00687984 = 9;
				}
			}
		}
	}
	return;
}

// ASPI

HMODULE wnaspi_006a32d0;
FARPROC PTR_GetASPI32SupportInfo_006a32d4;
FARPROC PTR_SendASPI32Command_006a32d8;
char CHAR_006a32cc;
uint UINT_006a328c;
int INT_006a32e4;
int INT_007a32e4;


uint ASPI_Initialize(char param_1)
{
	if (CHAR_006a32cc != NULL)
		return 0;

	int errorCode, pvVar5;

	// Ghidra says there's a for loop, but it's done in a single STOSD instruction that is basically a memset but instead of bytes it's words.
	__stosd((unsigned long*)&UINT_006a328c, 0, 8);


	INT_007a32e4 = 0;
	if ((param_1 == NULL))//&& (FUN_00621944() != NULL))
	{
		//PTR_GetASPI32SupportInfo_006a32d4 = FUN_00620525;
		//PTR_SendASPI32Command_006a32d8 = FUN_00621ea4;
	}
	else
	{
		
		__stosd((unsigned long*)&UINT_006a328c, 0, 8);

		char* local_804;
		INT_006a32e4 = 0;
		String_SimpleCopy(local_804, "wnaspi32.dll");
		wnaspi_006a32d0 = LoadLibraryA(local_804);
		if (wnaspi_006a32d0 == NULL)
		{
			GetSystemDirectoryA(local_804, 0x7FF);
			String_Append(local_804, "\\");
			String_Append(local_804, "wnaspi32.dll");
			wnaspi_006a32d0 = LoadLibraryA(local_804);
			if (wnaspi_006a32d0 == NULL)
			{
				errorCode = 1;
				//pvVar5 = extraout_ECX_01;
				goto exitPoint;
			}
		}
		PTR_GetASPI32SupportInfo_006a32d4 = GetProcAddress(wnaspi_006a32d0, "GetASPI32SupportInfo");
		PTR_SendASPI32Command_006a32d8 = GetProcAddress(wnaspi_006a32d0, "SendASPI32Command");
		if (PTR_GetASPI32SupportInfo_006a32d4 == NULL || PTR_SendASPI32Command_006a32d8 == NULL)
		{
			errorCode = 5;
			//pvVar5 = extraout_ECX_02;
			goto exitPoint;
		}
	}
	//uint uVar4 = 0;
	errorCode = (*PTR_GetASPI32SupportInfo_006a32d4)();
	pvVar5 = errorCode >> 8 & 0xFF;
	if (pvVar5 != 0x1)
	{
		int pvVar8 = pvVar5;
		//FUN_006205e0((int)pvVar5);
		//FUN_006218cd(pvVar8);
		return pvVar5 << 8 | 3;
	}

exitPoint:
	//...
	return 0;
}




/////////////////////////////////////////////////
//
// Direct X
// 
/////////////////////////////////////////////////

// CheckDirectXVersion
//
// Takes an expected version and compares that to the current version
// stored in the registry. 

int CheckDirectXVersion(LPBYTE expectedVersion)
{
	HKEY hkey;
	LPBYTE lpdata;
	LPDWORD lpcbdata;

	LSTATUS oStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\DirectX", 0, 1, &hkey);

	if (oStatus < 0)
		return oStatus & 0xFFFFFF00;

	LSTATUS qStatus = RegQueryValueExA(hkey, "Version", NULL, NULL, lpdata, lpcbdata);
	LSTATUS cStatus = RegCloseKey(hkey);

	if (qStatus < 0 || lpcbdata > (LPDWORD)0x20)
		return cStatus & 0xFFFFFF00;


	LPBYTE dataptr = lpdata;
	BYTE currentData;
	bool isOlder;

	// Goes through the version string, and if it reaches equal or greater numbers,
	// it'll return 1, otherwise, it'll return a concatenation that gives some
	// info about the differences.
	while (true)
	{
		currentData = *dataptr;
		isOlder = currentData < *expectedVersion;
		if (currentData != *expectedVersion)
			break;

		if (currentData == 0)
			return 1;

		currentData = dataptr[1];
		isOlder = currentData < expectedVersion[1];
		if (currentData != expectedVersion[1])
			break;

		dataptr += 2;
		expectedVersion += 2;

		if (currentData == 0)
			return 1;
	}

	// I worked out the complicated version and converted it to:
	uint result = isOlder ? -1 : 1;

	// I made a couple mistakes with this line, it's concatenating bytes, and it shifted right initially.
	// Is this faster than ANDing?
	return ((result >> 8) << 8) | (result > -1);
}

IDirect3D9* D3D9_008da784;
float FLOAT_008e5e80;
LPDIRECT3DDEVICE9 LPDIRECT3DDEVICE9_008da788;

LRESULT WndProcWithMoreSteps(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateD3DWindow(HWND parent, HINSTANCE hInstance, LPCSTR title, HICON icon, HCURSOR cursor, astruct_110* param_6, uint* param_7, BYTE param_8, uint flags, register int* in_EAX)
{
	int posX;
	int posY;
	uint style;
	WNDCLASSA newWindow;
	HWND hWnd;

	// Starts with clearing two buffers, not sure what they are yet
	uint* tempPtr = &UINT_008e5770;
	for (posX = 0x180; posX; posX--)
	{
		*tempPtr = NULL;
		tempPtr = tempPtr + 1;
	}
	tempPtr = &UINT_008e5d70;
	for (posX = 0x20; posX; posX--)
	{
		*tempPtr = NULL;
		tempPtr = tempPtr + 1;
	}

	if (D3D9_008da784 != NULL || (D3D9_008da784 = Direct3DCreate9(D3D_SDK_VERSION), D3D9_008da784 != NULL))
	{
		HINST_008da2dc = hInstance;
		// UINT_008da270 ends up as 19, does not seem to change.
		UINT_008da270 = flags;
		int nWidth;
		int nHeight;
		int iStack_7c;
		// In binary: 0000 0?00
		if ((flags & 4) == 0)
		{
			nWidth = param_6->field0_0x4;
			nHeight = param_6->field1_0x8;
		}
		else
		{
			style = ((unsigned int)((flags & 0x20) != 0) & 0xff310000) + WS_OVERLAPPEDWINDOW;
			if (parent != NULL)
			{
				style |= WS_CHILD;
			}

			param_7 = 0;
			in_EAX[0x8a] = 1;
			// I don't know which function is actually here, but whatever it is, takes no argument.
			D3D9_008da784->AddRef();
			posX = GetSystemMetrics(SM_CXEDGE);
			posY = GetSystemMetrics(SM_CXSIZEFRAME);
			nWidth = GetSystemMetrics(SM_CXBORDER);
			nWidth = posX + posY + nWidth;
			posX = GetSystemMetrics(SM_CYEDGE);
			posY = GetSystemMetrics(SM_CYFRAME);
			int iVar1 = GetSystemMetrics(SM_CYBORDER);
			int iVar2 = GetSystemMetrics(SM_CYSIZE);
			nHeight = iVar2 + param_6->field1_0x8 + 1 + (posX + posY + iVar1);
			nWidth = iStack_7c;
		}
		newWindow.style = 0;
		newWindow.lpfnWndProc = (WNDPROC)WndProcWithMoreSteps;
		newWindow.cbClsExtra = 0;
		newWindow.cbWndExtra = 0;
		newWindow.hInstance = hInstance;
		newWindow.hIcon = icon;
		newWindow.hCursor = cursor;
		newWindow.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
		newWindow.lpszMenuName = NULL;
		newWindow.lpszClassName = "BDX9 Render Window";
		RegisterClassA(&newWindow);
		// In binary: 00?0 0000
		uint flagTest = flags & 0x20;
		if (flagTest == 0)
		{
			posY = CW_USEDEFAULT;
			posX = CW_USEDEFAULT;
		}
		else
		{
			posY = 0;
			posX = 0;
		}

		// Creating the window
		HWND_008da79c = CreateWindowExA(WS_EX_LEFT, "BDX9 RenderWindow", title, style, posX, posY, nWidth, nHeight, parent, NULL, hInstance, NULL);

		if (HWND_008da79c != NULL)
		{
			posX = ShowCursor(in_EAX[0x8a]);
			hWnd = HWND_008da79c;
			in_EAX[0x69] = posX;
			ShowWindow(hWnd, SW_NORMAL);
			EnableWindow(HWND_008da79c, TRUE);
			UpdateWindow(HWND_008da79c);
			SetFocus(HWND_008da79c);
			/*
			if (flagTest == 0)
			{
				DAT_008da410 = PTR_008da7a0->field3_0x98;
				DAT_008da414 = PTR_008da7a0->field4_0x9c;
			}
			UINT_008da418 = uStack_88;
			astruct135_008da420 = param_8;
			HWND_008da42c = HWND_008da79c;
			DAT_008da430 = in_EAX[0x8A];
			DAT_008da41c = (flags & 1) ? 2 : 1;
			DAT_008da428 = 1;
			DAT_008da434 = 1;

			if (param_7 == NULL)
				// ???
				param_7 = NULL;

			DAT_008da440 = param_7;
			DAT_008da444 = 0;
			DAT_008da43c = 0;
			
			HardwareCompatibilityTest2(in_EAX);
			posX = FUN_005a6a50();
			*/
			posX = 0;
			if (posX > -1)
			{
				in_EAX[8] = 1;
				in_EAX[7] = 1;
				nWidth = param_6->field0_0x4;
				in_EAX[2] = nWidth;
				flagTest = param_6->field1_0x8;
				in_EAX[3] = flagTest;

				posX = param_6->field2_0xc;
				in_EAX[4] = posX;
				posY = *(int*)LPDIRECT3DDEVICE9_008da788;
				// Don't know which function is actually here, but it takes no argument.
				((LPDIRECT3DDEVICE9)posY)->AddRef();
				uint uVar5 = 2;
				// Whatever the above function was
				LPDIRECT3DDEVICE9_008da788->AddRef();
				float* pfVar4 = &FLOAT_008e5e80;
				// The same function, but now it suddenly takes 2 arguments.
				/*
				LPDIRECT3DDEVICE9_008da788->AddRef(0x10, &FLOAT_008e5e80);
				LPDIRECT3DDEVICE9_008da788->AddRef(0x11, &FLOAT_008e5e80);

				**(*in_EAX + 0x30)(0, 0, pfVar4, uVar5, 0xFFFFFFFF);

				// The EDX register is used as the second parameter, which contains pfVar4 when calling the previous function.
				// Then it's used as the D3D Format for the hardware compatibility test ?
				HardwareCompatibilityTest((int)in_EAX, pfVar4);
				*/
			}
		}

	}
}

// It seems like the second unknown can be swapped out, at least on other functions
D3DFORMAT D3DFMTs_0069bfe8[20] = {
	D3DFMT_UNKNOWN,
	D3DFMT_UNKNOWN,
	D3DFMT_P8,
	D3DFMT_X1R5G5B5,
	D3DFMT_R8G8B8,
	D3DFMT_X8R8G8B8,
	D3DFMT_V8U8,
	D3DFMT_L6V5U5,
	D3DFMT_X8L8V8U8,
	D3DFMT_Q8W8V8U8,
	D3DFMT_DXT1,
	D3DFMT_DXT2,
	D3DFMT_DXT3,
	D3DFMT_DXT4,
	D3DFMT_DXT5,
	D3DFMT_A1R5G5B5,
	D3DFMT_A4R4G4B4,
	D3DFMT_A8R8G8B8,
	D3DFMT_A8
};

// Returns the index of a given format into D3DFMTs_0069bfe8, with hard-coded returns instead of finding it.
// There are a few incorrect indices and a format that isn't on the current list, indicating it used to be different and they forgot to update this function.
uint GetIndexOfDXFormat(D3DFORMAT input)
{
	if (input < 0x2A)
	{
		if (input == D3DFMT_P8)
			return 2;

		switch (input)
		{

		case D3DFMT_R8G8B8:
			return 5;

		case D3DFMT_A8R8G8B8:
			return 0x12;

		case D3DFMT_X8R8G8B8:
			return 6;

		case D3DFMT_R5G6B5:
			return 4;

		case D3DFMT_X1R5G5B5:
			return 3;

		case D3DFMT_A1R5G5B5:
			return 0x10;

		case D3DFMT_A4R4G4B4:
			return 0x11;

		case D3DFMT_A8:
			return 0x13;

		}
	}
	else if (input < 0x31545845)
	{
		if (input == D3DFMT_DXT1)
			return 0xB;

		switch (input)
		{

		case D3DFMT_V8U8:
			return 7;

		case D3DFMT_L6V5U5:
			return 8;

		case D3DFMT_X8L8V8U8:
			return 9;

		case D3DFMT_Q8W8V8U8:
			return 10;

		}
	}
	else if (input < 0x34545845)
	{

		if (input == D3DFMT_DXT4)
			return 0xE;

		if (input == D3DFMT_DXT2)
			return 0xC;

		if (input == D3DFMT_DXT3)
			return 0xD;

	}
	else if (input == D3DFMT_DXT5)
		return 0xF;

	return 0;
}

D3DFORMAT D3DFMT_0069bfec;
D3DFORMAT D3DFMT_008da418;
uint UINT_008da7d8;

BYTE BYTE_008da490[20];

// For every D3DFORMAT, Run a CheckDeviceFormat() and if it succeeds, set a corrosponding flag.
// So in binary it can be represented like C-TS cvt-
// Where:
// c indicates the format can be used in a cube texture
// v indicates the format can be used in a volume texture
// t indicates the format can be used in a 2D texture
// C indicates the format can be used in a cube texture for a render target
// T indicates the format can be used in a 2D texture for a render target
// S indicates the format can be used on a surface for a render target
void HardwareCompatibilityTest(int struct_1, D3DFORMAT extraout_EDX)
{
	D3DFMTs_0069bfe8[1] = D3DFMT_008da418;
	UINT_008da7d8 = GetIndexOfDXFormat(D3DFMT_008da418);
	UINT uVar1 = *(uint *)(struct_1 + 0x70);
	// Starts with the second D3DFMT_UNKNOWN, so this function was also not updated after the list was changed.
	uint FMTIndex = 1;
	HRESULT result;
	D3DFORMAT uVar3 = extraout_EDX;
	do
	{
		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, uVar3, 0, D3DRTYPE_TEXTURE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 2;

		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, D3DFMT_008da418, 0, D3DRTYPE_VOLUMETEXTURE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 4;

		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, D3DFMT_008da418, 0, D3DRTYPE_CUBETEXTURE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 8;

		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, D3DFMT_008da418, D3DUSAGE_RENDERTARGET, D3DRTYPE_SURFACE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 0x10;

		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, D3DFMT_008da418, D3DUSAGE_RENDERTARGET, D3DRTYPE_TEXTURE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 0x20;

		result = D3D9_008da784->CheckDeviceFormat(uVar1, D3DDEVTYPE_HAL, D3DFMT_008da418, D3DUSAGE_RENDERTARGET, D3DRTYPE_CUBETEXTURE, D3DFMTs_0069bfe8[FMTIndex]);
		if (result == D3D_OK)
			BYTE_008da490[FMTIndex] |= 0x80;

		FMTIndex += 1;
		uVar3 = D3DFMT_008da418;

	} while (FMTIndex < 0x14);
	return;
}


uint UINT_006d6814;
uint* UINT_006d68f4;
uint UINT_006d68f8;
uint DAT_0069c138;
HWND* PTR_008da560;
uint UINT_006d68fc;



uint UINT_008da540;
HICON HICON_008da544;
uint UINT_008da548;
// The index of language.dat files. From 0-7
int LANGUAGE_006d6914;


struct astruct_164 {
	void* field_0x0, *field_0x4;
	// 4 undefined bytes at offset 0x8
	int field_0xc;
	uint unk_0x10, unk_0x14, unk_0x18, unk_0x20;
};

float g_fAspectRatioX_0069be18;
float g_fAspectRatioY_0069be1c;

void SetAspectRatio(float x, float y)
{
	g_fAspectRatioX_0069be18 = x;
	g_fAspectRatioY_0069be1c = y;
}

INT_PTR DlgProc_SettingsPanel(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Creating setup window
//
int CreateSetupWindow(astruct_140* param_1, HINSTANCE hInst, int showSetup, int setupFlag)
{
	param_1->hinst_0x58 = hInst;

	// Retrieve the version from Lua, which is kinda strange since that variable is already supposed to contain the version, it's where Lua got it from.
	//version_0069c13c = Lua_GetVersion();
	//copyOfVersion_008da550 = Lua_GetVersion();

	uint* uVar7;
	uint uVar13;
	HCURSOR cursor;

	// So I looked it up and I don't know why it has both a return value but also a pointer to place the return value in.
	// I guess it could save a few lines of code if you need it for a parameter but also want to store it, but I don't know, variable = _time32(NULL) isn't that bad, and it would be even easier if you didn't have to type out NULL
	//FUN_00529c60(_time32(NULL));

	//uint iVar = FileObject_BuildNew2();
	uint iVar = 0;
	if (iVar == NULL)
	{
		showSetup = 1;
	}
	if (setupFlag != 0)
	{
		showSetup = 1;
	}
	astruct_164* pvVar8 = (astruct_164*)malloc(sizeof(astruct_164));

	// ?
	if (pvVar8 == NULL)
		pvVar8 = NULL;
	else
	{
		pvVar8->field_0xc = 0;
		pvVar8->field_0x0 = pvVar8;
		pvVar8->field_0x4 = pvVar8;
		pvVar8->unk_0x10 = 0;
		pvVar8->unk_0x14 = 0;
		pvVar8->unk_0x18 = 0x20;
		//Initialize();
	}
	HICON_008da544 = LoadIconA(hInst, (LPCSTR)0x66);
	uVar7 = &UINT_008da540;

	if (iVar == NULL)
		//SettingsRelated();

	iVar = uVar7[1];
	uVar13 = UINT_006d6900;
	do
	{
		UINT_006d6900 = uVar13;
		if (iVar == uVar7[0])
		{
			int iVar17 = 0;
			//iVar17 = FUN_0044f580();
			if (iVar17 == 0)
			{
				//SettingsRelated();
				showSetup = 1;
			}
			//OpenLanguageDat(LANGUAGE_006d6914);
			if (showSetup != 0)
			{
				HGDIOBJ_006d67b8 = LoadImageA(hInst, (LPCSTR)0x82, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
				INT_PTR IVar10 = DialogBoxParamA(hInst, (LPCSTR)0x65, NULL, (DLGPROC)DlgProc_SettingsPanel, 0);
				DeleteObject(HGDIOBJ_006d67b8);
				if (IVar10 == 0)
					return 0;

				if (IVar10 != 1)
					return 2;

				//FUN_0044f520();
				if (setupFlag != 0)
				{
					return 1;
				}
			}
			//OpenLanguageDat(LANGUAGE_006d6814);
			DAT_0069c138 = LANGUAGE_006d6914;
			cursor = LoadCursorW(NULL, IDC_ARROW);
			bool bVar19 = UINT_006d6908 != 0;
			param_1->field1_0x44 = 1;
			iVar = (int)bVar19 | 0x10;
			if ((*(byte*)(iVar17 + 0x18) & 8) != 0)
			{
				iVar = (int)bVar19 | 0x18;
				param_1->field0_0x40 = 1;
			}
			HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar, (int*)hInst);
			if (HWND_008da56c == NULL)
			{
				DestroyWindow(*PTR_008da560);
				UINT_006d6908 = 0;
				HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar & 0xfffffffe, (int*)UINT_006d68f4);
				if (HWND_008da56c == NULL)
				{
					MessageBoxA(NULL, "Cannot open display mode", "FlatOut 2 error", MB_ICONINFORMATION);
					return 0;
				}
			}
			// I now know what's going on here
			// I'm going to replace hInst and showSetup with more descriptive variables
			float AspectX = 4.f;
			float AspectY = 3.f;
			switch (UINT_006d68f8)
			{
			case 0:
				AspectX = 4.f;
				AspectY = 3.f;
				break;
			case 1:
				AspectX = 16.f;
				AspectY = 10.f;
				break;
			case 2:
				AspectX = 16.f;
				AspectY = 9.f;
				break;
			case 3:
				AspectX = 5.f;
				AspectY = 4.f;
				break;
			}
			SetAspectRatio(AspectX, AspectY);
		}
	} while (false);

}

int* PTR_008da718;
HINSTANCE HINSTANCE_008da2dc;
uint UINT_008da798;

// Destroying Windows
void __fastcall DestroyWindow(int param_1)
{
	if (LPDIRECT3DDEVICE9_008da788 != NULL)
		LPDIRECT3DDEVICE9_008da788->Release();

	if (D3D9_008da784 != NULL)
		D3D9_008da784->Release();

	HWND hWnd = HWND_008da79c;
	char className[0x3F];
	if (HWND_008da79c != NULL)
	{
		HWND_008da79c = NULL;
		UINT_008da798 = 0;
		GetClassNameA(hWnd, className, 0x3F);
		DestroyWindow(hWnd);
		UnregisterClassA(className, HINSTANCE_008da2dc);
		ShowCursor(TRUE);
	}
	LPDIRECT3DDEVICE9_008da788 = NULL;
	D3D9_008da784 = NULL;
	PTR_008da718 = NULL;
	return;
}

HANDLE PTR_008da62c[];

LRESULT DeleteUpdateThread()
{
	HANDLE* pHandle1 = &PTR_008da62c[2];
	if (PTR_008da62c[2] != NULL)
	{
		HANDLE* pHandle2 = &PTR_008da62c[3];
		SetEvent(*pHandle2);
		WaitForSingleObject(*pHandle1, 0xFFFFFFFF);
		CloseHandle(*pHandle1);
		CloseHandle(*pHandle2);
		*pHandle2 = NULL;
		*pHandle1 = NULL;
	}
	return 0;
}




/////////////////////////////////////////////////
//
// WndProcs
// 
/////////////////////////////////////////////////

DLGPROC Dlgproc;

INT_PTR DlgProc_SettingsPanel(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = hWnd;
	LRESULT LVar6;
	LRESULT* iVar10, * iVar11;
	if (uMsg != WM_INITDIALOG)
	{
		if (uMsg == WM_NOTIFY)
		{
			if (((NMHDR*)lParam)->idFrom == 0x43d)
			{
				if (((NMHDR*)lParam)->code == -0x10)
				{
					// There were two options for it: WM_PSD_PAGESETUPDLG, and WM_USER. I chose the former.
					UINT_006d6900 = SendDlgItemMessageA(hWnd, 0x43d, WM_PSD_PAGESETUPDLG, 0, 0);
					UINT_008db344[UINT_008da548 + 0x14] = UINT_006d6900;
				}
				return 1;
			}
		}
		else if (uMsg == WM_COMMAND)
		{
			// Sent when the user selects a command item from a menu, when a control sends
			// a notification message to it's parent window, or when an accelerator keystroke
			// is translated.
			if (wParam == 1)
			{
				LVar6 = SendDlgItemMessageA(hWnd, 0x3eb, BM_GETCHECK, 0, 0);
				UINT_006d6908 = (uint)(LVar6 == 1);
				LVar6 = SendDlgItemMessageA(hWnd, 0x462, BM_GETCHECK, 0, 0);
				UINT_006d690c = (uint)(LVar6 == 1);
				LVar6 = SendDlgItemMessageA(hWnd, 0x44e, BM_GETCHECK, 0, 0);
				UINT_006d68d0 = (uint)(LVar6 == 1);
				/*
				iVar11 = &UINT_008db344[UINT_008da548];
				iVar10 = &UINT_008db344[UINT_008da548];
				UINT_006d68d8 = iVar11[0x38];
				DAT_006d68dc = iVar11[0x3c];
				DAT_006d68e0 = iVar11[0x40];
				DAT_006d68e0 = iVar11[0x44];
				UINT_006d68e8 = *(uint*)(iVar10[4] + 4);
				DAT_006d68ec = *(uint*)(iVar10[4] + 8);
				UINT_006d68f0 = *(uint*)(iVar10[4] + 0xC);
				*/
				EndDialog(hWnd, 1);
				return 1;
			}
			if (wParam == 2)
			{
				EndDialog(hWnd, 2);
				return 1;
			}
			// Clicking on the logo in the settings panel
			if (wParam == 0x3fc)
				
			{
				HINSTANCE errorCode = ShellExecuteA(hWnd, lpOperation_0066ab90, "http://www.flatoutgame.com/", NULL, NULL, TRUE);
				if ((INT_PTR)errorCode < 33)
					ShellExecuteA(hWnd, lpOperation_0066ab90, "iexplorer.exe", "http://www.flatoutgame.com/", NULL, TRUE);

				return 1;
			}
			// Control message
			if (wParam >> 16 == 9)
			{
				LRESULT WVar4 = SendMessageA((HWND)lParam, 0x147, 0, 0);
				LRESULT DVar8 = SendMessageA((HWND)lParam, 0x150, WVar4, 0);
				if (WVar4 != 0xffffffff)
				{
					switch (wParam & 0xffff)
					{
					case 1000:
						if (DVar8 != UINT_008da548)
						{
							UINT_008da548 = DVar8;
							//FUN_0044fbd0();
							return 1;
						}
						break;
					case 0x3e9:
						iVar10 = (LRESULT*)(UINT_008da548 * 0x24);
						LRESULT piVar1 = iVar10[(int)UINT_008db344];
						iVar10[(int)UINT_008db344 + 8] = DVar8;
					}
				}
			}
		}
	}
}

HRESULT BasicDlgProc(HWND hWnd, UINT uMsg, short param_3)
{
	if (uMsg == WM_COMMAND)
	{
		if (param_3 == 1)
		{
			EndDialog(hWnd, 1);
			return 1;
		}
		if (param_3 == 2)
		{
			EndDialog(hWnd, 2);
			return 1;
		}
	}
	return 0;
}

class AutoClass15
{
private:
	// 8 undefined bytes at offset 0x0
	void (**ptr_0x8)(); // array of methods
	// so many undefined bytes at offset 0xC
	int unkn_0x30;
	int int_0x34;
	WPARAM wParam_0x38;
	uint flags_0x3c;
	// I don't know if it actually returns a char but that's the type ghidra chose.
	char (*wndProcIsh_0x50)(HWND, UINT, WPARAM, LPARAM, WPARAM*, uint);
	
public:
	uint WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		WPARAM copy = wParam;
		char result;
		if (this->wndProcIsh_0x50 && this->wndProcIsh_0x50(hWnd, uMsg, wParam, lParam, &copy, 0))
			return wParam;

		int* piVar1 = PTR_008da718;
		if (uMsg < WM_SETCURSOR + 1)
		{
			// The original code uses an else-if chain but I thought this looked cleaner.
			switch (uMsg)
			{
			case WM_SETCURSOR:
				if ((this->flags_0x3c != 0) && (this->unkn_0x30 == 0) && (PTR_008da718[8] != NULL))
				{
					SetCursor(NULL);
					return 1;
				}
				break;

			case WM_SIZE:
				if ((copy == 4) || (copy == 1))
				{
					this->flags_0x3c = 0;
					piVar1[7] = 0;
				}
				else
				{
					this->flags_0x3c = 1;
					piVar1[7] = 1;
				}
				break;

			case WM_CLOSE:
				PostQuitMessage(0);
				return 0;

			case WM_ACTIVATEAPP:
				this->wParam_0x38 = copy;

			}
		}
		else if (uMsg == WM_NCHITTEST)
		{
			if (this->unkn_0x30 == 0)
				return 1;
		}
		else if (uMsg == WM_SYSCOMMAND)
		{
			// Credit to alex on the FOJ discord, Ghidra doesn't even have these as equates.
			if (copy == SC_KEYMENU || copy == SC_SIZE || copy == SC_MOVE || copy == SC_MAXIMIZE || copy == SC_SCREENSAVE || copy == SC_MONITORPOWER)
				return 1;

		}
		return DefWindowProcA(hWnd, uMsg, copy, lParam);
	}

	bool RunMessageLoop(int bWait)
	{
		tagMSG msg;
		this->ptr_0x8[1]();
		if (this->int_0x34 != 0)
			return false;

		while (true)
		{
			while (true)
			{
				BOOL BVar1 = PeekMessageA(&msg, NULL, 0, 0, 1);
				if (!BVar1 && !bWait) goto LAB_00451503;
				if (BVar1) break;
				if (bWait)
				{
					if (this->flags_0x3c != 0) goto LAB_00451503;
					WaitMessage();
				}
			}
			if (msg.message == 0x12) break;
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		this->int_0x34 = 1;
	LAB_00451503:
		return this->int_0x34 == 0;
	}

};

HRESULT WndProcWithMoreSteps(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// One of those things that is making me think this was written in C (or maybe even assembly).
	// Jumps directly to a WndProc function that apparently came from a class, without an object to reference.
	// Assumes the owner of the function is already in the ECX register.
	AutoClass15* in_ECX;
	in_ECX->WndProc(hWnd, uMsg, wParam, lParam);
	return 0;
}




/////////////////////////////////////////////////
//
// Windows Registry
// 
/////////////////////////////////////////////////


uint GetKeyFromRegistry(char* keyName, LPBYTE out_data, DWORD size_of_out_data)
{
	uint output = -1;
	bool done = false;
	LSTATUS result;
	HKEY key;
	CharLowerBuffA(keyName, strlen(keyName));
	char subKey[512];
	if (RegOpenKeyA(HKEY_CLASSES_ROOT, "clsid", &key) == ERROR_SUCCESS)
	{
		uint depth = 0;
		do 
		{
			do
			{
				if (done) goto Exit;
				result = RegEnumKeyA(key, depth, subKey, 0x200);
				depth += 1;
				if (result != ERROR_SUCCESS) goto Exit;
				CharLowerBuffA(subKey, strlen(subKey));
			} while (strcmp(subKey, keyName) != 0);
			HKEY newKey;
			HKEY newSubKey;
			if (RegOpenKeyExA(key, subKey, 0, KEY_READ, &newKey) == ERROR_SUCCESS)
			{
				if (RegOpenKeyExA(newKey, "InprocServer32", 0, KEY_READ, &newSubKey) == ERROR_SUCCESS)
				{
					DWORD type = REG_CREATED_NEW_KEY;
					if (RegQueryValueExA(newSubKey, NULL, NULL, &type, out_data, &size_of_out_data) == ERROR_SUCCESS)
					{
						OFSTRUCT reOpenBuf;
						ZeroMemory(&reOpenBuf, 0x88);
						reOpenBuf.cBytes = 0x88;
						if (OpenFile((LPCSTR)out_data, &reOpenBuf, OF_EXIST))
						{
							output = 0;
						}
					}
					RegCloseKey(newSubKey);
				}
				RegCloseKey(newKey);
			}
			done = true;
		} while (result == ERROR_SUCCESS);
	Exit:
		RegCloseKey(key);
	}
	return output;
}

static char* ReadCLSIDKey(HKEY hkey, LPCSTR subKey, int param_3, DWORD cbData)
{
	PHKEY result;
	HKEY hKey;
	char* output = (char*)cbData;
	if (cbData == 0)
	{
		if (RegOpenKeyExA(hkey, subKey, 0, KEY_READ, result) == ERROR_SUCCESS)
		{
			DWORD keyType = 1;
			cbData = 0x100;
			char data[200];

			if (RegQueryValueExA(hKey, "clsid", NULL, &keyType, (LPBYTE)data, &cbData) == ERROR_SUCCESS)
			{
				char* keyName;
				BYTE out_data[0x200];
				// Using an uninititialized string as the keyName.
				if (GetKeyFromRegistry(keyName, out_data, 0x200) == ERROR_SUCCESS)
				{
					if ((output = (char*)malloc(0x29C)) != NULL)
					{
						memset(output, 0, 0x29C);
						*(int*)output = param_3;

						OLECHAR olestr[0x100];
						_GUID clsid;

						MultiByteToWideChar(0, 0, data, -1, olestr, 100);
						if (CLSIDFromString(olestr, &clsid) == ERROR_SUCCESS)
							memcpy(output + 1, &clsid, 0x10);
						
						keyType = 1;
						cbData = 0x100;

						if (RegQueryValueExA(hKey, "description", NULL, &keyType, (LPBYTE)data, &cbData) == ERROR_SUCCESS)
							subKey = data;

						strcpy(output + 0x85, subKey);
					}
				}
			}
			
		}
		RegCloseKey(hKey);
	}
	else
	{
		char** ppiVar1 = (char**)(cbData + 0x298);
		char* piVar4 = ReadCLSIDKey(hKey, subKey, param_3 + 1, (DWORD)*ppiVar1);
		*ppiVar1 = piVar4;
	}

	return output;
}




/////////////////////////////////////////////////
//
// Time
// 
/////////////////////////////////////////////////

DWORD GetSeconds()
{
	LARGE_INTEGER local_c;
	LARGE_INTEGER local_14;
	if (QueryPerformanceCounter(&local_c))
	{
		QueryPerformanceFrequency(&local_14);
		LONGLONG lVar3 = Int32x32To64(local_c.QuadPart, 1000000);
		return lVar3 / (lVar3 >> 0x20);
	}
	return timeGetTime() * 1000;
}

void GetSecondsByRef(DWORD& out_seconds)
{
	out_seconds = GetSeconds();
	return;
}

DWORD GetMiliseconds()
{
	return GetSeconds() / 1000;
}




/////////////////////////////////////////////////
//
// Network
// 
/////////////////////////////////////////////////

bool StringAddressToBinaryRepresentation(char* stringAddress, ulong* out_addr)
{
	int net1, net2, host1, host2;

	int occurences = sscanf(stringAddress, "%d.%d.%d.%d", &net1, &net2, &host1, &host2);
	if (occurences < 4)
		return false;

	ulong binary = inet_addr(stringAddress);
	*out_addr = binary;
	return binary != INADDR_NONE;
}

unsigned int AsyncMaxWaitTime_00684b18;

void MaybeSleep(DWORD miliseconds)
{
	if (UINT_00684b24 != 0xD)
		Sleep(miliseconds);

	return;
}

void GetWSAHostName(char* stringAddress, int param_2, ushort extraout_var)
{
	HANDLE hRequest;
	bool bVar1 = StringAddressToBinaryRepresentation(stringAddress, (ulong*)hRequest);
	if (((extraout_var << 1) | bVar1) == 0)
	{
		char* result = (char*)malloc(0x400);
		hRequest = WSAAsyncGetHostByName(NULL, 0, stringAddress, result, 0x400);

		uint timePassed = 0;
		uint start = GetMiliseconds();
		uint now;

		// Waiting for response
		while (result == 0)
		{
			now = GetMiliseconds();
			timePassed += now - start;
			if (AsyncMaxWaitTime_00684b18 <= timePassed)
			{
				WSACancelAsyncRequest(hRequest);
				return;
			}
			MaybeSleep(10);
			start = now;
		}
	}
}

// Isn't this just an infinite loop?
void MaybeSleepLoop(FILE** fileArray)
{
	while (fileArray[10] != NULL)
		MaybeSleep(10);

	return;
}

BYTE lpData_006a04b8[0x104];

BYTE* CreateGameSpyRegistry()
{
	DWORD type = REG_SZ;
	DWORD length = 0x104;
	HKEY hKey;
	LSTATUS LVar2 = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\GameSpy\\GameSpy 3D\\Registration", 0, KEY_ALL_ACCESS, &hKey);
	LSTATUS LVar3 = RegQueryValueExA(hKey, "Crypt", NULL, &type, lpData_006a04b8, &length);

	if (LVar3 == ERROR_SUCCESS)
	{
		if (String_GetLength((const char*)lpData_006a04b8) == 19)
			goto CreateGameSpyRegistry_Exit;
	}
	//FUN_005e4ad0();
	if (LVar2 != ERROR_SUCCESS)
	{
		DWORD DStack_4;
		RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\GameSpy\\GameSpy 3D\\Registration", NULL, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &DStack_4);
	}
	RegSetValueExA(hKey, "Crypt", NULL, REG_SZ, lpData_006a04b8, String_GetLength((const char*)lpData_006a04b8));

CreateGameSpyRegistry_Exit:
	RegCloseKey(hKey);

}

// The newState determines which character is set to '\1' in the string.
// " (after 256 characters) 0 ? ? ? 2 ? ? ? 1;
int SetState(char** out_string, int newState)
{
	 char* theString = *out_string;
	 if (newState == 0x100)
	 {
		 theString[0x100] = '\1';
		 return 0;
	 }
	 if (newState != 0x101)
	 {
		 if (newState != 0x102)
		 {
			 //CopyStringToPointerToString(out_string, "Invalid state.");
			 return 2;
		 }
		 theString[0x104] = '\1';
		 return 0;
	 }
	 theString[0x108] = '\1';
	 return 0;
}

int SetState_s(char** out_string, int newState)
{
	if ((out_string != NULL) && (*out_string != NULL))
		return SetState(out_string, newState);

	return 2;
}

// astruct_165
struct GameSpyObject {
	void* (**func_0x0)(void*);
	int int_0x4;
	// 12 undefined bytes at offset 0x8

	char char_0x14;
	// 12 undefined bytes at offset 0x18
	int int_0x24;
	int int_0x28;
	//4 undefined bytes at offset 0x2c

	char unkn_0x30;
	// 12 undefined bytes at offset 0x34
	int int_0x40;
	int int_0x44;
	// 4 undefined bytes at offset 0x48

	char unkn_0x4c;
	// 12 undefined bytes at offset 0x50
	int int_0x5c;
	int int_0x60;
	// 4 undefined bytes at offset 0x64

	char unkn_0x68;
	// 4 undefined bytes at offset 0x6c
	int int_0x70;
	char* string_0x74;
	// 4 undefined bytes at offset 0x78
	char unkn_0x7c;
	// 12 undefined bytes at offset 0x80
	int int_0x8c;
	int int_0x90;
	void* (***ptr_0x94)(void*);
	void* (***ptr_0x98)(void*);
	int* ptr_0x9c;
};

GameSpyObject* GameSpyRelated_008ec884;

void NewGameSpyObject()
{
	// This appears to be allocating an array of GameSpyObjects
	// It's not cleanly divisible though, from what I've been able to gather they're each 256 bytes, which would fit 30 but still have room left.
	// Unless it's an array of pointers, then it would be able to store 1,976 of them. I don't know what they would need that many for though.
	GameSpyRelated_008ec884 = (GameSpyObject*)malloc(0x1EE0);
	return;
}

void InitGameSpy(GameSpyObject* gs_ESI);

uint UINT_008e84e8;
uint DAT_008e84e4;

void CreateGameSpyPresenceForReal()
{
	if ((UINT_008e84e8 == 0) && (DAT_008e84e4 == 0))
	{
		if (GameSpyRelated_008ec884 != NULL)
		{
			// This function doesn't return a value, and yet it's supposed to here.
			//UINT_008e84e8 = InitGameSpy(GameSpyRelated_008ec884);
			// I'll just do this for now
			InitGameSpy(GameSpyRelated_008ec884);
			UINT_008e84e8 = 1;

			DAT_008e84e4++;
			return;
		}
		UINT_008e84e8 = 0;
	}
	DAT_008e84e4++;
	return;
}

void CreateGameSpyPresence()
{
	CreateGameSpyPresenceForReal();
	return;
}

void* (*PTR_FUN_00676f88)(void*);

void InitGameSpy(GameSpyObject* gs_ESI)
{
	char** ppcVar1;
	gs_ESI->func_0x0 = &PTR_FUN_00676f88;
	gs_ESI->int_0x4 = 0;

	// To me this looks like a group of a different struct
	gs_ESI->char_0x14 = '\0';
	gs_ESI->int_0x24 = 0;
	gs_ESI->int_0x28 = 0xF;

	gs_ESI->unkn_0x30 = '\0';
	gs_ESI->int_0x40 = 0;
	gs_ESI->int_0x44 = 0xF;

	gs_ESI->unkn_0x4c = '\0';
	gs_ESI->int_0x5c = 0;
	gs_ESI->int_0x60 = 0xF;

	gs_ESI->unkn_0x68 = '\0';
	gs_ESI->int_0x70 = 0;
	gs_ESI->string_0x74 = NULL;

	gs_ESI->unkn_0x7c = '\0';
	gs_ESI->int_0x8c = 0;
	gs_ESI->int_0x90 = 0xF;

	// Assumes that an array of at least 49 GameSpyObjects have been passed in
	gs_ESI->ptr_0x94 = &gs_ESI[1].func_0x0;
	gs_ESI->ptr_0x98 = &gs_ESI[1].func_0x0;
	gs_ESI->ptr_0x9c = &gs_ESI[49].int_0x40;

	ppcVar1 = &gs_ESI->string_0x74;
	SetState_s(ppcVar1, 0x102);
}



// My own addition because this may as well be a function, makes the next function much simpler.
bool GameInvite_StringCompare(char* subject, const char* compare, int lenOfCompare)
{
	bool theSame = true;
	do
	{
		if (!lenOfCompare) break;
		lenOfCompare--;
		theSame = *subject == *compare;
		subject++;
		compare++;
	} while (theSame);
	return theSame;
}

void HandleGameInvite(undefined4 self, char** param_2[])
{
	// Compares the response as text to determine what to do.
	char* response = *param_2[2];

	if (GameInvite_StringCompare(response, "CANCEL GAME INVITE", 0x13))
	{
		// I thought this was a cancel invite function but it's called elsewhere so I'm not quite sure yet.
		//CancelInvite2Maybe(*param_2, NULL);
		return;
	}

	// Wouldn't this mean that both Decline and Accept do the same thing?
	if (!GameInvite_StringCompare(response, "DECLINE GAME INVITE", 0x14))
		if (!GameInvite_StringCompare(response, "ACCEPT GAME INVITE", 0x13))
			return;

	//FUN_00511910(*param_2, 0);
	return;
}

struct ProfileStruct
{
	int int_0x0;
	int int_0x4;
	void* unkn_0x8;
	void** unkn_0x18;
	char buffer_0x28[256]; // Contains all the user data, it seems like it's all one buffer but it could be different properties.
	int int_0x130;
	int int_0x134;
	int int_0x138;

	int int_0x140;
	int int_0x144;
};

struct astruct_166
{
	// 4 undefined bytes at offset 0x0
	ProfileStruct* profile_0x4;
	int int_0x8;
	char* ptr_0xc;
	uint uint_0x10;
	int int_0x14;
	undefined4 unkn_0x18;
};

struct LobbyManager
{
	char* string_0x0;
	char* sesskey_0x198;
	char* profileid_0x1a0;
	uint errorCode_0x430;
	char* namespaceid_0x484;
};

// Copies 256 characters from the in_string to the out_string, setting the
// 256th to NULL, and the 1072nd to param_2
void __cdecl LobbyManager_Error(LobbyManager** pManager, uint errorCode, const char* in_string)
{
	LobbyManager* manager = *pManager;
	strncpy(manager->string_0x0, in_string, 0x100);
	manager->string_0x0[0xff] = NULL;
	manager->errorCode_0x430 = errorCode;
	return;
}


// Or at least I thought it was searching for lobbies, but why would it need things like email?
void SearchForLobbies(LobbyManager** pManager, astruct_166* param_2)
{
	ProfileStruct* profile = param_2->profile_0x4;
	LobbyManager* manager;
	UINT errorCode = ERRORCODE_SUCCESS_00683798;
	UINT errorCode2 = ERRORCODE_SUCCESS_00683798;
	// Some kind of struct, unsure of what it is yet
	if ((param_2->int_0x8 == 0) && ((GetTickCount() - profile->int_0x144) > 60000))
	{
		profile->int_0x140 = 1;
		LobbyManager_Error(pManager, 0xD02, "The search timed out");
		//FUN_005f52f0(pManager, 3, 0);
		ReportFailureUnless(errorCode);
		return;
	}

	void** ppvVar1 = profile->unkn_0x18;
	int iVar4;
	while (true)
	{
		//iVar4 = FUN_005f11d0(pManager, profile->int_0x4, ppvVar1, &local_460, 1, "SM");
		if (iVar4) goto LAB_005edeae;
		if (param_2->int_0x14 != 1) break;
		//iVar4 = FUN_005eb1c0(pManager, profile->int_0x4, &local_45c);
		if (iVar4) goto LAB_005edeae;
		if (local_45c == 4)
		{
			ComplicatedCopyString(pManager, 0xD01, "Could not connect to the search manager.");
			//FUN_005f52f0(manager, 4, 0);
			ReportFailureUnless(errorCode2);
			return;
		}
		if (local_45c == 3)
		{
			iVar4 = profile->int_0x0;
			if (iVar4 == 1)
			{
				LobbyStruct_AddString(pManager, ppvVar1, "\\search\\");
				LobbyStruct_AddString(pManager, ppvVar1, "\\sesskey\\");
				LobbyStruct_AddValue(pManager, ppvVar1, manager->sesskey_0x198);
				LobbyStruct_AddString(pManager, ppvVar1, "\\profileid\\");
				LobbyStruct_AddValue(pManager, ppvVar1, manager->profileid_0x1a0);
				LobbyStruct_AddString(pManager, ppvVar1, "\\namespaceid\\");
				LobbyStruct_AddString(pManager, ppvVar1, manager->namespaceid_0x484);
				if (profile->buffer_0x28[0] != NULL)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\nick\\");
					LobbyStruct_AddValue(pManager, ppvVar1, profile->buffer_0x28);
				}
				if (profile->buffer_0x28[0x1F] != NULL)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\uniquenick\\");
					LobbyStruct_AddValue(pManager, ppvVar1, &profile->buffer_0x28[0x1F]);
				}
				if (profile->buffer_0x28[0x34] != NULL)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\email\\");
					LobbyStruct_AddValue(pManager, ppvVar1, &profile->buffer_0x28[0x34]);
				}
				if (profile->buffer_0x28[0x67] != NULL)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\firstname\\");
					LobbyStruct_AddValue(pManager, ppvVar1, &profile->buffer_0x28[0x67]);
				}
				if (profile->buffer_0x28[0x86] != NULL)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\lastname\\");
					LobbyStruct_AddValue(pManager, ppvVar1, &profile->buffer_0x28[0x86]);
				}

				if (profile->int_0x130)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\icquin\\");
					LobbyStruct_AddValue(pManager, ppvVar1, profile->int_0x130);
				}

				if (profile->int_0x134)
				{
					LobbyStruct_AddString(pManager, ppvVar1, "\\skip\\");
					LobbyStruct_AddValue(pManager, ppvVar1, profile->int_0x134);
				}
			}
			else if (iVar4 == 2)
			{
				LobbyStruct_AddString(pManager, ppvVar1, "\\nicks\\");
				LobbyStruct_AddString(pManager, ppvVar1, "\\email\\");
				LobbyStruct_AddString(pManager, ppvVar1, &profile->buffer_0x28[0x34]);
				LobbyStruct_AddString(pManager, ppvVar1, "\\pass\\");
				char* pcVar5 = &profile->buffer_0x28[0xA5];
				LobbyStruct_AddString(pManager, ppvVar1, pcVar5);
				iVar4 = String_GetLength(pcVar5);
				//FUN_005e4900(0x79707367);
				int iVar14 = 0;
				char local_254[256];
				int iVar14, iVar6;
				if (iVar4 > 0)
				{
					do
					{
						iVar6 = FUN_005e4920(0, 0xFF);
						local_254[iVar14] = profile->buffer_0x28[iVar14 + 0xA5];
						iVar14++;
					} while (iVar14 < iVar4);
				}
			}
		}
	}
}


// Some kind of generic Windows success error code
uint ERRORCODE_SUCCESS_00683798 = 0xBB40E64E;

void __fastcall ReportFailureUnless(UINT errorCode)
{
	if (errorCode == ERRORCODE_SUCCESS_00683798)
		return;

	//_report_failure();
	__report_gsfailure();
}

// Puts an entire 0x400 length string on the stack in order to vsprintf to it.
void vsprintfOnStack(char out_string[0x400], undefined4 param_1, char* format, ...)
{

	va_list args;
	va_start(args, format);

	vsprintf(out_string, format, args);

	UINT errorCode = ERRORCODE_SUCCESS_00683798;
	ReportFailureUnless(errorCode);
}



struct astruct_150 {
	// 48 undefined bytes at offset 0x0
	int field_0x30;
	// 4 undefined bytes at offset 0x34
	uint field_0x38;
};

struct astruct_151 {
	// 16 undefined bytes at offset 0x0
	char field_0x10;
	// 53 undefined bytes at offset 0x14
	char field_0x45;
	// 2 undefined bytes at offset 0x46;
	uint field_0x48;
	undefined4* undefined2actually_0x4C;
	void* field_0x50;
	size_t field_0x54;
	// 4 undefined bytes at offset 0x58
	uint field_0x5C;
	uint field_0x60;
};




/////////////////////////////////////////////////
//
// PropertyDb
// 
/////////////////////////////////////////////////

struct PropertyDbItem
{
	const char* name_0x0;
	int flagsMaybe_0x4;
	void* var_0x8; // The address of the variable itself
};

int MinScreenSize_008dd460;
int Propability_008dd464;
int Lifetime_008dd468;
int AngleSpeed_0067cc54;
int Size_008dd474;
int Grow_008dd47c;
int MinTurbulence_0067cc3c;
int AddSpeedTurbulence_008dd488;
int AddLoadTurbulence_008dd48c;
int MinVelocity_008dd490;
int AddLoadVelocity_008dd494;
int Damping_008dd498;
int MinAlpha_008dd49c;
int AddLoadAlpha_008dd4a0;
int FadePeak_008dd4a4;

PropertyDbItem mappedTable_006679b0[] =
{
	{ "MinScreenSize", 0x407, &MinScreenSize_008dd460 },
	{ "Propability", 0x407, &Propability_008dd464 },
	{ "Lifetime", 0x809, &Lifetime_008dd468 },
	{ "AngleSpeed", 0x407, &AngleSpeed_0067cc54 },
	{ "Size", 0x809, &Size_008dd474 },
	{ "Grow",  0x809, &Grow_008dd47c },
	{ "MinTurbulence", 0x407,& MinTurbulence_0067cc3c },
	{ "AddSpeedTurbulence", 0x407, &AddSpeedTurbulence_008dd488 },
	{ "AddLoadTurbulence", 0x407, &AddLoadTurbulence_008dd48c },
	{ "MinVelocity", 0x407, &MinVelocity_008dd490 },
	{ "AddLoadVelocity", 0x407, &AddLoadVelocity_008dd494 },
	{ "Damping", 0x407, &Damping_008dd498 },
	{ "MinAlpha", 0x407, &MinAlpha_008dd49c },
	{ "AddLoadAlpha", 0x407, &AddLoadAlpha_008dd4a0 },
	{ "FadePeak", 0x407, &FadePeak_008dd4a4 }
};

// PropertyDb
// The way it's used reminds me of XML or JSON, it appears to be just an element, but it has functions to access more elements inside.
class AutoClass9 {
public:
	INT INT_0x0;
	short index_0x4;
	short short_0x6;
	// 2 undefined bytes at offset 0x8, probably a short
	short short_0xa;

	AutoClass9* FUN_00557fe0(char* in_string, char param_2)
	{
		char charStack[256];
		char* tempString = in_string;
		char currentChar;
		// Counts the length of the string
		do {
			currentChar = *tempString;
			tempString++;
		} while (currentChar != NULL);

		if (tempString == in_string + 1)
			return this;

		currentChar = *in_string;
		int iVar4 = 0;
		int iVar5 = 0;
		if (currentChar != NULL)
		{
			tempString = in_string;
			do {
				if (currentChar == '.') break;
				iVar5++;
				tempString[(int)(charStack + -(int)in_string)] = currentChar;
				currentChar = tempString[1];
				iVar4++;
				tempString++;
			} while (currentChar != NULL);
		}
		currentChar = in_string[iVar4];
		charStack[iVar5] = NULL;
		if (currentChar == '.')
			iVar4++;

		/*
		//AutoClass9* this_00 = FUN_00557e60(this);
		if (this_00 == NULL)
		{
			this_00 = PropertyDb_AccessProperty();
			if (this_00 == NULL)
			{
				if (param_2 == NULL)
					return NULL;
				//this_00 = PropertyDb_RuntimeTables();
			}
		}
		AutoClass9 *pAVar3 = this_00->FUN_00557fe0(in_string + iVar4, param_2);
		return pAVar3;
		*/
		return this;
	}

	void AddMappedTable(char* param_1, uint* param_2, uint param_3)
	{
		AutoClass9* pAVar3 = this->FUN_00557fe0(param_1, '\0');
		int iVar12 = 0;
		int iVar8 = *param_2;
		uint* piVar4 = param_2;
		uint* piVar1;

		while (iVar8 != 0)
		{
			piVar1 = piVar4 + 3;
			piVar4 = piVar4 + 3;
			iVar12 += 1;
			iVar8 = *piVar1;
		}

		if ( (pAVar3 == NULL || (pAVar3->short_0xa == 0)) && (((param_3 & 6) != 0 || (param_3 & 0x400) != 0)) )
		{
			if (pAVar3 == NULL)
				pAVar3 = this->FUN_00557fe0(param_1, '\1');

			param_3 = 0;
			if (iVar12 > 0)
			{
				uint* puVar5 = param_2 + 1;
				iVar8 = iVar12;
				do
				{
					param_3 += 0xC + (*puVar5 >> 8 & 0xFFFF);
					puVar5 += 3;
					iVar8--;
				} while (iVar8 != 0);
			}
			pAVar3->short_0xa = (short)iVar12;
			//paVar6 = FUN_00557540((int*)&ppuStack_4);
			//...
		}
	}

};

// Property Db

char** PropertyDb_ActuallyFindTheProperty(char* param_1, void* in_EAX)
{
	short sVar1 = *(short*)((uint)in_EAX + 10);
	char** ppcVar3 = *(char***)((uint)in_EAX + 0x10);
	int iVar4 = 0;
	if (sVar1 > 0)
	{
		int iVar2;
		do
		{
			iVar2 = _stricmp(param_1, *ppcVar3);
			if (iVar2 == 0)
				return ppcVar3;

			iVar4++;
			ppcVar3 = ppcVar3 + (((uint)ppcVar3[1] >> 8 & 0xFFFF) + 0xC);
		} while (iVar4 < sVar1);
	}
	return NULL;

}


// I can't even remember how many different versions of this function there are, I think it's a Get function that is slightly different depending on either the struct being accessed, or the type of variable being accessed.
int PropertyDb_AccessProperty(char* in_EAX)
{
	char* leftBracket = strstr(in_EAX, "[");
	char* rightBracket = strstr(in_EAX, "]");
	char* tempPtr = in_EAX;
	char* local_100;
	char* local_110;
	long lVar4;

	// Counts the length of the string
	do
		tempPtr = tempPtr + 1;
	while (*tempPtr != NULL);

	int iVar6;
	char currentChar;
	if (leftBracket == NULL || rightBracket == NULL || rightBracket <= leftBracket || (rightBracket + -(int)in_EAX != tempPtr + (-1 - (int)(in_EAX + 1))))
	{
		iVar6 = -(int)in_EAX;
		do
		{
			// Copies the string in a strange way, right now I don't know what it means.
			currentChar = *in_EAX;
			in_EAX[local_100[iVar6]] = currentChar;
			in_EAX += 1;
		} while (currentChar != NULL);
		lVar4 = 0;
	}
	else
	{
		tempPtr = leftBracket + 1;
		iVar6 = -(int)tempPtr;
		do
		{
			currentChar = *tempPtr;
			tempPtr[local_110[iVar6]] = currentChar;
			tempPtr += 1;
		} while (currentChar != NULL);
		
		uint* puVar2 = (uint*)local_110;
		uint* puVar3;
		do
		{
			puVar3 = puVar2;
			puVar2 = puVar3 + 1;
		} while (*puVar3 != NULL);

		puVar3[-1] = NULL;
		lVar4 = atol(local_110);
		strncpy(local_100, in_EAX, (size_t)(leftBracket - in_EAX));
		local_100[(int)leftBracket - (int)in_EAX] = NULL;
	}
	char** ppcVar5 = PropertyDb_ActuallyFindTheProperty(local_100, in_EAX);
	if ((ppcVar5 != NULL) && (ppcVar5[1] != (char*)0xF))
	{
		if (((uint)ppcVar5[1] >> 8 & 0xFFFF) < lVar4 * 2 + 2U)
			CreateErrorMessageAndDie("PropertyDb: out-of-bounds access of property \'%s\'");

		char** ppcVar7 = (char**)ppcVar5[2];
		if (ppcVar7 == NULL)
			ppcVar7 = ppcVar5 + 3;

		iVar6 = (int)ppcVar7 + (lVar4 * 2);
		if (iVar6 != 0)
			return UINT_008da728 + iVar6 * 0x14;
	}
	return 0;
}

// It's effectively (floatA >= floatB)
#define SafeGreaterThan(floatA, floatB) (floatA < floatB) == (isnan(floatA) || isnan(floatB))

void FUN_005c9fa0(int param_1, float unaff_ESI[])
{
	if (param_1 > 0)
	{
		bool invert;
		float10 fVar2;
		// The original code uses a do while but it's structured exactly like a for so why not.
		for (uint i = 0; i < param_1; i++)
		{
			invert = false;
			fVar2 = (i * 4.0) / param_1;

			// This must have been a macro because I don't know why they'd check if a constant is nan.
			if (SafeGreaterThan(fVar2, 1.0))
			{
				if (SafeGreaterThan(fVar2, 2.0))
				{
					if (SafeGreaterThan(fVar2, 3.0))
						fVar2 = 4.0 - fVar2;
					else
					{
						fVar2 -= 2.0;
						invert = true;
					}
				}
				else
				{
					fVar2 = 2.0 - fVar2;
					invert = true;
				}
			}

			fVar2 = cos(fVar2 * 1.9979);
			fVar2 = (0.5 - fVar2 * 0.5) * (0.5 - 0.5 * fVar2);
			unaff_ESI[i] = fVar2;

			if (invert)
				unaff_ESI[i] = 1.f - fVar2;

			unaff_ESI[i] = sqrtf(unaff_ESI[i]);
		}
	}
	return;
}



/////////////////////////////////////////////////
//
// File System
// 
/////////////////////////////////////////////////

struct astruct_142
{
	// 4 undefined bytes at offset 0x0
	ArrayMaybe* filenameList_0x4;
	// 12 undefined bytes at offset 0x8
	int* unkn_0x14;
	// 8 undefined bytes at offset 0x18
	int* unkn_0x20;
	int filenameIndex_0x24;

	size_t size_0x3c;
};

struct bbFileStruct
{
	char* filename_0x0;
	// 4 undefined bytes at offset 0x4
	uint unkn_0x8;
	uint unkn_0xc;
	// 4 undefined bytes at offset 0x10
	FILE* file_0x14;
	uint flags_0x18;
	// Way too many undefined bytes at offset 0x1c
	uint unkn_0x78;
};

BYTE buffer_006a0af8[8192];

int bbOpenFile(char** param_1, astruct_142* param_2)
{
	char* pcVar1 = *param_1;
	bbFileStruct* bbFile = (bbFileStruct*)GetItem(param_2->filenameList_0x4, param_2->filenameIndex_0x24);

	if (!(bbFile->flags_0x18 & 4))
	{
		if (!(bbFile->flags_0x18 & 2))
		{
			if (bbFile->file_0x14 == NULL)
			{
				undefined4* newStruct;
				FILE* file = fopen(bbFile->filename_0x0, "rb");
				bbFile->file_0x14 = file;
				if (file == NULL)
				{
					newStruct = (undefined4*)malloc(0x14);
					if (newStruct != NULL)
					{
						newStruct[0] = NULL;
						newStruct[1] = NULL;
						newStruct[2] = NULL;
						newStruct[3] = NULL;
						newStruct[4] = NULL;

						newStruct[0] = (uint)param_2->unkn_0x14;
						newStruct[1] = 0x80F;
						newStruct[2] = param_2->filenameIndex_0x24;
						newStruct[3] = 0x900;
						//FUN_005f4fd0(param_1, pcVar1 + 0x1D4, pcVar1 + 0x1D8, newStruct, 0, 7);
					}
				bbOpenFileExit:
					//FUN_005f3650(param_1, param_2, 0);
					bbFile->flags_0x18 |= 8;
					bbFile->unkn_0x78 = 0x900;
					return 0;
				}
				//int fileInfo = GetInfoOnFile(bbFile, );
				//if (fileInfo) return fileInfo;

				//FUN_005f6150(ppcVar2 + 8);
				newStruct = (undefined4*)malloc(0x14);
				if (newStruct != NULL)
				{
					*newStruct = NULL;
					newStruct[1] = NULL;
					newStruct[2] = NULL;
					newStruct[3] = NULL;
					newStruct[4] = NULL;

					*newStruct = (uint)param_2->unkn_0x14;
					newStruct[1] = 0x80F;
					newStruct[2] = param_2->filenameIndex_0x24;
					newStruct[3] = 0x900;
					//FUN_005f4fd0(param_1, pcVar1 + 0x1D4, pcVar1 + 0x1D8, newStruct, 0, 7);
				}
			}
			if (bbFile->unkn_0x8 < bbFile->unkn_0xc)
			{
				do
				{
					if (*(param_2->unkn_0x20 + 0x30)) break;
					size_t sVar6 = fread(buffer_006a0af8, 1, 0x2000, bbFile->file_0x14);
					if (sVar6)
					{
						//FUN_005f6a90(ppcVar8 + 8, buffer_006a0af8, sVar6);
						int iVar5 = 0;//FUN_005f45d0(buffer_006a0af8, sVar6);
						if (iVar5) return iVar5;

						param_2->size_0x3c += sVar6;
					}
				} while (bbFile->unkn_0x8 < bbFile->unkn_0xc);
			}
			//...
		}
	}
}


/*
void __fastcall GetInfoOnFile(int unaff_EBX, int unaff_ESI)
{
	uint errorCode = ERRORCODE_SUCCESS_00683798;
	uint uVar1 = fstat((*(int*)(unaff_EBX + 0x14) + 0x10), &local_68);

}
*/

void (**PTR_JMPTABLE_008da700)()  = NULL;

/*
void LoadBinaryDatabase(char *flags)
{
	int* piVar1;
	int* piVar5;
	int iVar3;
	char cVar2;
	uchar local_28;
	int iStack_34;
	int iStack_30;
	uint local_8;
	undefined4* paVar4;
	void* puVar4;

	PTR_JMPTABLE_008da700 = NULL;
	free(MemoryPointer);
	MemoryPointer = NULL;
	memAllocationSize = 0;
	cVar2 = FUN_0054c610('\0', (uchar *)flags);
	if (cVar2 != '\0')
	{
		FUN_0054c3b0(flags, 9);
		iVar3 = **(*(int*)local_8 + 0x1c)();
		FUN_0054c5a0((int)&local_28, &iStack_34, 0xc);
		if ((iStack_34 == 0x1a424450) && (iStack_30 == 0x200))
		{
			memAllocationSize = iVar3 + 0x13f4;
			MemoryPointer = malloc(memAllocationSize);
			piVar1 = (int*)((int)MemoryPointer + 0x1400);
			FUN_0054c5a0((int)&local_28, piVar1, iVar3 + -0xc);
			UINT_008d7c30 = MemoryPointer;
			puVar4 = MemoryPointer;
			for (iVar3 = 0x500; iVar3 != 0; iVar3 += -1)
			{
				*puVar4 = 0;
				puVar4 = puVar4 + 1;
			}
			if (piVar1 == NULL)
				piVar5 = NULL;
			else
			{
				*piVar1 = (int)&PTR_LAB_0067b1c0;
				piVar5 = piVar1;
			}
			UINT_008da700 = (uint)piVar5;
			UINT_008da728 = (uint)piVar5;
			FUN_00559580(piVar1);
			FUN_0054c410();
			return;
		}
		FUN_0054c540();
		if (0xF < uStack_10)
		{
			paVar4 = FUN_0054c710();
			FUN_00557650(paStack_24, paVar4);
		}
	}
	CreateErrorMessageAndDie("Failed to load binary database \'%s\'!");
	return;
}
*/

void InitOpenBFS(LPCSTR lpFilename, register YetAnotherFileObject* in_EAX)
{
	void* pvVar2 = malloc(0x224);
	void* uVar3;
	if (pvVar2 == NULL)
		uVar3 = NULL;
	else
		OpenBFS(lpFilename, in_EAX);

	//if (in_EAX[2] == in_EAX[1])
		//FUN_00434840();

	in_EAX->size_0x4 += 4;

	return;
}

bool WriteCharToStream(char in_char, FILE* file)
{
	return fputc(in_char, file) != -1;
}

// I'm not very familiar with FPUs, so I don't know what's going on.
UINT SetFPUCW(USHORT in_FPUControlWord)
{
	uint copyOfWhat;

	copyOfWhat = unkn_008da6a0 >> 16;
	if (unkn_008da6a0 == 0) {
		unkn_008da6a0 = 1;
		FPUConW_008d781c = in_FPUControlWord;
	}
	return copyOfWhat << 2 | in_FPUControlWord;
}

/////////////////////////////////////////////////
//
// Threads
// 
/////////////////////////////////////////////////

HANDLE CreateThreadAndSetPriority(const char* name, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, int priorityKinda)
{
	DWORD local_8;
	HANDLE hThread = CreateThread(NULL, 0, lpStartAddress, lpParameter, 0, &local_8);

	// Ghidra suggests the original was an else-if chain but I thought this looked cleaner
	int nPriority;
	switch (priorityKinda)
	{
	case -1:
	case 2:
		nPriority = priorityKinda;
		break;

	case 0:
		nPriority = 1;
		break;

	case 3:
		nPriority = 0xF;
		break;

	default:
		return hThread;
	}

	SetThreadPriority(hThread, nPriority);
	return hThread;
}

struct bbThread
{
	// 4 undefined bytes at offset 0x0
	DWORD threadId_0x4;
	HANDLE handle_0x8;
	HANDLE hEvent_0xc;
};

ULONG __stdcall ThreadUpdate(LPVOID thread)
{
	//FUN_004e3780();
	// (UINT_008dcad8 + 0x10)();
	DWORD DVar1 = WaitForSingleObject(((bbThread*)(thread))->hEvent_0xc, 20);
	while (DVar1 != WAIT_OBJECT_0)
	{
		//FUN_004e3780();
		//(UINT_008dcad8 + 0x10)();
		//FUN_004e2290(thread);
		DVar1 = WaitForSingleObject(((bbThread*)(thread))->hEvent_0xc, 20);
	}
	return 0;
}

bbThread* UINT_008da62c;

int CreateUpdateThread()
{
	bbThread* thread = UINT_008da62c;
	HANDLE* pHandle = &thread->handle_0x8;

	if (thread->handle_0x8 == NULL)
	{
		HANDLE handle = CreateEventA(NULL, FALSE, FALSE, NULL);
		thread->hEvent_0xc = handle;
		handle = CreateThread(NULL, 0, ThreadUpdate, thread, 0, &thread->threadId_0x4);
		SetThreadPriority(handle, 0xF);
	}
	
	return 0;
}


/////////////////////////////////////////////////
//
// Misc.
// 
/////////////////////////////////////////////////

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

// Function that doesn't do anything but apparently was for debug logging.
int DEBUGLOG(lua_State* L)
{
	return 0;
}

void MoveToEAX(void* param_1)
{
	_asm
	{
		MOV EAX, param_1
	}
}

void sprintf_strange(undefined4 param_1, char* format, ...)
{
	va_list list;
	va_start(list, format);

	// This function reaches backwards into the stack to get the string to copy to.
	char* local_404 = (char*)((&param_1) - 0x400);

	UINT errorCode = ERRORCODE_SUCCESS_00683798;
	vsprintf(local_404, format, list);
	ReportFailureUnless(errorCode); // Does this do anything?
}

// Here's the thing: nearly every time this function is called,
// It's given the DoNothing() function.
// Is it some kind of delay?
void RepeatFunction(void (*func)(), register int nTimes_EAX)
{
	if (nTimes_EAX + -1 > -1)
	{
		do {
			func();
			nTimes_EAX += -1;
		} while (nTimes_EAX != 0);
	}
	return;
}

void memsetWithOffset(void** Dst, uint Offset, int Val, size_t Size)
{
	memset((void*)((uint)(*Dst) + Offset), Val, Size);
	return;
}


undefined4 Depointerize(undefined4* output)
{
	return *output;
}


/////////////////////////////////////////////////
//
// Pure Assembly
// 
/////////////////////////////////////////////////
// 
// Functions where the p-code view doesn't really tell you anything, so I imagine it was written in assembly.
// I've never written assembly functions in C, do I just put it under my own labels like so, or do I wrap it in a C function? I guess it's easy to fix if I didn't do it right.
//
/*
__asm
{
	SetALRegisterTo1:
		mov al, 0x1
		ret

	SetALRegisterTo1Again:
		mov al, 0x1
		ret

	SetEAXTo1:
		mov eax, 0x1
		ret

	SetEAXTo6:
		mov eax, 0x6
		ret
}
*/







