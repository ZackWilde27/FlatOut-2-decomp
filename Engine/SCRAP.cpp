/////////////////////////////////////////////////
// 
// SCRAP Engine
// 
/////////////////////////////////////////////////

// My decompilation of FlatOut 2's ROMU
// Code will be moved here when I find it in the other games

// ROMU is always spelled with capitals, so I assumed it was an acronym, but it turns out it's the finnish word for scrap metal.
// SCRAP it is.
#include "SCRAP2.h"

// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// I checked, and I guess they considered the changes to be very small
// ROMU v0.28b
const char* verString_00698b4c = "Version 0.28 build 2004.09.20";




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

// Goes along the string until it reaches the end or finds a difference and returns the difference between the characters in integer value.
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

// My own addition to make other functions easier to read
bool String_Equal(char* string1, char* string2, uint lengthOfString1)
{
	bool theSame = true;
	uint iterations = lengthOfString1;
	do
	{
		if (iterations == 0) break;
		iterations--;
		theSame = *string1 == *string2;
		string1++;
		string2++;
	} while (theSame);
	return theSame;
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
// I just decided to replace them with a GetLength call
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
		out_string++;
		in_string++;
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
		} while (--length);
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
	*((uint*)_Dest[0x430]) = param_2;
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
// then it will treated as a hex string
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
			*outFloat = (float)(ulonglong)strtoul(stringFloat, &EndPtr, 16);

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
// Debug
// 
/////////////////////////////////////////////////



void CreateErrorMessageAndDie(const char* message, ...)
{
	char temp[1024];
	char body[1024];

	// The list of arguments to put into the message is the rest of the CPU stack, meaning the inputs of the last-called function.
	// I'm not quite sure how that works, I'm new to the ... operator
	va_list list;
	va_start(list, message);

	vsprintf(temp, message, list);
	sprintf(body, "%s", temp);
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
	//_amsg_exit(25);
}

// The normal jumptable
// In FO2 Ghidra did not find a name for it,
// but in FOUC it's apparently a LiteDb void function table.
// LiteDb is a database library which makes sense, but the oldest mention of LiteDb I can find is from 2014, and the oldest release I can find is from 2015.
// Were they using LiteDb back in 2003? Did they go back and upgrade it to LiteDb in 2009? Or was it just a false positive on Ghidra's part?
void (*LiteDb_vftable_0067b1c0[])() = {
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

// FO1 does not have this function, either because it doesn't exist or it's not blocked off.
// Wreckfest does not appear to have this function, although there is something similar, immediately crashes with "Not implemented"
void* DoNotCallEver(void* jmpTable, int bFree)
{
	// Seems like a default value maybe.
	jmpTable = &LiteDb_vftable_0067b1c0;
	CreateErrorMessageAndDie("Must not be called - ever.");

	// If you bypassed the error message in FO2, this jump table would be replaced with one where every function will exit with code 25.
	// I checked, and bypassing the error message just silently crashes anyways.
	jmpTable = &NOJMPTABLE_0067ad08;
	if (bFree)
		free(jmpTable);

	return jmpTable;

}



/////////////////////////////////////////////////
// 
// LuaTable
//
/////////////////////////////////////////////////

// I'm finally starting to understand this one, I think
// There are a lot of functions where the first parameter is a pointer to this struct, even if they don't reference it, leading me to believe it's part of a class/bugbear method system.
// I'll just make it a C++ class to make things easier.


uint LuaTable::AttemptToYield(int index)
{
		if (this->bDebug_0x34)
			//this->LuaLogMaybe("attempt to yield across metamethod/C-call boundary");
			DoNothing();

		this->table_0xc = this->next_0x8 + (index * -2);
		this->field7_0x6 = 1;
}

void LuaTable::Lua_AddNilProperty()
{
	// No bounds checking, If there's a way to access this function from lua it would be interesting to see what happens if this is spammed.
	this->next_0x8->type = LT::nil;
	// For some reason I thought the 2 meant 2 pointers length, but now I don't understand what it means.
	// This would overwrite memory it's already written when repeated, it clears 4 bytes while only advancing 2 bytes.
	this->next_0x8 += 2;
}

void LuaTable::Lua_ActuallyAddStringProperty(char* data, size_t dataLength)
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
	this->next_0x8 += 2;
}

