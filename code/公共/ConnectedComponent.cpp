#include<bits/stdc++.h>
using namespace std;
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define mst(a,b) memset(a,b,sizeof(a))
#define all(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;

const int maxn = 1000;

//原图点从1到n，使用init初始化点数n与图N
//使用run运行，生成各个点所属的集合的标号fa
//割点存储在cut中，桥存储在bridge中
struct BCC{
	BCC(){init(0,0);}
	int n,t,dfn[maxn],low[maxn],fa[maxn],s[maxn];
	vector<int>*N,cut;vector<pii> bridge;
	void init(int _n,vector<int>*_N){
		n=_n;t=-1;N=_N;mst(dfn,0);mst(low,0);cut.clear();bridge.clear();}
	void dfs(int u,int d,int p){
		int sec=0,son=d>1;dfn[u]=low[u]=d;s[++t]=u;
		for(auto v:N[u]){
			if(!dfn[v]){
				dfs(v,d+1,u);low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])bridge.pb(mp(u,v));
				if(low[v]>=dfn[u]&&++son==2)cut.pb(u);}
			else if(v!=p||sec++)low[u]=min(low[u],dfn[v]);}
		if(dfn[u]==low[u])do fa[s[t]]=u;while(s[t--]!=u);}
	void run(){repb(i,1,n)if(!dfn[i])dfs(i,1,0);}};


//原图点从1到n，使用init初始化点数n与图N
//使用run运行，生成点联通分量数目m，各点联通分量存储在D[1,m]中
//run过程中默认使用gen生成对应边数信息存储在e[1,m]
//割点存储在cut中
struct DCC{
	DCC(){init(0,0);}
	int n,t,m,dfn[maxn],low[maxn],s[maxn],e[maxn];
	vector<int>*N,cut,D[maxn];
	void init(int _n,vector<int>* _N){
		n=_n;N=_N;t=-1;m=0;mst(dfn,0);mst(low,0);cut.clear();}
	void dfs(int u,int d,int p){
		int sec=0,son=d>1;dfn[u]=low[u]=d;s[++t]=u;
		for(auto v:N[u]){
			if(!dfn[v]){
				dfs(v,d+1,u);low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]){
					if(++son==2)cut.pb(u);
					m+=1;D[m].clear();D[m].pb(u);
					do D[m].pb(s[t]);while(s[t--]!=v);}}
			else if(v!=p||sec++)low[u]=min(low[u],dfn[v]);}}
	void run(){repb(i,1,n)if(!dfn[i])dfs(i,1,0);gen();}
	void gen(){
		mst(s,-1);mst(e,0);
		repb(i,1,m){
			for(auto j:D[i])s[j]=i;
			for(auto j:D[i])for(auto k:N[j])if(s[k]==i)e[i]+=1;}}};