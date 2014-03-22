#include <layout.h>

GtkWidget* layout_init(GtkWidget* MainWindow)
{
	GtkWidget* pMainBox = NULL;

	// Création de la fenêtre principale de l'application
	MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(MainWindow), "Éditeur de maps");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 400);

	// Création du conteneur principal
	pMainBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(MainWindow), pMainBox);

	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( menu_new(NULL) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( toolbar_new(NULL) ), FALSE, FALSE, 0);
 
	//Création du bouton Quitter
	GtkWidget* pButton = NULL;
	pButton = gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	gtk_box_pack_start(GTK_BOX(pMainBox), pButton, FALSE, FALSE, 0);
	
	return MainWindow;
}