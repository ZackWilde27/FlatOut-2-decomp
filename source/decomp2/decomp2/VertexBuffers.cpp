#include "VertexBuffers.h"

UINT g_uBufferUsage_008da2b0;

//////////////////////////////////
// Vertex Buffer
//////////////////////////////////

VertexBuffer::VertexBuffer(register int numItems_ECX, undefined4 param_3, DWORD usage, D3DPOOL pool, register UINT itemSize_EAX)
{
	itemSize_0x1c = itemSize_EAX;
	length_0x34 = itemSize_EAX * numItems_ECX;
	totalItems_0x38 = numItems_ECX;
	capacity_0x10 = itemSize_EAX * numItems_ECX;

	DWORD baseUsage = g_uBufferUsage_008da2b0;

	itemsLeft_0x14 = numItems_ECX;
	buffer_0x24 = NULL;
	dataPtr_0x30 = NULL;
	offset_0x8 = 0;
	itemsMapped_0xc = 0;
	//unkn_0x4 = 1;
	//vftable_0x0 = JMPTABLE_VertexBuffer_0067dae8;
	//unkn_0x20 = 1;
	//unkn_0x18 = param_3;
	usage_0x28 = baseUsage | usage;
	pool_0x2c = pool;
	VertexBuffer_CreateD3DBuffer(this);
}

LPDIRECT3DVERTEXBUFFER9 VertexBuffer::GetD3DBuffer() const
{
	return buffer_0x24;
}

void* VertexBuffer::LockWithMoreSteps(UINT size)
{
	auto vBuffer = buffer_0x24;
	if (vBuffer)
	{
		UINT flags = D3DLOCK_NOOVERWRITE;

		if (capacity_0x10 < size)
		{
			capacity_0x10 = length_0x34;
			offset_0x8 = 0;
			itemsMapped_0xc = 0;
			itemsLeft_0x14 = length_0x34;
		}

		if (offset_0x8 == 0)
			flags = D3DLOCK_DISCARD;

		HRESULT hr = vBuffer->Lock(offset_0x8, size, &dataPtr_0x30, flags);
		if (FAILED(hr))
		{
			dataPtr_0x30 = NULL;
			mappedSize_0x3c = 0;
			return NULL;
		}
	}

	mappedSize_0x3c = size;
	return dataPtr_0x30;
}

void* VertexBuffer::Lock(UINT offset, UINT size, DWORD flags)
{
	auto vBuffer = buffer_0x24;
	if (vBuffer)
	{
		HRESULT hr = vBuffer->Lock(offset, size, &dataPtr_0x30, flags);
		if (FAILED(hr))
		{
			dataPtr_0x30 = NULL;
			mappedSize_0x3c = 0;
			return NULL;
		}
	}

	mappedSize_0x3c = size;
	return dataPtr_0x30;
}

bool VertexBuffer::Unlock()
{
	bool succeeded = true;

	if (dataPtr_0x30 && buffer_0x24)
	{
		HRESULT hr = buffer_0x24->Unlock();
		succeeded = SUCCEEDED(hr);

		if (usage_0x28 & D3DUSAGE_DYNAMIC)
		{
			offset_0x8 += mappedSize_0x3c;
			capacity_0x10 -= mappedSize_0x3c;
			int itemsMapped = mappedSize_0x3c / itemSize_0x1c;
			itemsMapped_0xc += itemsMapped;
			itemsLeft_0x14 -= itemsMapped;
		}
	}

	return succeeded;
}



//////////////////////////////////
// Index Buffer
//////////////////////////////////

IndexBuffer::IndexBuffer(DWORD usage, D3DPOOL pool, int numIndices_EAX)
{
	buffer_0x1c = NULL;
	dataPtr_0x28 = NULL;
	offset_0x8 = 0;
	itemsMapped_0xc = 0;
	totalItems_0x30 = numIndices_EAX;
	length_0x2c = numIndices_EAX * 2;
	itemsLeft_0x14 = numIndices_EAX;

	DWORD baseUsage = g_uBufferUsage_008da2b0;
	capacity_0x10 = numIndices_EAX * 2;
	//unkn_0x4 = 1;
	//vftable_0x0 = &JMPTABLE_IndexBuffer_0067dad8;
	//unkn_0x18 = 1;
	usage_0x20 = baseUsage | usage;
	pool_0x24 = pool;
	IndexBuffer_CreateD3DBuffer(this);
}

void* IndexBuffer::LockWithMoreSteps(UINT size)
{
	LPDIRECT3DINDEXBUFFER9 iBuffer = buffer_0x1c;
	if (iBuffer)
	{
		UINT flags = D3DLOCK_NOOVERWRITE;
		if (capacity_0x10 < size)
		{
			capacity_0x10 = length_0x2c;
			offset_0x8 = 0;
			itemsMapped_0xc = 0;
			itemsLeft_0x14 = totalItems_0x30;
		}

		if (offset_0x8 == 0)
			flags = D3DLOCK_DISCARD;

		HRESULT hr = iBuffer->Lock(offset_0x8, size, &dataPtr_0x28, flags);
		if (FAILED(hr))
		{
			dataPtr_0x28 = NULL;
			mappedSize_0x34 = 0;
			return NULL;
		}
	}

	mappedSize_0x34 = size;
	return dataPtr_0x28;
}

void* IndexBuffer::Lock(UINT offset, UINT size, DWORD flags)
{
	auto iBuffer = buffer_0x1c;
	dataPtr_0x28 = NULL;

	if (iBuffer)
	{
		if (FAILED(iBuffer->Lock(offset, size, &dataPtr_0x28, flags)))
			return NULL;
	}

	return dataPtr_0x28;
}

bool IndexBuffer::Unlock()
{
	bool succeeded = true;

	if (dataPtr_0x28 && buffer_0x1c)
	{
		if (usage_0x20 & D3DUSAGE_DYNAMIC)
		{
			offset_0x8 += mappedSize_0x34;
			capacity_0x10 -= mappedSize_0x34;
			itemsMapped_0xc += mappedSize_0x34 >> 1;
			itemsLeft_0x14 -= mappedSize_0x34 >> 1;
		}

		dataPtr_0x28 = NULL;
		//unkn_0x18 = 0;

		succeeded = SUCCEEDED(buffer_0x1c->Unlock());
	}

	return succeeded;
}