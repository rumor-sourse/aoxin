#include<stdio.h>
#include<stdlib.h>
#define max(a,b)  a>b?a:b
#define M 200005
int main(){
    int m,lay,cream,i,t;
	int arr[M];
	scanf("%d",&m);   //输入一共进行m次测试用例
	t=m-1;
	while(m--){
		if(m!=t)  printf("\n");
		scanf("%d",&lay);    //输入一共几层蛋糕
		for(i=1;i<=lay;i++) arr[i]=0;      //数组初始化
		for(i=1;i<=lay;i++){
			scanf("%d",&cream);
			if(cream){
				arr[max(1,i-cream+1)]++;  
				arr[i+1]--;      //差分的利用
			}
		}
		for(i=1;i<=lay;i++)
            arr[i]=arr[i]+arr[i-1];  //求前缀和
		i=1;
		if(lay==1)
		printf("%d",arr[i]!=0);
		else 
		{
		for(;;)
		{
		 	printf("%d ",arr[i]!=0);   //arr[i]!=0成立时输出1，不成立时输出0
			i++;
			if(i==lay)
			{
				printf("%d",arr[i]!=0);
				break;
			}
		}
		}
	}
	return 0;
} 

