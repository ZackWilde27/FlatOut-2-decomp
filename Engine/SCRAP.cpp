/////////////////////////////////////////////////
// 
// SCRAP Engine
// 
/////////////////////////////////////////////////

// My on-going recreation of ROMU based on decompiling FlatOut 2

// ROMU is always spelled with capitals, so I assumed it was an acronym, but it turns out it's the finnish word for scrap metal.
// SCRAP it is.
#include "SCRAP.h"

// Code will be moved here when I find the same functions, structs, or classes in the other games, or when it depends on functions, structs, or classes already in here.
// It's extremely similar to 1 and UC's ROMU but there are enough changes, especially in the locations of things that it would make more sense to re-write it to match each game.


// This build is dated September 20th, 2004, which is a couple months before FlatOut 1 released.
// I checked, and they forgot to update the string, unless they considered the changes to be that small.
// SCRAP v0.28b
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
// If mode is 3, or g_slashOverride is 0, it'll convert slashes to backslashes and vise-versa
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
			{
				if (currentChar == '/')
					currentChar = '\\';
				else if (currentChar == '\\')
					currentChar = '/';
			}
				

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

// The same as String_Compare except safer.
// but if string2's length is less than maxLength, it'll produce an unintended result.
int String_Compare_s(char* string1, char* string2, int maxLength)
{
	char char1, char2;
	int iVar3 = 0;

	do
	{
		char1 = *string1;
		char2 = *string2;
		string1++;
		string2++;
		iVar3++;

		if (char1 == NULL || char1 != char2) break;

	} while (iVar3 < maxLength);

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

			out_string++;
			length--;
		} while (length > 0);
	}
	return NULL;
}

// They have a String_GetLength function but there are a lot of places that counted the string manually.
// Did the person who wrote this forget to tell anyone else about it? Was it written later and those functions were already implemented?
// I just decided to replace them with a GetLength call
int String_GetLength(const char* in_string)
{
	char* tempPtr = (char*)in_string;
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
// Finds the first NULL in the out_string and starts copying from there.
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

void static CopyStringToPointerToString(char** out_string, const char* in_string)
{
	char* _Dest;
	_Dest = *out_string;
	strncpy(_Dest, in_string, 0x100);
	_Dest[0xFF] = NULL;
	return;
}

// It's the same as Microsoft's tolower() except 'A' - 'a' is precalculated, happens to be the space character.
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
// Sweeps through as if it's a string, but when it does the comparison it casts both of them to integer pointers, so it'll compare 4 characters each time.
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
			while (isspace(*EndPtr))
				EndPtr++;

			nullTerminated = *EndPtr == NULL;
		}
	}

	return nullTerminated;
}

static char* String_IndexOfAlmost(char* string, char theChar)
{
	// This function has 3 stages:
	// The first stage is a strange indexOf where it only checks a few characters based on the location of the string in memory.
	// The second stage makes no sense to me, it's both heavily obfuscated and probably needs more context.
	// The third stage is a standard indexOf, but it only checks 4 characters
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


	uint uVar1, uVar3, uVar4;
	char* pcVar5;
	char tempChar;
	while (true)
	{
		while (true)
		{
			// What is even going on in this first loop
			uVar1 = *(uint*)string;
			// Checks if the string has 4 of theChar in a row
			uVar4 = uVar1 ^ (theChar << 24 | theChar << 16 | theChar << 8 | theChar);

			// (x XOR y XOR x) gives you y. This could have just been 0x7EFEFEFE
			//uVar3 = uVar1 ^ ((uint)-1) ^ uVar1 + 0x7EFEFEFF;
			uVar3 = 0x7EFEFEFE;

			pcVar5 = string + 4;

			// Same thing here, it's just 0x7EFEFEFE again
			//if ((uVar4 ^ ((uint)-1) ^ uVar4 + 0x7EFEFEFF) & 0x81010100) break;
			// Considering that was the only break, is it possible to reach the third stage?
			if (false) break;

			string = pcVar5;
			if (uVar3 & 0x81010100)
			{
				if (uVar3 & 0x1010100)
					return NULL;

				if (uVar1 + 0x7EFEFEFF & 0x80000000)
					return NULL;
			}	
		}

		// Changed this to a loop
		for (uVar1 = 0; uVar1 < 4; uVar1++)
		{
			if (string[uVar1] == theChar)
				return string + uVar1;

			if (string[uVar1] == NULL)
				return NULL;
		}

		string = pcVar5;
	}

	// Considering the outer while loop doesn't have any breaks, I don't think it's possible to reach here.
	return NULL;
}

