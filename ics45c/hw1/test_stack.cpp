#include"Stack.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	while(1)
	{
		string input;
		bool result=getline(cin,input);
		if(!result)return 0;
		Stack s;
		int length=input.length();
		for(int i=0;i<length;++i)
		{
			if(!s.isFull())
				s.push(input[i]);
			else
			{
				cout<<"Stack is full!"<<endl;
				break;
			}
		}
		while(!s.isEmpty())
			cout<<s.pop();
		cout<<endl;
	}

}
