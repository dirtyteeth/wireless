#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int capacity(int i,int j,int n,int N)
{
     int c_size=i*i+j*j+i*j;
     return c_size*n*N;
}

int main(){
 int i,j,n,N;
 printf("Enter i & j:");
 scanf("%d%d",&i,&j);
 printf("Enter no of channel allocated to each cell:");
 scanf("%d",&n);
 printf("Enter No of cluster:");
 scanf("%d",&N);
 int cap=capacity(i,j,n,N);
 printf("Capacity of system:%d\n",cap);
}
