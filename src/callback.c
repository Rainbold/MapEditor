#include <callback.h>
#include <functions.h>
#include <assert.h>

// Data initialization
struct data* data_init()
{
	struct data* data = malloc(sizeof(struct data*));
	data->code = 0x30;
	data->x = 12;
	data->y = 12;
	data->upX = 12;
	data->upY = 12;
	data->save = FALSE;
	data->file = FALSE;

	return data;
}

void data_set_filename(struct data* data, gchar* filename)
{
	assert(data);
	data->filename = filename;
}

gchar* data_get_filename(struct data* data)
{
	assert(data);
	return data->filename;
}

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

void data_set_table(struct data* data, GtkWidget* widget)
{
	assert(data);
	data->table = widget;
}

GtkWidget* data_get_table(struct data* data)
{
	assert(data);
	return data->table;
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

char* data_get_sprite(unsigned char code, char spritesList[][MAX_SIZE])
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

void data_set_code(struct data* data, unsigned char code)
{
	assert(data);
	data->code = code;
}

unsigned char data_get_code(struct data* data)
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

void data_set_file(struct data* data, gboolean file)
{
	assert(data);
	data->file = file;
}

gboolean data_get_file(struct data* data)
{
	assert(data);
	return data->file;
}

void data_set_up_x(struct data* data, int x)
{
	assert(data);
	data->upX = x;
}

int data_get_up_x(struct data* data)
{
	assert(data);
	return data->upX;
}

void data_set_up_y(struct data* data, int y)
{
	assert(data);
	data->upY = y;
}

int data_get_up_y(struct data* data)
{
	assert(data);
	return data->upY;
}

void data_set_map_sprites(struct data* data, unsigned char mapSprites[MAX_SIZE_TAB_X])
{
	assert(data);
	for(int i=0; i<MAX_SIZE_TAB_X; i++)
	{
		data->mapSprites[i] = mapSprites[i];
	}
}

unsigned char* data_get_map_sprites(struct data* data)
{
	assert(data);
	return data->mapSprites;
}

void data_set_cell_type(struct data* data, char type, int x, int y)
{
	assert(data);
	data->mapSprites[ CELL(x,y,data->x) ] = type;
}

void map_editor_new_file(GtkButton* button, gpointer data)
{
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pEventBox = NULL;
	gchar* img;
	int cancel = 0;

	// If the current file is not saved
	if(data_get_save(data))
	{
		GtkWidget* pBox;
		GtkWidget* pLabel = NULL;

		// Dialog creation
	    pBox = gtk_dialog_new_with_buttons("Unsaved file",
	        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
	        GTK_DIALOG_MODAL,
	        GTK_STOCK_CLOSE,GTK_RESPONSE_CLOSE,
	        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	        GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	        NULL);
	 
	    pLabel = gtk_label_new("Save changes to current file before closing ?");

	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBox)->vbox), pLabel, TRUE, FALSE, 1.0);
	 
	    gtk_widget_show_all(GTK_DIALOG(pBox)->vbox);
	    switch (gtk_dialog_run(GTK_DIALOG(pBox)))
	    {
	        case GTK_RESPONSE_CANCEL:
	        	cancel = 1;
	        	break;
	        case GTK_RESPONSE_ACCEPT:
	        	map_editor_save(button, data);
	        case GTK_RESPONSE_CLOSE:
	        	cancel = 0;
	        	break;
	        case GTK_RESPONSE_NONE:
	        default:
	            break;
	    }

		gtk_widget_destroy(pBox);
	}

	if(!cancel) {
		int sizeX = 0;
		int sizeY = 0;

		GtkWidget* pBoite;
		GtkAdjustment* spinnerAdjX = NULL;
		GtkAdjustment* spinnerAdjY = NULL;
		GtkWidget* pSpinButtonX = NULL;
		GtkWidget* pSpinButtonY = NULL;
		GtkWidget* pLabelX = NULL;
		GtkWidget* pLabelY = NULL;

		// Dialog used to select the map size
	    pBoite = gtk_dialog_new_with_buttons("Map size",
	        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
	        GTK_DIALOG_MODAL,
	        GTK_STOCK_OK,GTK_RESPONSE_OK,
	        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	        NULL);
	 
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
	 
	 	// The dialog windows and its elements are displayed
	    gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);


	    switch (gtk_dialog_run(GTK_DIALOG(pBoite)))
	    {
	    	// If the ok button is pressed
	        case GTK_RESPONSE_OK:
	        	data_set_file(data, TRUE);

	        	sizeX = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(pSpinButtonX));
	        	sizeY = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(pSpinButtonY));

				data_set_save(data, FALSE);
				data_set_filename(data, "");

	        	data_set_x(data, sizeX);
	        	data_set_y(data, sizeY);
	        	
	        	// Initialization of the map variable containing the hex values
	        	unsigned char mapS[MAX_SIZE_TAB_X] = "";
	        	for(int i=0; i<MAX_SIZE_TAB_X; i++)
					mapS[i] = 0x00;
				data_set_map_sprites(data, mapS);
				
				// Set the window title				
	        	gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), "Map Editor - Untitled Map");
	    
					pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
					pTable = gtk_table_new(sizeX, sizeY, TRUE);
					// The window is filled with white images to which event boxes are attached
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
								gtk_table_attach( GTK_TABLE(pTable), pEventBox, j, j+1, i, i+1, FALSE, FALSE, 0, 0);
						}
					}
					gtk_container_add(GTK_CONTAINER(pAlignment), pTable);


				GList *children, *iter;

				// If there was a previous map loaded, it is removed from the view
				children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
				for(iter = children; iter != NULL; iter = g_list_next(iter))
					gtk_widget_destroy(GTK_WIDGET(iter->data));
				g_list_free(children);

				gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(data_get_widget(data)), pAlignment);

				gtk_widget_show(pTable);
				gtk_widget_show(pAlignment);
	            break;
	        case GTK_RESPONSE_CANCEL:
	        case GTK_RESPONSE_NONE:
	        default:
	            break;
	    }
	 
	    gtk_widget_destroy(pBoite);
	}
}

