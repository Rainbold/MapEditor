#include <functions.h>
#include <math.h>


unsigned char strToHex(const char * s) 
{
	unsigned char result = 0;
	char c;
   char* sOr = s;
   int i=2;
 	
 	if ('0' == *s && 'x' == *(s+1)) { 
      printf("%s\n", s);
      s+=2;
      while (*s && i<=4){
         result = result << 4;
            if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
            else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
            else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
            else break;
            printf("%d %c\n", c, *s);
		   	++s;
            i++;
  		}
 	}

 	return result;
}

char **str_split (char *s, const char *ct)
{
   char **tab = NULL;

   if (s != NULL && ct != NULL)
   {
      unsigned int i;
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

int map_is_valid_file(const gchar* mapFile)
{
   FILE* f = NULL;
   unsigned char byte = 0;

   f = fopen(mapFile, "rb");

   if(!f) 
      return 0;

   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x6c )
      return 0;
   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x76 )
      return 0;
   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x6c )
      return 0;

   fclose(f);

   return 1;
}

char* map_read_file(const gchar* mapFile, int* sizeX, int* sizeY)
{
   FILE* f = NULL;
   unsigned char byte = 0;

   int i;
   int j;

   f = fopen(mapFile, "rb");

   if(!f) 
      exit(1);

   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x6c )
      exit(1);
   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x76 )
      exit(1);
   if( fread(&byte, 1, sizeof(byte), f) == 0 || byte != 0x6c )
      exit(1);

	if( fread(&byte, 1, sizeof(byte), f) == 0 )
	  	exit(1);
	*sizeX = byte;

	if( fread(&byte, 1, sizeof(byte), f) == 0 )
	  	exit(1);
	*sizeY = byte;

	char* map = malloc(sizeof(char)* (*sizeX) * (*sizeY) );

	for(i=0; i<*sizeY; i++) {
	  	for(j=0; j<*sizeX; j++) {
	     	if( fread(&byte, 1, sizeof(byte), f) == 0 )
	        	exit(1);
	     	map[CELL(j,i,*sizeX)] = byte;
	  	}
	}

   fclose(f);

	return map;
}

void map_resize_var(struct data* data, int x, int y, int xn, int yn)
{
   int i, j;

   unsigned char mapSpritesNew[MAX_SIZE_TAB_X] = "";
   unsigned char mapSprites[MAX_SIZE_TAB_X] = ""; 
   // for(int i=0; i<MAX_SIZE_TAB_X; i++)
   //    printf("%02x ", data_get_map_sprites(data)[i]);
   for(i=0; i<x; i++)
   {
      for(j=0; j<y; j++)
      {
         printf("%02x ", data_get_map_sprites(data)[CELL(i,j,x)]);
      }
      printf("\n");
   }
   for(int i=0; i<MAX_SIZE_TAB_X; i++)
      mapSprites[i] = data_get_map_sprites(data)[i];

      printf("\n");
      printf("%d %d %d %d\n", x, y, xn, yn);

   for(i=0; i<yn; i++)
   {
      for(j=0; j<xn; j++)
      {
         if(j<x && i<y)
            mapSpritesNew[CELL(j,i,xn)] = mapSprites[CELL(j,i,x)];
         else
            mapSpritesNew[CELL(j,i,xn)] = 0x00;

         printf("%02x ", mapSpritesNew[CELL(j,i,xn)]);
      }
      printf("\n");
   }

   data_set_x(data, xn);
   data_set_y(data, yn);

   data_set_map_sprites(data, mapSpritesNew);
   // for(int i=0; i<MAX_SIZE_TAB_X; i++)
   //    printf("%02x ", data_get_map_sprites(data)[i]);
}
