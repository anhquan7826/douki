#include "string-util.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char* str_concat(char* str, ...)
{
    va_list ap;
    va_start(ap, str);
    char *arg;
    int length = strlen(str);
    while ((arg = va_arg(ap, char *)))
    {
        length += strlen(arg);
    }
    char *res = malloc(sizeof(char) * length);
    strcat(res, str);
    va_end(ap);
    va_start(ap, str);
    while ((arg = va_arg(ap, char *)))
    {
        strcat(res, arg);
    }
    va_end(ap);
    return res;
}

char* random_lowercase_string(int length) {
    char *str = malloc((length + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        str[i] = 'a' + (rand() % 26);
    }
    str[length] = '\0';

    return str;
}