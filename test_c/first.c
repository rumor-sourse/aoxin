#include<stdio.h>
#include<string.h>
#define max(a,b) a>b?a:b
char s1[201],s2[201],s3[201];
int num1[200],num2[200];
int len_s1,len_s2,i,j;

//s1与s2同号，利用flag标志结果的符号（0为正，1为负）
void Plus_operation(int flag)
{
    len_s1=strlen(s1);
    len_s2=strlen(s2);
    for(i=len_s1-1,j=0; i>=0 ; i--)
    {
        num1[j]=s1[i]-'0';
        j++;
        if(i==flag) break; //如果s1与s2同负，flag=1，不录入符号位
    }
    for(i=len_s2-1,j=0; i>=0 ; i--)
    {
        num2[j]=s2[i]-'0';
        j++;
        if(i==flag) break; //如果s1与s2同负，flag=1，不录入符号位
    }

    //计算两字符串长度最大值作为和的长度
    int len;
    if(flag==0) 
        len=max(len_s1,len_s2);
    else 
        len=max(len_s1-1,len_s2-1); //如果s1与s2同负，len值应为长度减1

    //进行加计算及进位
    for(i=0; i<len; i++)
    {
        num1[i]+=num2[i];
        if(num1[i]>9)
        {
            num1[i+1]+=1;
            num1[i]-=10;
        }
    }

    //输出符号位
    if(flag==1) printf("-"); //如果s1与s2同负，flag=1，结果的符号位为负
    //输出结果
    if(num1[i]) //最高位进位
    {
        for(j=i; j>=0; j--)
            printf("%d",num1[j]);
        printf("\n");
    }
    else        //最高位未进位
    {
        for(j=i-1; j>=0; j--)
            printf("%d",num1[j]);
        printf("\n");
    }
}

//s1，s2若异号，则大数减小数
void Minus_operation(int flag,int len,int num1[],int num2[])
{
    //进行减计算及借位
    for(i=0; i<len; i++)
    {
        if(num1[i]>=num2[i])
        {
            num1[i]-=num2[i];
        }
        else
        {
            num1[i]=num1[i]+10-num2[i];
            num1[i+1]-=1;
        }
    }

    //不要前面的0
    while(num1[i]==0)
    {
        i--;
        if(i==0) break;
    }

    //输出符号位
    if(flag==1) printf("-");  
    //输出结果
    for(j=i; j>=0; j--)
        printf("%d",num1[j]);
    printf("\n");
}
//当s1与s2异号，以正数-负数顺序传递实参给形参
void Minus(char s1[],char s2[])
{
    len_s1=strlen(s1);
    len_s2=strlen(s2);
    for(i=len_s1-1,j=0; i>=0 ; i--)  //s1为正数
    {
        num1[j]=s1[i]-'0';
        j++;
    }
    for(i=len_s2-1,j=0; i>0 ; i--)  //s2为负数，s2[0]为符号位，不要
    {
        num2[j]=s2[i]-'0';
        j++;
    }

    memset(s3,0,sizeof(s3)); 
    //为了便于比较同长度下的两个数的大小，将去掉负号的s2赋值给s3
    for(i=1,j=0; i<len_s2; i++)
    {
        s3[j++]=s2[i];
    }

    //len_s1>(len_s2-1) 或 len_s1==（len_s2-1）,s1>=s2 做num1-num2，设置flag=0，标志得正数
    if((len_s1>(len_s2-1))||((len_s1==(len_s2-1)&&strcmp(s1,s3)==0))||(len_s1==(len_s2-1)&&strcmp(s1,s3)==1))
    {
        Minus_operation(0,len_s1,num1,num2);
    }
    //(len_s2-1)>len_s1 或 len_s1==（len_s2-1）,s1<s2  做num2-num1，设置flag=1，标志得负数
    else if((len_s2-1)>len_s1||(len_s1==(len_s2-1)&&strcmp(s1,s3)==-1))
    {
        Minus_operation(1,len_s2-1,num2,num1);
    }
}
int main()
{
        printf("please intput numbers:\n");
        scanf("%s%s",s1,s2);
        memset(num1,0,sizeof(num1));   //初始化num1
        memset(num2,0,sizeof(num2));   //初始化num2
        if(s1[0]!='-'&&s2[0]!='-')
        {
            Plus_operation(0); //s1与s2同正，设置flag=0
        }
        else if(s1[0]=='-'&&s2[0]=='-')
        {
            Plus_operation(1); //s1与s2同负，设置flag=1
        }
        else if(s1[0]!='-'&&s2[0]=='-')
        {
            Minus(s1,s2); //s1为正，s2为负，传递s1,s2顺序，实现一个正数减一个负数
        }
        else
        {
            Minus(s2,s1); //s1为正，s2为负，传递s2,s1顺序，实现一个正数减一个负数
        }
    return 0;
}
