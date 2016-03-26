#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * argv[])
{
    char * tokenData = "3.16";
    printf("%.2f\n", atof(tokenData));
    return 0;
}