#ifndef _RAY_SIMPLE_INCLUDED_
#define _RAY_SIMPLE_INCLUDED_

class Ray{
public:
	Point p;
	Vector d;
	Ray(){

	}
	Ray(Point a, Vector b){
		p = a;
		d = b;
	}
	Ray(const Ray& rr){
		p = rr.p;
		d = rr.d;
	}
};

#endif