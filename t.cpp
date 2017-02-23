#include <iostream>
using namespace std;

void change(int& x){
	x = 2;
}
int main(){
	int x = 0;
	change(x);
	cout<<x;
}