void map_editor_open_file_aux(GtkNotebook* pNotebookMap, const gchar* f, char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE], gpointer data)
{
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pEventBox = NULL;
	gchar* img;

	int sizeX = 0;
	int sizeY = 0;

	unsigned char* map = map_read_file(f, &sizeX, &sizeY);
	data_set_map_sprites(data, map);

	// Map title
	const int len = strlen( "Map Editor - " );
	char* title = malloc(sizeof(char)*(len+strlen(f)+1));
	strcpy( title, "Map Editor - ");
	strcat( title, f );
	gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);

		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(sizeX, sizeY, TRUE);

		// All the images are displayed depending on the array containing all the hex values
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

	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(data_get_widget(data)), pAlignment);

	gtk_widget_show(pTable);
	gtk_widget_show(pAlignment);
}

void map_editor_open_file(GtkButton* button, gpointer data)
{
	GtkWidget *pDialog = NULL;
	int cancel = 0;

	if(data_get_save(data))
	{
		GtkWidget* pBox;
		GtkWidget* pLabel = NULL;

	    pBox = gtk_dialog_new_with_buttons("Unsaved file",
	        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
	        GTK_DIALOG_MODAL,
	        GTK_STOCK_OPEN,GTK_RESPONSE_CLOSE,
	        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	        GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	        NULL);
	 
	    pLabel = gtk_label_new("Save changes to current file before closing ?");

	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBox)->vbox), pLabel, TRUE, FALSE, 1.0);
	 
	    gtk_widget_show_all(GTK_DIALOG(pBox)->vbox);
	    switch (gtk_dialog_run(GTK_DIALOG(pBox)))
	    {
	        case GTK_RESPONSE_CANCEL:
	        	cancel = 1;
	        	break;
	        case GTK_RESPONSE_ACCEPT:
	        	map_editor_save(button, data);
	        case GTK_RESPONSE_CLOSE:
	        	cancel = 0;
	        	break;
	        case GTK_RESPONSE_NONE:
	        default:
	            break;
	    }

		gtk_widget_destroy(pBox);
	}

	if(!cancel) {
	  	pDialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	  	gtk_widget_show(pDialog);

	  	if (gtk_dialog_run(GTK_DIALOG (pDialog)) == GTK_RESPONSE_ACCEPT)
	  	{
	  		gchar* fileName = NULL;
	  		GtkWidget* pErrorMessage = NULL;

		    fileName = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pDialog));

		    if(map_is_valid_file(fileName)) {
		    	data_set_save(data, FALSE);
		    	data_set_filename(data, fileName);
	        	data_set_file(data, TRUE);
	  			map_editor_open_file_aux(GTK_NOTEBOOK(data_get_widget(data)), fileName, (char (*)[MAX_SIZE])data_get_spriteslst(data), data);
		    }
	  		else {
	  			pErrorMessage = gtk_message_dialog_new (GTK_WINDOW(pDialog), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Invalid file.");
	  			gtk_widget_show(pErrorMessage);
				gtk_dialog_run (GTK_DIALOG (pErrorMessage));
				gtk_widget_destroy (pErrorMessage);
	  		}
	  		
	  		gtk_widget_destroy (pDialog);

	  	}

	  	if (gtk_dialog_run(GTK_DIALOG (pDialog)) == GTK_RESPONSE_CANCEL)
	  	{
	  		gtk_widget_destroy (pDialog);
	  	}
	}
}

