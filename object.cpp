#ifndef _OBJECT_SIMPLE_INCLUDED_
#define _OBJECT_SIMPLE_INCLUDED_

class Mesh{
	//will be declared later
};

#define RAND(a,b) (a + (((double)rand())/(RAND_MAX))*b);

class Light{
public:
	Light(){

	}
	Ray source;
	double angle;
	double power;
	Vector generate(int i){
		double a = RAND(-angle, 2*angle);
		Vector v;
		do{
			v.x = RAND(-10,20);
			v.y = RAND(-10,20);
			v.z = RAND(-10,20);
			// v.print();
			// cout<<" "<<v.mod()<<" "<<compare(v.mod(),0);

			// printf(" a %d\n", i);
		}while(compare(v.mod(),0) == 0 || v.mod() > 100 );
		// if(compare(source.d.mod(), 0) == 0) return v;
		// else{
		// 	while( compare(v.mod(),0) == 0 || (v^(source.d)) < ( (v.mod2()) * ((source.d).mod2()) * (cos(angle)) )  ){
		// 		v.x = RAND(-10,20);
		// 		v.y = RAND(-10,20);
		// 		v.z = RAND(-10,20);
		// 	}
		// }

		// if((v^(source.d)) < 0) v = -v;
		return v;
	}
};

typedef Point (*SurfaceFn)(Ray r, int mode, void *args);
// 0 - intersection determination
// 1 - normal determination at point
// 2 - point at curve

class Surface{
public:
	SurfaceFn surfaceFn;
	void *param;
	char type=0;//default
				//1 = reflect , perfectly
				//2 = refract , perfectly
	double coeff=1;
	void *typeParam;
	Surface(){
		param = NULL;
		typeParam = NULL;
		surfaceFn = NULL;
	}
};

class Object;

Object* rootObject = NULL;




class Object{
public:

	static int c;
	Object *object;
	Mesh *mesh;
	Surface* surface;
	int sLen, mLen, oLen;

	Object(){
		mesh = NULL;
		surface = NULL;
		object = NULL;
		sLen = mLen = oLen = 0;
	}

	Point intersectSurface(Ray r, int index){
		Point p;
		p.color.a = -1;
		if(index >= sLen) return p;
		SurfaceFn s = surface[index].surfaceFn;
		return s(r, 0, surface[index].param);
	}

	Point intersectMesh(Ray r, int index){
		Point p;
		p.color.a = -1;
		return p;
	}

	Point intersect(Ray r, Vector *normal);

	Point intersectObject(Ray r, int index, Vector *normal){
		Point p;
		p.color.a = -1;
		if(index >= oLen) return p;
		return object[index].intersect(r, normal);
	}

	Color** render(Vector vp, int w, int h){
		/*
		For every ray find min intersection point , point.color = pixel.color
		*/
		Color **ret = new Color*[2*h+1];
		int i,j;
		Ray r;
		Point tmp;
		for(j=-h;j<=h;j++){
			ret[j+h] = new Color[2*w+1];
			for(i=-w;i<=w;i++){

				r = Ray(Point(Vector(vp.x + i, vp.y + j, 0), Color(0,0,0,0)), Vector(i , j, -vp.z));

				tmp = intersect(r, NULL);



				if(i == 0 && j == 0)
					tmp.print();
				
				
				ret[j+h][i+w] = tmp.color;
			}
		}

		return ret;
	}

	

	static int illuminate(OTNode *root, Light *light, int lc, int pc){
		if(rootObject == NULL) return 0;
		if(root == NULL) return 0;
		
		int pcp;
		Ray lr;
		Point ip;
		Photon ins;
		Vector nrm;
		Vector gen;
		double co;
		int done;
		int d2;
		double gg;
		double poww;
		while(lc--){
			done = 0;
			pcp = pc;
			cout<<pcp<<" "<<pc;
			
			while(pcp--){
				//use light lc to generate random photon ray and find intersection then insert into OCTree
				lr.d = light[lc].generate(pcp);
				// printf("\nRAY GEN ");
				// lr.d.print();
				// printf("\n");
				lr.p = light[lc].source.p;
				ip = rootObject->intersect(lr, &nrm);
				//cout<<pcp<<endl;

				d2 = pc/100;
				if(done%d2 == 0)cout<<(done/d2)<<endl;
				done++;

				co = (lr.d^nrm)/(lr.d.mod2() * nrm.mod2());
				if(co < 0) co = - co;
				poww = light[lc].power/pc;
				poww *= co;
				root->insert(Photon(ip, (poww )));

				gg = RAND(-2,3);
				while(gg<0){
					//cout<<"r";
					do{
						gen.x = RAND(-10,20);
						gen.y = RAND(-10,20);
						gen.z = RAND(-10,20);
					}while(gen.mod() > 100 || compare(gen.mod(), 0) == 0 || (gen^nrm) < 0 );
					lr.p = ip;
					lr.d = gen;
					ip = rootObject->intersect(lr, &nrm);
					co = (lr.d^nrm)/(lr.d.mod2() * nrm.mod2());
					if(co < 0) co = - co;
					poww *= co;
					root->insert(Photon(ip, poww));
					gg = RAND(-2,3);
				}

			}
			
		}
		return 1;
	}

