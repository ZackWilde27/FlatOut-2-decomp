// FlatOut 2 Decompilation

// So here's what I've learned using Cheat Engine:
//
// 0x37CB2A4 and 0x37CB325 are 4-byte integers, counting up during the game, like a timer or something.
// I've found that these values are set rather than incremented, because I can't override the value.
//
// Things that I have tried overriding and nothing happened:
// 
// 0x6D6AE0 through 0x6D6BE8 is related to the currently selected car when choosing one
//
// When choosing a car, 0x6D69D8 through 0x6D6A0B flip between two different states based on the car.
//
// The name of the currently playing song is printed at 0x6D6D50.
// 



// Bugbear used Visual Studio 2003, which means we know the IDE, compiler, all that. But finding a copy these days is difficult.

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

#include <dinput.h>


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
#include <synchapi.h>
#include <winbase.h>
#include <winsock.h>
#include <winsock2.h>
#include <sys/stat.h>

/////////////////////////////////////////////////
// Variables
// They have been sorted by address location, grouped by relevance when possible.

struct Settings Settings;

DLGPROC g_dlgproc;

LPCSTR lpOperation_0066ab90;

const char* u_NO_TEXT_0066b38c = "u\"NO_TEXT\"";

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// Leads me to believe it means ROMU v0.28
const char* verString_00698b4c = "Version_0.28_build_2004.09.20";

// These are treated like an array, AutoClass31s have an index into these DATs
unsigned int DAT_0069ba70;
unsigned int DAT_0069ba74;
unsigned int DAT_0069ba78;
unsigned int DAT_0069ba7c;
unsigned int DAT_0069ba80;
unsigned int DAT_0069ba84;
unsigned int DAT_0069ba88;
unsigned int DAT_0069ba8c;

unsigned int UINT_0069c2d0;

const char** PTR_u_NO_TEXT_0069df4 = &u_NO_TEXT_0066b38c;

DWORD TimePassed_006a32e8;

HGDIOBJ HGDIOBJ_006d67b8;
LRESULT DAT_006d68dc;
LRESULT DAT_006d68e0;
LRESULT DAT_006d68ec;
LRESULT UINT_006d6900;
unsigned int UINT_006d6908;

unsigned int UINT_006d690c;
unsigned int UINT_006d68d0;
unsigned int UINT_006d68d8;
unsigned int UINT_006d68e8;
unsigned int UINT_006d68f0;

void* PTR_LAB_007a9e4[5];

unsigned short FPUConW_008d781c;

unsigned int UINT_008d780c;
unsigned int UINT_008d7bb0;


unsigned int UINT_008da270;
HINSTANCE HINST_008da2dc;



unsigned int UINT_008da540;
HICON HICON_008da544;
unsigned int UINT_008da548;

void* MEM_008da568;

unsigned int UINT_008da728;

// 1 = delete bfs file on opening, 0 = normal
unsigned int UINT_008da730;

IDirect3D9* D3D9_008da784;
HWND HWND_008da79c;

unsigned int UINT_008d7c30;

HWND HWND_008da56c;

// It's an int, but used as a bool.
int setupFlag_008da684 = 0;

unsigned int unkn_008da6a0;

// The handle of the .exe file
HINSTANCE HINST_008da564;

void (*FUNC_008da6f4)();

unsigned int UINT_008da6fc;

unsigned int UINT_008da700;
AutoClass24* AC24_008da72c;
unsigned int UINT_008da730;

LRESULT UINT_008db344[30];

unsigned int UINT_008e5770;

unsigned int UINT_008e5d70;

int* int_008e8420;

unsigned int UINT_008e855c;

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

struct astruct_97 {
    // 8 undefined bytes at offset 0x0
    unsigned int** field_0x8[2];
    int* field_0x10;
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
    // 100 undefined bytes at offset 0x0
    unsigned int int_0x64;
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

// placeholder
struct undefined4 {
    float nothing;
};

// Settings Structures
// Got this info from the cfg files

struct Version {
    unsigned int Settings = 15; // 0 - 1,000,000
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
    unsigned int Port = 23756;                     // 0 - 65536
    unsigned int BroadcastPort = 23757;            // 0 - 65536
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
    unsigned int fileattributes;         // 0x4018 - bitmask related to the parameters the file was opened with
    char* filename1; // 0x401C
    char* filename2; // 0x4020
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

                WriteFile(hFile, buffer_temp, tempToWrite, bytesWritten, NULL);
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

