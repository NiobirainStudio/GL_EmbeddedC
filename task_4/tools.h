#pragma once

#include <stdio.h>      // printf
#include <string.h>     // Basic string functionality
#include <stdlib.h>     // malloc and friends



unsigned int get_last_index_of(const char* string, char element) {
    unsigned long long ind = -1;
    for (unsigned long long a = strlen(string); a > 0; a--) 
        if (string[a] == element) {
            ind = a;
            break;
        }
    return ind;
}

char is_of_extension(const char* filePath, const char* extension) {
    unsigned long long dotInd = get_last_index_of(filePath, '.');
    if (dotInd == -1) {
        printf("File has no extension!\n");
        return -1;
    }

    char result = 1;

    unsigned long long extensionLen = strlen(extension);

    if (strlen(filePath) - dotInd - 1 != strlen(extension)) return 0;
    
    for (unsigned long long a = 0; a < extensionLen; a++)
        if (filePath[dotInd + 1 + a] != extension[a])
            result = 0;

    return result;
} 


const char* concat_path_from_exe_path(const char* exePath, const char* patternHead) {

    unsigned int patternLen = strlen(patternHead);

    // Find the index of the last slash
    unsigned long long slashInd = get_last_index_of(exePath, '\\');
    if (slashInd == -1) 
        slashInd = get_last_index_of(exePath, '/');

    // Prepare the concatenation buffer
    unsigned int resultSize = slashInd + 1 + patternLen;
    char* resultPath = (char*)malloc(resultSize + 1);
    
    // Memory exception
    if (resultPath == NULL) {
        printf("Unable to allocate heap memory!\n");
        return NULL;
    }

    // String ending
    resultPath[resultSize] = '\0';

    // Concatenate strings
    if (slashInd != -1) 
        for (unsigned long long a = 0; a <= slashInd; a++)
            resultPath[a] = exePath[a];
    
    for (unsigned long long a = 0; a < patternLen; a++)
        resultPath[slashInd + 1 + a] = patternHead[a];

    return resultPath;
}