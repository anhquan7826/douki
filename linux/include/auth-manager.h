#pragma once

#include <glib.h>

const gchar *auth_manager_get_connected_id();

void auth_manager_set_connected_id(const gchar *id);

void auth_manager_clear_connected_id();