#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t) for(int i=(s);i<(t);++i)
#define repb(i,s,t) for(int i=(s);i<=(t);++i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)x.size())
#define dd(x) cout<<#x<<'='<<x<<' '
#define de(x) cout<<#x<<'='<<x<<'\n'
#define fi first
#define se second
#define sq(x) ((x)*(x))
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef double db;
typedef vector<vector<db> > mat;
typedef complex<double> cpd;//*counter rotate
typedef db(*func)(db x);

const int inf = 0x3f3f3f3f;
const ll infl = 4557430888798830399ll;
const db infd = 1./0.;
const db eps = 1e-10;
const db pi = acosl(-1.);
const ll mod = 1e9+7;

int sgn(db x){return (x>eps)-(x<-eps);}

db det(mat v){
	db ans=1.,c;
	rep(i,0,sz(v)){
		if(!sgn(v[i][i])){
			ans=-ans;
			rep(j,i+1,sz(v))if(sgn(v[j][i])){
				swap(v[i],v[j]);break;}}
		if(!sgn(v[i][i]))return 0.;
		rep(j,i+1,sz(v))if(sgn(v[j][i])){
			c=v[j][i]/v[i][i];
			rep(k,i,sz(v))v[j][k]-=v[i][k]*c;}}
	rep(i,0,sz(v))ans*=v[i][i];return ans;}

bool cramer(mat a,vector<db> c,vector<db>& x){
	db da=det(a);mat t;x.clear();
	rep(i,0,sz(a)){
		t=a;rep(j,0,sz(a))t[j][i]=c[j];x.pb(det(t)/da);}
	return sz(x)==sz(a);}

mat operator*(mat a,mat b){
	int n=sz(a);mat c;c.resize(n,vector<db>(n));
	rep(i,0,n)rep(j,0,n)rep(k,0,n)c[i][j]+=a[i][k]*b[k][j];
	return c;}

vector<db> quadratic(db a,db b,db c){
	db d=b*b-4.*a*c;vector<db> r;
	if(sgn(d)==0)r.pb(-.5*b/a);
	if(sgn(d)>0)r.pb(.5*(sqrt(d)-b)/a),r.pb(.5*(-sqrt(d)-b)/a);
	sort(all(r));return r;}

db simpson(db a,db b,func f){
	return (f(a)+4.*f(.5*(a+b))+f(b))*(b-a)/6.;}

db asr(db a,db b,db S,func f){
	if(a>b)return 0.;
	db L=simpson(a,.5*(a+b),f),R=simpson(.5*(a+b),b,f),dS=(L+R-S)/15.;
	if(sgn(dS)==0)return L+R+dS;
	return asr(a,.5*(a+b),L,f)+asr(.5*(a+b),b,R,f);}

// o: -1 min|+1 max t: 0 left|1 right
pair<db,db> search_extreme(db l,db r,func f,int o,int t=0){
	db d,lv,rv;
	while(r-l>eps){
		d=(r-l)/3.;lv=f(l+d);rv=f(r-d);
		if(sgn(lv-rv)==0)t?l+d:r-=d;
		else if(sgn(lv-rv)==o)r-=d;
		else l+=d;}return mp(.5*(l+r),f(.5*(l+r)));}

// o: -1 dec|+1 inc t: 0 left|1 right
db binary_search(db l,db r,db s,func f,int o,int t=0){
	while(r-l>eps){
		if(sgn(f(.5*(l+r))-s)==0)t?l=.5*(l+r):r=.5*(l+r);
		else if(sgn(f(.5*(l+r))-s)==o)r=.5*(l+r);
		else l=.5*(l+r);}return .5*(l+r);}

struct vec{
	vec(){}
	vec(int O){cin>>x>>y;len=hypot(x,y),ang=atan2(y,x);}
	vec(db X,db Y):x(X),y(Y),len(hypot(X,Y)),ang(atan2(Y,X)){}
	vec(db T,db R,int o):x(R*cosl(T)),y(R*sinl(T)),len(R),ang(atan2(y,x)){};
	vec operator-(){return vec(-x,-y);}
	vec operator~(){return vec(-y,x);}//left
	vec operator+(vec v){return vec(x+v.x,y+v.y);}
	vec operator-(vec v){return vec(x-v.x,y-v.y);}
	vec operator*(db c){return vec(x*c,y*c);}
	vec operator/(db c){assert(sgn(c));return vec(x/c,y/c);}
	db operator*(vec v){return x*v.x+y*v.y;}
	db operator^(vec v){return x*v.y-v.x*y;}//counter +|clockwise -
	vec norm(){assert(sgn(len));return vec(x/len,y/len);}
	vec trunc(db l){assert(sgn(len));return *this*(l/len);}
	vec rot(db t){return vec(len*cos(ang+t),len*sin(ang+t));}//left
	bool operator<(const vec& v)const{
		return sgn(x-v.x)<0||(!sgn(v.x-x)&&sgn(y-v.y)<0);}
	bool operator==(const vec& v)const{
		return !sgn(v.x-x)&&!sgn(v.y-y);}
	db x,y,len,ang;};

