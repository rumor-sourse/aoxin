#include<stdio.h>
#include<stdlib.h>
#define T 10000  //取值范围

// void init();
void merge(int u,int v);
int get_r(int v);
int check();
int N;
int f[T];
int main(){
    int M;
    int i,t,a,b;
    scanf("%d %d",&N,&M);
    int flag[M];
    for(i=1;i<N;i++)
    {
        f[i]=i;      //初始化数组f[]
    }
    for(i=1;i<=M;i++)
    {
        scanf("%d %d",&a,&b);
        merge(a,b);
        if(check()==-1)
        flag[i]=0;     //遍历后若存在根节点不同的情况，则该次遍历记为0
        else 
        flag[i]=1;     //遍历所有根节点若相同，则该次遍历记为1
    }
    // for(i=1;i<=M;i++)
    // {
    //     printf("%d",flag[i]);    //输出所有搜索次数后的flag数组
    // }
    // printf("\n");
    for(t=1;t<=M;t++)
    {
        if(flag[t]==1)
        {
            printf("%d",t);     //输出flag数组里第一个1
            return 0;
        }
        
    }
    printf("-1");
    return 0;
}

//将某个数连接到其父节点上
void merge(int u,int v)
{
    if(u>v)
        f[u]=v;
    else
        f[v]=u;
}
//利用递归求出v的根节点
int get_r(int v)
{
    if(f[v]==v)
        return v;
    else
        return get_r(f[v]);   
}
//遍历检查是否根节点相同
int check(){
    int p,m;
    for(m=2;m<=N;m++)
    {
        p=get_r(1);
        if(get_r(m)!=p)
        {
            return -1;
        }
    }
    return 1;

}