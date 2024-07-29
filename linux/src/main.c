#include "main-process.h"
#include <glib.h>
#include "dbus-credential.h"

static void handle_set_name(DoukiCredential *self, GVariant *params, gpointer user_data)
{
    gsize *size = malloc(sizeof(gsize));
    const gchar *name = g_variant_get_string(params, size);
    g_print("name: %s\n", name);
    g_free(size);
}

static void on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    g_print("on bus acquired: %s\n", name);
}

static void on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
{
    g_print("name acquired: %s\n", name);

    DoukiCredential *interface = NULL;
    interface = douki_credential_skeleton_new();
    g_signal_connect(interface, "handle-set-name", G_CALLBACK(handle_set_name), NULL);
    GError *error = NULL;
    g_dbus_interface_skeleton_export(
        G_DBUS_INTERFACE_SKELETON(interface),
        connection,
        "/com/douki/Credential",
        &error
    );
    if (error) {
        g_printerr("Error: %s\n", error->message);
        g_free(error);
    }
}

int main(int argc, char **argv)
{
    GMainLoop *loop = NULL;
    loop = g_main_loop_new(NULL, FALSE);
    g_bus_own_name(
        G_BUS_TYPE_SESSION, 
        "com.douki",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        on_bus_acquired,
        on_name_acquired,
        NULL,
        NULL,
        NULL
    );
    g_main_loop_run(loop);
    // run_process();
    return 0;
}
