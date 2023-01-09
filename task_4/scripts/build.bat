@ECHO OFF
REM Build script for assembling the project and copying the required files over to build directory

SET CURR_DIRECTORY=%~dp0
SET PLATFORM=%1
SET TARGET=%2
SET SRC_FOLDER=%CURR_DIRECTORY%..\*.c

ECHO Building everything on %PLATFORM% (%TARGET%)...

REM Create build directory if not exists
mkdir %CURR_DIRECTORY%..\..\build\%TARGET%\

REM Copy files
cp %CURR_DIRECTORY%..\level.level %CURR_DIRECTORY%..\..\build\%TARGET%\

if "%TARGET%" == "release" (
    SET COMPILE_STR=-D_RELEASE -O3 -o %CURR_DIRECTORY%..\..\build\release\main.exe
) else (
    SET COMPILE_STR=-D_DEBUG -g -o %CURR_DIRECTORY%..\..\build\debug\main.exe
)

REM Compiling the project
clang -Wall %SRC_FOLDER% %COMPILE_STR%