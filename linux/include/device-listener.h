#pragma once
#include "device-connection.h"
#include <avahi-client/client.h>
#include <avahi-common/simple-watch.h>
#include <avahi-client/publish.h>

G_BEGIN_DECLS

#define DEVICE_TYPE_LISTENER device_listener_get_type()

typedef void (*OnNewConnectionCallback)(DeviceConnection *connection);

G_DECLARE_FINAL_TYPE(DeviceListener, device_listener, DEVICE, LISTENER, GObject)

DeviceListener *device_listener_get_instance(void);

void device_listener_add_on_new_connection_callback(DeviceListener *self, OnNewConnectionCallback cb);

void device_listener_join_thread(DeviceListener *self);

G_END_DECLS