void LuaTable::Lua_AddStringProperty(char* in_string)
{
	if (in_string == NULL)
		this->Lua_AddNilProperty();
	else
		this->Lua_ActuallyAddStringProperty(in_string, String_GetLength(in_string));

	return;
}

void LuaTable::Lua_AddBoolProperty(bool in_bool)
{
	LuaItem* pNext = this->next_0x8;
	pNext->data = (void*)in_bool;
	pNext->type = LT::boolean;
	this->next_0x8 += 2;
}

// Seems like astruct_114 has several different tables, or maybe it's like one big table that has temporary pointers
// If the index is equal to or greater than 1:
//		The 1-based index into table_0xc
// If index is less than 1, it's compared to specific values to determine the list to return. These numbers seem arbitrary and I wonder if part of the number is a flag.
//		-0x2712 : field56_0x44
//		-0x2711 :  some math involving field11_0x14
//		-0x2710 : table_0x10 + 0x17

LuaItem* LuaTable::Lua_GetItem(int index)
{
	LuaItem* output;
	if (index < 1)
	{
		if (index < -0x270F)
		{

			switch (index)
			{

			case -0x2710:
				output = (LuaItem*)this->field10_0x10 + 0x17;
				break;

			case -0x2711:
				this->field61_0x4c = *(int*)(*this->field11_0x14[1] + 0xC);
				this->field62_0x50 = 5;
				output = (LuaItem*)&this->field61_0x4c;
				break;

			case -0x2712:
				output = this->table_0x44;
				break;

			default:
				if ((*this->field11_0x14[1] + 7) < -0x2712 - index)
					output = &LuaItem_None_0065271c;
				else
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

// Returns the type of the item at index
int LuaTable::Lua_GetItemType(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);

	if (pItem == &LuaItem_None_0065271c)
		return (int)-1;

	return pItem->type;
}

bool LuaTable::Lua_StringFromNumber(LuaItem* pItem)
{
	char local_28[4];

	if (pItem->type == LT::number)
	{
		float num = *(float*)&pItem->data;
		sprintf(local_28, "%.5g", num);

		//pItem->data = this->Lua_NewStringStructMaybe(local_28, String_GetLength(local_28))

		pItem->type = LT::string;
		return true;
	}
	
	return false;
}

bool LuaTable::Lua_IsNumber(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type != LT::number)
	{
		LuaItem tempItem;
		return Lua_NumberFromString(pItem, &tempItem) != NULL;
	}
	return true;
}

bool LuaTable::Lua_IsUserData(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	return pItem->type == LT::userdata_s || pItem->type == LT::userdata;
}



LuaItem* LuaTable::Lua_NumberFromString(LuaItem* pStringItem, LuaItem* pNewNumberItem)
{
	if (pStringItem->type != LT::number)
	{
		float local_8;
		// So endPtr_0x10 is not a pointer to the string, it is the string.
		if (pStringItem->type == LT::string && StringToNum((char*)&((LuaString*)pStringItem->data)->endPtr_0x10, &local_8))
		{
			pNewNumberItem->data = local_8;
			pNewNumberItem->type = LT::number;
			pStringItem = pNewNumberItem;
		}
		else
			pStringItem = NULL;
	}
	return pStringItem;
}

float LuaTable::Lua_GetNumber(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	LuaItem tempItem;
	if (pItem->type != LT::number && (pItem = Lua_NumberFromString(pItem, &tempItem), pItem == NULL))
	{
		return 0.f;
	}
	return *(float*)&pItem->data;
}


bool LuaTable::Lua_GetBool(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type == LT::boolean)
		return pItem->data != 0;

	return pItem->type != LT::nil;
}


uint __fastcall Lua_GetVersion(LuaTable** table_EAX, int unaff_ESI)
{
	int type = table_EAX[0]->Lua_GetItemType((int)table_EAX[1]);
	if (type == LT::boolean)
		return table_EAX[0]->Lua_GetBool((int)table_EAX[1]);

	float data = table_EAX[0]->Lua_GetNumber((int)table_EAX[1]);

	// Some intense bit manipulation is about to happen
	uint intForm = *(uint*)&data;
	type = intForm >> 23;
	type &= 0xFF;
	type -= 0x7F;

	// What
	return (((intForm | 0xFF800000) << 8) >> (0x1F - (uchar)type & 0x1F) ^ intForm >> 31) - intForm >> 31 & ~(type >> 31);
}

int LuaTable::Lua_StringItemRelated(int index, undefined4* param_3)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type != LT::string)
	{
		if (Lua_StringFromNumber(pItem) == 0)
		{
			if (param_3 != NULL)
				*param_3 = NULL;

			return 0;
		}
		//if (this->field10_0x10[0x10] <= this->field10_0x10[0x11])
			//this->FUN_005ba3a0();
		pItem = this->Lua_GetItem(index);
	}
	if (param_3 != NULL)
		*param_3 = (uint)((LuaString*)(pItem->data))->startPtr_0xc;

	return (int)&((LuaString*)(pItem->data))->endPtr_0x10;
}

