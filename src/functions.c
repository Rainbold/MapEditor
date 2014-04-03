#include <functions.h>

unsigned int strToHex(const char * s) 
{
	unsigned int result = 0;
	int c;
 	
 	if ('0' == *s && 'x' == *(s+1)) { 
 		s+=2;
  		while (*s) {
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