#include "process.h"

static void on_new_connection(DeviceConnection *connection);
static void on_new_message(char *message, void *data);
static void on_connection_closed(void *data);

void run_process()
{
    DeviceListener *listener = device_listener_get_instance();
    device_listener_add_on_new_connection_callback(listener, on_new_connection);
    device_listener_join_thread(listener);
}

static void on_new_connection(DeviceConnection *connection)
{
    g_print("New connection!\n");
    device_connection_set_on_message_callback(connection, on_new_message, NULL);
    device_connection_set_on_connection_closed_callback(connection, on_connection_closed, connection);
}

static void on_new_message(char *message, void *data)
{
    g_print("Message: %s\n", message);
}

static void on_connection_closed(void *data)
{
    DeviceConnection *connection = (DeviceConnection *)data;
    g_print("Connection closed!\n");
    g_object_unref(connection);
}