struct line{
	line(){}
	line(vec a,vec b):s(a),t(b),d(b-a),A(b.y-a.y),B(a.x-b.x),C(b^a){assert(sgn(d.len));}
	line(db a,db b,db c):A(a),B(b),C(c){
		if(sgn(c)){
			if(sgn(a)&&sgn(b))s=vec(0.,-c/b),t=vec(-c/a,0.);
			else if(sgn(a))s=vec(-c/a,0.),t=vec(-c/a,1.);
			else if(sgn(b))s=vec(0.,-c/b),t=vec(1.,-c/b);}
		else{
			if(sgn(a)&&sgn(b))s=vec(0.,0.),t=vec(-b,a);
			else if(sgn(a))s=vec(0.,0.),t=vec(0.,1.);
			else if(sgn(b))s=vec(0.,0.),t=vec(1.,0.);}
		assert(sgn(a)||sgn(b));d=t-s;}
	db dis(vec p){return ((s-p)^(t-p))/d.len;}//left +|right -
	bool on(vec p){return !sgn((s-p)^(t-p))&&sgn((s-p)*(t-p))<1;}
	int pos(vec p){return sgn((s-p)^(t-p));}//left +|right -
	vec proj(vec p){return p-~d.trunc(dis(p));}
	bool operator<(line l){return sgn(d.ang-l.d.ang)<0||
								(!sgn(d.ang-l.d.ang)&&pos(l.s)<0);}
	bool operator==(line l){return sgn(d.ang-l.d.ang)==0;}
	vec s,t,d;db A,B,C;};

struct cir{
	cir(){};
	cir(db X,db Y,db R):x(X),y(Y),r(R),o(vec(X,Y)){};
    cir(vec O,db R):x(O.x),y(O.y),r(R),o(O){};
    bool on(vec p){return sgn((p-o).len-r)==0;}
	db x,y,r;vec o;};

//strict X|touch T|end L|inf I|connect C|no N
int cross_judge(line p,line q){
	int a=sgn((p.s^p.t)+(p.t^q.s)+(q.s^p.s))*sgn((p.s^p.t)+(p.t^q.t)+(q.t^p.s));
	int b=sgn((q.s^q.t)+(q.t^p.s)+(p.s^q.s))*sgn((q.s^q.t)+(q.t^p.t)+(p.t^q.s));
	if(a+b==-2)return 'X';if(a+b==-1)return 'T';
	if(a||b)return 'N';if(sgn(p.d^q.d))return 'L';
	int in=	sgn((q.s-p.s)*(q.t-p.s))<0||sgn((q.s-p.t)*(q.t-p.t))<0||
			sgn((p.s-q.s)*(p.t-q.s))<0||sgn((p.s-q.t)*(p.t-q.t))<0;
	int on=(p.s==q.s)+(p.s==q.t)+(p.t==q.s)+(p.t==q.t);
	if(in||on==2)return 'I';if(on)return 'C';return 'N';}

//has 1|no or inf 0
int intersect_point(line p,line q,vec& v){
	db d=p.B*q.A-p.A*q.B,x=p.C*q.B-p.B*q.C,y=p.A*q.C-p.C*q.A;
	if(!sgn(d))return 0;v=vec(x/d,y/d);return 1;}

//fast
vec isp(line p,line q){
	return vec((p.C*q.B-p.B*q.C)/(p.B*q.A-p.A*q.B),(p.A*q.C-p.C*q.A)/(p.B*q.A-p.A*q.B));}

//number of points
int intersect_point(line l,cir c,vector<vec>& v){
	v.clear();db lo=fabsl(l.dis(c.o));
	if(sgn(lo-c.r)>0)return 0;
	if(sgn(lo-c.r)==0){v.pb(l.proj(c.o));return 1;}
	db ld=sqrtl(c.r*c.r-lo*lo);vec p=l.proj(c.o);
	v.pb(p-l.d.trunc(ld));v.pb(p+l.d.trunc(ld));return 2;}

