#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

#define MAX_KEY_OR_VALUE_LEN 1024

int main(void)
{
    token_type_t token = TOKEN_UNDEFINED;
    const char* to_parse = "asdf  :  qwer\nSerial : test\nBogoMIPS : 1";
    const char* pos = to_parse;
    const char* new_pos;
    char key_or_value[MAX_KEY_OR_VALUE_LEN] = { '\0' };

    do
    {
        token = scan(pos, &new_pos);
        switch(token)
        {
            case TOKEN_END:
                printf("END\n");
                break;
            case TOKEN_SEPARATOR:
                printf("SEPARATOR\n");
                break;
            case TOKEN_NEWLINE:
                printf("NEWLINE\n");
                break;
            case TOKEN_KEY_OR_VALUE:
                strncpy(key_or_value, pos, new_pos - pos);
                key_or_value[new_pos - pos] = '\0';
                printf("KEY_OR_VALUE: '%s'\n", key_or_value);
                break;
            case TOKEN_SERIAL:
                printf("SERIAL\n");
                break;
            case TOKEN_BOGOMIPS:
                printf("BOGOMIPS\n");
                break;
            case TOKEN_ERROR:
                printf("ERROR\n");
                break;
            default:
                break;
        }
        pos = new_pos;
    } while (TOKEN_END != token && TOKEN_ERROR != token);

    return 0;
}
