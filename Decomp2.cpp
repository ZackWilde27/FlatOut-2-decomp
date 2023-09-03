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

unsigned int UINT_008e5770;
unsigned int UINT_008e5d70;
IDirect3D9* D3D9_008da784;
HINSTANCE HINST_008da2dc;
unsigned int UINT_008da270;
HWND HWND_008da79c;
unsigned int UINT_008da728;
unsigned int UINT_008d7c30;

HICON HICON_008da544;
unsigned int UINT_008da540;
LRESULT UINT_006d6900;
unsigned int UINT_006d6908;
unsigned int UINT_008da548;
unsigned int UINT_006d690c;
unsigned int UINT_006d68d0;
unsigned int UINT_006d68d8;
unsigned int UINT_006d68e8;
unsigned int UINT_006d68f0;

LRESULT DAT_006d68dc;
LRESULT DAT_006d68e0;
LRESULT DAT_006d68ec;

HGDIOBJ HGDIOBJ_006d67b8;
HWND HWND_008da56c;
LPCSTR lpOperation_0066ab90;

LRESULT UINT_008db344[30];

void* PTR_LAB_007a9e4[5];

const char** PTR_u_NO_TEXT_0069df4 = &u_NO_TEXT_0066b38c;

const char* u_NO_TEXT_0066b38c = "u\"NO_TEXT\"";

unsigned int unkn_008da6a0;
unsigned short FPUConW_008d781c;

unsigned int DAT_0069ba70;
unsigned int DAT_0069ba74;
unsigned int DAT_0069ba78;
unsigned int DAT_0069ba7c;
unsigned int DAT_0069ba80;
unsigned int DAT_0069ba84;
unsigned int DAT_0069ba88;
unsigned int DAT_0069ba8c;

unsigned int UINT_0069c2d0;

unsigned int UINT_008d780c;
unsigned int UINT_008d7bb0;

void* MEM_008da568;
void (*FUNC_008da6f4)();
unsigned int UINT_008da700;
AutoClass24* AC24_008da72c;
unsigned int UINT_008da730;

unsigned int UINT_008e855c;



void* MemoryPointer;
size_t memAllocationSize;

int _Size;





/////////////////////////////////////////////////
// Structs

// astruct_1
struct ArrayMaybe {
    INT count;
    // 4 undefined bytes at offset 0x4
    INT lenOfItem;
    // 8 undefined bytes at offset 0xC
    INT memLoc;
};

// Returns the memory address of an item in an array, or 0.
int GetItem(ArrayMaybe* rray, int index)
{
    if ((index > -1) && (index < rray->count))
    {
        return rray->lenOfItem * index + rray->memLoc;
    }
    return 0;
}

struct astruct_42 {
    void (*func_0x0)();
    unsigned int field1_0x4;
    unsigned int field2_0x8;
    unsigned int field3_0x10;
    // Maybe this is all one buffer, I don't know
    DWORD dw1_0xc;
    // 4 undefined bytes at offset 0x10
    DWORD dwbuffer1_0x14[10];
    // 4 undefined bytes at offset 0x3c
    DWORD dwbuffer2_0x40[35];
    // 4 undefined bytes at offset 0xcc
    unsigned int field4_0xd0;
    // 12 undefined bytes at offset 0xd4
    unsigned int field5_0xe0;
    unsigned int field6_0xe4;
};


struct astruct_110 {
    // 4 undefined bytes at 0x0
    int field0_0x4;
    unsigned int field1_0x8;
    int field2_0xc;
    // 136 undefined bytes at 0x10
    undefined4 field3_0x98;
    undefined4 field4_0x9c;
    undefined4 field5_0xa0;
    unsigned int field6_0xa4;
};

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

struct astruct_138
{
    // 104 undefined bytes at offset 0x0
    HANDLE handle_0x68;
    // 8 undefined bytes at offset 0x6C
    LONG long_0x74;
    void * unkn_0x78;
    // 4 undefined bytes at offset 0x7C
    DWORD dw_0x80;
};

struct astruct_140 {
    // 64 undefined bytes at offset 0x0
    unsigned int field0_0x40;
    unsigned int field1_0x44;
    // 16 undefined bytes at offset 0x48
    HINSTANCE hinst_0x58;
};

// placeholder
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
// Classes

// AutoClass 23
class Handleish
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
            BVar1 = ReadFile(hFile, unaff_EBX, numBytes, NULL, (LPOVERLAPPED)&unaff_ESI);
        }
    }
};

// Credit to mrwonko on GitHub for their file object reverse engineering
// AutoClass 25
class FileObject
{
public:
    void* vtable;

    char buffer[0x4000]; // 0x4

    int alwaysNeg1;           // 0x4004 - is -1 on newly opened track_spvs.gen,
    // Ghidra says it's always -1

