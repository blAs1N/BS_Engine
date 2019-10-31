#include "PoolAllocator.h"
#include "MathFunctions.h"
#include "MemoryManager.h"
#include "MarkerMemory.h"
#include <memory>

/// @todo Link memory manager
PoolAllocatorBase::PoolAllocatorBase(const size_t size, bool isSingleFrame /*= false*/) noexcept
	: memoryManager(nullptr),
	markerMemory(nullptr),
	isSingleFrameAlloc(isSingleFrame)
{
	Init(size);
}

PoolAllocatorBase::PoolAllocatorBase(const PoolAllocatorBase& other) noexcept
	: memoryManager(other.memoryManager),
	markerMemory(nullptr),
	isSingleFrameAlloc(other.isSingleFrameAlloc)
{
	Init(other.GetMaxSize());
}

PoolAllocatorBase::PoolAllocatorBase(PoolAllocatorBase&& other) noexcept
	: memoryManager(std::move(other.memoryManager)),
	markerMemory(std::move(other.markerMemory)),
	isSingleFrameAlloc(std::move(other.isSingleFrameAlloc)) {}

PoolAllocatorBase::~PoolAllocatorBase() noexcept
{
	auto* const mem = markerMemory->GetMemory();
	const auto memSize = markerMemory->GetMemorySize();
	const auto markSize = markerMemory->GetMarkerSize();
	memoryManager->Deallocate(this, mem, memSize + markSize);
}

void* PoolAllocatorBase::Allocate(const size_t size) noexcept
{
	return markerMemory->Alloc(size);
}

void PoolAllocatorBase::Deallocate(void* const ptr, const size_t size) noexcept
{
	markerMemory->Dealloc(ptr, size);
}

void PoolAllocatorBase::Clear() noexcept
{
	markerMemory->Clear();
}

size_t PoolAllocatorBase::GetMaxSize() const noexcept
{
	return markerMemory->GetMemorySize();
}

void PoolAllocatorBase::Init(const size_t size) noexcept
{
	if (size == 0) return;

	const auto markerSize = static_cast<size_t>(
		Math::Ceil(static_cast<float>(size) * 0.125f));

	auto* ptr = memoryManager->Allocate(this, size + markerSize + sizeof(MarkerMemory));
	if (ptr == nullptr) return;

	auto* const memory = static_cast<uint8*>(ptr);
	auto* const marker = static_cast<uint8*>(ptr) + size;

#pragma push_macro("new")
#undef new
	auto* markerPtr = reinterpret_cast<MarkerMemory*>(marker + markerSize);
	markerMemory = new(markerPtr)MarkerMemory{ memory, marker, size, markerSize };
#pragma pop_macro("new")
}