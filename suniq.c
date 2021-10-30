#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/* print appropriate information on standard output */
void printLine(char line[], int count, bool ifC, bool ifD, bool ifU) {
    if (ifD && !ifU) { /* -d */
        if (count > 1) {
            if (ifC) {
                printf("%7i %s", count, line);
            } else {
                printf("%s", line);
            }
        }
    } else if (!ifD && ifU) { /* -u */
        if (count == 1) {
            if (ifC) {
                printf("%7i %s", count, line);
            } else {
                printf("%s", line);
            }
        }
    } else if (ifC) { /* -c */
        printf("%7i %s", count, line);
    } else if (!ifC && !ifD && !ifU) {
        printf("%s", line);
    }
}

/* read lines from `fd’, performing uniq processing given ifC, ifD, ifI, ifU */
void uniqFile(FILE *fd, bool ifC, bool ifD, bool ifI, bool ifU) {
    char last[BUFSIZ];
    char current[BUFSIZ];
    int lcount = 1;
    fgets(last, sizeof last, fd); /* read first line */
    while (fgets(current, sizeof current, fd) != NULL) {
        if (ifI) {
            if (strcasecmp(last, current) != 0) {
                printLine(last, lcount, ifC, ifD, ifU);
                strcpy(last, current);
                lcount = 1;
            } else {
                lcount++;
            }
        } else {
            if (strcmp(last, current) != 0) {
                printLine(last, lcount, ifC, ifD, ifU);
                strcpy(last, current);
                lcount = 1;
            } else {
                lcount++;
            }
        }
    }
    printLine(last, lcount, ifC, ifD, ifU);
}

int main(int argc, char *argv[]) {
    int option;
    bool ifC, ifD, ifI, ifU;
    int returnStatus = EXIT_FAILURE;
    bool firstOccur = true;
    bool start = true;
    while ((option = getopt(argc, argv, "cdiu")) != -1) {
        switch (option) {
        case 'c':
            ifC = true;
            firstOccur = false;
            break;
        case 'd':
            ifD = true;
            firstOccur = false;
            break;
        case 'i':
            ifI = true;
            firstOccur = false;
            break;
        case 'u':
            ifU = true;
            firstOccur = false;
            break;
        default:
            printf("Unknown flag: -%c\n", optopt);
            start = false;
            break;
        }
    }
    if (start) {
        if (argv[optind]) {
            FILE *fd = fopen(argv[optind], "r");
            if (fd == NULL) {
                printf("Error, no file found: %s\n", argv[optind]);
            } else {
                uniqFile(fd, ifC, ifD, ifI, ifU);
                fclose(fd);
                returnStatus = EXIT_SUCCESS;
            }
        } else {
            uniqFile(stdin, ifC, ifD, ifI, ifU);
            returnStatus = EXIT_SUCCESS;
        }
        return returnStatus;
    }
}