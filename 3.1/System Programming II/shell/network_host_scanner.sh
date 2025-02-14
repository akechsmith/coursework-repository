#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Prompt the user to enter the IP address or network range
read -p "Enter the IP address or network range to scan (e.g., 192.168.1.0/24): " ip_range

# Check if the input is not empty
if [ -z "$ip_range" ]; then
    echo "Error: No IP address or network range entered."
    exit 1
fi

# Notify the user that scanning has started
echo "Scanning the network for active hosts on $ip_range..."

# Use nmap to scan for active hosts
nmap -sn $ip_range | while read -r line; do
    # Check for lines indicating a host is up
    if [[ $line == *"Nmap scan report for"* ]]; then
        host=$(echo $line | awk '{print $5}')
        echo "Host: $host - Status: Yes (Up)"
    fi
done

