#include<stdio.h>
#define N 20005
#define max(a,b) a>b?a:b
int main()
{
    int t;
    int a[N];
    int f[N];
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<=n+1;i++) f[i]=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]>0)
            {
                int st=i-a[i]+1;
                st=max(st,1);
                f[st]++;
                f[i+1]--;
            }
        }
        for(int i=1;i<=n;i++)
        {
            f[i]=f[i-1]+f[i];
            if(f[i]>=1) printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    //system("pause");
    return 0;
}
