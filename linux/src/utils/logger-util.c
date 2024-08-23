#include "logger-util.h"

void log_print(const gchar *format, ...)
{
    GDateTime *time = g_date_time_new_now_local();
    gchar *timestamp = g_date_time_format(time, "HH:mm dd/mm/yyyy");
    gchar *home = getenv("HOME");
    FILE *fp = fopen("", "a");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    if (fp != NULL)
    {
        fprintf(fp, format, args);
        fclose(fp);
    }
    va_end(args);
    g_object_unref(time);
}