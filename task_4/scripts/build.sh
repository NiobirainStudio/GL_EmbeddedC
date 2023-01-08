set echo off
# Build script for assembling the project and copying the required files over to build directory

CURR_DIRECTORY=$(dirname $0)
PLATFORM="$1"
TARGET="$2"
SRC_FOLDER="$CURR_DIRECTORY..\*.c"

echo $CURR_DIRECTORY
echo $SRC_FOLDER

# ECHO Building everything on %PLATFORM% (%TARGET%)..."

# REM Copy files
# cp %CURR_DIRECTORY%..\level.level %CURR_DIRECTORY%..\..\build\%TARGET%

# if "%TARGET%" == "release" (
#     SET COMPILE_STR=-D_RELEASE -O3 -o %CURR_DIRECTORY%..\..\build\release\main.exe
#     ECHO %COMPILE_STR%
# ) else (
#     SET COMPILE_STR=-D_DEBUG -g -o %CURR_DIRECTORY%..\..\build\debug\main.exe
#     ECHO %COMPILE_STR%
# )

# REM Compiling the project

# clang -Wall %SRC_FOLDER% %COMPILE_STR%