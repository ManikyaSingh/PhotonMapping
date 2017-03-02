#include "math.cpp"
#include "graphics.cpp"
#include <math.h>
#include <iostream>
using namespace std;

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
	v[2][2] = 8;
	


	Matrix<3,3> r = Matrix<3,3>(v);

	Matrix <3,2> s = 1;

	r.print();
	s.print();




	(r*s).print();
	cout<<r.mod();



	Vector v1(1,1,1);

	cout<<endl;
	v1.print();
	cout<<endl;

	Vector v2(1,1,-1);

	cout<<endl;
	v2.print();
	cout<<endl;

	cout<<endl<<endl;
	(v1*v2).print();
	cout<<endl;
	(v2*v1).print();
	cout<<endl<<endl<<endl;

	Vector i = Vector(1,1,0);
	Vector n = Vector(0,0,1);
	Vector r2 = i.reflect(n);

	i.print();
	cout<<endl;
	n.print();
	cout<<endl;
	r2.print();
	cout<<endl<<endl;

	i = Vector(1,1,0);
	n = Vector(0,-1,0);
	Vector rb = i/n;
	r2 = i.reflect(n);

	i.print();
	cout<<endl;
	n.print();
	cout<<endl;
	rb.print();
	cout<<endl;
	(rb*2).print();
	cout<<endl;
	r2.print();
	cout<<endl;
	
	return 0;
}