/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: Test.c                    *
*************************************/
#include "Test.h"


void Test_initArray() 
{
    printf("\nRun Test_initArray\n");
    CustomArray array;

    initArray(&array, 5);
    assert(array.capacity == 5);
    assert(array.size == 0);
    LogError(INFO, "Test_initArray" ,__LINE__,  "==========>initArray Test Passed");
    printf("\n==========>initArray Test Passed\n");
    freeArray(&array);
}

void Test_insertElement() 
{
    printf("\nRun Test_insertElement\n");
    CustomArray array;

    initArray(&array, 5);
    
    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    assert(getElement(&array, 0) == 10);
    assert(getElement(&array, 1) == 20);
    assert(getElement(&array, 2) == 30);
    assert(array.size == 3);
    
    // Test expansion
   /* insertElement(&array, 40);
    assert(getElement(&array, 3) == 40);
    assert(array.size == 4);*/
    
    LogError(INFO, "Test_insertElement" ,__LINE__,  "==========>insertElement Test Passed");
    printf("\n==========>insertElement Test Passed\n");
    freeArray(&array);
}

void Test_PrintArray() 
{
    printf("\nRun Test_PrintArray\n");
    CustomArray array;

    initArray(&array, 3);
    
    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    
    printf("Expected output:\n10\n20\n30\n");
    printf("Actual output: \n");
    PrintArray(&array);
    
    LogError(INFO, "Test_PrintArray" ,__LINE__,  "==========>PrintArray Test Passed if the result is identical");
    printf("\n==========>PrintArray Test Passed if the result is identical\n");
    freeArray(&array);
}

void Test_deleteElement() 
{    
    printf("\nRun Test_deleteElement\n");
    CustomArray array;
    initArray(&array, 5);
    
    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    insertElement(&array, 40);
    insertElement(&array, 50);
    
    deleteElement(&array, 2);
    assert(getElement(&array, 2) == 40);
    assert(array.size == 4);
    
    deleteElement(&array, 0);
    assert(getElement(&array, 0) == 20);
    assert(array.size == 3);
    
    
    LogError(INFO, "Test_deleteElement" ,__LINE__,  "==========>deleteElement Test Passed");
    printf("\n==========>deleteElement Test Passed\n");
    freeArray(&array);
}

void Test_getElement() 
{
    printf("\nRun Test_getElement\n");
    CustomArray array;
    initArray(&array, 3);
    
    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    
    assert(getElement(&array, 0) == 10);
    assert(getElement(&array, 1) == 20);
    assert(getElement(&array, 2) == 30);
    
    // Test accessing element in a new block
    insertElement(&array, 40);
    assert(getElement(&array, 3) == 40);
    
    LogError(INFO, "Test_getElement" ,__LINE__,  "==========>getElement Test Passed");
    printf("\n==========>getElement Test Passed\n");
    freeArray(&array);
}

void Test_IsEmpty() 
{
    printf("\nRun Test_IsEmpty\n");
    CustomArray array;
    initArray(&array, 3);
    
    assert(IsEmpty(&array) == TRUE);
    
    insertElement(&array, 10);
    assert(IsEmpty(&array) == FALSE);
    
    LogError(INFO, "Test_IsEmpty" ,__LINE__,  "==========>IsEmpty Test Passed");
    printf("\n==========>IsEmpty Test Passed\n");
    freeArray(&array);
}



int main()
{
    InitLogFile("ErrorLogger.log");

    printf("\n<===========Test Result==========>\n");
    Test_initArray();
    Test_insertElement();
    Test_PrintArray();
    Test_deleteElement();
    Test_getElement();
    Test_IsEmpty();
    printf("\n<===========Test Ended==========>\n");

    CloseLogFile();
  
return 0;
}