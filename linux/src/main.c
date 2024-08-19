#include "main-process.h"
#include <glib.h>
#include "authentication.h"

static gboolean handle_set_name(DoukiCredential *interface, GDBusMethodInvocation *invocation,
					const gchar *name, gpointer user_data)
{
    g_print("handle-set-name invoked\n");
    g_print("%s\n", name);
    douki_credential_complete_set_name(interface, invocation, TRUE);
    return TRUE;
}

static gboolean handle_set_password(DoukiCredential *interface, GDBusMethodInvocation *invocation,
					const gchar *password, const gchar *retype, gpointer user_data) 
{
    g_print("handle-set-password invoked\n");
    g_print("%s\n", password);
    g_print("%s\n", retype);
    gboolean result = strcmp(password, retype) == 0 ? TRUE : FALSE;
    g_print("%d\n", result);
    g_dbus_method_invocation_return_error(invocation, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, "this is error message");
    // douki_credential_complete_set_password(interface, invocation, result);
    return TRUE;
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
    g_signal_connect(interface, "handle-set-password", G_CALLBACK(handle_set_password), NULL);
    GError *error = NULL;
    g_dbus_interface_skeleton_export(
        G_DBUS_INTERFACE_SKELETON(interface),
        connection,
        "/com/anhquan/douki/Credential",
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
        "com.anhquan.douki",
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
