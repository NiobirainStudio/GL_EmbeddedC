# Build script for assembling the project and copying the required files over to build directory

CURR_DIRECTORY=$(dirname $0)
PLATFORM=$1
TARGET=$2
SRC_FOLDER="$CURR_DIRECTORY/../*.c"

echo "Building everything on $PLATFORM ($TARGET)..."

# Create build directory if not exists
mkdir -p $CURR_DIRECTORY/../../build/$TARGET/

# Copy files
cp $CURR_DIRECTORY/../level.level $CURR_DIRECTORY/../../build/$TARGET/

if [ $TARGET = "release" ]
then
    COMPILE_STR="-D_RELEASE -O3 -o $CURR_DIRECTORY/../../build/release/main.out"
else
    COMPILE_STR="-D_DEBUG -g -o $CURR_DIRECTORY/../../build/debug/main.out"
fi

# Compiling the project
gcc -Wall $SRC_FOLDER $COMPILE_STR