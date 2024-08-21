#pragma once
#include <glib-object.h>
#include <sqlite3.h>

G_BEGIN_DECLS

#define ENTITY_TYPE_DEVICE entity_device_get_type()

G_DECLARE_FINAL_TYPE(EntityDevice, entity_device, ENTITY, DEVICE, GObject)

EntityDevice *entity_device_new_from_sqlite3_stmt(sqlite3_stmt *stmt);

void entity_device_write_to_db(EntityDevice *self, sqlite3 *db, GError **error);

void entity_device_clear(sqlite3 *db, GError **error);

G_END_DECLS