	static Color** render(Vector vp, int w, int h, OTNode *root, double range){
		/*
		For every ray find min intersection point , point.color = pixel.color
		*/


		Color **ret = new Color*[2*h+1];
		int i,j;
		Ray r;
		Point tmp;
		int pc = 0;
		int pcp;
		Vector VR2 = Vector(range/2);
		for(j=-h;j<=h;j++){
			ret[j+h] = new Color[2*w+1];
			for(i=-w;i<=w;i++){

				r = Ray(Point(Vector(vp.x + i, vp.y + j, 0), Color(0,0,0,0)), Vector(i , j, -vp.z));

				tmp = rootObject->intersect(r, NULL);

				double ip = root->rangeCount(tmp.v - VR2 , range);

				//if(ip != 0) cout<<"\nPHOTONS - "<<ip<<"\n";


				ip /= range;
				ip /= range;

				tmp.color = tmp.color * ip;

				if(i == 0 && j == 0)
					tmp.print();
				
				
				ret[j+h][i+w] = tmp.color;
			}
			pcp = (((h+j)*100)/(2*h));
			if(pcp != pc){pc = pcp;
				cout<<endl<<pcp<<"% completed\n";
			}
			
		}

		return ret;
	}
};

int Object::c(0);

Point Object::intersect(Ray r, Vector *normal){
	//cout<<"#"<<c<<endl;
	int i;
	Point p, min;
	Ray tmp;
	min.color.a = -1;
	int frm = 0;
	int ind = 0;
	for(i=0;i<sLen;i++){
		p = intersectSurface(r, i);
		//p.print();
		if(p.color.a == -1){

		}else{
			if(min.color.a == -1){
				if(((p.v - r.p.v)^(r.d)) > 0){
					min = p;
					frm = 0;
					ind = i;
				}
			}else{
				if(((min.v - p.v)^(r.d)) > 0){
					min = p;
					frm = 0;
					ind = i;
				}
			}
		}
	}

	for(i=0;i<mLen;i++){
		p = intersectMesh(r, i);
		if(p.color.a == -1){

		}else{
			if(min.color.a == -1){
				if(((p.v - r.p.v)^(r.d)) > 0){
					min = p;
					frm = 1;
					ind = i;
					// if(normal != NULL)
					// 	*normal = (*(surface[i].surfaceFn))(tmp, -1, NULL).v;
				}
			}else{
				if(((min.v - p.v)^(r.d)) > 0){
					min = p;
					frm = 1;
					ind = i;
					// if(normal != NULL)
					// 	*normal = (*(surface[i].surfaceFn))(tmp, -1, NULL).v;
				}
			}
		}
	}

	for(i=0;i<oLen;i++){
		p = intersectObject(r, i, normal);
		if(p.color.a == -1){

		}else{
			if(min.color.a == -1){
				if(((p.v - r.p.v)^(r.d)) > 0){
					min = p;
					frm = 2;
					ind = i;
				}
			}else{
				if(((min.v - p.v)^(r.d)) > 0){
					min = p;
					frm = 2;
					ind = i;
				}
			}
		}
	}

	if(c>10){
		min.color.a = -1;
		c = 0;
	}

	if(min.color.a >= 0){
		if(frm == 0){
			tmp.p = min;
			
			tmp.p = (*(surface[ind].surfaceFn))(tmp, 1, surface[ind].param);


			if(normal != NULL){ *normal = tmp.p.v; }

			if(surface[ind].type == 1 && rootObject != NULL && tmp.p.color.a >= 0){
				r = Ray(min, r.d.reflect(tmp.p.v));
				min = rootObject->intersect(r, normal);
				//min.print();
				
					//min.color.a = 100;
					c++;

					
				
			}else if(surface[ind].type == 2 && rootObject != NULL && tmp.p.color.a >= 0){
				//tmp.p.v.print();cout<<endl;
				r.d = r.d.refract(tmp.p.v, surface[ind].coeff);
				//min.v = min.v + (r.d*0.1);
				r = Ray(min,r.d);
				//r.d.print();cout<<endl;
				min = rootObject->intersect(r, normal);
				//min.print();
				c++;
					
			}else{
				c = 0;
			}
			
				
		}
	}
	return min;

}

