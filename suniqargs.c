#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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
            printf("Prefix lines by number of occurances\n");
            firstOccur = false;
            returnStatus = EXIT_SUCCESS;
            break;
        case 'd':
            ifD = true;
            printf("Only print duplicate lines\n");
            firstOccur = false;
            returnStatus = EXIT_SUCCESS;
            break;
        case 'i':
            ifI = true;
            printf("Ignore case\n");
            firstOccur = false;
            returnStatus = EXIT_SUCCESS;
            break;
        case 'u':
            ifU = true;
            printf("Only print unique lines\n");
            firstOccur = false;
            returnStatus = EXIT_SUCCESS;
            break;
        default:
            printf("Unknown flag: -%c\n", optopt);
            start = false;
            break;
        }
    }
    if (start) {
        if (firstOccur) {
            printf("Matching lines merged to first occurance\n");
        }
        if (argv[optind] && argv[optind+1] == NULL) { /* One filename */
            printf("Processing %s\n", argv[optind]);
        } else if (argv[optind] == NULL) { /* No output for multiple files */
            printf("Processing standard input\n");
        }
        returnStatus = EXIT_SUCCESS;
    }
    return returnStatus;
}
