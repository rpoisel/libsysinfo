#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "system_info.h"

#define INIT_N_A_STR "N/A"
#define MAX_SUPPORTED_FILE_LEN 8192 /* support case that file is bigger than that! */
#define MAX_KEY_OR_VALUE_LEN 1024

#define PATH_CPUINFO "/tmp/cpuinfo"

static void initialize_cpuinfo(struct cpuinfo* info);

void parse_cpu_info(struct cpuinfo* info)
{
    token_type_t token = TOKEN_UNDEFINED;
    token_type_t last_field = TOKEN_UNDEFINED;
    const char* new_pos;
    char token_value[MAX_KEY_OR_VALUE_LEN] = { '\0' };
    char file_contents[MAX_SUPPORTED_FILE_LEN] = { '\0' };
    const char* pos = file_contents;

    initialize_cpuinfo(info);

    read_whole_file(PATH_CPUINFO, file_contents, sizeof(file_contents));

    do
    {
        token = scan(pos, &new_pos, token_value, sizeof(token_value));
        switch (token)
        {
            case TOKEN_SERIAL:
                last_field = token;
                break;
            case TOKEN_BOGOMIPS:
                last_field = token;
                break;
            case TOKEN_FLAGS:
                last_field = token;
                break;
            case TOKEN_KEY_OR_VALUE:
                switch (last_field)
                {
                    case TOKEN_SERIAL:
                        strncpy(info->serial, token_value, MAX_VALUE_LEN);
                        break;
                    case TOKEN_BOGOMIPS:
                        strncpy(info->bogomips, token_value, MAX_VALUE_LEN);
                        break;
                    case TOKEN_FLAGS:
                        strncpy(info->flags, token_value, MAX_FLAGS_LEN);
                    default:
                        /* ignore other fields and values */
                        break;
                }
                last_field = TOKEN_UNDEFINED;
                break;
            case TOKEN_ERROR:
            case TOKEN_END:
            case TOKEN_SEPARATOR:
            case TOKEN_NEWLINE:
            case TOKEN_TAB:
            case TOKEN_UNDEFINED:
            default:
                break;
        }
        pos = new_pos;
    } while (TOKEN_END != token && TOKEN_ERROR != token);
}

static void initialize_cpuinfo(struct cpuinfo* info)
{
    strncpy(info->serial, INIT_N_A_STR, MAX_VALUE_LEN);
    strncpy(info->bogomips, INIT_N_A_STR, MAX_VALUE_LEN);
    strncpy(info->flags, INIT_N_A_STR, MAX_FLAGS_LEN);
}

