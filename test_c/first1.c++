#include<iostream>
#include<string>
using namespace std;

string s1,s2;
//flag1  s1的符号  flag2  s2的符号  flag0最终结果的符号   0--->正  1---->负
int flag1=0,flag2=0;
int flag0=0;
int max_decimal,max_integer;

void Init()
{
    cin>>s1>>s2;
    if(s1[0]=='-')flag1=1,s1.erase(0,1);
    if(s2[0]=='-')flag2=1,s2.erase(0,1);
    int decimal_1=0,decimal_2=0;            //a,b的小数位数
    int integer_1,inter_2;                  //a,b的整数位数
    if(s1.find('.')!=string::npos)
    {                                           //按小数点的位置存小数位数和整数位数
        integer_1=s1.find('.');
        decimal_1=s1.size()-s1.find('.')-1;
        s1.erase(s1.find('.'),1);
    }
    else                                        //若没找到小数点则直接存整数位数
        integer_1=s1.size();
    if(s2.find('.')!=string::npos)
    {                                           //第二个数同理
        inter_2=s2.find('.');
        decimal_2=s2.size()-s2.find('.')-1;
        s2.erase(s2.find('.'),1);
    }
    else
        inter_2=s2.size();
    max_decimal=max(decimal_1,decimal_2);
    max_integer=max(integer_1,inter_2);
    //补全位数
    if(decimal_1<decimal_2)
        s1+=string(decimal_2-decimal_1,'0');               
    else
        s2+=string(decimal_1-decimal_2,'0');
    if(integer_1<inter_2)
        s1=string(inter_2-integer_1,'0')+s1;
    else
        s2=string(integer_1-inter_2,'0')+s2;
    //结果为负数的情况
    if(flag1==1&&flag2==1||flag1==1&&flag2==0&&s1>s2||flag1==0&&flag2==1&&s1<s2)
        flag0=1;
    if(s1<s2)
        s1.swap(s2);
   /* cout<<integer_1<<"---"<<decimal_1<<endl;
    cout<<inter_2<<"---"<<decimal_2<<endl;
    cout<<flag1<<"---"<<flag2<<"---"<<flag0<<endl;
    cout<<s1<<endl<<s2<<endl;*/
}
//相同正负则相加
string add(string a,string b)
{
    string res;
    int acc=0;
    //实现加法
    for(int i=a.length()-1,j=b.length()-1;i>=0||j>=0;)
    {
        if(i>=0)acc+=a[i--]-'0';
        if(j>=0)acc+=b[j--]-'0';
        res=to_string(acc%10)+res;
        acc/=10;
    }
    //出现相加后进位的情况
    if(acc) res='1'+res;
    return res;
}
//一正一负则相减
string sub(string a,string b)
{
    int t=0;
    string c;
    for(int i=a.size()-1,j=b.size()-1;i>=0;)
    {
        t=t+a[i--]-'0';
        if(j>=0)
            t=t-(b[j--]-'0');
        c=to_string((t+10)%10)+c;
        if(t<0)t=-1;
        else t=0;
    }
    int r;
    for( r=0;r<max_integer-1&&c[r]=='0';r++);
    c=c.substr(r);
    return c;
}
//将结果进行展示
void show(string a)
{
    string res;
    bool flag=false;
    for(int i=a.length()-1;i>=0;i--)
    {
        if(a.length()-i<=max_decimal)
        {
            if(flag||a[i]!='0')
            {
            res=a[i]+res;
            flag=true;
            }
        }
        else if(a.length()-i==max_decimal+1)
        {
            if(flag)
                res="."+res;
            res=a[i]+res;
        }
        else
            res=a[i]+res;
    }
    if(flag0==1)res="-"+res;
    cout<<res;
}
int main()
{
        Init();
        if(flag1^flag2)
            show(sub(s1,s2));
        else
            show(add(s1,s2));
        return 0;
}