//-1 inf
int intersect_point(cir a,cir b,vector<vec>& v){
	v.clear();if(a.o==b.o&&sgn(a.r-b.r)==0)return -1;
	if(sgn((a.o-b.o).len-(a.r+b.r))>0)return 0;
	line l=line(2.*(b.x-a.x),2.*(b.y-a.y),(a.o*a.o)-(b.o*b.o)-sq(a.r)+sq(b.r));
	vector<vec> p;int n;
	n=intersect_point(l,a,p);rep(i,0,n)if(a.on(p[i])&&b.on(p[i]))v.pb(p[i]);
	n=intersect_point(l,b,p);rep(i,0,n)if(a.on(p[i])&&b.on(p[i]))v.pb(p[i]);
	sort(all(v));v.erase(unique(all(v)),v.end());return sz(v);}

//no vertical line
int intersect_point(vector<line> l,vector<vec>& v){
	return 0;
}

//no same point|on boarder
bool in_convex_hull(vec p,vector<vec> v){
	if(sz(v)==1)return p==v[0];
	int cnt[2]={0,0};
	rep(i,0,sz(v)){
		if(line(v[i],v[(i+1)%sz(v)]).on(p))return true;
		cnt[0]+=sgn((v[i]-p)^(v[(i+1)%sz(v)]-p))>0;
		cnt[1]+=sgn((v[i]-p)^(v[(i+1)%sz(v)]-p))<0;}
	return cnt[0]==sz(v)||cnt[1]==sz(v);}

bool in_polygon(vec p,vector<vec> v){
	return false;}

//judge == ang<180 non-zero area unique | != ang<=180 zero area
//< <= counter | > >= clockwise
//judge 1->counter
#define judge(a,b,c) sgn((a^b)+(b^c)+(c^a))
vector<vec> convex_hull(vector<vec> a){
	int n=0,m;vector<vec> c;
    sort(all(a));a.erase(unique(all(a)),a.end());
    if(sz(a)<3)return a;c.resize(2*sz(a));
    for(int i=0;i<sz(a);c[n++]=a[i++])
    	while(n>1&&judge(c[n-2],c[n-1],a[i])<=0)n--;
    reverse(all(a));m=n;
    for(int i=0;i<sz(a);c[m++]=a[i++])
    	while(m>n&&judge(c[m-2],c[m-1],a[i])<=0)m--;
    c.resize(m-1);return c;}

/*
struct dynamic_convex_hull
{
	dynamic_convex_hull(){};
	

	void add(vec v)
	{
		auto p=U.lower_bound(v);
		if(p==U.begin()||p==U.end())
		{

		}
	}
	set<vec> U,D;
};
*/


db nearest_pair(int l,int r,vector<vec>& v){
	if(l==r)return infd;
	int m=(l+r)>>1;db x=v[m].x;vector<vec> p;
	db sol=min(nearest_pair(l,m,v),nearest_pair(m+1,r,v));
	inplace_merge(v.begin()+l,v.begin()+m+1,v.begin()+r+1,[](vec a,vec b){return a.y<b.y;});
	rep(i,l,r+1)if(fabsl(v[i].x-x)<=sol)p.pb(v[i]);
	rep(i,0,sz(p))rep(j,i+1,min(i+9,sz(p)))sol=min(sol,(p[i]-p[j]).len);
	return sol;}

db nearest_pair(vector<vec> v){
	sort(all(v),[](vec a,vec b){return a.x<b.x;});
	return nearest_pair(0,sz(v)-1,v);}

db get_area(db r,vec a,vec b){
	db la=max(a.len,b.len),li=min(a.len,b.len),l=(a-b).len;
	if(!sgn(la)||!sgn(li)||!sgn(l))return 0.;
	db t=acosl((a*b)/(la*li)),d=fabsl(a^b)/l;vec c=b-a;
	if(d>=r)return .5*r*r*t;
	if(la<=r)return .5*la*li*sinl(t);
	if(li<=r){
		db ot=acosl(d/la)-acosl(d/r),it=t-ot;
		return .5*r*r*ot+.5*r*li*sinl(it);}
	if(sgn((a*c)*(b*c))==-1){
		db it=2.*acosl(d/r),ot=t-it;
		return .5*r*r*ot+.5*r*r*sinl(it);}
	return .5*r*r*t;}

