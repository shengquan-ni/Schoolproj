#ifndef MAPARRAY_H
#define MAPARRAY_H
#include <algorithm>
#include <iterator>
using namespace std;

template<class K,class V>
class MapArray
{	
	int size;
	bool sortflag;
    pair<K,V>* map;
	void ensure_sorted()
	{
       if(!sortflag)
		{
			sortflag=true;
            quicksort(0,size-1);
		}
	}
	void quicksort(int lo,int hi)
	{
		if(lo>=hi)return;
		int first=lo,last=hi;
		auto key=map[lo];
		while(first<last)
		{
			while(first<last && map[last].first>=key.first)--last;
			map[first]=map[last];
			while(first<last && map[first].first<=key.first)++first;
			map[last]=map[first];
		}
		map[first]=key;
		quicksort(lo,first-1);
		quicksort(first+1,hi);
	}
public:
	typedef const pair<K,V>& const_reference; 
	MapArray():size(0),sortflag(false),map(nullptr){};
	void insert(const pair<K,V>& p)
	{
		size++;
		pair<K,V>* temp=map;
		map=new pair<K,V>[size];
		if(temp)
		{
			for(int i=0;i<size-1;++i)
				map[i]=temp[i];
			delete[] temp;
			temp=nullptr;
		}
		map[size-1]=p;
		sortflag=false;
	}
	struct iterator
	{
		typedef random_access_iterator_tag iterator_category;
		typedef iterator self_type;
		typedef pair<K,V> value_type;
		typedef pair<K,V>& reference;
		typedef pair<K,V>* pointer;
		typedef ptrdiff_t difference_type;
	private:
		pointer iter;
	public:
		iterator(pointer i):iter(i){}
		self_type& operator++(){++iter;return *this;}
		self_type& operator++(int postfix){self_type temp=*this;iter++;return temp;}
		self_type& operator--() { --iter; return *this; }
		self_type& operator--(int postfix) { self_type temp = *this; iter--; return temp; }
		self_type& operator-(int n) { iter -= n; return *this; }
		self_type& operator+(int n) { iter += n; return *this; }
		bool operator<(const self_type& rhs) { return iter < rhs.iter; }
		reference operator*(){return *iter;}
		bool operator==(const self_type& rhs)const{return iter==rhs.iter;}
		bool operator!=(const self_type& rhs)const{return iter!=rhs.iter;}
	};
	iterator begin()
	{
		ensure_sorted();
		return iterator(map);
	}
	
	iterator end()
	{
		ensure_sorted();
		return iterator(map+size);
	}
	V& operator[](const K& key)
	{
		for(int i=0;i<size;i++)
			if(map[i].first==key)
				return map[i].second;
		insert(pair<K,V>(key,V()));
		return map[size-1].second;
	}
    ~MapArray()
	{
		if(map)
			delete[] map;
	}

};
#endif
