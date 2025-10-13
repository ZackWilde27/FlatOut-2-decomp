#pragma once

#include <stdint.h>
#include "MrWonkoFileObject.h"
#include "Lua.h"

//////////////////////////////
// Enums
//////////////////////////////

// Ported from SDK, I changed them to use the original names used in Lua

enum GameMode
{
	GM_NONE,
	GM_CAREER,
	GM_TIMEATTACK,
	GM_SINGLE_RACE,
	GM_INSTANT_ACTION,
	GM_CRASHTEST_DUMMY,
	GM_ONLINE_MULTIPLAYER,
	GM_PARTYMODE,
	GM_DEVELOPER,
	GM_TOURNAMENT,
	GM_SPLITSCREEN,
	GM_TEST
};

enum GameRules
{
	GR_DEFAULT,
	GR_RACE,
	GR_STUNT,
	GR_DERBY,
	GR_HUNTER_PREY,
	GR_ARCADE_ADVENTURE,
	GR_PONGRACE,
	GR_TIMEATTACK,
	GR_TEST
};

// I didn't find the real names for these so I just assumed they'd put SESSION as the prefix
enum SessionType
{
	SESSION_NONE,
	SESSION_MENU,
	SESSION_RACE
};

enum StuntType
{
	STUNT_NONE,
	STUNT_CURLING,
	STUNT_BULLSEYE, // Unused
	STUNT_HIGHJUMP,
	STUNT_STONESKIPPING,
	STUNT_RINGOFFIRE,
	STUNT_DARTS,
	STUNT_BREAKDOWN, // Unused
	STUNT_BLACKDANNY, // Royal Flush
	STUNT_SKIJUMP,
	STUNT_FIELDGOAL,
	STUNT_BOWLING,
	STUNT_BASKETBALL,
	STUNT_BASEBALL,
	STUNT_SOCCER
};

// As far as I know, OBSERVER and SIMULATED are unused
enum PlayerType
{
	PLAYER_UNKNOWN,
	PLAYER_LOCAL,
	PLAYER_REMOTE,
	PLAYER_OBSERVER,
	PLAYER_AI,
	PLAYER_SIMULATED
};

enum DerbyType
{
	DERBY_NONE,
	DERBY_LMS, // Last Man Standing: Same as Wrecking except when you win you are labelled as 'Survived' on the results page
	DERBY_WRECKING, // The mode is always plays normally
	DERBY_FRAG, // Same as Wrecking except there's a bug where the match doesn't end when you wreck
	DERBY_END // Crashes the game if you play it
};



//////////////////////////////
// Structs
//////////////////////////////

// Thanks to Sewer56 on GitHub for figuring out these structs.

struct sRGBA
{
	unsigned char b, g, r, a;
};

struct Vector3_pad
{
	float x, y, z, pad;
};

struct Vector4Int
{
	int x, y, z, w, a;
};

struct Quaternion
{
	float y, z, x, w;
};

struct Matrix33
{
	Vector3_pad right, up, at;
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
	struct Player* m_pPlayer;
	// 9312 undefined bytes at offset 0x4640
	float m_fDamage_0x6aa0;
	// 36 undefined bytes at offset 0x6aa4
	bool m_bGodMode;
	//
};

