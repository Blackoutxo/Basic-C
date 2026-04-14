#include<stdio.h>
#include<stdlib.h>

int main() {
    double a, b, res;
    char c;
    const char *error = NULL;
    
    // Get First number
    printf("Enter first number:\n");
    scanf("%lf", &a);

    // Get Operator
    printf("Enter operator:\n");
    scanf(" %c", &c);

    // Get Second number
    printf("Enter second number:\n");
    scanf("%lf", &b);

    // Operations
    if (c=='x' || c =='*') { 
        res = a * b;
    } else if (c=='%') { 
        res = (int) a % (int) b;
    } else if (c=='+') {
        res = a + b;
    } else if (c=='-') { 
        res = a - b;
    } else if (c=='/') {
        res = a / b;
    } else {
        printf("Null operator");
    }

    // Print the results 
    printf(" %lf %c %lf = %lf", a, c, b, res);

    return 0;
}