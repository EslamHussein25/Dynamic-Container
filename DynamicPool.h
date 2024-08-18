/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: DynamicPool.h             *
*************************************/
#include <stdio.h>
#include <stdlib.h>

#define POOL_SIZE 100

// Memory pool structure
typedef struct 
{
    char* Pool;
    int* Blocks;
    int FreeBlocks;
    int ReservedBlocks;

} MemoryPool;



/**************************************** Functions Declrations ********************************************/

// Initialize the memory pool
MemoryPool* AllocatePool(int BLOCK_SIZE) ;

// Allocate from the pool
void * AllocateBlock(MemoryPool* mp , int BLOCK_SIZE) ;

// Free memory back to the pool
void DeallocateBlock(MemoryPool* mp, void* ptr , int BLOCK_SIZE) ;

// Destroy the memory pool
void DestroyPool(MemoryPool* mp);
