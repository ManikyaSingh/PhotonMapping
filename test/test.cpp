#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;

double EPS = ldexp (0.5 , -40);

int compare(double a, double b) {
	double c = a-b;
	double d = c;
	if(c<0) c *= -1;
	
	double param, result;
	int n;

	if(c < EPS && c > -EPS){
		return 0;
	}else if(d<0){
		return -1;
	}else if(d>0){
		return 1;
	}

	return 0;
}


int roots(double a, double b, double c, double *r1, double *r2){
	if(compare(a,0) == 0){
		if(compare(b,0) == 0) return 0;
		*r1 = -c/b;
		return 1;
	}
	double d = b*b - 4*a*c;
	int x = compare(d,0);
	if(x<0) return 0;
	if(x == 0){
		a *= 2;
		b /= a;
		*r1 = *r2 = -b;
		return 1;
	}
	d = sqrt(d);
	a *= 2;
	*r1 = -(b + d)/a;
	*r2 = -(b - d)/a;
	return 2;
}

template <int N>
class Matrix{
public:
	double **val;
	Matrix(){
		val = new double*[N];
		for(int i=0;i<N;i++){
			val[i] = new double[N];
		}
	}
	Matrix(double a[N][N]){
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				val[i][j] = a[i][j];
			}
		}
	}
	Matrix(double **a, int ni, int nj){
		int i,j;
		int li=0;
		int lj;
		for(i=0;i<N;i++){
			lj=0;
			if(i == ni) li++;
			else for(j=0;j<N;j++){
				if(j == nj) lj++;
				else val[i][j] = a[i+li][j+lj];
			}
		}
	}
	Matrix<N-1> slice(int i, int j){
		Matrix <N-1>r = Matrix(val,i,j);
		return r;
	}
	int set(int i, int j, double v){
		if(i<N && j< N && i>0 && j>0){
			val[i][j] = v;
			return 1;
		}
		return 0;
	}
	Matrix<N> operator+(Matrix<N> b){
		Matrix<N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]+b.val[i][j];
			}
		}
		return r;
	}
	Matrix<N> operator-(Matrix<N> b){
		Matrix<N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]-b.val[i][j];
			}
		}
		return r;
	}
	Matrix<N> operator*(double b){
		Matrix<N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]*b;
			}
		}
		return r;
	}
	Matrix<N> operator/(double b){
		Matrix<N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]/b;
			}
		}
		return r;
	}
	Matrix<N> operator-(){
		Matrix<N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = -val[i][j];
			}
		}
		return r;
	}
	double mod(){
		if(N == 1){
			return val[0][0];
		}
		double r = 0;
		for(int i=0;i<N;i++){
			Matrix <N-1> tmp = Matrix();
			if(i%2) r -= val[0][i]*(slice(0,i).mod());
			else r += val[0][i]*(slice(0,i).mod());
		}
	}
};

template <int N>
Matrix<N> operator*(double b, Matrix<N> a){
	Matrix<N> r;
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			r.val[i][j] = a.val[i][j]*b;
		}
	}
	return r;
}

template <int N>
Matrix<N> operator/(double b, Matrix<N> a){
	Matrix<N> r;
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			r.val[i][j] = a.val[i][j]/b;
		}
	}
	return r;
}

class Color{
public:
	unsigned char r;//0 to 255
	unsigned char g;//0 to 255
	unsigned char b;//0 to 255
	char a = 100;//-128 to 127 (0 to 100 rest special cases)
};

class Vector{
public:
	double x;
	double y;
	double z;
	Vector(){

	}
	Vector(double _x, double _y, double _z){
		x = _x;
		y = _y;
		z = _z;
	}
	Vector operator=(const Vector& v){
		x = v.x;
		y = v.y;
		z = v.z;
		return v;
	}
	Vector operator=(const double& d){
		x = y = z = d;
		return *this;
	}
	Vector operator+(Vector v){
		return Vector(v.x+x,v.y+y,v.z+z);
	}
	Vector operator-(Vector v){
		return (*this)+(-v);
	}
	Vector operator-(){
		return Vector(-x,-y,-z);
	}
	int operator==(const Vector& v){
		if(x == v.x && y == v.y && z == v.z){
			return 1;
		}else{
			return 0;
		}
	}
	int operator==(const int& a){
		if(x == y && y == z && z == a) return 1;
		else return 0;
	}
	double dot(const Vector& v){
		return x*v.x+y*v.y+z*v.z;
	}
	double operator*(const Vector& v){
		return x*v.x+y*v.y+z*v.z;
	}
	double operator*(const double& d){
		return Vector(d*x,d*y,d*z);
	}
	double operator/(const double& d){
		return Vector(x/d,y/d,z/d);
	}
	double mod(){
		return x*x + y*y + z*z;
	}
	operator double(){
		return x*x + y*y + z*z;
	}
	Vector unit(){
		double m = *this;
		m = sqrt(m);
		Vector v = Vector(x/m,y/m,z/m);
		return v;
	}
	Vector reflect(Vector n){
		Vector i = (*this).unit();
		n = n.unit();
		n = (((double)(i))*(double(n))*2)*n;
		n = n/((double)(i*n));
		n = n + (i);
		return -n;
	}
};
Vector operator*(const double& d, const Vector& v){
	return Vector(d*v.x,d*v.y,d*v.z);
}
Vector operator/(const double& d, const Vector& v){
	return Vector(v.x/d,v.y/d,v.z/d);
}

