#include <env/env_utils.h>
#include <commands/quotes.h>
#include <defines.h>
#include <ctype.h>

int get_key_len(const char *key) 
{
    int len;

    len = 0;
    while (key[len] != '\0' && !isspace(key[len]) && !is_single_quote(key[len]) && !is_double_quote(key[len]) && key[len] != '$')
        ++len;
    return (len);
}
