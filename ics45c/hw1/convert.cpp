#include<iostream>
using namespace std;
double Convert(int knot)
{
	return (6076/(double)5280)*knot/60;
}

int main()
{
	int input;
	cin>>input;
	cout<<Convert(input)<<endl;
	return 0;
}
