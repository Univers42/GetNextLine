#include "test_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int compare_output(const char *expected, const char *actual) {
    if (expected == NULL || actual == NULL) {
        return (expected == actual) ? 0 : -1;
    }
    return strcmp(expected, actual);
}

int compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 0;
    }

    char ch1 = getc(f1);
    char ch2 = getc(f2);
    int pos = 0;

    while (ch1 != EOF && ch2 != EOF) {
        if (ch1 != ch2) {
            printf("Difference at position %d: '%c' != '%c'\n", pos, ch1, ch2);
            fclose(f1);
            fclose(f2);
            return 0;
        }
        if (ch1 == '\n' && ch2 == '\r') {
            ch2 = getc(f2);
            if (ch2 != '\n') {
                printf("Difference at position %d: '%c' != '%c'\n", pos, ch1, ch2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
        } else if (ch1 == '\r' && ch2 == '\n') {
            ch1 = getc(f1);
            if (ch1 != '\n') {
                printf("Difference at position %d: '%c' != '%c'\n", pos, ch1, ch2);
                fclose(f1);
                fclose(f2);
                return 0;
            }
        }
        ch1 = getc(f1);
        ch2 = getc(f2);
        pos++;
    }

    if (ch1 != ch2) {
        printf("Files differ in length\n");
    }

    fclose(f1);
    fclose(f2);

    return (ch1 == ch2);
}
