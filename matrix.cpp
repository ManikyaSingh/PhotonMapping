#ifndef _MATRIX_SIMPLE_INCLUDED_
#define _MATRIX_SIMPLE_INCLUDED_

#include <math.h>
#include <iostream>
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

template <int N, int M>
class Matrix{
public:
	double val[N][M];
	
	Matrix(){
		
	}
	Matrix(double **a){
		Matrix();
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				val[i][j] = a[i][j];
			}
		}
	}
	Matrix(double a[N][M]){
		Matrix();
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
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
				
				for(j=0;j<=M;j++){
					if(j != nj){
						val[li][lj] = a[i][j];
						lj++;
					}	
				}
				li++;
			}
		}
	}
	Matrix(double a[N+1][M+1], int ni, int nj){
		Matrix();
		int i,j;
		int li=0;
		int lj=0;
		for(i=0;i<=N;i++){
			if(i != ni){
				lj = 0;
				for(j=0;j<=M;j++){
					if(j != nj){
						val[li][lj] = a[i][j];
						//cout<<li<<" "<<lj<<" "<<a[i][j]<<"\n";
						lj++;
					}	
				}
				li++;
			}
		}
	}
	Matrix(double d){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				if(i == j) val[i][j] = d;
				else val[i][j] = 0;
			}
		}
	}
	
	Matrix (const Matrix<N,M> &obj) {
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				val[i][j] = obj.val[i][j];
			}
		}
	}
	Matrix(Vector v);
	Matrix(Vector v, int i, int j);

	Matrix<N-1,M-1> slice(int i, int j){
		Matrix <N-1,M-1>r = Matrix<N-1,M-1>(val,i,j);
		return r;
	}
	int set(int i, int j, double v){
		if(i<N && j<M && i>0 && j>0){
			val[i][j] = v;
			return 1;
		}
		return 0;
	}
	Matrix<N,M> operator+(Matrix<N,M> b){
		Matrix<N,M> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]+b.val[i][j];
			}
		}
		return r;
	}
	Matrix<N,M> operator-(Matrix<N,M> b){
		Matrix<N,M> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]-b.val[i][j];
			}
		}
		return r;
	}
	Matrix<N,M> operator*(double b){
		Matrix<N,M> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]*b;
			}
		}
		return r;
	}
	Matrix<N,M> operator/(double b){
		Matrix<N,M> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = val[i][j]/b;
			}
		}
		return r;
	}
	Matrix<N,M> operator-(){
		Matrix<N,M> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[i][j] = -val[i][j];
			}
		}
		return r;
	}
	Matrix<N,M> operator+(){
		return *this;
	}
	double mod();
	Matrix<M,N> transpose(){
		Matrix<M,N> r;
		int i,j;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				r.val[j][i] = val[i][j];
			}
		}
		return r;
	}
	Matrix<M,N> operator~(){
		return (*this).transpose();
	}
	void print(){
		int i,j;
		
		for(i=0;i<N;i++){
			cout<<endl;
			for(j=0;j<M;j++){
				cout<<val[i][j]<<" ";
			}
		}
		cout<<endl;
	}
};

template <int N, int M, int L>
Matrix<N,L> operator*(Matrix<N,M> A, Matrix<M,L> B){
	Matrix <N,L> r;
	int n,m,l;
	for(n=0;n<N;n++){
		for(l=0;l<L;l++){
			r.val[n][l] = 0;
			for(m=0;m<M;m++){
				r.val[n][l] += A.val[n][m]*B.val[m][l];
			}
		}
	}
	return r;
}

template <int N, int M>
Matrix<N,M> operator*(double b, Matrix<N,M> a){
	Matrix<N,M> r;
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			r.val[i][j] = a.val[i][j]*b;
		}
	}
	return r;
}

template <int N, int M>
Matrix<N,M> operator/(double b, Matrix<N,M> a){
	Matrix<N,M> r;
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			r.val[i][j] = a.val[i][j]/b;
		}
	}
	return r;
}


template <int N, int M>
double Matrix<N,M>::mod(){
	double r = 0;
	for(int i=0;i<N;i++){
		Matrix<N-1,M-1> tmp = slice(0,i);

		
		if(i%2) r -= val[0][i]*tmp.mod();
		else r += val[0][i]*tmp.mod();
		
		
	}
	return r;
}

template <>
double Matrix<1,1>::mod(){

	return val[0][0];
}

#endif