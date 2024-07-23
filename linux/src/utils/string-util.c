#include "string-util.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

char* str_concat(char* str, ...)
{
    va_list ap;
    va_start(ap, str);
    char *arg;
    int length = 0;
    while ((arg = va_arg(ap, char *)))
    {
        length += strlen(arg);
    }
    char *res = malloc(sizeof(char) * length);
    va_end(ap);
    va_start(ap, str);
    while ((arg = va_arg(ap, char *)))
    {
        strcat(res, arg);
    }
    va_end(ap);
    return res;
}