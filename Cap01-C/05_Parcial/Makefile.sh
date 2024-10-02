#!/bin/bash

# Usage check
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <output_executable> <source_files...>"
    exit 1
fi

# Compiler and flags
CC=clang
CFLAGS="-Wall"

# Output executable
OUTPUT=$1
shift  # Move past the output name to get the source files

# Source and object files
SRC_FILES="$@"
OBJ_FILES=$(echo "$SRC_FILES" | sed 's/\.c/\.o/g')

# Compile each source file
for src in $SRC_FILES; do
    obj="${src%.c}.o"
    echo "Compiling $src to $obj"
    $CC $CFLAGS -c "$src" -o "$obj"
done

# Link object files into the final executable
echo "Linking object files to create $OUTPUT"
$CC $CFLAGS $OBJ_FILES -o "$OUTPUT"

# Clean up object files (optional)
# rm $OBJ_FILES

echo "Build completed successfully!"
