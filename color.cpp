#ifndef _COLOR_SIMPLE_INCLUDED_
#define _COLOR_SIMPLE_INCLUDED_

class Color{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	char a = -1;
	Color(){

	}
	Color(unsigned char R, unsigned char G, unsigned char B, char A){
		r = R;
		g = G;
		b = B;
		a = A;
	}
	Color(const Color& cc){
		r = cc.r;
		g = cc.g;
		b = cc.b;
		a = cc.a;
	}
};

#endif