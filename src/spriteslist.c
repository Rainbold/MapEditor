#include <spriteslist.h>

enum {
	IMG_COLUMN = 0,
	TEXT_COLUMN,
	N_COLUMN
};

#define MAX_SIZE 1000

GtkWidget* spriteslist_new(gpointer data)
{
	GtkWidget* pListView = NULL;
	GtkTreeViewColumn* pColumn = NULL;
	GtkListStore* pSpriteList = NULL;
	GtkCellRenderer* pCellRenderer = NULL;
	GtkTreeIter pIter;
	GtkWidget* pScrollbar = NULL;
	gchar* sText = NULL;
	GtkWidget* vBox = NULL;
	GtkWidget* hBox = NULL;

	GtkWidget* pImage = NULL;
	GdkPixbuf* pPixBuf = NULL;

	sText = g_malloc(100);

	// Insertion des éléments
	pSpriteList = gtk_list_store_new(N_COLUMN, GDK_TYPE_PIXBUF, G_TYPE_STRING);

	FILE* f = NULL;
	char c[MAX_SIZE] = "";
	char img[MAX_SIZE] = "";

	f = fopen("sprites.lst", "r");

	if(f)
	{
		while(fgets(c, MAX_SIZE, f))
		{
			if(c[0] != '\n' && c[0] != '#' && c[0] != '-') {
				strcpy(img, str_split(c, " ")[1]);
				if(img[ strlen(img) - 1 ] == '\n')
					img[ strlen(img) - 1 ] = '\0';
				pImage = gtk_image_new_from_file(img);
				pPixBuf = gtk_image_get_pixbuf(GTK_IMAGE(pImage));
				gtk_list_store_append(pSpriteList, &pIter);
				sprintf(sText, str_split(c, " ")[0]);
				gtk_list_store_set(pSpriteList, &pIter, IMG_COLUMN, pPixBuf, TEXT_COLUMN, sText, -1);
			}
		}
		fclose(f);
	}
	else
		printf("Cannot open sprites.lst\n");

	g_free(sText);


	// View creation
	pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(pSpriteList));

	g_signal_connect(G_OBJECT(pListView), "cursor-changed", G_CALLBACK(spriteslst_change_sprite), data);
	// Creation of the first column
	pCellRenderer = gtk_cell_renderer_pixbuf_new();
	pColumn = gtk_tree_view_column_new_with_attributes("Images", pCellRenderer, "pixbuf", IMG_COLUMN, NULL);

	// The column is added to the view
	gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);

	// Second column creation
	pCellRenderer = gtk_cell_renderer_text_new();
	pColumn = gtk_tree_view_column_new_with_attributes("Nom", pCellRenderer, "text", TEXT_COLUMN, NULL);

	// The column is added to the view
	gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);

	// The scrollba is added to the view
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(pScrollbar), pListView);

	vBox = gtk_vbox_new(FALSE, 0);
	gtk_box_set_homogeneous(GTK_BOX(vBox), FALSE);
	
		hBox = gtk_hbox_new(FALSE, 0);
			gtk_box_set_homogeneous(GTK_BOX(hBox), FALSE);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(hBox), FALSE, FALSE, 0);
		hBox = gtk_hbox_new(FALSE, 0);
			gtk_box_set_homogeneous(GTK_BOX(hBox), FALSE);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(hBox), FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pScrollbar), GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0);

	return vBox;
}