//server
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define IP_PROTOCOL 0
#define PORT_NO 15050
#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0
#define nofile "File Not Found!"
void clearBuf(char* b)
{
int i;
for (i = 0; i < NET_BUF_SIZE; i++)
b[i] = '\0';
}
int curr_bal = 10000;
int main()
{
int sockfd, nBytes;
struct sockaddr_in addr_con;
int addrlen = sizeof(addr_con);
addr_con.sin_family = AF_INET;
addr_con.sin_port = htons(PORT_NO);
addr_con.sin_addr.s_addr = INADDR_ANY;
char user[NET_BUF_SIZE],pass[NET_BUF_SIZE],mess[NET_BUF_SIZE];
char *data_user, *data_pass,*mob;
data_user="avkumar_19";
data_pass="avinash123";
mob="7274068340";
 // socket()
sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);
 if (sockfd < 0)
printf("\nfile descriptor not received!!\n");
else
printf("\nfile descriptor %d received\n", sockfd);
 // bind()
if (bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con)) == 0)
printf("\nSuccessfully binded!\n");
else
printf("\nBinding Failed!\n");
 int ch = 5;
while(ch == 5) 
{
	printf("\nWaiting for Usename and password...\n");
	 
	 
	nBytes = recvfrom(sockfd, user, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
	nBytes = recvfrom(sockfd, pass, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
	printf("Received password: %s\n",pass);

	printf("\nUsername and password Name Received:\n");
	 
	if(strcmp(user,data_user)==0 && strcmp(pass,data_pass)==0)
	{
	strcpy(mess,"Valid-User");
	}
	else
	{
	strcpy(mess,"Not Match");
	sendto(sockfd, mess, NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con, addrlen);
	return 0;
	}
	sendto(sockfd, mess, NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con, addrlen);
	printf("-----Message-Sent-------\n");
// Accept Choice
	while(1)
	{

	recvfrom(sockfd, &ch, sizeof ch, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
	if(ch >= 4) break;
	if(ch == 1){
		//printf("Successfully receieved: %d\n", ch);
		sendto(sockfd, &curr_bal, sizeof curr_bal, 0, (struct sockaddr*)&addr_con, addrlen);
	}
	else if(ch==2)
	{
		sendto(sockfd, mob, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
		mob = calloc(32, sizeof(mob[0]));
		memset(mob, 0, sizeof mob);
		recvfrom(sockfd, mob, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
		printf("Successfully Done. New Mobile No: %s\n", mob);	
	}
		else if(ch == 3) {
			data_pass = calloc(32, sizeof(data_pass[0]));
			memset(data_pass, 0, sizeof data_pass);
			recvfrom(sockfd, data_pass, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
			printf("Successfully Done. New password: %s\n", data_pass);
		}
	}

}
    return 0;
}
