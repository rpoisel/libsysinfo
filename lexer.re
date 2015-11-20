#include "lexer.h"
#include <stdlib.h>
#include <stdio.h>

token_type_t scan(const char* pos, const char** cursor)
{
    token_type_t retVal = TOKEN_UNDEFINED;
    const char* marker;

    if (NULL == cursor)
    {
        return TOKEN_ERROR;
    }

    /*!re2c
     re2c:define:YYCTYPE  = "char";
     re2c:define:YYCURSOR = pos;
     re2c:define:YYMARKER = marker;
     re2c:yyfill:enable   = 0;

     '\000'                            { *cursor = pos; return TOKEN_END; }
     [ ]*":"[ ]*                       { *cursor = pos; return TOKEN_SEPARATOR; }
     [\n]                              { *cursor = pos; return TOKEN_NEWLINE; }
     "Serial"                          { *cursor = pos; return TOKEN_SERIAL; }
     'bogomips'                        { *cursor = pos; return TOKEN_BOGOMIPS; }
     [a-zA-Z0-9]+([ ][a-zA-Z0-9]+)*    { *cursor = pos; return TOKEN_KEY_OR_VALUE; }
     [^]                               { *cursor = pos; return TOKEN_ERROR; }
    */

    return TOKEN_UNDEFINED;
}
