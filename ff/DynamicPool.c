/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: DynamicPool.c             *
*************************************/
#include  "DynamicPool.h"


/**************************************** Functions Defintion ********************************************/

// Initialize the memory Pool
MemoryPool* AllocatePool(int BLOCK_SIZE) 
{
    //alocate new pointer in the memoery heap to point to the main containers first is pool and second is blocks 
    MemoryPool* mp = (MemoryPool*)malloc(sizeof(MemoryPool));
    if(!mp)
    {
        return NULL ;
    }
    //alocate the memeory of the pool and blocks 
    mp->Pool = (char*)malloc(POOL_SIZE * BLOCK_SIZE); // char Pool[POOL_SIZE * BLOCK_SIZE]; IN stack Pool ;; this array of Pools and single Pool is char just to point to it  
    if(!mp->Pool)
    {
        return NULL ;
    }
    mp->Blocks = (int*)malloc(POOL_SIZE * sizeof(int)); // int Blocks[POOL_SIZE]; in stack Pool ;; here we acutual reserve this area 
    if(!mp->Blocks)
    {
        return NULL ;
    }
    mp->FreeBlocks = POOL_SIZE; //int FreeBlocks = POOL_SIZE; in stack Pool 
    mp->ReservedBlocks = 0 ;

    //mark every block inside the pool with init number to accessed then using this number 
    for (int i = 0; i < POOL_SIZE; i++) 
    {
        mp->Blocks[i] = i;
    }

    return mp;
}

// Allocate from the Pool
void * AllocateBlock(MemoryPool* mp , int BLOCK_SIZE) 
{
    if (mp->FreeBlocks == 0) 
    {
        return NULL;
    }
    //get the number of the block whcih i have to  start allocate from it  and increased the reserved blocks 
    int block = mp->Blocks[mp->ReservedBlocks++];
   // printf("Block number: %d\n" , block);
   //decreased the free blocks
    mp->FreeBlocks-- ;
    //return the current space of the block size inside the pool itself 
    return &mp->Pool[block * BLOCK_SIZE];
}

// Free memory back to the Pool
void DeallocateBlock(MemoryPool* mp, void* ptr , int BLOCK_SIZE) 
{
    //get the current block to remove 
    int block = ((char*)ptr - mp->Pool) / BLOCK_SIZE;
    //decreaesd the blocks whcih reserved 
    mp->Blocks[mp->ReservedBlocks--] = block;
    //increased the free blocks 
    mp->FreeBlocks++;
}

// Destroy the memory Pool
void DestroyPool(MemoryPool* mp) 
{
    //destroy any memeoery reserved in the heap 
    free(mp->Pool);
    free(mp->Blocks);
    free(mp);
}

