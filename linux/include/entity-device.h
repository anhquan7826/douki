#pragma once
#include <glib-object.h>

G_BEGIN_DECLS

#define ENTITY_TYPE_DEVICE entity_device_get_type()

G_DECLARE_FINAL_TYPE(EntityDevice, entity_device, ENTITY, DEVICE, GObject)

G_END_DECLS