#include <functions.h>
#include <math.h>


unsigned char strToHex(const char * s) 
{
	unsigned char result = 0;
	char c;
 	
 	if ('0' == *s && 'x' == *(s+1)) { 
      s+=2;
      while (*s){
         result = result << 4;
            if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
            else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
            else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
            else break;
		   	++s;
  		}
 	}

 	return result;
}

// Splits a string in an array of string in function of a separator
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

// Checks if the map is valid
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

unsigned char* map_read_file(const gchar* mapFile, int* sizeX, int* sizeY)
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

	unsigned char* map = malloc(sizeof(char)* (*sizeX) * (*sizeY) );

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

// Not fully fonctionnal; abandonned idea
void map_resize_var(struct data* data, int x, int y, int xn, int yn)
{
   int i, j;

   unsigned char mapSpritesNew[MAX_SIZE_TAB_X] = "";
   unsigned char mapSprites[MAX_SIZE_TAB_X] = ""; 

   for(int i=0; i<MAX_SIZE_TAB_X; i++)
      mapSprites[i] = data_get_map_sprites(data)[i];

   for(i=0; i<yn; i++)
   {
      for(j=0; j<xn; j++)
      {
         if(j<x && i<y)
            mapSpritesNew[CELL(j,i,xn)] = mapSprites[CELL(j,i,x)];
         else
            mapSpritesNew[CELL(j,i,xn)] = 0x00;

      }
   }

   data_set_x(data, xn);
   data_set_y(data, yn);

   data_set_map_sprites(data, mapSpritesNew);
}
