#pragma once
#include <glib-object.h>
#include <sqlite3.h>

G_BEGIN_DECLS

#define DATABASE_TYPE_RESULT database_result_get_type()

G_DECLARE_FINAL_TYPE(DatabaseResult, database_result, DATABASE, RESULT, GObject)

DatabaseResult *database_result_new(sqlite3_stmt *stmt);

int database_result_get_column_count(DatabaseResult *self);

const char** database_result_get_column_list(DatabaseResult *self);

const char* database_result_get_column_name(DatabaseResult *self, int index);

gboolean database_result_next(DatabaseResult *self);

G_END_DECLS