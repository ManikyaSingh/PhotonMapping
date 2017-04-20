#include <math.h>
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

#ifndef NULL
#define NULL 0
#endif

#include "math.cpp"
#include "graphics.cpp"

#define BG_RED 0
#define BG_GREEN 0
#define BG_BLUE 0



void bitmap(Color **c, int w, int h, string fileName)
{
	ofstream outfile;
	outfile.open(fileName);
	outfile<<"P3\n"<<w<<" "<<h<<"\n255\n";

	for(int i=h-1;i>=0;i--){
		for(int j=0;j<w;j++){
			if(c[i][j].a < 0){
				c[i][j].r = BG_RED;
				c[i][j].g = BG_GREEN;
				c[i][j].b = BG_BLUE;
			}
			outfile<<(int)c[i][j].r<<" "<<(int)c[i][j].g<<" "<<(int)c[i][j].b<<" ";
		}
		outfile<<endl;
	}
	outfile.close();
}

int main(){
	Vector i = Vector(1,0,0);
	Vector n = Vector(-1,0,0);
	Vector r = i.refract(n,2);
	cout<<endl;

	cout<<endl;
	i = Vector(-10,10,10);
	i.unit().print();cout<<endl;
	r = i.refract(n,1.2);
	r.print();
	cout<<endl;

	cout<<"\n--------------------------\n\n";

	Ray ray = Ray(Point(Vector(0,0,0), Color(255,255,255,1)), Vector(1,0.1,0));

	Surface s = Surface();
	s.type = 2;
	SphereParam sp = SphereParam(50,0,0, 25);
 
	s.surfaceFn = &Sphere;

	s.param = (void*)&sp;
	

	Object o = Object();

	rootObject = &o;

	o.surface = &s;
	o.sLen = 1;
	cout<<"\n\n\n\n";
	Vector nrm;
	o.intersect(ray, &nrm).print();
	cout<<"\n\n\n\n";
	nrm.print();
	cout<<"\n\n\n";


	return 0;
}