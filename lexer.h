#ifndef LEXER_H
#define LExER_H

#include <stddef.h>

typedef enum token_type
{
    TOKEN_UNDEFINED = 0,
    TOKEN_END,
    TOKEN_SEPARATOR,
    TOKEN_NEWLINE,
    TOKEN_TAB,
    TOKEN_KEY_OR_VALUE,
    TOKEN_SERIAL,
    TOKEN_BOGOMIPS,
    TOKEN_FLAGS,
    TOKEN_ERROR
} token_type_t;

token_type_t scan(const char* pos, const char** cursor,
        char* buf, size_t buflen);
void read_whole_file(const char* path, char* buf, size_t buflen);

#endif /* LEXER_H */
