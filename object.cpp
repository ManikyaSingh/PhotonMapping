#ifndef _OBJECT_SIMPLE_INCLUDED_
#define _OBJECT_SIMPLE_INCLUDED_

class Mesh{
	//will be declared later
};

#define RAND(a,b) (a + (((double)rand())/(RAND_MAX))*b);

class Light{
	Light(){

	}
	Ray source;
	double Angle;
	double power;
	Vector generate(){
		double a = RAND(0, Angle);
		Vector v;
		v.x = RAND(0,1);
		v.y = RAND(0,1);
		v.z = (Cos(a) * (d.mod2()))/(((source.d.x)*x)+((source.d.y)*y));
		if(v^d < 0) v = -v;
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

	Color** render(Vector vp, int w, int h, Light *light){
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

	int Illuminate(OTNode *root, Light *light, int lc){
		if(root == NULL)
			root = new OTNode();
		root->p.v.x = 0;
		root->p.v.y=0;
		root->p.v.z=0;
		root->p.p = 0;
		root->lb = root->ub = root->p.v;
		root->power = 0;
		while(lc--){
			//use light lc to generate random photon ray and find intersection then insert into OCTree
		}
		return 0;
	}
};

Point Object::intersect(Ray r, Vector *normal){
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
				if(((p.v - r.p.v)^(r.d)) >= 0){
					min = p;
					frm = 0;
					ind = i;
				}
			}else{
				if(((min.v - p.v)^(r.d)) >= 0){
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
				if(((p.v - r.p.v)^(r.d)) >= 0){
					min = p;
					frm = 1;
					ind = i;
					// if(normal != NULL)
					// 	*normal = (*(surface[i].surfaceFn))(tmp, -1, NULL).v;
				}
			}else{
				if(((min.v - p.v)^(r.d)) >= 0){
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
				if(((p.v - r.p.v)^(r.d)) >= 0){
					min = p;
					frm = 2;
					ind = i;
				}
			}else{
				if(((min.v - p.v)^(r.d)) >= 0){
					min = p;
					frm = 2;
					ind = i;
				}
			}
		}
	}

	

	if(min.color.a >= 0){
		if(frm == 0){
			tmp.p = min;
			
			tmp.p = (*(surface[ind].surfaceFn))(tmp, 1, surface[ind].param);
			//tmp.p.print();

			if(normal != NULL){ *normal = tmp.p.v; }

			if(surface[ind].type == 1 && rootObject != NULL && tmp.p.color.a >= 0){
				r = Ray(min, r.d.reflect(tmp.p.v));
				min = rootObject->intersect(r, normal);
				//min.print();
				
					//min.color.a = 100;
					if(min.color.a < 0){
						min.color.r = min.color.g=min.color.b = 50;
						min.color.a = 100;
					}else{
						// min.color.r += 50;
						// min.color.g += 50;
						// min.color.b += 50;
					}
					
				
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
			if(r1 > 0){
				p.v = v + r1*dir;
			}else{
				p.color.a = -1;
			}
		}else{
			if(r1 > 0){
				if(r2 > 0){
					if(r1 > r2) r1 = r2;
				}
			}else{
				if(r2 > 0){
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
	}else if(mode == 1 || mode == 2){
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
				if(p.v.x < param->lb.x && p.v.x > param->ub.x) p.color.a = -1;
			}else if(param->lb.x < param->ub.x){
				if(p.v.x < param->lb.x || p.v.x > param->ub.x) p.color.a = -1;
			}

			if(param->lb.y > param->ub.y){
				if(p.v.y < param->lb.y && p.v.y > param->ub.y) p.color.a = -1;
			}else if(param->lb.y < param->ub.y){
				if(p.v.y < param->lb.y || p.v.y > param->ub.y) p.color.a = -1;
			}

			if(param->lb.z > param->ub.z){
				if(p.v.z < param->lb.z && p.v.z > param->ub.z) p.color.a = -1;
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