class Point{
public:
	Vector v;
	Color color;
};

class Ray{
public:
	Vector start;
	Vector dir;
};

class Object{
	Point (*surface)(Vector v, Vector dir, char *arg[]);
};

void printBits(double decker){
    unsigned char * desmond = (unsigned char *) & decker;
    int i;

    for (i = 0; i < sizeof (double); i++) {
         printf ("%02X ", desmond[i]);
    }
    printf ("\n");
}



Vector intersection(Point (*surface)(Vector v, Vector dir, char *arg[]), Ray r, char *arg[]){
/*

*/
}

Point sphere(Vector v, Vector dir, char *arg[]){
// if(v.x > 0) v.x -= 5*sin(v.y/25);
// if(v.x <= 0) v.x += 5*sin(v.y/25);
	v.y -= 0;
	// double tmp = v.x;
	v.x -= 15*cos((v.y)/25);

	
	v.z -= 0;
	;

	Point p;
	p.v.x = p.v.y = p.v.z = 0;
	p.color.r = p.color.g = p.color.b = 255;

	int act = 0;

	if(dir == 0){
		//point on curve
		act = 1;
	}else{
		if(v == 0){
			//normal
			act = 2;
			if(arg != NULL){
				if(arg[0] != NULL){
					if(strcmp(arg[0], "ray") == 0){
						act = 0;
					}
				}
			}
			if(act){
				v = dir;
				dir = 0;
			}
			
		}else{
			//ray
			act = 0;
		}
	}
	
	double rhs = 2500;
	if(act){
		//point on curve
		double lhs = (double)v;
		

		if(compare(lhs, rhs) == 0){
			//point on curve
			p.v = v;
			p.color.r = p.color.g = p.color.b = 255;
		}else{
			//point not on curve
			if(act == 1) p.color.a = -1;
			else{
				act = 0;
				dir = v;
				v = 0;
			}
		}
		if(act == 2) p.color.a = 0;
	}
	if(!act){
		//ray
		//find poi in direction
		double r1,r2;
		int r = roots((double)dir , 2*(v*dir), (double)v - rhs, &r1, &r2);
		if(r == 0){
			p.color.a = -1;
		}else if(r == 1){
			p.v = v + r1*dir;
			if(p.v > v){
				p.color.r = p.color.g = p.color.b = 255;
			}else{
				p.color.a = -1;
			}
		}else{
			p.color.a = 100;
			if(compare(r1,0) > 0){
				if(compare(r2,0) > 0){
					if(r1 > r2) r1 = r2;
				}else{
					//r1 >0 , r2<0
				}
			}else{
				if(compare(r2,0) > 0){
					r1 = r2;
				}else{
					p.color.a = -1;
				}
			}
			p.v = v + r1*dir;

		}
	}
	p.color.r = p.color.g = p.color.b = 50;
	if(p.v.x > 0){
		p.color.r = 255;
	}
	if(p.v.y > 0){
		p.color.g = 255;
	}
	if(p.v.z > 0){
		p.color.b = 255;
	}
	
	//printf("\n%f %f %f %d\n",p.v.x,p.v.y,p.v.z,p.color.a);
	return p;
	
}


Point mirrorSphere(Vector v, Vector dir, char *arg[]){

	v.x -= 50;
	v.y -= 50;
	v.z -= 0;
	Point p;
	p.v.x = p.v.y = p.v.z = 0;
	p.color.r = p.color.g = p.color.b = 255;

	int act = 0;

	if(dir == 0){
		//point on curve
		act = 1;
	}else{
		if(v == 0){
			//normal
			act = 2;
			if(arg != NULL){
				if(arg[0] != NULL){
					if(strcmp(arg[0], "ray") == 0){
						act = 0;
					}
				}
			}
			if(act){
				v = dir;
				dir = 0;
			}
			
		}else{
			//ray
			act = 0;
		}
	}
	
	double rhs = 2500;
	if(act){
		//point on curve
		double lhs = (double)v;
		

		if(compare(lhs, rhs) == 0){
			//point on curve
			p.v = v;
			p.color.r = p.color.g = p.color.b = 255;
		}else{
			//point not on curve
			if(act == 1) p.color.a = -1;
			else{
				act = 0;
				dir = v;
				v = 0;
			}
		}
		if(act == 2) p.color.a = 0;
	}
	if(!act){
		//ray
		//find poi in direction
		double r1,r2;
		int r = roots((double)dir , 2*(v*dir), (double)v - rhs, &r1, &r2);
		if(r == 0){
			p.color.a = -1;
		}else if(r == 1){
			p.v = v + r1*dir;
			if(p.v > v){
				Vector n = p.v;
				n.x += 100;
				Point tmp = sphere(p.v,-dir.reflect(n),NULL);
				p.color.r = tmp.color.r;
				p.color.g = tmp.color.g;
				p.color.b = tmp.color.b;
				p.color.a = tmp.color.a;
				if(p.color.a <= 0){
					p.color.a = 100;
					p.color.r = 200;
					p.color.g = 200;
					p.color.b = 200;
				}
			}else{
				p.color.a = -1;
			}
		}else{
			p.color.a = 100;
			if(compare(r1,0) > 0){
				if(compare(r2,0) > 0){
					if(r1 > r2) r1 = r2;
				}else{
					//r1 >0 , r2<0
				}
			}else{
				if(compare(r2,0) > 0){
					r1 = r2;
				}else{
					p.color.a = -1;
				}
			}
			p.v = v + r1*dir;
			if(p.color.a != -1){
				Vector n = p.v;
				n.x += 100;
				Point tmp = sphere(p.v,-dir.reflect(n),NULL);
				p.color.r = tmp.color.r;
				p.color.g = tmp.color.g;
				p.color.b = tmp.color.b;
				p.color.a = tmp.color.a;
				if(p.color.a <= 0){
					p.color.a = 100;
					p.color.r = 200;
					p.color.g = 200;
					p.color.b = 200;
				}
			}
		}
	}
	//printf("\n%f %f %f %d\n",p.v.x,p.v.y,p.v.z,p.color.a);
	return p;
	
}

