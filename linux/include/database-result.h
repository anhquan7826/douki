#pragma once
#include <glib-object.h>

G_BEGIN_DECLS

#define DATABASE_TYPE_RESULT database_result_get_type()

G_DECLARE_FINAL_TYPE(DatabaseResult, database_result, DATABASE, RESULT, GObject)

G_END_DECLS