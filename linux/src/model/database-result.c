#include "database-result.h"

struct _DatabaseResult {
    GObject parent_instance;
};

typedef struct {
    sqlite3_stmt *stmt;
} DatabaseResultPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(DatabaseResult, database_result, DATABASE_TYPE_RESULT)

static void database_result_class_init(DatabaseResultClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
}

static void database_result_init(DatabaseResult *self)
{
    DatabaseResultPrivate *priv = database_result_get_instance_private(self);
}

static void database_result_dispose(GObject *object)
{
    DatabaseResultPrivate *priv = database_result_get_instance_private(object);
    sqlite3_finalize(priv->stmt);
    G_OBJECT_CLASS(database_result_parent_class)->dispose(object);
}

static DatabaseResultPrivate *_get_private(DatabaseResult *instance)
{
    return database_result_get_instance_private(instance);
}

DatabaseResult *database_result_new(sqlite3_stmt *stmt)
{
    DatabaseResult *instance;
    instance = g_object_new(DATABASE_TYPE_RESULT, NULL);
    DatabaseResultPrivate *priv = database_result_get_instance_private(instance);
    priv->stmt = stmt;
    return instance;
}

int database_result_get_column_count(DatabaseResult *self)
{
    DatabaseResultPrivate *priv = _get_private(self);
    return sqlite3_column_count(priv->stmt);
}

const char** database_result_get_column_list(DatabaseResult *self)
{
    DatabaseResultPrivate *priv = _get_private(self);
    int count = database_result_get_column_count(self);
    const char **names = (const char **)malloc(sizeof(const char *) * count);
    for (int i = 0; i < count; i++)
    {
        names[i] = g_strdup(sqlite3_column_name(priv->stmt, i));
    }
    return names;
}

const char* database_result_get_column_name(DatabaseResult *self, int index)
{
    DatabaseResultPrivate *priv = _get_private(self);
    return g_strdup(sqlite3_column_name(priv->stmt, index));
}

gboolean database_result_next(DatabaseResult *self)
{
    DatabaseResultPrivate *priv = _get_private(self);
    sqlite3_step(priv->stmt);
}
