#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<math.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define PORT 8080
int main(int argc, char const *argv[]){
struct sockaddr_in address;
int sock = 0, valread;
struct sockaddr_in serv_addr;
char bufer[2256] = {0};
if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
printf("\n Socket creation error \n");
return -1;
}
memset(&serv_addr, '0', sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
printf("\nInvalid address \n");
return -1;
} if (
connect(sock, (
struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
0){
printf("\nConnection Failed \n");
return -1;
}
while(true){
string ques;
cout<<"Enter The Question (all lowercase) (or) 0 to exit ?\n Q : ";
getline(cin, ques);
send(sock, ques.data(), ques.size(), 0);
if(ques == "0") break;
int len = recv(sock, bufer, sizeof(bufer), 0);
string res;
res.append(bufer, bufer + len);
cout<<" A : "<<res<<endl;
}
return 0;
}
