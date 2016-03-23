#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
    char const * str;
    str = "123ss";
    printf("%d\n", atoi(str));
    return 0;
}