struct Player
{
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
	BOOL m_bGodMode_0x348;
	uint32_t m_bDriverFemale_0x34c;
	uint32_t m_nDriverSkin_0x350;
	// 20 undefined bytes at offset 0x354
	uint32_t m_nPlayerId_0x368;
	PlayerType m_nPlayerType_0x36c;
	// 16 undefined bytes at offset 0x370
	uint32_t m_bDisableControlAndReset_0x380;
	// 4 undefined bytes at offset 0x384
	uint32_t m_nUnknown_0x388;
	// 164 undefined bytes at offset 0x388
	Vector3_pad m_vPosition_0x428;
	// 116 undefined bytes at offset 0x42c
	float m_fReadOnlyDamage_0x49c;
	// 484 undefined bytes at offset 0x4a0
	uint32_t m_nUnknown_0x4e8;
	float m_fSteerAngle_0x684;
	float m_fGasPedal_0x688;
	float m_fBrakePedal_0x68c;
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

typedef Player* sPlayerArray[8];

class BfsManager
{
public:
	//pad_0x0[16];
	MWFileObject* openedFiles_0x10[3];
	//pad_0x1c[72];
	undefined1 byte_0x64;
	HANDLE fileHandle_0x68;
	LPOVERLAPPED lpOverlapped_0x6c;
};

struct PlayerHost
{
	void (**vftable_0x0)();
	//BYTE pad_0x4[16];
	sPlayerArray* m_pPlayerArray_0x14;
	//BYTE pad_0x18[2416];
	uint32_t m_nNumCars_0x988;
	//BYTE pad_0x98c[130784];
	uint32_t m_nLevelID_0x2086c;
};

struct CarDatabaseItem
{
	BOOL bLocked_0x0;
	BOOL bOwned_0x4;
	uint nSkinIndex_0x8;
	//BYTE pad_0xc[16];
	int nMoneySpentUpgrades_0x1c;
};

struct Garage
{
	//BYTE pad_0x0[4];
	uint m_nNumCars_0x4;
	uint m_nNumFunnyCars_0x8;
	BYTE* pCarClasses_0xc;
	//BYTE pad_0x10[8];
	BYTE* pAIClasses_0x18;
	//BYTE pad_0x1c[56];
	CarDatabaseItem* pDatabase_0x54;
	//BYTE pad_0x58[8];
	float fCareerOdometer_0x60;
	uint32_t nCarsOwned_0x64;
	uint32_t nCarsUnlocked_0x68;
};

struct GUI_SimpleButton
{
	void (**vftable_0x0)();
	GUI_SimpleButton* pNext_0x60;
	uint32_t nFlags_0xf8;
	int nIDMaybe_0x164;
};

struct ButtonStruct
{
	void (**vftable_0x0)();
	//BYTE pad_0x4[4];
	GUI_SimpleButton* pActualButton_0x8;
	//BYTE pad_0xc[8];
};

struct ButtonBar
{
	uint32_t nNumSlots_0x164;
	BOOL bEnableMovement_0x174;
	ButtonStruct** pButtons_0x18c;
	ButtonStruct** pNextButton_0x190;
	uint32_t nSelectedButton_0x19c;
};

struct PlayerProfile
{
	void (**vftable_0x0)();
	bool m_bFemale_0xe31;
	Garage m_sGarage_0x3c4;
	BYTE m_bHelmet_0xe32;
	BYTE m_bSuit_0xe33;
	wchar_t m_sProfileName_0xe34[8];
	BYTE m_bDifficulty_0xe54;
	//BYTE pad_0xe55[3];
	int m_nMoney_0xe58;
	BYTE m_bActiveEvent_0xe60;
	BOOL m_bAutosaveEnabled_0xedc;
	BOOL m_bCareerWelcome1Displayed_0xee4;
	BOOL m_bCareerWelcome2Displayed_0xee8;
	BOOL m_bCareerWelcome3Displayed_0xeec;
	int m_nNumCupRestarts_0xf14;
	int m_nNumTimesRagdolled_0xf18;
	float m_fTotalRagdollFlyDistance_0xf1c;
};

// a.k.a RaceInfo
struct GameSettings
{
	//BYTE pad_0x0[32];
	uint uint_0x20;
	undefined4 unkn_0x24;
	//BYTE pad_0x28[4];
	int m_nSaveFlowResult_0x2c;
	//BYTE pad_0x30[20];
	BOOL bSaveGameInfoValid_0x44;
	//BYTE pad_0x48[1008];
	int m_nSaveFlowState_0x434;
	undefined4 unkn_0x438;
	undefined4 unkn_0x43c;
	//BYTE pad_0x440[12];
	int m_nSaveStatus_0x44c;
	//BYTE pad_0x450[48];
	SessionType m_nSessionType_0x458;
	GameMode m_nGameMode_0x464;
	GameRules m_nGameRulesOverride_0x468;
	DerbyType m_nDerbyTypeOverride_0x46c;
	uint32_t m_nLevelID_0x480;
	int m_nWeather_0x484;
	uint32_t m_nNumLaps_0x488;
	//BYTE pad_0x48c[296];
	GameRules m_nGameRules_0x4ac;
	StuntType m_nStuntType_0x4b0;
	DerbyType m_nDerbyType_0x4b4;
	char* m_pPositions_0x4b8;
	BOOL m_bNitroRegen_0x4bc;
	wchar_t* m_aPlayerNames_0x5b0;
	// BYTE pad_0x5b4[1028]
	PlayerHost* m_pHost_0x9b8;
	//BYTE pad_0x9bc[80];
	void* m_pMenuInterface_0x9c8;
	BOOL m_bStarted_0xa0c;
	//BYTE pad_0xa10[1488];
	PlayerProfile m_pPlayerProfile_0xfe0;
};

struct CupRace
{
	int unkn_0x34;
	int m_nNextRaceIndex_0x38;
	int m_nPosition_0x40;

	BOOL m_bLocked_0x68;
	BOOL m_bCompleted_0x6c;
};

struct CupPoints
{
	int m_nIndexOrId_0x0;
	int m_nPoints_0x4;
};

class CupManager
{
public:
	void* vftable_0x0;
	int unkn_0x4;
	CupRace m_aCupRaces_0x8[6];
	//BYTE undefined_0x30[1304];
	CupPoints m_aCupPoints_0x548[8];
	uint32_t m_nActiveIndex_0x588;
	//BYTE undefined_0x58c[24];
	int m_nNumDrivers_0x5ac;
	uint32_t m_nCupRaceLength_0x5a8;
	//BYTE undefined_0x5ac[2220];

