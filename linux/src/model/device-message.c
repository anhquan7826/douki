#include "device-message.h"

static void json_serializable_interface_init(JsonSerializableIface *iface);

struct _DeviceMessage
{
    GObject parent_instance;

    const char *id;
    const char *method;
    const char *type;
    const char *status;
    guint64 timestamp;
    JsonObject *body;
};

G_DEFINE_FINAL_TYPE_WITH_CODE(
    DeviceMessage,
    device_message,
    G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE(
        JSON_TYPE_SERIALIZABLE,
        json_serializable_interface_init))

static void device_message_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
    DeviceMessage *self = DEVICE_MESSAGE(object);
    switch (property_id)
    {
    case PROP_DEVICE_MESSAGE_ID:
        g_value_set_string(value, g_strdup(self->id));
        break;
    case PROP_DEVICE_MESSAGE_METHOD:
        g_value_set_string(value, g_strdup(self->method));
        break;
    case PROP_DEVICE_MESSAGE_TYPE:
        g_value_set_string(value, g_strdup(self->type));
        break;
    case PROP_DEVICE_MESSAGE_STATUS:
        g_value_set_string(value, g_strdup(self->status));
        break;
    case PROP_DEVICE_MESSAGE_TIMESTAMP:
        g_value_set_uint64(value, self->timestamp);
        break;
    case PROP_DEVICE_MESSAGE_BODY:
        g_value_set_pointer(value, self->body);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(self, property_id, pspec);
        break;
    }
}

static void device_message_set_property(GObject *object, guint property_id, const GValue *value, GParamSpec *pspec)
{
    g_print("device_message_set_property: %s\n", pspec->name);
    DeviceMessage *self = DEVICE_MESSAGE(object);
    switch (property_id)
    {
    case PROP_DEVICE_MESSAGE_ID:
        self->id = g_strdup(g_value_get_string(value));
        break;
    case PROP_DEVICE_MESSAGE_METHOD:
        self->method = g_strdup(g_value_get_string(value));
        break;
    case PROP_DEVICE_MESSAGE_TYPE:
        self->type = g_strdup(g_value_get_string(value));
        break;
    case PROP_DEVICE_MESSAGE_STATUS:
        self->status = g_strdup(g_value_get_string(value));
        break;
    case PROP_DEVICE_MESSAGE_TIMESTAMP:
        self->timestamp = g_value_get_uint64(value);
        break;
    case PROP_DEVICE_MESSAGE_BODY:
        self->body = (JsonObject *)g_value_get_pointer(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(self, property_id, pspec);
        break;
    }
}

static void device_message_class_init(DeviceMessageClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->get_property = device_message_get_property;
    object_class->set_property = device_message_set_property;

    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_ID,
        g_param_spec_string(
            "id",
            "id",
            "Identification",
            "",
            G_PARAM_READWRITE));

    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_METHOD,
        g_param_spec_string(
            "method",
            "method",
            "Method",
            "",
            G_PARAM_READWRITE));
    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_TYPE,
        g_param_spec_string(
            "type",
            "type",
            "Type",
            "",
            G_PARAM_READWRITE));
    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_STATUS,
        g_param_spec_string(
            "status",
            "status",
            "Status",
            "",
            G_PARAM_READWRITE));
    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_TIMESTAMP,
        g_param_spec_uint64(
            "timestamp",
            "timestamp",
            "Timestamp",
            0,
            G_MAXUINT64,
            0,
            G_PARAM_READWRITE));
    g_object_class_install_property(
        object_class,
        PROP_DEVICE_MESSAGE_BODY,
        g_param_spec_pointer(
            "body",
            "body",
            "Body",
            G_PARAM_READWRITE));
}

static void device_message_init(DeviceMessage *self)
{
    self->id = NULL;
    self->method = NULL;
    self->type = NULL;
    self->status = NULL;
    self->timestamp = 0;
    self->body = NULL;
}

