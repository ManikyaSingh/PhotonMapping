#ifndef _MATH_SIMPLE_INCLUDED_
#define _MATH_SIMPLE_INCLUDED_

class Vector;

template <int N, int M>
class Matrix;

#include "matrix.cpp"
#include "vector.cpp"


template <int N, int M>
Matrix<N,M>::Matrix(Vector v, int i, int j){
	int n = N;
	int m = M;
	if(n >= 3+i){
		if(m >= 3+j){
			val[i+0][j+0] = v.x;
			val[i+1][j+1] = v.y;
			val[i+2][j+2] = v.z;
		}else{
			val[i+0][0] = v.x;
			val[i+1][0] = v.y;
			val[i+2][0] = v.z;
			if(n >= 4+i){
				val[i+3][0] = 1;
			}
		}
	}else{
		if(m >= 3+j){
			val[0][j+0] = v.x;
			val[1][j+1] = v.y;
			val[2][j+2] = v.z;
			if(m >= 4+j) val[0][j+3] = 1;
		}
	}
}

template <int N, int M>
Matrix<N,M>::Matrix(Vector v){
	val[0][0] = v.x;
	val[1][0] = v.y;
	val[2][0] = v.z;
	if(N == 4) val[3][0] = 1;
}

Vector Vector::transform(Matrix<3,3> M){
	Matrix <3,1> r = (*this);
	
	r = M*r;

	return r;
}

Vector Vector::operator*(Matrix<3,3> M){
	return transform(M);
}

Vector Vector::transform(Matrix<4,4> M){
	Matrix <4,1> r = (*this);
	r.print();
	r = M*r;
	return r;
}

Vector Vector::operator*(Matrix<4,4> M){
	return transform(M);
}

Vector Vector::cross(Vector v){
	Matrix <3,3> m = 0.0;
	m.val[0][1] = v.z;
	m.val[0][2] = -v.y;
	m.val[1][0] = -v.z;
	m.val[1][2] = v.x;
	m.val[2][0] = v.y;
	m.val[2][1] = -v.x;

	Matrix <3,1> n = (*this);
	
	return (*this)*m;
}

Vector Vector::operator*(Vector v){
	return cross(v);
}

#include "color.cpp"

#endif