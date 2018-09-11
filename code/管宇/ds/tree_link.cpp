#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=s;--i)
#define mst(a,b) memset(a,b,sizeof(a))
#define sz(a) (int(a.size()))
#define pb push_back

namespace tree_link{
	const int maxn=10;
	vector<int> N[maxn],q;
	int fa[maxn],so[maxn],sz[maxn],u,v,ms,id;
	int tp[maxn],bd[maxn],od[maxn],uod[maxn],dpth[maxn];
	void init(int rt){
		mst(sz,0);mst(so,0);mst(od,0);q.clear();
		q.pb(rt);id=1;fa[rt]=0;
		rep(i,0,sz(q)){
			sz[u=q[i]]=1;
			for(auto v:N[u])if(v!=fa[u])
				dpth[v]=dpth[u]+1,fa[v]=u,q.pb(v);}
		per(i,0,sz(q)){
			ms=0;u=q[i];bd[u]=u;
			for(auto v:N[u])if(v!=fa[u]){
				sz[u]+=sz[v];
				if(sz[v]>ms)so[u]=v,ms=sz[v],bd[u]=bd[v];}}
		rep(i,0,sz(q))if(!od[u=q[i]])
			for(;u;tp[u]=q[i],od[u]=id,uod[id]=u,u=so[u],id+=1);}
	
	int lca(int x,int y){
		for(;tp[x]!=tp[y];x=fa[tp[x]])
			if(dpth[tp[x]]<dpth[tp[y]])swap(x,y);
		if(dpth[x]<dpth[y])return x;return y;}}