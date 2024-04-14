#include <stdio.h>
#include <stdlib.h>
#define SIZE 250

float myAtof(char *string, char *errorState);

int main()
{
    char string[SIZE];            // Array declaration.
    float fnum1;
    char errorState = 0;

    printf("Enter a number:\n");

     gets(string);
   

     fnum1 = myAtof(string, &errorState);

    if (errorState == 0) {
        printf("Your number is: %.2f\n", fnum1); 
    } else if (errorState == 1) {
        printf("Error has been occurred due to inappropriate input!\n");
    }

    return 0;
}

float myAtof(char* string, char* errorState)
{
    float fnum1 = 0.0f;
    float fraction = 1.0f;
    int noktadansonrasicheck = 0;

    while (*string != '\0') { 
        if (*string >= '0' && *string <= '9') {
            if (!noktadansonrasicheck) {
                fnum1 = fnum1 * 10 + (*string - '0');
            } else {
                fraction /= 10;
                fnum1 = fnum1 + (*string - '0') * fraction;
            }
        } else if (*string == '.') {
            noktadansonrasicheck = 1;
        } else {
            *errorState = 1;
            return 0.0f;
        }
        string++;
    }

    return fnum1;
}
