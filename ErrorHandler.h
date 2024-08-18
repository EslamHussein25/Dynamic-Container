/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: ErrorHandler.h            *
*************************************/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

// Error levels
typedef enum 
{
    INFO,
    WARNING,
    ERROR,
    FATAL

} ErrorLevel;

/**************************************** Functions Declarations ********************************************/

// Initialize error logging
void InitLogFile(const char* filename);

// Log an error to our opended file 
void LogError(ErrorLevel level, const char* function, int line, const char* message) ;

// Close error logging
void CloseLogFile();

