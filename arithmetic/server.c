#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<math.h>
#define PORT 8080
int main(int argc, char const *argv[]){
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
perror("socket failed");
exit(EXIT_FAILURE);
}
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR |
SO_REUSEPORT,&opt, sizeof(opt))){
perror("setsockopt");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons( PORT );
if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0){
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0){
perror("listen");
exit(EXIT_FAILURE);
} if ((new_socket =
accept(server_fd, (
struct sockaddr *)&address,
(socklen_t*)&addrlen))<0){
perror("accept");
exit(EXIT_FAILURE);
} int n1,n2,sum,prod, minus; 
float divide;
valread = read( new_socket , &n1 , sizeof(int));
valread = read( new_socket , &n2 , sizeof(int));
printf("TWO NUMBER RECEIVED: %d %d\n",n1,n2 );
sum = n1 + n2;
prod = n1 * n2;
minus = n1 - n2;
divide = (float)n1 / n2;
send(new_socket , &sum , sizeof(int) , 0 );
send(new_socket , &prod , sizeof(int) , 0 );
send(new_socket , &minus , sizeof(int) , 0 );
send(new_socket , &divide , sizeof(float) , 0 );
return 0;
}
