#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define N 3
#define PORT 8080
struct db{
char *pswd;
char *usnm;
};
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
char* decrypt(char *text)
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
       t=power(t,d,n);
       text[i]=(char) t+'A';
    }
   //printf("Decrypted PASSWORD  : %s\n",text);
   return text;
}
int main(int argc, char const *argv[])
{     
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1,i;
    int addrlen = sizeof(address);
    char username[20]={0};
    char password[20]={0};

///////////////////////   DATA  //////////////////////////////////////

    struct db auth_table[N];
    for(i=0;i<N;i++){
      auth_table[i].pswd=(char *)malloc(20*sizeof(char));
      auth_table[i].usnm=(char *)malloc(20*sizeof(char));
    }
    auth_table[0].pswd="RSACHAMP";
    auth_table[0].usnm="USENAMERSA";
    auth_table[1].pswd="CRYPTOCHAMP";
    auth_table[1].usnm="USENAMECRYPTO";
    auth_table[2].pswd="GREATINDIA";
    auth_table[2].usnm="USENAMINDIA";
  
/////////////////////////////////////////////////////////////


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
        
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    while(1)
    {   
        read( new_socket, username, 20);
        printf("USERNAME RECEIVED : %s\n",username);
        read( new_socket, password, 20);
        printf("PASSWORD RECEIVED : %s\n",password);
        decrypt(password);
        printf("Decrypted PASSWORD  :%s\n",password);
        int status=-1;
        for(i=0;i<N;i++)
        {
              if(strcmp(auth_table[i].usnm,username)==0)
               {
                  if(strcmp(auth_table[i].pswd,password)==0)
                   status=0;
                  else
                    status=1;
                    break;
               }
        }
        switch(status)
        {
           case 0: send(new_socket ,"Successful", strlen("Successful") , 0 );
           break;
           case -1: send(new_socket ,"Invalid Username", strlen("Invalid username") , 0 );
           break;
           case 1: send(new_socket ,"Invalid Password", strlen("Invalid Password") , 0 );
        }
    }
}
