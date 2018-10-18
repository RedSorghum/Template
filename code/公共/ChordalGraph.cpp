#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=(s);--i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define mst(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define sz(x) ((int)x.size())
typedef pair<int,int> pii;

const int maxn = 1000;

struct MSC{
	MSC(){init(0,0);}
	int n,deg[maxn],rk[maxn],nxt[maxn],mxc[maxn],cn;bool vis[maxn],perfect;
	vector<int>*N,peo,indep;priority_queue<pii> q;
	void init(int _n,vector<int>*_N){
		n=_n;N=_N;mst(vis,0);mst(deg,0);peo.clear();}
	bool run(){
		int u;q.push(mp(0,1));
		while(!q.empty()){
			u=q.top().se;q.pop();
			if(vis[u])continue;
			vis[u]=1;peo.pb(u);
			for(auto v:N[u])
				if(!vis[v])deg[v]+=1,q.push(mp(deg[v],v));}
		reverse(all(peo));rep(i,0,sz(peo))rk[peo[i]]=i;
		return perfect=check();}
	bool check(){
		if(n!=sz(peo))return false;
		auto cmp=[&](int a,int b){return rk[a]<rk[b];};
		repb(i,1,n){
			sort(all(N[i]),cmp);
			nxt[i]=lower_bound(all(N[i]),i,cmp)-N[i].begin();}
		per(i,0,n){
			int u=peo[i],p=nxt[u];
			if(p<sz(N[u])){
				int v=N[u][p],q=nxt[v];
				rep(m,p+1,sz(N[u])){
					while(q<sz(N[v])&&rk[N[v][q]]<rk[N[u][m]])q+=1;
					if(q==sz(N[v])||rk[N[v][q]]!=rk[N[u][m]])return false;}}}
		return true;}
	int maxclique(){//==min color
		cn=0;repb(i,1,n)mxc[i]=sz(N[i])-nxt[i]+1;
		per(i,0,n){
			int u=peo[i],p=nxt[u];
			if(p<sz(N[u])){
				int v=N[u][p],q=nxt[v];
				if(sz(N[v])-q+1<=sz(N[u])-p)mxc[v]=0;}}
		return cn=*max_element(mxc+1,mxc+1+n);}
	vector<int> maxindep(){//==min clique cover
		mst(vis,0);indep.clear();
		rep(i,0,sz(peo))if(!vis[peo[i]]){
			indep.pb(peo[i]);
			for(auto v:N[peo[i]])vis[v]=1;}
		return indep;}};