#include <layout.h>

GtkWidget* layout_init(GtkWidget* MainWindow)
{
	GtkWidget* pMainBox = NULL;
	GtkWidget* pTable = NULL;

	// Création de la fenêtre principale de l'application
	MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(MainWindow), "Éditeur de maps");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 800, 600);
	gtk_widget_set_size_request(MainWindow, 400, 400);

	// Création du conteneur principal
	pMainBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(MainWindow), pMainBox);

	// Création de la table
	pTable = gtk_table_new(4, 4, TRUE);
		gtk_table_attach( GTK_TABLE(pTable), spriteslist_new(), 0, 1, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
		gtk_table_attach( GTK_TABLE(pTable), map_editor_new(), 1, 4, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);

	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( menu_new(NULL) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( toolbar_new(NULL) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( pTable ), TRUE, TRUE, 0);
	
	return MainWindow;
}