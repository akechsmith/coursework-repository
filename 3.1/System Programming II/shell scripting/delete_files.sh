#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Define the files to delete
jokes_file="/Users/macbook/Desktop/shell/jokes.txt"
json_file="/Users/macbook/Desktop/shell/employees.json"

# Check if both files exist
if [ -f "$jokes_file" ] && [ -f "$json_file" ]; then
    echo "Deleting jokes.txt and employees.json..."

    # Delete the files
    rm "$jokes_file" "$json_file"

    # Verify if the files were deleted
    if [ ! -f "$jokes_file" ] && [ ! -f "$json_file" ]; then
        echo "Files successfully deleted."
    else
        echo "Error: Failed to delete the files."
    fi
else
    echo "Error: One or both files not found. Please ensure jokes.txt and employees.json exist."
fi
