#include "MrWonkoFileObject.h"
#include <string>

// Writes a section of the file to it's handle, given the buffer and desired bytes to write. Returns the number of bytes actually written for comparison.
// Updates realFilePos and filePos to point after the written bytes.
DWORD MWFileObject::WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite)
{
	DWORD bytesWritten;
	DWORD totalBytesWritten = 0;
	HANDLE hFile;
	DWORD tempToWrite;

	if (bytesToWrite != 0)
	{
		hFile = this->handle;

		for (int d = bytesToWrite; d; d -= tempToWrite)
		{
			// Writes in 64 KB chunks
			tempToWrite = 0xFFFF;
			if (d < 0x10000)
				tempToWrite = d;

			WriteFile(hFile, buffer, tempToWrite, &bytesWritten, NULL);
			buffer = (LPCVOID)((int)buffer + tempToWrite);
			totalBytesWritten += bytesWritten;
		}
	}

	// I just noticed, it uses bytesToWrite instead of totalBytesWritten, so it'll skip too far if it couldn't write everything.
	this->realFilePos += bytesToWrite;
	this->filePos += bytesToWrite;
	return totalBytesWritten;
}

void MWFileObject::bbSetFilePointer(int newLoc)
{
	if (this->realFilePos != (char*)newLoc)
	{
		this->realFilePos = (char*)newLoc;
		SetFilePointer(this->handle, newLoc, NULL, FILE_BEGIN);
	}
	return;
}

// FileObject_New() is a more complicated version of FileObject_Create()
MWFileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX)
{
	MWFileObject* output = NULL;
	// Checking if it's reading an existing file or not
	if ((flags_unaff_EBX & 1) == 0)
	{
		MWFileObject* newFile = (MWFileObject*)malloc(sizeof(MWFileObject));
		if (newFile != NULL)
		{
			newFile->filePos = NULL;
			newFile->realFilePos = NULL;
			newFile->handle = NULL;
			newFile->filename1 = NULL;
			newFile->fileattributes = NULL;
			//piVar2->vtable = JMPTABLE_0067b6f8;
			newFile->usuallyNeg1 = -1;
			output = newFile;
		}
		// It's outside the if statement, which will try to access output even when it's NULL.
		output->Create(filename_unaff_EDI, flags_unaff_EBX);
	}
	else
	{
		struct _stat result;
		int iVar1 = _stat(filename_unaff_EDI, &result);

		if (iVar1 == 0)
		{
			MWFileObject* pAVar2 = (MWFileObject*)malloc(sizeof(MWFileObject));
			if (pAVar2 != NULL)
			{
				FileObject_ClearEAX(pAVar2);
				output = pAVar2;
			}
			// They did it again
			output->Create(filename_unaff_EDI, flags_unaff_EBX);
			void* pvStack_18;
			//output->size = pvStack_18;
			return output;
		}
	}
	return output;
}

void MWFileObject::Create(LPCSTR lpFilename, uint flags)
{
	DWORD desiredAccess = 0;
	DWORD creationDisposition = 0;
	bool bRead = flags & 1;
	if (bRead)
	{
		desiredAccess = GENERIC_READ;
		creationDisposition = OPEN_EXISTING;
	}
	DWORD shareMode = bRead;
	DWORD flagsAndAttributes = bRead;
	if (flags & 2)
	{
		desiredAccess |= GENERIC_WRITE;
		creationDisposition |= CREATE_ALWAYS;
		flagsAndAttributes |= FILE_ATTRIBUTE_NORMAL;
		shareMode = FILE_SHARE_READ;
	}
	HANDLE handle = CreateFileA(lpFilename, desiredAccess, shareMode, NULL, creationDisposition, flagsAndAttributes, NULL);
	this->fileattributes = flags;
	this->handle = handle;
	//if ((handle == NULL) && (FUNC_008da6f4 != NULL))
		//(*FUNC_008da6f4)();

	return;
}


// If mode is 1, It'll just set the file pos with no fuss.
// If mode is 2, It'll treat the file pos relative to the end.
// If mode is 0, checks a flag in the attributes and if it's cleared, read from the file in, a way.
void MWFileObject::SetFilePos(int newPos, int mode)
{
	switch (mode)
	{

	case 0:
		if ((this->fileattributes & 0x100) == 0)
		{
			char* pcVar1 = this->filePos;
			/*
			for (int iVar2 = this->usuallyNeg1; iVar2 < (int)(pcVar1 + newPos) >> 14; iVar2++)
				if (iVar2 > -1)
					this->FileObject_Read(iVar2);
			*/
		}
		break;

	case 1:
		this->filePos = (char*)newPos;
		break;

	case 2:
		this->filePos = (char*)((int)this->size - newPos);

	}
	return;
}

void MWFileObject::FlushBuffers()
{
	FlushFileBuffers(this->handle);
}

// This would make sense if the filePos was private, but it has to be public to be accessed by the FileObject_ClearEAX() function.
// It might not be a C++ class anyways so did they go through the trouble of integrating public/private distinction in their own class?
char* MWFileObject::GetFilePosButLikeWhy()
{
	return this->filePos;
}


bool MWFileObject::AtEndOfFile()
{
	return ((int)this->filePos > 0) && (this->size <= this->filePos);
}

int MWFileObject::GetSize()
{
	return (this->size == (void*)-1) ? (int)this->filePos : (int)this->size;
}

void MWFileObject::Clear()
{
	this->usuallyNeg1 = -1;
	this->filePos = NULL;
	this->realFilePos = NULL;
	this->handle = NULL;
	this->filename1 = NULL;
	this->filename2 = NULL;
	return;
}

void __fastcall MWFileObject::Close()
{
	if (this->handle != NULL)
	{
		CloseHandle(this->handle);
		this->handle = NULL;
	}
	return;
}

MWFileObject* MWFileObject::ResetMaybe(int bFree)
{
	//this->vtable = JMPTABLE_0067b6f8;
	if (this->handle != NULL)
	{
		CloseHandle(this->handle);
		this->handle = NULL;
	}
	if (bFree & 1)
		free(this);

	return this;
}

void __fastcall FileObject_ClearEAX(MWFileObject* in_EAX)
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

void MWFileObject::DoNothing()
{
	return;
}