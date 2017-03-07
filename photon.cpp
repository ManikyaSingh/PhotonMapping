class Photon{
public:
	Vector v;
	Color c;
	double p;
	Photon(){

	}
	Photon(Point a, double b){
		v = a.v;
		c = a.color;
		p = b;
	}
	Photon(Vector a, double d){
		v = a;
		p=d;
	}
	Photon(double a, double b, double c, double d){
		v.x = a;
		v.y = b;
		v.z = c;
		p = d;
	}
	Photon (const Photon &obj) {
		v = obj.v;
		p = obj.p;
		c = obj.c;
	}
};

class OTNode{
public:
	Photon p;
	OTNode *quad[8];
	Vector lb;
	Vector ub;
	double power;
	OTNode(){
		for(int i=0; i<8;i++){
			quad[i] = NULL;
		}
	}
	
	OTNode(Photon q){
		p = q;
		lb = p.v;
		ub = p.v;
		power = q.p;
	}
	~OTNode(){
		for(int i=0;i<8;i++){
			if(quad[i] != NULL)
				delete quad[i];
		}
	}
	int getQno(Vector p, Vector q){
		int qno;
		if(p.x >= q.x){
			if(p.y >= q.y){
				if(p.z >= q.z){
					qno = 0;
				}else{
					qno = 1;
				}
			}else{
				if(p.z >= q.z){
					qno = 2;
				}else{
					qno = 3;
				}
			}
		}else{
			if(p.y >= q.y){
				if(p.z >= q.z){
					qno = 4;
				}else{
					qno = 5;
				}
			}else{
				if(p.z >= q.z){
					qno = 6;
				}else{
					qno = 7;
				}
			}
		}
		return qno;
	}
	int insert(Photon q){
		int qno = getQno(p.v, q.v);

		if(lb.x > q.v.x){
			lb.x = q.v.x;
		}
		if(lb.y > q.v.y){
			lb.y = q.v.y;
		}
		if(lb.z > q.v.z){
			lb.z = q.v.z;
		}

		if(ub.x < q.v.x){
			ub.x = q.v.x;
		}
		if(ub.y < q.v.y){
			ub.y = q.v.y;
		}
		if(ub.z < q.v.z){
			ub.z = q.v.z;
		}

		power += q.p;

		if(quad[qno] != NULL){
			quad[qno]->insert(q);
		}else{
			quad[qno] = new OTNode(q);
		}
		
		return qno;

	}
	void print(){
		for(int i=0;i<8;i++){
			if(quad[i] != NULL){
				quad[i]->print();
			}
		}
		printf("\n%f %f %f %f ", p.v.x, p.v.y, p.v.z, p.p);
		cout<<"(";
		lb.print();
		cout<<" , ";
		ub.print();
		cout<<") "<<power<<"\n";

	}
	int inBB(Vector v, double r){
		Vector u = Vector(v.x+r, v.y+r, v.z+r);



		if(v.x <= ub.x && v.y <= ub.y && v.z <= ub.z && u.x >= lb.x && u.y >= lb.y && u.z >= lb.z){
			Vector tmp = u+v;
			tmp = tmp/2;
			if( (tmp-lb).mod()*4 <= r*r && (tmp-ub).mod()*4 <= r*r ){
				return 2;
			}
			return 1;
		}
		
		return 0;
	}
	double rangeCount(Vector q, double r){
		int qno = inBB(q, r);
		// cout<<"\n---SEARCH LOGS---\n";
		// cout<<"\nCUR NODE - ";
		// p.v.print();
		// cout<<"\n";
		// cout<<"intersct no = "<<qno<<endl;
		if(qno == 0) return 0;
		if(qno == 2) return power;

		qno = getQno(q, p.v);
		// cout<<"quad no = "<<qno<<" | q ";q.print();cout<<" | v ";p.v.print();cout<<"\n";


		double ret = 0;
		if(qno == 7){
			if(p.v.x <= q.x+r && p.v.y <= q.y+r && p.v.z <= q.z+r){
				Vector tmp = Vector(r/2);
				tmp = q + tmp - p.v;
				if((tmp.mod())*4 <= r*r ) ret = p.p;
				//cout<<"\nCUR NODE ACCEPTED\n";
			}else{
				//cout<<"\nCUR NODE REJECTED LV 2\n";
			}
		}else{
			//cout<<"\nCUR NODE REJECTED LV 1\n";
		}
		for(qno=0;qno<8;qno++){
			if(quad[qno] != NULL){
				ret += quad[qno]->rangeCount(q, r);
			}
		}
		
		return ret;
	}

	double rangeCountLinear(Vector q, double r){
		double ret = 0;
		if(p.v.x >= q.x && p.v.y >= q.y && p.v.z >= q.z && p.v.x < q.x+r && p.v.y < q.y+r && p.v.z < q.z+r){
			ret += p.p;
		}
		for(int qno=0;qno<8;qno++){
			if(quad[qno] != NULL){
				ret += quad[qno]->rangeCountLinear(q, r);
			}
		}
		return ret;
	}


	void projectPoint(Vector vp, Color** c, int w, int h){
		Vector d = vp - p.v;
		int a,b;
		if(d.z != 0){
			double lam = vp.z/d.z;
			d = (vp+(lam*d));
			a = d.x;
			b = d.y;
			Color tmp = Color(255,255,255,100);
			if(a <= w && a >= -w && b <= h && b >= -h){
				c[h-b][w-a] = tmp;
			}
		}

		for(int i=0;i<8;i++){
			if(quad[i] != NULL){
				quad[i]->projectPoint(vp, c, w, h);
			}
		}
		
		
	}
	Color** project(Vector vp, int w, int h){
		Color **ret = new Color*[2*h+1];
		int i,j;
		Color tmp = Color(0,0,0,100);
		for(j=-h;j<=h;j++){
			ret[h-j] = new Color[2*w+1];
			for(i=-w;i<=w;i++){
				ret[h-j][i+w] = tmp;
			}
		}

		this->projectPoint(vp, ret, w, h);

		return ret;
		
	}
};
