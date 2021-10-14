#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define mod 1000000007
int main(){
    // int a,b,c,i;
    // int n,t;
    int n,i;
    unsigned long int num,result,a,b,c,t;
    // unsigned long int result;
    a=0;
    b=0;
    c=1;
    scanf("%d",&n);
    if(n==1)
    result=a;   //输入为1时情况个数为0
    else if(n==2)
    result=b;    //输入为2时情况个数为0
    else if(n==3)
    result=2*c;    //输入为3时情况个数为2
    else{
        for(i=4;i<=n;i++)
    {   
        t=fmod(pow(2,(i-3)),mod);
        num=fmod(a%mod+b%mod+c%mod+t,mod);    //只考虑正面时的丑陋排列，递归数列为An=2**(n-3)+An-1+An-2+An-3
        a=b;
        b=c;
        c=num;
        // printf("%d %lu %lu %lu\n",i,a,b,c);
    }
    result=(2*num)%mod;   //由于正面和反面情况相同，所以最终结果为2*An
    }
    // printf("%lu\n",t);
    printf("%lu",result);
}    
