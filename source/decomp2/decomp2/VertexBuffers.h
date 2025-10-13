#pragma once

#include "Macros.h"
#include "DirectX.h"

class Buffer
{
public:
	//BYTE pad_0x4[4];
	UINT offset_0x8;
	int itemsMapped_0xc; // The number of items that have been written to so far
	UINT capacity_0x10; // The number of bytes that haven't been written to yet
	int itemsLeft_0x14; // For the vertex buffer, the number of items that haven't been written to yet
	//BYTE pad_0x18[4];

	virtual void* LockWithMoreSteps(UINT size)
	{
		return NULL;
	}

	virtual void* Lock(UINT offset, UINT size, DWORD flags)
	{
		return NULL;
	}

	virtual bool Unlock()
	{
		return false;
	}
};


class VertexBuffer : public Buffer
{
public:
	UINT itemSize_0x1c;
	//BYTE pad_0x20[4];
	LPDIRECT3DVERTEXBUFFER9 buffer_0x24;
	DWORD usage_0x28;
	D3DPOOL pool_0x2c;
	void* dataPtr_0x30;
	UINT length_0x34;
	int totalItems_0x38;
	UINT mappedSize_0x3c;

	// This probably isn't a class, since the constructor puts the numItems in ECX, while 'this' goes in EDX
	VertexBuffer(register int numItems_ECX, undefined4 param_3, DWORD usage, D3DPOOL pool, register UINT itemSize_EAX);

	LPDIRECT3DVERTEXBUFFER9 GetD3DBuffer() const;

	void* LockWithMoreSteps(UINT size) override;
	void* Lock(UINT offset, UINT size, DWORD flags) override;
	bool Unlock() override;
};

// Defined in Decomp2.cpp
void VertexBuffer_CreateD3DBuffer(register VertexBuffer* buffer_ESI);


class IndexBuffer : public Buffer
{
public:
	LPDIRECT3DINDEXBUFFER9 buffer_0x1c;
	DWORD usage_0x20;
	D3DPOOL pool_0x24;
	void* dataPtr_0x28;
	UINT length_0x2c;
	int totalItems_0x30;
	int mappedSize_0x34;

	IndexBuffer(DWORD usage, D3DPOOL pool, int numIndices_EAX);

	void* LockWithMoreSteps(UINT size) override;
	void* Lock(UINT offset, UINT size, DWORD flags) override;
	bool Unlock() override;
};

// Defined in Decomp2.cpp
void IndexBuffer_CreateD3DBuffer(register IndexBuffer* buffer_ESI);