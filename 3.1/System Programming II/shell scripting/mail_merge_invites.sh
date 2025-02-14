#!/bin/bash
# Name: Akech Dau Atem
# RegNo: SCT211-0535/2022

# Prompt the user for the file containing the names and emails
read -p "Enter the file name containing the names and emails (e.g., students_list.txt): " file_name

# Check if the file exists
if [ ! -f "$file_name" ]; then
    echo "Error: File '$file_name' does not exist."
    exit 1
fi

# Read the file and send invitations
while IFS=',' read -r name email; do
    echo "Sending invitation to $name <$email>..."
    mail -s "Invitation to JhubAfrica Webinar" "$email" <<EOF
Dear $name,

You are invited to our 21st Open Webinar on Skills Optimization by JhubAfrica.  
**Date:** Friday, 29th November  
**Time:** 5:00 P.M.  
**Zoom Link:** https://youtu.be/ONVTA7LKMIs  

We will also broadcast the webinar on our YouTube channel.  
**YouTube Link:** https://youtu.be/ONVTA7LKMIs  

Looking forward to your participation.

Best regards,  
Department of Computing  
EOF
done < "$file_name"

echo "All invitations sent!"
