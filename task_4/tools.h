#pragma once

#include <stdio.h>      // printf
#include <string.h>     // Basic string functionality
#include <stdlib.h>     // malloc and friends


// Get terminal height (platform specific)
#if _WIN32
#include<windows.h>

unsigned int get_terminal_height() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
#elif linux
#include <sys/ioctl.h>
#include<unistd.h>

unsigned int get_terminal_height() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}
#endif


// Easy error printing function
void* err_out(const char* message) {
    printf("%s\n", message);
    return NULL;
}

// Get the last index of an element from a string. Return -1 if not found
long long get_last_index_of(const char* string, char element) {
    long long ind = -1;
    for (long long a = strlen(string); a > 0; a--) 
        if (string[a] == element) {
            ind = a;
            break;
        }
    return ind;
}

// Check if the specified file path has a certain extension
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

// Replace exe path tail with another string
char* concat_path_from_exe_path(const char* exePath, const char* patternHead) {

    unsigned int patternLen = strlen(patternHead);

    // Find the index of the last slash
    unsigned long long slashInd = get_last_index_of(exePath, '\\');
    if (slashInd == -1) 
        slashInd = get_last_index_of(exePath, '/');

    // Prepare the concatenation buffer
    unsigned int resultSize = slashInd + 1 + patternLen;
    char* resultPath = (char*)malloc(resultSize + 1);
    
    // Memory exception
    if (resultPath == NULL) 
        return err_out("Unable to allocate heap memory!");

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