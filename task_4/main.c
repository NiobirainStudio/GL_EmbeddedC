#include "tools.h"      // Additional tools header
#include "level.h"      // Maze level header



int main(int argc, char *argv[])
{
    // Get system path to level file
    char* levelPath = concat_path_from_exe_path(argv[0], "level.level");
    if (levelPath == NULL)
        goto Exit;

    // Get the level data
    Level* level = load_level_from_file(levelPath);
    free(levelPath);
    if (level == NULL)
        goto Exit;

    solve_level(level);

    destroy_level(level);

    return 0;

    Exit:
        printf("Unexpected program termination.\n");
        return 1;
}