int WString_GetLength(const wchar_t* in_wstring)
{
	wchar_t c;
	wchar_t* tempstring = (wchar_t*)in_wstring;

	do
	{
		c = *tempstring;
		tempstring += 2;
	} while (c != NULL);

	return ((tempstring - in_wstring) >> 1) - 1;
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

// My guess is, this is where bugbear's bug-tearing debugger would take over.
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

void DoNothing()
{
	return;
}

// The normal jumptable
// In FO2 Ghidra did not find a name for it,
// but in FOUC it's apparently a LiteDb void function table.
// The oldest mention of LiteDb I can find is from 2014, and the oldest release I can find is from 2015.
// Was it just a false positive on Ghidra's part?
void (*LiteDb_vftable_0067b1c0[])() = {
	//FUN_00558390
	//AutoClass9::AddMappedTable,
	//FUN_005585e0
	DoNothing,
	//FUN_005585f0
};

// The no jumptable
void (*NOJMPTABLE_0067ad08[58])() = {};
void* DoNotCallEverExceptItsNotBlockedOff(void* jmpTable, int bFree);

// Instead of writing all that out I'll replace it with code that would do the same thing
// 56 of them are ExitWithCode25, and the last one is a duplicate of DoNotCallEver except without the error message
void CreateThatWeirdJumpTable()
{
	for (int i = 0; i < 57; i++)
		NOJMPTABLE_0067ad08[i] = ExitWithCode25;

	NOJMPTABLE_0067ad08[57] = (void (*)())DoNotCallEverExceptItsNotBlockedOff;
}

// So it turns out that DoNotCallEver has a duplicate that doesn't create the error message, so what is the first one?
void* DoNotCallEverExceptItsNotBlockedOff(void* jmpTable, int bFree)
{
	jmpTable = &NOJMPTABLE_0067ad08;
	if (bFree & 1)
		free(jmpTable);
	
	return jmpTable;
}


// The "Must not be called - ever" error message can be triggered in fo2, fouc, and even ridge racer unbounded. The locations in memory are different for each game though.
// FO2: Change 0x0067ADFC to 0x00558350 and it should crash immediately in-game or when loading into the menus
// FOUC: Change 0x006F3DD0 to 0x005B2FB0 while the intro is playing and it'll crash on the title card
// RR: Change 0x00C8C428 to  0x006E2CE0 while the intro is playing and it'll crash before the title is shown.

// This function is under AutoClass8, it doesn't show up in Ghidra's Functions tree for some reason.
void* DoNotCallEver(void** self, int bFree)
{
	// Seems like a default value maybe.
	self->vtable_0x0 = &LiteDb_vftable_0067b1c0;
	CreateErrorMessageAndDie("Must not be called - ever.");

	// If you bypassed the error message in FO2, this jump table would be replaced with one where every function except for one will exit with code 25
	// I checked, and bypassing the error message just silently crashes anyways
	self->vtable_0x0 = &NOJMPTABLE_0067ad08;
	if (bFree & 1)
		free(self);

	return self;
}



/////////////////////////////////////////////////
// 
// Lua
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

	// Data is just left as is, could be anything.
	this->next_0x8->type = LT::nil;
	// Turns out adding by 2 was ghidra's mistake, and my first assumption was right. Looking at the machine code it clearly adds 8 but the p-code view showed it as 2 pointers without mentioning it.
	this->next_0x8 += size_of(LuaItem);
}

// Everything I've seen so far suggests that this function only takes standard strings as input, but sometimes it's given a wide string and I can't figure out how that doesn't break things.
void LuaTable::Lua_ActuallyAddStringProperty(const char* in_string, size_t length)
{
	// Some kind of bounds checking I assume
	/*
	if (this->field10_0x10[0x10] <= this->field10_0x10[0x11])
	{
		this->FUN_005ba3a0();
	}
	*/

	LuaItem* pNext = this->next_0x8;

	// It's quite the rabbit hole of a function, still figuring it out.
	//pNext->data = this->Lua_NewStringStructMaybe(in_string, length);

	pNext->type = LT::string;
	this->next_0x8 += size_of(LuaItem);
}

void LuaTable::Lua_AddStringProperty(const char* in_string)
{
	if (in_string == NULL)
		this->Lua_AddNilProperty();
	else
		this->Lua_ActuallyAddStringProperty(in_string, String_GetLength(in_string));

	return;
}

void LuaTable::Lua_AddStringProperty2(char* in_string)
{
	LuaItem* pItem = this->next_0x8;

	//pItem->data = this->Lua_NewStringStructMaybe(in_string, String_GetLength(in_string));
	pItem->type = LT::string;

	//if ((this->field16_0x1c - this->next_0x8) < 9)
		//this->FUN_005b8790(1);

	this->next_0x8 += size_of(LuaItem);
}