char* LuaTable::Lua_GetItemAsString(int index)
{
	char* result;
	LuaItem* pItem = this->Lua_GetItem(index);
	switch (pItem->type)
	{

	case LT::number:
		if (Lua_StringFromNumber(pItem) == 0)
			result = NULL;
		else
			result = ((LuaString*)(pItem->data))->startPtr_0xc;
		break;

	case LT::string:
		result = ((LuaString*)(pItem->data))->startPtr_0xc;
		break;

	case LT::table:
		//result = FUN_005c0510(pItem->data);
		break;

	default:
		result = NULL;
		break;

	case LT::userdata_s:
		// It's been put after default so it's not possible to reach here.
		result = ((LuaUserData*)pItem->data)->string_0x10;
	}
	return result;
}

// Returns the name of a type
const char* LuaTable::Lua_StringTypeFromInt(int type)
{
	if (type == -1)
		return "no value";
	else
		return LuaTypes_0065284c[type];
}

struct LuaUserDataS
{
	// 8 undefined bytes at offset 0x0, probably a vftable
	LuaUserData* userdata_0x8;
};

// I'm not sure if the userdata uses the same struct as the strings
LuaUserData* LuaTable::Lua_GetUserdata(int param_2)
{
	LuaItem* pItem = this->Lua_GetItem(param_2);

	if (pItem->type == LT::userdata)
		return (LuaUserData*)pItem->data;

	else if (pItem->type == LT::userdata_s)
		// The LuaUserData struct is hidden inside another struct
		return ((LuaUserDataS*)pItem->data)->userdata_0x8;

	else
		return NULL;
}

// Pads the table if the newLength is greater than length
// If the newLength is the same as the current length, this function will instead add 65535 nil items due to the pre-decrement
void __fastcall Lua_PadTableIfNeeded(int newLength, LuaTable*** unaff_EDI)
{
	int length = (*unaff_EDI[1])->Lua_GetTableLength();
	if (length < newLength)
	{
		int i = newLength - length;
		do
			(*unaff_EDI[1])->Lua_AddNilProperty();
		while (--i);
	}
}

bool LuaTable::Lua_IsItemAStringOrNumber(int index)
{
	DWORD itemType = this->Lua_GetItemType(index);
	return (itemType == LT::string || itemType == LT::number);
}

bool LuaTable::Lua_ItemsEqual_s(int index1, int index2)
{
	LuaItem* pItem1 = this->Lua_GetItem(index1);
	LuaItem* pItem2 = this->Lua_GetItem(index2);

	if (pItem1 == &LuaItem_None_0065271c || pItem2 == &LuaItem_None_0065271c)
		return false;
	else
		return Lua_ItemsEqual(pItem1, pItem2);
}

