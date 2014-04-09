#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include <functions.h>

#define MAX_SIZE 1000
#define MAX_SIZE_TAB_X 30*30
#define MAX_SIZE_TAB_Y 3

struct data;
struct upSize;

struct data* data_init();

void data_set_main_window(struct data*, GtkWidget*);
GtkWidget* data_get_main_window(struct data*);

void data_set_widget(struct data*, GtkWidget*);

void data_set_spriteslst(struct data* data, char spritesList[][MAX_SIZE]);
char** data_get_spriteslst(struct data* data);

void data_set_sprite(struct data* data, char* sprite);
char* data_get_sprite(char code, char spritesList[][MAX_SIZE]);

void data_set_code(struct data* data, char);
char data_get_code(struct data* data);

void data_set_x(struct data*, int);
void data_set_y(struct data*, int);

void data_set_up_x(struct data*, int);
void data_set_up_y(struct data*, int);

void data_set_save(struct data* data, gboolean save);
gboolean data_get_save(struct data* data);

void data_set_file(struct data*, gboolean);
gboolean data_get_file(struct data*);

void data_set_cell_type(struct data*, char type, int x, int y);
char data_get_cell_type(struct data*, int x, int y);

void data_set_map_sprites(struct data*, char mapSprites[MAX_SIZE_TAB_X]);

void map_editor_new_file(GtkButton* button, gpointer data);
void map_editor_open_file(GtkButton* button, gpointer data);
void map_editor_add_tab(GtkNotebook*, const gchar*, char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE], gpointer data);
void map_editor_replace_sprite(GtkWidget* parent, GdkEventButton* event, gpointer data);

void map_editor_change_size_x(GtkSpinButton* spinButton, gpointer data);
void map_editor_change_size_y(GtkSpinButton* spinButton, gpointer data);
void map_editor_change_size(GtkButton* button, gpointer data);

void spriteslst_change_sprite(GtkTreeView*, gpointer);


#endif