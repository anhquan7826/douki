#include "process.h"
#include "device-message.h"

// static gboolean handle_set_name(DoukiCredential *interface, GDBusMethodInvocation *invocation,
// 					const gchar *name, gpointer user_data)
// {
//     g_print("handle-set-name invoked\n");
//     g_print("%s\n", name);
//     douki_credential_complete_set_name(interface, invocation, TRUE);
//     return TRUE;
// }

// static gboolean handle_set_password(DoukiCredential *interface, GDBusMethodInvocation *invocation,
// 					const gchar *password, const gchar *retype, gpointer user_data)
// {
//     g_print("handle-set-password invoked\n");
//     g_print("%s\n", password);
//     g_print("%s\n", retype);
//     gboolean result = strcmp(password, retype) == 0 ? TRUE : FALSE;
//     g_print("%d\n", result);
//     g_dbus_method_invocation_return_error(invocation, G_DBUS_ERROR, G_DBUS_ERROR_FAILED, "this is error message");
//     // douki_credential_complete_set_password(interface, invocation, result);
//     return TRUE;
// }

// static void on_bus_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
// {
//     g_print("on bus acquired: %s\n", name);
// }

// static void on_name_acquired(GDBusConnection *connection, const gchar *name, gpointer user_data)
// {
//     g_print("name acquired: %s\n", name);

//     DoukiCredential *interface = NULL;
//     interface = douki_credential_skeleton_new();
//     g_signal_connect(interface, "handle-set-name", G_CALLBACK(handle_set_name), NULL);
//     g_signal_connect(interface, "handle-set-password", G_CALLBACK(handle_set_password), NULL);
//     GError *error = NULL;
//     g_dbus_interface_skeleton_export(
//         G_DBUS_INTERFACE_SKELETON(interface),
//         connection,
//         "/com/anhquan/douki/Credential",
//         &error
//     );
//     if (error) {
//         g_printerr("Error: %s\n", error->message);
//         g_free(error);
//     }
// }

int main(int argc, char **argv)
{
    // GMainLoop *loop = NULL;
    // loop = g_main_loop_new(NULL, FALSE);
    // g_bus_own_name(
    //     G_BUS_TYPE_SESSION,
    //     "com.anhquan.douki",
    //     G_BUS_NAME_OWNER_FLAGS_NONE,
    //     on_bus_acquired,
    //     on_name_acquired,
    //     NULL,
    //     NULL,
    //     NULL
    // );
    // g_main_loop_run(loop);
    // run_process();
    const char *json =
        "{"
        "\"id\": \"abcdef\","
        "\"method\": \"sample_method\","
        "\"type\": \"signal\","
        "\"status\": \"success\","
        "\"timestamp\": 1000000000,"
        "\"body\": null"
        "}";
    g_print("%s\n", json);
    // DeviceMessage *instance = g_object_new(
    //     DEVICE_TYPE_MESSAGE,
    //     "id",
    //     "abcdef", NULL);
    DeviceMessage *instance = device_message_from_json(json);
    if (instance == NULL)
    {
        g_print("instance is null\n");
        return 1;
    }
    guint n_props = 0;
    GParamSpec **pspecs = json_serializable_list_properties(JSON_SERIALIZABLE(instance), &n_props);
    for (int i = 1; i < n_props; i++)
    {
        GParamSpec *pspec = pspecs[i];
        g_print("prop name: %s\n", pspec->name);
    }
    GValue body = G_VALUE_INIT;
    g_value_init(&body, G_TYPE_POINTER);
    g_object_get_property(G_OBJECT(instance), "body", &body);
    g_print("id: %p\n", g_value_get_pointer(&body));
    // const char *to_json = device_message_to_json(instance);
    // g_print("to json: %s\n", to_json);
    return 0;
}