// This function does not do what I think it's supposed to, it raises an error when the given item is not the given type,
// but ReportError() will discard expectedType and call GetItemType() again to report the error, which was just confirmed to be the wrong type.
void LuaTable::Lua_ThrowIfIndexIsNotGivenType(int index, int expectedType)
{
	if (this->Lua_GetItemType(index) != expectedType)
		this->Lua_ReportError(index, expectedType);
}

void LuaTable::Lua_ReportError(int index, int expectedType)
{
	this->Lua_ReportErrorForReal(index);
}

void LuaTable::Lua_ReportErrorForReal(int index)
{
	DWORD type = this->Lua_GetItemType(index);
	this->Lua_StringTypeFromInt(type);
	//this->Lua_AnotherLoggingFunction("%s expected, got %s");
	//this->Lua_ErrorHandling();
}


// Okay, maybe this LuaTable does more than store tables.
uint LuaTable::Lua_KickPlayer()
{
	this->Lua_ThrowIfIndexIsNotGivenType(1, LT::userdata_s);

	LuaUserData* pUserData = (LuaUserData*)this->Lua_GetUserdata(1);
	if (pUserData == NULL)
		this->Lua_ReportErrorForReal(1);

	// Function pointers have nothing on function pointers inside function pointers
	void (**vftable1)(void(***)()) = pUserData->vftable;

	pUserData = (LuaUserData*)this->Lua_GetUserdata(2);
	// To avoid a paradoxical declaration, the second vftable will have to be a different type at first
	void (**vftable2)() = (void (**)())pUserData->vftable;

	undefined4 local_4 = pUserData->unkn_0x4;
	vftable1[12](&vftable2);
}

void LuaTable::StructThing(astruct_169* tableStruct)
{
	tableStruct->end_0x0 = tableStruct + 3;
	tableStruct->unkn_0x4 = NULL;
	tableStruct->table_0x8 = this;
}

// It's dividing by 8, makes sense now
int LuaTable::Lua_GetTableLength()
{
	return this->next_0x8 - this->table_0xc >> 3;
}




// It's another structish where I guess the second pointer is the index of a special item, which should be a function
bool __fastcall Lua_IsFunction(LuaTable** in_EAX)
{
	DWORD type = in_EAX[0]->Lua_GetItemType((int)in_EAX[1]);
	return type == LT::function;
}

#define SafeEquals(floatA, floatB) ((isnan(floatA) || isnan(floatB)) != (floatA == floatB))

bool Lua_ItemsEqual(LuaItem* pItem1, LuaItem* pItem2)
{
	bool equal;
	if (pItem1->type == pItem2->type)
	{
		switch (pItem1->type)
		{
		case LT::nil:
			equal = true;
			break;

		case LT::boolean:
		case LT::userdata:
			equal = pItem1->data == pItem2->data;
			break;

		case LT::number:
			equal = SafeEquals(pItem1->data, pItem2->data);
			break;

		default:
			equal = pItem1->data == pItem2->data;
		}
	}
	else
		equal = false;

	return equal;
}

int LuaTable::JoinCurrentSession()
{
	if (this->Lua_GetItemType(1) != LT::nil)
		this->Lua_GetUserdata(1);
	return 0;
}

int LuaTable::JoinSessionFromCommandLine()
{
}

char* String_IndexOf(char* string, char theChar)
{
	// Searches within a max of 2 characters depending on where the string is located in memory.
	// address ends with 0 or C: does not search
	// address ends with 4: searches 1 char
	// address ends with 8: searches 2 chars
	DWORD parityish = (DWORD)string & 3;
	while (parityish != 0)
	{
		if (*string == theChar)
			return string;

		if (*string == NULL)
			return NULL;

		string++;
		parityish = (DWORD)string & 3;
	}
	// That's the indexOf part, I don't know what the rest of this function is for though.

	uint uVar1;
	while (true)
	{
		while (true)
		{
			uVar1 = *(uint*)string;
			uint uVar4 = uVar1 ^ (theChar << 24 | theChar << 16 | theChar << 8 | theChar);
			uint uVar3 = uVar1 ^ ((uint)-1) ^ uVar1 + 0x7EFEFEFF;

		}
	}
		
}


