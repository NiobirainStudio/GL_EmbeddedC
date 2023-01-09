#pragma once
#include <stdio.h>      // printf


// Const define section 
// (if your level has other characters you may replace the current ones)
#define WALL_CHAR 'X'
#define SPACE_CHAR ' '
#define START_CHAR 'S'
#define EXIT_CHAR 'E'
#define SNAKE_CHAR '+'
#define CHECK_CHAR '?'
#define FRAME_TIME_MS 50


void clear_on_input();

// Terminal cursor reset (platform specific)
#if _WIN32
#include<windows.h>

void clear_on_input() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
    Sleep(FRAME_TIME_MS);
}
#elif linux
#include<unistd.h>

void clear_on_input() {
    printf("\033[%d;%dH",1,1);
    usleep(FRAME_TIME_MS * 1000);
}
#endif

#include "tools.h"      // Tools header


// Maze level structure 
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

// Print the level and it's completion mask
void print_composite(Level* level, char** map) {
    for (unsigned int a = 0; a < level->height; a++) {
        for (unsigned int b = 0; b < level->width; b++) 
            
            if (map[a][b] != SPACE_CHAR)
                printf("%c ", map[a][b]);
            else if (a == level->ePosY && b == level->ePosX)
                printf("%c ", EXIT_CHAR);
            else
                printf("%c ", level->map[a][b]);
        printf("\n");
    }
}

// *Private* function for recursive exit search 
char _proceed_rec(
    Level* level,
    char** completion_map,
    unsigned int currPosX, 
    unsigned int currPosY) {
    
    completion_map[currPosY][currPosX] = SNAKE_CHAR;
    print_composite(level, completion_map);
    clear_on_input();

    // Check left
    if (currPosX > 0 && completion_map[currPosY][currPosX - 1] != SNAKE_CHAR) {
        completion_map[currPosY][currPosX - 1] = CHECK_CHAR;
        print_composite(level, completion_map);
        clear_on_input();
        if (currPosY == level->ePosY && currPosX - 1 == level->ePosX) {
            return 1;
        } else if (level->map[currPosY][currPosX - 1] == SPACE_CHAR) {
            if(_proceed_rec(level, completion_map, currPosX - 1, currPosY))
                return 1;
        }
        completion_map[currPosY][currPosX - 1] = SPACE_CHAR;
    }

    // Check up (down by indices)
    if (currPosY > 0 && completion_map[currPosY - 1][currPosX] != SNAKE_CHAR) {
        completion_map[currPosY - 1][currPosX] = CHECK_CHAR;
        print_composite(level, completion_map);
        clear_on_input();
        if (currPosY - 1 == level->ePosY && currPosX == level->ePosX) {
            return 1;
        } else if (level->map[currPosY - 1][currPosX] == SPACE_CHAR) {
            if(_proceed_rec(level, completion_map, currPosX, currPosY - 1))
                return 1;
        }
        completion_map[currPosY - 1][currPosX] = SPACE_CHAR;
    }

    // Check right
    if (currPosX + 1 <= level->width && completion_map[currPosY][currPosX + 1] != SNAKE_CHAR) {
        completion_map[currPosY][currPosX + 1] = CHECK_CHAR;
        print_composite(level, completion_map);
        clear_on_input();
        if (currPosY == level->ePosY && currPosX + 1 == level->ePosX) {
            return 1;
        } else if (level->map[currPosY][currPosX + 1] == SPACE_CHAR) {
            if(_proceed_rec(level, completion_map, currPosX + 1, currPosY))
                return 1;
        }
        completion_map[currPosY][currPosX + 1] = SPACE_CHAR;
    }

    // Check down (up by indices)
    if (currPosY + 1 < level->height && completion_map[currPosY + 1][currPosX] != SNAKE_CHAR) {
        completion_map[currPosY + 1][currPosX] = CHECK_CHAR;
        print_composite(level, completion_map);
        clear_on_input();
        if (currPosY + 1 == level->ePosY && currPosX == level->ePosX) {
            return 1;
        } else if (level->map[currPosY + 1][currPosX] == SPACE_CHAR) {
            if(_proceed_rec(level, completion_map, currPosX, currPosY + 1))
                return 1;
        }
        completion_map[currPosY + 1][currPosX] = SPACE_CHAR;
    }
    
    completion_map[currPosY][currPosX] = SPACE_CHAR;
    print_composite(level, completion_map);
    clear_on_input();
    return 0;
}

