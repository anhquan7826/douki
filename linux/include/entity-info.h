#pragma once

#include <glib-object.h>
#include <sqlite3.h>

G_BEGIN_DECLS

#define ENTITY_TYPE_INFO entity_info_get_type()

G_DECLARE_FINAL_TYPE(EntityInfo, entity_info, ENTITY, INFO, GObject)

EntityInfo *entity_info_new(const char* name);

EntityInfo *entity_info_new_from_sqlite3_stmt(sqlite3_stmt *stmt);

void entity_info_write_to_db(EntityInfo *self, sqlite3 *db, GError **error);

G_END_DECLS