void map_editor_save_as(GtkButton* button, gpointer data)
{
	// If there's a file loaded or unsaved
	if(data_get_file(data) || data_get_save(data))
	{
		GtkWidget *p_dialog = NULL;

        p_dialog = gtk_file_chooser_dialog_new ("Save as", NULL,
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                                NULL);

        if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
        {
          	data_set_filename(data, gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog)));
			
			int len = strlen("Map Editor - ");
			len += strlen(data_get_filename(data));
			char* title = malloc(sizeof(char)*(len+1));
			strcpy( title, "Map Editor - ");
			strcat( title, data_get_filename(data) );
			gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);
			data_set_save(data, FALSE);
			free(title);

			FILE* f = NULL;
			f = fopen(data_get_filename(data), "w");

			if(f)
			{
				fputc('l', f);
				fputc('v', f);
				fputc('l', f);
				fputc(data_get_x(data), f);
				fputc(data_get_y(data), f);
				for(int i=0; i<data_get_y(data); i++) {
					for(int j=0; j<data_get_x(data); j++) {	
						fputc(data_get_map_sprites(data)[CELL(j,i,data_get_x(data))], f);
					}
				}


				fclose(f);
			}
			else
				printf("Impossible de sauver le fichier\n");
        }

        gtk_widget_destroy (p_dialog);
	}
}

void map_editor_save(GtkButton* button, gpointer data)
{
	if(data_get_file(data) || data_get_save(data))
	{
		if(!strcmp(data_get_filename(data), ""))
		{
			map_editor_save_as(button, data);
		}
		else
		{
			int len = strlen("Map Editor - ");
			len += strlen(data_get_filename(data));
			char* title = malloc(sizeof(char)*(len+1));
			strcpy( title, "Map Editor - ");
			strcat( title, data_get_filename(data) );
			gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);
			data_set_save(data, FALSE);
			free(title);

			FILE* f = NULL;
			f = fopen(data_get_filename(data), "w");

			if(f)
			{
				fputc('l', f);
				fputc('v', f);
				fputc('l', f);
				fputc(data_get_x(data), f);
				fputc(data_get_y(data), f);
				for(int i=0; i<data_get_y(data); i++) {
					for(int j=0; j<data_get_x(data); j++) {	
						fputc(data_get_map_sprites(data)[CELL(j,i,data_get_x(data))], f);
					}
				}


				fclose(f);
			}
			else
				printf("Impossible de sauver le fichier\n");
    	}
	}
}

