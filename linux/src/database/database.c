#include "database.h"
#include <glib.h>

#define APP_DB "douki.db"

sqlite3 *get_database_instance()
{
    static sqlite3 *instance = NULL;
    if (instance != NULL) return instance;
    sqlite3_open(APP_DB, &instance);
    return instance;
}

