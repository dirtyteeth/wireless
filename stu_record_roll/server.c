#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
struct db{
int r;
char name[30];
};
#define N 5
#define PORT 8080
int main(int argc, char const *argv[])
{     
    struct db record[N];
    int i=0;
    char end;
    printf("Enter records to database\n");
    for(i=0;i<N;i++){
       printf("roll no:");
       scanf("%d",&record[i].r);
       printf("name:");
       scanf("%s",record[i].name);
      }
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
       
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
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
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

       int msg,status=1;
       read( new_socket , &msg, sizeof(msg));
       int roll_no =ntohl(msg);
       printf("Request for details of roll No %d",roll_no);
       char rec[30]="No records found";
       for( i=0;i<N;i++)
       {
           if(record[i].r==roll_no)
           {
                send(new_socket , record[i].name , strlen(record[i].name ) , 0 );
                printf("Details of roll No %d sent",roll_no);
                status=0;
                break;
           }
       }
    
       if(status==1){
       	send(new_socket , rec , strlen(rec) , 0 );
       	printf("Staus sent: No records found");
       }
    }
} 
