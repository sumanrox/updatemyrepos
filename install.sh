#!/bin/bash

# Check if GCC is installed
if ! command -v gcc &> /dev/null; then
    echo "GCC is not installed. Please install GCC to compile the tool."
    exit 1
fi

# Compile the tool
gcc -o updatemyrepos updatemyrepos.c

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Copy the tool to /usr/bin/
    sudo cp updatemyrepos /usr/bin/

    # Check if copy was successful
    if [ $? -eq 0 ]; then
        echo "Tool installed in /usr/bin/updatemyrepos."
        exit 0
    else
        echo "Error: Failed to install the tool."
        exit 1
    fi
else
    echo "Error: Compilation failed."
    exit 1
fi
