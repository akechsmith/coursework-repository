#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Check if jokes.txt exists
if [ -f "jokes.txt" ]; then
    echo "Displaying lines 2 to 7 from jokes.txt:"
    sed -n '2,7p' jokes.txt
else
    echo "Error: jokes.txt not found. Please download the file first."
fi