// Tries to solve the specified level
void solve_level(Level* level) {
    // Create the completion map
    char** completion_map = (char**)malloc(level->width * sizeof(char*));
    for (unsigned int a = 0; a < level->width; a++)
        completion_map[a] = (char*)malloc(level->height * sizeof(char));
    
    for (unsigned int a = 0; a < level->height; a++)
        for (unsigned int b = 0; b < level->width; b++) 
            completion_map[a][b] = SPACE_CHAR;

    // Clear the screen before printing
    system("clear");

    // Start the recursive algorithm
    char result = _proceed_rec(level, completion_map, level->sPosX, level->sPosY);
    completion_map[level->sPosY][level->sPosX] = START_CHAR;
    if (result) {
        completion_map[level->ePosY][level->ePosX] = EXIT_CHAR;
        print_composite(level, completion_map);
        printf("Maze solved!\n");
    } else {
        print_composite(level, completion_map);
        printf("Unable to solve the maze!\n");
    }

    // Delete the completion map
    for (unsigned int i = 0; i < level->width; i++)
        free(completion_map[i]);
 
    free(completion_map);
}

// Load level from a file
Level* load_level_from_file(const char* levelPath) {
    
    // Viev the file
    FILE *file;
    
    #if _WIN32
    fopen_s(&file, levelPath, "r");
    #elif linux
    file = fopen(levelPath, "r");
    #endif

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
    char c, l = '-';
    while ((c = fgetc(file)) != EOF)
    {
        switch (c) {
            case WALL_CHAR:    // WALL
                i++;
                break;
            
            case SPACE_CHAR:   // PASSAGE
                i++;
                break;
            
            case '\n':         // LINE END
                if (i == 0) 
                    break;
                level->height++;

                // Level width is different in certain parts
                if (level->width != 0 && level->width != i) {
                    free(level);
                    fclose(file);
                    return err_out("Inconsistent level width!");
                }
                level->width = i;
                i = 0;
                break;
            
            case START_CHAR:   // START
                sCount++;

                // Too many start points
                if (sCount > 1) {
                    free(level);
                    fclose(file);
                    return err_out("Levels can't have more than one start points!");
                }
                level->sPosX = i;
                level->sPosY = level->height;
                i++;
                break;
            
            case EXIT_CHAR:   // EXIT
                eCount++;

                // Too many exit points
                if (eCount > 1) {
                    free(level);
                    fclose(file);
                    return err_out("Levels can't have more than one exit points!");
                }
                level->ePosX = i;
                level->ePosY = level->height;
                i++;
                break;

            default:           // UNKNOWS CHAR
                free(level);
                fclose(file);
                return err_out("Unknown level symbol!");
        }
        l = c;
    }

    // If the level is a single line
    if (level->height == 0 && i != 0)
        level->width = i;

    // No start/exit points found
    if (sCount != 1 || eCount != 1) {
        free(level);
        fclose(file);
        return err_out("No start or exit points!");
    }

    // Level file is empty
    if (level->width == 0) {
        free(level);
        fclose(file);
        return err_out("Level file is empty!");
    }

    if (l != '\n')
        level->height++;



    // Generate the map
    level->map = (char**)malloc(level->width * sizeof(char*));
    for (unsigned int a = 0; a < level->width; a++)
        level->map[a] = (char*)malloc(level->height * sizeof(char));

    i = 0;
    rewind(file);
    while ((c = fgetc(file)) != EOF)
    {
        if (c == SPACE_CHAR || c == WALL_CHAR) {
            level->map[j][i] = c;
            i++;
        } else if (c == '\n' && i != 0) {
            j++;
            i = 0;
        } else if (c == START_CHAR || c == EXIT_CHAR) 
            i++;
    }

    // Close the file
    fclose(file);

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