#include <stdio.h>
#include <stdlib.h>
#include <layout.h>
#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
	GtkWidget* MainWindow = NULL;

	// Initialisation de GTK+
	gtk_init(&argc, &argv);

	MainWindow = layout_init(MainWindow);

	gtk_widget_show_all(MainWindow);
	gtk_main();

	return EXIT_SUCCESS;
}