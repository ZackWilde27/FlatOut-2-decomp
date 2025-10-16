#pragma once

class MemoryManager
{
public:
	void* m_pAllBlocks_0x1c;

	void* IsThatACustomMadeMalloc(int size);
	void* IsThatACustomMadeRealloc(int size);
	void IsThatACustomMadeFree(int size);
};