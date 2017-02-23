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
	double val[N][N];
	Matrix(){
		
	}
	Matrix(double **a){
		Matrix();
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				val[i][j] = a[i][j];
			}
		}
	}
	Matrix(double a[N][N]){
		Matrix();
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				val[i][j] = a[i][j];
			}
		}
	}
	Matrix(double **a, int ni, int nj){
		Matrix();
		int i,j;
		int li=0;
		int lj=0;
		for(i=0;i<=N;i++){
			if(i != ni){
				
				for(j=0;j<=N;j++){
					if(j != nj){
						val[li][lj] = a[i][j];
						lj++;
					}	
				}
				li++;
			}
		}
	}
	Matrix(double a[N+1][N+1], int ni, int nj){
		Matrix();
		int i,j;
		int li=0;
		int lj=0;
		for(i=0;i<=N;i++){
			if(i != ni){
				lj = 0;
				for(j=0;j<=N;j++){
					if(j != nj){
						val[li][lj] = a[i][j];
						cout<<li<<" "<<lj<<" "<<a[i][j]<<"\n";
						lj++;
					}	
				}
				li++;
			}
		}
	}
	Matrix<N-1> slice(int i, int j){
		Matrix <N-1>r = Matrix<N-1>(val,i,j);
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
	double mod();
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


template <int N>
double Matrix<N>::mod(){
	double r = 0;
	for(int i=0;i<N;i++){
		Matrix<N-1> tmp = slice(0,i);

		printf("%2f * (",val[0][i]);
		if(i%2) r -= val[0][i]*tmp.mod();
		else r += val[0][i]*tmp.mod();
		printf(") ");
		
	}
	return r;
}
template <>
double Matrix<1>::mod(){
	printf("%2f",val[0][0]);
	return val[0][0];
}



int main(){
	double v[3][3];
	v[0][0] = 1;
	v[0][1] = 2;
	v[0][2] = 3;
	v[1][0] = 4;
	v[1][1] = 5;
	v[1][2] = 6;
	v[2][0] = 7;
	v[2][1] = 8;
	v[2][2] = 9;
	
	Matrix<3> r = Matrix<3>(v);

	cout<<endl;
	Matrix<2> tmp = Matrix<2>(v,0,0);
	for(int j=0;j<2;j++){
		for(int k=0;k<2;k++)
			printf("%f ", tmp.val[j][k]);
		printf("\n");
	}
	cout<<endl<<"---"<<endl;

	cout<<endl;
	tmp = Matrix<2>(v,0,1);
	for(int j=0;j<2;j++){
		for(int k=0;k<2;k++)
			printf("%f ", tmp.val[j][k]);
		printf("\n");
	}
	cout<<endl<<"---"<<endl;

	cout<<endl<<r.mod();
	printf("\na\n");
	cout<<endl<<compare(r.mod(), 0);
	return 0;
}