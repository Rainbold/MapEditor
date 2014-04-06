#include <map_editor.h>

GtkWidget* map_editor_new(char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE])
{
	GtkWidget* pMap = NULL;

	pMap = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pMap), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	return pMap;
}