void LuaTable::Lua_AddBoolProperty(bool in_bool)
{
	LuaItem* pNext = this->next_0x8;
	pNext->data = (void*)in_bool;
	pNext->type = LT::boolean;
	this->next_0x8 += size_of(LuaItem);
}

void LuaTable::Lua_AddUserDataProperty(void* userdata)
{
	LuaItem* pNext = this->next_0x8;
	pNext->data = userdata;
	pNext->type = LT::userdata;
	this->next_0x8 += size_of(LuaItem);
}

void LuaTable::Lua_AddNumberPropertyFromInt(int in_number)
{
	LuaItem* pNext = this->next_0x8;
	float converted = (float)in_number;
	pNext->data = *(void**)&converted;
	pNext->type = LT::number;
	this->next_0x8 += size_of(LuaItem);
}

void LuaTable::Lua_AddNumberPropertyFromFloat(float in_number)
{
	LuaItem* pNext = this->next_0x8;
	pNext->data = *(void**)&in_number;
	pNext->type = LT::number;
	this->next_0x8 += size_of(LuaItem);
}

// Seems like the LuaTable has several different tables, or maybe it's like one big table that has temporary pointers
// If the index is equal to or greater than 1:
//		The 1-based index into table_0xc
// If index is less than 1, it's compared to specific values to determine the list to return. These numbers seem arbitrary and I wonder if part of the number is a flag.
//		-1002 : field56_0x44
//		-1001 :  some math involving field11_0x14
//		-1000 : table_0x10 + 0x17
// -1000 is the registry apparently, I don't know if that's related to the windows registry at all.

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


int LuaTable::Lua_GetItemType(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);

	if (pItem == &LuaItem_None_0065271c)
		return (int)-1;

	return pItem->type;
}


void LuaTable::Lua_RemoveItem(int index)
{
	LuaItem* tempItem;
	LuaItem* pItem = this->Lua_GetItem(index);

	while ((tempItem = pItem + size_of(LuaItem), tempItem < this->next_0x8))
	{
		pItem->data = tempItem->data;
		pItem->type = tempItem->type;
		pItem = tempItem;
	}

	this->next_0x8 -= size_of(LuaItem);
}

// Duplicates the last item in the table, inserting it at index.
void LuaTable::Lua_InsertLastItem(int index)
{
	LuaItem* firstItem = this->Lua_GetItem(index);

	for (LuaItem* i = this->next_0x8; i > firstItem; i -= size_of(LuaItem))
	{
		i->data = i[-1].data;
		i->type = i[-1].type;
	}

	LuaItem* pNext = this->next_0x8;
	firstItem->data = pNext->data;
	firstItem->type = pNext->type;
}


void LuaTable::Lua_DuplicateItem(int index)
{
	// 2 more local variables are declared, but never used.
	LuaItem* pItem = this->Lua_GetItem(index);
	LuaItem* pNext = this->next_0x8;

	pNext->data = pItem->data;
	pNext->type = pItem->type;

	this->next_0x8 += 8;
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

void LuaTable::Lua_SeekNextPtr(int newIndex)
{
	if (newIndex < 0)
		this->next_0x8 += (newIndex * 8) + 8;
	else
	{
		while (this->next_0x8 < (this->table_0xc + (newIndex * 8)))
			this->Lua_AddNilProperty();

		this->next_0x8 = this->table_0xc + (newIndex * 8);;
	}
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
		float converted;
		if (pStringItem->type == LT::string && StringToNum((wchar_t*)&((LuaString*)pStringItem->data)->theString_0x10, &converted))
		{
			// floats are the same size as a void*, but you can't just (void*)
			pNewNumberItem->data = *(void**)&converted;
			pNewNumberItem->type = LT::number;
			pStringItem = pNewNumberItem;
		}
		else
			pStringItem = NULL;
	}
	return pStringItem;
}

LuaItem* NumberFromString2(LuaItem* pItem1, LuaItem* pItem2)
{
	if (pItem1->type != LT::number)
	{
		if ((pItem1->type == LT::string) && StringToNum(((LuaString*)pItem1->data)->theString_0x10, &local_8))
	}
}

float LuaTable::Lua_GetNumberAsFloat(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	LuaItem tempItem;

	if (pItem->type != LT::number && (pItem = Lua_NumberFromString(pItem, &tempItem), pItem == NULL))
		return 0.f;

	return *(float*)&pItem->data;
}

long LuaTable::Lua_GetNumberAsInt(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type != LT::number && (pItem = Lua_NumberFromString(pItem, &tempItem), pItem == NULL))
		return 0;

	return (long)*(float*)&pItem->data;
}

