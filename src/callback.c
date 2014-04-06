#include <callback.h>
#include <assert.h>

struct data
{
	GtkWidget* widget;
	char** spritesList;
	char code;
	int x;
	int y;
	struct filesList* filesList;
	gboolean save;
};

void data_set_widget(struct data* data, GtkWidget* widget)
{
	assert(data);
	data->widget = widget;
}

GtkWidget* data_get_widget(struct data* data)
{
	assert(data);
	return data->widget;
}

void data_set_spriteslst(struct data* data, char spritesList[][MAX_SIZE])
{
	assert(data);
	data->spritesList = (char **)spritesList;
}

char** data_get_spriteslst(struct data* data)
{
	assert(data);
	return data->spritesList;
}

char* data_get_sprite(char code, char spritesList[][MAX_SIZE])
{
	int i = 0;
	
	while(strcmp(spritesList[CELL(i,0,MAX_SIZE_TAB_X)], ""))
	{
		if(strToHex(spritesList[CELL(i,2,MAX_SIZE_TAB_X)]) == code)
			return spritesList[CELL(i,1,MAX_SIZE_TAB_X)];
		i++;
	}
	return "";
}

void data_set_code(struct data* data, char code)
{
	assert(data);
	data->code = code;
}

char data_get_code(struct data* data)
{
	assert(data);
	return data->code;
}

void data_set_x(struct data* data, int x)
{
	assert(data);
	data->x = x;
}

int data_get_x(struct data* data)
{
	assert(data);
	return data->x;
}

void data_set_y(struct data* data, int y)
{
	assert(data);
	data->y = y;
}

int data_get_y(struct data* data)
{
	assert(data);
	return data->y;
}

void data_set_save(struct data* data, gboolean save)
{
	assert(data);
	data->save = save;
}

gboolean data_get_save(struct data* data)
{
	assert(data);
	return data->save;
}


void map_editor_new_file(GtkButton* button, gpointer data)
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pEventBox = NULL;
	gchar* img;

	if(data_get_save(data)) {

	}
	else {

		int sizeX = data_get_x(data); 
		int sizeY = data_get_y(data);

		GtkWidget* pBoite;
		GtkAdjustment* spinnerAdjX = NULL;
		GtkAdjustment* spinnerAdjY = NULL;
		GtkWidget* pSpinButtonX = NULL;
		GtkWidget* pSpinButtonY = NULL;
		GtkWidget* pLabelX = NULL;
		GtkWidget* pLabelY = NULL;
	    const gchar* sNom;
	 
	    /* Création de la boite de dialogue */
	    /* 1 bouton Valider */
	    /* 1 bouton Annuler */
	    pBoite = gtk_dialog_new_with_buttons("Saisie du nom",
	        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
	        GTK_DIALOG_MODAL,
	        GTK_STOCK_OK,GTK_RESPONSE_OK,
	        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	        NULL);
	 
	    /* Création de la zone de saisie */
	    spinnerAdjX = (GtkAdjustment*) gtk_adjustment_new(12.0, 0.0, 50.0, 1.0, 5.0, 5.0);
			pSpinButtonX = gtk_spin_button_new(spinnerAdjX, 1.0, 0);
		spinnerAdjY = (GtkAdjustment*) gtk_adjustment_new(12.0, 0.0, 50.0, 1.0, 5.0, 5.0);
			pSpinButtonY = gtk_spin_button_new(spinnerAdjY, 1.0, 0);

		pLabelX = gtk_label_new("Horizontal map size");
		pLabelY = gtk_label_new("Vertical map size");

	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pLabelX, TRUE, FALSE, 1.0);
	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pSpinButtonX, TRUE, FALSE, 1.0);
	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pLabelY, TRUE, FALSE, 1.0);
	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pSpinButtonY, TRUE, FALSE, 1.0);
	 
	    /* Affichage des éléments de la boite de dialogue */
	    gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);



		/* On lance la boite de dialogue et on récupéré la réponse */
	    switch (gtk_dialog_run(GTK_DIALOG(pBoite)))
	    {
	        /* L utilisateur valide */
	        case GTK_RESPONSE_OK:
	        	sizeX = gtk_spin_button_get_value_as_int(pSpinButtonX);
	        	sizeY = gtk_spin_button_get_value_as_int(pSpinButtonY);
	        	gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), "Map Editor - Untitled_map.lvl");
	    
					pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
					pTable = gtk_table_new(sizeX, sizeY, TRUE);
					for(int i=0; i<sizeY; i++)
					{
						for(int j=0; j<sizeX; j++)
						{
							img = "./images/empty.png";
							pEventBox = gtk_event_box_new();
							pImage = gtk_image_new_from_file(img);
								gtk_container_add(GTK_CONTAINER(pEventBox), pImage);
								gtk_widget_show(pImage);
								gtk_widget_show(pEventBox);
								gtk_widget_set_events (pEventBox, GDK_BUTTON_PRESS_MASK);
			    				g_signal_connect (pEventBox, "button_press_event", G_CALLBACK(map_editor_replace_sprite), data);
								gtk_table_attach( GTK_TABLE(pTable), pEventBox, i, i+1, j, j+1, FALSE, FALSE, 0, 0);
						}
					}
					gtk_container_add(GTK_CONTAINER(pAlignment), pTable);


				GList *children, *iter;

				children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
				for(iter = children; iter != NULL; iter = g_list_next(iter))
					gtk_widget_destroy(GTK_WIDGET(iter->data));
				g_list_free(children);

				gtk_scrolled_window_add_with_viewport(GTK_CONTAINER(data_get_widget(data)), pAlignment);

				gtk_widget_show(pTable);
				gtk_widget_show(pAlignment);
	            break;
	        /* L utilisateur annule */
	        case GTK_RESPONSE_CANCEL:
	        case GTK_RESPONSE_NONE:
	        default:
	            break;
	    }
	 
	    /* Destruction de la boite de dialogue */
	    gtk_widget_destroy(pBoite);
	}
}

