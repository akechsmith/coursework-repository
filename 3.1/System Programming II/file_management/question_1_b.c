#include <stdio.h>

int main() {
    FILE *fptr;
    int number;

    // Open the file in read mode
    fptr = fopen("Kenya.txt", "r");
    if ( fptr== NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read the integer from the file
    fscanf(fptr, "%d", &number);

    // Close the file
    fclose(fptr);

    // Print the integer to the screen
    printf("The integer read from the file is: %d\n", number);

    return 0;
}
