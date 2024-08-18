# Custom contanier in c 

## Description 
- this code is a Dynamic memeory container allocation with this specs:
    - insert elements without care about inital capcaity so autoresize 
    - get any element with the index access only 
    - deleted any element with it's index only 
    - print all elements in the memeory 
    - auto dealocation for none memory use 
    - api for destroy every thing for this container 

## Code Files with Description
- DynamicContainer.c --> for main api's for the dynamic array 
- DynamicContainer.h
- DynamicPool.c --> for pool work like allocate new pool and blocks 
- DynamicPool.h
- ErrorHandler.c --> for open , log and close the error file 
- ErrorHandler.h
- Test.c --> this file containing on the main funtion and this the main file to run all the files in main with test cases 
- Test.h


## Requirements
- gcc compiler 
- cmake VERSION 3.10
- make 
- valgrind tool for heap testing 
- OS: any 
- time command for calculate the time execution and cpu usage 

## How to build this API's 
- use this commands to build 
    - ```git clone repolink```
    - ```cd reponame/build ```
    - ```cmake ../ ```
- or use the this command for normal build without make and cmake 
    - ```gcc  DynamicContainer.c  DynamicPool.c  ErrorHandler.c Test.c -pthread ```
        - test file is the main file so run the outout file ``` a.out ``` and edit in test file 

## How to run and test this API's 
- ``` make TestExecutable ```
-  Use this command to run this file directly ```./bin/TestExecutable```  this file is the Test file with some cases for every parameter 


## Avaliable API's 
- ```void initArray(CustomArray * array, int initial_capacity)``` 
   - init new container using the pool mechneism
   - input parameters: 
    - custom array passed by user 
    - inital capacity 
- ```void insertElement(CustomArray *array, int element)``` 
   - insert element in the container with auto resize so if  the    container array inital capacity is over will give you warning about this and allocate new block inside the pool the block size is the same first inital capacity value by default 
   - input parameters: 
    - custom array passed by user 
    - elment value to add 
- ```void deleteElement(CustomArray *array, size_t index)``` 
   - delete element in the container  with auto resize so if any container is become empty will deallocate it to allocate it in the feuature again 
   - input parameters: 
    - custom array passed by user 
    - elment value to delete 
- ```int getElement(CustomArray *array, size_t index)``` 
   - to get the element from array using main index don't  care about the inital value capacity here we care about the main size of the array 
   - input parameters: 
    - custom array passed by user 
    - index to get it's value if valid 
   - return 
    - the element which we passed it's index if index is valid 
- ```void freeArray(CustomArray *array)``` 
   - to get the element from array using main index don't  care about the inital value capacity here we care about the main size of the array 
   - input parameters: 
    - custom array passed by user 
    - index to get it's value if valid     
- ```void PrintArray(CustomArray *array)``` 
   - print all elements inside the container 
   - input parameters: 
    - custom array passed by user    
- ```bool IsEmpty(CustomArray * array)``` 
   - return true if the array is empty and false if not 
   - input parameters: 
    - custom array passed by user    



## Output files 
- if using make and cmake
    - main output file for run```./buid/bin/TestExecutable```
- if using gcc to build 
    - the output file is ```./a.out```
- ErrorLogger.log 



