#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void stripTokenValue(char* buf, const char* start, size_t token_len);

/* Using re2c for lexing the cpuinfo file is a bit of an overkill
 * however, I wanted to learn using it. Here we go! :-)
 */
token_type_t scan(const char* pos, const char** cursor,
        char* buf, size_t buflen)
{
    token_type_t retVal = TOKEN_UNDEFINED;
    size_t used_buflen = buflen - 1;
    const char* old_pos = pos;
    const char* marker;
    const char* limit;

    do
    {
    /*!re2c
     re2c:define:YYCTYPE  = "char";
     re2c:define:YYCURSOR = pos;
     re2c:define:YYMARKER = marker;
     re2c:define:YYLIMIT = limit;
     re2c:yyfill:enable   = 0;

     nul = "\x00";

     'serial'                            { retVal = TOKEN_SERIAL; break; }
     'bogomips'                          { retVal = TOKEN_BOGOMIPS; break; }
     'flags'                             { retVal = TOKEN_FLAGS; break; }
     ":"                                 { retVal = TOKEN_SEPARATOR; break; }
     [\r]?[\n]                           { retVal = TOKEN_NEWLINE; break; }
     "\t"                                { retVal = TOKEN_TAB; break; }
     [^:\t\r\n\x00]+                     { retVal = TOKEN_KEY_OR_VALUE; break; }
     nul                                 { retVal = TOKEN_END; break; }
     [^]                                 { retVal = TOKEN_UNDEFINED; break; }
    */
    } while (0);

    *cursor = pos;

    if (pos - old_pos < used_buflen)
    {
        used_buflen = pos - old_pos;
    }

    if (TOKEN_END != retVal && TOKEN_UNDEFINED != retVal)
    {
        stripTokenValue(buf, old_pos, used_buflen);
    }
    
    return retVal;
}

void read_whole_file(const char* path, char* buf, size_t buflen)
{
    size_t char_read = 0;
    FILE* fh = fopen(path, "r");

    if (NULL == fh)
    {
        return;
    }

    char_read = fread(buf, sizeof(char), buflen - 1, fh);
    buf[char_read] = '\0';
}

void YYDEBUG(int state, char current)
{
        if (-1 == state)
        {
            printf("Current char: %c (0x%02X)\n", current, current);
        }
        else
        {
            printf("State: %d\n", state);
        }
}

static void stripTokenValue(char* buf, const char* start, size_t token_len)
{
    const char const* pos_r = start;
    char* pos_w;

    while(*pos_r == ' ' && token_len > 0)
    {
        token_len--;
        pos_r++;
    }

    strncpy(buf, pos_r, token_len);
    buf[token_len] = '\0';
}
