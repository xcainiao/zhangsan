#include "memory.h"

void CreatePool(Mpool *pool, size_t sizeOfEachBlock, uint numOfBlocks)
{
    pool->m_numOfBlocks = numOfBlocks;
    pool->m_sizeOfEachBlock = sizeOfEachBlock;
    pool->m_memStart = (char *)malloc(sizeOfEachBlock * numOfBlocks);
    pool->m_numFreeBlocks = numOfBlocks;
    pool->m_next = pool->m_memStart;

    pool->m_numInitialized = 0;
}

uchar* AddrFromIndex(Mpool *pool, uint i)
{
    return pool->m_memStart + ( i * pool->m_sizeOfEachBlock );
}

uint IndexFromAddr(Mpool *pool)
{
	return (((uint)(pool->m_next - pool->m_memStart)) / pool->m_sizeOfEachBlock);
}

void* Allocate(Mpool *pool)
{
    uint* p;
    void* ret = NULL;
    /*
     * initialize all block value
     * block1 = 1
     * block2 = 2
     * block3 = 3
	 * (*pool->m_next) = block;
     * pool->m_next = pool->m_memStart + i*(*pool->m_next)
     */
    if (pool->m_numInitialized < pool->m_numOfBlocks )
    {
        p = (uint*)AddrFromIndex(pool, pool->m_numInitialized);
        *p = pool->m_numInitialized + 1;
        pool->m_numInitialized++;
    }
    
    if (pool->m_numFreeBlocks > 0)
    {
        ret = (void*)pool->m_next;
        pool->m_numFreeBlocks--;
        if (pool->m_numFreeBlocks!=0)
        {
            pool->m_next = AddrFromIndex(pool, *((uint*)pool->m_next));
        }
        else
        {
            pool->m_next = NULL;
        }
    }
    return ret;
}
/*
 * "free block"
 * (*block) = pool->m_next index  //then allocate pool->m_next
 * pool->m_next = block
 *
 */
void DeAllocate(Mpool *pool, void *p)
{
   if(pool->m_next !=NULL)
   {
       *(uint*)p = IndexFromAddr(pool);
       pool->m_next = (uchar *)p;
       pool->m_numFreeBlocks++;
   }
   else
   {
       *(uint*)p = pool->m_sizeOfEachBlock;
       pool->m_next = (uchar*)p;
       pool->m_numFreeBlocks++;
   }
}
void DestroyPool(Mpool *pool)
{
   free(pool->m_memStart);
   pool->m_memStart = NULL;
}
