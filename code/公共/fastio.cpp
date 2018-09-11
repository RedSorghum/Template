#include<bits/stdc++.h>
char io[1<<15],*is=io,*ie=io+1;
#define rd if(++is==ie)ie=(is=io)+fread(io,1,sizeof(io),stdin)
template<class T>
inline bool Cin(T &a){
	a=0;bool s=0;
	if(is==ie)return 0;
	do{rd;if(*is=='-')s=1;}while(!isdigit(*is)&&is!=ie);
	if(is==ie)return 0;
	do{(a*=10)+=*is&15;rd;}while(isdigit(*is)&&is!=ie);
	if(s)a=-a;return 1;}

inline int Gets(char a[]){
	int p=0;
	if(is==ie)return 0;
	do rd; while(!isgraph(*is)&&is!=ie);
	if(is==ie)return 0;
	do {a[p++]=*is;rd;}while(isgraph(*is)&&is!=ie);
	a[p]=0;return p;}
