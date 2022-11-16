#include<iostream>
#include<cmath>
using namespace std;
bool cache_1[100000];
bool cache_2[100000]={0};
bool cache_3[100000]={0};
bool cache_4[100000];
bool memory[1000001];
int len,lena,lenb;
bool And_gate(bool A,bool B)//与门
{
    if(A==true)//如果A为True
    {
        if(B==true)//在A为True的条件下，B为True
        return true;//返回值为True
    }
    return false;//若执行完if语句，函数未返回True，则返回False
}
bool Not_gate(bool A)//非门
{
    if(A==true)//若输入为True
    return false;//则返回False
    else//若输入不为True
    return true;//则返回True
}
bool Or_gate(bool A,bool B)//或门
{
    if(A==true)//如果A为True
    return true;//返回值为True
    else if(B==true)//若A为False，但B为True
    return true;//返回值为True
    else//若A，B均为False
    return false;//返回值为False
}
bool add(bool a,bool b)
{
    bool m=Or_gate(a,b);
    bool n=Not_gate(And_gate(a,b));
    return And_gate(m,n);
}
bool carry(bool a,bool b)
{
    return And_gate(a,b);
}
void sys(int a)//10进制数
{
    string ans;
    char list[2]={'0','1'};
    int N=2;
    int x;
    while(true)//取模转进制法，不懂得自行百度
    {
        x=a%N;
        cout<<"本次取模结果为"<<x<<endl;
        ans+=list[x];
        a=a/N;
        if(a==0)
        break;
    }
    len=ans.size();//记录二进制数长度
    cout<<"该二进制数总长度为"<<len<<endl;
    cout<<"该二进制数为";
    for(int i=len-1;i>=0;i--)//所记录的字符串是倒序的，要从后往前转化为bool数组
    {
        if(ans[i]=='1')//若为1
        cache_1[i]=1;//bool中的1代表True
        else
        cache_1[i]=0;
        cout<<ans[i];
    }
    cout<<endl;
}//上方代码为进制转化，存储在cache_1数组里
int sys2(int len)//位数转进制法
{
    cout<<"开始在缓存中将结果二进制数转化为十进制数"<<endl;
    int n=len-1,ans=0;
    for(int i=0;i<=n;i++)
    {
        cout<<"本次循环位数为"<<i<<endl;
        int s=pow(2,i);
        if(cache_4[i]==1)
        ans+=s;
    }
    cout<<"运算结果为";
    return ans;
}
int main()
{
    int a,b;//两个十进制数
    int address_begin_a,address_begin_b;//两个二进制数的开始地址
    int address_end_a,address_end_b;//两个二进制数的结束地址
    cin>>a>>b;
    cout<<"将十进制数a转化为二进制"<<endl;
    sys(a);//将a转化为二进制
    lena=len;
    address_begin_a=0;//a的开始地址为0
    address_end_a=len-1;//结束地址为二进制数a的长度
    cout<<"内存中存储二进制数a的起始位置为"<<address_begin_a<<endl;
    cout<<"结束位置为"<<address_end_a<<endl;
    address_begin_b=address_end_a+1;//b的开始地址为a结束地址的下一位
    for(int i=address_begin_a;i<=address_end_a;i++)
    {
        memory[i]=cache_1[i];//将cache中存储的a输入到内存中
    }
    cout<<"将十进制数b转化为二进制"<<endl;
    sys(b);//将b转化为二进制，此时cache和len都已经刷新
    lenb=len;
    address_end_b=address_begin_b+len-1;//记录b的结束地址
    cout<<"内存中存储二进制数b的起始位置为"<<address_begin_b<<endl;
    cout<<"结束位置为"<<address_end_b<<endl;
    for(int i=address_begin_b;i<=address_end_b;i++)
    {
        memory[i]=cache_1[i-address_begin_b];//将cache中存储的b输入到内存中
    }
    cout<<"将内存中的数据调入缓存"<<endl;
    for(int i=address_begin_a;i<=address_end_a;i++)
    {
        cache_2[i]=memory[i];
    }
    for(int i=address_begin_b;i<=address_end_b;i++)
    {
        cache_3[i-address_begin_b]=memory[i];
    }
    cout<<"CPU将缓存中的二进制数进行相加处理"<<endl;
    cout<<"二进制数a的长度为"<<lena<<endl;
    cout<<"二进制数b的长度为"<<lenb<<endl;
    int times,lenans;
    if(lena>lenb)
    times=lena;
    else
    times=lenb;
    bool Carry=0;
    for(int i=0;i<times;i++)
    {
        cout<<"对第"<<i<<"位进行加法运算处理"<<endl;
        cache_4[i]=add(Carry,add(cache_2[i],cache_3[i]));//计算结果
        cout<<"加法结果为"<<cache_4[i]<<endl;
        Carry=Or_gate(carry(cache_2[i],cache_3[i]),carry(Carry,add(cache_2[i],cache_3[i])));//计算进位
        cout<<"进位结果为"<<Carry<<endl;
    }
    cache_4[times]=Carry;//将最高一位的更高一位输入为当前的进位
    if(Carry)
    times++;
    cout<<"结果二进制数为";
    for(int i=times-1;i>=0;i--)
    cout<<cache_4[i];
    cout<<endl;
    cout<<"存储在缓存中的结果二进制数长度为"<<times<<endl;
    lenans=times;
    cout<<sys2(lenans)<<endl;
}