void map_editor_open_file(GtkButton* button, gpointer data)
{
	GtkWidget *pDialog = NULL;

	if(data_get_save(data))
		printf("Il faut sauvegarder le fichier\n");
	else {
	  	pDialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	  	gtk_widget_show(pDialog);

	  	if (gtk_dialog_run(GTK_DIALOG (pDialog)) == GTK_RESPONSE_ACCEPT)
	  	{
	  		gchar* fileName = NULL;
	  		// GtkWidget* toplevel = gtk_widget_get_toplevel(GTK_WIDGET(button));
	  		GtkWidget* pErrorMessage = NULL;

		    fileName = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pDialog));

		    if(map_is_valid_file(fileName)) {
	  			map_editor_open_file_aux(GTK_NOTEBOOK(data_get_widget(data)), fileName, (char (*)[MAX_SIZE])data_get_spriteslst(data), data);
		    }
	  		else {
	  			pErrorMessage = gtk_message_dialog_new (GTK_WINDOW(pDialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid file.");
	  			gtk_widget_show(pErrorMessage);
				gtk_dialog_run (GTK_DIALOG (pErrorMessage));
				gtk_widget_destroy (pErrorMessage);
	  		}
	  		
		    g_free (fileName), fileName = NULL;
	  		gtk_widget_destroy (pDialog);

	  	}

	  	if (gtk_dialog_run(GTK_DIALOG (pDialog)) == GTK_RESPONSE_CANCEL)
	  	{
	  		gtk_widget_destroy (pDialog);
	  	}
	}
}

void map_editor_open_file_aux(GtkNotebook* pNotebookMap, const gchar* f, char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE], gpointer data)
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pEventBox = NULL;
	gchar* img;

	int sizeX = 0;
	int sizeY = 0;

	char* map = map_read_file(f, &sizeX, &sizeY);

	const int len = strlen( gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
	char* title = malloc(sizeof(char)*(len+strlen(f)+3));
	strcpy( title, gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
	strcat( title, " - " );
	strcat( title, f );
	gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);

		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(sizeX, sizeY, TRUE);
		for(int i=0; i<sizeY; i++)
		{
			for(int j=0; j<sizeX; j++)
			{
				img = "./images/empty.png";
				
				for(int k=0; k<MAX_SIZE_TAB_X; k++)
				{
					if(!strcmp(spriteList[CELL(k, 0, MAX_SIZE_TAB_X)], ""))
						break;
					if( map[CELL(i,j,sizeX)] == strToHex(spriteList[CELL(k, 2, MAX_SIZE_TAB_X)]) )
					{
						img = spriteList[CELL(k, 1, MAX_SIZE_TAB_X)];
						break;
					}
            	}

            	pEventBox = gtk_event_box_new();
				pImage = gtk_image_new_from_file(img);
					gtk_container_add(GTK_CONTAINER(pEventBox), pImage);
					gtk_widget_show(pImage);
					gtk_widget_show(pEventBox);
					gtk_widget_set_events (pEventBox, GDK_BUTTON_PRESS_MASK);
    				g_signal_connect (pEventBox, "button_press_event", G_CALLBACK(map_editor_replace_sprite), data);
					gtk_table_attach( GTK_TABLE(pTable), pEventBox, i, i+1, j, j+1, FALSE, FALSE, 0, 0);
			}
		}
		gtk_container_add(GTK_CONTAINER(pAlignment), pTable);


	GList *children, *iter;

	children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);

	gtk_scrolled_window_add_with_viewport(GTK_CONTAINER(data_get_widget(data)), pAlignment);

	gtk_widget_show(pTable);
	gtk_widget_show(pAlignment);
}

void map_editor_replace_sprite(GtkWidget* parent, GdkEventButton* event, gpointer data)
{	
	GtkWidget* pImage = NULL;

	GList *children, *iter;

	assert(data);

	if(!data_get_save(data)) {
		const int len = strlen( gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
		char* title = malloc(sizeof(char)*(len+2));
		strcpy( title, gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
		strcat( title, "*" );
		gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);
		data_set_save(data, TRUE);
	}

	children = gtk_container_get_children(GTK_CONTAINER(parent));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);

	pImage = gtk_image_new_from_file( data_get_sprite(data_get_code(data), (char (*)[MAX_SIZE])data_get_spriteslst(data)) );
					gtk_container_add(GTK_CONTAINER(parent), pImage);
					gtk_widget_show(pImage);
					gtk_widget_show(parent);
					gtk_widget_set_events (parent, GDK_BUTTON_PRESS_MASK);
    				g_signal_connect (parent, "button_press_event", G_CALLBACK(map_editor_replace_sprite), data);
}

void spriteslst_change_sprite(GtkTreeView *treeView, gpointer data)
{
	GtkTreePath* path[MAX_SIZE_TAB_X];
	GtkTreeViewColumn** col = NULL;

	gtk_tree_view_get_cursor(treeView,path,col);
	data_set_code(data, strToHex(((char (*)[MAX_SIZE])data_get_spriteslst(data))[CELL(atoi(gtk_tree_path_to_string(path[0])), 2, MAX_SIZE_TAB_X)]));
}