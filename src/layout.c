#include <layout.h>

GtkWidget* layout_init(GtkWidget* MainWindow)
{
	GtkWidget* pMainBox = NULL;
	GtkWidget* pTable = NULL;
	GtkNotebook* pNotebookMap = NULL;

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
			    strcpy(d, c);
			    strcpy(spriteList[CELL(i,0,MAX_SIZE_TAB_X)], str_split(d, " ")[0]);
			    strcpy(d, c);
			    strcpy(spriteList[CELL(i,1,MAX_SIZE_TAB_X)], str_split(d, " ")[1]);
			    strcpy(d, c);
			    d[ strlen(d) - 1 ] = '\0';
			    strcpy(spriteList[CELL(i,2,MAX_SIZE_TAB_X)], str_split(d, " ")[2]);
			    i++;
			}
		}
		strcpy(spriteList[CELL(i+1,0,MAX_SIZE_TAB_X)], "");
		fclose(f);
	}
	else
	  printf("Cannot open sprites.lst\n");

	// Création de la fenêtre principale de l'application
	MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_title(GTK_WINDOW(MainWindow), "Éditeur de maps");
	gtk_window_set_default_size(GTK_WINDOW(MainWindow), 800, 600);
	gtk_widget_set_size_request(MainWindow, 400, 400);

	// Création du conteneur principal
	pMainBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(MainWindow), pMainBox);

	pNotebookMap = map_editor_new(spriteList);

	//char sprite[MAX_SIZE] = "./images/player_down.png";

	struct data* data = malloc(sizeof(struct data*));
		data_set_widget(data, GTK_WIDGET(pNotebookMap));
		data_set_spriteslst(data, spriteList);
		data_set_code(data, 0x30);
		data_set_x(data, 12);
		data_set_y(data, 12);

	// Création de la table
	pTable = gtk_table_new(4, 4, TRUE);
		gtk_table_attach( GTK_TABLE(pTable), spriteslist_new(), 0, 1, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);
		gtk_table_attach( GTK_TABLE(pTable), GTK_WIDGET(pNotebookMap), 1, 4, 0, 4, GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0, 0);


	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( menu_new(data) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( toolbar_new(data) ), FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pMainBox), GTK_WIDGET( pTable ), TRUE, TRUE, 0);
	
	return MainWindow;
}