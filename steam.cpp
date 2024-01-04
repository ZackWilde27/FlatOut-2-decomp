// What I could recover from the Steam version. I am not familiar with Valve's DRM.

#include <setjmp.h>
// I'm including it because the file has thunk functions set up for kernel32 functions, but ghidra cant find an instance of them being used.
#include <windows.h>

#define undefined1 unsigned char
#define undefined2 unsigned short
#define undefined4 unsigned int
#define undefined8 unsigned long long

// Why do function pointers have to be damn near undecipherable?
#define thatCodePointer(a) ( *( int(*)( int, undefined4, int, int, void*, char** ) )( a ) )
#define thisCodePointer(a) ( *( void(*)( char*, int, char***, int, int) )( a ) )
#define voidFunc(a) ( *(void (*)() )( a ) )

undefined4 DAT_009444a3;
char* PTR_DAT_009443e8 = (char*)0x00543598;
undefined4 DAT_009443ec = 0x1D1C;
void* PTR_IMAGE_DOS_HEADER_00944400 = (void*)0x40000;
char** PTR_DAT_00944408 = (char**)0x00543504;
char** PTR_DAT_00944404 = (char**)0x00543500;
undefined4 DAT_009443f0 = 0xAA0;
char* PTR_DAT_009443f4;
undefined4* PTR_DAT_009443f8 = (undefined4*)0x543508;

jmp_buf JumpBuffer;

void __fastcall FUN_0094440c(int argc, char** argv)
{
	int iVar4 = 0;
	// Call the function at PTR_DAT_009443f8 + PTR_IMAGE_DOS_HEADER_00944400
	// Points at a buffer with nothing in it, This is the first function called on entry so I'm wondering how the buffer gets filled.
	int iVar1 = thatCodePointer(0x00583508)(0, DAT_009443ec, 0x1000, 0x40, PTR_IMAGE_DOS_HEADER_00944400, argv);

	PTR_DAT_00944408 = PTR_DAT_00944408 + iVar4;
	PTR_DAT_00944404 = PTR_DAT_00944404 + iVar4;
	char* puVar3 = PTR_DAT_009443e8 + iVar4;

	// Another empty spot for code
	thisCodePointer(0x0054433B)(puVar3, iVar1, &PTR_DAT_00944404, iVar4, iVar1);

	undefined4 (*pcVar2)(char*) = (undefined4 (*)(char*))(iVar1 + DAT_009443f0);
	iVar1 = (int)pcVar2 - 4;
	*(char**)((int)pcVar2 + (8 - (iVar1 + 4))) = puVar3;
	*(char**)((int)pcVar2 + (0x14 - (iVar1 + 4))) = PTR_DAT_009443f4;
	DAT_009444a3 = (*pcVar2)(puVar3);

	// Jumping to a function instead of calling, assuming it'll have a longjmp call.
	voidFunc(DAT_009444a3)();
}

int main(int argc, char* argv[])
{
	if (setjmp(JumpBuffer) == 0)
		FUN_0094440c(argc, argv);
	return;
}