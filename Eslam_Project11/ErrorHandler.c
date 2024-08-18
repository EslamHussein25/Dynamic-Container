/************************************
 *  Author: Eslam Hussein           *
 *  Date: 15/08/2024                *
 *  Version: 01                     *
 *  Project: Custom Container       *
 *  File: ErrorHandler.c            *
*************************************/
#include "ErrorHandler.h"


static FILE* error_log_file = NULL;

//open the error log file to write the erors in it 
#include <errno.h>
#include <string.h>


/**************************************** Functions Defintion ********************************************/

void InitLogFile(const char* filename) 
{
    error_log_file = fopen(filename, "a");
    if (error_log_file == NULL) 
    {
        fprintf(stderr, "Failed to open error log file: %s\nError: %s\n", filename, strerror(errno));
        exit(1);
    }
    else 
    {
        printf("File opend for Logging\n");
    }
}

void LogError(ErrorLevel level, const char* function, int line, const char* message) 
{
    if (error_log_file == NULL) 
    {
        fprintf(stderr, "Error logging not initialized\n");
        return;
    }

    const char* lEVEL;
    switch (level) 
    {
        case INFO:    lEVEL = "INFO";    break;
        case WARNING: lEVEL = "WARNING"; break;
        case ERROR:   lEVEL = "ERROR";   break;
        case FATAL:   lEVEL = "FATAL";   break;
        default:      lEVEL = "UNKNOWN"; break;
    }
    
    time_t now;
    time(&now);
    char* date = ctime(&now);
    date[strlen(date) - 1] = '\0'; // Remove newline
    
    fprintf(error_log_file, "[%s] %s in %s (line %d): %s \n",date , lEVEL, function, line , message);

    fflush(error_log_file);

    //handel this case here 
    if (level == FATAL) 
    {
        CloseLogFile();
        exit(1);
    }
}

void CloseLogFile() 
{
    if (error_log_file != NULL) 
    {
        fclose(error_log_file);
        error_log_file = NULL;
        printf("\n\n\nFile Closed and Saved!\n\n\n");
    }
}

