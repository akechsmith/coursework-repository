#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Prompt user for a directory path
read -p "Enter the directory path to check: " dir_path

# Check if the directory exists
if [ -d "$dir_path" ]; then
    echo "Checking for empty folders in: $dir_path"

    # Find empty directories and store them in a temporary file
    empty_folders=$(find "$dir_path" -type d -empty)

    if [ -n "$empty_folders" ]; then
        echo "List of empty folders:"
        echo "$empty_folders"
        
        # Count the number of empty folders
        count=$(echo "$empty_folders" | wc -l)
        echo "Total number of empty folders: $count"

        # Display creation times
        echo "Creation times of empty folders:"
        for folder in $empty_folders; do
            # Use stat to retrieve creation time
            creation_time=$(stat -f "%SB" -t "%Y-%m-%d %H:%M:%S" "$folder" 2>/dev/null)
            echo "$folder - Created on: $creation_time"
        done
    else
        echo "No empty folders found in the directory."
    fi
else
    echo "Error: The directory path '$dir_path' does not exist."
fi