    char* filePos;         // 0x4008 - "virtual" file pos - reads in 16kb blocks internally, but allows for arbitrary reads
    char* realFilePos;     // 0x400C - real file's filePos, gets increased by bytesRead
    void* size;        // 0x4010 - returned by BvhFile_Func8 unless it's -1 - *0x4008 otherwise
    HANDLE handle;      // 0x4014
    void* unknown;         // 0x4018 - some bitmask?
    char* filenameRelated; // 0x401C
    char* filenameRelated; // 0x4020
    int always0_0; // 0x4024
    int always0_1; // 0x4028
    int always0_2; // 0x402C
    int always0_3; // 0x4030


    // Writes a section of the file to it's handle, starting at the buffer_item. Returns the number of bytes actually written for comparison.
    // Updates realFilePos and filePos to point after the written bytes.
    DWORD WriteFileToHandle(char buffer_item, DWORD bytesToWrite)
    {
        LPDWORD bytesWritten;
        DWORD totalBytesWritten;
        HANDLE hFile;
        DWORD tempToWrite;

        // My own addition, just to avoid changing the buffer_item directly.
        // It's probably intentional, but for now, I haven't figured it out.
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

                WriteFile(hFile, &buffer_item, tempToWrite, bytesWritten, NULL);
                // I tried to make this less confusing by just adding but it throws errors about incomplete objects.
                buffer_temp = (LPCVOID)((int)buffer_temp + tempToWrite);
                totalBytesWritten += *bytesWritten;
            }
        }
        // Advance the pointers
        this->realFilePos = this->realFilePos + bytesToWrite;
        this->filePos = this->filePos + bytesToWrite;
        return totalBytesWritten;
    }
};

/////////////////////////////////////////////////
// Lua

// Lua script stored as text inside the game.
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

function Sandbox:SetEnvironment(environment)
    local meta=getmetatable(self)
    setmetatable(self, nil)
    self._environment=environment or {}

    setmetatable(self, meta);
end

function Sandbox:SetSandbox(func)
    setfenv(func, self._globals);
end

function Sandbox:ClearGlobals()
    local meta=getmetatable(self)
    setmetatable(self, nil)
    self.__environment={}

    setmetatable(self,meta);
end



function Sandbox:DoFile(filename)
    
    dofile(filename)

