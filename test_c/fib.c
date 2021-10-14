#include<stdio.h>
#include<math.h>
#define mod 1000000007
int main()
{
    unsigned long int m,result;
    scanf("%lu",&m);
    result=(unsigned long int)fmod(pow(2,m),mod);
    printf("%lu",result);
    return 0;
}