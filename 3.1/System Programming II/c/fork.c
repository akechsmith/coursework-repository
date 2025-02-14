#include <stdio.h>
#include <unistd.h>

int main() {

    int c = 5;
    pid_t pid = fork();
    
    if (pid == 0) {  // First child process
        c += 5;
    } else {
        pid = fork();  // Second fork (creates a new child)
        c += 10;       // Parent process after second fork
        if (pid == 0) {  // New child process
            c += 10;
        }
    }
    
    fork();  // Third fork
    
    printf("%d\n", c);  // Print the value of c in each process
    return 0;
}
