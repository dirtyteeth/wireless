#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<math.h>
#define PORT 8080
int main(int argc, char const *argv[]){
struct sockaddr_in address;
int sock = 0, valread;
struct sockaddr_in serv_addr;
if ((sock =socket(AF_INET, SOCK_STREAM, 0)) < 0){
printf("\n Socket creation error \n");
return -1;
}
memset(&serv_addr, '0', sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
printf("\nInvalid address \n");
return -1;
}
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
printf("\nConnection Failed \n");
return -1;
} 
int n1,n2, res;
float sol;
printf("Enter Two Number:\n");
scanf("%d",&n1);
scanf("%d",&n2);
send(sock , &n1 , sizeof(int) , 0 );
send(sock , &n2 , sizeof(int) , 0 );
valread = read( sock , &res, sizeof(int));
printf("Sum : %d\n",res);
valread = read( sock , &res, sizeof(int));
printf("Product : %d\n",res);
valread = read(sock, &res, sizeof(int));
printf("Minus : %d\n", res);
valread = read(sock, &sol, sizeof(float));
printf("Divide : %f", sol);
return 0;
}
