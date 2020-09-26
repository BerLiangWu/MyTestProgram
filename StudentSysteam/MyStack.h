#pragma once
#include"List.h"

template<typename ST>
class MyStack
{
public:
	MyStack() {};
	~MyStack() {};
	void Push(ST val);
	void Pop();
	int Size();
	bool IsEmpaty();  //返回1为空表，返回0不是空表
	ST Top();
private:
	CMyList<ST> Stack;
};


//先进后出 头插
template<typename ST>
void MyStack<ST>::Push(ST val)
{
	Stack.AddHead(val);
}


//头元素出栈
template<typename ST>
void MyStack<ST>::Pop()
{
	Stack.Delete(Stack.GetHeapNode());
}

template<typename ST>
int  MyStack<ST>::Size()
{
	return Stack.GetLength();
}

//访问栈顶元素
template<typename ST>
ST  MyStack<ST>::Top()
{
	return Stack.GetHeapData();
}

//判断栈是否为空
template<typename ST>
bool MyStack<ST>::IsEmpaty()
{
	return Stack.IsEmpty();
}