/////////////////////////////////////////////////
// 
// File System
//
/////////////////////////////////////////////////

// Writes a section of the file to it's handle, given the buffer and desired bytes to write. Returns the number of bytes actually written for comparison.
// Updates realFilePos and filePos to point after the written bytes.
DWORD FileObject::FileObject_WriteFileToHandle(LPCVOID buffer, DWORD bytesToWrite)
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
			tempToWrite = 0xFFFF;
			if (d < 0x10000)
				tempToWrite = d;

			WriteFile(hFile, buffer, tempToWrite, &bytesWritten, NULL);
			buffer = (LPCVOID)((int)buffer + tempToWrite);
			totalBytesWritten += bytesWritten;
		}
	}
	// Advance the pointers
	// I just noticed, it uses bytesToWrite instead of totalBytesWritten, so it'll skip too far if it couldn't write everything.
	this->realFilePos = this->realFilePos + bytesToWrite;
	this->filePos = this->filePos + bytesToWrite;
	return totalBytesWritten;
}

void FileObject::FileObject_SetFilePointer(int newLoc)
{
	if (this->realFilePos != (char*)newLoc)
	{
		this->realFilePos = (char*)newLoc;
		SetFilePointer(this->handle, newLoc, NULL, FILE_BEGIN);
	}
	return;
}

// FileObject_New() is a more complicated version of FileObject_Create()
FileObject* FileObject::FileObject_New(uint unaff_EBX, const char* filename_unaff_EDI)
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
		// It's outside the if statement, which will try to access output even when it's un-initialized.
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
			// They did it again
			output->FileObject_Create();
			void* pvStack_18;
			output->size = pvStack_18;
			return output;
		}
	}
	return output;
}

void FileObject::FileObject_Create(LPCSTR lpFilename, uint flags)
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
	if ((handle == NULL) && (FUNC_008da6f4 != NULL))
		(*FUNC_008da6f4)();

	return;
}

// If mode is 1, It'll just set the file pos with no fuss.
// If mode is 2, It'll treat the file pos relative to the end.
// If mode is 0, checks a flag in the attributes and if it's set, read from the file in, a way.
void FileObject::FileObject_SetFilePos(int newPos, int mode)
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

void FileObject::FileObject_FlushBuffers()
{
	FlushFileBuffers(this->handle);
}

// This would make sense if the filePos was private, but it has to be public to be accessed by the FileObject_ClearEAX() function.
// It might not be a C++ class anyways so did they go through the trouble of integrating public/private distinction in their own class?
char* FileObject::FileObject_GetFilePosButLikeWhy()
{
	return this->filePos;
}

bool FileObject::FileObject_IsFilePosBeyond()
{
	return ((int)this->filePos > 0) && (this->size <= this->filePos);
}

int FileObject::FileObject_GetSize()
{
	return (this->size == (void*)-1) ? (int)this->filePos : (int)this->size;
}

void FileObject::FileObject_Clear()
{
	this->usuallyNeg1 = -1;
	this->filePos = NULL;
	this->realFilePos = NULL;
	this->handle = NULL;
	this->filename1 = NULL;
	this->filename2 = NULL;
	return;
}

void __fastcall FileObject::FileObject_Close()
{
	if (this->handle != NULL)
	{
		CloseHandle(this->handle);
		this->handle = NULL;
	}
	return;
}

FileObject* FileObject::FileObject_ResetMaybe(int bFree)
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


void (*FUNC_008da6f4)();
FileObject* PTR_008da72c;
uint UINT_008da730;

