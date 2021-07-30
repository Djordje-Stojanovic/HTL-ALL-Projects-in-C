#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdbool.h>

#define BUF_SIZE 20 
// Definition der Groesse des Buffers in Byte

/*
Author: Dorde Stojanovic
Class: 5BHEL
Startdatum: 27.12.2020
Abgabe: 28.12.2020
Programm: Das Programm soll eine Datei kopieren mittels der Funktion "file_copy" 
            Es wird hierbei ein 20-Byte-Buffer verwendet und auch einige POSIX-Systemcalls
            wie open, read, write und close
Github-Respo: https://github.com/Djordje-Stojanovic/FSST/tree/main/Stojanovic_FileCopy
*/

//__________________________________________________________________
int file_copy(const char *filename, const char *newfilename, bool err_message_en)
{
	int handle_date; 
	// ist ein handle fuer die zu kopierende Datei
	int handle_copy; 
	// ist ein handle fuer die Kopie
	void *buf; 
	// ist der Buffer fuer gelesene Daten
	int n_read; 
	// gibt die Anzahl der gelesenen Bytes an

	handle_date = open(filename, O_RDONLY);
	// O_RDONLY bedeutet es soll nur geöffnet werden zum lesen
	
	if(handle_date == -1)
	{
		if(err_message_en == true) puts("Es ist ein Fehler beim Oeffnen der zu kopierenden Datei aufgetreten");
		return -1;
	}
	handle_copy = open(newfilename, O_CREAT | O_EXCL | O_WRONLY, S_IRWXU); 
	// O_CREAT erstellt die Datei
	// O_EXCL gibt einen Fehler wenn datei schon existiert
	// O_WRONLY oeffnet nur zum schreiben; 
	// S_IRWXU gibt dem Eigentümer lese und schreibrechte

//__________________________________________________________________
	if(handle_copy == -1) 
	{
		close(handle_date);
		if(err_message_en == true) puts("Est ist ein Fehler beim Oeffnen/Erstellen der Kopie aufgetreten");
		return -2;
	}
	// dieser Teil ist wiederrum nur für die Fehlerüberprüfung
	//__________________________________________________________________
	
	for(n_read = 20; n_read >= 20;)
	// Wenn n_read kleiner als 20 => Eend of File ist erreicht
	{
		n_read = read(handle_date, buf, BUF_SIZE); 
		// Daten werden in buf eingelesen in diesem Fall
		//__________________________________________________________________
		
		if(n_read == -1)  
		{
			close(handle_date);
			close(handle_copy);
			if(err_message_en == true) puts("Es ist ein Fehler beim Lesen der zu kopierenden Datei aufgetreten");
			return -3;
		}
		//dieser Teil war wieder nur die Fehlerpruefung
		//__________________________________________________________________
		
		if (write(handle_copy, buf, n_read) == -1)  
		{
			close(handle_date);
			close(handle_copy);
			if(err_message_en == true) puts("Es ist ein Fehler beim Schreiben in die Kopie aufgetreten");
		 	return -4;
		}
		//hier wird datei geschrieben und nochmal die Fehlerpruefung gemacht
        //__________________________________________________________________
	}
	close(handle_date);
	close(handle_copy);
	return 0;
}
//__________________________________________________________________

//__________________________________________________________________
void clr_str(char *string)
{
	for(int i = 0; ;i++)
	{
		if(string[i] == '\n')
		{
			string[i] = '\0';
			break;
		}
	}
}
// *String ist hier der string der gecleart/gesaeubert werden werden muss
//  die funktion ist nur da um das \n mit \0 zu ersetzen weil durch den 
//  Enter bei der Eingabe ein \n entsteht
//  Funktion hat hier keinen Rueckgabewert
//__________________________________________________________________


//__________________________________________________________________
int main()
{
	char filename[BUF_SIZE+1]; 
	// 20 Zeichen + \0
	
	char newfilename[BUF_SIZE+1]; 
	// 20 Zeichen + \0

	puts("Bitte hier den Namen der zu kopierenden Datei eingeben:");
	
	fgets(filename, BUF_SIZE, stdin);
	
	clr_str(filename); 
	// um \n durch \0 zu ersetzen
	
	puts("\nBitte hier den Namen der neuen Datei eigeben:");
	
	fgets(newfilename, BUF_SIZE, stdin);
	
	clr_str(newfilename); 
	// um \n durch \0 zu ersetzen

	return file_copy(filename, newfilename, true);
}
//__________________________________________________________________

