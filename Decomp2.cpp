// FlatOut 2 Decompilation

// So here's what I've learned so far:
//
// Almost every boolean is an integer. It turns out that deep down, bools are somehow slower than integers, I guess back in it's day, that fraction of performance mattered.
// I may have changed a few of these ints back to bools in Ghidra, thinking they should be bools, and also some 3rd party functions require them.
//

// I don't think these are included but hey
#include <stdio.h>
#include <stdarg.h>

// All libraries that FlatOut 2 imports. (Except for Havok Physics, it's not available.)
#include <memoryapi.h>
#include <WinUser.h>

// D3D9.DLL
#include <d3d9.h>

// D3DX9_30.DLL
// Requires you to run this command in Visual Studio's NuGet console:
// NuGet\Install-Package Microsoft.DXSDK.D3DX -Version 9.29.952.8

#include "D3DX9Effect.h"
#include "D3dx9tex.h"


// GDI32.DLL
#include <wingdi.h>

#include <strsafe.h>

// IPHLPAPI.DLL
#include <iphlpapi.h>

#include <winreg.h>

// WINMM.DLL
#include <timeapi.h>

#include <combaseapi.h>
#include <shellapi.h>

// Structs

struct undefined4 {
    float nothing;
};


// Settings Structures
// Got this info from the cfg files

struct Version {
    int Settings = 15; // 0 - 1,000,000
};

struct Game {
    bool ImperialUnits = false;
    bool OverlayGauges = true;
    bool IngameMap = true;
    bool Ragdoll = true;
    bool ShowBonus = true;
    bool ShowTutorials = true;
    char DefaultPlayerName[7] = "PLAYER";
    int Camera = 0; // 0 - 9
    int Hud = 0;    // 0 - 4
};

struct Control {
    char ControllerGuid[33] = "00000000000000000000000000000000";
    int Controller = 0;                     // 0 - 2
    int ForceMagnitude = 100;               // 0 - 100
    int ControllerSensitivity = 90;         // 0 - 100
    int ControllerDeadzone = 0;             // 0 - 100
    int ControllerSaturation = 90;          // 0 - 100
    int ControllerLayout = 0;               // 0 - 10
    bool ForceFeedback = true;
    float DigitalCenteringSpeed = 0.999f;   // 0.0 - 100.0
    float DigitalSteeringMaxSpeed = 1.85f;  // 0.0 - 100.0
    float DigitalSteeringMinSpeed = 1.25f;  // 0.0 - 100.0
};

struct Visual {
    bool AlphaBlend = true;
    bool SunFlare = true;
    int TextureQuality = 4;       // 0 - 4
    int TrackDetail = 2;          // 0 - 2
    int PS2MotionBlurIngame = 32; // 0 - 255
    int Visibility = 100;         // 0 - 100
};

struct Audio {
    int InterfaceMusicVolume = 50;  // 0 - 100
    int InterfaceSfxVolume = 80;    // 0 - 100
    int IngameMusicVolume = 50;     // 0 - 100
    int IngameSfxVolume = 80;      // 0 - 100
    int ChannelMode = 0;            // 0 - 2
    bool DopplerEffects = false;
};

