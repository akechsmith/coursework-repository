#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Define the files to compare
jokes_file="/Users/macbook/Desktop/shell/jokes.txt"
json_file="/Users/macbook/Desktop/shell/employees.json"
checksum_file="MD5SUM"

# Check if the MD5SUM file and the restored files exist
if [ -f "$checksum_file" ] && [ -f "$jokes_file" ] && [ -f "$json_file" ]; then
    echo "Comparing MD5 checksums..."

    # Generate the MD5 checksums for the restored files
    md5 -r "$jokes_file" > MD5CHECK
    md5 -r "$json_file" >> MD5CHECK

    # Compare the original MD5SUM file with the new checksums
    if diff "$checksum_file" MD5CHECK > /dev/null; then
        echo "Checksums match: The files are intact."
    else
        echo "Checksums do not match: The files may have been altered."
    fi

    # Clean up the temporary MD5CHECK file
    rm MD5CHECK
else
    echo "Error: MD5SUM file or one or both of the files do not exist."
fi

