//client
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define IP_PROTOCOL 0
#define IP_ADDRESS "127.0.0.1" // localhost
#define PORT_NO 15050
#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define sendrecvflag 0
 
// funtion to clear buffer
void clearBuf(char* b)
{
int i;
for (i = 0; i < NET_BUF_SIZE; i++)
b[i] = '\0';
}
 
 
 int ch=5;
// driver code
int main()
{
    char *mob;
    mob="7274068340";
    int sockfd, nBytes;
    struct sockaddr_in addr_con;
    int addrlen = sizeof(addr_con);
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    char user[NET_BUF_SIZE],pass[NET_BUF_SIZE],mess[NET_BUF_SIZE];
    
    // socket()
    sockfd = socket(AF_INET, SOCK_DGRAM,
    IP_PROTOCOL);
    
    if (sockfd < 0)
    printf("\nfile descriptor not received!!\n");
    else
    printf("\nfile descriptor %d received\n", sockfd);
    
    while(ch == 5) { 
    printf("\nPlease enter username and password:\n");
    scanf("%s%s", user,pass);
    sendto(sockfd, user, NET_BUF_SIZE,
                                        sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
    

    sendto(sockfd, pass, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
    
    printf("---------Username and Password sent---------\n");
    
    
    nBytes = recvfrom(sockfd, mess, NET_BUF_SIZE,
    sendrecvflag, (struct sockaddr*)&addr_con,
    &addrlen);
    
    
    printf("\n-----Reply from server------\n");
    printf("%s\n",mess);
    if(strcmp(mess, "Not Match") == 0) {
        return 0;
    } 

    ///-------------------------------------
    while(1) {

        printf("Enter choice in range [1,4]\n");
        printf("Enter choice 5 to login again\n");

        scanf("%d", &ch);
        sendto(sockfd, &ch, sizeof ch, 0, (struct sockaddr*)&addr_con, addrlen);
        if(ch >= 4) break;
        if(ch == 1){ 
            int amt;
            recvfrom(sockfd, &amt, sizeof amt, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
            printf("\nYour current balance is: %d\n", amt);
        }
        if(ch == 2)
        {
            mob = calloc(32, sizeof(mob[0]));
            memset(mob, 0, sizeof mob);
            recvfrom(sockfd, mob, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, &addrlen);
            printf("\n------Mobile number change Portal----\n");
            printf("Current Mobile No: %s\n", mob);
            printf("Please enter new Mobile no\n");	
            char new_mob[NET_BUF_SIZE];
            scanf("%s", new_mob);
            sendto(sockfd, new_mob, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
            
            printf("\nDone!");	
        }
        else if(ch == 3){
            printf("\n------PASSWORD change Portal----\n");
            printf("Please enter new PASSWORD\n");	
            char new_pass[NET_BUF_SIZE];
            scanf("%s", new_pass);
            sendto(sockfd, new_pass, NET_BUF_SIZE, sendrecvflag, (struct sockaddr*)&addr_con, addrlen);
            
            printf("\nDone!");
        }
        }

    }
    return 0;
}