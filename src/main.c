#include <stdio.h>
#include <stdlib.h>
#include <layout.h>
#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
	GtkWidget* MainWindow = NULL;

	// GTK+ Initialization
	gtk_init(&argc, &argv);

	// Initialization of the main window
	MainWindow = layout_init(MainWindow);

	gtk_widget_show_all(MainWindow);
	gtk_main();

	return EXIT_SUCCESS;
}