--[[--/*
    scope=self.__globals --- or getfenv(0)

    local f,err=loadfile(filename);
    if f then
        setfenv(f, scope)
        return f()
    end

    error(err);
--]]--*/
/*
end


function Sandbox:DoString(string)

    scope=self.__globals

    local f,err=loadstring(string)

    if f then
        setfenv(f,scope)
        local ok,err=pcall(f)

        if not ok then
            error(err)
            return nil,err
        end
        return true
    end

    error(err)
end

TRUE = 1
FALSE = 0

#ifdef _USE_DEBUGLOG_

function LOG(...)
    local s=string.format(unpack(arg))
    host.LOG(s)
end

#else

function LOG(...)
end

#endif


function ERROR(...)
    local s=string.format(unpack(arg))
    error(s);
end

function enum(start,values)
    local i
    local enumeration

    if type(start)=="table" then
        i=0
        enumeration=start
    else
        i=start
        enumeration=values
    end

    local r={}

    local k,v

    for k,v in pairs(enumeration) do
        r[v]=i
        i=i+1   
    end

    return r
end
*/

/* Lua Script Part 2, there's more

--///////////////////////////////////////////////////////////////////////////
--// WindowFunctions.bed
--///////////////////////////////////////////////////////////////////////////
--// Copyright (c) 2003 Bugbear Entertainment ltd. 
--// All Rights Reserved.
--// 
--// @date 15.4.2003 10:01:58
--//
--// @Author Mikko Sivulainen (mikko.sivulainen@bugbear.fi)
--///////////////////////////////////////////////////////////////////////////


---helper functions
function SAFEPOS(x,y)
    local t_x = TITLESAFE_X or 0
    local t_y = TITLESAFE_Y or 0
    return { t_x+x,t_y+y }
end

function POS(x,y)
    return { x,y }
end

function SIZE(x,y)
    return { x,y }
end

function SYSTEMFONT()
    return wm.GetResource(\"SystemFont\");
end 

function GETFONT(name)
    return wm.GetResource(name)
end

function AddPos(Pos1, Pos2)
    local x=Pos1[1]
    local y=Pos1[2]
    x=x+Pos2[1]
    y=y+Pos2[2]
    return POS(x, y)
end

function AddPosAndMakeSafe(Pos1, Pos2)
    local x=Pos1[1]
    local y=Pos1[2]
    x=x+Pos2[1]
    y=y+Pos2[2]
    return SAFEPOS(x, y)    
end

function MakeSafePos(Pos)
    return SAFEPOS(Pos[1], Pos[2])
end



---enums

DIRECTION = enum{
        UPDOWN,
        LEFTRIGHT,
}





wm._Menu={}
wm._ActiveMenu={}
--setmetatable(wm._Menus,{ __mode =\"k\" })



function wm.LoadMenu(menuname,filename)
    local sandbox=Sandbox.GetSandbox(menuname)
    
    local env=sandbox:GetEnvironment()
    env.menuself=menuname
    

    wm._Menu[menuname]=sandbox
    
    return sandbox:DoFile(filename)
end


function wm.GetMenu(menuname)
    local m=wm._Menu[menuname] or ERROR(\"wm.GetMenu: menu \'%s\' not found\",menuname)
    return m
end


function wm.DeleteMenu(menuname)
    wm._Menu[menuname]=nil
    collectgarbage();
end


function wm.DeleteAll()
    wm._Menu={}
    
    collectgarbage();
end


function wm.Activate(win)
    local i
    for i=1,table.getn(wm._ActiveMenu) do
        if wm._ActiveMenu[i] == win then return end
    end

    wm.ActivateWindow(win)
    table.insert(wm._ActiveMenu,win)
end


function wm.Deactivate(win)
    local k,v
    for k,v in pairs(wm._ActiveMenu) do
        if win == v then
            wm.DeactivateWindow(win)
            wm.ActiveMenu[k]=nil
            return
        end
    end
end

function wm.ClearActive()
    local k,v
    for k,v in pairs(wm._ActiveMenu) do
        wm.Deactivate(v)
    end
    wm.ActiveMenu={}
    collectgarbage();
end


function wm.ActivateMenu(menuname)
    local menu=wm.GetMenu(menuname)

-----   wm.ClearActive();
    local env=menu:GetEnvironment()

    LOG("activatemenu %s", menuname)


    if env.Init then
        env.Init()
    end

    --windows to be activated
    local win=menu:GetEnvironment().ActiveWindows

    if not win then LOG("no activated windows") return end

    local k,v
    for k,v in pairs(win) do
        wm.Activate(v)
    end

    wm.EnterMenu(menuname);


end

function wm.DeactivateMenu(menuname)
    local menu=wm.GetMenu(menuname)

    local win=menu:GetEnvironment().ActiveWindows

    local k,v
    for k,v in pairs(win) do
        wm.Deactivate(v)    
    end
end



-----------menu generation


function wm._ParseWindow(menu,parent,window)

    local w


    local constructor=window.Type


    if not constructor then
        LOG("window %s doesn't have type", window.Name or "unnamed")
        return nil
    end

    window.Type=nil
        
    --inherit parameters from parent
    if parent then

        if not window.Font then
            window.Font=parent.Font
        end

        window.Parent=parent
    end

    local k,v

    ---get defined actions
    local actions = {
        onAction = 0,
        onShow = 0,
        onHide = 0
        onInit = 0
    }
    for k,v in pairs(actions) do
        if window[k] then
            actions[k]=window[k] 
            window[k] = nil
        end
    end


    local childs
    if window.Childs then
        childs=window.Childs
        window.Childs = nil
    end

    w=constructor(window)

    --set actions back
    for k,v in pairs(actions) do
        if type(v) == "function" then
            w[k]=v
        end
    end


    if not childs then return w end

    for k,v in pairs(childs) do
        wm._ParseWindow(menu, w, v)
    end

    return w
end



function wm.GenerateMenu(menuname, template)

    LOG("GenerateMenu: Creating menu %s...",menuname)

    local menu=Sandbox.GetSandbox(menuname)
    menu:GetEnvironment().ActiveWindows={}

    local parent
    local itemname, item

    for itemname,item in pairs(template) do
        if type(item) == "table" then
            LOG("item %s",itemname)
            menu:GetEnvironment().ActiveWindows[itemname]=wm._ParseWindow(menu,parent,item)
        end
    end

    LOG("GenerateMenu: Menu created.")
    collectgarbage()
end


-- The listbox params for CreateSingleColumns

/* There's more but that's a lot of typing. */



/////////////////////////////////////////////////
// Direct X

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

    // Concatenate by shifting over an extra bit and or-ing.
    return iVar << 9 | iVar > -1;
}

/////////////////////////////////////////////////
// Creating Windows

// CreateD3DWindow
//
//
HWND CreateD3DWindow(HWND parent, HINSTANCE hInstance, LPCSTR title, HICON icon, HCURSOR cursor, astruct_110* param_6, int param_7, BYTE param_8, unsigned int param_9, int * in_EAX)
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
            nWidth = param_6->field0_0x4;
            nHeight = param_6->field1_0x8;
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
            nHeight = iVar2 + param_6->field1_0x8 + 1 + (posX + posY + iVar1);
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
        unsigned int uStack_98 = param_9 & 0x20;
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
            if (uStack_98 == 0)
            {

            }
        }

    }
}

