/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: DynamicContainer.c        *
*************************************/
#include "DynamicContainer.h"

MemoryPool * MyPool ;

/**************************************** Functions Defintion ********************************************/
void initArray(CustomArray * array, int initial_capacity)
{
    //create new block size in the heap 
    if(initial_capacity < 0 )
    {
        printf("Error in allocation \n..Error in logger file ./ErrorLogger.log !\n");
        LogError(FATAL , "initArray" , (__LINE__ - 6) , "Enter postive number for container size!");
       // exit(EXIT_FAILURE);
    }
    else 
    {
        //alocate new Pool in the heap memory to be ready for allocation 
        MyPool = AllocatePool(initial_capacity);
        //can't allocate this Pool 
        if (!MyPool) 
        {
            printf("Memory allocation failed \n..Error in logger file ./ErrorLogger.log !\n");
            LogError(FATAL , "initArray" , __LINE__ , "Can't Allocate new space in the heap:\n may be have alot of fregmentions or buffer size bigger than heap free space !");
            exit(EXIT_FAILURE);
        }
        else 
        {
            array->capacity = initial_capacity ;
            array->size = 0 ;
            pthread_mutex_init(&(array->lock), NULL);
        }
    }
}

void insertElement(CustomArray *array, int element)
{
    //mutex lock for thread safe 
    pthread_mutex_lock(&(array->lock)) ;
    
    //calcluse the current index which we must indeicate to it 
    int BlockIndex = (array->size / array->capacity) ;
    //to calculate if we need to allocate new block or not 
    int BlockIsFull = (array->size  % array->capacity) ;

    if(BlockIsFull == 0) // we need to allocate new block incase the current block is full  
    {
        if(BlockIndex != 0)
        {
            printf("Warning: the array capacity is over and we will allocate new space for you with multiple of the array capcity:\n");
            LogError(WARNING , "insertElement" , (__LINE__ - 14) , "the array capacity is over and we will allocate new space for you with multiple of the array capcity");
        }
        //printf("Allocate new block!: %d\n" , BlockIndex) ;
        int * check = AllocateBlock(MyPool , array->capacity * sizeof(int)); // add new block 
        if(check == NULL)
        {
            printf("Can't Resize the container and add new elements  \n..Error in logger file ./ErrorLogger.log !\n");
            LogError(ERROR , "insertElement" , __LINE__ , "Can't Resize the container and add new elements beacuse the buffer is full ");
        }
    }
    //point to the current block inside the Pool 
    array->data = (int*)&MyPool->Pool[  (BlockIndex * array->capacity * sizeof(int))  ];
    // the real index mean the index inside the block within the array capacity like from 0 to 5
    //so calculate which index we have to start from 
    int RealIndex = array->size - (BlockIndex * array->capacity) ;
    //add the new data element to this index in the true block
    array->data[RealIndex] = element ;
    //printf("array size: %ld\n" , array->size);
    //increament the size of the array 
    //don't care about the capacity 
    array->size++;
        
    //mutex unlock 
    pthread_mutex_unlock(&(array->lock)) ;

}

int getElement(CustomArray *array, size_t index)
{
    int Data = 0 ;
    if(index < 0)
    {
        printf("Invalid Index !   \n..Error in logger file ./ErrorLogger.log !\n");
        LogError(ERROR , "getElement" , (__LINE__ - 6) , "Invalid Index!");
        return 0 ;
    }
    else if(index >= array->size)
    {
        printf(" Out of range !   \n..Error in logger file ./ErrorLogger.log !\n");
        LogError(ERROR , "getElement" , (__LINE__ - 12) , "Out of range !");
        return 0;
    }
    else 
    {
        //if not the first block 
        if(index >= array->capacity)
        {
            // calculate the block index 
            int BlockIndex = (index / array->capacity) ;
            // calculate the index inside the block 
            int RealIndex = (index - (BlockIndex * array->capacity) ) ;
            //adjust the array  to the true block whcih have our data 
            array->data = (int*)&MyPool->Pool[BlockIndex * array->capacity * sizeof(int)];
            //point to the data inside this block 
            Data = array->data[RealIndex];

        }
        else 
        {
            //adjust out pointer to the first block dirctly 
            array->data = (int*)&MyPool->Pool[0];
            //point and get the true data from true index inside this block 
            Data = array->data[index]; 
        }
    }
    return Data ;
}

