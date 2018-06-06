#include "src/memory.h"

void main()
{
    Mpool pool;
    void *p1, *p2, *p3, *p4;
    void *p5;
    CreatePool(&pool, 4, 6);

    p1 = Allocate(&pool);
    printf("%x\n", p1);
    p2 = Allocate(&pool);
    printf("%x\n", p2);
    p3 = Allocate(&pool);
    printf("%x\n", p3);
    p4 = Allocate(&pool);
    printf("%x\n", p4);
    p5 = Allocate(&pool);
    printf("%x\n", p5);

    DeAllocate(&pool, p1);
    printf("free p1 \n");
    DeAllocate(&pool, p3);
    printf("free p3 \n");
    DeAllocate(&pool, p2);
    printf("free p2 \n");
    
    p5 = Allocate(&pool);
    printf("%x\n", p5);
    p5 = Allocate(&pool);
    printf("%x\n", p5);
    p5 = Allocate(&pool);
    printf("%x\n", p5);
    p5 = Allocate(&pool);
    printf("%x\n", p5);

    DestroyPool(&pool);
}
