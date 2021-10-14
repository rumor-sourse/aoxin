#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 10050  //字符数组的范围
int main()
{   
    int count=1,sum=0;   //count用于计连续相同的字符的个数，sum用于计字符总个数
    int m=0,pos=0;
    int ch; //p指针用于遍历字符串数组
    int s=0,p; 
    char arr1[M],arr2[M];
    const char list[10]={'0','1','2','3','4','5','6','7','8','9'};
    //输入字符数组
    while((ch=getchar())!='\n')
    {
        arr1[m]=ch;
        m++;
    }   
    for(p=0;p<=m;)
    {
        if(arr1[p]==arr1[p+1])
        {   
            count++;
            p++;
        }
        else
        {
            sum+=count;
            arr2[s]=arr1[p];
            s++;
            pos++;           
            if(count!=1)
            {       
                int dig=0;
                int j;
                for(j=count;j>0;j/=10)
                    dig++;
                pos+=dig;
                for(j=1;j<=dig;j++){
                    arr2[pos-j]=list[count%10];
                    count/=10;
                    s++;
                }
            }
            p++;
            count=1;
        }
    }
        for(s=0;arr2[s]!='\0';s++)
    {
       printf("%c",arr2[s]);    
    }
    printf("\n%d\n",pos); 
}