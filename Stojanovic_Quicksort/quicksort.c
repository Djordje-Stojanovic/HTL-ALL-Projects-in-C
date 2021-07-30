/*
Author: Dorde Stojanovic
Class: 5BHEL
Abgabe: 25.01.2021
Programm: rekursiver Quicksort Algorytmus
Github-Respo: https://github.com/Djordje-Stojanovic/FSST/tree/main/Stojanovic_Quicksort
*/

//-------------------------------------------------------------
//Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//-------------------------------------------------------------


//-------------------------------------------------------------
//Initialisierien der funktionen
void zahlen_austauschen(int *x,int *y);
int pivot_suchen(int i,int j );
void quicksort_ausfuehren(int list[],int m,int n);
void ausgabe_ausfuehren(int list[],const int n);
//-------------------------------------------------------------


//-------------------------------------------------------------
//Grundeinstellungen welche hier verändert werden können
#define maxzahl 10000
#define anzahlelemente 10000000
//-------------------------------------------------------------
 

//-------------------------------------------------------------
//Main Funktion
void main()
{   
    //start der Zeitmessung
    clock_t anfang = clock();
    
    //erstellung des arrays
    const int groese = anzahlelemente;
    int list[groese];
 
    //random zahlen generieren und den array befüllen
    for(int i = 0; i < groese; i++ )
        list[i] = rand() % maxzahl;

    //erste ausgabe des befüllten arrays
    printf("\n\nVor quicksort sieht der array so aus:\n");
    ausgabe_ausfuehren(list,groese);
 
    //sortieren der liste mittels quicksort
    quicksort_ausfuehren(list,0,groese-1);
 
    //Ausgabe des sortierten Arrays
    printf("\n\nNach quicksort sieht der array so aus:\n");
    ausgabe_ausfuehren(list,groese);
    
    //Ende der Zeitmessung und deren Ausgabe
    clock_t ende = clock();
    float time_spent = (double)(ende - anfang) / CLOCKS_PER_SEC;
    printf("\n\nDie Zeit ist: %f Sekunden\n", time_spent);
}
//-------------------------------------------------------------


//-------------------------------------------------------------
//Funktion zuständig für den Zahlentausch von Quicksort
void zahlen_austauschen(int *x,int *y)
{
    int platzhalter;
    platzhalter = *x;
    *x = *y;
    *y = platzhalter;
}
//-------------------------------------------------------------


//-------------------------------------------------------------
//Funktion zuständig für das "suchen" bzw finden des Pivotelementen
int pivot_suchen(int i,int j )
{
    return((i+j) /2);
}
//-------------------------------------------------------------


//-------------------------------------------------------------
//Der eigentliche Quicksort algorythmus
void quicksort_ausfuehren(int list[],int m,int n)
{
    //defintion von variabeln für den algorythmus
    int h,i,j,k;
    
    //der hauptalgorythmus
    if( m < n)
    {
        //Pivot wird ausgesucht
        k = pivot_suchen(m,n);
        
        //zahlen werden ausgetauscht
        zahlen_austauschen(&list[m],&list[k]);
        h = list[m];
        i = m+1;
        j = n;
        
        //Die while schleife um die einzelnen partionen zu sorieren
        while(i <= j)
        {
            while((i <= n) && (list[i] <= h))
                i++;
            while((j >= m) && (list[j] > h))
                j--;
            if( i < j)
                zahlen_austauschen(&list[i],&list[j]);
        }
        zahlen_austauschen(&list[m],&list[j]);
 
        //die kleinere liste rekursiv sortieren
        quicksort_ausfuehren(list,m,j-1);
        quicksort_ausfuehren(list,j+1,n);
    }
}
//-------------------------------------------------------------


//-------------------------------------------------------------
//Die Ausgabefunktion für den Array
void ausgabe_ausfuehren(int list[],const int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%d\t",list[i]);
}
//-------------------------------------------------------------
