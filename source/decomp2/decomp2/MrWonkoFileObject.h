#pragma once

#include "Macros.h"
#include <windows.h>

// Thanks to mrwonko on GitHub for their file object reverse engineering
// There's more than one file object, so this one is the MrWonkoFileObject
class MWFileObject
{
public:
	void (**vtable)();
	// Array of functions, methods if you will. unused in my implementation because I made it a class instead

	char buffer[0x4000]; // 0x4

	int usuallyNeg1;           // 0x4004 - is -1 on newly opened track_spvs.gen,
	// I've just discovered a function that changes it, I'm still figuring this one out.

	char* filePos;         // 0x4008 - "virtual" file pos - reads in 16kb blocks internally, but allows for arbitrary reads

	char* realFilePos;     // 0x400C - real file's filePos, gets increased by bytesRead
	void* size;        // 0x4010 - returned by BvhFile_Func8 unless it's -1 - *0x4008 otherwise
	HANDLE handle;      // 0x4014
	uint fileattributes;         // 0x4018 - flags describing the file

	char* filename1; // 0x401C
	char* filename2; // 0x4020
	// Two different filename properties (maybe), I'm thinking it's for objects that need to load both a model and texture file?

	DWORD WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite);
	void bbSetFilePointer(int newLoc);
	void Create(LPCSTR lpFilename, uint flags);
	void SetFilePos(int newPos, int mode);
	void FlushBuffers();
	char* GetFilePosButLikeWhy();
	bool AtEndOfFile();
	int GetSize();
	void Clear();
	void __fastcall Close();
	void DoNothing();
	MWFileObject* ResetMaybe(int bFree);
};

// there's another class based off the original one.
class MW2FileObject : MWFileObject
{
private:
	undefined4 unkn_0x4028;
	undefined4 unkn_0x402c;
	undefined4 unkn_0x4030;
	// 0x72 undefined bytes at offset 0x4034
	undefined4 unkn_0x407c;
	undefined4 unkn_0x4084;

public:
};

void __fastcall FileObject_ClearEAX(MWFileObject* in_EAX);