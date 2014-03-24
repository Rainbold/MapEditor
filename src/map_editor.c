#include <map_editor.h>

GtkWidget* map_editor_new()
{
	GtkWidget* pNotebookMap = NULL;

	pNotebookMap = gtk_notebook_new();

	
	map_editor_add_tab(pNotebookMap, "Map_1.lvl");

	return pNotebookMap;
}

static void map_editor_add_tab(GtkWidget* pNotebookMap, const gchar* f)
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pScrollbar = NULL;

	pTabLabel = gtk_label_new(f);
		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(12, 12, TRUE);
		for(int i=0; i<12; i++)
		{
			for(int j=0; j<12; j++)
			{
				pImage = gtk_image_new_from_file("./images/closed_door.png");
				gtk_table_attach( GTK_TABLE(pTable), pImage, i, i+1, j, j+1, FALSE, FALSE, 1, 1);
			}
		}
		gtk_container_add(GTK_CONTAINER(pAlignment), pTable);

	// Ajout de la scrollbar
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(pScrollbar), pAlignment);

	gtk_notebook_append_page(pNotebookMap, pScrollbar, pTabLabel);
}