struct Network {
    int Port = 23756;                     // 0 - 65536
    int BroadcastPort = 23757;            // 0 - 65536
    int VoiceOutputVolume = 80;           // 0 - 100
    int VoiceJitterMaxDelay = 10;         // 0 - 100
    int VoiceJitterMaxVariation = 10;     // 0 - 100
    int VoiceJitterInitialVariation = 2;  // 0 - 100
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


HINSTANCE g_Instance;

DLGPROC g_dlgproc;

int setupFlag = 0;


/////////////////////////////////////////////////
// Checking Direct X Version

int CheckDirectXVersion(LPBYTE* expectedVersion)
{
    HKEY hkey;
    LPBYTE lpdata;
    LPDWORD lpcbdata;

    LSTATUS oStatus = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\DirectX", 0, 1, &hkey);

    if (oStatus < 0)
        return oStatus & 0xffffff00;

    LSTATUS qStatus = RegQueryValueExA(hkey, "Version", NULL, NULL, lpdata, lpcbdata);
    LSTATUS cStatus = RegCloseKey(hkey);

    if (qStatus < 0 || lpcbdata >(LPDWORD)0x20)
        return cStatus & 0xffffff00;


    LPBYTE* dataptr = &lpdata;
    LPBYTE currentData;
    bool isOlder;

    // I don't know what the purpose of this is, it either returns 1 or breaks anyways.
    while (true)
    {
        currentData = *dataptr;
        isOlder = currentData < *expectedVersion;
        // 
        if (currentData != *expectedVersion)
            break;

        if (currentData == 0)
            return 1;

        currentData = dataptr[1];
        isOlder = currentData < expectedVersion[1];
        if (currentData != expectedVersion[1])
            break;

        dataptr = dataptr + 2;
        expectedVersion = expectedVersion + 2;

        if (currentData == 0)
            return 1;
    }

    // I worked out the obfuscated version and converted it to:
    int iVar = isOlder ? -1 : 1;

    return iVar >> 9 | iVar > -1;
}

void* PTR_008da72c;

unsigned int UINT_008da700;

void* MemoryPointer;
size_t memAllocationSize;

class AutoClass24 {
public:

    int field0_0x0;
    unsigned int field1_0x4;

