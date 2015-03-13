#include <iostream>
#include <stack>

using namespace std;

template <class T, class C = class stack<T> > class queue
{
protected :
	C stack1;
	C stack2;
public :
	typedef typename C::value_type value_type;
    typedef typename C::size_type size_type;

    bool empty() const 
	{
		return (stack1.empty() || stack2.empty()); 
	}

    size_type size() const
	{
		return (stack1.size() + stack2.size());
	}

    void push(const value_type & x) 
	{
		stack1.push(x); 
	}

	const value_type & front()
	{
		if (stack2.size() != 0)
		{
			return stack2.top();
		}
		while (!stack1.empty())
		{
			T krap = stack1.top();
			stack2.push(krap);
			stack1.pop();
		}
		return stack2.top(); 
	}

	void emplace(const value_type & x) 
	{
		stack1.emplace(x); 
	}

    void pop() 
	{
		if (stack2.size() != 0)
		{
			stack2.pop();
			return;
		}
		while (!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
		stack2.pop();
		return;
	}
};

int main()
{
	queue <int> que;
	que.push(2);
	que.push(7);
	que.push(9);
	que.push(-1);
	que.pop();
	cout << que.empty() << endl;
	cout << que.front() << endl;
	cout << que.size() << endl;
	que.pop();
	que.emplace(88);
	return 0;
}