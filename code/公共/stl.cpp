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
}