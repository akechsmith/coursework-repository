#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Define the files to archive
jokes_file="/Users/macbook/Desktop/shell/jokes.txt"
json_file="/Users/macbook/Desktop/shell/employees.json"
archive_name="Johnnie.tar.gz"

# Check if both files exist
if [ -f "$jokes_file" ] && [ -f "$json_file" ]; then
    echo "Archiving jokes.txt and employees.json into $archive_name..."

    # Create the tarball archive
    tar -czf "$archive_name" -C "/Users/macbook/Desktop/shell" "jokes.txt" "employees.json"

    # Confirm the archive was created
    if [ -f "$archive_name" ]; then
        echo "Files successfully archived as $archive_name."
    else
        echo "Error: Failed to create the archive."
    fi
else
    echo "Error: One or both files not found. Please ensure jokes.txt and employees.json exist."
fi