struct SphereParam{
	double X,Y,Z,R;
	SphereParam(double _X, double _Y, double _Z, double _R){
		X = _X;
		Y = _Y;
		Z = _Z;
		R = _R;
	}
	SphereParam(){

	}
};

Point Sphere(Ray r, int mode, void *args){
	SphereParam *param = (SphereParam*) args;
	Vector dir = r.d;
	Vector v = r.p.v;
	v.x -= param->X;
	v.y -= param->Y;
	v.z -= param->Z;
	double rhs = param->R;
	Point p;
	p.color.a = 100;
	p.color.r = p.color.g = p.color.b = 144;
	if(mode == 0){
		double r1,r2;
		int r = roots(dir.mod() , 2*(v^dir), v.mod() - rhs, &r1, &r2);
		if(r == 0){
			p.color.a = -1;
		}else if(r == 1){
			if(compare(r1,0) > 0){
				p.v = v + r1*dir;
			}else{
				p.color.a = -1;
			}
		}else{
			if(compare(r1,0) > 0){
				if(compare(r2,0) > 0){
					if(compare(r1,r2) > 0) r1 = r2;
				}
			}else{
				if(compare(r2,0) > 0){
					r1 = r2;
				}else{
					p.color.a = -1;
				}
			}
			p.v = v + r1*dir;
			p.v.x += param->X;
			p.v.y += param->Y;
			p.v.z += param->Z;
		}
	}else if(mode == 1){
		// if(compare(rhs, v.mod()) == 0){
			p.v = v;
		// 	if(mode == 1){
		// 		p.v = r.p.v;
		// 	}
		// }else{
		// 	p.color.a = -1;
		// }
	}else if(mode == 2){
		if(compare(rhs, v.mod()) == 0){
			p.v = v;
			if(mode == 1){
				p.v = r.p.v;
			}
		}else{
			p.color.a = -1;
		}
	}
	return p;
}
struct PlaneParam{
	double d;
	Vector v;
	Color c = Color(255,255,255,100);
	Vector lb = Vector(0,0,0);
	Vector ub = Vector(0,0,0);
	PlaneParam(double A, double B, double C, double D){
		v = Vector(A,B,C);
		d=D;
	}
	PlaneParam(Vector a, double D){
		v = a;
		d = D;
	}
	PlaneParam(){

	}
};

Point Plane(Ray r, int mode, void *args){
	PlaneParam *param = (PlaneParam*) args;
	Vector dir = r.d;
	Vector v = r.p.v;
	
	Vector n = param->v;
	double rhs = param->d;

	Point p;
	p.color = param->c;

	if(mode == 0){
		double r1,r2;
		int r = roots(0 , dir^n , (v^n) - rhs, &r1, &r2);
		//printf("\n%f", r1);
		if(r == 0){
			p.color.a = -1;
		}else{
			if(r1 > 0){
				p.v = v + r1*dir;
			}else{
				p.color.a = -1;
			}
		}
		if(!(param->lb == param->ub)){
			if(param->lb.x > param->ub.x){
				if(!(p.v.x < param->ub.x || p.v.x > param->lb.x)) p.color.a = -1;
			}else if(param->lb.x < param->ub.x){
				if(p.v.x < param->lb.x || p.v.x > param->ub.x) p.color.a = -1;
			}

			if(param->lb.y > param->ub.y){
				if(!(p.v.y < param->ub.y || p.v.y > param->lb.y)) p.color.a = -1;
			}else if(param->lb.y < param->ub.y){
				if(p.v.y < param->lb.y || p.v.y > param->ub.y) p.color.a = -1;
			}

			if(param->lb.z > param->ub.z){
				if(!(p.v.z < param->ub.z || p.v.z > param->lb.z)) p.color.a = -1;
			}else if(param->lb.z < param->ub.z){
				if(p.v.z < param->lb.z || p.v.z > param->ub.z) p.color.a = -1;
			}
		}
	}else if(mode == 1){
		//if(compare((v^n), rhs) == 0){
			p.v = -n;
		//}else{
		//	p.color.a = -1;
		//}
	}else if(mode == 2){
		if(compare((v^n), rhs) == 0){
			p.v = v;
			if(!(param->lb == param->ub)){
				if(p.v.x > param->ub.x || p.v.y > param->ub.y || p.v.z > param->ub.z || p.v.x < param->lb.x || p.v.y < param->lb.y || p.v.z < param->lb.z){
					p.color.a == -1;
				}

			}
		}else{
			p.color.a = -1;
		}
	}
	
	

	return p;
}

#endif