int HandleDialogBox(HWND hwnd, WPARAM wparam, short param_3, HWND param_4)
{
    HWND hDlg = hwnd;
    LRESULT LVar6;
    LRESULT* iVar10, * iVar11;
    if (wparam != WM_INITDIALOG)
    {
        if (wparam == WM_NOTIFY)
        {
            if (param_4[1].unused == 0x43d)
            {
                if (param_4[2].unused == -0x10)
                {
                    // There were two options for it: WM_PSD_PAGESETUPDLG, and WM_USER. I chose the former.
                    UINT_006d6900 = SendDlgItemMessageA(hwnd, 0x43d, WM_PSD_PAGESETUPDLG, 0, 0);
                    UINT_008db344[UINT_008da548 + 0x14] = UINT_006d6900;
                }
                return 1;
            }
        }
        else if (wparam == WM_COMMAND)
        {
            if (param_3 == 1)
            {
                LVar6 = SendDlgItemMessageA(hwnd, 0x3eb, BM_GETCHECK, 0, 0);
                UINT_006d6908 = (unsigned int)(LVar6 == 1);
                LVar6 = SendDlgItemMessageA(hwnd, 0x462, BM_GETCHECK, 0, 0);
                UINT_006d690c = (unsigned int)(LVar6 == 1);
                LVar6 = SendDlgItemMessageA(hwnd, 0x44e, BM_GETCHECK, 0, 0);
                UINT_006d68d0 = (unsigned int)(LVar6 == 1);
                iVar11 = &UINT_008db344[UINT_008da548];
                iVar10 = &UINT_008db344[UINT_008da548];
                UINT_006d68d8 = iVar11[0x38];
                DAT_006d68dc = iVar11[0x3c];
                DAT_006d68e0 = iVar11[0x40];
                DAT_006d68e0 = iVar11[0x44];
                UINT_006d68e8 = *(unsigned int*)(iVar10[4] + 4);
                DAT_006d68ec = *(unsigned int*)(iVar10[4] + 8);
                UINT_006d68f0 = *(unsigned int*)(iVar10[4] + 0xC);
                EndDialog(hwnd, 1);
                return 1;
            }
            if (param_3 == 2)
            {
                EndDialog(hwnd, 2);
                return 1;
            }
            if (param_3 == 0x3fc)
            {
                HINSTANCE pHVar7 = ShellExecuteA(hwnd, lpOperation_0066ab90, "http://www.flatoutgame.com/", NULL, NULL, TRUE);
                if ((INT_PTR)pHVar7 < 0x21)
                {
                    ShellExecuteA(hwnd, lpOperation_0066ab90, "iexplorer.exe", "http://www.flatoutgame.com/", NULL, TRUE);
                }
                return 1;
            }
            if (param_3 >> 0x10 == 9)
            {
                LRESULT WVar4 = SendMessageA(param_4, 0x147, 0, 0);
                LRESULT DVar8 = SendMessageA(param_4, 0x150, WVar4, 0);
                if (WVar4 != 0xffffffff)
                {
                    switch (param_3 & 0xffff)
                    {
                    case 1000:
                        if (DVar8 != UINT_008da548)
                        {
                            UINT_008da548 = DVar8;
                            FUN_0044fbd0();
                            return 1;
                        }
                        break;
                    case 0x3e9:
                        iVar10 = UINT_008da548 * 0x24;
                        piVar1 = (int*)(iVar10 + UINT_008db344);
                        *(DWORD*)(iVar10 + 8 + UINT_008db344) = DVar8;
                    }
                }
            }
        }
    }
}

// Creating setup window
//
int CreateSetupWindow(astruct_140 *param_1, HINSTANCE hInst, int showSetup, int setupFlag)
{
    param_1->hinst_0x58 = hInst;

    unsigned int uVar7;
    unsigned int uVar13;
    HCURSOR cursor;
    int iVar = FUN_0044f340();
    if (iVar == 0)
    {
        showSetup = 1;
    }
    if (setupFlag != 0)
    {
        showSetup = 1;
    }
    HICON_008da544 = LoadIconA(hInst, (LPCSTR)0x66);
    uVar7 = UINT_008da540;
    if (iVar == 0)
        FUN_00450aa0();

    iVar = *(unsigned int*)(uVar7 + 4);
    uVar13 = UINT_006d6900;
    do
    {
        UINT_006d6900 = uVar13;
        if (iVar == uVar7)
        {
            iVar17 = FUN_004f580();
            if (iVar17 == 0)
            {
                FUN_00450aa0();
                showSetup = 1;
            }
            FUN_00452f80(UINT_006d6914);
            if (showSetup != 0)
            {
                HGDIOBJ_006d67b8 = LoadImageA(hInst, (LPCSTR)0x82, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
                IVar10 = DialogBoxParamA(hInst, (LPCSTR)0x65, NULL, HandleDialogBox, 0);
                DeleteObject(HGDIOBJ_006d67b8);
                if (IVar10 == 0)
                    return 0;

                if (IVar10 != 1)
                    return 2;

                FUN_0044f520();
                if (setupFlag != 0)
                {
                    return 1;
                }
            }
            FUN_00452f80(UINT_006d6814);
            DAT_0069c138 = UINT_006d6914;
            cursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
            bVar19 = UINT_006d6908 != 0;
            param_1->field1_0x44 = 1;
            iVar = bVar19 | 0x10;
            if ((*(byte*)(iVar17 + 0x18) & 8) != 0)
            {
                iVar = bVar19 | 0x18;
                param_1->field0_0x40 = 1;
            }
            HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar);
            if (HWND_008da56c == NULL)
            {
                // What
                **(*(int*)UINT_008da560 + 0x1c)();
                UINT_006d6908 = 0;
                HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar & 0xfffffffe);
                if (HWND_008da56c == NULL)
                {
                    MessageBoxA(NULL, "Cannot open display mode", "FlatOut 2 error", MB_ICONINFORMATION);
                    return 0;
                }
            }
            // I have no idea what's going on here.
            hInst = (HINSTANCE)0x40800000;
            showSetup = 0x40400000;
            switch (UINT_006d68f8)
            {
            case 0:
                hInst = (HINSTANCE)0x40800000;
                showSetup = 0x40400000;
                break;
            case 1:
                hInst = (HINSTANCE)0x41800000;
                showSetup = 0x41200000;
                break;
            case 2:
                hInst = (HINSTANCE)0x41800000;
                showSetup = 0x41100000;
                break;
            case 3:
                hInst = (HINSTANCE)0x40a00000;
                showSetup = 0x40800000;
                break;
            }
        }
    }

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
// By the end, in_string and out_string will point at the character after the NULL

