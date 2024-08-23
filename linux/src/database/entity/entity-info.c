#include "entity-info.h"
#include "string-util.h"

static const char* table_info = "device_info";

static void entity_info_get_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
static void entity_info_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);

enum
{
    TABLE_INFO_COLUMN_ID,
    TABLE_INFO_COLUMN_NAME,
    TABLE_INFO_COLUMN_PASSWORD
};

enum
{
    ENTITY_INFO_PROP_ID,
    ENTITY_INFO_PROP_NAME,
    ENTITY_INFO_PROP_PASSWORD,
    ENTITY_INFO_N_PROPERTIES
};

static GParamSpec *entity_info_props[ENTITY_INFO_N_PROPERTIES] = { NULL };

struct _EntityInfo
{
    GObject parent_instance;
    int id;
    const gchar* name;
    const gchar* password;
};

G_DEFINE_FINAL_TYPE(EntityInfo, entity_info, ENTITY_TYPE_INFO)

static void entity_info_class_init(EntityInfoClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->get_property = entity_info_get_property;
    object_class->set_property = entity_info_set_property;
    entity_info_props[ENTITY_INFO_PROP_ID] = g_param_spec_int(
        "id",
        "id",
        "Identification",
        G_MININT32,
        G_MAXINT32,
        0,
        G_PARAM_READABLE
    );
    entity_info_props[ENTITY_INFO_PROP_NAME] = g_param_spec_string(
        "name",
        "name",
        "Name",
        "",
        G_PARAM_READWRITE
    );
    entity_info_props[ENTITY_INFO_PROP_PASSWORD] = g_param_spec_string(
        "password",
        "pass",
        "Password",
        "",
        G_PARAM_READWRITE
    );
    g_object_class_install_properties(
        object_class,
        ENTITY_INFO_N_PROPERTIES,
        entity_info_props
    );
}

static void entity_info_init(EntityInfo *self)
{}

static void entity_info_get_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    g_return_if_fail(ENTITY_IS_INFO(object));
    EntityInfo *instance = ENTITY_INFO(object);
    switch (property_id)
    {
        case ENTITY_INFO_PROP_ID:
            g_value_set_int(value, instance->id);
            break;
        case ENTITY_INFO_PROP_NAME:
            g_value_set_string(value, g_strdup(instance->name));
            break;
        case ENTITY_INFO_PROP_PASSWORD:
            g_value_set_string(value, g_strdup(instance->password));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void entity_info_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    g_return_if_fail(ENTITY_IS_INFO(object));
    EntityInfo *instance = ENTITY_INFO(object);
    switch (property_id)
    {
    case ENTITY_INFO_PROP_NAME:
        instance->name = g_strdup(g_value_get_string(value));
        break;
    case ENTITY_INFO_PROP_PASSWORD:
        instance->password = g_strdup(g_value_get_string(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

EntityInfo *entity_info_new(const char* name)
{
    EntityInfo *instance = g_object_new(ENTITY_TYPE_INFO, NULL);
    instance->id = rand();
    instance->name = name;
    instance->password = random_lowercase_string(8);
    return instance;
}

EntityInfo *entity_info_new_from_sqlite3_stmt(sqlite3_stmt *stmt)
{
    EntityInfo *instance = g_object_new(ENTITY_TYPE_INFO, NULL);
    instance->id = sqlite3_column_int(stmt, TABLE_INFO_COLUMN_ID);
    instance->name = g_strdup(sqlite3_column_text(stmt, TABLE_INFO_COLUMN_NAME));
    instance->password = g_strdup(sqlite3_column_text(stmt, TABLE_INFO_COLUMN_PASSWORD));
    return instance;
}

void entity_info_write_to_db(EntityInfo *self, sqlite3 *db, GError **error)
{
    const char* query = g_strdup_printf(
        "INSERT OR REPLACE INTO %s(id, name, password) VALUES (%d, %s, %s)",
        table_info,
        self->id,
        self->name,
        self->password
    );
    char *error_msg = NULL;
    sqlite3_exec(db, query, NULL, NULL, &error_msg);
    if (error_msg != NULL)
    {
        *error = g_error_new_literal(0, -1, error_msg);
    }
    g_free(query);
}