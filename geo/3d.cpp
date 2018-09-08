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
typedef complex<double> cpd;
typedef db(*func)(db x);

const int inf = 0x3f3f3f3f;
const ll infl = 4557430888798830399ll;
const db infd = 1./0.;
const db eps = 1e-9;
const db pi = acos(-1.);
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

bool cramer(mat a,vector<db>& c,vector<db>& x){
	db da=det(a);mat t;x.clear();
	rep(i,0,sz(a)){
		t=a;rep(j,0,sz(a))t[j][i]=c[j];x.pb(det(t)/da);}
	return sz(x)==sz(a);}

vector<db> quadratic(db& a,db& b,db& c){
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

struct vec{vec(){}
    vec(int O){cin>>x>>y>>z;len=hypot(hypot(x,y),z);t=0.;if(sgn(len))t=acos(z/len);p=atan2(y,x);}
    vec(db X,db Y,db Z):x(X),y(Y),z(Z),len(hypot(hypot(X,Y),Z)){
    	t=0.;if(sgn(len))t=acos(z/len);p=atan2(y,x);}
    vec(db T,db P,db R,int o):
		x(R*sin(T)*cos(P)),y(R*sin(T)*sin(P)),z(R*cos(T)),len(R),t(T),p(P){};
    vec operator-(){return vec(-x,-y,-z);}
    vec operator+(vec v){return vec(x+v.x,y+v.y,z+v.z);}
    vec operator-(vec v){return vec(x-v.x,y-v.y,z-v.z);}
    vec operator^(vec v){return vec(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);}
    vec operator*(db c){return vec(x*c,y*c,z*c);}
    vec operator/(db c){return vec(x/c,y/c,z/c);}
    db operator*(vec v){return x*v.x+y*v.y+z*v.z;}
    bool operator<(const vec& v)const{
		return sgn(v.x-x)==1||(sgn(v.x-x)==0&&sgn(v.y-y)==1)||
		(sgn(v.x-x)==0&&sgn(v.y-y)==0&&sgn(v.z-z)==1);}
	bool operator==(const vec& v)const{
		return !sgn(x-v.x)&&!sgn(y-v.y)&&!sgn(z-v.z);}
    vec norm(){assert(sgn(len));return vec(x/len,y/len,z/len);}
    vec trunc(db l){assert(sgn(len));return *this*(l/len);}
    // k is norm
    vec rot(vec k,db t){return (*this)*cos(t)+(k^(*this))*sin(t)+k*(k*(*this))*(1.0-cos(t));}
    db cen_ang(vec v){return acos(cos(t)*cos(v.t)+sin(t)*sin(v.t)*cos(fabs(p-v.p)));}
    db x,y,z,len,t,p;};

struct line{line(){}
	line(vec a,vec b):s(a),t(b),d((b-a).norm()){}
	bool cop(line l){return !sgn(((t-s)^(l.t-s))*(l.s-s));}
	db dis(vec p){return ((s-p)^(t-p)).len/(s-t).len;}
	vec proj(vec p){return p+(d^((s-p)^(t-p)))/(s-t).len;}
	bool on(vec p){return !sgn(dis(p))&&sgn((s-p)*(t-p))!=1;}
	vec s,t,d;};

struct plane{plane(){}
	plane(vec A,vec B,vec C):a(A),b(B),c(C){d=((B-A)^(C-A)).norm();h=d*a;}//(p-a)*d=0
	plane(vec A,vec P):a(A),d(P.norm()),h(P.norm()*A){
		vector<vec> v;
		if(sgn(d.x))v.pb(vec(h/d.x,0.,0.));else v.pb(vec(A.x-1.,A.y,A.z));
		if(sgn(d.y))v.pb(vec(0.,h/d.y,0.));else v.pb(vec(A.x,A.y-1.,A.z));
		if(sgn(d.z))v.pb(vec(0.,0.,h/d.z));else v.pb(vec(A.x,A.y,A.z-1.));
		rep(i,0,2)if(v[i]==A)swap(v[i],v[2]);b=v[0];c=v[1];}
	db dis(vec p){return fabs(((a-p)^(b-p))*(c-p))/((b-a)^(c-a)).len;}
	vec proj(vec p){return p+d*(((a-p)^(b-p))*(c-p)/((b-a)^(c-a)).len);}
	bool on(vec p){
		return !sgn(dis(p))&&1<abs(
				sgn(((a-p)^(b-p))*d)+
				sgn(((b-p)^(c-p))*d)+
				sgn(((c-p)^(a-p))*d));}
	vec a,b,c,d;db h;};

struct ball{ball(){}
	ball(db X,db Y,db Z,db R):x(X),y(Y),z(Z),r(R),o(vec(X,Y,Z)),vol(4.*pi*R*R*R/3.),area(4.*pi*R*R){}
	ball(vec O,db R):x(O.x),y(O.y),z(O.z),r(R),o(O),vol(4.*pi*R*R*R/3.),area(4.*pi*R*R){}
	db cap_vol(db h){return pi*h*h*(3.*r-h)/3.;}
	db cap_area(db h){return 2*pi*r*h;}//base area not include
	db x,y,z,r,vol,area;vec o;};

//-1 inf|0 no|1 one
int intersect_point(plane& p,line& l,vec& v){
	vec o=p.proj(l.s);db a=asin((p.d^l.d).len),d=(o-l.s).len/cos(a);
	if(!sgn(a-0.5*pi)){
		if(!sgn(p.dis(l.s)))return -1;return 0;}
	if(!sgn(p.dis(v=l.s+l.d*d)))return 1;
	if(!sgn(p.dis(v=l.s-l.d*d)))return 1;}

int intersect_point(line& p,line& q,vec& v){
	if(!sgn(1.-sq(p.d*q.d))){
		if(!sgn(p.dis(q.s)))return -1;return 0;}
	if(!p.cop(q))return 0;
	mat a={{p.d.x,-q.d.x,1.},{p.d.y,-q.d.y,1.},{p.d.z,-q.d.z,1.}};
	vector<db> t,y={q.s.x-p.s.x,q.s.y-p.s.y,q.s.z-p.s.z};
	cramer(a,y,t);v=p.d*t[0]+p.s;return 1;}

int intersect_line(plane& p,plane& q,line& l){
	if(!sgn(1.-sq(p.d*q.d))){
		if(!sgn(p.dis(q.a)))return -1;return 0;}
	db cp=(p.h-q.h*(p.d*q.d))/(1.-sq(p.d*q.d));
	db cq=(q.h-p.h*(p.d*q.d))/(1.-sq(p.d*q.d));
	vec o=(p.d*cp)+(q.d*cq),d=p.d^q.d;
	l=line(o,o+d);return true;}

int main(){
	cin.sync_with_stdio(false);cin.tie(0);
	cout<<fixed;cout.precision(10);}