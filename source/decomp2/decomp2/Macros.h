#pragma once

// Wait a minute, Microsoft already did this
#define uint UINT
#define ulong ULONG
#define ushort USHORT
#define uchar UCHAR
#define ulonglong ULONGLONG
#define cchar const char // This was my idea though, I can at least claim that.

// I didn't know that wide strings were unicode, but in my defence, if they are interchangable why is there both wchar_t and char16_t? both u"String" and L"String"?
#define LPUSTR LPWSTR

#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
// I thought a long was 8 bytes, but that's not the case on Windows.
// long and int are the same size? Why is it a 'long' then?
#define undefined8 unsigned long long

// Doesn't end there, putting aside the missed opportunity to call it a double double, it turns out a long double is the same size as a double.
// I couldn't find much information about what ghidra's float10 actually is.
// I've heard it's an 80-bit float but 64 is the best we're going to get without some other solution.
#define float10 long double

// Can't do += sizeof() but you can with this workaround.
#define size_of(type) (1 * sizeof(type))