#pragma once
#include <glib-object.h>
#include <giotypes.h>

G_BEGIN_DECLS

#define DEVICE_TYPE_CONNECTION device_connection_get_type()

typedef void (*OnMessageReceivedCallback)(const char* message);

G_DECLARE_FINAL_TYPE(DeviceConnection, device_connection, DEVICE, CONNECTION, GObject)

DeviceConnection *device_connection_new(GSocketConnection *socket);

void device_connection_set_on_message_callback(DeviceConnection *self, OnMessageReceivedCallback cb);

gboolean device_connection_is_connected(DeviceConnection *self);

G_END_DECLS