// If mode is not 0:
//
// Starts at the location after the first NULL in the out_string
// If mode is 3, or g_slashOverride is 0, it'll convert slashes to backslashes
// By the end, in_string will point at the character after the ending NULL
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
        // Steps through the data until it reaches a NULL, storing the next address as it goes.
        do
        {
            currentChar = *tempPtr;
            tempPtr = tempPtr + 1;
        } while (currentChar != NULL);
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
                    if (isupper(currentChar))
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
                if (currentChar == '/')
                {
                    currentChar = '\\';
                }
            else if (currentChar == '\\')
                currentChar = '/';

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

// Copies 256 characters from the in_string to the out_string, setting the
// 256th to NULL, and the 1072nd to param_2
void __cdecl CopyStringToString(char* out_string, char param_2, char* in_string)
{
    char* _Dest = out_string;
    strncpy(_Dest, in_string, 0x100);
    _Dest[0xff] = NULL;
    _Dest[0x430] = param_2;
    return;
}

/////////////////////////////////////////////////
// I know what they do, but I don't know why.

void ClearAStruct42(astruct_42* in_struct)
{
    in_struct->func_0x0 = &PTR_FUN_0067af94;
    in_struct->field6_0xe4 = 0xf;
    in_struct->field5_0xe0 = 0;
    in_struct->field4_0xd0 = 0;
    in_struct->field1_0x4 = 0;
    in_struct->field3_0x10 = 0;
    in_struct->field2_0x8 = 0;
    // The last three indexes of the dwbuffer2 are important.
    in_struct->dwbuffer2_0x40[34] = 0;
    in_struct->dwbuffer2_0x40[32] = 0;
    in_struct->dwbuffer2_0x40[33] = 0;
    in_struct->dw1_0xc = 0;

    // It appears to be 2 objects that each have 3 objects, and an ending parameter.
    in_struct->dwbuffer2_0x40[0] = 0x3F800000;

    in_struct->dwbuffer2_0x40[1] = 0;
    in_struct->dwbuffer2_0x40[2] = 0;
    in_struct->dwbuffer2_0x40[3] = 0;
    in_struct->dwbuffer2_0x40[4] = 0;

    in_struct->dwbuffer2_0x40[5] = 0x3F800000;

    in_struct->dwbuffer2_0x40[6] = 0;
    in_struct->dwbuffer2_0x40[7] = 0;
    in_struct->dwbuffer2_0x40[8] = 0;
    in_struct->dwbuffer2_0x40[9] = 0;

    in_struct->dwbuffer2_0x40[10] = 0x3F800000;

    in_struct->dwbuffer2_0x40[11] = 0;
    in_struct->dwbuffer2_0x40[12] = 0;
    in_struct->dwbuffer2_0x40[13] = 0;
    in_struct->dwbuffer2_0x40[14] = 0;

    in_struct->dwbuffer2_0x40[15] = 0x3F800000;
    in_struct->dwbuffer2_0x40[16] = 0x3F800000;

    in_struct->dwbuffer2_0x40[17] = 0;
    in_struct->dwbuffer2_0x40[18] = 0;
    in_struct->dwbuffer2_0x40[19] = 0;
    in_struct->dwbuffer2_0x40[20] = 0;

    in_struct->dwbuffer2_0x40[21] = 0x3F800000;

    in_struct->dwbuffer2_0x40[22] = 0;
    in_struct->dwbuffer2_0x40[23] = 0;
    in_struct->dwbuffer2_0x40[24] = 0;
    in_struct->dwbuffer2_0x40[25] = 0;

    in_struct->dwbuffer2_0x40[26] = 0x3F800000;

    in_struct->dwbuffer2_0x40[27] = 0;
    in_struct->dwbuffer2_0x40[28] = 0;
    in_struct->dwbuffer2_0x40[29] = 0;
    in_struct->dwbuffer2_0x40[30] = 0;

    in_struct->dwbuffer2_0x40[31] = 0x3F800000;
}


