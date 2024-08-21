#include "entity-device.h"

static const char* table_device = "connected_device";

enum
{
    TABLE_DEVICE_COLUMN_ID,
    TABLE_DEVICE_COLUMN_NAME
};

enum {
    ENTITY_DEVICE_PROP_ID,
    ENTITY_DEVICE_PROP_NAME,
    ENTITY_DEVICE_N_PROPERTIES
};

static GParamSpec *entity_device_props[ENTITY_DEVICE_N_PROPERTIES] = { NULL };

struct _EntityDevice {
    GObject *parent_instance;
    int id;
    const char* name;
};

G_DEFINE_FINAL_TYPE(EntityDevice, entity_device, ENTITY_TYPE_DEVICE)

static void entity_device_class_init(EntityDeviceClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->get_property = entity_device_get_property;
    object_class->set_property = entity_device_set_property;
    entity_device_props[ENTITY_DEVICE_PROP_ID] = g_param_spec_int(
        "id",
        "id",
        "Identification",
        G_MININT32,
        G_MAXINT32,
        0,
        G_PARAM_READABLE
    );
    entity_device_props[ENTITY_DEVICE_PROP_NAME] = g_param_spec_string(
        "name",
        "name",
        "Name",
        "",
        G_PARAM_READWRITE
    );
    g_object_class_install_properties(object_class, ENTITY_DEVICE_N_PROPERTIES, entity_device_props);
}

static void entity_device_init(EntityDevice *self)
{
    
}

static void entity_device_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    g_return_if_fail(ENTITY_IS_DEVICE(object));
    EntityDevice *instance = ENTITY_DEVICE(object);
    switch (property_id)
    {
        case ENTITY_DEVICE_PROP_ID:
            g_value_set_int(value, instance->id);
            break;
        case ENTITY_DEVICE_PROP_NAME:
            g_value_set_string(value, instance->name);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

static void entity_device_set_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    g_return_if_fail(ENTITY_IS_DEVICE(object));
    EntityDevice *instance = ENTITY_DEVICE(object);
    switch (property_id)
    {
        case ENTITY_DEVICE_PROP_NAME:
            instance->name = g_value_get_string(value);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
    }
}

EntityDevice *entity_device_new_from_sqlite3_stmt(sqlite3_stmt *stmt)
{
    EntityDevice *instance = g_object_new(ENTITY_TYPE_DEVICE, NULL);
    instance->id = sqlite3_column_int(stmt, 0);
    instance->name = g_strdup(sqlite3_column_text(stmt, 1));
    return instance;
}

void entity_device_write_to_db(EntityDevice *self, sqlite3 *db, GError **error)
{
    entity_device_clear(db, error);
    if (*error != NULL) return;
    char *error_msg = NULL;
    char *query = g_strdup_printf(
        "INSERT INTO %s (id, name) VALUES (%d, %s)",
        table_device,
        self->id,
        self->name
    );
    sqlite3_exec(db, query, NULL, NULL, &error_msg);
    if (error_msg != NULL)
    {
        *error = g_error_new_literal(0, -1, error_msg);
        return;
    }
    g_free(query);
}

void entity_device_clear(sqlite3 *db, GError **error)
{
    char *error_msg = NULL;
    gchar* query = g_strdup_printf(
        "DELETE FROM %s WHERE TRUE",
        table_device
    );
    sqlite3_exec(db, query, NULL, NULL, &error_msg);
    if (error_msg != NULL)
    {
        *error = g_error_new_literal(0, -1, error_msg);
        return;
    }
    g_free(query);
}
