/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: DynamicContainer.h        *
*************************************/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "DynamicPool.h"
#include "ErrorHandler.h"


typedef struct 
{

int * data;
size_t size; // current size 
size_t capacity; // max size 
pthread_mutex_t lock;

}CustomArray;

typedef enum 
{
    FALSE,
    TRUE

}bool;


/**************************************** Functions Declarations ********************************************/

void initArray(CustomArray *array, int initial_capacity);
void insertElement(CustomArray *array, int element);
void deleteElement(CustomArray *array, size_t index);
int getElement(CustomArray *array, size_t index);
void freeArray(CustomArray *array);
void PrintArray(CustomArray *array);
bool IsEmpty(CustomArray * array);
