#include <toolbar.h>

GtkToolbar* toolbar_new(gpointer data)
{
	GtkWidget* pToolbar = NULL;

	pToolbar = gtk_toolbar_new();
	
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_NEW, G_CALLBACK(map_editor_new_file), data);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_OPEN, G_CALLBACK(map_editor_open_file), data);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_SAVE, G_CALLBACK(gtk_main_quit), NULL);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_SAVE_AS, G_CALLBACK(gtk_main_quit), NULL);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_CLOSE, G_CALLBACK(gtk_main_quit), NULL);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_QUIT, G_CALLBACK(gtk_main_quit), NULL);

	return GTK_TOOLBAR(pToolbar);
}

void toolbar_item_new(GtkToolbar* pToolbar, const gchar* stockId, GCallback callback, gpointer userData)
{
	GtkToolItem* pToolItem = NULL;

	pToolItem = gtk_tool_button_new_from_stock(stockId);
	g_signal_connect(G_OBJECT(pToolItem), "clicked", callback, userData);
	gtk_toolbar_insert(pToolbar, pToolItem, -1);
}