    unsigned int FUN_00559b00(undefined4 param_1, int* param_2)
    {
        int iVar4 = (this->field1_0x4 - this->field0_0x0 >> 2) - 1;
        if (iVar4 > -1)
        {
            int* piVar3 = (int*)(this->field0_0x0 + iVar4 * 4);
            do
            {
                int iVar1 = *piVar3;
                //iVar2 = FUN_00560d70(iVar1);
                int iVar2 = 0;
                if (iVar2 != 0)
                {
                    *param_2 = iVar1;
                    param_2[1] = iVar2;
                    return (unsigned int)iVar2 >> 8 | 0x1;
                }
            } while (iVar4 > -1);
        }
        *param_2 = 0;
        param_2[1] = 0;
        return (unsigned int)param_2 & 0xffffff00;
    }
}



// FUN_0054c1d0:
// Ok, I think I'm starting to figure out what this function is. It takes a pointer to the first character in a "string", converts backslashes into forward slashes, and 
// does the reverse if param_1 is not 0
// 
//
// If param_1 is 0:
//
//  charptr is an array of unsigned characters, maybe it's a string, or their version of one. 
//  This function returns the number of characters beyond the address of charptr. It decides the end when it reaches a 0
//  thisptr seems to be a temporary variable, pointing at the current character. by the end it points to the byte after the ending 0, which seems kinda dangerous.
// The reason it's a variable is because Ghidra is convinced this function came from a class, and thisptr must be a this

// if param_1 is not 0:
//
// 

int FUN_0054c1d0(unsigned char *thisptr, int param_1, unsigned char *charptr)
{
    unsigned char currentChar;
    int lenOfData;
    int counter;
    unsigned char* pcVar2;
    unsigned char* tempPtr;
    
    if (param_1 == 0)
    {
        tempPtr = charptr;
        // Steps through the data until it reaches a 0, storing the next address as it goes.
        do
        {
            currentChar = *tempPtr;
            tempPtr = tempPtr + 1;
        } while (currentChar != '\0');
        // Converting raw addresses into byte difference
        // charptr has a +1 to account for the ending 0
        lenOfData = (int)tempPtr - ((int)charptr + 1);
        counter = lenOfData;
        if (lenOfData != 0)
        {
            do
            {
                // Converts backslashes to forward slashes, and uppercase to lowercase
                // thisptr and charptr both point at the same thing. Why.
                currentChar = *charptr;
                charptr = charptr + 1;
                if (currentChar == '\\')
                    currentChar = '/';
                else
                {
                    if (isupper(currentChar) != 0)
                    {
                        // Convert to lowercase. I love how odd yet simple it is.
                        currentChar += ' ';
                    }
                }
                // I don't see the purpose of using thisptr, since charptr should already be doing the work.
                thisptr = &currentChar;
                thisptr = thisptr + 1;
                
                counter -= 1;
            } while (counter != 0);
            return lenOfData;
        }
    }
    else
    {
        *thisptr = 0;
        tempPtr = thisptr;
        do
        {
            pcVar2 = tempPtr;
            tempPtr = pcVar2 + 1;
        } while (*pcVar2 != '\0');
        currentChar = *charptr;
        while (currentChar != '\0')
        {
            charptr = charptr + 1;
            // This is starting to seem like a converter/reverter function of some kind, with a problem.
            // This one converts slashes to backslashes, but good luck trying
            // to figure out which characters used to be uppercase.
            if (neverReferencedAgain == 0 || param_1 == 3)
                if (currentChar == '/')
                    currentChar = '\\';


        }
    }
    *pcVar2 = '\0';
    return lenOfData;
}



char FUN_0054c610(char param_1, char* in_EAX)
{
    unsigned char local_154;
    unsigned char local_104;
    if (param_1 > -1 && PTR_008da72c != NULL)
    {
        AutoClass24::FUN_00559b00(PTR_008da72c, in_EAX, (int*)&local_154);
        return;
    }
    FUN_0054c1d0(&local_104, 0, in_EAX);
}


/////////////////////////////////////////////////
// Loading Database

void LoadBinaryDatabase()
{
    UINT_008da700 = 0;
    free(MemoryPointer);
    MemoryPointer = NULL;
    memAllocationSize = 0;
    char cVar2 = FUN_0054c610('\0');
    if (cVar2 != '\0')
    {

    }



    //...

    CreateErrorMessageAndDie("Failed to load binary database \'%s\'!");
    return;
}

unsigned int g_WhatDoesThisDo;
unsigned short g_FPUControlWord;

unsigned int FUN_00529ed0(unsigned short in_FPUControlWord)
{
    unsigned int copyOfWhat;

    copyOfWhat = g_WhatDoesThisDo >> 0x10;
    if (g_WhatDoesThisDo == 0) {
        g_WhatDoesThisDo = 1;
        g_FPUControlWord = in_FPUControlWord;
    }
    return copyOfWhat << 2 | in_FPUControlWord;
}

/////////////////////////////////////////////////
// Startup Sequence

unsigned int UINT_008d7bb0;
unsigned int UINT_0069c2d0;
unsigned int UINT_008d780c;

DWORD Startup(HINSTANCE hInstance, undefined4 param_3, char* flags)
{
    g_Instance = hInstance;

    // The random seed is set to the current time
    DWORD seed = timeGetTime();
    srand(seed);

    // Dealing with the setup flag
    setupFlag = 0;
    if (flags != "" && (stricmp(flags, "-setup") || stricmp(flags, "setup")))
        setupFlag = 1;

    CoInitializeEx(NULL, 0);

    int verCheck = CheckDirectXVersion((LPBYTE*)"4.09.00.0904");
    if (verCheck == 0 && DialogBoxParamA(hInstance, (LPCSTR)0x83, (HWND)0x0, g_dlgproc, (LPARAM)0) == (INT_PTR)1)
        return 0xffffffff;

    FUN_00529ed0();

    // Unused flags
    strstr(flags, "-binarydb");
    strstr(flags, "-bedit");

    LoadBinaryDatabase();

    //...
}


/////////////////////////////////////////////////
// Debug Stuff

void CreateErrorMessageAndDie(char* message)
{
    char* local_800;
    char* body[1024];

    sprintf(*body, "%s", &message);
    MessageBoxA(NULL, (LPCSTR)body, "Fatal error", MB_ICONERROR);
    ExitProcess(0);
}

