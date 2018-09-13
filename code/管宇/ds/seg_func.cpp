#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define per(i,s,t) for(int i=((t)-1);i>=s;--i)
#define mst(a,b) memset(a,b,sizeof(a))
#define sz(a) (int(a.size()))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ls l,(l+r)/2
#define rs (l+r)/2+1,r
typedef long long ll;

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

namespace seg_func_lazy{
	const int maxn = 10;
    int ch[maxn][2],T[maxn],cnt=1;
    ll S[maxn],add[maxn];pair<ll,int> Ma[maxn],Mi[maxn];
    int init(int l,int r){
        int u=cnt++;
    	if(l==r){Ma[u]=Mi[u]=mp(0,l);return u;}
    	ch[u][0]=init(l,(l+r)/2);ch[u][1]=init((l+r)/2+1,r);
    	Ma[u]=max(Ma[ch[u][0]],Ma[ch[u][1]]);
    	Mi[u]=min(Mi[ch[u][0]],Mi[ch[u][1]]);
    	return u;}
    void copy(int v,int u){
    	add[v]=add[u];S[v]=S[u];Ma[v]=Ma[u];Mi[v]=Mi[u];
    	ch[v][0]=ch[u][0];ch[v][1]=ch[u][1];}
    int upd(int& u,int l,int r,int L,int R,int a){
    	if(L>r||l>R||l>r||L>R)return u;
    	int v=cnt++;assert(cnt<=maxn);copy(v,u);
    	if(L<=l&&r<=R){
    		Ma[v].fi+=a;Mi[v].fi+=a;add[v]+=a;S[u]+=v*(r-l+1);return v;}
    	ch[v][0]=upd(ch[u][0],ls,L,R,a);ch[v][1]=upd(ch[u][1],rs,L,R,a);
    	Ma[v]=max(Ma[ch[v][0]],Ma[ch[v][1]]);Ma[v].fi+=add[v];
    	Mi[v]=min(Mi[ch[v][0]],Mi[ch[v][1]]);Mi[v].fi+=add[v];
    	S[v]=S[ch[u][0]]+S[ch[u][1]];S[v]+=add[v]*(r-l+1);
    	return v;}
	pair<ll,int> qmax(int& u,int l,int r,int L,int R){
		if(L>r||l>R||l>r||L>R)return mp(1ull<<63,-1);
		if(L<=l&&r<=R)return Ma[u];
		pair<ll,int> t=max(qmax(ch[u][0],ls,L,R),qmax(ch[u][1],rs,L,R));
		t.fi+=add[u];return t;}
	ll qsum(int& u,int l,int r,int L,int R){
		if(L>r||l>R||l>r||L>R)return 0;
		if(L<=l&&r<=R)return S[u];
		return qsum(ch[u][0],ls,L,R)+qsum(ch[u][1],rs,L,R)+add[u]*(r-l+1);}};

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