//be careful with precision
db intersection_area(cir c,vector<vec> p){
	db area=0;rep(i,0,sz(p))p[i]=p[i]-c.o;
	rep(i,0,sz(p))
		area+=sgn(p[i]^p[(i+1)%sz(p)])*get_area(c.r,p[i],p[(i+1)%sz(p)]);
	return fabsl(area);}

#define arc(a,b,c) acos((a*a+b*b-c*c)/(2.*a*b))
#define seg(a,r) .5*r*r*(a-sin(a))
db union_area(vector<cir> c){
	sort(all(c),[](cir a,cir b){return a.r>b.r;});
	vector<cir> z;vector<vec> v;vector<pair<db,db> >itv;
	bool cover;db d,a,ta,sa,ea,area=0.;vec t;
	rep(i,0,sz(c)){
		rep(k,0,sz(c)){cout<<c[k].x<<" "<<c[k].y<<endl;}
		cover=false;
		rep(j,0,sz(z))if(sgn((z[j].o-c[i].o).len-(z[j].r-c[i].r))<=0){
			cover=true;break;}
		if(!cover)z.pb(c[i]);}
	rep(i,0,sz(z)){
		itv.clear();
		rep(j,0,sz(z)){
			t=z[j].o-z[i].o;d=t.len;a=t.ang;
			if(j!=i&&sgn(d-(z[i].r+z[j].r))<0){
				ta=arc(z[i].r,d,z[j].r);sa=a-ta;ea=a+ta;
				if(sa<-pi)itv.pb(mp(sa+2.*pi,pi));
				if(ea>pi)itv.pb(mp(-pi,ea-2.*pi));
				itv.pb(mp(max(-pi,sa),min(pi,ea)));}}
		if(!sz(itv)){area+=pi*z[i].r*z[i].r;continue;}
		sort(all(itv));itv.pb(mp(itv[0].fi+2.*pi,itv[0].se+2.*pi));
		rep(j,0,sz(itv)-1){
			if(sgn(itv[j+1].fi-itv[j].se)>0)
				area+=seg(itv[j+1].fi-itv[j].se,z[i].r),
				area+=.5*((z[i].o+vec(itv[j].se,z[i].r,0))^
							(z[i].o+vec(itv[j+1].fi,z[i].r,0)));
			else itv[j+1].fi=itv[j].fi,itv[j+1].se=max(itv[j+1].se,itv[j].se);}}
	return area;}

//make sure not on same line
vec circumcircle_center(vec a,vec b,vec c){
    mat d={{a.x,a.y,1},{b.x,b.y,1.},{c.x,c.y,1.}};
    mat x={{sq(a.x)+sq(a.y),a.y,1.},{sq(b.x)+sq(b.y),b.y,1.},{sq(c.x)+sq(c.y),c.y,1.}};
    mat y={{a.x,sq(a.x)+sq(a.y),1.},{b.x,sq(b.x)+sq(b.y),1.},{c.x,sq(c.x)+sq(c.y),1.}};
    return vec(det(x),det(y))/(2.*det(d));}

vec incircle_center(vec a,vec b,vec c){
	db A=(b-c).len,B=(a-c).len,C=(a-b).len;
	return (a*A+b*B+c*C)/(A+B+C);}

vec ortho_center(vec a,vec b,vec c){
	mat d={{a.x,a.y,1.},{b.x,b.y,1.},{c.x,c.y,1.}};
	mat x={{b*c,1.,a.y},{c*a,1.,b.y},{a*b,1.,c.y}};
	mat y={{b*c,a.x,1.},{c*a,b.x,1.},{a*b,c.x,1.}};
	return vec(det(x),det(y))/(2.*det(d));}

vec centroid(vector<vec> v){
	db a=0.,cx=0.,cy=0.;
	rep(i,0,sz(v)){
		a+=v[i]^v[(i+1)%sz(v)];
		cx+=(v[i].x+v[(i+1)%sz(v)].x)*(v[i]^v[(i+1)%sz(v)]);
		cy+=(v[i].y+v[(i+1)%sz(v)].y)*(v[i]^v[(i+1)%sz(v)]);}
	a=3.*fabsl(a);return vec(cx,cy)/a;}

