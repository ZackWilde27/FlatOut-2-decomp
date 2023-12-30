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

// Bugbear used Visual Studio 2003 aka Visual Studio 6, which means we know the IDE, compiler, all that. But finding a copy these days is difficult.

// I was forced to replace all string functions with the safe counterpart in order for it to compile.

// Originally I made my own names for globals, but I'm now including the address to make investigating easier.

// I don't think these are included but hey
#include <stdio.h>
#include <stdarg.h>

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

// GDI32.DLL
#include <wingdi.h>

// IPHLPAPI.DLL
#include <iphlpapi.h>

// WINMM.DLL
#include <winsock.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

// Misc.
#include <strsafe.h>
#include <sys/stat.h>
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

// Having to write out 'unsigned' every time is a bit tedious.
#define uint unsigned int
#define ulong unsigned long
#define ushort unsigned short
#define uchar unsigned char
#define ulonglong unsigned long long

#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
#define undefined8 unsigned long

/////////////////////////////////////////////////
// Variables
// They have been sorted by address location, grouped by relevance when possible.

DLGPROC g_dlgproc;

LPCSTR lpOperation_0066ab90;

const char* u_NO_TEXT_0066b38c = "u\"NO_TEXT\"";

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// Leads me to believe it means ROMU v0.28
const char* verString_00698b4c = "Version_0.28_build_2004.09.20";

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

const char** PTR_u_NO_TEXT_0069df4 = &u_NO_TEXT_0066b38c;

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

void* PTR_LAB_007a9e4[5];

unsigned short FPUConW_008d781c;

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

uint UINT_008da700;

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

struct astruct_114
{
	// 8 undefined bytes at 0x0
	BYTE field7_0x6;
	// 1 undefined byte at 0x7
	int* field8_0x8;
	int field9_0xc;
	int field10_0x10;
	int field11_0x14;
	// 32 undefined bytes at 0x18
	short field12_0x34;
	// 16 undefined bytes at 0x36
	int* field56_0x44;
	// 4 undefined bytes at 0x48
	int field61_0x4c;
	int field62_0x50;
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
	uint Port = 23756;                     // 0 - 65536
	uint BroadcastPort = 23757;            // 0 - 65536
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

void CreateErrorMessageAndDie(const char* message);

/////////////////////////////////////////////////
// Classes

// This jump table thing is making me think it's not a class but like a bugbear-made method system. But maybe that's just how classes are implemented in assembly and Ghidra is right?
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
	void (*vtable)(); // Array of functions, methods if you will. I don't know if this is a bugbear-made system using C or this is how C++ methods are handled by the compiler.

	char buffer[0x4000]; // 0x4

	int usuallyNeg1;           // 0x4004 - is -1 on newly opened track_spvs.gen,
	// I've just discovered a function that changes it, I'm still figuring this one out.

	char* filePos;         // 0x4008 - "virtual" file pos - reads in 16kb blocks internally, but allows for arbitrary reads

	char* realFilePos;     // 0x400C - real file's filePos, gets increased by bytesRead
	void* size;        // 0x4010 - returned by BvhFile_Func8 unless it's -1 - *0x4008 otherwise
	HANDLE handle;      // 0x4014
	uint fileattributes;         // 0x4018 - bitmask related to the parameters the file was opened with

	// Two different filename properties, I'm thinking maybe it's for objects that need to load both a model and texture file?
	char* filename1; // 0x401C
	char* filename2; // 0x4020

	// I thought there was more but it's always 0x4024 bytes allocated for this object, so that solves that.

