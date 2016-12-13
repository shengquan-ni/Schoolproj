#include "String.h"
String::String(const char* s)
{
	head=ListNode::stringToList(s);
}

String::String(const String& s)
{
	head=ListNode::copy(s.head);
}

String& String::operator = (const String& s)
{
	if(this!=&s)
		if(head)ListNode::deleteList(head);
		head=ListNode::copy(s.head);
	return *this;
}

char& String::operator [] (const int index)
{
	static char error='\0';
	ListNode* result=head;
	for(int i=0;i<index;++i)
		if(result)
			result=result->next;
		else
		{
			cerr<<"index out of range!!!"<<endl;
			return error;
		}
	return result->info;
}

String String::reverse()
{
	String result(*this);
	if(result.length()<2)return result;
	ListNode* p=result.head;
	ListNode* q=p->next;
	p->next=nullptr;
	while(q)
	{
		ListNode* temp=q->next;
	    q->next=p;
		p=q;
		q=temp;
	}
	result.head=p;
	return result;
}

int String::indexOf(char c)const
{
	int i=0;
	ListNode* l=head;
	while(l)
	{
		if(l->info==c)
			return i;
		++i;
		l=l->next;
	}
	return -1;
}

bool String::operator == (const String& s)const
{
	return ListNode::equal(head,s.head);
}

bool String::operator < (const String& s)const
{
	return ListNode::compare(head,s.head)<0;
}

String String::operator + (const String& s)const
{
	String res(*this);
	res+=s;
	return res;
}

String& String::operator += (const String& s)
{
	head=ListNode::concat(head,s.head);
	return *this;
}

void String::print(ostream& out)
{
	ListNode* l=head;
	while(l)
	{
		cout<<l->info;
		l=l->next;
	}
}

void String::read(istream& in)
{
	char s[256];
	cin>>s;
	ListNode::deleteList(head);
	head=ListNode::stringToList(s);
}

String::~String()
{
	ListNode::deleteList(head);
}

String::ListNode* String::ListNode::stringToList(const char* s)
{
	if(!*s)return nullptr;
	return new ListNode(*s,stringToList(s+1));
}

String::ListNode* String::ListNode::copy(ListNode* L)
{
	if(!L)return nullptr;
	return new ListNode(L->info,copy(L->next));
}

bool String::ListNode::equal(ListNode* L1,ListNode* L2)
{
	if(!L1 && !L2)return true;
	return L1 && L2 && L1->info==L2->info && equal(L1->next,L2->next);
}

String::ListNode* String::ListNode::concat(ListNode* L1,ListNode* L2)
{
	if(!L1)return copy(L2);
	ListNode* i=L1;
	while(i->next)i=i->next;
	i->next = copy(L2);
	return L1;
}

int String::ListNode::compare(ListNode* L1,ListNode* L2)
{
	int result=(L1?L1->info:0)-(L2?L2->info:0);
	return result?result:((L1&&L2)?compare(L1->next,L2->next):result);
}

void String::ListNode::deleteList(ListNode* L)
{
	if(!L)return;
	deleteList(L->next);
	delete L;
}


int String::ListNode::length(ListNode* L)
{
	if(!L)return 0;
	return length(L->next)+1;
}


ostream& operator << (ostream& out, String str)
{
	str.print(out);
	return out;
}

istream& operator >> (istream& in, String& str)
{
	str.read(in);
	return in;
}
