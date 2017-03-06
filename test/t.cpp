#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define RAND(a,b) (a + (((double)rand())/(RAND_MAX))*b);

int main(){
	cout<<rand()<<" "<<rand();
	srand(time(NULL));
	double d = ((double)rand())/(RAND_MAX);
	cout<<"\n";
	unsigned long long int sam = 100000000;
	unsigned long long int ran[10];
	for(int i=0;i<10;i++){
		ran[i] = 0;
	}
	int dd;
	unsigned long long int tot = sam;
	int ph = 0;
	while(sam--){
		//cout<<d<<" ";
		d = RAND(0,10);
		dd = d;
		if(((tot-sam)*100)/tot > ph) cout<<"\n "<<++ph<<"% done \n";
		ran[dd%10]++;
	}

	for(int i=0;i<10;i++){
		cout<<endl<<endl<<"# "<<ran[i];
	}
		

	return 0;
}