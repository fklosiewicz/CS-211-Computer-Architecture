/* CS 211 PA1: roman
 * Created for: fk206
 */

#include <stdio.h>
#include <stdlib.h>


void NumberToRoman(int number) {
    int D = number;

    int numbers[] = {1,4,5,9,10,40,50,90,100,400,500,900,1000};
    char symbols[] = {'I','V','X','L','C','D','M'};

    while (D > 0) {
        if(D >= numbers[12]) {
            printf("%c",symbols[6]);
            D = D - numbers[12];
        }

        else if(D >= numbers[11]) {
            printf("CM");
            D = D - numbers[11];
        }

        else if(D >= numbers[10]) {
            printf("%c",symbols[5]);
            D = D - numbers[10];
        }

        else if(D >= numbers[9]) {
            printf("CD");
            D = D - numbers[9];
        }

        else if(D >= numbers[8]) {
            printf("%c",symbols[4]);
            D = D - numbers[8];
        }

        else if(D >= numbers[7]) {
            printf("XC");
            D = D - numbers[7];
        }

        else if(D >= numbers[6]) {
            printf("%c",symbols[3]);
            D = D - numbers[6];
        }

        else if(D >= numbers[5]) {
            printf("XL");
            D = D - numbers[5];
        }

        else if(D >= numbers[4]) {
            printf("%c",symbols[2]);
            D = D - numbers[4];
        }

        else if(D >= numbers[3]) {
            printf("IX");
            D = D - numbers[3];
        }

        else if(D >= numbers[2]) {
            printf("%c",symbols[1]);
            D = D - numbers[2];
        }

        else if(D >= numbers[1]) {
            printf("IV");
            D = D - numbers[1];
        }

        else if(D >= numbers[0]) {
            printf("%c",symbols[0]);
            D = D - numbers[0];
        }

    }

    return;
}




int main(int argc, char **argv)
{
    int value = atoi(argv[1]);

    NumberToRoman(value);

    return EXIT_SUCCESS;
}
