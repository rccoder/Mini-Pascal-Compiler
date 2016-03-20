#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "./define.h"

int main() {

    FILE *fp;

    if((fp = fopen("./test", "r")) == NULL) {
        printf("\nOpen File Error");
    }

    char ch;
    ch = fgetc(fp);

    char tep;
    while(ch != EOF) {

        // spance TAB LF(换行)
        if(!(ch == 32 || ch == 9|| ch == 10)) {

            // ID
            if(isalpha(ch)) {
                char token[256] = "";
                printf("(ID,");
                printf("%c", ch);
                //strcat(token, ch);

                ch = fgetc(fp);

                while(isalnum(ch)) {
                    printf("%c", ch);
                    //strcat(token, ch);
                    ch = fgetc(fp);
                }
                fseek(fp, -1L, SEEK_CUR);
                printf(")\n");

            } else if(isdigit(ch)) {

                printf("(INT,");

                ch = fgetc(fp);

                while(isdigit(ch)) {

                    printf("%c", ch);

                    ch = fgetc(fp);
                }

                fseek(fp, -1L, SEEK_CUR);
                printf(")\n");

            } else switch(ch) {
                case '*': 
                    tep = ch;
                    ch = fgetc(fp);
                    if(ch == '*') {
                        printf("(EXP,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        printf("(MULTI,%c)\n", tep);
                    }
                    break;
                case ':':
                    tep = ch;
                    ch = fgetc(fp);
                    if(ch == '=') {
                        printf("(ASSIGN,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        printf("(COLON,%c\n", tep);
                    }
                    break;
                case '<':
                    tep = ch;
                    ch = fgetc(fp);
                    if(ch == '=') {
                        printf("(LE,%c%c)\n", tep, ch);
                    } else if(ch == '>') {
                        printf("(NE,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        printf("(LT,%c)\n", tep);
                    }
                    break;
                case '=':
                    printf("(EQ,%c)\n", ch);
                    break;
                case '>':
                    tep = ch;
                    ch = fgetc(fp);
                    if(ch == '=') {
                        printf("(GE,%c%c)\n", tep, ch);
                    } else {
                        fseek(fp, -1L, SEEK_CUR);
                        printf("(GT,%c)\n", tep);
                    }
                    break;
                case '+':
                    printf("(PLUS,%c)\n", ch);
                    break;
                case '-':
                    printf("(MINUS,%c)\n", ch);
                    break;
                case '/':
                    printf("(RDIV,%c)\n", ch);
                    break;
                case ',':
                    printf("(COMMA,%c)\n", ch);
                    break;
                case ';':
                    printf("(SEMIC,%c)\n", ch);
                    break;
                default:
                    break;
            }
            //printf("%c\n", ch);
        } else {

        }

        ch = fgetc(fp);
    }
    fclose(fp);
    return 0;
}