#include <callback.h>
#include <assert.h>

struct data
{
	GtkWidget* widget;
	char** spritesList;
	char code;
	int x;
	int y;
};

void data_set_widget(struct data* data, GtkWidget* widget)
{
	assert(data);
	data->widget = widget;
}

void data_set_spriteslst(struct data* data, char spritesList[][MAX_SIZE])
{
	assert(data);
	data->spritesList = (char **)spritesList;
}

// void data_set_sprite(struct data* data, char* sprite)
// {
// 	assert(data);
// 	data->sprite = (char *)calloc(strlen(sprite)+1, sizeof(char));
// 	strcpy(data->sprite, sprite);
// 	printf("%s\n", data->sprite);
// }

void data_set_code(struct data* data, char code)
{
	assert(data);
	data->code = code;
}

void data_set_x(struct data* data, int x)
{
	assert(data);
	data->x = x;
}

void data_set_y(struct data* data, int y)
{
	assert(data);
	data->y = y;
}

GtkWidget* data_get_widget(struct data* data)
{
	assert(data);
	return data->widget;
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

char data_get_code(struct data* data)
{
	assert(data);
	return data->code;
}

char** data_get_spriteslst(struct data* data)
{
	assert(data);
	return data->spritesList;
}

int data_get_x(struct data* data)
{
	assert(data);
	return data->x;
}

int data_get_y(struct data* data)
{
	assert(data);
	return data->y;
}

void map_editor_new_file(GtkButton* button, gpointer data)
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	// GtkWidget* pScrollbar = NULL;
	gchar* img;

	GtkNotebook* pNotebookMap = GTK_NOTEBOOK(data_get_widget(data));
	int sizeX = data_get_x(data); 
	int sizeY = data_get_y(data);

	assert(pNotebookMap);

	pTabLabel = gtk_label_new("Untitled_map.lvl");
		pAlignment = gtk_alignment_new(0.5, 0.5, 0, 0);
		pTable = gtk_table_new(sizeX, sizeY, TRUE);
		for(int i=0; i<sizeY; i++)
		{
			for(int j=0; j<sizeX; j++)
			{
				img = "./images/empty.png";
				pImage = gtk_image_new_from_file(img);
					gtk_widget_show(pImage);
					gtk_table_attach( GTK_TABLE(pTable), pImage, i, i+1, j, j+1, FALSE, FALSE, 0, 0);
			}
		}
		gtk_container_add(GTK_CONTAINER(pAlignment), pTable);

	// Ajout de la scrollbar
  	// pScrollbar = gtk_scrolled_window_new (NULL, NULL);
 //    gtk_box_pack_start (GTK_BOX(pAlignment), pScrollbar, TRUE, TRUE, 0);
	// //gtk_container_add(GTK_CONTAINER(pScrollbar), pAlignment);
	// printf("AAA\n");

	gtk_notebook_append_page(GTK_NOTEBOOK(pNotebookMap), pAlignment, pTabLabel);
	gtk_widget_show(pAlignment);
	gtk_widget_show(pTable);
}

void map_editor_open_file(GtkButton* button, gpointer data)
{
	GtkWidget *pDialog = NULL;

  	pDialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
  	gtk_widget_show(pDialog);

  	if (gtk_dialog_run(GTK_DIALOG (pDialog)) == GTK_RESPONSE_ACCEPT)
  	{
  		gchar* fileName = NULL;
  		// GtkWidget* toplevel = gtk_widget_get_toplevel(GTK_WIDGET(button));
  		GtkWidget* pErrorMessage = NULL;

	    fileName = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pDialog));

	    if(map_is_valid_file(fileName)) {
  			map_editor_add_tab(GTK_NOTEBOOK(data_get_widget(data)), fileName, (char (*)[MAX_SIZE])data_get_spriteslst(data), data);
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

void map_editor_add_tab(GtkNotebook* pNotebookMap, const gchar* f, char spriteList[MAX_SIZE_TAB_X*MAX_SIZE_TAB_Y][MAX_SIZE], gpointer data)
{
	GtkWidget* pTabLabel = NULL;
	GtkWidget* pTable = NULL;
	GtkWidget* pImage = NULL;
	GtkWidget* pAlignment = NULL;
	//GtkWidget* pScrollbar = NULL;
	GtkWidget* pEventBox = NULL;
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

	// Ajout de la scrollbar
	// pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	// gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	// gtk_container_add(GTK_CONTAINER(pScrollbar), pAlignment);

	gtk_notebook_append_page(pNotebookMap, pAlignment, pTabLabel);
	gtk_widget_show(pAlignment);
	gtk_widget_show(pTable);
}

void map_editor_replace_sprite(GtkWidget* parent, GdkEventButton* event, gpointer data)
{	
	GtkWidget* pImage = NULL;

	GList *children, *iter;

	assert(data);

	children = gtk_container_get_children(GTK_CONTAINER(parent));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);

	printf("%02x %s\n", data_get_code(data), data_get_sprite(data_get_code(data), (char (*)[MAX_SIZE])data_get_spriteslst(data)) );
	pImage = gtk_image_new_from_file( data_get_sprite(data_get_code(data), (char (*)[MAX_SIZE])data_get_spriteslst(data)) );
					gtk_container_add(GTK_CONTAINER(parent), pImage);
					gtk_widget_show(pImage);
					gtk_widget_show(parent);
					gtk_widget_set_events (parent, GDK_BUTTON_PRESS_MASK);
    				g_signal_connect (parent, "button_press_event", G_CALLBACK(map_editor_replace_sprite), data);
}
