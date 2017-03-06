class Photon{
public:
	Vector v;
	double p;
	Photon(){

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
		int ret = 0;
		Vector u = Vector(v.x+r, v.y+r, v.z+r);
		if(v.x <= lb.x && v.y <= lb.y && v.z <= lb.z && u.x >= lb.x && u.y >= lb.y && u.z >= lb.z){
			ret += 1;
		}

		if(v.x <= ub.x && v.y <= ub.y && v.z <= ub.z && u.x >= ub.x && u.y >= ub.y && u.z >= ub.z){
			ret += 1;
		}
		return ret;
	}
	int rangeCount(Vector q, double r){
		int qno = inBB(q, r);
		if(qno == 0) return 0;
		if(qno == 2) return power;

		qno = getQno(q, p.v);

		int ret = 0;
		if(qno == 0){
			if(p.v.x <= q.x+r && p.v.y <= q.y+r && p.v.z <= q.z+r){
				ret = p.p;
				printf("\nFOUND %f %f %f %f\n", p.v.x, p.v.y, p.v.z, p.p);
				//check both 0th and 7th quad
			}
		}
		for(qno=0;qno<8;qno++){
			if(quad[qno] != NULL){
				ret += quad[qno]->rangeCount(q, r);
			}
		}
		
		return ret;
	}
};
