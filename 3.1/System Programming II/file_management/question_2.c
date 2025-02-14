#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void searchAndSaveMp3Files(const char *fileName) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    FILE *outputFile;

    // Open file to write the output
    outputFile = fopen(fileName, "w");
    if (outputFile == NULL) {
        printf("Could not open the file for writing.\n");
        return;
    }

    // Search pattern for .mp3 files in C drive
    hFind = FindFirstFile("C:\\*.mp3", &findFileData);

    // Check if any .mp3 files exist
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No .mp3 files found.\n");
        fclose(outputFile);
        return;
    } else {
        do {
            // Get file name and file size
            const char *fileName = findFileData.cFileName;
            DWORD fileSize = findFileData.nFileSizeLow;

            // Write to the output file
            fprintf(outputFile, "File Name: %s\tSize: %lu bytes\n", fileName, fileSize);
        } while (FindNextFile(hFind, &findFileData) != 0);

        // Close file handle and output file
        FindClose(hFind);
        fclose(outputFile);
        printf("File listing completed and saved to %s.\n", fileName);
    }
}

int main() {
    const char *outputFileName = "akech.txt";
    searchAndSaveMp3Files(outputFileName);
    return 0;
}
