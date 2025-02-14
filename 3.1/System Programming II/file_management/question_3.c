#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    const char *fileName = "akech.txt";
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Could not open %s for reading.\n", fileName);
        return 1;
    }

    // Define colors for ROYGBIV using Windows color codes
    int colors[] = {4, 6, 14, 2, 1, 5, 13};  // Red, Orange, Yellow, Green, Blue, Indigo, Violet
    int colorCount = sizeof(colors) / sizeof(colors[0]);
    int lineNumber = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int colorIndex = lineNumber % colorCount;
        setColor(colors[colorIndex]);  // Set color for the line
        printf("%s", line);            // Print the line
        lineNumber++;
    }

    // Reset color to default after printing
    setColor(7);
    fclose(file);
    return 0;
}
