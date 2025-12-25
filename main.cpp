#include <iterator>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>

struct header_t {
    size_t size;
    bool is_free;
    struct header_t* next;
};

header_t *head = nullptr;
header_t *tail = nullptr;

void * find_free_memory(size_t size ) {
    header_t * current = head;
    while (current) {
        if ((*current).is_free && (*current).size >= size ) {
            (*current).is_free = false;
            return (void*)(current + 1);

        }
        current = (*current).next;
    }
}

void * my_molloce( size_t size) {
    if (size == 0)
        return nullptr;

    header_t *header =(header_t*) find_free_memory(size);

    if (header) {
        (*header).is_free = false;
        return (void*)(header + 1);
    }

    size_t total_size = sizeof(header_t) + size;
    void* block = VirtualAlloc(NULL, total_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (!block) return nullptr;

    header = (header_t*)block;
    (*header).size = size;
    (*header).is_free = false;
    (*header).next = nullptr;

    if (head == nullptr) {
        head = header;
    }
    else {
        (*tail).next = header;
    }
    tail = header;
}

int main() {


}