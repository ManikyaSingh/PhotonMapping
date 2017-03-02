# RayTracing

1. Matrix
	+ Matrix
	- Matrix
	* SCALAR
	/ SCALAR
	* Matrix
	mod
	~ transpose
//	! inverse	//
//	adjoint		//
	print

2. Vector
	+ Vector
	- Vector
	* Scalar
	/ Scalar
	^ Vector dot
	* Vector cross
	unit
	mod
	mod2
	transform Matrix<3>
	transform Matrix<4>
//	rotate	//
	/ Vector component
	reflect

3. Color

4. Point

5. Ray

/*

Trace(ray){
	p = infinity
	tri = null;
	For every triangle t{
		i = intersection of ray and t
		if(i is inside t and on ray){
			if(p.z > i.z){
				p = i;
				tri = t;
			}
		}
	}

	ray.color = p.color;

	if(p != infinity){
		reflectedRay = ray.reflect(normal of tri at p)
		Trace(reflecedRay);
		ray.color = reflectedRay.color/10 + ray.color*9/10
	}

}

Ray.Intersect(Surface){
	
	int mFactor = 1;
	int dFactor = 1;
	int limit = 1000; // 0.001 - 3 decimal places

	int mFUL = -1;
	
	while(dFactor != 1000){
		i = Sruface(Ray);
		if(i > 0){
			if(mFactor != mFUL) mFactor *= 10;
			Ray.v += Ray.dir.unit() * (mFactor/dFactor);
		}else if(i < 0){
			if(mFUL == -1){
				mFUL = mFactor/10;
			}
			if(mFactor > 1){
				mFactor /= 10;
			}else{
				dFactor *= 10;
			}
		}else{
			return;
		}		
	}
	return;
}









Consider points in 3d.
Assumption: they lie on poly curve

Xn Xn-1 Xn-2 . . .. . X0  (n+1 terms)
Yn ...
Zn ...

no of terms in expansion of (X + Y + Z + 1)^n

(x1 y1 z1 1)(x2 y2 z2 1) ... (xn yn zn 1)k = 3n + 1 independent terms

3n + 1 > number of points on object

3n + 1 > k

n > (k-1)/3




*/