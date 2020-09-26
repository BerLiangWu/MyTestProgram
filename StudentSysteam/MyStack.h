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
	bool IsEmpaty();  //����1Ϊ�ձ�����0���ǿձ�
	ST Top();
private:
	CMyList<ST> Stack;
};


//�Ƚ���� ͷ��
template<typename ST>
void MyStack<ST>::Push(ST val)
{
	Stack.AddHead(val);
}


//ͷԪ�س�ջ
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

//����ջ��Ԫ��
template<typename ST>
ST  MyStack<ST>::Top()
{
	return Stack.GetHeapData();
}

//�ж�ջ�Ƿ�Ϊ��
template<typename ST>
bool MyStack<ST>::IsEmpaty()
{
	return Stack.IsEmpty();
}
