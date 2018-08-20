import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;

public class Main {
	public static int scale=50;
	public static int mode=BigDecimal.ROUND_HALF_DOWN;
	public static BigDecimal zero=BigDecimal.ZERO;
	public static BigDecimal one=BigDecimal.ONE;
	public static BigDecimal two=one.add(one);
	public static BigDecimal ten=BigDecimal.TEN;
	public static BigDecimal eps=one.divide(new BigDecimal("1e40"),scale,mode);
	public static BigDecimal pi=gen_pi();
	public static Scanner sc = new Scanner(System.in);
	public static PrintWriter pt = new PrintWriter(System.out);
	public static DecimalFormat df = new DecimalFormat(".00000000");
	
	public static BigDecimal sq(BigDecimal n) {return n.multiply(n);}
	public static BigDecimal min(BigDecimal a,BigDecimal b) {if(a.compareTo(b)==1)return b;return a;}
	public static BigDecimal max(BigDecimal a,BigDecimal b) {if(a.compareTo(b)==1)return a;return b;}
	public static int sgn(BigDecimal b) {return b.compareTo(eps);}
	
	public static BigDecimal gen_pi() {
		BigDecimal r=zero;
		for(int i=0;i<40;++i) {
			r=r.add((
					two.multiply(two).divide(BigDecimal.valueOf(8*i+1),scale,mode).subtract(
					two.divide(BigDecimal.valueOf(8*i+4),scale,mode)).subtract(
					one.divide(BigDecimal.valueOf(8*i+5),scale,mode)).subtract(
					one.divide(BigDecimal.valueOf(8*i+6),scale,mode))
					).divide(two.pow(4*i),scale,mode));}
		return r;}
	
	public static BigDecimal fpow(BigDecimal n,int p) {
		BigDecimal r=one;
		for(;p!=0;p/=2) {if(p%2==1)r=r.multiply(n);n=n.multiply(n);}
		return r;}
	
	public static BigDecimal sqrt(BigDecimal n) {
		BigDecimal r=n;
		for(int i=0;i<80;++i) {
			if(r.compareTo(zero)==0)break;
			r=r.add(n.divide(r,scale,mode)).divide(two,scale,mode);}
		return r;}
	
	public static BigDecimal asin(BigDecimal x) {
		int op=x.signum();
		x=x.divide(ten,scale,mode);
		x=sqrt((one.subtract(sqrt(one.subtract(sq(ten.multiply(x)))))).divide(two,scale,mode));
		BigDecimal ans=x,ud=x,x2=x.multiply(x);
		for(int i=1;i<320;i+=2) {
			ud=ud.multiply(BigDecimal.valueOf(i)).multiply(x2);
			ud=ud.divide(BigDecimal.valueOf(i+1),scale,mode);
			ans=ans.add(ud.divide(BigDecimal.valueOf(i+2),scale,mode));}
		ans=ans.multiply(two);
		if(op==-1)return ans.negate();
		return ans;}
	
	public static BigDecimal acos(BigDecimal x) {return pi.divide(two,scale,mode).subtract(asin(x));}
	
	public static class vec3{
		public vec3() {}
		public vec3(BigDecimal _x,BigDecimal _y,BigDecimal _z) {x=_x;y=_y;z=_z;}
		BigDecimal x,y,z;}
	public vec3 add(vec3 a,vec3 b) {return new vec3(a.x.add(b.x),a.y.add(b.y),a.z.add(b.z));}
	public vec3 sub(vec3 a,vec3 b) {return new vec3(a.x.subtract(b.x),a.y.subtract(b.y),a.z.subtract(b.z));}
	public vec3 mul(vec3 a,BigDecimal b) {return new vec3(a.x.multiply(b),a.y.multiply(b),a.z.multiply(b));}
	public vec3 div(vec3 a,BigDecimal b) {
		return new vec3(a.x.divide(b,scale,mode),a.y.divide(b,scale,mode),a.z.divide(b,scale,mode));}
	public vec3 norm(vec3 a,vec3 b) {vec3 n=sub(b,a);n=div(n,len(n));return n;}
	public vec3 det(vec3 a,vec3 b) {return new vec3(a.y.multiply(b.z).subtract(a.z.multiply(b.y)),
													a.z.multiply(b.x).subtract(a.x.multiply(b.z)),
													a.x.multiply(b.y).subtract(a.y.multiply(b.x)));}	
	public BigDecimal dot(vec3 a,vec3 b) {return a.x.multiply(b.x).add(a.y.multiply(b.y)).add(a.z.multiply(b.z));}
	public BigDecimal len(vec3 a) {return sqrt((a.x.multiply(a.x)).add(a.y.multiply(a.y)).add(a.z.multiply(a.z)));}
	public BigDecimal dis(vec3 a,vec3 b,vec3 c) {return len(det(sub(a,c),sub(b,c))).divide(len(sub(a,b)),scale,mode);}

	public static class vec{
		public vec(){}
		public vec(BigDecimal _x,BigDecimal _y){x=_x;y=_y;}
		BigDecimal x,y;}
	public vec add(vec a,vec b) {return new vec(a.x.add(b.x),a.y.add(b.y));}
	public vec sub(vec a,vec b) {return new vec(a.x.subtract(b.x),a.y.subtract(b.y));}
	public vec mul(vec a,BigDecimal b) {return new vec(a.x.multiply(b),a.y.multiply(b));}
	public vec div(vec a,BigDecimal b) {return new vec(a.x.divide(b,scale,mode),a.y.divide(b,scale,mode));}
	public BigDecimal dot(vec a,vec b) {return a.x.multiply(b.x).add(a.y.multiply(b.y));}
	public BigDecimal det(vec a,vec b) {return a.x.multiply(b.y).subtract(a.y.multiply(b.x));}
	public BigDecimal len(vec a) {return sqrt(dot(a,a));}
	public BigDecimal dis(vec a,vec b,vec c) {return det(sub(a,c),sub(b,c)).abs().divide(len(sub(b,a)));}
	
	Main(){}
	
	public static void main(String[] args) throws Exception{
		new Main();sc.close();pt.close();}}
