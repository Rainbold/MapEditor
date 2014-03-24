#include <spriteslist.h>

enum {
	IMG_COLUMN = 0,
	TEXT_COLUMN,
	N_COLUMN
};

#define MAX_SIZE 1000

char **str_split (char *s, const char *ct)
{
   char **tab = NULL;

   if (s != NULL && ct != NULL)
   {
      int i;
      char *cs = NULL;
      size_t size = 1;

      for (i = 0; (cs = (char*)strtok (s, ct)); i++)
      {
         if (size <= i + 1)
         {
            void *tmp = NULL;

            size <<= 1;
            tmp = realloc (tab, sizeof (*tab) * size);
            if (tmp != NULL)
            {
               tab = tmp;
            }
            else
            {
               fprintf (stderr, "Insufficient memory\n");
               free (tab);
               tab = NULL;
               exit (EXIT_FAILURE);
            }
         }
         tab[i] = cs;
         s = NULL;
      }
      tab[i] = NULL;
   }
   return tab;
}

GtkWidget* spriteslist_new()
{
	GtkWidget* pListView = NULL;
	GtkTreeViewColumn* pColumn = NULL;
	GtkListStore* pSpriteList = NULL;
	GtkCellRenderer* pCellRenderer = NULL;
	GtkTreeIter pIter;
	GtkWidget* pScrollbar = NULL;
	gchar* sText = NULL;

	GtkWidget* pImage = NULL;
	GdkPixbuf* pPixBuf = NULL;

	sText = g_malloc(100);
	sprintf(sText, "Test");

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

	/*
		gtk_list_store_append(pSpriteList, &pIter);
		gtk_list_store_set(pSpriteList, &pIter, IMG_COLUMN, pPixBuf, TEXT_COLUMN, sText, -1);
		gtk_list_store_append(pSpriteList, &pIter);
		gtk_list_store_set(pSpriteList, &pIter, IMG_COLUMN, pPixBuf, TEXT_COLUMN, sText, -1);
		gtk_list_store_append(pSpriteList, &pIter);
		gtk_list_store_set(pSpriteList, &pIter, IMG_COLUMN, pPixBuf, TEXT_COLUMN, sText, -1);*/

	g_free(sText);

	// Création de la vue
	pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(pSpriteList));

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

	return pScrollbar;
}

/*
static void spritelist_new(GtkListStore* pSpriteList, )
{

}
*/