#include "device-message.h"

static void json_serializable_interface_init(JsonSerializableIface *iface);

static GParamSpec *device_message_props[N_PROPS_DEVICE_MESSAGE] = {NULL};

struct _DeviceMessage
{
    GObject parent_instance;
    const char *id;
    const char *method;
    const char *type;
    const char *status;
    guint64 timestamp;
    JsonNode *body;
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
        self->body = (JsonNode *)g_value_get_pointer(value);
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
    device_message_props[PROP_DEVICE_MESSAGE_ID] = g_param_spec_string(
        "id",
        "id",
        "Identification",
        "",
        G_PARAM_READWRITE);
    device_message_props[PROP_DEVICE_MESSAGE_METHOD] = g_param_spec_string(
        "method",
        "method",
        "Method",
        "",
        G_PARAM_READWRITE);
    device_message_props[PROP_DEVICE_MESSAGE_TYPE] = g_param_spec_string(
        "type",
        "type",
        "Type",
        "",
        G_PARAM_READWRITE);
    device_message_props[PROP_DEVICE_MESSAGE_STATUS] = g_param_spec_string(
        "status",
        "status",
        "Status",
        "",
        G_PARAM_READWRITE);
    device_message_props[PROP_DEVICE_MESSAGE_TIMESTAMP] = g_param_spec_uint64(
        "timestamp",
        "timestamp",
        "Timestamp",
        0,
        G_MAXUINT64,
        0,
        G_PARAM_READWRITE);
    device_message_props[PROP_DEVICE_MESSAGE_BODY] = g_param_spec_pointer(
        "body",
        "body",
        "Body",
        G_PARAM_READWRITE);
    g_object_class_install_properties(object_class, N_PROPS_DEVICE_MESSAGE, device_message_props);
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
    JsonNode *node = NULL;
    GList *str_props = NULL;
    str_props = g_list_prepend(str_props, "id");
    str_props = g_list_prepend(str_props, "method");
    str_props = g_list_prepend(str_props, "type");
    str_props = g_list_prepend(str_props, "status");

    GList *result_ptrs = g_list_find(str_props, property_name);

    if (g_list_length(result_ptrs))
    {
        node = json_node_new(JSON_NODE_VALUE);
        json_node_set_string(node, g_value_get_string(value));
    }
    else if (g_str_equal(property_name, "timestamp"))
    {
        node = json_node_new(JSON_NODE_VALUE);
        json_node_set_int(node, g_value_get_int64(value));
    }
    else
    {
        node = json_node_new(JSON_NODE_OBJECT);
        json_node_set_parent((JsonNode *)g_value_get_pointer(value), node);
    }
    g_list_free(str_props);
    g_list_free(result_ptrs);
    return node;
}

static gboolean device_message_deserialize_property(
    JsonSerializable *serializable,
    const gchar *property_name,
    GValue *value,
    GParamSpec *pspec,
    JsonNode *property_node)
{
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
        g_value_set_pointer(value, property_node);
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
    *n_pspecs = N_PROPS_DEVICE_MESSAGE;
    return device_message_props;
}

static GParamSpec *device_message_find_property(
    JsonSerializable *serializable,
    const char *name)
{
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
    return json_gobject_to_data(G_OBJECT(self), NULL);
}