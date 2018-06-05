#include <stdio.h>
typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct Mpoll{
    uint m_numOfBlocks; // Num of blocks
    uint m_sizeOfEachBlock; // Size of each block
    uint m_numFreeBlocks; // Num of remaining blocks
    uint m_numInitialized; // Num of initialized blocks
    uchar* m_memStart; // Beginning of memory pool
    uchar* m_next; 
} Mpoll;

void CreatePool(Mpoll *pool, size_t sizeOfEachBlock, uint numOfBlocks)
{
    pool->m_numOfBlocks = numOfBlocks;
    pool->m_sizeOfEachBlock = sizeOfEachBlock;
    pool->m_memStart = (char *)malloc(m_sizeOfEachBlock * m_numOfBlocks);
    pool->m_numFreeBlocks = numOfBlocks;
    pool->m_next = pool->m_memStart;

    pool->m_numInitialized = 0;
}

uchar* AddrFromIndex(Mpool *pool, uint i)
{
    return pool->m_memStart + ( i * pool->m_sizeOfEachBlock );
}

void* Allocate(Mpool *pool)
{
    uint* p;
    void* ret = NULL;
    if (pool->m_numInitialized < pool->m_numOfBlocks )
    {
        p = (uint*)AddrFromIndex(pool->m_numInitialized);
        *p = pool->m_numInitialized + 1;
        pool->m_numInitialized++;
    }
    if (pool->m_numFreeBlocks > 0)
    {
        ret = (void*)pool->m_next;
        pool->m_numFreeBlocks--;
        if (pool->m_numFreeBlocks!=0)
        {
            pool->m_next = AddrFromIndex(*((uint*)pool->m_next));
        }
        else
        {
            pool->m_next = NULL;
        }
    }
    return ret;
}

void DeAllocate(Mpool *pool, void *p)
{
   if(pool->m_next !=NULL)
   {
        pool->m_next = (uchar *)p;
        pool->m_numFreeBlocks++;
        pool->m_numInitialized--;
   }
   else
   {
        pool->m_next = (uchar*)p;
        pool->m_numFreeBlocks++;
        pool->m_numInitialized--;
   }
}
void DestroyPool(Mpool *pool)
{
   free(pool->m_memStart);
   pool->m_memStart = NULL;
}
