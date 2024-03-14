// FlatOut 2 Decompilation

// This is a decompilation of the GOG version of Flatout 2.
// As far as I'm aware, the DRM is the only difference between versions, they share jump tables, function locations, and every variable that I've checked so far does the same thing.

// I had a section about variables I had found with Cheat Engine but I've realized that their location is random, so it wasn't really useful anyways.

// Bugbear used Visual Studio 2003 aka Visual Studio 6, which means we know the IDE, compiler, all that. But finding a copy these days is difficult.
// To remove the warnings about the unsafe string functions, add _CRT_SECURE_NO_WARNINGS to the Preprocessor definitions under Properties -> C/C++ -> Preprocessor

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
#include <math.h>
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

#define cchar const char

#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
// I thought a long was 8 bytes, but that's not the case on Windows.
// long and int are the same size? Why is it a 'long' then?
#define undefined8 unsigned long long

// Doesn't end there, turns out a long double is the same size as a double.
// I couldn't find much information about what ghidra's float10 actually is.
// I've heard it's an 80-bit float but 64 is the best we're going to get without some custom/third party solution.
#define float10 long double


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

void CreateErrorMessageAndDie(const char* message, ...);

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

	// Writes a section of the file to it's handle, given the buffer and desired bytes to write. Returns the number of bytes actually written for comparison.
	// Updates realFilePos and filePos to point after the written bytes.
	DWORD FileObject_WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite)
	{
		
		DWORD bytesWritten;
		DWORD totalBytesWritten = 0;
		HANDLE hFile;
		DWORD tempToWrite;

		

		if (bytesToWrite != 0)
		{
			hFile = this->handle;

			for (int d = bytesToWrite; d != 0; d -= tempToWrite)
			{
				// Writes in 64 KB chunks unless what's left is less.
				tempToWrite = 0xffff;
				if (d < 0x10000)
					tempToWrite = d;

				WriteFile(hFile, buffer, tempToWrite, &bytesWritten, NULL);
				buffer = (LPCVOID) ((int)buffer + tempToWrite);
				totalBytesWritten += bytesWritten;
			}
		}
		// Advance the pointers
		this->realFilePos = this->realFilePos + bytesToWrite;
		this->filePos = this->filePos + bytesToWrite;
		return totalBytesWritten;
	}

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
			// Also, it wasn't given any parameters from what I can tell
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
				// They did it again, it's gotta be on purpose for some reason
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
			(*FUNC_008da6f4)();

		return;
	}

	// If mode is 1, It'll just set the file pos with no fuss.
	// If mode is 2, It'll treat the file pos relative to the end.
	// If mode is 0, checks a flag in the attributes and if it's set, read from the file in, a way.
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

	// This would make sense if the filePos was private, but it has to be public to be accessed by the FileObject_ClearEAX() function.
	// It might not be a C++ class anyways so did they go through the trouble of integrating public/private distinction in their own class?
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
		return (this->size == (void*)0xFFFFFFFF) ? (int)this->filePos : (int)this->size;
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

	FileObject* FileObject_ResetMaybe(int bFree)
	{
		//this->vtable = &JMPTABLE_0067b6f8;
		if (this->handle != NULL)
		{
			CloseHandle(this->handle);
			this->handle = NULL;
		}
		if (bFree & 1)
		{
			free(this);
		}
		return this;
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

		// Counts the length of the string.
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

// They have a String_GetLength function but there are a lot of places that counted the string manually.
// Maybe this was written later, or it was too expensive to call more functions?
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
		if (!length)
			return original;

		current = *in_string;
		*out_string = current;
		out_string++;
		in_string++;
		length--;
	} while (current != NULL);
	return original;
}

// Appends the in_string to the end of the out_string.
// Finds the first NULL in the out_string and starts there.
// It returns the starting pointer to the out_string, but my own experimenting tells me that the original isn't modified anyways, the function is given a copy of the pointer.
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
void __cdecl ComplicatedCopyString(char** out_string, uint param_2, const char* in_string)
{
	char* _Dest = *out_string;
	strncpy(_Dest, in_string, 0x100);
	_Dest[0xff] = NULL;
	*((uint *)_Dest[0x430]) = param_2;
	return;
}

