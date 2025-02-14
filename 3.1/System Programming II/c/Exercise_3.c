// NAME: AKECH DAU ATEM  Reg No: SCT211-0535/2022

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Create a child process
    if (pid == 0) {
        // Child process PID is 0
        for (int i = 0; i < 3; i++) {
            printf("Niko Juja\n");   // Print the child process
            sleep(1);  // Let the child process print first by sleeping
        }
    } else {
        // Parent process PID is not 0
        for (int i = 0; i < 3; i++) {
            printf("ICS2305 ni softlife\n");    // Print the parent process
            sleep(1);  // Sleep to allow child process to print first
        }
    }
    return 0;
}
// The output of the code is:   
// ICS2305 ni softlife
// Niko Juja    
// ICS2305 ni softlife
// Niko Juja
// ICS2305 ni softlife
// Niko Juja

// The output is as expected. The parent process prints first followed by the child process.