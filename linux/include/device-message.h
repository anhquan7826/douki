#pragma once
#include <glib-object.h>
#include <json-glib/json-glib.h>

G_BEGIN_DECLS

#define DEVICE_TYPE_MESSAGE device_message_get_type()

enum {
    PROP_DEVICE_MESSAGE_ID = 1,
    PROP_DEVICE_MESSAGE_METHOD,
    PROP_DEVICE_MESSAGE_TYPE,
    PROP_DEVICE_MESSAGE_STATUS,
    PROP_DEVICE_MESSAGE_TIMESTAMP,
    PROP_DEVICE_MESSAGE_BODY,
    N_PROPS_DEVICE_MESSAGE
};

typedef enum {
    REQUEST,
    RESPONSE,
    SIGNAL
} MessageType;

typedef enum {
    NONE,
    SUCCESS,
    ERROR
} MessageStatus;

G_DECLARE_FINAL_TYPE(DeviceMessage, device_message, DEVICE, MESSAGE, GObject)

struct _DeviceMessageClass {
    GObjectClass parent_class;
    DeviceMessage (*device_message_from_json) (char *raw_string);
};

DeviceMessage *device_message_from_json(const char *raw_string);

const char *device_message_to_json(DeviceMessage *self);

G_END_DECLS