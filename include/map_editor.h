#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <functions.h>
#include <callback.h>


GtkNotebook* map_editor_new(char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE]);

#endif