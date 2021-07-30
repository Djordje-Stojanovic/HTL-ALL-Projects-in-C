/*
Titel: Einfache Kompression von Strings
Beschreibung: Die Funktion *encode() "komprimiert" Strings,
indem sie Anzahl gleicher Zeichen in Serie durch das entsprechende
Zeichen, gefolgt von der Anzahl der Wiederholungen, ersetzt, z. B. 
wird der String "AAbBc" in "A2b1B1c1" umgewandelt.
Autor: Stojanovic Djordje
Datum der letzten Bearbeitung: 21.10.2020
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_RLEN 42

// -- Funktion *encode --
// Parameter: char *str ... zu komprimierender String
// Beschreibung: siehe oben
// Rueckgabewert: Adresse des komprimierten Strings
char *encode(char *str)
{
	char *result_strt = malloc(2*sizeof(str)); // Allozieren des maximal benoetigten Speicherplatzes
	char *result; 
	result = result_strt; 
	
	char *str_temp; // zum temporaeren Speichern der Adresse und des letzten gleichen Zeichens
	str_temp = str++; // Speichern der Startadresse auf str_temp

	for(; *str != '\0'; str++)
	{
		if(*str_temp != *str)
		{
			*result = *str_temp;
			sprintf(++result, "%i", (str-str_temp));
			result++;
			str_temp = str;
		}	
	}
	*result = *str_temp;
	sprintf(++result, "%i", (str-str_temp));

	return result_strt;
}

int main(int argc, char **argv)
{
	char str[MAX_RLEN];
      
       	do {	
		if (fgets(str, MAX_RLEN, stdin) == NULL) break;
		str[MAX_RLEN-1] = 0;    // TODO: is this really needed?
		str[strlen(str)-1] = 0; // TODO: why is this here?
		char* res = encode(str);
		printf(">%s\n", res);
		free(res);              // see: malloc
	} while (strlen(str) > 1);
}