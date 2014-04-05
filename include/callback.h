#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include <functions.h>

#define MAX_SIZE 1000
#define MAX_SIZE_TAB_X 256
#define MAX_SIZE_TAB_Y 3

struct data;

void data_set_widget(struct data*, GtkWidget*);
void data_set_spriteslst(struct data* data, char spritesList[][MAX_SIZE]);
void data_set_sprite(struct data* data, char* sprite);
void data_set_code(struct data* data, char);
void data_set_x(struct data*, int);
void data_set_y(struct data*, int);
char** data_get_spriteslst(struct data* data);
char* data_get_sprite(char code, char spritesList[][MAX_SIZE]);
char data_get_code(struct data* data);
void map_editor_new_file(GtkButton* button, gpointer data);
void map_editor_open_file(GtkButton* button, gpointer data);
void map_editor_add_tab(GtkNotebook*, const gchar*, char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE], gpointer data);
void map_editor_replace_sprite(GtkWidget* parent, GdkEventButton* event, gpointer data);
void spriteslst_change_sprite(GtkTreeView*, gpointer);


#endif