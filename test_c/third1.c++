// #include<stdio.h>
// #include<math.h>
#include<iostream>
#include<math.h>
using namespace std;
#define mod 1000000007
int main()
{
    unsigned long int m,t,result,a,b,c,i;
    a=2;
    b=4;
    c=4;
    cin>>m;
    if(m==1)
    result=0;
    else if(m==2)
    result=0;
    else 
    {
    for(i=3;i<=m;i++)
    {
        t=(a+b)%mod;
        a=b%mod;
        b=t%mod;
        c=(2*c)%mod;
        if(c>t)
        result=(c-t)%mod;
        else
        result=(c+mod-t)%mod;
    }
    }
    cout<<result<<endl;
    return 0;
}