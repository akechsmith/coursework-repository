#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Check if the file exists
file="Angukanayo.txt"
search_string="Mpangale"

if [ -f "$file" ]; then
    # Search for the string and display line numbers
    result=$(grep -n "$search_string" "$file")
    
    if [ -n "$result" ]; then
        echo "The string '$search_string' is found in the file '$file' at the following line(s):"
        echo "$result"
    else
        echo "The string '$search_string' was not found in the file '$file'."
    fi
else
    echo "Error: The file '$file' does not exist."
fi