/////////////////////////////////////////////////
// File System

void LoadBinaryDatabase(unsigned char *in_EAX)
{
    int* piVar1;
    int* piVar5;
    int iVar3;
    char cVar2;
    unsigned char local_28;
    int iStack_34;
    int iStack_30;
    unsigned int local_8;
    undefined4* paVar4;
    void* puVar4;
    UINT_008da700 = 0;
    free(MemoryPointer);
    MemoryPointer = NULL;
    memAllocationSize = 0;
    cVar2 = FUN_0054c610('\0', in_EAX);
    if (cVar2 != '\0')
    {
        FUN_0054c3b0(in_EAX, 9);
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
            UINT_008da700 = (unsigned int)piVar5;
            UINT_008da728 = (unsigned int)piVar5;
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

void OpenBFS(LPCSTR filename, HANDLE* unaff_EDI)
{
    LPCSTR pCVar5 = filename;
    DWORD fileFlags;
    HANDLE bfsFile;
    HANDLE pvVar3;
    AutoClass24* pAVar4;
    int aiStack_10[2];
    int iVar2;
    int iVar9;
    int* piVar8;
    int* piVar10;
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
    bfsFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, fileFlags, NULL);
    // Copies the file to unaff_EDI because it's about to be overwritten.
    *unaff_EDI = bfsFile;
    if (bfsFile== NULL)
    {
        if (FUNC_008da6f4 != NULL)
        {
            FUNC_008da6f4();
        }
        CreateErrorMessageAndDie("Failed to open BFS archive: %s");
    }
    // Converts it's size into a handle ?
    bfsFile = (HANDLE)GetFileSize(bfsFile, NULL);
    if (bfsFile == (HANDLE)0xffffffff)
        CreateErrorMessageAndDie("Could not query file size for BFS archive: %s");

    pAVar4 = AC24_008da72c;
    unaff_EDI[1] = bfsFile;
    FUN_0059b60(pAVar4, unaff_EDI, aiStack_10, 0, 0x10);
    // The file must start with the characters "bfsl"
    if (aiStack_10[0] != 0x31736662)
        CreateErrorMessageAndDie("BFS archive <%s> has invalid id");

    unaff_EDI[0x84] = bfsFile;
    _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
    unaff_EDI[0x85] = pvStack_4;
    puVar7 = malloc(_Size);
    pAVar4 = AC24_008da72c;
    unaff_EDI[0x82] = puVar7;
    FUN_00559b60(pAVar4, unaff_EDI, puVar7, unaff_EDI[0x88], _Size);
    pvVar6 = unaff_EDI[0x82];
    if ((int)uStack_8 < 0)
        FUN_005610f0((int)&DAT_0069bd10, _Size - 0x10 >> 2);

    if (*(int *) ((int) bfsFile + 0x10) != 0x3E5)
        CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

    unaff_EDI[0x86] = (HANDLE)((int)bfsFile + 0x14);
    piVar10 = (int*)((int)bfsFile + 0x1F3C);
    piVar8 = (int*)malloc(0x14);
    if (piVar8 == NULL)
        piVar8 = NULL;
    else
    {
        iVar9 = *(int*)((int)bfsFile + 8000);
        *piVar8 = *piVar10;
        iVar2 = *(int*)((int)bfsFile + 0x1F44);
        piVar8[1] = iVar9 + (int)piVar10;
        iVar9 = *(int*)((int)bfsFile + 0x1F48);
        piVar8[2] = iVar2 + (int)piVar10;
        iVar2 = *(int*)((int)bfsFile - 0x1F4C);
        piVar8[3] = iVar9 + (int)piVar10;
        piVar8[4] = iVar2 + (int)piVar10;
    }
    pvVar3 = unaff_EDI[0x88];
    unaff_EDI[0x87] = piVar7;
    bfsFile = (HANDLE)((int)piVar9 + *piVar7);
    unaff_EDI[0x83] = bfsFile;
    if (pvVar3 != NULL)
    {
        for (HANDLE pvVar10 = unaff_EDI[0x85]; pvVar10 != NULL; pvVar10 = (HANDLE)((int)pvVar10 + -1))
        {
            *(int*)((int)bfsFile + 4) = *(int*)((int)bfsFile + 4) + (int)pvVar3;
            if ((*(char*)((int)bfsFile + 1) != NULL) && (*(char*)((int)bfsFile + 1) != NULL))
            {
                int iVar8 = 0;
                do
                {
                    piVar7 = (int*)((int)bfsFile + iVar8 * 4 + 0x18);
                    *piVar7 = *piVar7 + (int)pvVar3;
                    iVar8 += 1;
                } while (iVar8 < (int)(unsigned int)*(byte *)((int)bfsFile + 1));
            }
            bfsFile = (HANDLE)((int)bfsFile + (unsigned int) * (byte*)((int)bfsFile + 1) * 4 + 0x18);
        }
    }
    return;
}

// astruct_142
struct YetAnotherFile {
    // 4 undefined bytes at offset 0x0
    struct ArrayMaybe* rray;
    undefined4 field8_0x8;
    // 8 undefined bytes at offset 0xC
    undefined4 field14_0x14;
    // 8 undefined bytes at offset 0x18
    int field23_0x20;
    int pointerIndex;
    // 8 undefined bytes at offset 0x28
    DWORD field30_0x30;
    // 8 undefined bytes at offset 0x34
    size_t field42_0x3c;
};

int __cdecl OpenFile(char** param_1, YetAnotherFile* param_2)
{
    char* pcVar1;
    char** ppcVar2;
    FILE* pFVar4;
    void* puVar3;
    pcVar1 = *param_1;
    ppcVar2 = (char **)GetItem(param_2->rray, param_2->pointerIndex);
    if (((unsigned int)ppcVar2[6] & 4) == 0)
    {
        if (((unsigned int)ppcVar2[6] & 2) == 0)
        {
            if (ppcVar2[5] == NULL)
            {
                pFVar4 = fopen(*ppcVar2, "rb");
                ppcVar2[5] = (char *)pFVar4;
                if (pFVar4 == NULL)
                {
                    puVar3 = malloc(0x14);
                    if (puVar3 != NULL)
                    {
                        *puVar3 = NULL;
                        puVar3[1] = NULL;
                        puVar3[2] = NULL;
                        puVar3[3] = NULL;
                        puVar3[4] = NULL;
                        *puVar3 = param_2->field14_0x14;
                        puVar3[2] = param_2->pointerIndex;
                        puVar3[1] = 0x80F;
                        puVar3[3] = 0x900;
                        FUN_005f4fd0(param_1, pcVar1 + 0x1d4, pcVar1 + 0x1d8);
                    }
                }
            }
        }
    }
}

bool WriteCharToStream(char in_char, FILE* file)
{
    int result = fputc(in_char, file);
    return result != -1;
}

// Still confused about this one

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
    if (verCheck == 0 && DialogBoxParamA(hInstance, (LPCSTR)0x83, NULL, g_dlgproc, (0) == (INT_PTR)1)
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

    // Allocating 8.2KB
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

void* DoNotCallEver(void *in_mem, int bFree)
{
    in_mem = &PTR_LAB_0067b1c0;
    CreateErrorMessageAndDie("Must not be called - ever.");
    in_mem = &PTR_LAB_0067ad08;
    if (bFree)
        free(in_mem);

    return in_mem;
}

void DoNothing()
{
    return;
}

// Here's the thing: nearly every time this function is called,
// It's given the DoNothing() function.
// Is it some kind of delay?
void RepeatFunction(void (*func)(), int nTimes_EAX)
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
    LPOSVERSIONINFOA osInfo;
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


char __fastcall FUN_0054c610(char param_1, unsigned char* in_EAX)
{
    int* local_154;
    unsigned char* local_104;
    AutoClass24 local_1;
    if (param_1 > -1 && AC24_008da72c != NULL)
    {
        AC24_008da72c->FUN_00559b00(in_EAX, local_154);
        return;
    }
    SlashConvertString(local_104, 0, in_EAX);
}

unsigned int* FUN_005c07b0(astruct_114* param_1, char* string, unsigned int length)
{
    unsigned int* puVar1;
    unsigned int local_8;
    unsigned int local_c = length;
    unsigned int uVar2 = (length >> 5) + 1;
    for (local_8 = length; uVar2 <= local_8; local_8 -= uVar2)
        local_c = local_c * 0x20 + (local_c >> 2) + (unsigned int)(byte)string[local_8 - 1] ^ local_c;

    unsigned int* local_14 = *(unsigned int**)(*(int*)param_1[4] + (*(int*)(param_1[4] + 8) - 1U & local_c) * 4);
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
            char* pcVar3 = string;
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
                // So if 
                if ((*(byte*)(local_14 + 5) & (*(byte*)(param_1[4] + 0x14) ^ 3) & 3) == 0)
                {
                    return local_14;
                }
                *(byte*)(local_14 + 5) = *(byte*)(local_14 + 5) ^ 3;
                return local_14;
            }
        }
        // Setting the pointer to the memory address equal to it's value?
        local_14 = (unsigned int*)*local_14;
    } while (true);
}