    // Updates the file pointer to the new value if it isn't already there.
    void FileObject_SetFilePointer(int newLoc)
    {
        if (this->realFilePos != (char*)newLoc)
        {
            this->realFilePos = (char*)newLoc;
            SetFilePointer(this->handle, newLoc, NULL, FILE_BEGIN);
        }
        return;
    }

    // FileObject_New() is a more complicated version of FileObject_Create()
    FileObject* FileObject_New(unsigned int unaff_EBX, const char* filename_unaff_EDI)
    {
        FileObject* pAVar3 = NULL;
        if ((unaff_EBX & 1) == 0)
        {
            FileObject* piVar2 = (FileObject*)malloc(0x4024);
            if (piVar2 != NULL)
            {
                piVar2->filePos = NULL;
                piVar2->realFilePos = NULL;
                piVar2->handle = NULL;
                piVar2->filename1 = NULL;
                piVar2->fileattributes = NULL;
                piVar2->vtable = &JMPTABLE_0067b6f8;
                piVar2->alwaysNeg1 = -1;
                pAVar3 = piVar2;
            }
            pAVar3->FileObject_Create();
        }
        else
        {
            struct stat result;
            if (stat(filename_unaff_EDI, &result) == 0)
            {
                FileObject* pAVar2 = (FileObject*)malloc(0x4024);
                if (pAVar2 != NULL)
                {
                    pAVar2->FileObject_Clear();
                    pAVar3 = pAVar2;
                }
                pAVar3->FileObject_Create();
                pAVar3->size = pvStack_18;
                return pAVar3;
            }
        }
        return pAVar3;
    }

    void FileObject_Create(LPCSTR lpFilename, unsigned int flags)
    {
        DWORD desiredAccess = 0;
        DWORD creationDisposition = 0;
        bool bVar2 = (flags & 1) != 0;
        if (bVar2)
        {
            desiredAccess = GENERIC_READ;
            creationDisposition = OPEN_EXISTING;
        }
        DWORD shareMode = bVar2;
        DWORD flagsAndAttributes = bVar2;
        if ((flags & 2) != 0)
        {
            desiredAccess |= GENERIC_WRITE;
            creationDisposition |= CREATE_ALWAYS;
            flagsAndAttributes |= FILE_ATTRIBUTE_NORMAL;
            shareMode = FILE_SHARE_READ;
        }
        HANDLE handle = CreateFileA(lpFilename, desiredAccess, shareMode, NULL, creationDisposition, flagsAndAttributes, NULL);
        this->fileattributes = flags;
        this->handle = handle;
        if ((handle == NULL) && (FUNC_008da6f4 != NULL))
        {
            FUNC_008da6f4();
        }
        return;
    }

    void FileObject_FlushBuffers()
    {
        FlushFileBuffers(this->handle);
    }

    char* FileObject_GetFilePosButLikeWhy()
    {
        return this->filePos;
    }

    bool FileObject_IsFilePosValid()
    {
        return (this->filePos > 0) && (this->size <= this->filePos);
    }

    int FileObject_GetSize()
    {
        return (this->size == (void*)0xffffffff) ? (int)this->filePos : (int)this->size;
    }

