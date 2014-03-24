#ifndef SPRITESLIST_H
#define SPRITESLIST_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char** str_split (char*, const char*);
GtkWidget* spriteslist_new();

#endif