astruct_42* FUN_0058e640(void* in_struct, byte param_1)
{
    astruct_13* pAVar1;
    int iVar2;
    unsigned int* puVar3;
    unsigned int* puVar4;
    int* out_pointer;
    if ((param_1 & 2) == 0)
    {
        FUN_0054cfc0((astruct_42*)in_struct);
        if ((param_1 & 1) != 0)
        {
            free(in_struct);
        }
        return in_struct;
    }
    iVar2 = *(int*)((int)in_struct + -0x10);
    out_pointer = (int*)(iVar2 * 0xf0 + (int)in_struct);
    if (iVar2 + -1 > -1)
    {
        puVar3 = (unsigned int*)(out_pointer + 0x39);
        do {
            out_pointer = out_pointer + -0x3C;
            puVar4 = puVar3 + -0x3C;
            *out_pointer = (int)&PTR_FUN_0067af94;
            if (*puVar4 > 0xf)
            {
                paVar1 = FUN_0054c710();
                FUN_00557650((astruct_12*)puVar3[-0x41], paVar1);
            }
            *puVar4 = 0xf;
            puVar3[-0x3D] = 0;
            *(unsigned int*)(puVar3 + -0x41) = 0;
            FUN_0054cc80(out_pointer);
            iVar2 += -1;
            puVar3 = puVar4;
        } while (iVar2 != 0);
    }
    if ((param_1 & 1) != 0)
        free((astruct_42*)((int)in_struct + -0x10));
    return (astruct_42*)((int)in_struct + -0x10);
}

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



