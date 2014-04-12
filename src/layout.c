#include <layout.h>

GtkWidget* layout_init(GtkWidget* MainWindow)
{
	GtkWidget* pMainBox = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pMap = NULL;

	// Sprites list array
	char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE];

	FILE* f = NULL;
	char c[MAX_SIZE] = "";
	char d[MAX_SIZE] = "";

	// We open sprites.lst
	f = fopen("sprites.lst", "r");

	int i = 0;

	// Creation of the array that contains the map data
	if(f)
	{
		while(fgets(c, MAX_SIZE, f))
		{
			if(c[0] != '\n' && c[0] != '#' && c[0] != '-') {
				// Each line of the file that does not start with a '#' or '-' is cut in three different strings
			    strcpy(d, c);
				// The first one is the name of the sprite
			    strcpy(spriteList[CELL(i,0,MAX_SIZE_TAB_X)], str_split(d, " ")[0]);
			    strcpy(d, c);
				// The second one is the full path to the image
			    strcpy(spriteList[CELL(i,1,MAX_SIZE_TAB_X)], str_split(d, " ")[1]);
			    strcpy(d, c);
			    d[ strlen(d) - 1 ] = '\0';
				// The third one is the hexa code
			    strcpy(spriteList[CELL(i,2,MAX_SIZE_TAB_X)], str_split(d, " ")[2]);
			    i++;
			}
		}
		// The array's end is signaled with an empty string
		strcpy(spriteList[CELL(i+1,0,MAX_SIZE_TAB_X)], "");
		fclose(f);
	}
	else
	  printf("Cannot open sprites.lst\n");

	// Main window creation
	MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(MainWindow), "Map Editor");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 800, 600);
	gtk_widget_set_size_request(MainWindow, 400, 400);

	// Main container creation
	pMainBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(MainWindow), pMainBox);

	pMap = map_editor_new(spriteList);


	unsigned char mapSprites[MAX_SIZE_TAB_X] = "";
	struct data data;
		data_set_widget(&data, GTK_WIDGET(pMap));
		data_set_spriteslst(&data, (char(*)[MAX_SIZE])spriteList);
		data_set_code(&data, 0x30);
		data_set_x(&data, 12);
		data_set_y(&data, 12);
		data_set_up_x(&data, 15);
		data_set_up_y(&data, 15);
		data_set_map_sprites(&data, mapSprites);
		data_set_save(&data, FALSE);
		data_set_file(&data, FALSE);


	// Table creation
	pTable = gtk_table_new(4, 4, TRUE);
		data_set_table(&data, GTK_WIDGET(pTable));
		gtk_table_attach( GTK_TABLE(pTable), spriteslist_new(&data), 0, 1, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
		gtk_table_attach( GTK_TABLE(pTable), GTK_WIDGET(pMap), 1, 4, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
	
	// We then add the menu, the toolbar and the table to the main container
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( menu_new(&data) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( toolbar_new(&data) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( pTable ), TRUE, TRUE, 0);

	return MainWindow;
}