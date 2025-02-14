// NAME: AKECH DAU ATEM    Reg No: SCT211-0535/2022

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <dirent.h>
#include <stdlib.h>

// Check if string is numeric (valid PID)
int is_numeric(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        str++;
    }
    return 1;
}

int main() {
    // Open /proc directory   NB: Linux specific code
    DIR *proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Error opening /proc");
        return 1;
    }

    struct dirent *entry;
    
    // Loop through /proc entries
    while ((entry = readdir(proc_dir)) != NULL) {
        if (is_numeric(entry->d_name)) {  // Process only numeric (PID) entries
            pid_t pid = atoi(entry->d_name);  // Convert to PID
            pid_t ppid = getppid();  // Get parent PID
            int priority = getpriority(PRIO_PROCESS, pid);  // Get priority

            // Print process info
            printf("Process ID: %d\n", pid);
            printf("Parent ID: %d\n", ppid);
            printf("Priority: %d\n\n", priority);
        }
    }

    closedir(proc_dir);  // Close directory
    return 0;
}
