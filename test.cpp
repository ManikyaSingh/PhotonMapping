#include <math.h>
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

	printf("--------------------------------");

	OTNode root;
	root.p.v.x = 0.1;
	root.p.v.y=0.1;
	root.p.v.z=0.1;
	root.p.p = 1.0;
	root.lb = root.ub = root.p.v;
	root.power = 1;

	root.insert(Photon(0.9, 0.9, 0.9, 1));

	root.print();

	cout<<root.rangeCount(Vector(0,0,0),1.0);

	printf("\n-------------------------------------\n");

	Object o = Object();

	rootObject = &o;

	o.sLen = 7;
	o.oLen = 0;
	
	SphereParam sp = SphereParam(80-500,80-500,500-80,80*80);

	PlaneParam ppB = PlaneParam(0,0,1,500);

	PlaneParam ppL = PlaneParam(-1,0,0,500);
	ppL.c = Color(255,0,0,100);
	PlaneParam ppR = PlaneParam(1,0,0,500);
	ppR.c = Color(0,255,0,100);
	PlaneParam ppU = PlaneParam(0,1,0,500);
	PlaneParam ppD = PlaneParam(0,-1,0,500);
	ppU.c = Color(217, 206, 178,100);
	ppD.c = Color(217, 206, 178,100);
	ppB.c = Color(255, 255, 255,100);

	PlaneParam ppM = PlaneParam(-1,0,0,500);
	ppM.c = Color(255,255,255,100);
	ppM.lb = Vector(500,-500,300);
	ppM.ub = Vector(500,-300,500);
	

	o.surface = new Surface[7];

	o.surface[0] = Surface();
	o.surface[0].surfaceFn = &Sphere;
	o.surface[0].param = (void*)&sp;

	
	o.surface[1] = Surface();
	o.surface[1].surfaceFn = &Plane;
	o.surface[1].param = (void*)&ppB;
	o.surface[1].type = 0;

	o.surface[2] = Surface();
	o.surface[2].surfaceFn = &Plane;
	o.surface[2].param = (void*)&ppL;
	o.surface[2].type = 0;

	o.surface[3] = Surface();
	o.surface[3].surfaceFn = &Plane;
	o.surface[3].param = (void*)&ppR;
	o.surface[3].type = 0;

	o.surface[4] = Surface();
	o.surface[4].surfaceFn = &Plane;
	o.surface[4].param = (void*)&ppU;
	o.surface[4].type = 0;

	o.surface[5] = Surface();
	o.surface[5].surfaceFn = &Plane;
	o.surface[5].param = (void*)&ppD;
	o.surface[5].type = 0;

	o.surface[6] = Surface();
	o.surface[6].surfaceFn = &Plane;
	o.surface[6].param = (void*)&ppM;
	o.surface[6].type = 1;



	
	Ray rr = Ray(Point(Vector(0,0,-5), Color(0,0,0,100)), Vector(0,0,1));

	Point bb = o.intersect(rr, NULL);
	bb.print();

	// cout<<endl;

	// Point aa = (*o.surface[1].surfaceFn)(rr, 0, &pp);
	// aa.v.print();
	

	// printf("\n");

	// rr = Ray(Point(Vector(0,0,0), Color(0,0,0,100)), Vector(1,0,0));

	// bb = o.intersect(rr, NULL);
	// bb.v.print();

	// printf("\n");

	// aa = (*o.surface[1].surfaceFn)(rr, 0, &pp);
	// aa.v.print();

	printf("\n\n\n----------------------------\n\n\n");

	Color **ccc  = NULL;

	int ww , hh;
	ww = hh = 500;

	ccc = o.render(Vector(0,0,-1000), ww, hh);

	
	bitmap(ccc, (ww*2)+1, (hh*2) + 1, "a.ppm");
	
	return 0;
}