#include <map_editor.h>

GtkNotebook* map_editor_new(char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE])
{
	GtkNotebook* pNotebookMap = NULL;

	pNotebookMap = gtk_notebook_new();
	
	map_editor_add_tab(pNotebookMap, "map.lvl", spriteList);
	map_editor_add_tab(pNotebookMap, "map2.lvl", spriteList);
	map_editor_add_tab(pNotebookMap, "map.lvl", spriteList);

	return pNotebookMap;
}

