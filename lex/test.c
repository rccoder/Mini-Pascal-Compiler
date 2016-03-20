#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
   char str[] = "ss";
   strcat(str, "333");
   strcat(str, 's');
   printf("%s\n", str);
  return 0;
}