    void FileObject_Clear()
    {
        this->alwaysNeg1 = -1;
        this->filePos = NULL;
        this->realFilePos = NULL;
        this->handle = NULL;
        this->filename1 = NULL;
        this->filename2 = NULL;
        return;
    }
};

void* PTR_Group_0066e448[7] = { &RecursivePointer, &FUN_00489670,  };

// AutoClass32 ?
void** RecursivePointer(void** addr, byte bFree)
{
    // Sets the address to point at this function.
    addr = &PTR_Group_0066e448[0];
    if (bFree & 1)
    {
        free(addr);
    }
    return addr;
}


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


-- The listbox params for CreateSingleColumnsListBox has the following structure
--[[--/*
local listboxParams={
    ListBoxTemplate={},
    Left=0,
    Top=0,
    LeftPadding=0,
    RightPadding=0,
    TopPadding=0,
    BottomPadding=0,
    RowWidth=100,
    RowHeight=16,
    RowPadding=0,
    RowTemplate={},
    RowTemplateType="Button",
    RowTemplateCust=function(Row, RowNr)
    end,
    NumRows=1,
}
--]]--*/
/* their comment system ended my comment

function CreateSingleColoumnListBox(ListBoxParams)
    local params=ListBoxParams

    local width=params.LeftPadding + params.RowWidth + params.RightPadding
    local height=params.TopPadding
    height=height + params.RowHeight * params.NumRows
    height=height + params.RowPadding * (params.NumRows - 1)
    height=height + params.BottomPadding

    if params.ListBoxTemplate.Parent==nil then
        params.ListBoxTemplate.Position=SAFEPOS(params.Left, params.Top)
    else
        params.ListBoxTemplate.Position=POS(params.Left, params.Top)
    end
        
    params.ListBoxTemplate.Size=SIZE(width, height)

    local listBox=ListBox(params.ListBoxTemplate)

    params.RowTemplate.Parent=listBox

    local y=params.TopPadding
    params.RowTemplate.Size=SIZE(params.RowWidth, params.RowHeight)

    for i=1, params.NumRows do
        params.RowTemplate.Position=POS(params.LeftPadding, y)
        local row=addchild(_G[params.RowTemplateType] (params.RowTemplate))
        params.RowTemplateCust(row, i)
        y=y + params.RowPadding + params.RowHeight
    end

    return listBox
end


-- The listbox params for CreateDoubleColoumnListBox has the following structure
--[[--/*
local listboxParams={
    ListBoxTemplate={},
    Left=0,
    Top=0,
    LeftPadding=0,
    RightPadding=0,
    TopPadding=0,
    BottomPadding=0,
    RowWidth=100,
    RowHeight=16,
    RowPadding=0,
    RowTemplate={},
    RowTemplateType="Button",
    RowTemplateCust=function(Row, RowNr)
    end,
    NumRows=1,
    Coloumns={
        [1]={
        Name="coloumn1", -- _row# is added
        ColoumnTemplate={},
        ColoumnTemplateType="Button"
        ColoumnTemplateCust=function(Coloumn, RowNr, ColoumnNr)
        end
        }
    }
}
    --]]--*/
/*


function CreateMultiColoumnListBox(ListBoxParams)
    local params=ListBoxParams

    local width=params.LeftPadding + params.RowWidth + params.RightPadding
    local height=params.TopPadding
    height=height + params.RowHeight * params.NumRows
    height=height + params.RowPadding * (params.NumRows - 1)
    height=height + params.BottomPadding

    if params.ListBoxTemplate.Parent==nil then
        params.ListBoxTemplate.Position=SAFEPOS(params.Left, params.Top)
    else
        params.ListBoxTemplate.Position=POS(params.Left, params.Top)
    end

    params.ListBoxTemplate.Size=SIZE(width, height)

    local listBox=ListBox(params.ListBoxTemplate)
    
    params.RowTemplate.Parent=listBox

    local y=params.TopPadding
    params.RowTemplate.Size=SIZE(params.RowWidth, params.RowHeight)

    local numColoumns=table.getn(params.Coloumns)
    for i=1, params.NumRows do
        params.RowTemplate.Position=POS(params.LeftPadding, y)
        local row=addchild(_G[params.RowTemplateType] (params.RowTemplate))
        params.RowTemplateCust(row, i)

        for j=1, numColoumns do
            local coloumn=params.Coloumns[j]
            coloumn.ColoumnTemplate.Parent=row
            coloumn.ColoumnTemplate.Name=coloumn.Name..string.format("_row%i", i)
            local coloumncont=addchild(_G[coloumn.ColoumnTemplateType] (coloumn.ColoumnTemplate))
            coloumn.ColoumnTemplateCust(coloumncont, i, j)
        end

        y=y + params.RowPadding + params.RowHeight
    end

    return listBox
end










*/

/* Lua Script Part 3: Fonts

function AddAllFonts()
local k,v
for k,v in pairs(Fonts) do
    if k ~= "DataPath" then
        AddFont(k, v.Texture, v.Data, v.TopPadding or 0)
    end
end
end
SetGlobalFontScale(GlobalFontScale or 1.00)
AddAllFonts()
AddAllFonts=nil

*/


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
    unsigned int result = isOlder ? -1 : 1;

    // Concatenate by shifting over an extra bit and or-ing.
    return result << 9 | result > -1;
}

HMODULE DINPUTMODULE_008da744;
FARPROC PTR_DirectInput8Create_008da784;
void* PTR_008da74c;
REFIID REFIID_006613e4;

unsigned int LoadDInputLibrary()
{
    DINPUTMODULE_008da744 = LoadLibraryA("dinput8.dll");
    PTR_DirectInput8Create_008da784 = GetProcAddress(DINPUTMODULE_008da744, "DirectInput8Create");
    unsigned int punkOuter = NULL;
    void** ppvOut = &PTR_008da74c;
    REFIID riidltf = REFIID_006613e4;
    HINSTANCE hInst = GetModuleHandleA(NULL);
    DWORD dwVersion = DIRECTINPUT_VERSION;
    int returnCode = (*PTR_DirectInput8Create_008da784)(hInst, dwVersion, riidltf, ppvOut, punkOuter);
    return returnCode & ((returnCode > -1) ? 0 : -1);
}

/////////////////////////////////////////////////
// Creating Windows

// CreateD3DWindow
//
//
HWND CreateD3DWindow(HWND parent, HINSTANCE hInstance, LPCSTR title, HICON icon, HCURSOR cursor, astruct_110* param_6, int param_7, BYTE param_8, unsigned int flags, int * in_EAX)
{
    int posX;
    int posY;
    unsigned int style;
    unsigned int* tempPtr = &UINT_008e5770;
    WNDCLASSA newWindow;
    HWND hWnd;
    for (posX = 0x180; posX != 0; posX--)
    {
        *tempPtr = 0;
        tempPtr = tempPtr + 1;
    }
    tempPtr = &UINT_008e5d70;
    for (posX = 0x20; posX != 0; posX--)
    {
        *tempPtr = 0;
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
            style = ((flags & WS_EX_TRANSPARENT != 0) & 0xff310000) + WS_OVERLAPPEDWINDOW;
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
        newWindow.lpfnWndProc = &LAB_what;
        newWindow.cbClsExtra = 0;
        newWindow.cbWndExtra = 0;
        newWindow.hInstance = hInstance;
        newWindow.hIcon = icon;
        newWindow.hCursor = cursor;
        newWindow.hbrBackground = (HBRUSH)GetStockObject(5);
        newWindow.lpszMenuName = NULL;
        newWindow.lpszClassName = "BDX9 Render Window";
        RegisterClassA(&newWindow);
        // In binary: 00?0 0000
        unsigned int flagTest = flags & 0x20;
        if (flagTest == 0)
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
            if (flagTest == 0)
            {

            }
        }

    }
}

LPDIRECT3DDEVICE9 LPDIRECT3DDEVICE9_008da788;
int* PTR_008da718;
HINSTANCE HINSTANCE_008da2dc;
unsigned int UINT_008da798;

// Destroying Windows
void __fastcall DestroyWindow(int param_1)
{
    LPDIRECT3DDEVICE9 device = LPDIRECT3DDEVICE9_008da788;
    bool deviceIsNotNull = LPDIRECT3DDEVICE9_008da788 != NULL;
    if (deviceIsNotNull)
        device->Release();

    if (D3D9_008da784 != NULL)
        D3D9_008da784->Release();

    HWND hWnd = HWND_008da79c;
    CHAR className;
    if (HWND_008da79c != NULL)
    {
        HWND_008da79c = NULL;
        UINT_008da798 = 0;
        GetClassNameA(hWnd, &className, 0x3F);
        DestroyWindow(hWnd);
        UnregisterClassA(&className, HINSTANCE_008da2dc);
        ShowCursor(TRUE);
    }
    LPDIRECT3DDEVICE9_008da788 = NULL;
    D3D9_008da784 = NULL;
    PTR_008da718 = NULL;
    return;
}


///////////////////////////////////////////////////////
// WndProcs

LRESULT DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hDlg = hwnd;
    LRESULT LVar6;
    LRESULT* iVar10, * iVar11;
    if (uMsg != WM_INITDIALOG)
    {
        if (uMsg == WM_NOTIFY)
        {
            if (lParam[1].unused == 0x43d)
            {
                if (lParam[2].unused == -0x10)
                {
                    // There were two options for it: WM_PSD_PAGESETUPDLG, and WM_USER. I chose the former.
                    UINT_006d6900 = SendDlgItemMessageA(hwnd, 0x43d, WM_PSD_PAGESETUPDLG, 0, 0);
                    UINT_008db344[UINT_008da548 + 0x14] = UINT_006d6900;
                }
                return 1;
            }
        }
        else if (uMsg == WM_COMMAND)
        {
            if (param_3 == 1)
            {
                LVar6 = SendDlgItemMessageA(hwnd, 0x3eb, BM_GETCHECK, 0, 0);
                UINT_006d6908 = (unsigned int)(LVar6 == 1);
                LVar6 = SendDlgItemMessageA(hwnd, 0x462, BM_GETCHECK, 0, 0);
                UINT_006d690c = (unsigned int)(LVar6 == 1);
                LVar6 = SendDlgItemMessageA(hwnd, 0x44e, BM_GETCHECK, 0, 0);
                UINT_006d68d0 = (unsigned int)(LVar6 == 1);
                /*
                iVar11 = &UINT_008db344[UINT_008da548];
                iVar10 = &UINT_008db344[UINT_008da548];
                UINT_006d68d8 = iVar11[0x38];
                DAT_006d68dc = iVar11[0x3c];
                DAT_006d68e0 = iVar11[0x40];
                DAT_006d68e0 = iVar11[0x44];
                UINT_006d68e8 = *(unsigned int*)(iVar10[4] + 4);
                DAT_006d68ec = *(unsigned int*)(iVar10[4] + 8);
                UINT_006d68f0 = *(unsigned int*)(iVar10[4] + 0xC);
                */
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
                            //FUN_0044fbd0();
                            return 1;
                        }
                        break;
                    case 0x3e9:
                        iVar10 = (LRESULT *)(UINT_008da548 * 0x24);
                        LRESULT piVar1 = iVar10[(int)UINT_008db344];
                        iVar10[(int)UINT_008db344 + 8] = DVar8;
                    }
                }
            }
        }
    }
}


