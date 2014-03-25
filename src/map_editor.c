#include <map_editor.h>

GtkWidget* map_editor_new()
{
	GtkWidget* pNotebookMap = NULL;

	pNotebookMap = gtk_notebook_new();

	char spriteList[256][3][MAX_SIZE];

	FILE* f = NULL;
	char c[MAX_SIZE] = "";
	char d[MAX_SIZE] = "";

	f = fopen("sprites.lst", "r");

	int i = 0;
	int j = 0;

	if(f)
	{
		while(fgets(c, MAX_SIZE, f))
		{
			if(c[0] != '\n' && c[0] != '#' && c[0] != '-') {
			    strcpy(d, c);
			    strcpy(spriteList[i][0], str_split(d, " ")[0]);
			    strcpy(d, c);
			    strcpy(spriteList[i][1], str_split(d, " ")[1]);
			    strcpy(d, c);
			    d[ strlen(d) - 1 ] = '\0';
			    strcpy(spriteList[i][2], str_split(d, " ")[2]);
			    i++;
			}
		}

		strcpy(spriteList[i+1][0], "");

		fclose(f);
	}
	else
	  printf("Cannot open sprites.lst\n");
	
	map_editor_add_tab(pNotebookMap, "map.lvl", spriteList);
	map_editor_add_tab(pNotebookMap, "map2.lvl", spriteList);
	map_editor_add_tab(pNotebookMap, "map.lvl", spriteList);

	return pNotebookMap;
}

static void map_editor_add_tab(GtkWidget* pNotebookMap, const gchar* f, char spriteList[TAB_SIZE][3][MAX_SIZE])
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pScrollbar = NULL;
	gchar* img;

	int sizeX = 0;
	int sizeY = 0;

	char* map = map_read_file(f, &sizeX, &sizeY);

	pTabLabel = gtk_label_new(f);
		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(sizeX, sizeY, TRUE);
		for(int i=0; i<sizeY; i++)
		{
			for(int j=0; j<sizeX; j++)
			{
				img = "./images/empty.png";
				
				for(int k=0; k<TAB_SIZE; k++)
				{
					if(spriteList[k][0] == "")
						break;
					if( map[CELL(i,j,sizeX)] == strToHex(spriteList[k][2]) )
					{
						img = spriteList[k][1];
						break;
					}
            	}

				pImage = gtk_image_new_from_file(img);
					gtk_table_attach( GTK_TABLE(pTable), pImage, i, i+1, j, j+1, FALSE, FALSE, 0, 0);
			}
		}
		gtk_container_add(GTK_CONTAINER(pAlignment), pTable);

	// Ajout de la scrollbar
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(pScrollbar), pAlignment);

	gtk_notebook_append_page(pNotebookMap, pScrollbar, pTabLabel);
}