void map_editor_close(GtkButton* button, gpointer data)
{
	if(data_get_file(data))
	{
		GList *children, *iter;
		int cancel = 0;

		if(data_get_save(data))
		{
			GtkWidget* pBox;
			GtkWidget* pLabel = NULL;
			 
		    pBox = gtk_dialog_new_with_buttons("Unsaved file",
		        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
		        GTK_DIALOG_MODAL,
		        GTK_STOCK_CLOSE,GTK_RESPONSE_CLOSE,
		        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
		        GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
		        NULL);
		 
		    pLabel = gtk_label_new("Save changes to current file before closing ?");

		    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBox)->vbox), pLabel, TRUE, FALSE, 1.0);
		 
		    gtk_widget_show_all(GTK_DIALOG(pBox)->vbox);
		    switch (gtk_dialog_run(GTK_DIALOG(pBox)))
		    {
		        case GTK_RESPONSE_CANCEL:
		        	cancel = 1;
		        	break;
		        case GTK_RESPONSE_ACCEPT:
		        	map_editor_save(button, data);
		        case GTK_RESPONSE_CLOSE:
		        	cancel = 0;
		        	break;
		        case GTK_RESPONSE_NONE:
		        default:
		            break;
		    }



			gtk_widget_destroy(pBox);
		}

	    if(!cancel)
	    {
			gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), "Map Editor");
			data_set_save(data, FALSE);
			data_set_code(data, 0x00);
			data_set_x(data, 12);
			data_set_y(data, 12);
			data_set_up_x(data, 15);
			data_set_up_y(data, 15);
			data_set_save(data, FALSE);
			data_set_file(data, FALSE);
			data_set_filename(data, "");
			children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
			children = gtk_container_get_children(GTK_CONTAINER(children->data));
			for(iter = children; iter != NULL; iter = g_list_next(iter))
				gtk_widget_destroy(GTK_WIDGET(iter->data));
			g_list_free(children);
		}
	}
}

void map_editor_quit(GtkButton* button, gpointer data)
{
	int cancel = 0;

	if(data_get_save(data))
	{
		GtkWidget* pBox;
		GtkWidget* pLabel = NULL;
		 
	    pBox = gtk_dialog_new_with_buttons("Unsaved file",
	        GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )),
	        GTK_DIALOG_MODAL,
	        GTK_STOCK_CLOSE,GTK_RESPONSE_CLOSE,
	        GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
	        GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	        NULL);
	 
	    pLabel = gtk_label_new("Save changes to current file before closing ?");

	    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBox)->vbox), pLabel, TRUE, FALSE, 1.0);
	 
	    gtk_widget_show_all(GTK_DIALOG(pBox)->vbox);
	    switch (gtk_dialog_run(GTK_DIALOG(pBox)))
	    {
	        case GTK_RESPONSE_CANCEL:
	        	cancel = 1;
	        	break;
	        case GTK_RESPONSE_ACCEPT:
	        	map_editor_save(button, data);
	        case GTK_RESPONSE_CLOSE:
	        	cancel = 0;
	        	break;
	        case GTK_RESPONSE_NONE:
	        default:
	            break;
	    }

		gtk_widget_destroy(pBox);
	}

    if(!cancel)
    {
		gtk_main_quit();
	}

}

