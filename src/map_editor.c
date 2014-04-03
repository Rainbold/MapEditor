#include <map_editor.h>

GtkNotebook* map_editor_new(char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE])
{
	GtkWidget* pNotebookMap = NULL;

	pNotebookMap = gtk_notebook_new();

	return GTK_NOTEBOOK(pNotebookMap);
}

