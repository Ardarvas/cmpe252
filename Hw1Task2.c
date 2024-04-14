#include <stdio.h>
#include <stdlib.h>
#define SIZE 250

float myAtof(char *string, char *errorState);

int main()
{
    char string[SIZE];
    float operand1 = 0.0f, operand2 = 0.0f, result = 0.0f;
    char operator = '\0', errorState = 0;

    printf("Enter arithmetic operation:\n");

    scanf("%s", string);

    int operatorCount = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
            operatorCount++;
        }
    }

    if (operatorCount > 1) {
        printf("Error has been occurred due to inappropriate input!\n");
        return 1;
    }

    if (operatorCount == 1) {
        if (sscanf(string, "%f %c %f", &operand1, &operator, &operand2) != 3) {
            if (string[0] == '+' || string[0] == '-' || string[0] == '*' || string[0] == '/') {
                operand1 = 0.0f;
                operand2 = 0.0f;
                operator = string[0];
            } else {
                printf("Invalid operator type!\n");
                return 1;
            }
        }
    } else {
        printf("Invalid operator type!\n");
        return 1;
    }

    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                printf("Cannot divided into 0.\n");
                return 1;
            }
            break;
        default:
            printf("Invalid operator!\n");
            return 1;
    }

    printf("%.2f %c %.2f = %.2f\n", operand1, operator, operand2, result);

    return 0;
}
