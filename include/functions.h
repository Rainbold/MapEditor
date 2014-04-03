#ifndef FUNCTION_H
#define FUNCTION_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define CELL(x,y,sizeX) (x +  sizeX * y)

unsigned int strToHex(const char * s);
char **str_split (char *s, const char *ct);
char* map_read_file(const gchar* mapFile, int* sizeX, int* sizeY);
int map_is_valid_file(const gchar* mapFile);

#endif