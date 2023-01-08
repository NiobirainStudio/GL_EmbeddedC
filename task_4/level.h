#pragma once
#include <stdio.h>      // printf

#if _WIN32
#include<windows.h>
#define t_sleep(time) Sleep(time)
#elif linux
#include<unistd.h>
#define t_sleep(time) sleep(time)
#endif

#include "tools.h"      // Tools header



typedef struct
{
    // Map params
    unsigned int width, height;
    char** map;

    // Start point params
    unsigned int sPosX, sPosY;

    // Exit point params
    unsigned int ePosX, ePosY;
} Level;

void print_composite(Level* level, char** map) {
    for (unsigned int a = 0; a < level->height; a++) {
        for (unsigned int b = 0; b < level->width; b++) 
            
            if (map[a][b] != ' ')
                printf("%c ", map[a][b]);
            else if (a == level->ePosY && b == level->ePosX)
                printf("E ");
            else
                printf("%c ", level->map[a][b]);
        printf("\n");
    }
}

void clear_on_input(unsigned int str_height) {
    for (unsigned int i = get_terminal_height() - str_height - 1; i > 0; i--) {
        printf("\n");
    }
    t_sleep(50);
    //system("cls");
}

char _proceed_rec(
    Level* level,
    char** completion_map,
    unsigned int currPosX, 
    unsigned int currPosY) {
    
    completion_map[currPosY][currPosX] = '#';
    print_composite(level, completion_map);
    clear_on_input(level->height);

    // Check left
    if (currPosX > 0 && completion_map[currPosY][currPosX - 1] != '#') {
        completion_map[currPosY][currPosX - 1] = '?';
        print_composite(level, completion_map);
        clear_on_input(level->height);
        if (currPosY == level->ePosY && currPosX - 1 == level->ePosX) {
            return 1;
        } else if (level->map[currPosY][currPosX - 1] == ' ') {
            if(_proceed_rec(level, completion_map, currPosX - 1, currPosY))
                return 1;
        }
        completion_map[currPosY][currPosX - 1] = ' ';
    }

    // Check up (down by indices)
    if (currPosY > 0 && completion_map[currPosY - 1][currPosX] != '#') {
        completion_map[currPosY - 1][currPosX] = '?';
        print_composite(level, completion_map);
        clear_on_input(level->height);
        if (currPosY - 1 == level->ePosY && currPosX == level->ePosX) {
            return 1;
        } else if (level->map[currPosY - 1][currPosX] == ' ') {
            if(_proceed_rec(level, completion_map, currPosX, currPosY - 1))
                return 1;
        }
        completion_map[currPosY - 1][currPosX] = ' ';
    }

    // Check right
    if (currPosX + 1 <= level->width && completion_map[currPosY][currPosX + 1] != '#') {
        completion_map[currPosY][currPosX + 1] = '?';
        print_composite(level, completion_map);
        clear_on_input(level->height);
        if (currPosY == level->ePosY && currPosX + 1 == level->ePosX) {
            return 1;
        } else if (level->map[currPosY][currPosX + 1] == ' ') {
            if(_proceed_rec(level, completion_map, currPosX + 1, currPosY))
                return 1;
        }
        completion_map[currPosY][currPosX + 1] = ' ';
    }

    // Check down (up by indices)
    if (currPosY + 1 < level->height && completion_map[currPosY + 1][currPosX] != '#') {
        completion_map[currPosY + 1][currPosX] = '?';
        print_composite(level, completion_map);
        clear_on_input(level->height);
        if (currPosY + 1 == level->ePosY && currPosX == level->ePosX) {
            return 1;
        } else if (level->map[currPosY + 1][currPosX] == ' ') {
            if(_proceed_rec(level, completion_map, currPosX, currPosY + 1))
                return 1;
        }
        completion_map[currPosY + 1][currPosX] = ' ';
    }
    
    completion_map[currPosY][currPosX] = ' ';
    print_composite(level, completion_map);
    clear_on_input(level->height);
    return 0;
}

void solve_level(Level* level) {
    // Create the completion map
    char** completion_map = (char**)malloc(level->width * sizeof(char*));
    for (unsigned int a = 0; a < level->width; a++)
        completion_map[a] = (char*)malloc(level->height * sizeof(char));
    
    for (unsigned int a = 0; a < level->height; a++)
        for (unsigned int b = 0; b < level->width; b++) 
            completion_map[a][b] = ' ';

    // Start the recursive algorithm
    char result = _proceed_rec(level, completion_map, level->sPosX, level->sPosY);
    print_composite(level, completion_map);
    clear_on_input(level->height);
    if (result) {
        printf("Maze solved! ");
    } else {
        printf("Unable to solve the maze! ");
    }

    // Delete the completion map
    for (unsigned int i = 0; i < level->width; i++)
        free(completion_map[i]);
 
    free(completion_map);
}

Level* load_level_from_file(const char* levelPath) {
    
    // Viev the file
    FILE *file;
    fopen_s(&file, levelPath, "r");
    
    // Check if the level exists
    if (file == NULL) 
        return err_out("Unable to open file!");

    // Create the level and init the fields
    Level* level = (Level*)malloc(sizeof(Level));
    level->height = 0;
    level->width = 0;
    level->map = NULL;

    unsigned char sCount = 0, eCount = 0;

    unsigned int i = 0, j = 0;

    // Read the file char-by-char
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        switch (c) {
            case 'X':   // WALL
                i++;
                break;
            
            case ' ':   // PASSAGE
                i++;
                break;
            
            case '\n':  // LINE END
                level->height++;
                if (level->width != 0 && level->width != i) {
                    free(level);
                    return err_out("Inconsistent level width!");
                }
                level->width = i;
                i = 0;
                break;
            
            case 'S':   // START
                sCount++;
                if (sCount > 1) {
                    free(level);
                    return err_out("Levels can't have more than one start points!");
                }
                level->sPosX = i;
                level->sPosY = level->height;
                i++;
                break;
            
            case 'E':   // EXIT
                eCount++;
                if (eCount > 1) {
                    free(level);
                    return err_out("Levels can't have more than one exit points!");
                }
                level->ePosX = i;
                level->ePosY = level->height;
                i++;
                break;

            default:
                free(level);
                return err_out("Unknown level symbol!");
        }
    }

    if (sCount != 1 || eCount != 1) {
        free(level);
        return err_out("No start or exit points!");
    }

    if (level->width == 0) {
        free(level);
        return err_out("Level file is empty!");
    }

    level->height++;



    // Generate the map
    level->map = (char**)malloc(level->width * sizeof(char*));
    for (unsigned int a = 0; a < level->width; a++)
        level->map[a] = (char*)malloc(level->height * sizeof(char));

    i = 0;
    rewind(file);
    while ((c = fgetc(file)) != EOF)
    {
        if (c == ' ' || c == 'X') {
            level->map[j][i] = c;
            i++;
        } else if (c == '\n') {
            j++;
            i = 0;
        } else if (c == 'S' || c == 'E') 
            i++;
    }

    return level;
}

void destroy_level(Level* level) {
    if (level == NULL)
        return;
    
    for (unsigned int i = 0; i < level->width; i++)
        free(level->map[i]);
 
    free(level->map);
    
    free(level);
}