//o(n)
cir minimal_circumcircle(vector<vec> v){
    random_shuffle(all(v));cir c=cir(v[0],0.);
    rep(i,1,sz(v)){
        if((v[i]-c.o).len<=c.r)continue;
        c=cir(v[i],0);
        rep(j,0,i){
            if((v[j]-c.o).len<=c.r)continue;
            c=cir((v[i]+v[j])*.5,.5*(v[i]-v[j]).len);
            rep(k,0,j){
                if((v[k]-c.o).len<=c.r)continue;
                vec o=circumcircle_center(v[i],v[j],v[k]);
                c=cir(o,(v[i]-o).len);}}}
    return c;}

//left area|add boarder when necessary
//vec z=vec(1e10,1e10);rep(i,0,4)l.pb(line(z,z.rot(.5*pi))),z=z.rot(.5*pi);
vector<vec> half_plane_intersection(vector<line> l){
	vec z=vec(200,200);rep(i,0,4)l.pb(line(z,z.rot(.5*pi))),z=z.rot(.5*pi);
	deque<vec> c;deque<line> q;vector<vec> v;
	sort(all(l));l.erase(unique(all(l)),l.end());
	rep(i,0,sz(l)){
		while(sz(c)&&l[i].pos(c.back())==-1)c.pop_back(),q.pop_back();
		while(sz(c)&&l[i].pos(c.front())==-1)c.pop_front(),q.pop_front();
		if(sz(q))c.pb(isp(q.back(),l[i]));q.pb(l[i]);}
	while(sz(c)&&q.back().pos(c.front())==-1)c.pop_front(),q.pop_front();
	while(sz(c)&&q.front().pos(c.back())==-1)c.pop_back(),q.pop_back();
	if(sz(q)<3)return v;c.pb(isp(q.front(),q.back()));
	rep(i,0,sz(c))if(!sz(v)||!(c[i]==v.back()))v.pb(c[i]);
	if(v.front()==v.back())v.pop_back();return v;}


/*
void delauny_triangulation(int l,int r,vector<vec>& v,vector<vector<int> >& u)
{
	if(r-l<=2){rep(i,l,r)repb(j,l,r)if(i!=j)u[i].pb(j);return;}
	int m=(l+r)>>1,lid=l,rid=r,pl,pr,op;
	delauny_triangulation(l,m,v,u);delauny_triangulation(m+1,r,v,u);
	
	for(;pl!=lid||pr!=rid;){
		for(auto nlid:u[lid]){
			op=judge(v[lid],v[nlid],v[rid]);
			if(op==1||(op==0&&(v[nlid]-v[rid]).len<(v[lid]-v[rid]).len)){
				pl=lid;lid=nlid;break;}}
		for(auto nrid:u[rid]){
			op=judge(v[lid],v[nrid],v[rid]);
			if(op==1||(op==0&&(v[nrid]-v[lid]).len<(v[rid]-v[lid]).len)){
				pr=rid;rid=nrid;break;}}}
	for(pl=pr=0;pl!=lid||pr!=rid;){	
		for(auto nlid:u[lid]{
			if(judge(v[lid],v[nlid],v[rid])==-1&&
				(!op||in_circle(v[lid],v[op],v[rid],v[nlid])))op=nlid;}
		for(auto nrid:u[rid]){
			if(judge(v[lid],v[nrid],v[rid])==-1&&
				(!op||in_circle(v[lid],v[op],v[rid],v[nrid])))op=nrid;}
		if(!op)break;
	}
		
}

void delauny_triangulation(vector<vec> v)
{
	sort(all(v));
	vector<vector<int> > u;u.resize(sz(v));
	delauny_triangulation(0,sz(v)-1,v,u);
}
*/

//guaranteed outer|5 vec|c.r<C.r
vector<vec> circle_tangent(cir c,cir C){
	db a=(C.o-c.o).ang;
	db t=asin((C.r-c.r)/(c.o-C.o).len);
	vector<vec> v;
	v.pb(c.o+vec(a-t-0.5*pi,c.r,1));
	v.pb(C.o+vec(a-t-0.5*pi,C.r,1));
	v.pb(c.o+vec(a+t+0.5*pi,c.r,1));
	v.pb(C.o+vec(a+t+0.5*pi,C.r,1));
	v.pb(vec((c.r*C.o.x+C.r*c.o.x),(c.r*C.o.y+C.r*c.o.y))/(c.r+C.r));
	return v;}

int main(){
	cin.sync_with_stdio(false);cin.tie(0);
	cout<<fixed;cout.precision(10);}