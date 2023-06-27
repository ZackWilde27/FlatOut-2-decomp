// FlatOut 2 Decompilation

// My first ever decompilation, and given how long these things take, maybe not even.

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

// Credit to mrwonko on GitHub for their file object reverse engineering

class FileObject
{
public:
    void* vtable;

    char buffer[0x4000]; // 0x4

    int alwaysNeg1;           // 0x4004 - is -1 on newly opened track_spvs.gen

    char* filePos;         // 0x4008 - "virtual" file pos - reads in 16kb blocks internally, but allows for arbitrary reads
    char* realFilePos;     // 0x400C - real file's filePos, gets increased by bytesRead
    void* size;        // 0x4010 - returned by BvhFile_Func8 unless it's -1 - *0x4008 otherwise
    HANDLE handle;      // 0x4014
    void* unknown;         // 0x4018 - some bitmask?
    char* filenameRelated; // 0x401C
    char* filenameRelated; // 0x4020
    int always0_0;
    int always0_1;
    int always0_2;
    int always0_3;

    // Writes a section of the file to it's handle, starting at the buffer_item. Returns the number of bytes actually written for comparison.
    // Updates realFilePos and filePos to point after the written bytes.
    int WriteFileToHandle(char buffer_item, DWORD bytesToWrite)
    {
        int bytesWritten = 0;
        int totalBytesWritten = 0;
        HANDLE hFile;
        DWORD tempToWrite;

        // My own addition, just to avoid changing the buffer_item directly.
        // It's probably intentional for some reason, but for now, I haven't figured it out.
        LPCVOID buffer_temp = &buffer_item;

        if (bytesToWrite != 0)
        {
            hFile = this->handle;

            for (int d = bytesToWrite; d != 0; d -= tempToWrite)
            {
                // Writes in 64 KB chunks unless what's left is less.
                tempToWrite = 0xffff;
                if (d < 0x10000)
                    tempToWrite = d;

                WriteFile(hFile, &buffer_temp, tempToWrite, (LPDWORD)&bytesWritten, NULL);
                // I tried to make this less confusing by just adding but it throws errors about incomplete objects.
                buffer_temp = (LPCVOID)((int)buffer_temp + tempToWrite);
                totalBytesWritten += bytesWritten;
            }
        }
        // Advance the pointers
        this->realFilePos = this->realFilePos + bytesToWrite;
        this->filePos = this->filePos + bytesToWrite;
        return totalBytesWritten;
    }
};



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

    // I'm still not sure what this part does.
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

    // I worked out the complicated version and converted it to:
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
};

// It used to be called neverReferencedAgain, because this next function checks if it's 0,
// and that's the only time it's ever referenced. Maybe its for debugging?
int g_slashOverride = 1;

// SlashConvertString:
//
// Since getting the length is part of copying a string, they have a mode that only gets the length.
// It'll also convert uppercase to lowercase.

// If mode is 0:
// This function copies the in_string to the out_string, returning the length of the in_string.
//
// Starts at the location of the in_string pointer
// Convert backslashes to slashes
// By the end, in_string and out_string will point at the character after the ending 0

// If mode is not 0:
// This function simply returns the length of the in_string
//
// Starts at the location after the first 0 character
// If mode is 3, or g_slashOverride is 0, it'll convert slashes to backslashes
// By the end, in_string will point at the character after the ending 0
int SlashConvertString(unsigned char* in_string, int mode, unsigned char* out_string)
{
    unsigned char* tempPtr;
    unsigned char currentChar;
    int lenOfData;
    int counter;
    unsigned char* pcVar2;
    
    if (mode == 0)
    {
        tempPtr = in_string;
        // Steps through the data until it reaches a 0 character, storing the next address as it goes.
        do
        {
            currentChar = *tempPtr;
            tempPtr = tempPtr + 1;
        } while (currentChar != '\0');
        // Converting raw addresses into byte difference
        lenOfData = (int)tempPtr - ((int)in_string + 1);
        counter = lenOfData;
        if (lenOfData != 0)
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
                    if (isupper(currentChar) != 0)
                    {
                        // Convert to lowercase. I love how odd yet simple it is.
                        currentChar += ' ';
                    }
                }
                // Setting the out_string to point at the address of currentChar
                out_string = &currentChar;
                out_string = out_string + 1;
            }
            return lenOfData;
        }
    }
    else
    {
        // If mode is not 0, replace the first character to a 0.
        *out_string = 0;
        tempPtr = out_string;
        // So first it steps through until a 0, and starts from there instead.
        do
        {
            pcVar2 = tempPtr;
            tempPtr = pcVar2 + 1;
        } while (*pcVar2 != '\0');

        currentChar = *in_string;

        while (currentChar != '\0')
        {
            in_string = in_string + 1;
            if (g_slashOverride == 0 || mode == 3)
                if (currentChar == '/')
                {
                    currentChar = '\\';
                }
            else if (currentChar == '\\')
                currentChar = '/';

            // Converting to lowercase to uppercase
            lenOfData = isupper(currentChar);
            if (lenOfData != 0)
                currentChar += ' ';

            *pcVar2 = currentChar;
            pcVar2 = pcVar2 + 1;
            currentChar = *in_string;
        }
        lenOfData = (int)pcVar2 - (int)out_string;
    }
    *pcVar2 = '\0';
    return lenOfData;
}

char FUN_0054c610(char param_1, unsigned char* in_EAX)
{
    unsigned char local_154;
    unsigned char local_104;
    AutoClass24 local_1;
    if (param_1 > -1 && PTR_008da72c != NULL)
    {
        local_1.FUN_00559b00(PTR_008da72c, in_EAX, (int*)&local_154);
        return;
    }
    SlashConvertString(&local_104, 0, in_EAX);
}

void FUN_0054c540()
{
    astruct_94* unaff_ESI;
    int* piVar1 = unaff_ESI->field23_0x20;
}

/////////////////////////////////////////////////
// Loading Database

void LoadBinaryDatabase()
{
    UINT_008da700 = 0;
    free(MemoryPointer);
    MemoryPointer = NULL;
    memAllocationSize = 0;

    FUN_0054c540();

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

    FUN_00529ed0(g_FPUControlWord);

    // Unused flags
    strstr(flags, "-binarydb");
    strstr(flags, "-bedit");

    LoadBinaryDatabase();

    //...
}


/////////////////////////////////////////////////
// Debug Stuff

void CreateErrorMessageAndDie(const char* message)
{
    char* local_800;
    char* body[1024];

    sprintf(*body, "%s", &message);
    MessageBoxA(NULL, (LPCSTR)body, "Fatal error", MB_ICONERROR);
    ExitProcess(0);
}

DWORD DWORD_006a2cd8;
undefined4 DAT_00000094;

int main()
{
    int* piVar2;
    int iVar1

    // Get OS information
    LPOSVERSIONINFOA osInfo = (LPOSVERSIONINFOA) &DAT_00000094;
    GetVersionExA(osInfo);

    DWORD dStack_110;
    DWORD dStack_104;
    unsigned int uStack_108;
    DWORD_006a2cd8 = uStack_108;
    if (dStack_104 != 2)
    {
        DWORD_006a2cd8 |= 0x8000;
    }

    HMODULE hmodule = GetModuleHandleA(NULL);
    piVar2 = (int*)((int)&hmodule->unused + hmodule[0xf].unused);
    if ((int)&hmodule->unused == 0x5a4d && *piVar2 == 0x4550)
        if (*(short *)(piVar2 + 6) == 0x10b)
            if (piVar2[0x1d] > 0xe)
            {
                iVar1 = piVar2[0x3a];
            }

}

