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
	srand (time(NULL));
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

	int inp;
	Photon tmpP;
	cout<<"Insert? ";
	cin>>inp;
	while(inp){
		cout<<"x = ";
		cin>>tmpP.v.x;
		cout<<"y = ";
		cin>>tmpP.v.y;
		cout<<"z = ";
		cin>>tmpP.v.z;
		tmpP.p = 1;
		cout<<"\nINSERTING - ";
		tmpP.v.print();
		cout<<"\n";
		root.insert(tmpP);
		cin>>inp;
	}

	cout<<"\nINSERTIONS COMPLETE\n";

	root.insert(Photon(0.9, 0.9, 0.9, 1));

	root.print();

	cout<<"Search? ";
	cin>>inp;
	Vector tmpV;
	double tmpR;
	while(inp){
		cout<<"x = ";
		cin>>tmpV.x;
		cout<<"y = ";
		cin>>tmpV.y;
		cout<<"z = ";
		cin>>tmpV.z;
		cout<<"r = ";
		cin>>tmpR;
		cout<<"\nSEARCHING FOR - ";
		tmpV.print();
		cout<<"  |  "<<tmpR;
		cout<<"\nFOUND "<<root.rangeCount(tmpV,tmpR)<<"\n";
		cin>>inp;
	}

	cout<<root.rangeCount(Vector(0,0,0),1.0);

	printf("\n-------------------------------------\n");

	Object o = Object();

	rootObject = &o;

	o.sLen = 7;
	o.oLen = 0;
	
	SphereParam sp = SphereParam(0,0,250,80*80);

	PlaneParam ppB = PlaneParam(0,0,1,500);

	PlaneParam ppL = PlaneParam(-1,0,0,500);
	ppL.c = Color(150,0,0,100);
	PlaneParam ppR = PlaneParam(1,0,0,500);
	ppR.c = Color(0,150,0,100);
	// ppR.lb = Vector(500, 100, 300);
	// ppR.ub = Vector(500, -100, 200);

	PlaneParam ppU = PlaneParam(0,1,0,500);
	PlaneParam ppD = PlaneParam(0,-1,0,500);
	ppU.c = Color(255, 255, 255,100);
	ppD.c = Color(255, 255, 255,100);
	ppB.c = Color(220, 220, 220,100);

	PlaneParam ppM = PlaneParam(-1,0,1,600);
	ppM.c = Color(150,150,150,100);
	ppM.lb = Vector(-500 , -500 , 100);
	ppM.ub = Vector(-500 , -100 , 500);
	

	o.surface = new Surface[7];

	o.surface[0] = Surface();
	o.surface[0].surfaceFn = &Sphere;
	o.surface[0].param = (void*)&sp;
	o.surface[0].type = 2;
	o.surface[0].coeff = 2;

	
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


	OTNode *rnode = new OTNode();
	rnode->p.v.x = 0;
	rnode->p.v.y = 0;
	rnode->p.v.z = 0;
	rnode->p.p = 0;
	rnode->lb = rnode->p.v;
	rnode->ub = rnode->p.v;
	rnode->power = 0;

	Light lights[1];
	lights[0].angle = M_PI/2;
	lights[0].power = 800000;
	lights[0].source = Ray(Point(Vector(-40,0,250), Color(255,255,255,100)), Vector(0,0,0));

	Object::illuminate(rnode, lights, 1, 100000);

	cout<<"\n------------------------PHOTON MAP-------------------------\n";

	//rnode->insert(Photon(0.9, 0.9, 0.9, 1));

	//rnode->print();

	//cout<<rnode->rangeCountLinear(Vector(0.1,0.1,0.1), 100.0);
	cout<<"\n-------------------------------------------------\n";


	Color **ddd  = NULL;

	int ww , hh;
	ww = hh = 500;

	ddd = rnode->project(Vector(0,0,-1000), ww, hh);

	
	bitmap(ddd, (ww*2)+1, (hh*2) + 1, "map2.ppm");

	
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

	// int ww , hh;
	// ww = hh = 500;

	ccc = o.render(Vector(0,0,-1000), ww, hh);

	
	bitmap(ccc, (ww*2)+1, (hh*2) + 1, "a2.ppm");

	printf("\n\n\n----------------------------\n\n\n");

	Color **eee  = NULL;

	// int ww , hh;
	// ww = hh = 500;

	eee = Object::render(Vector(0,0,-1000), ww, hh, rnode, 60.0);

	
	bitmap(eee, (ww*2)+1, (hh*2) + 1, "a_i2.ppm");
	
	return 0;
}