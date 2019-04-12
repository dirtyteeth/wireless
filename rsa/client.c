#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int power(int x, unsigned int y, int p)
{
    int res = 1;      
  
    x = x % p;  
  
    while (y > 0)
    {
        
        if (y & 1)
            res = (res*x) % p;
  
       
        y = y>>1; 
        x = (x*x) % p;  
    }
    return res;
}
int modinv(int a, int m)
{
    a = a%m;
    int x;
    for (x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
}  
char* encrypt(char *text)
{ 
    int p=3;
    int q=7;
    int phi=(p-1)*(q-1);
    int n=p*q;
    int e=5;
    int d=modinv(e,phi);
    int i,t;
    for(i=0;i<strlen(text);i++)
    {
       t=text[i]-'A';
       t=power(t,e,n);
       text[i]=(char) t+'A';
    }
   printf("%s \n",text);
   return text;
}
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char username[20];
    char password[20];
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
      printf("USERNAME:");
      scanf("%s",username);
      send(sock , username, 20 , 0);
      printf("PASSWORD:");
      scanf("%s",password);
      send(sock , encrypt(password) , 20 , 0);
      read( sock, buffer, 1024);
      printf("Message : %s\n",buffer);
    }
}
