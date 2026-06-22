#include "stdlib.h"
#include <stdint.h>

#define HEAP_SIZE 16384
#define BLOCK_MAGIC 0x4D424C4B

typedef struct {
    uint32_t magic;
    size_t size;
    int free;
} BlockHeader;

static uint8_t heap[HEAP_SIZE];
static int heap_initialized = 0;

void malloc_init(void) {
    if (!heap_initialized) {
        BlockHeader *header = (BlockHeader *)&heap[0];
        header->magic = BLOCK_MAGIC;
        header->size = HEAP_SIZE - sizeof(BlockHeader);
        header->free = 1;
        heap_initialized = 1;
    }
}

void *malloc(size_t size) {
    if (!heap_initialized) {
        malloc_init();
    }
    
    if (size == 0) {
        return NULL;
    }
    
    size_t aligned_size = (size + 7) & ~7;
    
    BlockHeader *current = (BlockHeader *)&heap[0];
    
    while ((uintptr_t)current < (uintptr_t)&heap[HEAP_SIZE]) {
        if (current->magic != BLOCK_MAGIC) {
            break;
        }
        
        if (current->free && current->size >= aligned_size) {
            if (current->size > aligned_size + sizeof(BlockHeader)) {
                BlockHeader *next = (BlockHeader *)((uintptr_t)current + sizeof(BlockHeader) + aligned_size);
                next->magic = BLOCK_MAGIC;
                next->size = current->size - aligned_size - sizeof(BlockHeader);
                next->free = 1;
                
                current->size = aligned_size;
            }
            
            current->free = 0;
            return (void *)((uintptr_t)current + sizeof(BlockHeader));
        }
        
        current = (BlockHeader *)((uintptr_t)current + sizeof(BlockHeader) + current->size);
    }
    
    return NULL;
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }
    
    BlockHeader *header = (BlockHeader *)((uintptr_t)ptr - sizeof(BlockHeader));
    
    if (header->magic == BLOCK_MAGIC) {
        header->free = 1;
    }
}
