#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <functions.h>

#define MAX_SIZE 1000
#define TAB_SIZE 256

static void map_editor_add_tab(GtkWidget*, const gchar*, char spriteList[TAB_SIZE][3][MAX_SIZE]);
GtkWidget* map_editor_new();

#endif