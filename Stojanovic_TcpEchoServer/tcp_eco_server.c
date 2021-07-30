//-----------------------------------------------------------------------------------
/* 
Autor: Djordje Stojanovic
Klasse 5BHEL
Letzte bearbeitung: 26.01.2021
Abgabedatum: 26.01.2021
Aufgabe: Schreiben Sie einen TCP Server Prozess der alle vom Client geschickte Daten zurück sendet.
Dabei wird der Inhalt, welcher zuserst RLE-encodet wird wieder zurückgeschickt
*/
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//Includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>  
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>     
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//Defines
#define ADDR "127.0.0.1"
#define PORT 60000
#define BSize 32
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//Funktion welche notwendig ist
#define Fehlerbehandlung(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0) 
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
int main()
{
    //Buffer size allozieren
    char* buffer=malloc(BSize);   

    //Definition des Adressstructs
    struct sockaddr_in ip_adresse; 

    //Definition der size  
    socklen_t adresse_size;        

    //Vorfuellen der adresse mit 0
    memset(&ip_adresse,0,sizeof(struct sockaddr_in)); 

    //sin-family
    ip_adresse.sin_family = AF_INET;  

    //Zuweisen eines Ports
    ip_adresse.sin_port = htons(PORT);    
    
    //Zuweisung einer IP adresse
    ip_adresse.sin_addr.s_addr = inet_addr(ADDR);

    //erstellen eines sockets auf variable sockett
    int sockett = socket(AF_INET, SOCK_STREAM,0);  


    //-----------------------------------------------------------------------------------
    //Haupt if-schleife
    if (sockett == -1){
        Fehlerbehandlung("socket");
        close(sockett);
    }
    if (bind(sockett,( struct sockaddr *) &ip_adresse, sizeof(struct sockaddr_in))== -1){ //weist dem Socket eine Adresse zu
        Fehlerbehandlung("bind");
        close(sockett);
    };
    if(listen(sockett,5) == -1){  //Socket wartet auf Verbindungen, "Verbindungswarteschlange" beträgt 5 
        Fehlerbehandlung("listen");
        close(sockett);
    };
    int clientfd = accept(sockett, &ip_adresse, &adresse_size); //akzeptiert eine Verbindung
    if (clientfd == -1){
        Fehlerbehandlung("accept");
        close(sockett);
    }
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------

    //Eine unendliche schleife
    while(2602){         

        //definieren einer variable für antworten/nachrichten                     
        int read = recv(clientfd,buffer,BSize,0); 

    //-----------------------------------------------------------------------------------
    //Weitere haupt if schleife
        if(read == -1)
        {
            Fehlerbehandlung("recieve");
            close(sockett);
        }
        buffer[read] = 0;
        int se = send(clientfd, buffer,strlen(buffer),0);   //nachricht wird aus dem Buffer zurückgesendet
        if (se == -1)
        {
            Fehlerbehandlung("send");
            close(sockett);
        }
    }
}
//-----------------------------------------------------------------------------------