LuaItem* LuaTable::Lua_GetNumberItem(int index)
{
	LuaItem tempItem;
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type != LT::number)
		pItem = NumberFromString2(pItem, &tempItem);

	return pItem;
}

BOOL LuaTable::Lua_IsNumber_s(int index, LuaTable* otherTable)
{
	float extraout_ST0;

	LuaItem* pItem = this->Lua_GetNumberItem(index);
	float fVar1 = extraout_ST0;

	BOOL whateverThisIs = ((fVar1 < 0.0) << 8 | (isnan(fVar1) << 10) | ((fVar1 == 0.0) << 0xE));

	BOOL isNumber = (((BOOL)pItem & 0xFFFF0000) | whateverThisIs);
	if (isnan(fVar1) != (fVar1 == 0.0))
	{
		isNumber = this->Lua_IsNumber(index);
		if (isNumber == 0)
			this->Lua_ReportError(index, LT::number);
	}
	return isNumber;
}


bool LuaTable::Lua_GetBool(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type == LT::boolean)
		return pItem->data != 0;

	return pItem->type != LT::nil;
}

// New struct that I gotta figure out
void* LuaTable::Lua_GetThread(int index)
{
	void* result;

	LuaItem* pItem = this->Lua_GetItem(index);

	if (pItem->type == LT::thread)
		result = pItem->data;
	else
		result = NULL;

	return result;
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
	//return (((intForm | 0xFF800000) << 8) >> (0x1F - (uchar)type & 0x1F) ^ intForm >> 31) - intForm >> 31 & ~(type >> 31);
}

wchar_t* LuaTable::Lua_GetStringItem(int index, UINT* out_length)
{
	LuaItem* pItem = this->Lua_GetItem(index);
	if (pItem->type != LT::string)
	{
		if (Lua_StringFromNumber(pItem) == 0)
		{
			if (out_length != NULL)
				*out_length = 0;
			return NULL;
		}
		//if (this->field10_0x10[0x10] <= this->field10_0x10[0x11])
			//this->FUN_005ba3a0();
		pItem = this->Lua_GetItem(index);
	}
	if (out_length != NULL)
		*out_length = (uint)((LuaString*)(pItem->data))->length_0xc;

	return ((LuaString*)(pItem->data))->theString_0x10;
}

wchar_t* LuaTable::Lua_GetStringItem_s(int index, UINT* out_length)
{
	wchar_t* text;
	text = this->Lua_GetStringItem(index, out_length);
	if (text == NULL)
		this->Lua_ReportError(index, LT::string);

	return text;

}

char* LuaTable::Lua_GetItemStringLength(int index)
{
	char* result;
	LuaItem* pItem = this->Lua_GetItem(index);
	switch (pItem->type)
	{

	case LT::number:
		if (Lua_StringFromNumber(pItem) == 0)
			result = NULL;
		else
			result = ((LuaString*)(pItem->data))->length_0xc;
		break;

	case LT::string:
		result = ((LuaString*)(pItem->data))->length_0xc;
		break;

	case LT::table:
		//result = FUN_005c0510(pItem->data);
		break;

	// I thought being put after default means it couldn't be reached but it turns out it can
	// I'll move it above default to make things less confusing.
	case LT::userdata_s:
		result = ((LuaUserDataS*)pItem->data)->length_0x10;
		break;

	default:
		result = NULL;
	}
	return result;
}

int LuaTable::Lua_Printf(char* format, ...)
{
	va_list list;
	va_start(list, format);

	uint local_8 = 1;
	//this->Lua_AddStringProperty2("");

	char* puVar1;
	LuaItem* pNext;
	int local_3c;
	void* puVar2;

	while (puVar1 = String_IndexOfAlmost(format, '%'), puVar1 != NULL)
	{
		pNext = this->next_0x8;
		local_3c = puVar1 - format;
		puVar2 = this->Lua_NewStringStructMaybe(format, local_3c);
		pNext->data = puVar2;
		pNext->type = LT::string;
		if (this->endOfTable_0x1c - (int)this->next_0x8 < 9)
		{
			local_3c = 1;
			//this->FUN_005b8790(1);
		}
		this->next_0x8 += 8;
		switch (puVar1[1])
		{
		case '%':
			local_3c = "%";
			this->Lua_AddStringProperty2("%");
			break;

		default:
			this->Lua_AddStringProperty2(&local_3c);
			break;
		}

	}
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
	// 8 undefined bytes at offset 0x0
	LuaUserData* userdata_0x8;
	// 4 undefined bytes at offset 0xC
	int length_0x10;
};

