#include <menu.h>

GtkMenuBar* menu_new(gpointer userData)
{
	GtkWidget* pMenuBar = NULL;

	GtkWidget* pMenuFile = NULL;
	GtkWidget* pMenuItemFile = NULL;

	pMenuBar = gtk_menu_bar_new();

	pMenuFile = gtk_menu_new();
	pMenuItemFile = gtk_menu_item_new_with_mnemonic("_File");
		menu_item_new(GTK_MENU(pMenuFile), "_New", G_CALLBACK(map_editor_new_file), userData);
		menu_item_new(GTK_MENU(pMenuFile), "_Open", G_CALLBACK(map_editor_open_file), userData);
		menu_item_new(GTK_MENU(pMenuFile), "_Save", G_CALLBACK(map_editor_save), userData);
		menu_item_new(GTK_MENU(pMenuFile), "Save _As", G_CALLBACK(map_editor_save_as), userData);
		menu_item_new(GTK_MENU(pMenuFile), "_Close", G_CALLBACK(map_editor_close), userData);
		menu_item_new(GTK_MENU(pMenuFile), "_Quit", G_CALLBACK(map_editor_quit), userData);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItemFile), pMenuFile);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItemFile);

	pMenuFile = gtk_menu_new();
	pMenuItemFile = gtk_menu_item_new_with_mnemonic("_?");
		menu_item_new(GTK_MENU(pMenuFile), "_Help", G_CALLBACK(NULL), userData);
		menu_item_new(GTK_MENU(pMenuFile), "_About", G_CALLBACK(NULL), userData);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItemFile), pMenuFile);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItemFile);

	return GTK_MENU_BAR(pMenuBar);
}

void menu_item_new(GtkMenu* pMenu, const gchar* title, GCallback callback, gpointer userData)
{
	GtkWidget* pMenuItem = NULL;

	pMenuItem = gtk_menu_item_new_with_mnemonic(title);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	g_signal_connect(G_OBJECT(pMenuItem), "activate", callback, userData);
}