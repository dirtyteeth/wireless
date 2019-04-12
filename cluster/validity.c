#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define limit 6
int is_valid_cluster(int n){ 
     if(n<3)
        return 0;
    int t=0,i,j;
    for(i=1;i<limit;i++) {
          for(j=1;j<limit;j++) {
             t=i*i+j*j+i*j;
             if(t==n) {
             printf("i: %d ,j: %d\n",i,j);
             return 1;
      } } }
    return 0;
}
int main(){
  int n;
  printf("Enter cluster size to check:");
   scanf("%d",&n);
  int flag=is_valid_cluster(n);
  if(flag)
    printf("valid cluster size\n");
   else
    printf("Invalid cluster size\n");
}