	// Writes a section of the file to it's handle, starting at the buffer_item. Returns the number of bytes actually written for comparison.
	// Updates realFilePos and filePos to point after the written bytes.
	DWORD FileObject_WriteFileToHandle(char buffer_item, DWORD bytesToWrite)
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
	FileObject* FileObject_New(uint unaff_EBX, const char* filename_unaff_EDI)
	{
		FileObject* output = NULL;
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
				//piVar2->vtable = JMPTABLE_0067b6f8;
				piVar2->usuallyNeg1 = -1;
				output = piVar2;
			}
			// Did they mean to put this inside the if statement? it'll try to call it even when the output wasn't initialized, which would just crash.
			// Also, they didn't give it any parameters, it requires 2.
			//output->FileObject_Create();
		}
		else
		{
			struct _stat result;
			if (_stat(filename_unaff_EDI, &result) == 0)
			{
				FileObject* pAVar2 = (FileObject*)malloc(0x4024);
				if (pAVar2 != NULL)
				{
					pAVar2->FileObject_Clear();
					output = pAVar2;
				}
				//output->FileObject_Create();
				void* pvStack_18;
				output->size = pvStack_18;
				return output;
			}
		}
		return output;
	}

	void FileObject_Create(LPCSTR lpFilename, uint flags)
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
			//(*FUNC_008da6f4)();

			return;
	}

	// If mode is 1, It'll just set the file pos with no fuss.
	// If mode is 2, It'll treat the file pos relative to the end going backwards.
	// If mode is 0, 
	void FileObject_SetFilePos(int newPos, int mode)
	{
		if (mode == 0)
		{
			if ((this->fileattributes & 0x100) == 0)
			{
				char* pcVar1 = this->filePos;
				/*
				for (int iVar2 = this->usuallyNeg1; iVar2 < (int)(pcVar1 + newPos) >> 0xE; iVar2++)
					if (iVar2 > -1)
						this->FileObject_Read(iVar2);
				*/
			}
		}
		else
		{
			if (mode == 1)
			{
				this->filePos = (char*)newPos;
				return;
			}
			if (mode == 2)
			{
				this->filePos = (char*)((int)this->size - newPos);
				return;
			}
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
		return ((uint)this->filePos > 0) && (this->size <= this->filePos);
	}

	int FileObject_GetSize()
	{
		return (this->size == (void*)0xffffffff) ? (int)this->filePos : (int)this->size;
	}

	void FileObject_Clear()
	{
		this->usuallyNeg1 = -1;
		this->filePos = NULL;
		this->realFilePos = NULL;
		this->handle = NULL;
		this->filename1 = NULL;
		this->filename2 = NULL;
		return;
	}

	void __fastcall FileObject_Close()
	{
		if (this->handle != NULL)
		{
			CloseHandle(this->handle);
			this->handle = NULL;
		}
		return;
	}
};

void __fastcall FileObject_ClearEAX(FileObject* in_EAX)
{
	//in_EAX->vtable = JMPTABLE_0067b6f8;
	in_EAX->usuallyNeg1 = -1;
	in_EAX->filePos = NULL;
	in_EAX->realFilePos = NULL;
	in_EAX->handle = NULL;
	in_EAX->filename1 = NULL;
	in_EAX->filename2 = NULL;
	return;
}