static JsonNode *device_message_serialize_property(
    JsonSerializable *serializable,
    const gchar *property_name,
    const GValue *value,
    GParamSpec *pspec)
{
    g_print("device_message_serialize_prop: %s\n", property_name);
    JsonNode *node = NULL;

    if (g_str_equal(property_name, "id") ||
        g_str_equal(property_name, "method") ||
        g_str_equal(property_name, "type") ||
        g_str_equal(property_name, "status"))
    {
        node = json_node_new(JSON_NODE_VALUE);
        json_node_set_string(node, g_value_get_string(value));
    }
    else if (g_str_equal(property_name, "timestamp"))
    {
        node = json_node_new(JSON_NODE_VALUE);
        json_node_set_int(node, (gint64) g_value_get_uint64(value));
    }
    else
    {
        node = json_node_new(JSON_NODE_OBJECT);
        json_node_set_object(node, (JsonObject *)g_value_get_pointer(value));
    }
    return node;
}

static gboolean device_message_deserialize_property(
    JsonSerializable *serializable,
    const gchar *property_name,
    GValue *value,
    GParamSpec *pspec,
    JsonNode *property_node)
{
    g_print("device_message_deserialize_property: %s\n", property_name);
    if (
        g_str_equal(property_name, "id") ||
        g_str_equal(property_name, "method") ||
        g_str_equal(property_name, "type") ||
        g_str_equal(property_name, "status"))
    {
        g_value_set_string(value, json_node_get_string(property_node));
    }
    else if (g_str_equal(property_name, "timestamp"))
    {
        g_value_set_uint64(value, (guint64)json_node_get_int(property_node));
    }
    else if (g_str_equal(property_name, "body"))
    {
        JsonObject *object_ptr = (JsonObject *)json_node_get_object(property_node);
        g_value_set_pointer(value, json_object_ref(object_ptr));
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

static void device_message_json_get_property(
    JsonSerializable *serializable,
    GParamSpec *pspec,
    GValue *value)
{
    DeviceMessage *self = DEVICE_MESSAGE(serializable);
    g_object_get_property(G_OBJECT(self), pspec->name, value);
}

static void device_message_json_set_property(
    JsonSerializable *serializable,
    GParamSpec *pspec,
    const GValue *value)
{
    DeviceMessage *self = DEVICE_MESSAGE(serializable);
    g_print("device_message_json_set_property: %s\n", pspec->name);
    g_object_set_property(G_OBJECT(self), pspec->name, value);
}

static GParamSpec **device_message_list_properties(
    JsonSerializable *serializable,
    guint *n_pspecs)
{
    DeviceMessage *self = DEVICE_MESSAGE(serializable);
    return g_object_class_list_properties(
        G_OBJECT_GET_CLASS(self),
        n_pspecs
    );
}

static GParamSpec *device_message_find_property(
    JsonSerializable *serializable,
    const char *name)
{
    g_print("device_message_find_property: %s\n", name);
    return g_object_class_find_property(
        G_OBJECT_GET_CLASS(serializable),
        name);
}

static void json_serializable_interface_init(JsonSerializableIface *iface)
{
    iface->serialize_property = device_message_serialize_property;
    iface->deserialize_property = device_message_deserialize_property;
    iface->get_property = device_message_json_get_property;
    iface->set_property = device_message_json_set_property;
    iface->list_properties = device_message_list_properties;
    iface->find_property = device_message_find_property;
}

DeviceMessage *device_message_from_json(const char *raw_string)
{
    GError *error = NULL;
    GObject *obj = json_gobject_from_data(
        DEVICE_TYPE_MESSAGE,
        raw_string,
        -1,
        &error);
    if (error)
    {
        g_printerr("Cannot parse DeviceMessage from JSON: %s\n", error->message);
        g_error_free(error);
        return NULL;
    }
    return DEVICE_MESSAGE(obj);
}

const char *device_message_to_json(DeviceMessage *self)
{
    gsize length = 0;
    JsonGenerator *gen;
    JsonNode *root;
    gchar *data;

    g_return_val_if_fail(G_OBJECT(self), NULL);

    root = json_gobject_serialize(G_OBJECT(self));
    gen = g_object_new(JSON_TYPE_GENERATOR,
                       "root", root,
                       "pretty", TRUE,
                       "indent", 2,
                       NULL);

    data = json_generator_to_data(gen, &length);
    g_object_unref(gen);

    json_node_unref(root);

    return data;
}