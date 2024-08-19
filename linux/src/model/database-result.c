#include "database-result.h"

struct _DatabaseResult {
    GObject parent_instance;
};

G_DEFINE_TYPE(DatabaseResult, database_result, DATABASE_TYPE_RESULT)

static void database_result_class_init(DatabaseResultClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
}

static void database_result_init(DatabaseResult *self)
{
    
}