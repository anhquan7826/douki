#include "device-connection.h"
#include <gio.h>

struct _DeviceConnection {
    GObject *parent_object;
};

typedef struct {
    GSocketConnection *connection;
    OnMessageReceivedCallback *cb;
    GThread *thread;
} DeviceConnectionPrivate;

G_DEFINE_FINAL_TYPE_WITH_PRIVATE(DeviceConnection, device_connection, G_TYPE_OBJECT)

static void device_connection_class_init(DeviceConnectionClass *klass)
{}

static void device_connection_init(DeviceConnection *self)
{}

DeviceConnection *device_connection_new(GSocketConnection *socket)
{
    DeviceConnection *instance = g_object_new(DEVICE_TYPE_CONNECTION, NULL);
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(instance);
    priv->connection = socket;

}

gboolean device_connection_is_connected(DeviceConnection *self)
{
    DeviceConnectionPrivate *priv = device_connection_get_instance_private(self);
    return g_socket_connection_is_connected(priv->connection);
}

static void socket_listen(GSocketConnection *connection, OnMessageReceivedCallback cb)
{
    GInputStream *input_stream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GError *error = NULL;
    guint8 *buffer = malloc(4096);
    gssize size = g_input_stream_read(input_stream, buffer, 4096, NULL, &error);
}