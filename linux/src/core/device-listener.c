#include "device-listener.h"
#include "constants.h"

static void *listen_socket(gpointer data);

typedef struct {
    AvahiSimplePoll *simple_poll;
    AvahiClient *client;
    AvahiEntryGroup *entry_group;
} Mdns;

struct _DeviceListener
{
    GObject parent_instance;
};

typedef struct {
    OnNewConnectionCallback cb;
    GSocketListener *socket_listener;
    GThread *socket_thread;
    Mdns *mdns;
} DeviceListenerPrivate;

G_DEFINE_FINAL_TYPE_WITH_PRIVATE(DeviceListener, device_listener, G_TYPE_OBJECT)

static DeviceListener *_instance = NULL;

static void avahi_state_callback(AvahiClient *client, AvahiClientState state, void *userdata)
{
    Mdns *mdns = (Mdns *)userdata;
    if (state == AVAHI_CLIENT_S_RUNNING)
    {
        mdns->entry_group = avahi_entry_group_new(
            client, 
            NULL,
            NULL
        );
        avahi_entry_group_add_service(
            mdns->entry_group,
            AVAHI_IF_UNSPEC,
            AVAHI_PROTO_UNSPEC,
            AVAHI_PUBLISH_USE_MULTICAST,
            APP_MDNS_NAME,
            APP_MDNS_TYPE,
            APP_MDNS_DOMAIN,
            NULL,
            APP_MDNS_PORT,
            NULL
        );
        avahi_entry_group_commit(mdns->entry_group);
    }
}

static void device_listener_class_init(DeviceListenerClass *klass)
{}

static void device_listener_init(DeviceListener *self)
{
    g_print("Starting device listener...\n");
    int avahi_error = 0;
    DeviceListenerPrivate *priv = device_listener_get_instance_private(self);
    priv->mdns = (Mdns *)malloc(sizeof(Mdns));
    if (priv->mdns)
    {
        priv->mdns->simple_poll = avahi_simple_poll_new();
        priv->mdns->client = avahi_client_new(
            avahi_simple_poll_get(priv->mdns->simple_poll),
            AVAHI_CLIENT_NO_FAIL,
            avahi_state_callback,
            priv->mdns, 
            &avahi_error
        );
    }
    if (avahi_error)
    {
        g_printerr("Cannot start Avahi client!\n");
        exit(EXIT_CODE_AVAHI);
    }
    g_print("Avahi client started!\n");
    priv->socket_listener = g_socket_listener_new();
    GSocketAddress *address = g_inet_socket_address_new(
        g_inet_address_new_any(G_SOCKET_FAMILY_IPV4),
        APP_SOCKET_PORT
    );
    GError *socket_error = NULL;
    g_socket_listener_add_address(
        priv->socket_listener,
        address,
        G_SOCKET_TYPE_STREAM,
        G_SOCKET_PROTOCOL_TCP,
        NULL,
        NULL,
        &socket_error
    );
    if (socket_error)
    {
        g_printerr("Cannot start socket listener!\n");
        g_printerr("%s", socket_error->message);
        exit(EXIT_CODE_SOCKET_SERVER);
    }
    priv->socket_thread = g_thread_new(
        "thread-socket",
        listen_socket,
        priv
    );
    g_print("Socket server started!\n");
    g_print("Device listener started!\n");
}

static void *listen_socket(gpointer data)
{
    DeviceListenerPrivate *priv = (DeviceListenerPrivate *)data;
    while (TRUE)
    {
        GError *error = NULL;
        GSocketConnection *connection = g_socket_listener_accept(
            priv->socket_listener,
            NULL,
            NULL,
            &error
        );
        if (error)
        {
            g_printerr("%s", error->message);
            g_error_free(error);
            continue;
        }
        if (priv->cb)
        {
            DeviceConnection *device_connection = device_connection_new(connection);
            priv->cb(device_connection);
        }
    }
    return NULL;
}

DeviceListener *device_listener_get_instance(void)
{
    if (_instance) return _instance;
    _instance = g_object_new(DEVICE_TYPE_LISTENER, NULL);
    return _instance;
}

void device_listener_join_thread(DeviceListener *self)
{
    DeviceListenerPrivate *priv = device_listener_get_instance_private(self);
    g_thread_join(priv->socket_thread);
}

void device_listener_add_on_new_connection_callback(DeviceListener *self, OnNewConnectionCallback cb)
{
    DeviceListenerPrivate *priv = device_listener_get_instance_private(self);
    priv->cb = cb;
}