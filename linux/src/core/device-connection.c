#include "device-connection.h"

struct _DeviceConnection {
    GObject parent_instance;
};

typedef struct {
    GSocketConnection *connection;
    OnMessageReceivedCallback on_message_cb;
    void *on_message_cb_data;
    OnConnectionClosedCallback on_connection_closed_cb;
    void *on_connection_closed_cb_data;
    GThread *thread;
    char* thread_name;
} DeviceConnectionPrivate;

G_DEFINE_FINAL_TYPE_WITH_PRIVATE(DeviceConnection, device_connection, G_TYPE_OBJECT)

static void device_connection_class_init(DeviceConnectionClass *klass)
{}

static void device_connection_init(DeviceConnection *self)
{}

static void device_connection_dispose(GObject *object) 
{
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(DEVICE_CONNECTION(object));
    g_clear_object(&(priv->connection));
    g_thread_unref(priv->thread);
    g_free(priv->thread_name);
}

static void *socket_listen(gpointer data)
{
    DeviceConnectionPrivate *priv = (DeviceConnectionPrivate *)data;
    GInputStream *input_stream = g_io_stream_get_input_stream(G_IO_STREAM(priv->connection));
    GDataInputStream *data_stream = g_data_input_stream_new(input_stream);
    GError *error = NULL;
    while (!error)
    {
        gsize length;
        gchar *line = NULL;
        line = g_data_input_stream_read_line_utf8(data_stream, &length, NULL, &error);
        if (error)
        {
            g_printerr("%s", error->message);
        }
        else if (!line)
        {
            break;
        }
        else if (length > 0)
        {
            if (priv->on_message_cb)
            {
                priv->on_message_cb(line, priv->on_message_cb_data);
            }
        }
    }
    if (error) g_error_free(error);
    g_clear_object(&data_stream);
    g_clear_object(&input_stream);
    if (priv->on_connection_closed_cb)
        priv->on_connection_closed_cb(priv->on_connection_closed_cb_data);
    return NULL;
}

DeviceConnection *device_connection_new(GSocketConnection *socket)
{
    DeviceConnection *instance = g_object_new(DEVICE_TYPE_CONNECTION, NULL);
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(instance);
    priv->connection = socket;
    priv->thread_name = g_strdup_printf("device-connection-thread-%p", socket);
    priv->thread = g_thread_new(
        priv->thread_name,
        socket_listen,
        priv
    );
    return instance;
}

gboolean device_connection_is_connected(DeviceConnection *self)
{
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(self);
    return g_socket_connection_is_connected(priv->connection);
}

void device_connection_set_on_message_callback(DeviceConnection *self, OnMessageReceivedCallback cb, void *data)
{
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(self);
    priv->on_message_cb = cb;
    priv->on_message_cb_data = data;
}

void device_connection_set_on_connection_closed_callback(DeviceConnection *self, OnConnectionClosedCallback cb, void *data)
{
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(self);
    priv->on_connection_closed_cb = cb;
    priv->on_connection_closed_cb_data = data;
}