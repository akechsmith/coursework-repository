#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Define the archive file and restore destination
archive_name="Johnnie.tar.gz"
restore_dir="/Users/macbook/Desktop/shell"

# Check if the archive exists
if [ -f "$archive_name" ]; then
    echo "Restoring files from $archive_name..."

    # Extract the files from the archive
    tar -xzf "$archive_name" -C "$restore_dir"

    # Verify if the files were restored
    if [ -f "$restore_dir/jokes.txt" ] && [ -f "$restore_dir/employees.json" ]; then
        echo "Files successfully restored."
    else
        echo "Error: Failed to restore one or both files."
    fi
else
    echo "Error: $archive_name not found. Please ensure the archive exists."
fi