// Function used to replace the sprite when a event box is clicked
void map_editor_replace_sprite(GtkWidget* parent, GdkEventButton* event, gpointer data)
{	
	GtkWidget* pImage = NULL;

	GList *children, *iter;

	assert(data);

	gint wx, wy;
	gint cx, cy;
	children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
	children = gtk_container_get_children(GTK_CONTAINER(children->data));
	children = gtk_container_get_children(GTK_CONTAINER(children->data));
	gtk_widget_translate_coordinates(GTK_WIDGET(children->data), gtk_widget_get_toplevel(parent), 0, 0, &wx, &wy);
	gtk_widget_translate_coordinates(parent, gtk_widget_get_toplevel(parent), 0, 0, &cx, &cy);
	
	//data_set_cell_type(data, data_get_code(data), (cx-wx)/40, (cy-wy)/40);
	unsigned char mapS[MAX_SIZE_TAB_X] = ""; 
	for(int i=0; i<MAX_SIZE_TAB_X; i++)
		mapS[i] = data_get_map_sprites(data)[i];
	mapS[CELL((cx-wx)/40, (cy-wy)/40, data_get_x(data))] = data_get_code(data);
	data_set_map_sprites(data, mapS);

	if(!data_get_save(data)) {
		const int len = strlen( gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
		char* title = malloc(sizeof(char)*(len+2));	
		strcpy( title, gtk_window_get_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data)))) );
		strcat( title, "*" );
		gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel( data_get_widget(data) )), title);
		data_set_save(data, TRUE);
		free(title);
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


void map_editor_change_size_x(GtkSpinButton* spinButton, gpointer data)
{
	assert(data);
	data_set_up_x(data, (int)gtk_spin_button_get_value(spinButton));
}

void map_editor_change_size_y(GtkSpinButton* spinButton, gpointer data)
{
	assert(data);
	data_set_up_y(data, (int)gtk_spin_button_get_value(spinButton));
}

// Not fully fonctionnal; abandonned idea
void map_editor_change_size(GtkButton* button, gpointer data)
{
	assert(data);

	int sizeX = data_get_up_x(data);
	int sizeY = data_get_up_y(data);

	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	GtkWidget* pEventBox = NULL;
	gchar* img;

	if(data_get_file(data))
	{
		map_resize_var(data, data_get_x(data), data_get_y(data), sizeX, sizeY);
		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(sizeX, sizeY, TRUE);
		for(int i=0; i<sizeY; i++)
		{
			for(int j=0; j<sizeX; j++)
			{
				img = "./images/empty.png";
				
				for(int k=0; k<MAX_SIZE_TAB_X; k++)
				{
					if(!strcmp(((char(*)[MAX_SIZE])data_get_spriteslst(data))[CELL(k, 0, MAX_SIZE_TAB_X)], ""))
						break;
					if( data_get_map_sprites(data)[CELL(j,i,sizeX)] == strToHex(((char(*)[MAX_SIZE])data_get_spriteslst(data))[CELL(k, 2, MAX_SIZE_TAB_X)]) )
					{
						img = ((char(*)[MAX_SIZE])data_get_spriteslst(data))[CELL(k, 1, MAX_SIZE_TAB_X)];
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
					gtk_table_attach( GTK_TABLE(pTable), pEventBox, j, j+1, i, i+1, FALSE, FALSE, 0, 0);
			}
		}
		gtk_container_add(GTK_CONTAINER(pAlignment), pTable);


		GList *children, *iter;

		children = gtk_container_get_children(GTK_CONTAINER(data_get_widget(data)));
		for(iter = children; iter != NULL; iter = g_list_next(iter))
			gtk_widget_destroy(GTK_WIDGET(iter->data));
		g_list_free(children);

		data_set_x(data, sizeX);
		data_set_y(data, sizeY);

		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(data_get_widget(data)), pAlignment);

		gtk_widget_show(pTable);
		gtk_widget_show(pAlignment);
	}
}

// Changes the current sprite selected by the user
void spriteslst_change_sprite(GtkTreeView *treeView, gpointer data)
{
	GtkTreePath* path[MAX_SIZE_TAB_X];
	GtkTreeViewColumn** col = NULL;

	gtk_tree_view_get_cursor(treeView,path,col);
	data_set_code(data, strToHex(((char (*)[MAX_SIZE])data_get_spriteslst(data))[CELL(atoi(gtk_tree_path_to_string(path[0])), 2, MAX_SIZE_TAB_X)]));
}