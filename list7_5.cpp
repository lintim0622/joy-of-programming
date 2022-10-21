#include <list7_4.cpp>

Heap heap;

void* operator new(size_t n_bytes) {
    return heap.allocate(n_bytes);
}

void operator delete(void* p) {
    return heap.free(p);
}