	int GetNextRaceIndex(int always1)
	{
		int index = m_nActiveIndex_0x588;

		if (index > 0 && index < m_nCupRaceLength_0x5a8)
			// Just like CupManager_GetRacePosition, the math here is really weird
			// To the point where Ghidra doesn't know what this code does
			// It's (index * (sizeof(CupRace) / sizeof(int)) + always1) * sizeof(int) - 0x3c)
			return m_aCupRaces_0x8[index - 1].m_nNextRaceIndex_0x38;

		return FALSE;
	}
};

struct BCORE_Camera
{
	void (**vftable_0x0)();
};

// TIME

struct TimeInfo
{
	void (**vftable_0x0)();
	// 4 undefined bytes at offset 0x4
	LARGE_INTEGER counter_0x8;
	undefined4 unkn_0x10;
	undefined4 unkn_0x14;
	undefined4 unkn_0x18;
	undefined4 unkn_0x1c;
	undefined4 unkn_0x20;
};

struct LoadingBar
{
	//BYTE pad_0x0[12];
	int index_0xc;
	// My current theory for these is that they control the length and offset of the loading bar, since the equation is (progress * scales[i] + offsets[i])
	float offsets_0x10[64];
	float scales_0x110[64];
	float progress_0x210;
	//BYTE pad_0x214[172];
	void (**vftable_0x2c0)();
	//BYTE pad_0x2c4[48];
	int int_0x2f4;
};

struct MenuMap
{
	//BYTE pad_0x0[4];
	BOOL m_bEnabled_0x4;
};

// Is there such thing as a declaration for typedefs?
typedef const char *D3DXHANDLE;

struct Shader
{
	void(**vftable_0x0)();
	undefined4 unkn_0x4;
	int int_0x8;
	//BYTE pad_0xc[12];
	void* unkn_0x18;
	void* unkn_0x1c;
	uint flags_0x50;
	struct ID3DXEffect* pEffect_0x54;
	//BYTE pad_0x58[16];
	D3DXHANDLE hTex0_0x68, hTex1_0x6c, hTex2_0x70, hTex3_0x74, mCub_0x78, dFac_0x7c, vDiff_0x80;
	//BYTE pad_0x84[4];
	uint strideMaybe_0x88;
};

// Size: 0x48
struct PlayersListData
{
	//BYTE pad_0x0[32];
	char nameMaybe_0x20[8];
	//BYTE pad_0x24[9];
	bool bMuted_0x2d;
	//BYTE pad_0x2e[26];
};

class PlayersList
{
public:
	void (**vftable_0x0)();
	Player** m_aCurrentPlayers_0x4;
	Player* m_pLastCurrentPlayer_0x8; // Points at the last player in aCurrentPlayers
	//BYTE pad_0xC[4]
	Player** m_aRecentPlayers_0x10;
	Player* m_pLastRecentPlayer_0x14; // Same thing, but for the recent players
	//BYTE pad_0x18[4];
	PlayersListData* m_pPlayerData_0x1c;
	PlayersListData* m_pNextPlayerData_0x20;
	BOOL m_bListShowing_0x93d;

	void SetPlayerMutedForReal(bool bMuted, register char* unaff_EBX)
	{
		PlayersListData* ptr = m_pPlayerData_0x1c;

		if (ptr == m_pNextPlayerData_0x20)
			return;

		do
		{
			int i = 2;
			bool theSame = true;
			char* piVar3 = ptr->nameMaybe_0x20;
			char* piVar4 = unaff_EBX;
			do
			{
				if (!i--) break;
				theSame = *piVar3 == *piVar4;
				piVar3 += 4;
				piVar4 += 4;
			} while (theSame);

			if (theSame)
			{
				if (ptr)
					ptr->bMuted_0x2d = bMuted;

				return;
			}

			ptr += sizeof(PlayersListData);
			if (ptr == m_pNextPlayerData_0x20)
				return;
		} while (true);
	}
};

struct TextChat
{
	int nNumLines_0x0;
	// BYTE pad_0x4[5824];
	bool bTextUpdated_0x16c4;
};

struct Vector4
{
	float x, y, z, w;
};

typedef float Matrix44[4][4];


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

struct Font
{

};

struct FontEntry
{
	char* name_0x0;
	char* path_to_atlas_0x4;
	Font* font_0x8;
	BOOL unkn_0xc;
};

struct FontNames
{
	FontEntry entries_0x0[20];
	int numEntries_0x140;
};