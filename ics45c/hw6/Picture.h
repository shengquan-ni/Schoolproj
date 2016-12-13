#ifndef PICTURE_H
#define PICTURE_H
#include "Shape.h"
class Picture
{
public:
	Picture()
	{
		head=nullptr;
	}
	void Add(Shape* s)
	{
		ListNode* t=head;
		if(!t)head=new ListNode(s);
		else
		{
			while(t->next)t=t->next;
			t->next=new ListNode(s);
		}
	}

	double totalArea()
	{
		double result=0;
		ListNode* t=head;
		while(t)
		{
			result+=t->value->area();
			t=t->next;
		}
		return result;
	}

	void drawAll()
	{
		ListNode* t=head;
		while(t)
		{
			t->value->draw();
			t=t->next;
		}
	}
	~Picture()
	{
		while(head)
		{
			ListNode* p=head->next;
			if(head->value)delete head->value;
			delete head;
			head=p;
		}
	}
private:
	struct ListNode
	{
		Shape* value;
		ListNode* next;
		ListNode(Shape* sp,ListNode* n=nullptr)
		{
			value=sp;
			next=n;
		}
	};
	ListNode* head;
};
#endif
