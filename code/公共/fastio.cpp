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

template<class T>
inline bool Cind(T &a){
	a=0.;T b=1.;int s=0;bool neg=0;
	if(is==ie)return 0;
	while(!isgraph(*is)&&is!=ie)rd;
	if(is==ie)return 0;
	if(*is=='-')s=neg=1;else if(*is=='.')s=2;else a=*is&15,s=3;rd;
	while(s&&isgraph(*is)&&is!=ie){
		if(s==1)isdigit(*is)?(a*=10)+=*is&15,s=3:s=2;
		else if(s==2)isdigit(*is)?a+=(b*=.1)*(*is&15),s=4:s=0;
		else if(s==3)isdigit(*is)?(a*=10)+=*is&15:*is=='.'?s=2:s=0;
		else if(s==4)isdigit(*is)?a+=(b*=.1)*(*is&15):s=0;
		rd;}if(neg)a=-a;return 1;}

inline int Gets(char a[]){
	int p=0;
	if(is==ie)return 0;
	do rd; while(!isgraph(*is)&&is!=ie);
	if(is==ie)return 0;
	do {a[p++]=*is;rd;}while(isgraph(*is)&&is!=ie);
	a[p]=0;return p;}