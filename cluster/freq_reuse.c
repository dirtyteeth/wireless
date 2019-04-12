
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define limit 6

int is_valid_cluster(int n,int s)
{  
    if(n<3)
      return 0;
    int t=0,i,j;
    for(i=1;i<limit;i++)
    {
        for(j=1;j<limit;j++)
        {
             t=i*i+j*j+i*j;
             if(t==n)
              {
                 if(s==1)
                   printf("i: %d ,j: %d\n",i,j);
                 return 1;
              }  
        }
    }
    return 0;
}

float find_cluster(float n,float si,float co)
{
   float antilogsi=pow(10.0,si/10);
   float p=2/n;
   float pro=antilogsi*co;
   float N=pow(pro,p)/3;
   return ceil(N);
}


int main(){
 float n,si,co;
 printf("Enter No of co-channel:");
 scanf("%f",&co);
 printf("Enter path loss factor:");
 scanf("%f",&n);
 printf("Enter Signal to Interference Ratio:");
 scanf("%f",&si);

 int N=find_cluster(n,si,co);
 int x=limit*limit*3;
 while(!is_valid_cluster(N,0) && N< x)
 {
      N++;
 }
 float res=1.0/N;
 printf("Frequency Reuse Factor:%f(%d)\n",res,N);
}