// Registry

unsigned int MoreRegistryStuff(char* param1, LPBYTE filename, unsigned int param3)
{
    unsigned int output = 0xffffffff;
    bool done = false;
    LSTATUS result;
    HKEY key;
    CharLowerBuffA(param1, strlen(param1));
    LPSTR subKey;
    if (RegOpenKeyA(HKEY_CLASSES_ROOT, "clsid", &key) == ERROR_SUCCESS)
    {
        unsigned int depth = 0;
        do 
        {
            do
            {
                if (done) goto Exit;
                result = RegEnumKeyA(key, depth, subKey, 0x200);
                depth += 1;
                if (result != ERROR_SUCCESS) goto Exit;
                CharLowerBuffA(subKey, strlen(subKey));
            } while (strcmp(subKey, param1) != 0);
            HKEY newKey;
            HKEY newSubKey;
            if (RegOpenKeyExA(key, subKey, 0, KEY_READ, &newKey) == ERROR_SUCCESS)
            {
                if (RegOpenKeyExA(newKey, "InprocServer32", 0, KEY_READ, &newSubKey) == ERROR_SUCCESS)
                {
                    DWORD local_20 = param3;
                    DWORD local_24 = 1;
                    if (RegQueryValueExA(newSubKey, NULL, NULL, &local_24, filename, &local_20) == ERROR_SUCCESS)
                    {
                        OFSTRUCT local_ac;
                        memset(&local_ac, 0, 0x88);
                        local_ac = 0x88;
                        if (OpenFile(filename, &local_ac, OF_EXIST))
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

int* ReadCLSIDKey(HKEY hkey, LPCSTR subKey, int param3, char* param4)
{
    PHKEY result;
    HKEY local_c;
    char* Dst = param4;
    if (param4 == nullptr)
    {
        if (RegOpenKeyExA(hkey, subKey, 0, KEY_READ, result) == ERROR_SUCCESS)
        {
            DWORD keyType = 1;
            LPBYTE data;
            if ((RegQueryValueExA(local_c, "clsid", NULL, &keyType, data, (LPDWORD)&param4) == ERROR_SUCCESS))
            {
                
            }
        }
    }
}

////////////////////////////////////////////////////////
// Network

bool StringAddressToBinaryRepresentation(char* stringAddress, unsigned long* out_addr)
{
    unsigned char local_14, local_10, local_c, local_8;
    int occurences = sscanf(stringAddress, "%d.%d.%d.%d", &local_14, &local_10, &local_c, &local_8);
    if (occurences < 4)
        return false;

    unsigned long binary = inet_addr(stringAddress);
    *out_addr = binary;
    return binary != INADDR_NONE;
}

void FUN_0062f54e(char* stringAddress, int param_2, unsigned short extraout_var)
{
    HANDLE local_c;
    bool bVar1 = StringAddressToBinaryRepresentation(stringAddress, (unsigned long*)local_c);
    if (((extraout_var << 1) | bVar1) == 0)
    {
        char* local_40c = (char*)malloc(0x400);
        local_c = WSAAsyncGetHostByName(NULL, 0, stringAddress, local_40c, 0x400);

        unsigned int timePassed;
        unsigned int start = GetMiliseconds();
        unsigned int now;

        // Waiting for response
        while (local_40c == 0)
        {
            now = GetMiliseconds();
            timePassed += now - start;
            if (AsyncMaxWaitTime_00684b18 <= timePassed)
            {
                WSACancelAsyncRequest(local_c);
                return;
            }
            MaybeSleep(10);
            start = now;
        }
    }
}

unsigned int UINT_006d6814;
unsigned int DAT_0069c138;
int* UINT_008da560;

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
        //FUN_00450aa0();

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
                **(*UINT_008da560 + 0x1c)();
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
    } while (false);

}



// 1 = US, 2 = Germany, not 1 or 2 = Europe
// Germany got it's own version,
// Also, my presumably US copy is set to 0, meaning Europe. Changing it after starting the game seems to have no effect.
unsigned int version_0069c13c = 0;

void StartGame(int param_1)
{
    const char* version_string;
    astruct_97* paVar1 = *(astruct_97**)(*int_008e8420 + 4);
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
    //...
}

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

DWORD GetMiliseconds()
{
    return GetSeconds() / 1000;
}

struct astruct_150 {
    // 48 undefined bytes at offset 0x0
    int field_0x30;
    // 4 undefined bytes at offset 0x34
    unsigned int field_0x38;
};

struct astruct_151 {
    // 16 undefined bytes at offset 0x0
    char field_0x10;
    // 53 undefined bytes at offset 0x14
    char field_0x45;
    // 2 undefined bytes at offset 0x46;
    unsigned int field_0x48;
    undefined4* undefined2actually_0x4C;
    void* field_0x50;
    size_t field_0x54;
    // 4 undefined bytes at offset 0x58
    unsigned int field_0x5C;
    unsigned int field_0x60;
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



// Goes along the string until it finds a difference and returns the difference between the characters in integer value.
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
int String_Compare_s(char* string1, char* string2, int maxLength)
{
    char char1, char2;
    int iVar3 = 0;
    do
    {
        char1 = *string1;
        char2 = *string2;
        string1 += 1;
        string2 += 1;
        iVar3 += 1;
        if (char1 == NULL || char1 != char2) break;
    } while (iVar3 < maxLength);
    return char1 - char2;
}

// Honestly not too sure about the why.
// Same as Compare, it sweeps through until it finds a difference and then returns the difference in value between the characters.
char String_CompareEnd(char* out_string, char* in_string, int length)
{
    if (length > 0)
    {
        int difference = in_string - out_string;
        do
        {
            if (*out_string != out_string[difference])
                return *out_string - out_string[difference];

            out_string = out_string += 1;
            length -= 1;
        } while (length > 0);
    }
    return NULL;
}

// They had a GetLength function but quite a lot of functions still chose to do it themselves.
int String_GetLength(char* in_string)
{
    char* tempPtr = in_string;
    while (*tempPtr != NULL)
        tempPtr += 1;

    return tempPtr - in_string;
}

// Simple copy from one string to another.
// Both pointers will end up pointing at the end of the string, so it returns
// the original pointer to the out_string.
char * String_SimpleCopy(char* out_string, char* in_string)
{
    char* original = out_string;
    char current;
    do
    {
        current = *in_string;
        *out_string = current;
        out_string += 1;
        in_string += 1;
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
        if (length == 0)
        {
            return original;
        }
        current = *in_string;
        *out_string = current;
        out_string += 1;
        in_string += 1;
        length -= 1;
    } while (current != NULL);
    return original;
}

// Copies the in_string to the string after the out_string.
// Finds the first NULL in the out_string and starts there.
char* String_CopyTheStringAfterTheString(char* out_string, const char* in_string)
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

// Just like CopyTheStringAfterTheString except with a length, makes sure to add a terminator.
char* String_CopyTheSubstringAfterTheString(char* out_string, char* in_string, int length)
{
    char* original = out_string;
    if (length)
    {
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
            length--;
        } while (length);
        *out_string = NULL;
    }
    return original;
}

// I just checked, it's pretty much exactly how Microsoft wrote tolower() except 'A' - 'a' is precalculated, happens to be the space character.
char Char_ToLowercase(char theChar)
{
    if (theChar > 64 && theChar < 91)
        theChar += ' ';
    return theChar;
}

const char* s_no_value_006541c = "no value";

const char* Types_0065284c[] =
{
    "nil"
    "boolean",
    "userdata",
    "number",
    "string",
    "table",
    "function",
    "userdata",
    "thread",
    "proto",
    "upval"
};

const char* StringTypeFromInt(astruct_114* param_1, int type)
{
    if (type == -1)
        return s_no_value_006541c;
    else
        return Types_0065284c[type];
}


/////////////////////////////////////////////////
// AutoClass 9 / PropertyDb

// AutoClass 9
// I'm pretty sure this is the Lua interpreter.
class AutoClass9 {
public:
    AutoClass9* FUN_00557fe0(char* param_1, char param_2)
    {
        char* pcVar2 = param_1;
        char cVar1;
        // Counts the length of the string to make sure it's more than one character long
        do {
            cVar1 = *pcVar2;
            pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');

        if (pcVar2 == param_1 + 1)
            return this;

        cVar1 = *param_1;
        int iVar4 = 0;
        int iVar5 = 0;
        if (cVar1 != '\0')
        {
            pcVar2 = param_1;
            do {
                if (cVar1 == '.') break;
                iVar5 += 1;
                pcVar2[(int)(acStack_100 + -(int)param_1)] = cVar1;
                cVar1 = pcVar2[1];
                iVar4 += 1;
                pcVar2 = pcVar2 + 1;
            } while (cVar1 != '\0');
        }
        cVar1 = param_1[iVar4];
        acStack_100[iVar5] = NULL;
        if (cVar1 == '.')
            iVar4 += 1;

        AutoClass9* this_00 = FUN_00557e60(this);
        if (this_00 == NULL)
        {
            this_00 = PropertyDb_AccessProperty();
            if (this_00 == NULL)
            {
                if (param_2 == NULL)
                    return NULL;
                this_00 = PropertyDb_RuntimeTables();
            }
        }
        AutoClass9 *pAVar3 = this_00->FUN_00557fe0(param_1 + iVar4, param_2);
        return pAVar3;
    }

    void AddMappedTable(char* param_1, int* param_2, unsigned int param_3)
    {
        AutoClass9* pAVar3 = this->FUN_00557fe0(param_1, NULL);
        int iVar12 = 0;
        int iVar8 = *param_2;
        int* piVar4 = param_2;
        int* piVar1;
        while (iVar8 != 0)
        {
            piVar1 = piVar4 + 3;
            piVar4 = piVar4 + 3;
            iVar12 += 1;
            iVar8 = *piVar1;
        }

        if ((pAVar3 == NULL || ))
    }

};

int PropertyDb_AccessProperty(char* in_EAX)
{
    char* leftBracket = strstr(in_EAX, "[");
    char* rightBracket = strstr(in_EAX, "]");
    char* tempPtr = in_EAX;
    do
    {
        tempPtr = tempPtr + 1;
    } while (*tempPtr != NULL);
    if (leftBracket == NULL || rightBracket == NULL || rightBracket <= leftBracket || (rightBracket + -(int)in_EAX != tempPtr + (-1 - (int)(in_EAX + 1))))
    {
    }
}


/////////////////////////////////////////////////
// File System

void LoadBinaryDatabase(char *flags)
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
    cVar2 = FUN_0054c610('\0', (unsigned char *)flags);
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

void InitOpenBFS(LPCSTR param_1, HANDLE* in_EAX)
{
    // I thought it was allocating space for the file,
    //  but only 548 bytes?
    void* pvVar2 = malloc(0x224);
    void* uVar3;
    if (pvVar2 == NULL)
        uVar3 = NULL;
    else
        OpenBFS(param_1, in_EAX);

    //if (in_EAX[2] == in_EAX[1])
        //FUN_00434840();

    HANDLE puVar1 = in_EAX[1];
    in_EAX[1] = (HANDLE)((int)puVar1 + 4);

    return;

}

void FUN_0054c7a0(void ** unaff_EDI)
{
    void* pvVar2 = *unaff_EDI;
    int iVar3 = (int)unaff_EDI[1] - (int)pvVar2 >> 2;
    int iVar1;
    if (iVar3 < 4)
        iVar1 = 3;
    else
        iVar1 = iVar3 * 3 >> 1;

    if ((int)unaff_EDI[2] - (int)pvVar2 >> 2 < iVar1)
    {
        pvVar2 = realloc(pvVar2, iVar1 * 4);
        unaff_EDI[2] = (void*)(iVar1 * 4 + (int)pvVar2);
        *unaff_EDI = pvVar2;
        unaff_EDI[1] = (void*)((int)pvVar2 + iVar3 * 4);
    }
    return;
}

// ASPI

HMODULE wnaspi_006a32d0;
FARPROC PTR_GetASPI32SupportInfo_006a32d4;
FARPROC PTR_SendASPI32Command_006a32d8;
char CHAR_006a32cc;
unsigned int UINT_006a328c;
int INT_006a32e4;
int INT_007a32e4;


unsigned int ASPI_Initialize(char param_1)
{
    if (CHAR_006a32cc != '\0')
        return 0;

    unsigned int* puVar7 = &UINT_006a328c;
    int errorCode, pvVar5;
    for (int iVar3 = 8; iVar3 != 0; iVar3 -= 1)
    {
        *puVar7 = 0;
        puVar7 += 1;
    }
    INT_007a32e4 = 0;
    if ((param_1 == '\0') )//&& (uVar2 = FUN_00621944(), uVar2 != NULL))
    {
        //PTR_GetASPI32SupportInfo_006a32d4 = FUN_00620525;
        //PTR_SendASPI32Command_006a32d8 = FUN_00621ea4;
    }
    else
    {
        puVar7 = &UINT_006a328c;
        for (int iVar3 = 8; iVar3 != 0; iVar3 -= 1)
        {
            *puVar7 = 0;
            puVar7 += 1;
        }
        char* local_804;
        INT_006a32e4 = 0;
        String_SimpleCopy(&local_804, "wnaspi32.dll");
        wnaspi_006a32d0 = LoadLibraryA(&local_804);
        if (wnaspi_006a32d0 == NULL)
        {
            GetSystemDirectoryA(&local_804, 0x7FF);
            String_CopyTheStringAfterTheString(&local_804, "\\");
            String_CopyTheStringAfterTheString(&local_804, "wnaspi32.dll");
            wnaspi_006a32d0 = LoadLibraryA(&local_804);
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
    //unsigned int uVar4 = 0;
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
    size_t _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
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

bool WriteCharToStream(char in_char, FILE* file)
{
    return fputc(in_char, file) != -1;
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

typedef void (*funcPtr)(int);

funcPtr PTR_008e8418;

/////////////////////////////////////////////////
// Startup Sequence


LRESULT BasicDlgProc(HWND hWnd, int command, short param_3)
{
    if (command == WM_COMMAND)
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

DWORD Startup(HINSTANCE hInstance, unsigned int param_3, char* flags)
{
    HINST_008da564 = hInstance;
    INT_PTR IVar2;

    // The random seed is set to the current time
    DWORD seed = timeGetTime();
    srand(seed);

    // Dealing with the setup flag
    setupFlag_008da684 = 0;
    if (flags != "" && (stricmp(flags, "-setup") || stricmp(flags, "setup")))
        setupFlag_008da684 = 1;

    CoInitializeEx(NULL, 0);

    int verCheck = CheckDirectXVersion((LPBYTE*)"4.09.00.0904");
    if (verCheck == 0 && (IVar2 = DialogBoxParamA(hInstance, (LPCSTR)0x83, NULL, BasicDlgProc, 0), IVar2 == (INT_PTR)1))
        return 0xffffffff;

    // Sets unkn_008da6a0 to 1
    SetFPUCW(FPUConW_008d781c);

    // Unused flags
    strstr(flags, "-binarydb");
    strstr(flags, "-bedit");

    LoadBinaryDatabase(flags);

    UINT_0069c2d0 = (unsigned int)&UINT_008d7bb0;
    // Allocating ~131 KB
    void *newMem = malloc(0x20044);
    if (newMem == NULL)
        UINT_008d780c = 0;
    else
        //UINT_008d780c = FUN_0051c520();

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
        UINT_008e855c -= 1;

    if (PTR_008e8418 != NULL && UINT_008e855c == 0)
    {
        (*PTR_008e8418)(1);
        PTR_008e8418 = NULL;
    }

    //FUN_0051cdc0();
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
    in_mem = &JMPTABLE_0067b1c0;
    CreateErrorMessageAndDie("Must not be called - ever.");
    in_mem = &JMPTABLE_0067ad08;
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