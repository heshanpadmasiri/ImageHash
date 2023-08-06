#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>

void printHelp(bool isErr) {
    char* prefix = isErr ? "Error: " : "Usage: ";
    char* usage = "imhash --h file_path";
    printf("%s%s\n", prefix, usage);
}

int hashImage(char* file_path) {
    if (access(file_path, F_OK) == -1) {
        printf("Error: file not found\n");
        return 1;
    }
    printf("file_path: %s\n", file_path);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printHelp(true);
        return 1;
    }
    char* file_path = argv[1];
    if (strcmp(file_path, "--h") == 0) {
        printHelp(false);
        return 0;
    }
    return hashImage(file_path);
}
