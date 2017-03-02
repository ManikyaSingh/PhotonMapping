#ifndef _OBJECT_SIMPLE_INCLUDED_
#define _OBJECT_SIMPLE_INCLUDED_

class Mesh{
	//will be declared later
};

typedef Point (*Surface)(Ray r, int mode, void *args);
// 0 - intersection determination
// 1 - normal determination

class Object{
public:
	Object *object;
	Mesh *mesh;
	Surface* surface;
	int sLen, mLen, oLen;

	Point intersectSurface(Ray r, int index){
		Point p;
		p.color.a = -1;
		if(index >= sLen) return p;
		Surface s = surface[index];
	}

	Point intersectMesh(Ray r, int index){
		Point p;
		p.color.a = -1;
		return p;
	}

	Point intersectObject(Ray r, int index){
		Point p;
		p.color.a = -1;
		if(index >= oLen) return p;
		return object[index].intersect(r);
	}

	Point intersect(Ray r, Vector *normal){
		int i;
		Point p, min;
		Ray tmp;
		min.color.a = -1;
		for(i=0;i<sLen;i++){
			p = intersectSurface(r, i);
			if(p.color.a == -1){

			}else{
				if(min.color.a == -1){
					if((p - r.p).x > 0){
						min = p;
						tmp.p = min;
						if(normal != NULL)
							*normal = (*(surface[i]))(tmp, -1, NULL);
					}
				}else{
					if((min-r.p).x < (p-r.p).x){
						min = p;
						tmp.p = min;
						if(normal != NULL)
							*normal = (*(surface[i]))(tmp, -1, NULL);
					}
				}
			}
		}

		for(i=0;i<mLen;i++){
			p = intersectMesh(r, i);
			if(p.color.a == -1){

			}else{
				if(min.color.a == -1){
					if((p - r.p).x > 0)
						min = p;
				}else{
					if((min-r.p).x < (p-r.p).x){
						min = p;
					}
				}
			}
		}

		for(i=0;i<oLen;i++){
			p = intersectObject(r, i);
			if(p.color.a == -1){

			}else{
				if(min.color.a == -1){
					if((p - r.p).x > 0)
						min = p;
				}else{
					if((min-r.p).x < (p-r.p).x){
						min = p;
					}
				}
			}
		}

		return min;

	}
};

#endif