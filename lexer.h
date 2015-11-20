#ifndef LEXER_H
#define LExER_H

typedef enum token_type
{
    TOKEN_UNDEFINED = 0,
    TOKEN_END,
    TOKEN_SEPARATOR,
    TOKEN_NEWLINE,
    TOKEN_KEY_OR_VALUE,
    TOKEN_SERIAL,
    TOKEN_BOGOMIPS,
    TOKEN_ERROR
} token_type_t;

token_type_t scan(const char* pos, const char** cursor);

#endif /* LEXER_H */
