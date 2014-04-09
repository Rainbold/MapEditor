#include <spriteslist.h>

enum {
	IMG_COLUMN = 0,
	TEXT_COLUMN,
	N_COLUMN
};

#define MAX_SIZE 1000

GtkWidget* spriteslist_new(gpointer data)
{
	GtkTreeView* pListView = NULL;
	GtkTreeViewColumn* pColumn = NULL;
	GtkListStore* pSpriteList = NULL;
	GtkCellRenderer* pCellRenderer = NULL;
	GtkTreeIter pIter;
	GtkWidget* pScrollbar = NULL;
	gchar* sText = NULL;
	GtkWidget* vBox = NULL;
	GtkWidget* hBox = NULL;
	GtkAdjustment* spinnerAdjX = NULL;
	GtkAdjustment* spinnerAdjY = NULL;
	GtkWidget* pSpinButtonX = NULL;
	GtkWidget* pSpinButtonY = NULL;
	GtkWidget* pLabelTitle = NULL;
	GtkWidget* pLabelX = NULL;
	GtkWidget* pLabelY = NULL;
	GtkWidget* pHSeparator = NULL;
	GtkWidget* pButton = NULL;

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
				printf("%s\n", img);
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


	// Création de la vue
	pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(pSpriteList));

	g_signal_connect(G_OBJECT(pListView), "cursor-changed", G_CALLBACK(spriteslst_change_sprite), data);
	// Création de la première colonne
	pCellRenderer = gtk_cell_renderer_pixbuf_new();
	pColumn = gtk_tree_view_column_new_with_attributes("Images", pCellRenderer, "pixbuf", IMG_COLUMN, NULL);

	// Ajout de la colonne à la vue
	gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);

	// Création de la deuxième colonne
	pCellRenderer = gtk_cell_renderer_text_new();
	pColumn = gtk_tree_view_column_new_with_attributes("Nom", pCellRenderer, "text", TEXT_COLUMN, NULL);

	// Ajout de la colonne à la vue
	gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);

	// Ajout de la scrollbar
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(pScrollbar), pListView);

	spinnerAdjX = (GtkAdjustment*) gtk_adjustment_new(15.0, 0.0, 50.0, 1.0, 5.0, 5.0);
		pSpinButtonX = gtk_spin_button_new(spinnerAdjX, 1.0, 0);
	spinnerAdjY = (GtkAdjustment*) gtk_adjustment_new(15.0, 0.0, 50.0, 1.0, 5.0, 5.0);
		pSpinButtonY = gtk_spin_button_new(spinnerAdjY, 1.0, 0);

	pLabelTitle = gtk_label_new("Map size");
	pLabelX = gtk_label_new("X ");
	pLabelY = gtk_label_new("Y ");

	pHSeparator = gtk_hseparator_new();

	pButton = gtk_button_new_with_label("Update");
		data_set_up_x(data, 15);
		data_set_up_y(data, 15);


	g_signal_connect(G_OBJECT(pSpinButtonX), "value-changed", G_CALLBACK(map_editor_change_size_x), data);
	g_signal_connect(G_OBJECT(pSpinButtonY), "value-changed", G_CALLBACK(map_editor_change_size_y), data);
	g_signal_connect(G_OBJECT(pButton), "clicked", G_CALLBACK(map_editor_change_size), data);

	vBox = gtk_vbox_new(FALSE, 0);
	gtk_box_set_homogeneous(GTK_BOX(vBox), FALSE);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pLabelTitle), FALSE, FALSE, 5);
	
		hBox = gtk_hbox_new(FALSE, 0);
			gtk_box_set_homogeneous(GTK_BOX(hBox), FALSE);
			gtk_box_pack_start(GTK_BOX(hBox), GTK_WIDGET(pLabelX), FALSE, FALSE, 5);
			gtk_box_pack_start(GTK_BOX(hBox), GTK_WIDGET(pSpinButtonX), TRUE, TRUE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(hBox), FALSE, FALSE, 0);
		hBox = gtk_hbox_new(FALSE, 0);
			gtk_box_set_homogeneous(GTK_BOX(hBox), FALSE);
			gtk_box_pack_start(GTK_BOX(hBox), GTK_WIDGET(pLabelY), FALSE, FALSE, 5);
			gtk_box_pack_start(GTK_BOX(hBox), GTK_WIDGET(pSpinButtonY), TRUE, TRUE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(hBox), FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pButton), FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pHSeparator), FALSE, FALSE, 5);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pSpinButtonY), FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(vBox), GTK_WIDGET(pScrollbar), GTK_EXPAND | GTK_FILL, GTK_EXPAND | GTK_FILL, 0);

	return vBox;
}

/*
static void spritelist_new(GtkListStore* pSpriteList, )
{

}
*/