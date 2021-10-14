#include<iostream>
#include<string>
using namespace std;
int main()
{
    string arr,ans;
    int i=0,len;
    cin>>arr; 
    while(arr[i])
    {
        len=1;
        while(arr[i+len]&&arr[i+len]==arr[i])
        len++;
        ans+=arr[i];
        if(len>1)
        ans+=to_string(len);
        i+=len;
    }
    cout<<ans<<endl<<ans.length()<<endl;
}