void FUN_0052a170(float* param_1, float* in_EAX)
{
    float fVar1 = *param_1;
    in_EAX[0xf] = 1.0;
    fVar1 = fVar1 + fVar1;
    float fVar11 = param_1[1] + param_1[1];
    float fVar12 = param_1[2] + param_1[2];
    float fVar10 = fVar1 * param_1[3];

}

// Functions that sweep through strings

void FUN_005b4e70(astruct_114* param_1, int param_2, char* param_3)
{
    int* piVar2 = FUN_005b3d70(param_1, param_2);
    char* local_18 = param_3;
    char cVar1;
    do
    {
        cVar1 = *local_18;
        local_18 = local_18 + 1;
    } while (cVar1 != NULL);
    unsigned int* local_c = FUN_005c07b0(param_1, param_3, local_18 - (param_3 + 1));
    FUN_005bc570(param_1, piVar2, (float*)&local_c, (int*)(param_1[2] + -8));
    param_1[2] = param_1[2] - 8;
    return;
}

void __cdecl FUN_005b4790(undefined4* param_1, char* in_string)
{
    char currentChar;
    unsigned int local_14;
    unsigned char local_d;
    unsigned int local_c;
    char* tempPtr;
    if (in_string == NULL)
    {
        // To be solved later
        //FUN_005b4670();
    }
    else
    {
        tempPtr = in_string;
        // Sweeps through until the last character, saving it in currentChar
        do {
            currentChar = *tempPtr;
            tempPtr += 1;
        } while (currentChar != NULL);
        // Puts in param_1, the string, and the length of the string.
        FUN_006b4720(param_1, in_string, tempPtr - ((int)in_string + 1));
    }
    return;
}

void _cdecl FUN_0054ad0(astruct_114* param_1, int param_2, char* param_3)
{
    char cVar1;
    int* piVar2 = FUN_005b3d70(param_1, param_2);
    char* tempPtr = param_3;
    do
    {
        cVar1 = *tempPtr;
        tempPtr = tempPtr + 1;
    } while (cVar1 != NULL);

    unsigned int local_c FUN_005c07b0(param_1, param_3, (int)(local_18 - (param_3 + 1)));
    FUN_005bc300(param_1, piVar2, &local_c, param_1->field8_0x8);
    param_1->field8_0x8 = param_1->field8_0x8 + 2;
    return;
}

void SetABunchOfData(int in_EAX)
{
    if (in_EAX == 0)
    {
        DAT_0069ba78 = 0x3F800000;
        DAT_0069ba7c = 0x3F800000;
        DAT_0069ba80 = 0;
        DAT_0069ba84 = 0;
        DAT_0069ba88 = 0x437F0000;
        DAT_0069ba8c = 0x437F0000;
    }
    else
    {
        if (in_EAX != 1)
        {
            DAT_0069ba70 = 0x44800000;
            DAT_0069ba74 = 0x43800000;
            DAT_0069ba78 = 0x43340000;
            DAT_0069ba7c = 0x42C80000;
            DAT_0069ba80 = 0x42F00000;
            DAT_0069ba84 = 0x42700000;
            DAT_0069ba88 = 0x40880000;
            DAT_0069ba8c = 0x40CC0000;
            return;
        }
        DAT_0069ba78 = 0x42AA0000;
        DAT_0069ba7c = 0x42700000;
        DAT_0069ba84 = 0x41F00000;
        DAT_0069ba88 = 0x40CC0000;
        DAT_0069ba8c = 0x41080000;
    }
    DAT_0069ba70 = 0x43C80000;
    DAT_0069ba74 = 0x43480000;
    return;
}



void FUN_0054c540()
{
    astruct_94* unaff_ESI;
    int* piVar1 = unaff_ESI->field23_0x20;
}