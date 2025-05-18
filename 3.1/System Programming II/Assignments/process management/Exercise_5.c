// NAME: AKECH DAU ATEM  RegNo: SCT211-0535/2022

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Demonstration of exec family functions

int main() {
    // Example of execlp: executing 'ls' with options
    printf("Using execlp to list files with details:\n");
    execlp("ls", "ls", "-l", NULL);
    // If execlp is successful, this comment won't be printed

    // Example of execle: running 'env' command with a custom environment
    printf("Using execle to print environment variables:\n");
    char *envp[] = {"USER=akech", "HOME=/Users/macbook", NULL};  // Custom environment
    execle("/usr/bin/env", "env", NULL, envp);  // Execute 'env' to print environment variables

    // Example of execv: running 'echo' with an array of arguments
    printf("Using execv to print a message:\n");
    char *args[] = {"/bin/echo", "This is an execv example", NULL};  // Arguments array
    execv("/bin/echo", args);  // Running 'echo' with arguments

    // Example of execvp: running 'cat' with a file
    printf("Using execvp to display the content of a file:\n");
    char *args2[] = {"cat", "/etc/hosts", NULL};  // Arguments array
    execvp("cat", args2);  // Searches for 'cat' in PATH

    // Example of exeve: running 'ls' in a specific directory with a custom environment
    printf("Using exeve to list files in the root directory:\n");
    execve("/bin/ls", args, envp);  // Running 'ls' with custom environment

    // This code won't execute if exec calls are successful
    printf("Exec call failed, so this is printed.\n");

    return 0;
}
