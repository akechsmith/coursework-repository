#!/bin/bash
# Author: Akech Dau Atem
# Student Number: SCT211-0535/2022

# Function to check if input is a valid number
is_number() {
    [[ "$1" =~ ^[0-9]+$ ]]
}

echo "Enter 6 numbers (one at a time):"
sum=0
count=0

while [ $count -lt 6 ]; do
    read -p "Enter number $((count + 1)): " input
    if is_number "$input"; then
        sum=$((sum + input))
        count=$((count + 1))
    else
        echo "Invalid input! Please enter a number."
    fi
done

echo "The sum of the 6 numbers is: $sum"