/////////////////////////////////////////////////
//
// Strings
// 
/////////////////////////////////////////////////

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
int SlashConvertString(uchar* in_string, int mode, uchar* out_string)
{
	uchar* tempPtr;
	uchar currentChar;
	int lenOfData;
	uchar* pcVar2;

	if (mode == 0)
	{
		tempPtr = in_string;
		// Getting the length of the string.
		do
		{
			currentChar = *tempPtr;
			tempPtr = tempPtr + 1;
		} while (currentChar != NULL);
		lenOfData = (int)tempPtr - ((int)in_string + 1);

		if (lenOfData)
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
	// So it either returns the negative value of char2, or 0
	return char1 - char2;
}

// Honestly not too sure about the why
// Same as Compare_s, it sweeps through until it finds a difference and then returns the difference in value between the characters.
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

int String_GetLength(char* in_string)
{
	char* tempPtr = in_string;
	while (*tempPtr != NULL)
		tempPtr++;

	return tempPtr - in_string;
}

// Simple copy from one string to another.
// Both pointers will end up pointing at the end of the string, so it returns
// the original pointer to the out_string.
char* String_SimpleCopy(char* out_string, const char* in_string)
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

// Appends the in_string to the end of the out_string.
// Finds the first NULL in the out_string and starts there.
char* String_Append(char* out_string, const char* in_string)
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

// Same as String_Append except with a length
char* String_AppendSubstring(char* out_string, char* in_string, int length)
{
	char* original = out_string;
	if (length)
	{
		// Skips to the end of the string
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

// Copies 256 characters from the in_string to the out_string, setting the
// 256th to NULL, and the 1072nd to param_2
void __cdecl ComplicatedCopyString(char* out_string, char param_2, char* in_string)
{
	char* _Dest = out_string;
	strncpy_s(_Dest, 0x100, in_string, 0x100);
	_Dest[0xff] = NULL;
	_Dest[0x430] = param_2;
	return;
}

void static CopyStringToPointerToString(char** out_string, const char* in_string)
{
	char* _Dest;
	_Dest = *out_string;
	strncpy_s(_Dest, 0x100, in_string, 0x100);
	_Dest[0xFF] = NULL;
	return;
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

void AddStringToList(int index, const char* newString)
{
	if ((0x31 < index) && (index < 0xFF))
		StringList_00681888[index] = newString;
	return;
}




/////////////////////////////////////////////////
//
// Startup Sequence
// 
/////////////////////////////////////////////////

// 1 = US, 2 = Germany, not 1 or 2 = Europe
// Germany got it's own version (after doing some more research and looking at the game files, I see they had to censor it over there.)
// Also, my presumably US copy is set to 0, meaning Europe.
uint version_0069c13c = 0;

// I don't know if it's possible to change the value fast enough that the german intro video plays, but you can wait on the title screen to see the german version of the attract demo.
// If set to Germany in a US or Europe copy, the game will crash when loading into a map because it can't find the ragdoll models.


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

void (*PTR_008e8418)(int);


DWORD Startup(HINSTANCE hInstance, uint param_3, char* flags)
{
	HINST_008da564 = hInstance;
	INT_PTR IVar2;

	// The random seed is set to the current time
	DWORD seed = timeGetTime();
	srand(seed);

	// Dealing with the setup flag
	setupFlag_008da684 = 0;
	if (flags != "" && (_stricmp(flags, "-setup") || _stricmp(flags, "setup")))
		setupFlag_008da684 = 1;

	CoInitializeEx(NULL, 0);

	int verCheck = CheckDirectXVersion((LPBYTE*)"4.09.00.0904");
	if (verCheck == 0 && (IVar2 = DialogBoxParamA(hInstance, (LPCSTR)0x83, NULL, (DLGPROC)BasicDlgProc, 0), IVar2 == (INT_PTR)1))
		return 0xffffffff;

	// Sets unkn_008da6a0 to 1
	SetFPUCW(FPUConW_008d781c);

	// Unused flags
	strstr(flags, "-binarydb");
	strstr(flags, "-bedit");

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
uint UINT_00684b24 = -1;
uint* PTR_UINT_00684570 = &UINT_00684b20;

// Loads the sound module and sets UINT_00687984 to either 7, 8, or 9 based on how much was done.
// If just the sound library was loaded, it'll be 7
// If 
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
			char local_404[0x104];
			UINT uVar1 = GetSystemDirectoryA(local_404, 0x104);
			if (uVar1 != NULL)
			{
				char local_204;
				String_SimpleCopy(&local_204, local_404);
				String_Append(&local_204, "\\d3d9.dll");
				FILE** ppFVar2 = NULL;//FUN_0061f9bc(&local_204, NULL, 0);
				if (ppFVar2 != NULL)
				{
					//OpenDLLFile(ppFVar2);
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

	uint* puVar7 = &UINT_006a328c;
	int errorCode, pvVar5;
	for (int iVar3 = 8; iVar3 != 0; iVar3 -= 1)
	{
		*puVar7 = 0;
		puVar7 += 1;
	}
	INT_007a32e4 = 0;
	if ((param_1 == NULL))//&& (uVar2 = FUN_00621944(), uVar2 != NULL))
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
	uint result = isOlder ? -1 : 1;

	// Concatenate by shifting over an extra bit and or-ing.
	return (result << 9) | (result > -1);
}

IDirect3D9* D3D9_008da784;
float FLOAT_008e5e80;
LPDIRECT3DDEVICE9 LPDIRECT3DDEVICE9_008da788;

LRESULT WndProcWithMoreSteps(HWND hWnd, MSG uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateD3DWindow(HWND parent, HINSTANCE hInstance, LPCSTR title, HICON icon, HCURSOR cursor, astruct_110* param_6, uint* param_7, BYTE param_8, uint flags, int* in_EAX)
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
			posY = 0x80000000;
			posX = 0x80000000;
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
				DAT_008da410 = param_6->field3_0x98;
				DAT_008da414 = param_6->field4_0x9c;
			}
			UINT_008da418 = param_6->field6_0xa4;
			astruct135_008da420 = param_8;
			HWND_008da42c = HWND_008da79c;
			DAT_008da430 = in_EAX[0x8A];
			DAT_008da41c = (flags & 1) ? 2 : 1;
			DAT_008da428 = 1;
			DAT_008da434 = 1;
			if (param_7 == 0)
			{
				// ???
				param_7 = 0;
			}
			DAT_008da440 = param_7;
			DAT_008da444 = 0;
			DAT_008da43c = 0;
			
			HardwareCompatibilityTest2(in_EAX);
			posX = FUN_005a6a50();
			*/
			posX = 0;
			if (posX > -1)
			{
				posX = param_6->field2_0xc;
				in_EAX[8] = 1;
				in_EAX[7] = 1;
				nWidth = param_6->field0_0x4;
				in_EAX[2] = nWidth;
				flagTest = param_6->field1_0x8;
				in_EAX[3] = flagTest;
				posY = *(int*)LPDIRECT3DDEVICE9_008da788;
				in_EAX[4] = posX;
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

// I thought the 2 unknowns didn't make any sense, but the below function makes it clear this list used to be different.
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
// There are a few incorrect indices and a format that doesn't exist on the current list, indicating it used to be different and they forgot to update this function.
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

// For every D3DFORMAT, Run a CheckDeviceFormat() and if it succeeds, set a corrosponding bit in the above byte array.
// If every test passes, every byte in BYTE_008da490 should be 190, or 1011 1110
void HardwareCompatibilityTest(int struct_1, D3DFORMAT extraout_EDX)
{
	D3DFMT_0069bfec = D3DFMT_008da418;
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
int* PTR_008da560;
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

INT_PTR DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Creating setup window
//
int CreateSetupWindow(astruct_140* param_1, HINSTANCE hInst, int showSetup, int setupFlag)
{
	param_1->hinst_0x58 = hInst;

	// Retrieve the version from Lua, which is kinda strange since that variable is already supposed to contain the version, it's where Lua got it from.
	//version_0069c13c = FUN_00523500();
	//copyOfVersion_008da550 = FUN_00523500();

	uint* uVar7;
	uint uVar13;
	HCURSOR cursor;

	// What does putting a nullptr in _time32 mean? Can you do that?
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
				INT_PTR IVar10 = DialogBoxParamA(hInst, (LPCSTR)0x65, NULL, (DLGPROC)DlgProc, 0);
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
			cursor = LoadCursorA(NULL, (LPCSTR)IDC_ARROW);
			bool bVar19 = UINT_006d6908 != 0;
			param_1->field1_0x44 = 1;
			iVar = (int)bVar19 | 0x10;
			if ((*(byte*)(iVar17 + 0x18) & 8) != 0)
			{
				iVar = (int)bVar19 | 0x18;
				param_1->field0_0x40 = 1;
			}
			HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar, (int*)hInst);
			if (HWND_008da56c == (HANDLE)NULL)
			{
				DestroyWindow((HWND)*PTR_008da560);
				UINT_006d6908 = 0;
				HWND_008da56c = CreateD3DWindow(NULL, hInst, "FlatOut 2", HICON_008da544, cursor, *(astruct_110**)(iVar17 + 4), UINT_006d68f4, UINT_006d68fc, iVar & 0xfffffffe, (int*)UINT_006d68f4);
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

int* PTR_008da718;
HINSTANCE HINSTANCE_008da2dc;
uint UINT_008da798;

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




/////////////////////////////////////////////////
//
// WndProcs
// 
/////////////////////////////////////////////////

DLGPROC Dlgproc;

INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = hwnd;
	LRESULT LVar6;
	LRESULT* iVar10, * iVar11;
	if (uMsg != WM_INITDIALOG)
	{
		if (uMsg == WM_NOTIFY)
		{
			if (*(int*)(lParam + 4) == 0x43d)
			{
				if (*(int*)(lParam + 8) == -0x10)
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
			// Sent when the user selects a command item from a menu, when a control sends
			// a notification message to it's parent window, or when an accelerator keystroke
			// is translated.
			if (wParam == 1)
			{
				LVar6 = SendDlgItemMessageA(hwnd, 0x3eb, BM_GETCHECK, 0, 0);
				UINT_006d6908 = (uint)(LVar6 == 1);
				LVar6 = SendDlgItemMessageA(hwnd, 0x462, BM_GETCHECK, 0, 0);
				UINT_006d690c = (uint)(LVar6 == 1);
				LVar6 = SendDlgItemMessageA(hwnd, 0x44e, BM_GETCHECK, 0, 0);
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
				EndDialog(hwnd, 1);
				return 1;
			}
			if (wParam == 2)
			{
				EndDialog(hwnd, 2);
				return 1;
			}
			// Looks like code for a help button
			if (wParam == 0x3fc)
			{
				HINSTANCE pHVar7 = ShellExecuteA(hwnd, lpOperation_0066ab90, "http://www.flatoutgame.com/", NULL, NULL, TRUE);
				if ((INT_PTR)pHVar7 < 0x21)
				{
					ShellExecuteA(hwnd, lpOperation_0066ab90, "iexplorer.exe", "http://www.flatoutgame.com/", NULL, TRUE);
				}
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

class AutoClass15
{
public:
	char (*pointerToASpecialWndProc)(HWND, MSG, WPARAM, LPARAM, WPARAM*, uint);

	void WndProc(HWND hWnd, MSG uMsg, WPARAM wParam, LPARAM lParam)
	{
		WPARAM copy = wParam;
		if (this->pointerToASpecialWndProc != NULL)
		{
			this->pointerToASpecialWndProc(hWnd, uMsg, wParam, lParam, &copy, 0);
		}
	}
};

HRESULT WndProcWithMoreSteps(HWND hWnd, MSG uMsg, WPARAM wParam, LPARAM lParam)
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
	LPSTR subKey;
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
						// Intellisense doesn't like this, but that's what it does.
						//reOpenBuf = (OFSTRUCT)0x88;
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




/////////////////////////////////////////////////
//
// Input
// 
/////////////////////////////////////////////////

BYTE lpKeyState_008d7e60[0x40];
HHOOK HHOOK_008da738;
BYTE UINT_008d7d60[0x40];

void Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam);

HOOKPROC nextHook = (HOOKPROC)Keyboard_HookProc;

LRESULT Keyboard_Hook(void* cThis, uint param_1)
{
	BYTE* puVar2 = lpKeyState_008d7e60;
	for (int i = 0x40; i != 0; i--)
	{
		*puVar2 = 0;
		puVar2++;
	}

	puVar2 = UINT_008d7d60;
	for (int i = 0x40; i != 0; i--)
	{
		*puVar2 = 0;
		puVar2++;
	}

	if (HHOOK_008da738 == NULL)
	{
		DWORD dwThreadId = GetCurrentThreadId();
		HHOOK_008da738 = SetWindowsHookExA(2, nextHook, NULL, dwThreadId);
		if (HHOOK_008da738 == NULL)
		{
			//uStack_2c = 0xF;
			//uStack_30 = 0;
			//uStack_40 = 0;
			//FUN_0055b050(auStack_44, "KeyboardController: Unable to hook keyboard", 0x2B);
			//appuStack_28[0] = &PTR_FUN_006578c4;
			//uStack_4 = 0xF;
			//uStack_8 = 0;
			//uStack_18 = 0;
			//FUN_0055ae50(auStack_1c, auStack_44, 0, 0xFFFFFFFF);
			// Some kind of exception code, I'll just do this for now.
			throw EXCEPTION_INVALID_HANDLE;
		}
	}
}

void Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam)
{
	return;
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




/////////////////////////////////////////////////
//
// Network
// 
/////////////////////////////////////////////////

bool StringAddressToBinaryRepresentation(char* stringAddress, unsigned long* out_addr)
{
	int local_14, local_10, local_c, local_8;
	int occurences = sscanf(stringAddress, "%d.%d.%d.%d", &local_14, &local_10, &local_c, &local_8);
	if (occurences < 4)
		return false;

	unsigned long binary = inet_addr(stringAddress);
	*out_addr = binary;
	return binary != INADDR_NONE;
}

unsigned int AsyncMaxWaitTime_00684b18;

void MaybeSleep(DWORD miliseconds)
{
	if (PTR_UINT_00684570[1] != 0xd)
	{
		Sleep(miliseconds);
	}
	return;
}

void FUN_0062f54e(char* stringAddress, int param_2, unsigned short extraout_var)
{
	HANDLE local_c;
	bool bVar1 = StringAddressToBinaryRepresentation(stringAddress, (unsigned long*)local_c);
	if (((extraout_var << 1) | bVar1) == 0)
	{
		char* local_40c = (char*)malloc(0x400);
		local_c = WSAAsyncGetHostByName(NULL, 0, stringAddress, local_40c, 0x400);

		uint timePassed = 0;
		uint start = GetMiliseconds();
		uint now;

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

// Isn't this just an infinite loop?
void MaybeSleepLoop(FILE** fileArray)
{
	while (fileArray[10] != NULL)
		MaybeSleep(10);

	return;
}

// The newState determines which character is set to '\1' in the string.
// " (after 256 chacters) 0 ? ? ? 2 ? ? ? 1;
int SetState(char** out_string, int newState)
{
	 char* theString = *out_string;
	 if (newState == 0x100)
	 {
		 *(theString + 0x100) = '\1';
		 return 0;
	 }
	 if (newState != 0x101)
	 {
		 if (newState != 0x102)
		 {
			 CopyStringToPointerToString(out_string, "Invalid state.");
			 return 2;
		 }
		 *(theString + 0x104) = '\1';
		 return 0;
	 }
	 *(theString + 0x108) = '\1';
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
	// Presumably tons more, this object alone is nearly 8KB large
};

GameSpyObject* GameSpyRelated_008ec884;

void NewGameSpyObject()
{
	GameSpyRelated_008ec884 = (GameSpyObject*)malloc(0x1EE0);
	return;
}

void CreateGameSpyPresence()
{
	CreateGameSpyPresenceForReal();
	return;
}

uint UINT_008e84e8;
uint DAT_008e84e4;

void CreateGameSpyPresenceForReal()
{
	if ((UINT_008e84e8 == 0) && (DAT_008e84e4 == 0))
	{
		if (GameSpyRelated_008ec884 != NULL)
		{
			// This function doesn't return a value, and yet it's supposed to here.
			UINT_008e84e8 = InitGameSpy(GameSpyRelated_008ec884);
			DAT_008e84e4++;
			return;
		}
		UINT_008e84e8 = 0;
	}
	DAT_008e84e4++;
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
	gs_ESI->ptr_0x94 = &gs_ESI[1].func_0x0;
	gs_ESI->ptr_0x98 = &gs_ESI[1].func_0x0;
	gs_ESI->ptr_0x9c = &gs_ESI[1].int_0x40;

	ppcVar1 = &gs_ESI->string_0x74;
	SetState_s(ppcVar1, 0x102);
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
// AutoClass9 / PropertyDb
// 
/////////////////////////////////////////////////

// AutoClass 9
// I'm pretty sure this is the Lua interpreter, or at the very least it's some kind of structure that contains 
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
		// Counts the length of the string to make sure it's more than one character long
		do {
			currentChar = *tempString;
			tempString = tempString + 1;
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
				iVar5 += 1;
				tempString[(int)(charStack + -(int)in_string)] = currentChar;
				currentChar = tempString[1];
				iVar4 += 1;
				tempString = tempString + 1;
			} while (currentChar != '\0');
		}
		currentChar = in_string[iVar4];
		charStack[iVar5] = NULL;
		if (currentChar == '.')
			iVar4 += 1;

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
		AutoClass9* pAVar3 = this->FUN_00557fe0(param_1, NULL);
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
			// I think it's a bit too late for that.
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

int PropertyDb_AccessProperty(char* in_EAX)
{
	char* leftBracket = strstr(in_EAX, "[");
	char* rightBracket = strstr(in_EAX, "]");
	char* tempPtr = in_EAX;
	char local_100;
	char local_110;
	long lVar4;

	do
	{
		tempPtr = tempPtr + 1;
	} while (*tempPtr != NULL);

	int iVar6;
	char currentChar;
	if (leftBracket == NULL || rightBracket == NULL || rightBracket <= leftBracket || (rightBracket + -(int)in_EAX != tempPtr + (-1 - (int)(in_EAX + 1))))
	{
		iVar6 = -(int)in_EAX;
		do
		{
			currentChar = *in_EAX;
			// Doesn't using the address of a recently created local variable mean it's random?
			in_EAX[(int)(&local_100 + iVar6)] = currentChar;
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
			tempPtr[(int)(&local_110 + iVar6)] = currentChar;
			tempPtr += 1;
		} while (currentChar != NULL);
		
		uint* puVar2 = (uint*) & local_110;
		uint* puVar3;
		do
		{
			puVar3 = puVar2;
			puVar2 = puVar3 + 1;
		} while (*puVar3 != NULL);
		puVar3[-1] = NULL;
		lVar4 = atol(&local_110);
		strncpy(&local_100, in_EAX, (size_t)(leftBracket - in_EAX));
	}
}


uint AttemptToYield(astruct_114* param_1, int param_2)
{
	if (param_1->field12_0x34 != 0)
		//LuaLogMaybe(param_1, "attempt to yield across metamethod/C-call boundary");

	param_1->field9_0xc = (int)param_1->field8_0x8 + (param_2 * -2);
	param_1->field7_0x6 = 1;
}




/////////////////////////////////////////////////
//
// File System
// 
/////////////////////////////////////////////////

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
	UINT_008da700 = 0;
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

FileObject* PTR_008da72c;

void OpenBFS(LPCSTR filename, HANDLE* unaff_EDI)
{
	LPCSTR pCVar5 = filename;
	DWORD fileFlags;
	HANDLE bfsFile;
	HANDLE pvVar3;
	FileObject* pAVar4;
	int aiStack_10[2];
	int iVar2;
	int iVar9;
	int* piVar7;
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

	pAVar4 = PTR_008da72c;
	unaff_EDI[1] = bfsFile;
	//FUN_0059b60(pAVar4, unaff_EDI, aiStack_10, 0, 0x10);
	// The file must start with the characters "bfsl"
	if (aiStack_10[0] != 0x31736662)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid id");

	unaff_EDI[0x84] = bfsFile;
	uint uStack_8 = 0;
	size_t _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
	HANDLE pvStack_4;
	unaff_EDI[0x85] = pvStack_4;
	uint* puVar7 = (uint*)malloc(_Size);
	pAVar4 = PTR_008da72c;
	unaff_EDI[0x82] = puVar7;
	//FUN_00559b60(pAVar4, unaff_EDI, puVar7, unaff_EDI[0x88], _Size);
	//pvVar6 = unaff_EDI[0x82];
	if ((int)uStack_8 < 0)
		//FUN_005610f0((int)&DAT_0069bd10, _Size - 0x10 >> 2);

	if (*(int *) ((int) bfsFile + 0x10) != 0x3E5)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

	unaff_EDI[0x86] = (HANDLE)((int)bfsFile + 0x14);
	piVar10 = (int*)((int)bfsFile + 0x1F3C);
	piVar7 = (int*)malloc(0x14);
	if (piVar7 == NULL)
		piVar7 = NULL;
	else
	{
		iVar9 = *(int*)((int)bfsFile + 8000);
		*piVar7 = *piVar10;
		iVar2 = *(int*)((int)bfsFile + 0x1F44);
		piVar7[1] = iVar9 + (int)piVar10;
		iVar9 = *(int*)((int)bfsFile + 0x1F48);
		piVar7[2] = iVar2 + (int)piVar10;
		iVar2 = *(int*)((int)bfsFile - 0x1F4C);
		piVar7[3] = iVar9 + (int)piVar10;
		piVar7[4] = iVar2 + (int)piVar10;
	}
	pvVar3 = unaff_EDI[0x88];
	unaff_EDI[0x87] = piVar7;
	bfsFile = (HANDLE)((int)piVar10 + *piVar7);
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
				} while (iVar8 < (int)(uint)*(byte *)((int)bfsFile + 1));
			}
			bfsFile = (HANDLE)((int)bfsFile + (uint) * (byte*)((int)bfsFile + 1) * 4 + 0x18);
		}
	}
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

bool WriteCharToStream(char in_char, FILE* file)
{
	return fputc(in_char, file) != -1;
}

// Still confused about this one

uint SetFPUCW(unsigned short in_FPUControlWord)
{
	uint copyOfWhat;

	copyOfWhat = unkn_008da6a0 >> 0x10;
	if (unkn_008da6a0 == 0) {
		unkn_008da6a0 = 1;
		FPUConW_008d781c = in_FPUControlWord;
	}
	return copyOfWhat << 2 | in_FPUControlWord;
}

void DoNothing()
{
	return;
}





/////////////////////////////////////////////////
//
// Debug
// 
/////////////////////////////////////////////////

void CreateErrorMessageAndDie(const char* message)
{
	char local_800;
	char body[1024];

	// The list of arguments to put into the message is located at Stack[0x8], I'm not sure how that works or why, but sure.
	//vsprintf(&local_800, message, (va_list)0x8);
	sprintf(body, "%s", message);
	MessageBoxA(NULL, (LPCSTR)body, "Fatal error", MB_ICONERROR);
	ExitProcess(0);
}

void (*FUNC_006a2c28)();

// My guess is, this is where bugbear's debugger would take over for investigation.
void ExitWithCode25()
{
	if (FUNC_006a2c28 != NULL)
		(*FUNC_006a2c28)();

	// This function emits the runtime error message to stderr for console applications,
	// or displays the message in a message box for Windows applications.
	// In debug mode, you can choose to invoke the debugger before exiting.
	// - Documentation
	// It also needs an internal.h file, but I don't have it.
	//_amsg_exit(0x19);
}

// The normal jumptable
void (*JMPTABLE_0067b1c0[])() = {
	//FUN_00558390
	//AutoClass9::AddMappedTable,
	//FUN_005585e0
	DoNothing,
	//FUN_005585f0
};

// The not normal jumptable
void (*JMPTABLE_0067ad08[58])() = {};

// Instead of writing all that out I'll replace it with code that would do the same thing
// 56 of them are ExitWithCode25, and the last one is FUN_0054c970, I don't know about that one yet.
void CreateThatWeirdJumpTable()
{
	for (int i = 0; i < 57; i++)
		JMPTABLE_0067ad08[i] = ExitWithCode25;

	//JMPTABLE_0067ad08[57] = FUN_0054c970;
}


void* DoNotCallEver(void *in_mem, int bFree)
{
	// I don't think this does anything, seems like a default value.
	in_mem = &JMPTABLE_0067b1c0;
	CreateErrorMessageAndDie("Must not be called - ever.");

	// Does not return, so the rest of this never happens.
	// But if it did, this jump table would be replaced with one where every function will exit with error code 25.
	// If it didn't create the message, it would just silently crash anyways.
	in_mem = &JMPTABLE_0067ad08;
	if (bFree)
		free(in_mem);

	return in_mem;
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
//
// Entry / Main
// 
/////////////////////////////////////////////////

DWORD DWORD_006a2cd8;
undefined4 DAT_00000094;
LPSTR LPSTR_008edca4;
LPWCH LPWCH_006a2c2c;

int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	int* piVar2;
	int iVar1;
	bool bVar3;
	char* flags;
	LPSTARTUPINFOA startInfo;
	HINSTANCE hInst;

	// Checks if we're running Windows but doesn't store it anywhere.
	LPOSVERSIONINFOA osInfo;
	//GetVersionExA(osInfo);

	DWORD dStack_110;
	DWORD dStack_104;
	uint uStack_108;
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
		flags = lpCmdLine;
		uint uVar4 = 0;
		hInst = GetModuleHandleA(NULL);
		int code = Startup(hInst, uVar4, flags);
		if (bVar3)
		{
			// Performs complete C library termination procedures and returns to caller, but doesn't terminate process.
			// - Documentation
			//_cexit();
			return code;
		}
		exit(code);
}