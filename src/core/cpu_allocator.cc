#include "core/cpu_allocator.h"

namespace lytransformer {

void* Allocator<AllocatorType::CPU>::malloc(size_t size) {
    return std::malloc(size);
}

void* Allocator<AllocatorType::CPU>::mallocSync(size_t size) {
    return malloc(size);
}

void  Allocator<AllocatorType::CPU>::free(void** ptr) {
    std::free(*ptr);
    *ptr = nullptr;
}

// these two methods are not expected to be called
void* Allocator<AllocatorType::CPU>::reMalloc(void* ptr, size_t size) {
    // FT_FAIL("cpu reMalloc not implemented");
    return nullptr;
}


}  // namespace lytransformer
