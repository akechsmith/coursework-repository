#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Prompt user for the directory path
read -p "Enter the directory path containing .jpg files: " dir_path

# Check if the directory exists
if [ -d "$dir_path" ]; then
    echo "Checking for .jpg files in: $dir_path"

    # Find all .jpg files and convert them to .tiff
    jpg_files=$(find "$dir_path" -type f -iname "*.jpg")
    converted_count=0

    for file in $jpg_files; do
        # Get the filename without the extension
        base_name=$(basename "$file" .jpg)
        
        # Convert the .jpg file to .tiff
        convert "$file" "$dir_path/$base_name.tiff"

        if [ $? -eq 0 ]; then
            echo "Converted: $file to $dir_path/$base_name.tiff"
            ((converted_count++))
        else
            echo "Error converting: $file"
        fi
    done

    # Output the number of images converted
    echo "Total number of images converted: $converted_count"
else
    echo "Error: The directory '$dir_path' does not exist."
fi
