#ifndef SETLIST_H
#define SETLIST_H
#include <algorithm>
#include <iterator>
using namespace std;

template<class T>
class ListNode
{
public:
	T info;
	ListNode<T>* next;
	ListNode(T t,ListNode<T>* n=nullptr):info(t),next(n){};
};


template<class T>
class SetList
{
	ListNode<T>* head;
public:
	SetList()
	{
		head=nullptr;
	}
	void insert(T t)
	{
		head=new ListNode<T>(t,head);
	}
	struct iterator
	{
		typedef forward_iterator_tag iterator_category;
		typedef iterator self_type;
		typedef ListNode<T> value_type;
		typedef ListNode<T>& reference;
		typedef ListNode<T>* pointer;
		typedef ptrdiff_t difference_type;
	private:
		pointer iter;
	public:
		iterator(pointer ptr):iter(ptr){}
		self_type& operator++(){iter=iter->next;return *this;}
		self_type& operator++(int postfix){self_type temp=*iter; iter=iter->next;return temp; }
		reference operator*(){return *iter;}
		pointer operator->(){return iter;}
		bool operator==(const self_type& rhs)const{return iter==rhs.iter;}
		bool operator!=(const self_type& rhs)const{return iter!=rhs.iter;}
	};
	int length()
	{
		int count=0;
		ListNode<T>* temp=head;
		while(temp)
		{
			count++;
			temp=temp->next;
		}
		return count;
	}
	int size()
	{
		return this->length();
	}
	iterator find(T t)
	{
		ListNode<T>* temp=head;
		while(temp)
			if(temp->info==t)
				return iterator(temp);
			else
				temp=temp->next;
		return iterator(nullptr);
	}
	iterator begin(){return iterator(head);}
	iterator end(){return iterator(nullptr);}
	~SetList()
	{
		while (head)
		{
			ListNode<T>* temp = head->next;
			delete head;
			head = temp;
		}
	}
};
#endif