Point planeMirror(Vector v, Vector dir, char *arg[]){

	Point p;
	p.v.x = p.v.y = p.v.z = 0;
	p.color.r = p.color.g = p.color.b = 255;

	int act = 0;

	if(dir == 0){
		//point on curve
		act = 1;
	}else{
		if(v == 0){
			//normal
			act = 2;
			if(arg != NULL){
				if(arg[0] != NULL){
					if(strcmp(arg[0], "ray") == 0){
						act = 0;
					}
				}
			}
			if(act){
				v = dir;
				dir = 0;
			}
			
		}else{
			//ray
			act = 0;
		}
	}
	
	double rhs = 60;
	if(act){
		//point on curve
		double lhs = v.y+v.z-v.x;
		

		if(compare(lhs, rhs) == 0){
			//point on curve
			p.v = v;
			p.color.r = p.color.g = p.color.b = 255;
		}else{
			//point not on curve
			if(act == 1) p.color.a = -1;
			else{
				act = 0;
				dir = v;
				v = 0;
			}
		}
		if(act == 2) p.color.a = 0;
	}
	if(!act){
		//ray
		//find poi in direction
		double r1,r2;
		int r = roots(0 , dir.z+dir.y-dir.x, rhs+v.x-v.y-v.z, &r1, &r2);
		if(r == 0){
			p.color.a = -1;
		}else if(r == 1){
			p.v = v + r1*dir;
			if(p.v > v){
				Vector n = Vector(1,-1,-1);
				Point tmp = sphere(p.v,-dir.reflect(n),NULL);
				p.color.r = tmp.color.r;
				p.color.g = tmp.color.g;
				p.color.b = tmp.color.b;
				p.color.a = tmp.color.a;
				if(p.color.a <= 0){
					p.color.a = 100;
					p.color.r = 200;
					p.color.g = 200;
					p.color.b = 200;
				}
			}else{
				p.color.a = -1;
			}
		}else{
			p.color.a = -1;
		}
	}
	//printf("\n%f %f %f %d\n",p.v.x,p.v.y,p.v.z,p.color.a);
	return p;
	
}


int project(Color **c, int w, int h, int d, Vector Cam, Point (*surface)(Vector v, Vector dir, char *arg[])){
	int i,j;
	Color col;
	Vector v;
	cout<<"<!DOCTYPE html><html><body><svg width='"<<w*2+2<<"' height='"<<h*2+2<<"' style='background:#000;'>";
	for(i=-w;i<=w;i++){
		for(j=-h;j<=h;j++){
			v = Vector(i,j,d);


			col = mirrorSphere(v,v-Cam,NULL).color;
			if((int)col.a != -1)
			cout<<"<rect x='"<<w+i<<"' y='"<<w+j<<"' width='1' height='1' style='fill:rgba("<<(int)col.r<<","<<(int)col.g<<","<<(int)col.b<<","<<(int)col.a<<");stroke-width:0;' />";


			col = (*surface)(v,v-Cam,NULL).color;
			if((int)col.a != -1)
			cout<<"<rect x='"<<w+i<<"' y='"<<w+j<<"' width='1' height='1' style='fill:rgba("<<(int)col.r<<","<<(int)col.g<<","<<(int)col.b<<","<<(int)col.a<<");stroke-width:0;' />";

			
			
		}
	}
	cout<<"</svg></body></html>";
	return 0;
}


int main(int argc, char *argv[]){
	
	Vector cam = Vector(0, 0, -250);
	//Vector v = Vector(0,0,-10);
	//printf("\n%f %f %f - %f %f %f\n", (v-cam).x,(v-cam).y,(v-cam).z, v.x, v.y, v.z);
	//sphere(v,v-cam,NULL);
	project(NULL, 200, 200, -50, cam,&sphere);
	return 0;
}