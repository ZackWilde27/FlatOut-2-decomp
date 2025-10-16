#include "MemoryManager.h"

void* MemoryManager::IsThatACustomMadeMalloc(int size)
{
	void* allMem = m_pAllBlocks_0x1c;
	int fullSize = size + 7;

	int iVar6;

	int actualSize;
	if (fullSize < 16)
		actualSize = 16;
	else
	{
		// Masks out the first 2 bits to make it a multiple of 4
		actualSize = fullSize & 0xFFFFFFFC;
		if (actualSize > 255)
		{
			fullSize >>= 8;
			if (fullSize < 256)
			{
				// At first this looked like some kind of RNG, but what it actually does it a bit more simple
				// Starting at a fullSize of 256, it will get turned into 64, then the result will increase by 1 every 64 bytes
				// So
				// if (fullSize < 256) return fullSize;
				// if (fullSize >= 256 && fullSize < 320) return 64;
				// if (fullSize >= 320 && fullSize < 384) return 65;
				// and so on
				unsigned int uVar9 = fullSize - 0x100 >> 16 & 8;
				iVar6 = fullSize << (char)uVar9;
				unsigned int uVar8 = iVar6 - 0x1000U >> 16 & 4;
				iVar6 <<= (char)uVar8;
				unsigned int uVar11 = iVar6 - 0x4000U >> 16 & 2;
				fullSize = iVar6 << (char)uVar11;
				iVar6 = ((~(fullSize >> 15) & fullSize >> 14) - uVar11) - (uVar9 + uVar8);
				fullSize = (actualSize >> ((char)iVar6 + 19U & 0x1F) & 3) + 0x40 + (iVar6 + 0xD) * 4;
			}
			else
				fullSize = 0x5F;

			goto LAB_00550824;
		}
	}

	fullSize = actualSize / 4;
	void* piVar14 = allMem + (fullSize * 2 + 3) * 4;
	void* piVar1 = allMem + fullSize * 2;
	if (piVar14 != piVar1)
	{
		iVar6 = (void*)((char*)piVar14 + 12);
		*(unsigned int*)(piVar14 + actualSize + 4) |= 1;
		*(int*)(piVar1 + 12) = iVar6;
		*(int**)(iVar6 + 8) = piVar1;
		return piVar14 + 2;
	}

	LAB_00550824:
	piVar1 = allMem + 2;
	piVar14 = allMem + 20;
	while (piVar14 != piVar1)
	{

	}
}