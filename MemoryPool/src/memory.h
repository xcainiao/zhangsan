#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct Mpool{
    uint m_numOfBlocks; // Num of blocks
    uint m_sizeOfEachBlock; // Size of each block
    uint m_numFreeBlocks; // Num of remaining blocks
    uint m_numInitialized; // Num of initialized blocks
    uchar* m_memStart; // Beginning of memory pool
    uchar* m_next; 
} Mpool;

void CreatePool(Mpool *pool, size_t sizeOfEachBlock, uint numOfBlocks);
uchar* AddrFromIndex(Mpool *pool, uint i);
void* Allocate(Mpool *pool);
void DeAllocate(Mpool *pool, void *p);
