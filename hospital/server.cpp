#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<time.h>
#include<bits/stdc++.h>
#define N 3
#define PORT 8080
using namespace std;
struct db{
  string dept;
  string doctor;
  int avb;
  time_t begin;
};
struct Q{
  queue<string> pat;
};

int front,rear;
int main(int argc, char const *argv[])
{     
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1,i,j;
    int addrlen = sizeof(address);
    char  p[20]={0};
    char  d[20]={0};
    string pati,dept;

///////////////////////   DATA  //////////////////////////////////////

    struct db auth_table[N];
    for(i=0;i<N;i++){
      auth_table[i].begin=time(NULL);
      auth_table[i].avb=1;
    }
    auth_table[0].dept="DEPTA";
    auth_table[0].doctor="DOCA";
    auth_table[1].dept="DEPTB";
    auth_table[1].doctor="DOCB";
    auth_table[2].dept="DEPTC";
    auth_table[2].doctor="DOCC";
  
/////////////////////////////////////////////////////////////

    struct Q queue_table[N];

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
    time_t end;
    
    while(1)
    {   
        read( new_socket, p, 20);
        pati=p;
        cout<<"PATIENT NAME   :"<<pati<<endl;
        read( new_socket, d, 20);
        dept=d;
        cout<<"DEPARTMENT  NAME:"<<dept<<endl;
        int status=0,flag=0,index;

       // 0-dept not exist
       // 1-doctor assigned
       // 2-doctor not available
       //

    

        // processing wait list first

        for(i=0;i<N;i++)
        {
          end=time(NULL);
          if(difftime(end,auth_table[i].begin)>=40){
              auth_table[i].avb=1;
              if(!queue_table[i].pat.empty() )
              {  
                auth_table[i].avb=0;
                auth_table[i].begin=time(NULL);
                cout<<queue_table[i].pat.front()<<" has assigned doctor "<<auth_table[i].doctor<<" in department"<<auth_table[i].dept<<endl;
              }
            }
        }


        for(i=0;i<N;i++)
        {
              end=time(NULL);
              if(difftime(end,auth_table[i].begin)>=40){
                   auth_table[i].avb=1;
              }
              if(auth_table[i].dept==dept)
               {   flag=1;
                   index=i;
                  if(auth_table[i].avb==1)
                  { 
                     auth_table[i].avb=0;
                     auth_table[i].begin=time(NULL);
                     status=1;
                     break;
                  }
               }
        }

        if(flag==1 && status==0)
            status=2;
        if(status==1)  
         send(new_socket ,auth_table[index].doctor.c_str(), auth_table[index].doctor.length() , 0 );
        else if(status==0)
          send(new_socket ,"Invalid Department", strlen("Invalid Department") , 0 );
        else{
                send(new_socket ,"Doctor Not Available", strlen("Doctor Not Available") , 0 );
                queue_table[index].pat.push(pati);
                cout<<pati<<" is waiting  for department "<< auth_table[index].dept<<endl;
        }
    }
}

