#include <stdio.h>

int main() {
    FILE *fptr;
    int number;

    // Prompt the user for an integer
    printf("Enter an integer: ");
    scanf("%d", &number);

    // Open the file in write mode
    fptr = fopen("Kenya.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Write the integer to the file
    fprintf(fptr, "%d", number);

    // Close the file
    fclose(fptr);
    printf("Integer written to file successfully.\n");

    return 0;
}
