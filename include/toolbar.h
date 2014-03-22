#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <gtk/gtk.h>

GtkToolbar* toolbar_new(gpointer);
static void toolbar_item_new(GtkToolbar*, const gchar*, GCallback, gpointer);

#endif