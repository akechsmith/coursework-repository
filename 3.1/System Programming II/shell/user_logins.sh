#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Prompt user for a UID
read -p "Enter the UID of the user: " uid

# Get the username associated with the UID using the `id` command
username=$(id -un "$uid" 2>/dev/null)

# Check if the username exists
if [ -n "$username" ]; then
    echo "Checking login details for user with UID: $uid ($username)"
    
    # Check how many times the user is logged in
    login_count=$(who | grep -c "^$username")
    
    echo "The user '$username' is currently logged in $login_count time(s)."
    
    # Show login times if user is logged in
    if [ "$login_count" -gt 0 ]; then
        echo "Login time(s):"
        who | grep "^$username" | awk '{print $1, $4}'
    fi
else
    echo "Error: No user found with UID $uid."
fi

