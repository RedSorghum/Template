#include<bits/stdc++.h>
using namespace std;
int main()
{
    double vd;int vi;
    char c_str[]="123";
    vd=strtod(c_str,NULL);
    vi=strtol(c_str,NULL,10);
    //strtold strtoll strtoul strtoull
    string str="456";
    vd=stod(str);
    vi=stoi(str,NULL,10);
    //stol stoll stold stoul stoull
    int pos,len;
    string s1=str.substr(pos,len);
    string s2=str.substr(pos);//to end
    
    priority_queue<int,vector<int>,greater<int> >Q1;//1 2 3
    priority_queue<int,vector<int>,less<int> >Q2;//3 2 1

    bitset<10> BS;int p,v;
    BS.reset();//clear
    BS.set();//BS=~0
    BS.set(p,v);//BS|=v<<p
    BS.flip(p);//BS^=1<<p
    BS.test(p);//(BS>>p)&1
    BS.all();//BS==~0
    BS.any();//BS!=0
    BS.none();//BS==0
    BS.count();//__builtin_popcount(BS)
}