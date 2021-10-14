#include<stdio.h>
#include<stdbool.h>
#define N 10005
int m,n,i;
int arr[N],sum[N];
void init();
int find(int x);
int main()
{
    init();
    bool flag=false;
    int day;
    for(i=1;i<m;i++)
    {
        int x1,x2;
        scanf("%d %d",&x1,&x2);    // 输入小朋友的交友情况
        int a1,a2;
        a1=find(x1),a2=find(x2);
        if(a1!=a2)
        {
            arr[a1]=arr[a2];
            sum[a2]+=sum[a1];
        }
        if(sum[a2]==n)    //此时已全部结交
        {
            flag=true,day=i;       
            for(;i<m;i++)
            {
                scanf("%d,%d",&x1,&x2);    //输入剩下的小朋友的交友
            }
            break;
        }
    }
    if(flag)
    printf("%d",day);
    else
    printf("-1");
    return 0;

}
void init() //创建初始数组
{
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    arr[i]=i,sum[i]=1;
}
int find(int x) //查找祖宗
{
    if(arr[x]!=x)
    arr[x]=find(arr[x]);
    return arr[x];   
}