/* File I/O - writes text to a file and reads it back */
#include <stdio.h>

int main(void) {
    FILE *fp;
    char line[100];

    fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }
    fprintf(fp, "Hello from File I/O in C!\n");
    fprintf(fp, "This line was written by the program.\n");
    fclose(fp);

    fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }
    printf("Contents of sample.txt:\n");
    while (fgets(line, sizeof(line), fp) != NULL)
        printf("%s", line);
    fclose(fp);
    return 0;
}
