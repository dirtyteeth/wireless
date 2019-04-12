#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char pat[20];
    char dept[20];
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    memset(&serv_addr, '0', sizeof(serv_addr));
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("connection created!\n");


    while(1)
    {
      printf("PATIENT NAME    :");
      scanf("%s",pat);
      send(sock , pat, 20 , 0);
      printf("DEPARTEMENT NAME:");
      scanf("%s",dept);
      send(sock , dept , 20 , 0);
      read( sock, buffer, 1024);
      printf("Message : %s\n",buffer);
      int i=0;
      for(i=0;i<1024;i++)
      {
         buffer[i]='\0';
      }
    }
}
