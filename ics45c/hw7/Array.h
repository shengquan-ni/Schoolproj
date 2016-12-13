#ifndef ARRAY_H
#define ARRAY_H
#include <cassert>
#include <iomanip>
#include <iostream>
using namespace std;

class IndexOutOfBoundsException{};


template<class E>
class Array
{
private:
	int len;
	E* buf;
public:
	Array<E>(int newLen):len(newLen),buf(new E[newLen])
	{
	}	
	Array<E>(const Array<E>& l):len(l.len),buf(new E[l.len])
	{
		for(int i=0;i<l.len;i++)
			buf[i]=l.buf[i];
	}
	int length()
	{
		return len;
	}

	E & operator [] (int i)throw (IndexOutOfBoundsException)
	{
		if(!(0<=i && i<len))throw IndexOutOfBoundsException();
		return buf[i];
	}

	void print(ostream & out)
	{
		for(int i=0;i<len;++i)
			out<<setw(8)<<setprecision(2)<<fixed<<right<<buf[i];
	}

	friend ostream& operator<< (ostream & out,Array<E>& a)
	{
		a.print(out);
		return out;
	}
	friend ostream & operator<<(ostream & out,Array<E>* a)
	{
		a->print(out);
		return out;
	}
	~Array<E>()
	{
		delete[] buf;
	}
};
#endif