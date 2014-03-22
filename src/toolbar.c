#include <toolbar.h>

GtkToolbar* toolbar_new(gpointer userData)
{
	GtkWidget* pToolbar = NULL;

	pToolbar = gtk_toolbar_new();

	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_NEW, G_CALLBACK(gtk_main_quit), userData);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_OPEN, G_CALLBACK(gtk_main_quit), userData);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_SAVE, G_CALLBACK(gtk_main_quit), userData);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_SAVE_AS, G_CALLBACK(gtk_main_quit), userData);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_CLOSE, G_CALLBACK(gtk_main_quit), userData);
	toolbar_item_new(GTK_TOOLBAR(pToolbar), GTK_STOCK_QUIT, G_CALLBACK(gtk_main_quit), userData);

	return GTK_TOOLBAR(pToolbar);
}

static void toolbar_item_new(GtkToolbar* pToolbar, const gchar* stockId, GCallback callback, gpointer userData)
{
	GtkToolItem* pToolItem = NULL;

	pToolItem = gtk_tool_button_new_from_stock(stockId);
	g_signal_connect(G_OBJECT(pToolItem), "clicked", callback, userData);
	gtk_toolbar_insert(pToolbar, pToolItem, -1);
}