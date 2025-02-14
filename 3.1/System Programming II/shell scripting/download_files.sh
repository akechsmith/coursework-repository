#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# URLs to download
txt_url="https://raw.githubusercontent.com/yesinteractive/dadjokes/master/controllers/jokes.txt"
json_url="https://gist.githubusercontent.com/rominirani/8235702/raw/6820f70bd9187f9db51d97e089759fe92d8c1f1d/employees.json"

# Download the TXT file
curl -o jokes.txt "$txt_url"

# Download the JSON file
curl -o employees.json "$json_url"

# Verify if the files were downloaded
if [ -f "jokes.txt" ] && [ -f "employees.json" ]; then
    echo "Files downloaded successfully."
else
    echo "Error: Failed to download one or both files."
fi
