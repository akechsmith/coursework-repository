#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Check if both files exist
if [ -f "jokes.txt" ] && [ -f "employees.json" ]; then
    echo "Generating MD5 checksum for jokes.txt and employees.json..."

    # Generate checksums and save to MD5SUM file
    md5 jokes.txt > MD5SUM
    md5 employees.json >> MD5SUM

    echo "MD5 checksums saved to MD5SUM file."
else
    echo "Error: One or both files not found. Please ensure jokes.txt and employees.json are downloaded."
fi

