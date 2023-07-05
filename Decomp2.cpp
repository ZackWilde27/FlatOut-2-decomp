// FlatOut 2 Decompilation

// So here's what I've learned so far:
//
// 0x37CB2A4 and 0x37CB325 are 4-byte integers, counting up during the game, like a timer or something.
// I've found that these values are set rather than incremented, because cheat engine can't override the value.
//

// Originally I made my own names for globals, but I'm now including the address to make investigating easier.

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
#include <fileapi.h>
#include <libloaderapi.h>
#include <process.h>

// Structs

// Credit to mrwonko on GitHub for their file object reverse engineering

// AutoClass 25
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

                WriteFile(hFile, buffer_temp, tempToWrite, (LPDWORD)&bytesWritten, NULL);
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

struct astruct_138
{
    // 104 Undefined bytes at offset 0x0
    HANDLE handle_0x68;
    // 8 undefined bytes at offset 0x6C
    LONG long_0x74;
    void * unkn_0x78;
    // 4 undefined bytes at offset 0x7C
    DWORD dw_0x80;
};

// AutoClass 23
class AnotherFileThing
{
public:
    HANDLE handle;

    undefined4 __fastcall LoadFromHandle(DWORD numBytes, astruct_138 *unaff_ESI, LONG in_EAX, LPVOID unaff_EBX)
    {
        DWORD DVar2 = numBytes;
        DWORD DVar3;
        bool BVar1;
        HANDLE hFile = this->handle;
        unaff_ESI->dw_0x80 = numBytes;
        unaff_ESI->long_0x74 = in_EAX;
        unaff_ESI->unkn_0x78 = NULL;
        unaff_ESI->handle_0x68 = hFile;
        if (UINT_008da730 == 0)
        {
            DVar3 = SetFilePointer(hFile, in_EAX, NULL, FILE_BEGIN);
            if (DVar3 == 0xffffffff)
            {
                GetLastError();
            }
            else
            {
                BVar1 = ReadFile(hFile, unaff_EBX, DVar2, &numBytes, NULL);
                if (BVar1 > -1) goto LAB_00559FAB;
            }
        }
        else
        {
            BVar1 = ReadFile(hFile, unaff_EBX, numBytes, NULL, (LPOVERLAPPED)&unaff_ESI)
        }
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

/////////////////////////////////////////////////
// Variables

struct Settings Settings;

HINSTANCE g_Instance;

DLGPROC g_dlgproc;

// It's an int, but used as a bool.
int setupFlag_008da684 = 0;

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// Leads me to believe it means ROMU v0.28
const char* verString_00698b4c = "Version_0.28_build_2004.09.20";


/////////////////////////////////////////////////
// File Functions

bool WriteCharToStream(char in_char, FILE* file)
{
    int result = fputc(in_char, file);
    return result != -1;
}

// Raw code stored as text inside the game
// I don't recognize the language.
/*
Queue = {  };

function Queue.new();
    local s = {
            _queue={},
            __index = Queue,
            setmetatable(s, s)
            return s
            }
end

function Queue:Clear()
    self.queue={}
end

function Queue:Push(func, param)
    table.insert(self._queue, {func=func, param=param})
end

function Queue:PushFirst(func, param)
    table.insert(self._queue, 1, {func=func, param=param})
end

function Queue:Pop()
    if table.getn(self._queue) > 0 then
        return table.remove(self._queue, 1)
    end
end

function Queue:Empty()
    if table.getn(self._queue) == 0 then
        return true
        end
    return nil
end

function Queue:Size()
    return table.getn(self._queue)
end

function Queue:CallFirst()
    if table.getn(self._queue) > 0 then
        local t=rawget(self.queue, 1)

    if not t.func or type(t.func) ~= "function" then return end

    local param=t.param or {}
    return t.func(unpack(param))
end

end

nSandboxes = {}

--//setmetatable(Sandboxes, {__mode="v"})

nSandbox = {}

function Sandbox.GetSandbox(name, environment)
    local s = Sandboxes[name]
    if not s then
        ts = {
            __name = name,
            __globals = {},
            __environment = environment or {},
            t__index = function(table,key)
                local value
                tvalue=_parent.rawget(__environment,key)
                if value then return value end
                return _parent[key]
            end,
            __newindex = function(table,key,value)
                t_parent.rawset(__environment,key,value)
            end,

            t_parent=getfenv(0),
        }
        local meta = {
            t__index = Sandbox,
        }
        s.__environment.getglobals = function()
            local _s=s
            return Sandbox.GetEnvironment(_s)
        end
        setfenv(s.__index,s);
        setfenv(s.__newindex,s);
        setmetatable(s.__globals,s);
        setmetatable(s,meta);
        Sandboxes[name]=s
    end

    return s

end

function Sandbox.RemoveSandbox(box)
    local name=box.__name
    if not name then return end
    if Sandboxes[name] then Sandboxes[name]=nil end
end

function Sandbox:GetEnvironment()
    return self.__environment
end

/* There's more but man that's a lot of typing, I had to count line returns and tabs to get it right.*/


/////////////////////////////////////////////////
// Direct X Related Functions

// CheckDirectXVersion
//
// Takes an expected version and compares that to the current version
// stored in the registry. 

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

    if (qStatus < 0 || lpcbdata > (LPDWORD)0x20)
        return cStatus & 0xffffff00;


    LPBYTE* dataptr = &lpdata;
    LPBYTE currentData;
    bool isOlder;

    // Goes through the version string, and if it reaches equal or greater numbers,
    // it'll return 1, otherwise, it'll return a concatenation that gives some
    // info about the differences.
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
    unsigned int iVar = isOlder ? -1 : 1;

    // Concatenate by shifting over an extra byte and or-ing.
    return iVar << 9 | iVar > -1;
}

unsigned int UINT_008e5770;
unsigned int UINT_008e5d70;
IDirect3D9* D3D9_008da784;
HINSTANCE HINST_008da2dc;
unsigned int UINT_008da270;
HWND g_HWND;


// CreateD3DWindow
//
//
HWND CreateD3DWindow(HWND parent, HINSTANCE hInstance, LPCSTR title, HICON icon, HCURSOR cursor, astruct_110* param_6, int param_7, astruct_135* param_8, unsigned int param_9, int * in_EAX)
{
    int posX;
    int posY;
    unsigned int style;
    unsigned int* puVar3 = &UINT_008e5770;
    WNDCLASSA newWindow;
    HWND hWnd;
    for (int n = 0x180; n != 0; n--)
    {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
    }
    puVar3 = &UINT_008e5d70;
    for (int n = 0x20; n != 0; n--)
    {
        *puVar3 = 0;
        puVar3 = puVar3 + 1;
    }
    if (D3D9_008da784 != NULL || (D3D9_008da784 = Direct3DCreate9(D3D_SDK_VERSION), D3D9_008da784 != NULL))
    {
        HINST_008da2dc = hInstance;
        // UINT_008da270 ends up as 19, does not seem to change.
        UINT_008da270 = param_9;
        int nWidth;
        int nHeight;
        int iStack_7c;

        if ((param_9 & 4) == 0)
        {
            nWidth = param_6->field4_0x4;
            nHeight = param_6->field5_0x8;
        }
        else
        {
            style = ((param_9 & WS_EX_TRANSPARENT != 0) & 0xff310000) + WS_OVERLAPPEDWINDOW;
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
            nHeight = iVar2 + param_6->field5_0x8 + 1 + (posX + posY + iVar1);
            nWidth = iStack_7c;
        }
        newWindow.style = 0;
        newWindow.lpfnWndProc = (WNDPROC)&LAB_005a6270;
        newWindow.cbClsExtra = 0;
        newWindow.cbWndExtra = 0;
        newWindow.hInstance = hInstance;
        newWindow.hIcon = icon;
        newWindow.hCursor = cursor;
        newWindow.hbrBackground = (HBRUSH)GetStockObject(5);
        newWindow.lpszMenuName = NULL;
        newWindow.lpszClassName = "BDX9 Render Window";
        RegisterClassA(&newWindow);
        unsigned int uStack_98 = param_9 & WS_EX_TRANSPARENT;
        if (uStack_98 == 0)
        {
            posY = -0x80000000;
            posX = -0x80000000;
        }
        else
        {
            posY = 0;
            posX = 0;
        }

        // Creating the window
        g_HWND = CreateWindowExA(WS_EX_LEFT, "BDX9 RenderWindow", title, style, posX, posY, nWidth, nHeight, parent, NULL, hInstance, NULL);

        if (g_HWND != NULL)
        {
            posX = ShowCursor(in_EAX[0x8a]);
            hWnd = g_HWND;
            in_EAX[0x69] = posX;
            ShowWindow(hWnd, SW_NORMAL);
            EnableWindow(g_HWND, true);
            UpdateWindow(g_HWND);
            SetFocus(g_HWND);
            if (uStack_98 == 0)
            {

            }
        }

    }
}

struct astruct_114 {

};

unsigned int* FUN_005c07b0(astruct_114* param_1, char* string, unsigned int length)
{
    unsigned int* puVar1;
    unsigned int local_8;
    unsigned int local_c = length;
    unsigned int uVar2 = (length >> 5) + 1;
    for (local_8 = length; uVar2 <= local_8; local_8 -= uVar2)
        local_c = local_c * 0x20 + (local_c >> 2) + (unsigned int)(byte)string[local_8 - 1] ^ local_c;

    unsigned int *local_14 = *(unsigned int**)(*(int*)param_1[4] + (*(int*)(param_1[4] + 8) - 1U & local_c) * 4);
    do
    {
        if (local_14 == 0)
        {
            puVar1 = FUN_005c08b0(param_1, (unsigned int)string, length, local_c);
            return puVar1;
        }
        if (local_14[3] == length)
        {
            bool notDoneYet = true;
            uVar2 = length;
            char *pcVar3 = string;
            puVar1 = local_14 + 4;
            do
            {
                if (uVar2 == 0) break;
                uVar2 -= 1;
                notDoneYet = *pcVar3 == *puVar1;
                pcVar3 = pcVar3 + 1;
                puVar1 = puVar1 + 1;
            } while (notDoneYet);
            if (notDoneYet)
            {
                if ((*(byte*)(local_14 + 5) & (*(byte*)(param_1[4] + 0x14) ^ 3) & 3) == 0)
                {
                    return local_14;
                }
                *(byte*)(local_14 + 5) = *(byte*)(local_14 + 5) ^ 3;
                return local_14;
            }
        }
        // Setting the pointer to the memory address equal to it's value?
        local_14 = (unsigned int *)*local_14;
    } while (true);
}

struct astruct_114
{
    // 8 Undefined bytes at 0x0
    int* field8_0x8;
    int field9_0xc;
    int field10_0x10;
    int field11_0x14;
    // 44 Undefined bytes at 0x18
    int* field56_0x44;
    // 4 undefined bytes at 0x48
    int field61_0x4c;
    int field62_0x50;
};

int* FUN_005b3d70(astruct_114* param_1, int param_2)
{
    int* piVar2;
    if (param_2 < 1)
        // Converted -9999 into hex, everything else is in hex
        if (param_2 < -0x270F)
        {
            if (param_2 == -0x2712)
                piVar2 = param_1->field56_0x44;
            else if (param_2 == -0x2711)
            {
                param_1->field61_0x4c = *(int*)(**(int**)(param_1->field11_0x14 + 4) + 0xc);
                param_1->field62_0x50 = 5;
                piVar2 = &param_1->field61_0x4c;
            }
            else if (param_2 == -10000)
                piVar2 = (int*)(param_1->field10_0x10 + 0x5c);
            else
            {
                iVar1 = **(int**)param_1->field11_0x14;
            }
        }
}

void FUN_005b4e70(astruct_114 *param_1, int param_2, char *param_3)
{
    int* piVar2 = FUN_005b3d70(param_1, param_2);
    char * local_18 = param_3;
    char cVar1;
    do
    {
        cVar1 = *local_18;
        local_18 = local_18 + 1;
    } while (cVar1 != '\0');
    unsigned int *local_c = FUN_005c07b0(param_1, param_3, local_18 - (param_3 + 1));
    FUN_005bc570(param_1, piVar2, (float*)&local_c, (int*)(param_1[2] + -8));
    param_1[2] = param_1[2] - 8;
    return;
}

// 1 = US, 2 = Germany, not 1 or 2 = Europe
// Germany got it's own version,
// Also, my presumably US copy is set to 0, meaning Europe. Changing it after starting the game seems to have no effect.
unsigned int version_0069c13c = 0;

void FUN_0049180(int param_1)
{
    const char* version_string;

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
    

}



AutoClass24 * AC24_008da72c;

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
// and that's the only time it's ever referenced.
// Cheat Engine says this value is initialized to 0, so it always overrides.
int g_slashOverride = 0;

// SlashConvertString:
//
// This function copies the in_string to the out_string, returning the length of the in_string.
// It'll also convert uppercase to lowercase.

// If mode is 0:
//
// Starts at the location of the out_string pointer
// Convert backslashes to slashes
// By the end, in_string and out_string will point at the character after the ending \0

// If mode is not 0:
//
// Starts at the location after the first \0 in the out_string
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
                // Setting the out_string to point at the address of currentChar, rather than setting the value.
                // So every character is going to point at currentChar.
                // Still a little confused
                out_string = &currentChar;
                out_string = out_string + 1;
            }
            return lenOfData;
        }
    }
    else
    {
        // If mode is not 0, replace the first character of the out_string with \0.
        *out_string = 0;
        tempPtr = out_string;
        // So first it steps through the output string until a 0, and starts the copy process from there.
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

char __fastcall FUN_0054c610(char param_1, unsigned char* in_EAX)
{
    int *local_154;
    unsigned char *local_104;
    AutoClass24 local_1;
    if (param_1 > -1 && AC24_008da72c != NULL)
    {
        AC24_008da72c->FUN_00559b00(in_EAX, local_154);
        return;
    }
    SlashConvertString(local_104, 0, in_EAX);
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

// Still confused about this one

unsigned int unkn_008da6a0;
unsigned short FPUConW_008d781c;

unsigned int SetFPUCW(unsigned short in_FPUControlWord)
{
    unsigned int copyOfWhat;

    copyOfWhat = unkn_008da6a0 >> 0x10;
    if (unkn_008da6a0 == 0) {
        unkn_008da6a0 = 1;
        FPUConW_008d781c = in_FPUControlWord;
    }
    return copyOfWhat << 2 | in_FPUControlWord;
}

void* PTR_008e8418;

/////////////////////////////////////////////////
// Startup Sequence

unsigned int UINT_008d7bb0;
unsigned int UINT_0069c2d0;
unsigned int UINT_008d780c;
unsigned int UINT_008e855c;
void* MEM_008da568;

DWORD Startup(HINSTANCE hInstance, unsigned int param_3, char* flags)
{
    g_Instance = hInstance;

    // The random seed is set to the current time
    DWORD seed = timeGetTime();
    srand(seed);

    // Dealing with the setup flag
    setupFlag_008da684 = 0;
    if (flags != "" && (stricmp(flags, "-setup") || stricmp(flags, "setup")))
        setupFlag_008da684 = 1;

    CoInitializeEx(NULL, 0);

    int verCheck = CheckDirectXVersion((LPBYTE*)"4.09.00.0904");
    if (verCheck == 0 && DialogBoxParamA(hInstance, (LPCSTR)0x83, (HWND)0x0, g_dlgproc, (LPARAM)0) == (INT_PTR)1)
        return 0xffffffff;

    // Sets unkn_008da6a0 to 1
    SetFPUCW(FPUConW_008d781c);

    // Unused flags
    strstr(flags, "-binarydb");
    strstr(flags, "-bedit");

    LoadBinaryDatabase();

    UINT_0069c2d0 = (unsigned int)&UINT_008d7bb0;
    // Allocating ~131 KB
    void *newMem = malloc(0x20044);
    if (newMem == NULL)
        UINT_008d780c = 0;
    else
        UINT_008d780c = FUN_0051c520();

    // Allocating 8.2KB, kinda strangely
    // the first 1K is untouched so far
    // 1K - 2K is set to NULL
    // 2K - 8.2K is untouched so far
    char** newMem2 = (char **)malloc(0x2008);

    if (newMem2 == NULL)
        newMem2 = NULL;
    else
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
        FUN_00551090(newMem2);
    }
    MEM_008da568 = newMem2;
    FUN_00550f90(newMem2);
    FUN_0045lb70(&UINT_0069c128);
    int iVar1 = FUN_00520cf0();


    // From here its starting to seem like a shutdown sequence.


    if (iVar1 != 0)
        FreeALotOfMemory();

    CoUninitialize();
    if (UINT_008e855c != 0)
        UINT_008e855c -= 1;

    // Sneaky function call, where they use a pointer and immediately set the pointer
    // to NULL
    if (PTR_008e8418 != NULL && UINT_008e855c == 0)
    {
        *PTR_008e8418(1);
        PTR_008e8418 = NULL;
    }

    FUN_0051cdc0();
    newMem = PTR_008da568;
    if (PTR_008da568 != NULL)
    {
        free(PTR_008da568 + 0x2004);
        free(newMem);
    }
    PTR_008da568 = NULL;
    return 0;
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

/////////////////////////////////////////////////
// entry / main

DWORD DWORD_006a2cd8;
undefined4 DAT_00000094;
LPSTR LPSTR_008edca4;
LPWCH LPWCH_006a2c2c;

int main(int argc, char* argv[])
{
    int* piVar2;
    int iVar1;
    bool bVar3;
    char* flags;
    LPSTARTUPINFOA startInfo;
    HINSTANCE hInst;

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
    piVar2 = (int*)((int)hmodule->unused + hmodule[0xf].unused);
    if ((int)&hmodule->unused == 0x5a4d && *piVar2 == 0x4550)
        if (*(short*)(piVar2 + 6) == 0x10b)
        {
            if (piVar2[0x1d] > 0xe)
            {
                iVar1 = piVar2[0x3a];
                goto LAB_006026F9;
            }
        } else if ((int)piVar2 + 6 == 0x20b && piVar2[0x21] > 0xe)
        {
                iVar1 = piVar2[0x3e];
            LAB_006026F9:
                bVar3 = iVar1 != 0;
                goto LAB_006026FF;
        }
        bVar3 = false;
    LAB_006026FF:
        GetStartupInfoA(startInfo);
        flags = argv[1];
        unsigned int uVar4 = 0;
        hInst = GetModuleHandleA(NULL);
        int code = Startup(hInst, uVar4, flags);
        if (bVar3)
        {
            // Performs complete C library termination procedures and returns to caller, but doesn't terminate process.
            // - Documentation
            _cexit();
            return code;
        }
        exit(code);
}

/////////////////////////////////////////////////
// Unsure

void FUN_0052a170(float* param_1, float* in_EAX)
{
    float fVar1 = *param_1;
    in_EAX[0xf] = 1.0;
    // x2
    fVar1 = fVar1 + fVar1;
    float fVar11 = param_1[1] + param_1[1];
    float fVar12 = param_1[2] + param_1[2];
    float fVar10 = fVar1 * param_1[3];

}

unsigned int UINT_008da730;

void (*FUNC_008da6f4)();

void OpenBFS(LPCSTR filename, HANDLE *unaff_EDI)
{
    LPCSTR pCVar5 = filename;
    DWORD fileFlags;
    HANDLE pvVar6;
    AutoClass24 *pAVar4;
    char cVar1;
    do
    {
        cVar1 = *pCVar5;
        pCVar5 = pCVar5 + 1;
    } while (cVar1 != '\0');
    unaff_EDI[0x88] = NULL;
    if (UINT_008da730 == 0)
    {
        fileFlags = FILE_ATTRIBUTE_NORMAL;
    }
    else
    {
        fileFlags = FILE_FLAG_DELETE_ON_CLOSE | FILE_ATTRIBUTE_NORMAL;
    }
    pvVar6 = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, fileFlags, NULL);
    *unaff_EDI = pvVar6;
    if (pvVar6 == NULL)
    {
        if (FUNC_008da6f4 != NULL)
        {
            FUNC_008da6f4();
        }
        CreateErrorMessageAndDie("Failed to open BFS archive: %s");
    }
    DWORD fSize = GetFileSize(pvVar6, NULL);
    if (fSize == 0xffffffff)
        CreateErrorMessageAndDie("Could not query file size for BFS archive: %s");

    pAVar4 = AC24_008da72c;
    unaff_EDI[1] = pvVar6;
    FUN_0059b60(pAVar4, unaff_EDI, aiStack_10, 0, 0x10);
}

void FUN_0059b60()
