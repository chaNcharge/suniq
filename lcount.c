#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
    char last[BUFSIZ];
    char current[BUFSIZ];
    int lcount = 1;
    int exitStatus = EXIT_SUCCESS;
    fgets(last, sizeof last, stdin); /* read first line */
    while (fgets(current, sizeof current, stdin) != NULL) {
        if (strcmp(last, current) != 0) {
            printf("%7i %s", lcount, last);
            strcpy(last, current);
            lcount = 1;
        } else {
            lcount++;
        }
    }
    printf("%7i %s\n", lcount, last);
    return exitStatus;
}
