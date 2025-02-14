#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Check if the file exists
file="Angukanayo.txt"

if [ -f "$file" ]; then
    # Count characters (including spaces) using wc command
    char_count=$(wc -c < "$file")
    echo "The file '$file' contains $char_count characters (including white spaces)."
else
    echo "Error: The file '$file' does not exist."
fi

