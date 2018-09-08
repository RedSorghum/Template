#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=s;--i)
#define mst(a,b) memset(a,b,sizeof(a))
#define sz(a) (int(a.size()))
#define pb push_back
#define ls l,(l+r)/2
#define rs (l+r)/2+1,r

namespace seg_func{
    const int maxn=10;
	int ch[maxn][2],T[maxn],cnt=1,S[maxn];
	void init(){mst(S,0);mst(ch,0);cnt=1;}//1...n
	void upd(int u){S[u]=S[ch[u][0]]+S[ch[u][1]];}
	int upd(int& u,int l,int r,map<int,int>& p){
		if(p.lower_bound(l)==p.upper_bound(r))return u;
		int v=cnt++;assert(cnt<=maxn);
		if(l==r)return S[v]=p[l],v;
		ch[v][0]=upd(ch[u][0],ls,p);
        ch[v][1]=upd(ch[u][1],rs,p);
		upd(v);return v;}}

namespace seg_func_p{
    const int maxn=10;
	struct E{E(){S=0;ch[0]=ch[1]=NULL;};int S;E* ch[2];}*T[maxn];
	void init(){T[0]=new E();T[0]->ch[0]=T[0]->ch[1]=T[0];}
	void upd(E* u){u->S=u->ch[0]->S+u->ch[1]->S;}
	E* upd(E* u,int l,int r,map<int,int>& p){
		if(p.lower_bound(l)==p.upper_bound(r))return u;
		E* v=new E();
		if(l==r)return v->S=p[l],v;
		v->ch[0]=upd(u->ch[0],ls,p);
        v->ch[1]=upd(u->ch[1],rs,p);
		upd(v);return v;}}