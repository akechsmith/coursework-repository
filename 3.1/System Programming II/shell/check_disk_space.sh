#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Check available disk space on the root directory
disk_space=$(df -m / | awk 'NR==2 {print $4}')

# Display an alert with the available space in MB
echo "The space available on the drive is ${disk_space}MB."

