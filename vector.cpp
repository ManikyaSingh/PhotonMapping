#ifndef _VECTOR_SIMPLE_INCLUDED_
#define _VECTOR_SIMPLE_INCLUDED_

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
	Vector(double d){
		x = y = z = d;
	}
	Vector(const Vector& v){
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector(Matrix <3,1> M){
		x = M.val[0][0];
		y = M.val[1][0];
		z = M.val[2][0];
	}
	Vector(Matrix <4,1> M){
		x = M.val[0][0];
		y = M.val[1][0];
		z = M.val[2][0];
	}
	Vector operator+(Vector v){
		return Vector(x+v.x,y+v.y,z+v.z);
	}
	Vector operator-(Vector v){
		return Vector(x-v.x,y-v.y,z-v.z);
	}
	Vector operator-(){
		return Vector(-x,-y,-z);
	}
	Vector operator*(double d){
		return Vector(x*d,y*d,z*d);
	}
	
	Vector operator/(double d){
		return Vector(x/d,y/d,z/d);
	}

	double dot(Vector v){
		return (x*v.x + y*v.y + z*v.z);
	}
	double operator^(Vector v){
		return (*this).dot(v);
	}
	double mod(){
		return (x*x)+(y*y)+(z*z);
	}
	double mod2(){
		return sqrt((x*x)+(y*y)+(z*z));
	}
	Vector unit(){
		return (*this)/mod2();
	}
	Vector component(Vector dir){
		double r = (*this)^dir;
		if(r < 0) r = -r;
		return (dir*r)/dir.mod();
	}
	Vector operator/(Vector v){
		return (*this).component(v);
	}
	Vector reflect(Vector n){
		n = ((*this)/n)*2;
		return n + (*this);
	}

	Vector transform(Matrix<3,3> M);
	Vector transform(Matrix<4,4> M);
	Vector operator*(Matrix<3,3> M);
	Vector operator*(Matrix<4,4> M);
	Vector cross(Vector v);
	Vector operator*(Vector v);

	void print(){
		cout<<x<<" "<<y<<" "<<z;
	}

	int operator==(Vector v){
		return(v.x == x && v.y == y && v.z == z);
	}
};

Vector operator*(double d, Vector v){
	return v*d;
}

Vector operator/(double d, Vector v){
	return v/d;
}

// Matrix <3,1> operator=(Matrix& <3,1> M, Vector v){
// 	M.val[0][0] = v.x;
// 	M.val[1][0] = v.y;
// 	M.val[2][0] = v.z;
// 	return M;
// }


// Vector Vector::transform(Matrix<3,3> M){
// 	Matrix <3,1> m = (*this);
// 	return *this;
// }

#endif