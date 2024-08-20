#include "entity-device.h"

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

static void entity_device_get_property(EntityDevice *self, guint property_id, GValue *value, GParamSpec *pspec)
{

}