// My own addition to make reading this next function much easier.
// Macros to read different types from a char buffer at an offset.
#define ReadAsInt(buf, offset) (*(int*)(&buf[offset]))
#define ReadAsIntP(buf, offset) (*(int**)(&buf[offset]))
#define ReadAsByte(buf, offset) (*(BYTE*)(&buf[offset]))
#define ReadAsString(buf, offset) (&buf[offset])

void OpenBFS(LPCSTR filename, YetAnotherFileObject* unaff_EDI)
{
	HANDLE pvVar3;
	int aiStack_10[2];
	int iVar2;
	int iVar9;

	// The length of the filename is calculated, but it's never used.
	String_GetLength((char*)filename);

	// Very large structure
	unaff_EDI[0x88] = NULL;

	DWORD fileFlags = FILE_ATTRIBUTE_NORMAL;

	if (UINT_008da730)
		fileFlags |= FILE_FLAG_DELETE_ON_CLOSE;

	// bfsFile seems to be an all-purpose variable, first it's the handle of the file, then it's used to contain the size of the file, then it's used to point at the file's data.
	char* bfsFile = (char*)CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, fileFlags, NULL);

	unaff_EDI->handle_0x0 = bfsFile;
	if (bfsFile == NULL)
	{
		if (FUNC_008da6f4 != NULL)
			FUNC_008da6f4();

		CreateErrorMessageAndDie("Failed to open BFS archive: %s");
	}

	bfsFile = (char*)GetFileSize((HANDLE)bfsFile, NULL);
	if ((int)bfsFile == -1)
		CreateErrorMessageAndDie("Could not query file size for BFS archive: %s");

	FileObject* pAVar4 = PTR_008da72c;
	unaff_EDI->size_0x4 = (int)bfsFile;
	//FUN_0059b60(PTR_008da72c, unaff_EDI, aiStack_10, 0, 0x10);

	// The file must start with the characters "bfsl"
	if (aiStack_10[0] != 0x31736662)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid id");

	// I don't know how, but it ends up with bfsFile pointing to the contents of the file
	/*
	unaff_EDI[0x84] = bfsFile;
	uint uStack_8 = 0;
	size_t _Size = (int)(HANDLE)(uStack_8 & 0x7FFFFFFF) + 3U & 0xFFFFFFFC;
	HANDLE pvStack_4;
	unaff_EDI[0x85] = (char*)pvStack_4;
	uint* puVar7 = (uint*)malloc(_Size);
	pAVar4 = PTR_008da72c;
	unaff_EDI[0x82] = (char*)puVar7;
	//FUN_00559b60(PTR_008da72c, unaff_EDI, puVar7, unaff_EDI[0x88], _Size);
	//pvVar6 = unaff_EDI[0x82];
	if ((int)uStack_8 < 0)
		FUN_005610f0((int)&DAT_0069bd10, _Size - 0x10 >> 2);
	*/

	// The hash size located 16 bytes from the start, and must be 997.
	// If it has to be a known value, why include it in the file? Some kind of anti-tamper?
	if (ReadAsInt(bfsFile, 0x10) != 0x3E5)
		CreateErrorMessageAndDie("BFS archive <%s> has invalid hash size (%d)");

	unaff_EDI[0x86] = ReadAsString(bfsFile, 0x14);

	int* piVar10 = ReadAsIntP(bfsFile, 0x1F3C);
	int* piVar7 = (int*)malloc(0x14);
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

			// The ghidra code uses a second comparison like a trick to set i during the if. I chose to do it afterwards, is it any different?
			// && (i = 0, bfsFile[1] != NULL)
			// If that's all it was for I can probably just remove it
			if ((bfsFile[1] != NULL))
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



// MISC

// So far I've found 8 copies of this function in different spots, maybe they are different types of empty PROC functions?
void DoNothing()
{
	return;
}

// Maybe this is an assembly function?
void* Depointerize(void** pointer)
{
	return *pointer;
}