void deleteElement(CustomArray *array, size_t index)
{
    //lock gurd during to this operation 
    pthread_mutex_lock(&(array->lock));

    if (IsEmpty(array))
    {
        printf("Invalid index or empty array. \n..Error in logger file ./ErrorLogger.log !\n");   
        LogError(ERROR , "deleteElement" ,( __LINE__  - 8), " Invalid index or empty array.");
        pthread_mutex_unlock(&(array->lock));
        return;
    }
    else if(index >= array->size)
    {
        printf("Empty array. \n..Error in logger file ./ErrorLogger.log !\n");   
        LogError(ERROR , "deleteElement" ,( __LINE__  - 15), " Empty array no elements to delete insert some elemets to delete it (^_-) ");
        pthread_mutex_unlock(&(array->lock));
        return;
    }

    // Find the block and real index
    int BlockIndex = index / array->capacity; // block number 
    int RealIndex = index % array->capacity; // index inside the block 

    // Get the current block
    array->data = (int*)&MyPool->Pool[BlockIndex * array->capacity * sizeof(int)];

    for (size_t counter = index , IndexCounter = RealIndex ; counter < array->size - 1; counter++ , IndexCounter++)
    {
        
       // printf("data: %d\n" , array->data[IndexCounter]);
        if(IndexCounter == array->capacity) // this block is over shift to the next block 
        {
            BlockIndex++;
            if(BlockIndex <= MyPool->ReservedBlocks) // to make sure we arrived to the last reserved block in the Pool 
            {
                array->data = (int*)&MyPool->Pool[BlockIndex * array->capacity * sizeof(int)];
                int FirstBlockElement = array->data[0];
                BlockIndex--;
                array->data = (int*)&MyPool->Pool[BlockIndex * array->capacity * sizeof(int)];
                array->data[array->capacity] = FirstBlockElement ;
                BlockIndex++;
                array->data = (int*)&MyPool->Pool[BlockIndex * array->capacity * sizeof(int)];
                IndexCounter = 0;
            }
        }
        array->data[IndexCounter] = getElement(array , (counter + 1));  
    }
    
    
    array->size--;
    //check if block is embty to deallocate this block 
    //Last block we point to 
    int LastBlock = BlockIndex ;
    //calcluate the current block 
    BlockIndex = (array->size / array->capacity) ;
    if((BlockIndex - LastBlock) > 0)
    {
        printf("\nDealocation\n");
        // there are more block not needed , deleted 
        printf("the number of blocks now: %d\n" , MyPool->ReservedBlocks);
        DeallocateBlock(MyPool , array->data , array->size);
        printf("the number of blocks now: %d\n" , MyPool->ReservedBlocks);
    }
    //unlock gurd when op is over 
    pthread_mutex_unlock(&(array->lock)) ;

}

void PrintArray(CustomArray *array)
{
    pthread_mutex_lock(&(array->lock));
    if(array->size != 0)
    {
        for(int count = 0 ; count < array->size ; count++)
        {
            printf("%d\n" , getElement(array , count));
        } 
        printf("\n");
    }
    else 
    {
        printf("Empty array. \n..Error in logger file ./ErrorLogger.log !\n");   
        LogError(INFO , "PrintArray" ,( __LINE__  - 14), "Empty array no elements to show it , insert some elemets to show it (^_-) ");  
    }
    pthread_mutex_unlock(&(array->lock)) ;
}

void freeArray(CustomArray *array)
{
    DestroyPool(MyPool);
}

bool IsEmpty(CustomArray * array)
{
    bool Answer ;
    if(array->size == 0)
    {
        //Array Embty
        Answer = TRUE ;
    }
    else 
    {
        Answer = FALSE ;
    }
    return Answer ;
}

