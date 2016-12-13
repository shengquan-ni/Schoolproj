#define STACK_CAPACITY 1000
class Stack
{
public:
	Stack()
	{
		_count=0;
	};

	void push(char c)
	{
		_stack[_count++]=c;
	}

	char pop()
	{
		return _stack[(_count--)-1];
	}

	char top()
	{
		return _stack[_count-1];
	}

	bool isEmpty()
	{
		return _count==0;
	}

	bool isFull()
	{
		return _count==STACK_CAPACITY;
	}
	
	~Stack()
	{

	}
private:
	int _stack[STACK_CAPACITY];
	int _count;
};
