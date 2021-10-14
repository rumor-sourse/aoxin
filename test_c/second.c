#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 10000  //字符数组的范围
#define N 5      //count_array数组的范围
int count_arr[N];   //设置全局变量count_array数组
void init_count_array(int u);
int main()
{   
    int count=1,sum=0;   //count用于计连续相同的字符的个数，sum用于计字符总个数
    int i,m=0;
    char *p,ch; //p指针用于遍历字符串数组
    char *s; //s指针用于修改字符串数组，永远指向需要修改的那一位
    char arr[M];
    //输入字符数组
    while((ch=getchar())!='\n')
    {
        arr[m]=ch;
        m++;
    }
    arr[m+1]='\0';
    p=&arr[0];    //p指针初始化
    s=&arr[0];    //s指针初始化
    while((*p)!='\0')
    {
        if(*p == *(p+1))
        {   
            count++;
            p++;
        }
        else
        {
            // printf("%d",count);   //检查count是否正确
            sum+=count;
            (*s)=(*p);           
            if(count!=1)
            {       
                init_count_array(count);   //用数组count_array保存数字count
                // for(i=0;i<N;i++)
                // {
                //     printf("%d",count_arr[i]);  
                // }
                for(i=0;i<N;i++)
                {
                     if(count_arr[i]!=0)
                     {
                        s++;
                        (*s)=(char)(count_arr[i]+48);      //将输入数组进行修改，将int类型转换为char类型，每一位在数组中都有它的位置                                  
                     }                    
                }
            }
            p++;
            count=1;
            s++;
        }
    }
    for(;(*s)!='\0';s++)
    {
        (*s)='\0';      //将修改后的数组后面多余的全部删去
    }
    for(p=&arr[0];(*p)!='\0';p++)
    {
       printf("%c",*p);    //检查输入数组是否被修改正确
    }
    printf("\n%d\n",sum);    //输出sum

    
    
}
//将count转换为count_array数组的函数
void init_count_array(int u)
{
    int a,b,c,d,e;
    a=u%10;
    b=((u-a)/10)%10;
    c=((u-a-10*b)/100)%10;
    d=((u-a-10*b-100*c))%10;
    e=((u-a-10*b-100*c-d*1000))%10;
    count_arr[0]=e;
    count_arr[1]=d;
    count_arr[2]=c;
    count_arr[3]=b;
    count_arr[4]=a;
}