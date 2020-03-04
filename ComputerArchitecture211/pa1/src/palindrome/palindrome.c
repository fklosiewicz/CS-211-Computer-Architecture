/* CS 211 PA1: palindrome
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{

    int length = strlen(argv[1]);
    int starting = 0;

    int conclusion = 1;

    // Don't want to deal with upper/lower cases, I'll just convert it all to lower case for the sake of simplicity.

    int lowercaser;

    for(lowercaser = 0; lowercaser < length; lowercaser++) {
        argv[1][lowercaser] = tolower(argv[1][lowercaser]);
    }

    while(length > starting) {
        if(!isalpha(argv[1][starting])) {
            starting++;
            continue;
        }
        if(!isalpha(argv[1][length])) {
            length--;
            continue;
        }

        if (argv[1][starting] == argv[1][length]) {
            length--;
            starting++;
            continue;
        }
        else {
            conclusion = 0;
            break;
        }
    }

    if(conclusion == 1) {
        printf("yes");
    }
    else {
        printf("no");
    }

    return EXIT_SUCCESS;
}