void static CopyStringToPointerToString(char** out_string, const char* in_string)
{
	char* _Dest;
	_Dest = *out_string;
	strncpy(_Dest, in_string, 0x100);
	_Dest[0xFF] = NULL;
	return;
}

// I just checked, it's the same as Microsoft's tolower() except 'A' - 'a' is precalculated, happens to be the space character.
char Char_ToLowercase(char theChar)
{
	if (theChar > 64 && theChar < 91)
		theChar += ' ';
	return theChar;
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

// Apparently these aren't strings, but they are treated like them.
// Sweeps through as if it's a string, but when it does the comparison it casts both of them to integers with no conversion, so it'll compare 4 characters each time.
bool String_CompareAsIntegers(int* ints1, int* ints2)
{
	bool equal = true;
	int iVar1 = 4;
	do
	{
		if (iVar1 == 0)
			return equal;

		iVar1--;
		equal = *ints1 == *ints2;
		ints1++;
		ints2++;
	} while (equal);
	return equal;
}

// StringToNum
// Converts the string into a float, unless it ends with an x or X character,
// then it will treated as a ulong
// Returns whether or not the given string ended with a null.
bool StringToNum(char* stringFloat, float* outFloat)
{
	bool nullTerminated;
	char* EndPtr;

	*outFloat = (float)strtod(stringFloat, &EndPtr);

	if (EndPtr == stringFloat)
		nullTerminated = false;
	else
	{
		if (*EndPtr == 'x' || *EndPtr == 'X')
			*outFloat = (float)(ulonglong)strtoul(stringFloat, &EndPtr, 0x10);

		if (*EndPtr == NULL)
			nullTerminated = true;
		else
		{
			// Sweeps through the string until a non-white-space character
			while (isspace(*EndPtr))
				EndPtr++;

			nullTerminated = *EndPtr == NULL;
		}
	}

	return nullTerminated;
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

// I don't know if it's possible to change the value fast enough that the german intro video plays, but you can wait on the title screen to see the german version of the attract video.
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


DWORD wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPCSTR lpCmdLine, char* flags)
{
	HINST_008da564 = hInstance;
	INT_PTR IVar2;

	// The random seed is set to the current time
	DWORD seed = timeGetTime();
	srand(seed);

	// Dealing with the setup flag
	setupFlag_008da684 = 0;
	if (lpCmdLine != "" && (stricmp(lpCmdLine, "-setup") || _stricmp(lpCmdLine, "setup")))
		setupFlag_008da684 = 1;

	CoInitializeEx(NULL, 0);

	int verCheck = CheckDirectXVersion((LPBYTE*)"4.09.00.0904");
	if (verCheck == 0 && (IVar2 = DialogBoxParamA(hInstance, (LPCSTR)0x83, NULL, (DLGPROC)BasicDlgProc, 0), IVar2 == (INT_PTR)1))
		return 0xffffffff;

	// Sets unkn_008da6a0 to 1
	SetFPUCW(FPUConW_008d781c);

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
uint UINT_00684b24 = -1;
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
	if ((param_1 == NULL))//&& (FUN_00621944() != NULL))
	{
		//PTR_GetASPI32SupportInfo_006a32d4 = FUN_00620525;
		//PTR_SendASPI32Command_006a32d8 = FUN_00621ea4;
	}
	else
	{
		// Clearing an 8-byte buffer
		puVar7 = &UINT_006a328c;
		for (int iVar3 = 8; iVar3 != 0; iVar3--)
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

LRESULT WndProcWithMoreSteps(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hDlg = hwnd;
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
			// Clicking on the logo in the settings window
			if (wParam == 0x3fc)
				
			{
				HINSTANCE errorCode = ShellExecuteA(hwnd, lpOperation_0066ab90, "http://www.flatoutgame.com/", NULL, NULL, TRUE);
				if ((INT_PTR)errorCode < 33)
					ShellExecuteA(hwnd, lpOperation_0066ab90, "iexplorer.exe", "http://www.flatoutgame.com/", NULL, TRUE);

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
		if ((this->wndProcIsh_0x50 != NULL) && (this->wndProcIsh_0x50(hWnd, uMsg, wParam, lParam, &copy, 0) != NULL))
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
				break;

			}
		}
		else if (uMsg == WM_NCHITTEST)
		{
			if (this->unkn_0x30 == 0)
				return 1;
		}
		else if (uMsg == WM_SYSCOMMAND)
		{
			if (copy == 0xF100 || copy == 0xF000 || copy == 0xF010 || copy == 0xF030 || copy == 0xF140 || copy == 0xF170)
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
			LSTATUS LVar2 = RegQueryValueExA(local_c, "clsid", NULL, &keyType, data, (LPDWORD)&param4);
			char* local_11c;
			BYTE local_3e4[0x200];
			// Using an uninititialized string as the keyName.
			uint uVar3 = GetKeyFromRegistry(local_11c, local_3e4, 0x200);
			if ((LVar2 == ERROR_SUCCESS))
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

BYTE lpKeyState_008d7d60[0x40];
BYTE lpKeyState_008d7e60[0x40];
HHOOK HHOOK_008da738;


LRESULT Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam);

HOOKPROC nextHook = (HOOKPROC)Keyboard_HookProc;

LRESULT Keyboard_Hook(void* cThis, uint param_1)
{
	BYTE* puVar2 = lpKeyState_008d7e60;
	for (int i = 0x40; i != 0; i--)
	{
		*puVar2 = 0;
		puVar2++;
	}

	puVar2 = lpKeyState_008d7d60;
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

int DAT_008da740;
uint DAT_008da734;
int* PTR_008e844c;

LRESULT Keyboard_HookProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
		return;
	}

	uint wVirtKey = wParam & 0xFF;
	if (lParam < 0)
	{
		if (lpKeyState_008d7e60[wVirtKey] < 0)
			DAT_008da740--;

		lpKeyState_008d7e60[wVirtKey] &= 0x7F;
	}
	else
	{
		// In Binary: 00?0 0??0 00?0 0?0? ?0?0 0000 0000 0000
		if (DAT_008da734 || ((lParam & 0x40000000U) == 0))
		{
			if (lpKeyState_008d7e60[wVirtKey] > -1)
				DAT_008da740--;

			lpKeyState_008d7e60[wVirtKey] ^= 1;
			lpKeyState_008d7e60[wVirtKey] |= 0x80;

			lpKeyState_008d7d60[wVirtKey] += 1;
		}
		if (PTR_008e844c[11] != 0)
		{
			if (((lParam & 0x40000000U) != 0) && (PTR_008e844c[5] == 0))
			{
				CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
				return;
			}

			WCHAR convertedKey = 0;
			// local_4 is AND'd before it's even initialized.
			uint local_4;
			local_4 &= 0xFFFF0000;
			int iVar1 = ToUnicode(wVirtKey, lParam, lpKeyState_008d7e60, &convertedKey, 8, 0);
			if (iVar1 == 1)
				// Treat local_4 as an array of 2 shorts, take the second one and concatentate with local_20.
				local_4 = (((short*)&local_4)[1] << 16) | (short)convertedKey;

			LPARAM LVar4;
			uint uVar3;
			iVar1 = ToAscii(wVirtKey, lParam, lpKeyState_008d7e60, (LPWORD)&convertedKey, 0);
			if (iVar1 == -1)
			{
				uVar3 = convertedKey & 0xFFFF;
				wVirtKey = 0;
				LVar4 = 0;
			}
			else
			{
				if (iVar1 != 0)
				{
					if (iVar1 > 0)
					{
						int iVar2 = 0;
						do
						{
							//FUN_00550350(&local_20 + (iVar2 * 2), wVirtKey, 0, local_4);
							iVar2++;
						} while (iVar2 < iVar1);
					}
					goto hookExit;
				}
				uVar3 = 0;
				LVar4 = lParam;
			}
			//FUN_00550350(uVar3, wVirtKey, LVar4, local_4);
		}
	}
hookExit:
	CallNextHookEx(HHOOK_008da738, code, wParam, lParam);
	return;
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
	if (PTR_UINT_00684570[1] != 0xD)
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
			 CopyStringToPointerToString(out_string, "Invalid state.");
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
	bool output = true;
	do
	{
		if (!lenOfCompare) break;
		lenOfCompare--;
		output = *subject == *compare;
		subject++;
		compare++;
	} while (output);
	return output;
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

struct astruct_166
{
	// 4 undefined bytes at offset 0x0
	int* pbuffer_0x4;
	int int_0x8;
	char* ptr_0xc;
	uint uint_0x10;
	int int_0x14;
	undefined4 unkn_0x18;
};

void SearchForLobbies(char** param_1, astruct_166* param_2)
{
	// Some kind of struct, unsure of what it is yet
	if ((param_2->int_0x8 == 0) && ((GetTickCount() - (DWORD)(param_2->pbuffer_0x4[0x51])) > 60000))
	{
		param_2->pbuffer_0x4[0x50] = 1;
		ComplicatedCopyString(param_1, 0xD02, "The search timed out");
	}
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
// I thought this was the Lua interpreter, but I think it's exclusively a database thing.
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
			// Copes the string in a strange way, right now I don't know what it means.
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


// astruct_157
struct LuaData
{
	int (**jmptable_0x0)(void);
	// 7 undefined bytes at offset 0x0
	int int_0x4;
	BYTE byte_0x7;
	// 4 undefined bytes at offset 0x8
	int* ptr_0xc;
	int int_0x10;
};

bool __fastcall LuaData_Verify(LuaData* data)
{
	return LuaData_SomethingElse(data) > 0;
}

int __fastcall LuaData_SomethingElse(LuaData data[])
{
	return data[1].int_0x10 - (int)data[2].ptr_0xc;
}

bool __fastcall LuaData_Something(LuaData* data)
{
	int iVar2 = LuaData_SomethingElse(data);
	int iVar1 = *data->ptr_0xc;
	int iVar3 = data->jmptable_0x0[2]();
	return iVar2 + iVar1 < iVar3;
}


// My own addition, It's leaning a bit towards inaccuracy, but it'll make it much easier to read the code
// The lua table stores items as pairs of astruct_157*, where the second pointer is actually a DWORD describing the type
// My guess is that because a DWORD is the same size, they could just cast with no issues.
struct LuaItem
{
	LuaData* data;
	DWORD type;
};

// And here's the table translating DWORD type into it's name
// The first and second userdata are very different, I don't know why they have the same name outside of security.
// technically -1 has an entry, it'll return "no value" when calling Lua_StringTypeFromInt
const char* LuaTypes_0065284c[] =
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

// I'll make an enum so I can use the type names instead of numbers
enum LT
{
	nil,
	boolean,
	userdata,
	number,
	string,
	table,
	function,
	userdata_s,
	thread,
	proto,
	upval
};

// This item is never used, it represents a null LuaItem.
// The data pointer is checked, so maybe the data doesn't have to be a pointer?
LuaItem LuaItem_None_0065271c;


// Can't do += sizeof() but you can with this workaround.
#define size_of(type) (1 * sizeof(type))

struct astruct_167
{
	// 20 undefined bytes at offset 0x0
	char char_0x15;
	// 29 undefined bytes at offset 0x16
	uint uint_0x40;
	int int_0x44;
	uint uint_0x4c;
	int int_0x50;
	int int_0x54;
};


struct astruct_169
{
	void* end_0x0; // Pointer to the last byte of itself, don't know why just yet.
	void* unkn_0x4;
	LuaTable* table_0x8;
};



// I'm finally starting to understand this one
// There are a lot of functions where the first parameter is a pointer to this struct, even if they don't reference it, leading me to believe it's part of a class/bugbear method system.
// I'll just make it a C++ class to make things easier.

// astruct_114
class LuaTable
{
public:
	// 8 undefined bytes at 0x0
	BYTE field7_0x6;
	BYTE byte_0x7;
	LuaItem* next_0x8; // Stores a pointer to the next blank item in the main table, for adding new ones
	LuaItem* table_0xc; // The main table
	astruct_167* field10_0x10;
	int field11_0x14;
	// 32 undefined bytes at 0x18
	short bDebug_0x34; // Flag wether or not to enable debug logging.
	// 16 undefined bytes at 0x36
	LuaItem* table_0x44;
	// 4 undefined bytes at 0x48
	int field61_0x4c;
	int field62_0x50;
	
	uint AttemptToYield(int param_2)
	{
		if (this->bDebug_0x34 != 0)
			//this->LuaLogMaybe("attempt to yield across metamethod/C-call boundary");
			DoNothing();

		// I thought table_0xc was the full table, but I guess it's also a temporary pointer of some kind.
		// I'm not that familiar with Lua, but what does this have to do with metamethods?
		this->table_0xc = this->next_0x8 + (param_2 * -2);
		this->field7_0x6 = 1;
	}

	void Lua_AddNilProperty()
	{
		// No bounds checking, If there's a way to access this function from lua it would be interesting to see what happens if this is spammed.
		this->next_0x8->type = LT::nil;
		this->next_0x8 += size_of(LuaItem);
	}

	void Lua_ActuallyAddStringProperty(char* data, size_t dataLength)
	{
		// Some kind of bounds checking I assume
		/*
		if (this->field10_0x10[0x10] <= this->field10_0x10[0x11])
		{
			FUN_005ba3a0(this);
		}
		*/

		LuaItem* pNext = this->next_0x8;

		// It's quite the rabbit hole of a function, still figuring it out.
		//pNext->data = FUN_005c07b0(this, data, dataLength);

		pNext->type = LT::string;
		this->next_0x8 += size_of(LuaItem);
	}

	void Lua_AddStringProperty(char* in_string)
	{
		if (in_string == NULL)
			this->Lua_AddNilProperty();
		else
			this->Lua_ActuallyAddStringProperty(in_string, String_GetLength(in_string));

		return;
	}

	// Seems like astruct_114 has several different tables, or maybe it's like one big table that has temporary pointers
	// If the index is equal to or greater than 1:
	//		The 1-based index into table_0xc
	// If index is less than 1, it's compared to specific values to determine the list to return. These numbers seem arbitrary and I wonder if part of the number is a flag.
	//		-0x2712 : field56_0x44
	//		-0x2711 :  some math involving field11_0x14
	//		-0x2710 : table_0x10 + 0x17

	LuaItem* Lua_GetItem(int index)
	{
		LuaItem* output;
		if (index < 1)
		{
			if (index < -0x270F)
			{
				if (index == -0x2712)
					output = this->table_0x44;

				else if (index == -0x2711)
				{
					this->field61_0x4c = *(int*)(*this->field11_0x14[1] + 0xC);
					this->field62_0x50 = 5;
					output = (LuaItem*)&this->field61_0x4c;
				}
				else if (index == -0x2710)
				{
					output = (LuaItem*)this->field10_0x10 + 0x17;
				}
				else if ((*this->field11_0x14[1] + 7) < -0x2712 - index)
				{
					output = &LuaItem_None_0065271c;
				}
				else
				{
					output = (LuaItem*)(*this->field11_0x14[1] + 0xC + (-0x2712 - index) * 8);
				}
			}
		}
		else
		{
			output = (LuaItem*)(this->table_0xc - 8 + index * 8);
			if (output > this->next_0x8)
				output = &LuaItem_None_0065271c;
		}

		return output;
	}

	// Returns the type of the item at indexKinda
	DWORD Lua_GetItemType(int index)
	{
		 LuaItem* pItem = this->Lua_GetItem(index);

		if (pItem == &LuaItem_None_0065271c)
			return (DWORD)-1;
		else
			return pItem->type;
	}

	// Returns the name of a type
	const char* Lua_StringTypeFromInt(DWORD type)
	{
		if (type == -1)
			return "no value";
		else
			return LuaTypes_0065284c[type];
	}

	LuaData* Lua_GetUserdata(int param_2)
	{
		LuaItem* pItem = this->Lua_GetItem(param_2);

		if (pItem->type == LT::userdata)
			return pItem->data;

		else if (pItem->type == LT::userdata_s)
			return (LuaData*) pItem->data[1].int_0x4;

		else
			return NULL;
	}

	void StructThing(astruct_169 * tableStruct)
	{
		tableStruct->end_0x0 = tableStruct + 3;
		tableStruct->unkn_0x4 = NULL;
		tableStruct->table_0x8 = this;
	}


};

// It's another structish where I guess the second pointer is the index of a special item, which should be a function
bool __fastcall Lua_IsFunction(LuaTable** in_EAX)
{
	DWORD type = (*in_EAX)->Lua_GetItemType((int)in_EAX[1]);
	return type == LT::function;
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

BYTE buffer_006a0af8[8192];

int bbOpenFile(char** param_1, astruct_142* param_2)
{
	char* pcVar1 = *param_1;
	char** ppcVar2 = (char**)GetItem(param_2->filenameList_0x4, param_2->filenameIndex_0x24);
	// Maybe it's a struct instead of array?
	if (!((int)ppcVar2[6] & 4))
	{
		if (!((int)ppcVar2[6] & 2))
		{
			if (ppcVar2[5] == NULL)
			{
				undefined4* puVar3;
				FILE* pFVar4 = fopen(*ppcVar2, "rb");
				ppcVar2[5] = (char*)pFVar4;
				if (pFVar4 == NULL)
				{
					puVar3 = (undefined4*)malloc(0x14);
					if (puVar3 != NULL)
					{
						*puVar3 = NULL;
						puVar3[1] = NULL;
						puVar3[2] = NULL;
						puVar3[3] = NULL;
						puVar3[4] = NULL;

						*puVar3 = param_2->unkn_0x14;
						puVar3[1] = 0x80F;
						puVar3[2] = param_2->filenameIndex_0x24;
						puVar3[3] = 0x900;
						//FUN_005f4fd0(param_1, pcVar1 + 0x1D4, pcVar1 + 0x1D8, puVar3, 0, 7);
					}
				bbOpenFileExit:
					//FUN_005f3650(param_1, param_2, 0);
					ppcVar2[6] = (char*)((uint)ppcVar2[6] | 8);
					ppcVar2[0x1E] = (char*)0x900;
					return 0;
				}
				int fileInfo = GetInfoOnFile();
				if (fileInfo) return fileInfo;

				//FUN_005f6150(ppcVar2 + 8);
				puVar3 = (undefined4*)malloc(0x14);
				if (puVar3 != NULL)
				{
					*puVar3 = NULL;
					puVar3[1] = NULL;
					puVar3[2] = NULL;
					puVar3[3] = NULL;
					puVar3[4] = NULL;

					*puVar3 = param_2->unkn_0x14;
					puVar3[1] = 0x80F;
					puVar3[2] = param_2->filenameIndex_0x24;
					puVar3[3] = 0x900;
					//FUN_005f4fd0(param_1, pcVar1 + 0x1D4, pcVar1 + 0x1D8, puVar3, 0, 7);
				}
			}
			if (ppcVar2[2] < ppcVar2[3])
			{
				do
				{
					if (*(param_2->unkn_0x20 + 0x30)) break;
					size_t sVar6 = fread(buffer_006a0af8, 1, 0x2000, (FILE*)ppcVar2[5]);
					if (sVar6)
					{
						//FUN_005f6a90(ppcVar8 + 8, buffer_006a0af8, sVar6);
						int iVar5 = 0;//FUN_005f45d0(buffer_006a0af8, sVar6);
						if (iVar5) return iVar5;

						param_2->size_0x3c += sVar6;
					}
				}
			}
		}
	}
}

// Some kind of generic Windows success error code
uint ERRORCODE_SUCCESS_00683798 = 0xBB40E64E;

void __fastcall GetInfoOnFile(int unaff_EBX, int unaff_ESI)
{
	uint errorCode = ERRORCODE_SUCCESS_00683798;
	uint uVar1 = fstat((*(int*)(unaff_EBX + 0x14) + 0x10), &local_68);

}

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

uchar* PTR_UCHAR_008d7860;
uchar STRING_008d7868[64]; // Don't know how big the string is yet
int INT_008da6e0;

void FUN_0054c610(char param_1, uchar* in_EAX)
{
	int* local_154;
	if (param_1 > -1  &&  PTR_008da72c != NULL)
	{
		PTR_008da72c->FUN_00559b00(in_EAX, &local_154);
		return;
	}

	// There's a lot of local variables being used before being initialized, are they supposed to be parameters?
	uchar local_104;
	SlashConvertString(&local_104, 0, in_EAX);

	uchar local_155 = NULL;
	PTR_UCHAR_008d7860 = NULL;

	struct _stat local_14c;
	SlashConvertString(&local_104, (int)&local_14c, in_EAX);

	int iVar2;

	if (_stat((const char*)&local_104, &local_14c) == 0)
	{
		local_155 = '\1';
		iVar2 = 0;
		uchar uVar1;
		do
		{
			uVar1 = (&local_104)[iVar2];
			(&STRING_008d7868)[iVar2];
			iVar2++;
		} while (uVar1 != NULL);
		PTR_UCHAR_008d7860 = (uchar*)&STRING_008d7868;
	}
	else if (INT_008da6e0 > 0)
	{
		SlashConvertString(&local_104, 0, in_EAX);
		iVar2 = 0;
		if (INT_008da6e0 > 0)
		{
			do
			{
				filename = FUN_0054c180();
				fileStatus = __stat(filename, (int*)())
			}
		}
	}


}

uchar* FUN_0054c180(int in_EAX)
{
	char* puVar6 = (&UINT_008d796c)[in_EAX];

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

FileObject* PTR_008da72c;

// My own addition to make reading this next function much easier.
// Macros to read different types from a char buffer at an offset.
#define ReadAsInt(buf, offset) (*(int*)(&buf[offset]))
#define ReadAsIntP(buf, offset) (*(int**)(&buf[offset]))
#define ReadAsByte(buf, offset) (*(BYTE*)(&buf[offset]))
#define ReadAsString(buf, offset) (&buf[offset])

void OpenBFS(LPCSTR filename, char** unaff_EDI)
{
	LPCSTR pCVar5 = filename;
	DWORD fileFlags;
	// bfsFile seems to be an all-purpose variable, first it's the handle of the file, then it's used to contain the size of the file, then it's used to point at the file's data.
	char* bfsFile;
	HANDLE pvVar3;
	FileObject* pAVar4;
	int aiStack_10[2];
	int iVar2;
	int iVar9;
	int* piVar7;
	int* piVar10;
	char cVar1;

	// Counting the length of a string
	do
	{
		cVar1 = *pCVar5;
		pCVar5 = pCVar5 + 1;
	} while (cVar1 != NULL);

	unaff_EDI[0x88] = NULL;

	fileFlags = FILE_ATTRIBUTE_NORMAL;

	if (UINT_008da730)
		fileFlags |= FILE_FLAG_DELETE_ON_CLOSE;

	bfsFile = (char*)CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, fileFlags, NULL);

	*unaff_EDI = bfsFile;
	if (bfsFile== NULL)
	{
		if (FUNC_008da6f4 != NULL)
			FUNC_008da6f4();

		CreateErrorMessageAndDie("Failed to open BFS archive: %s");
	}

	bfsFile = (char*)GetFileSize((HANDLE)bfsFile, NULL);
	if ((uint)bfsFile == 0xffffffff)
		CreateErrorMessageAndDie("Could not query file size for BFS archive: %s");

	pAVar4 = PTR_008da72c;
	unaff_EDI[1] = bfsFile;
	//FUN_0059b60(pAVar4, unaff_EDI, aiStack_10, 0, 0x10);

	// The file must start with the characters "bfsl"
	if (aiStack_10[0] != 0x31736662)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid id");

	// I don't know how, but it ends up with bfsFile pointing to the contents of the file
	unaff_EDI[0x84] = bfsFile;
	uint uStack_8 = 0;
	size_t _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
	HANDLE pvStack_4;
	unaff_EDI[0x85] = (char*)pvStack_4;
	uint* puVar7 = (uint*)malloc(_Size);
	pAVar4 = PTR_008da72c;
	unaff_EDI[0x82] = (char*)puVar7;
	//FUN_00559b60(pAVar4, unaff_EDI, puVar7, unaff_EDI[0x88], _Size);
	//pvVar6 = unaff_EDI[0x82];
	if ((int)uStack_8 < 0)
		//FUN_005610f0((int)&DAT_0069bd10, _Size - 0x10 >> 2);
		DoNothing();

	// The hash size located 16 bytes from the start, and must be 997.
	// If it has to be a known value, why include it in the file? Some kind of anti-tamper?
	if (ReadAsInt(bfsFile, 0x10) != 0x3E5)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

	unaff_EDI[0x86] = ReadAsString(bfsFile, 0x14);

	piVar10 = ReadAsIntP(bfsFile, 0x1F3C);
	piVar7 = (int*)malloc(0x14);
	if (piVar7 != NULL)
	{
		iVar9 = ReadAsInt(bfsFile, 8000);
		*piVar7 = *piVar10;
		iVar2 = ReadAsInt(bfsFile, 0x1F44);
		piVar7[1] = iVar9 + (int)piVar10;
		iVar9 = ReadAsInt(bfsFile, 0x1F48);
		piVar7[2] = iVar2 + (int)piVar10;
		iVar2 = ReadAsInt(bfsFile, 0x1F4C);
		piVar7[3] = iVar9 + (int)piVar10;
		piVar7[4] = iVar2 + (int)piVar10;
	}

	pvVar3 = unaff_EDI[0x88];
	unaff_EDI[0x87] = (char*)piVar7;
	bfsFile = (char*)((int)piVar10 + *piVar7);
	unaff_EDI[0x83] = bfsFile;
	if (pvVar3 != NULL)
	{
		for (char* pvVar10 = unaff_EDI[0x85]; pvVar10 != NULL; pvVar10--)
		{
			ReadAsInt(bfsFile, 4) += (int)pvVar3;

			// The second time's the charm.
			if ((bfsFile[1] != NULL) && (bfsFile[1] != NULL))
			{
				int i = 0;
				do
				{
					piVar7 = ReadAsIntP(bfsFile, i * 4 + 0x18);
					*piVar7 += (int)pvVar3;
					i++;
				} while (i < ReadAsByte(bfsFile, 1));
			}
			bfsFile += ReadAsByte(bfsFile, 1) * 4 + 0x18;
		}
	}
	return;
}

void InitOpenBFS(LPCSTR lpFilename, char** in_EAX)
{
	void* pvVar2 = malloc(0x224);
	void* uVar3;
	if (pvVar2 == NULL)
		uVar3 = NULL;
	else
		OpenBFS(lpFilename, in_EAX);

	//if (in_EAX[2] == in_EAX[1])
		//FUN_00434840();

	in_EAX[1] += 4;

	return;
}

bool WriteCharToStream(char in_char, FILE* file)
{
	return fputc(in_char, file) != -1;
}

// Still confused about this one
uint SetFPUCW(ushort in_FPUControlWord)
{
	uint copyOfWhat;

	copyOfWhat = unkn_008da6a0 >> 16;
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

void CreateErrorMessageAndDie(const char* message, ...)
{
	char local_800[1024];
	char body[1024];

	// The list of arguments to put into the message is the rest of the CPU stack, meaning the inputs of the last-called function.
	// I'm not quite sure how that works, I'm new to the ... operator
	va_list list;
	va_start(list, message);

	vsprintf(local_800, message, list);
	sprintf(body, "%s", local_800);
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

// The no jumptable
void (*NOJMPTABLE_0067ad08[58])() = {};

// Instead of writing all that out I'll replace it with code that would do the same thing
// 56 of them are ExitWithCode25, and the last one is FUN_0054c970, I don't know about that one yet.
void CreateThatWeirdJumpTable()
{
	for (int i = 0; i < 57; i++)
		NOJMPTABLE_0067ad08[i] = ExitWithCode25;

	//NOJMPTABLE_0067ad08[57] = FUN_0054c970;
}


void* DoNotCallEver(void *in_mem, int bFree)
{
	// Seems like a default value maybe.
	in_mem = &JMPTABLE_0067b1c0;
	CreateErrorMessageAndDie("Must not be called - ever.");

	// Does not return, so the rest of this never happens.
	// But if it did, this jump table would be replaced with one where every function will exit with error code 25.
	// If it didn't create the message, it would just silently crash anyways.
	in_mem = &NOJMPTABLE_0067ad08;
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
// Misc.
// 
/////////////////////////////////////////////////

void memsetWithOffset(void** Dst, uint Offset, int Val, size_t Size)
{
	memset((void*)((uint)(*Dst) + Offset), Val, Size);
	return;
}

undefined4 Depointerize(undefined4* output)
{
	return *output;
}