// I'm not sure if the userdata uses the same struct as the strings
LuaUserData* LuaTable::Lua_GetUserdata(int index)
{
	LuaItem* pItem = this->Lua_GetItem(index);

	if (pItem->type == LT::userdata)
		return (LuaUserData*)pItem->data;

	else if (pItem->type == LT::userdata_s)
		// The LuaUserData struct is hidden inside another struct
		return ((LuaUserDataS*)pItem->data)->userdata_0x8;

	else
		return NULL;
}

void __fastcall Lua_PadTableIfNeeded(int newLength_EAX, LuaTable** unaff_EDI)
{
	int length = unaff_EDI[1]->Lua_GetTableLength();
	if (length < newLength_EAX)
	{
		length = newLength_EAX - length;
		do
			unaff_EDI[1]->Lua_AddNilProperty();
		while (--length);
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


void LuaTable::Lua_ThrowIfIndexIsNotGivenType(int index, int expectedType)
{
	if (this->Lua_GetItemType(index) != expectedType)
		this->Lua_ReportError(index, expectedType);
}

void LuaTable::Lua_ReportError(int index, int expectedType)
{
	this->Lua_ReportErrorForReal(index, expectedType);
}

// Based on the log it looks like it actually does use the expectedType, but ghidra has no idea how it was passed in C.
// I'll just add it to the parameters
void LuaTable::Lua_ReportErrorForReal(int index, int expectedType)
{
	DWORD type = this->Lua_GetItemType(index);
	this->Lua_StringTypeFromInt(type);
	//this->Lua_AnotherLoggingFunction("%s expected, got %s", expectedType, index);
	//this->Lua_ErrorHandling();
}


// Okay, maybe this LuaTable does more than store tables.
uint LuaTable::Lua_KickPlayer()
{
	this->Lua_ThrowIfIndexIsNotGivenType(1, LT::userdata_s);

	LuaUserData* pUserData = (LuaUserData*)this->Lua_GetUserdata(1);
	if (pUserData == NULL)
		this->Lua_ReportErrorForReal(1, LT::userdata_s);

	// Function pointers have nothing on function pointers inside function pointers
	void (**vftable1)(void(***)()) = pUserData->vftable;

	// This one is not checked to see if it's null
	pUserData = (LuaUserData*)this->Lua_GetUserdata(2);
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

// Until I confirm that this item is the same as LuaTable, I'm creating a new struct
struct TableItem
{
	// 7 undefined bytes at offset 0x0
	BYTE byte_0x7;
	TableItemStructThing* struct_0x8;
	int unkn_0x10;
};

struct LinkedTableItem
{
	// 8 undefined bytes at offset 0x0
	LuaItem item_0x8;
	LinkedTableItem* next_0x10;
};


#define SafeEquals(a, b) ( (isnan(a) || isnan(b)) != (a == b) )

LuaItem* FUN_005bfe40(TableItem* tableItem, LuaItem* pItem)
{
	LuaItem* newItem;
	int itemType = pItem->type;
	if (itemType != LT::nil)
	{
		if (itemType == LT::number)
		{
			// Converts from float to long to int to float, effectively rounding it.
			ulonglong asLong = (ulonglong)*(float*)&pItem->data;
			float rounded = (float)(int)asLong;

			if (SafeEquals(*(float*)&pItem->data, rounded))
				return Lua_GetItemFromTableItem(tableItem, asLong);

		}
		else if (itemType == LT::string)
			return FUN_005bfde0(tableItem, pItem->data);

		LinkedTableItem local_10 = Lua_GetLinkedList(tableItem, pItem);
		// Traversing a linked list to find an equal item
		do
		{
			if (Lua_ItemsEqual(local_10->pitem_0x8, pItem))
				return local_10;

			local_10 = local_10->linkedItem_0x10;
		} while (local_10 != NULL);
	}
	return &LuaItem_None_0065271c;
}

struct TableItemStructThing
{
	// 6 undefined bytes at offset 0x0
	BYTE byte_0x6;
};

void LuaTable::Lua_Add3ItemsAndCopy1(LuaItem* out_pItem1, LuaItem* pItem1, LuaItem* pItem2, LuaItem* pItem3)
{
	// I think this function is quite obfuscated, there was a lot of random math that didn't do anything and I ended up just removing it.
	LuaItem* pNext = this->next_0x8;
	pNext->data = pItem1->data;
	pNext->type = pItem1->type;

	//pNext = this->next_0x8;
	pNext[1].data = pItem2->data;
	pNext[1].type = pItem2->type;

	//pNext = this->next_0x8;
	pNext[2].data = pItem3->data;
	pNext[2].type = pItem3->type;

	//if (this->endOfTable_0x1c - this->next_0x8 < 25)
		//this->FUN_005b8790(3);

	
	this->next_0x8 += sizeof(LuaItem) * 3;
	//this->FUN_005b90c0(this->next_0x8 - (sizeof(LuaItem) * 3), 1);
	this->next_0x8 -= size_of(LuaItem);
	LuaItem* pNext = this->next_0x8;
	out_pItem1->data = pNext->data;
	out_pItem1->type = pNext->type;
}

LuaItem* LuaTable::FUN_005bc190(LuaItem* pItem, int param_3)
{
	LuaItem* result, local_8;

	if (pItem->type == LT::table)
		local_8 = pItem->data->uint_0x8;
	else if (pItem->type == LT::userdata_s)
		local_8 = pItem->data->uint_0x8;
	else
		result = this->field10_0x10[pItem->type + 0x1F];

	if (local_8 == NULL)
		result = &LuaItem_None_0065271c;
	else
		result = FUN_005bfde0(local_8, this->field10_0x10[param_3 + 0x28]);

	return result;
}

// Based on what I've decompiled so far, it replaces it's own table with the table of an item.
void LuaTable::Lua_gettable(LuaItem* pItem, LuaItem* pLastItem1, LuaItem* pNewItem)
{
	LuaItem* tempItem1;
	LuaItem* tempItem2;
	LuaItem* replacementItem;

	// Ghidra says it was originally a do while, but it's exactly like a for so why not
	for (uint i = 0; true; i++)
	{
		if (i > 99)
		{
			//this->LuaLogMaybe("loop in gettable");
			return;
		}

		if (pItem->type == LT::table)
		{
			TableItem* tableItem = (TableItem*)pItem->data;
			LuaItem* anotherItem = tableItem->FUN_005bfe40(pLastItem1);
			if (anotherItem->type != LT::nil)
			{
SaveNewItem:
				pNewItem->data = anotherItem->data;
				pNewItem->type = anotherItem->type;
				return;
			}

			if (tableItem->struct_0x8 == NULL)
				tempItem1 = NULL;
			else
			{
				if (((tableItem->struct_0x8->byte_0x6) & 1) == 0)
					tempItem2 = FUN_005bc140(tableItem->struct_0x8, NULL, this->field10_0x10[0x28]);
				else
					tempItem2 = NULL;

				tempItem1 = tempItem2;
			}
			replacementItem = tempItem1;

			if (tempItem1 == NULL)
				goto SaveNewItem;
		}
		else
		{
			replacementItem = this->FUN_005bc190(pItem, 0);
			if (replacementItem->type == LT::function)
			{
				this->Lua_Add3ItemsAndCopy1(pNewItem, replacementItem, pItem, pLastItem1);
				return;
			}
		}
		pItem = replacementItem;
	}
}

void LuaTable::CopyItemFromTableItem(int tableIndex, int itemIndex)
{
	LuaItem* tableItem = this->Lua_GetItem(tableIndex);
	LuaItem* itemItem = ()(tableItem->data)
}

// It's dividing by 8, makes sense now
int LuaTable::Lua_GetTableLength()
{
	return (this->next_0x8 - this->table_0xc) >> 3;
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
	this->Lua_ThrowIfIndexIsNotGivenType(1, LT::userdata_s);
	LuaUserData* pUserData = this->Lua_GetUserdata(1);
	if (pUserData != NULL)
		this->Lua_ReportErrorForReal(1);
	// So: This indicates that the first item of the struct is a pointer to another struct, and the first item of that struct is a jmptable
	(*((**pUserData)[4]))();
	return 0;
}

uint Lua_LongJump(LuaTable* table, void (*func)(LuaTable*, undefined4*), undefined4* scriptObject)
{
	jmp_buf local_48;
	uint local_4c = table[1].next_0x8;
	table[1].next_0x8 = (LuaItem*)&local_4c;

	// _setjmp3
	// Internal CRT function. A new implementation of the setjmp function.
	// Don't use this function in a C++ program. It's an intrinsic function that doesn't support C++.
	// - Documentation
	// I guess it's proof this wasn't written in C++
	int iVar1 = _setjmp3(&local_48, 0, local_4c, local_48);
	if (iVar1 == 0)
		(*func)(table, scriptObject);

	table[1].next_0x8 = (LuaItem*)local_4c;

	return 0;
}

void Lua_ReturnFromLongJump(uint* param_2)
{

}

// Functions that I imagine are called from Lua, given the strange procedure
// The first item in the table is used as the input to functions, while outputs to functions are added to the end of the table, almost like it's a print output or something.

LuaErrorCode len(LuaTable* table)
{
	UINT length;
	table->Lua_GetStringItem_s(1, &length);
	table->Lua_AddNumberPropertyFromInt(length);
	return BB_OK;
}

LuaErrorCode GetNumWStringLines(LuaTable* table)
{
	LuaTable* tableCopy = table;
	wchar_t* in_wstring = table->Lua_GetStringItem(1, NULL);

	LuaTable* pLVar2 = (LuaTable*)1;
	table = (LuaTable*)1;
	uint length = WString_GetLength(in_wstring);
	if (length)
	{
		// It was originally a do while but it's structured exactly like a for so why not
		for (int i = 0; i < length; i++)
		{
			if (in_wstring[i] == L'\n')
				pLVar2++;

			table = pLVar2;
		}
	}
	tableCopy->Lua_AddNumberPropertyFromFloat((float)(int)table);
	return BB_OK;
}

LuaErrorCode ConvertToWString(LuaTable* table)
{

	if (!table->Lua_IsItemAStringOrNumber(1))
	{
		table->Lua_ActuallyAddStringProperty(L"NIL STRING", WString_GetLength(L"NIL STRING") + 2);
	}
	else
	{
		wchar_t* pWVar2 = table->Lua_GetStringItem(1, NULL);
		wchar_t* iVar3 = pWVar2 + 1;
		do
		{

		}
	}
}

LuaErrorCode getplatform(LuaTable* table)
{
	table->Lua_ActuallyAddStringProperty("PC", 2);

	return BB_OK;
}

LuaErrorCode StartKickVote(LuaTable* table)
{
	table->Lua_ThrowIfIndexIsNotGivenType(1, LT::userdata_s);
	LuaUserData* pUserData = table->Lua_GetUserdata(1);
	if (pUserData == NULL)
		table->Lua_ReportErrorForReal(1, LT::userdata_s);

	int* piVar1 = *(int**)(pUserData->vftable);
	pUserData = table->Lua_GetUserdata(2);
	int local_8 = *(int*)pUserData->vftable;

	FUN_004f0f20(piVar1, &local_8);

	return BB_OK;
}

LuaErrorCode deg(LuaTable* table)
{
	LuaTable* unaff_ESI;
	table->Lua_GetNumber_s(1, unaff_ESI);
}

// FormatMemoryCard will call this function, but given the lack of formatting going on I'd say that's probably unintentional.
void FormatMemoryCardForRealMaybe(int param_1)
{
	return param_1->unkn_0x4;
}

// Left-over from the PS2 version, it still calls a function but clearly it doesn't do any formatting anymore.
LuaErrorCode FormatMemoryCard()
{
	bbSaveDevice* save = SaveDeviceRelated_008e8410;
	FormatMemoryCardForRealMaybe();
	save->field1088_0x44c = 7;
	return BB_OK;
}

BYTE byteArray_00652728[256] =
{
	0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, //...
};

// Instead of writing all that out, I'm going to replace it with code that would do the same thing
// Each item is duplicated by a factor of 2, so it only goes to 8
void CreateThatByteArray()
{
	byteArray_00652728[0] = 0;
	int num, innerLoops, index;
	num = innerLoops = index = 1;
	while (index < 256)
	{
		for (int j = 0; j < innerLoops; j++)
			byteArray_00652728[index + j] = num;

		index += innerLoops;
		num++;
		innerLoops *= 2;
	}
}


int FUN_005bb8a0(uint indexKinda)
{
	uint i = -1;
	for (; indexKinda > 255; indexKinda >>= 8)
		i += 8;

	return (uint)byteArray_00652728[indexKinda] + i;
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
FileObject* __fastcall FileObject_New(const char* filename_unaff_EDI, uint flags_unaff_EBX)
{
	FileObject* output = NULL;
	// Checking if it's reading an existing file or not
	if ((flags_unaff_EBX & 1) == 0)
	{
		FileObject* piVar2 = (FileObject*)malloc(sizeof(FileObject));
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
		// It's outside the if statement, which will try to access output even when it's NULL.
		output->FileObject_Create(filename_unaff_EDI, flags_unaff_EBX);
	}
	else
	{
		struct _stat result;
		int iVar1 = _stat(filename_unaff_EDI, &result);
		if (iVar1 == 0)
		{
			FileObject* pAVar2 = (FileObject*)malloc(sizeof(FileObject));
			if (pAVar2 != NULL)
			{
				FileObject_ClearEAX(pAVar2);
				output = pAVar2;
			}
			// They did it again
			output->FileObject_Create(filename_unaff_EDI, flags_unaff_EBX);
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
// If mode is 0, checks a flag in the attributes and if it's cleared, read from the file in, a way.
void FileObject::FileObject_SetFilePos(int newPos, int mode)
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
		free(this);

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
	int aiStack_10[2];
	int iVar2;
	int iVar9;

	// The length of the filename is calculated, but it's never used.
	String_GetLength((char*)filename);

	// Very large structure
	//unaff_EDI[0x88] = NULL;

	DWORD fileFlags = FILE_ATTRIBUTE_NORMAL;

	if (UINT_008da730)
		fileFlags |= FILE_FLAG_DELETE_ON_CLOSE;

	// bfsFile seems to be an all-purpose variable, first it's the handle of the file, then it's used to contain the size of the file, then it's used to point at the file's data, then it's used as a temporary int.
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
	unaff_EDI->unkn_0x210 = uStack_8 & 0x7FFFFFFFF;
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

	// Only included in fo2a.bfs, b and c's is NULL
	unaff_EDI->string_0x218 = ReadAsString(bfsFile, 0x14);

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

	unaff_EDI->string_0x21c = (char*)piVar7;

	bfsFile = (char*)((int)piVar10 + *piVar7);
	unaff_EDI->string_0x20c = bfsFile;

	int pvVar3 = unaff_EDI->int_0x220;
	if (pvVar3 != 0)
	{
		for (int i = unaff_EDI->int_0x214; i != 0; i--)
		{
			ReadAsInt(bfsFile, 4) += (int)pvVar3;

			// The ghidra code uses a second comparison like a trick to set j during the if. I chose to do it afterwards, is it any different?
			// && (j = 0, bfsFile[1] != NULL)
			// If that's all it was for I can probably just remove it
			if ((bfsFile[1] != NULL))
			{
				int j = 0;
				do
				{
					piVar7 = ReadAsIntP(bfsFile, j * 4 + 0x18);
					*piVar7 += (int)pvVar3;
					j++;
				} while (j < ReadAsByte(bfsFile, 1));
			}
			bfsFile += ReadAsByte(bfsFile, 1) * 4 + 0x18;
		}
	}
	return;
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

LRESULT KeyboardController::Keyboard_Hook(uint param_1)
{
	// Ghidra shows the STOSD.REP instruction as a for loop
	__stosd(lpKeyState_008d7e60, 0, 0x40);
	__stosd(lpKeyState_008d7d60, 0, 0x40);

	if (HHOOK_008da738 == NULL)
	{
		DWORD dwThreadId = GetCurrentThreadId();
		HHOOK_008da738 = SetWindowsHookExA(2, nextHook, NULL, dwThreadId);
		if (HHOOK_008da738 == NULL)
		{
			//uStack_2c = 0xF;
			//uStack_30 = 0;
			//uStack_40 = 0;
			//FUN_0055b050(auStack_44, "KeyboardController::Unable to hook keyboard", 0x2B);
			//appuStack_28[0] = &PTR_FUN_006578c4;
			//uStack_4 = 0xF;
			//uStack_8 = 0;
			//uStack_18 = 0;
			//FUN_0055ae50(auStack_1c, auStack_44, 0, 0xFFFFFFFF);

			// Some kind of exception code, I'll just do this for now.
			throw EXCEPTION_INVALID_HANDLE;
		}
	}

	DAT_008d7c44 = GetKeyboardLayout(0);

	_stosd(UINT_008d7c48, 0, 0x40);
	DAT_008d7d58 = 0;
	DAT_008da740 = 0;
	this->field_0x12c = 1;
	this->field_0x130 = 1;
	int iVar1 = FUN_00553220();
	if (iVar1 == 0)
	{
		//this->vftable_0x0[17]();
		FUN_00553360();
	}
	iVar1 = 0;
	do
	{
		FUN_00553120();
		iVar1++;
	} while (iVar1 < 20);

	return 1;
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
		// In Binary: 0?00 0000 0000 0000 0000 0000 0000 0000
		if (DAT_008da734 || ((lParam & 0x40000000U) == 0))
		{
			if (lpKeyState_008d7e60[wVirtKey] > -1)
				DAT_008da740++;

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

// Another function that looks suspicously like DoNotCallEver.
void* KeyboardController::Keyboard_Unhook(BYTE bFree)
{
	//this->vftable_0x0 = JMPTABLE_0067b818;
	if (this->int_0x12c)
	{
		if (HHOOK_008da738 != NULL)
			UnhookWindowsHookEx(HHOOK_008da738);

		HHOOK_008da738 = NULL;
		DAT_008da73c = NULL;
		this->int_0x12c = 0;
		this->byte_0x130 = 0;
	}
	//this->vftable_0x0 = JMPTABLE_0067b738;
	if (bFree & 1)
		delete this;

	return this;
}