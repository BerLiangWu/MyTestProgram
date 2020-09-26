#pragma once
#include<iostream>
using namespace std;
template<typename T>
class CMyList
{
public:
	template<typename T>
	struct ListNode
	{
		ListNode(T nval)
		{
			m_nval = nval;
		}
		T m_nval; //数据域
		ListNode<T>* m_pPreNode = nullptr;//前结点
		ListNode<T>* m_pNextNode = nullptr;//后结点
	};
public:
	CMyList(const CMyList& obj);
	CMyList();
	~CMyList();

	//几个重载
	CMyList& operator=(const CMyList& obj);
	CMyList& operator+=(const CMyList& obj);
	CMyList& Append(const CMyList& obj);
	void Cat(const CMyList& obj);


	void AddTail(T nval);//向尾部添加数据
	void AddHead(T nval);//向头部添加数据
	void Insert(ListNode<T>* pNode, T nval, bool chose);//任意位置
	void Insert(ListNode<T>* pNode, T nval);
	void Delete(ListNode<T>* pNode);//删除指定位置数据
	void Updata(ListNode<T>* pNode, T nval); //修改指定位置

	T GetVal(ListNode<T>* pNode);
	ListNode<T>* Find(T nval);//查找数据

	int GetLength()const; //取链表中元素的个数
	void Clear();   //清空链表
	bool IsEmpty(); //判断是否为空表

	ListNode<T>* GetHeapNode();
	ListNode<T>* GetTailNode();
	ListNode<T>* TagNode(int nPos);

	T GetHeapData() const;
	T GetTailData() const;

private:
	void InitWatch();
	void Copy(const CMyList& obj);

private:
	ListNode<T>* m_pHeadNode = nullptr;//指向头结点
	ListNode<T>* m_pTailNode = nullptr; //指向尾结点
	int m_nCount = 0; //元素个数

public:
	class CPosition
	{
	public:
		friend class CMyList<T>;
		T operator*()
		{
			return m_pNode->m_nval;
		}
		CPosition& operator++() //位置向链表后移动
		{
			//检查，位置是否到了尾部哨兵
			if (m_pNode->m_pNextNode != nullptr)
			{
				m_pNode = m_pNode->m_pNextNode;
			}
			return *this;
		}
		CPosition operator++(int)//位置向后移动
		{
			//到了哨兵
			ListNode* pOld = m_pNode;
			if (m_pNode->m_pNextNode == nullptr)
			{
				return *this;
			}

			//没有到哨兵
			++(*this);
			return CPosition(pOld, m_pHeadNode, m_pTailNode);
		}
		CPosition& operator--()//位置向前面移动
		{
			//检查位置是否到了头部哨兵
			m_pNode = m_pNode->m_pPreNode;
			if (m_pNode == m_pHeadNode)
			{
				m_pNode = m_pNode->m_pNextNode;
			}
			return *this;
		}
		CPosition operator--(int)//位置向前面移动
		{
			ListNode* pOld = m_pNode;
			if (m_pNode->m_pPreNode == m_pHeadNode)
			{
				return *this;
			}

			--(*this);
			return CPosition(pOld, m_pHeadNode, m_pTailNode);
		}

		bool operator==(const CPosition& posObj)
		{
			return (m_pNode == posObj.m_pNode);
		}
		bool operator!=(const CPosition& posObj)
		{
			return !(*this == posObj);
		}

	private:
		template<typename T>
		CPosition(ListNode<T>* pNode,
			ListNode<T>* pHeadNode,
			ListNode<T>* pTailNode)
		{
			m_pNode = pNode;
			m_pHeadNode = pHeadNode;
			m_pTailNode = pTailNode;
		}
		ListNode<T>* m_pNode = nullptr;
		ListNode<T>* m_pHeadNode = nullptr;
		ListNode<T>* m_pTailNode = nullptr;


	};

};



template<typename T>
CMyList<T>::CMyList()
{
	//初始化创建哨兵结点
	InitWatch();
}

template<typename T>
CMyList<T>::CMyList(const CMyList& obj)
{
	//初始化创建哨兵结点
	InitWatch();

	//从头遍历目标链表
	ListNode* pNode = obj.m_pHeadNode->m_pNextNode;
	for (int i = 0; i < obj.m_nCount; i++)
	{
		AddTail(pNode->m_nval);

		pNode = pNode->m_pNextNode;
	}


}

template<typename T>
CMyList<T>::~CMyList()
{


}


template<typename T>
typename void CMyList<T>::AddHead(T nval)
{
	Insert(m_pHeadNode->m_pNextNode, nval);
}

template<typename T>
typename void CMyList<T>::AddTail(T nval)
{
	Insert(m_pTailNode, nval);

}


/*
	chose=true 选择指定目标前插模式，
	chose=false 选择指定目标后插模式
*/
template<typename T>
void  CMyList<T>::Insert(ListNode<T>* pNode, T nval, bool chose)
{
	int flag = IsEmpty();
	if (flag)
	{
		cout << "该链表为空" << endl;
		throw;
	}
	if (pNode == m_pHeadNode || pNode == m_pTailNode)
	{
		cout << "哨兵神圣不可侵犯" << endl;
	}

	if (chose == true)
	{
		//前插 pNodem目标数据

		//创建新结点
		ListNode* pNewNode = new ListNode(nval);

		//保存指定结点的前一个数据
		//即前一个数据的next
		ListNode* pOldPreNode = pNode->m_pPreNode;

		//原数据的前数据next结点连接新数据
		pOldPreNode->m_pNextNode = pNewNode;

		//新结点的前结点连接旧结点的前结点
		pNewNode->m_pPreNode = pOldPreNode;

		//新结点的next保存旧数据
		pNewNode->m_pNextNode = pNode;

		//旧数据的前结点为新数据
		pNode->m_pPreNode = pNewNode;

		//链表元素增加
		m_nCount++;
	}
	else if (chose == false)
	{
		//创建新结点
		ListNode* pNewNode = new ListNode(nval);

		//保存指定结点的后一个数据
		ListNode* pOldPreNode = pNode->m_pNextNode;

		//原数据的前驱结点变成了新数据
		pOldPreNode->m_pPreNode = pNewNode;

		//新结点的后结点变成了前数据
		//前结点变成了目标数据

		pNewNode->m_pNextNode = pOldPreNode;
		pNewNode->m_pPreNode = pNode;

		//指定结点的后结点变成了新数据
		pNode->m_pNextNode = pNewNode;

		//链表增加元素个数
		m_nCount++;

	}
}

template<typename T>
void  CMyList<T>::Insert(ListNode<T>* pNode, T nval)
{

	//前插 pNodem目标数据

	//创建新结点
	ListNode<T>* pNewNode = new ListNode<T>(nval);

	//保存指定结点的前一个数据
	//即前一个数据的next
	ListNode<T>* pOldPreNode = pNode->m_pPreNode;

	//原数据的前数据next结点连接新数据
	pOldPreNode->m_pNextNode = pNewNode;

	//新结点的前结点连接旧结点的前结点
	pNewNode->m_pPreNode = pOldPreNode;

	//新结点的next保存旧数据
	pNewNode->m_pNextNode = pNode;

	//旧数据的前结点为新数据
	pNode->m_pPreNode = pNewNode;

	//链表元素增加
	m_nCount++;

}

//删除指定结点数据
template<typename T>
typename void CMyList<T>::Delete(ListNode<T>* pNode)
{
	if (pNode == nullptr)
	{
		throw "空指针";
	}
	//创建头结点保存指定目标的前驱结点
	ListNode<T>* pOldPreNode;
	pOldPreNode = pNode->m_pPreNode;

	//创建尾结点保存指定目标的后继结点
	ListNode<T>* pOldNexNode;
	pOldNexNode = pNode->m_pNextNode;


	//删除结点
	delete pNode;

	//前数据的next连接后数据，后数据的pre连接前数据
	pOldPreNode->m_pNextNode = pOldNexNode;
	pOldNexNode->m_pPreNode = pOldPreNode;
	m_nCount--;
}
template<typename T>
void CMyList<T>::Updata(ListNode<T>* pNode, T NvalNew)
{
	if (pNode == nullptr)
	{
		cout << "无效" << endl;
	}
	pNode->m_nval = NvalNew;
}
template<typename T>
T CMyList<T>::GetVal(ListNode<T>* pNode)
{
	return pNode->m_nval;
}
template<typename T>
int CMyList<T>::GetLength()const
{
	return m_nCount;
}
template<typename T>
void CMyList<T>::Clear()
{
	//删除所有结点
	int count = m_nCount;
	for (int i = 1; i < count; i++)
	{
		this->Delete(this->TagNode(i));
	}
	m_nCount = 0;
}


template<typename T>
bool  CMyList<T>::IsEmpty()
{
	if (this->m_pHeadNode->m_pNextNode == this->m_pTailNode)
	{
		return 1;
	}
	else
	{
		return 0;//不是空表
	}
}
template<typename T>
CMyList<T>::ListNode<T>*  CMyList<T>::Find(T nval)
{
	//从头结点找
	ListNode* FindNodeData = this->m_pHeadNode;
	int Index = 0;
	while (FindNodeData->m_pNextNode != this->m_pTailNode)
	{
		Index++;
		FindNodeData = FindNodeData->m_pNextNode;
		if (FindNodeData->m_nval == nval)
		{
			cout << "数据是链表的第" << Index << "元素" << endl;
			return FindNodeData;
		}

	}
	cout << "没有该数据" << endl;
	return 0;
}
template<typename T>
 CMyList<T>::ListNode<T>* CMyList<T>::GetHeapNode()
{
	return m_pHeadNode->m_pNextNode;
}

template<typename T>
 CMyList<T>::ListNode<T>* CMyList<T>::GetTailNode()
{
	return m_pTailNode->m_pPreNode;
}
template<typename T>
T CMyList<T>::GetHeapData() const
{
	return m_pHeadNode->m_pNextNode->m_nval;
}
template<typename T>
T CMyList<T>::GetTailData() const
{
	return m_pTailNode->m_pPreNode->m_nval;
}

//获取指定的目标结点
template<typename T>
 CMyList<T>::ListNode<T>* CMyList<T>::TagNode(int nPos)
{
	if (IsEmpty())
	{
		cout << "该链表为空" << endl;
		throw;
	}



	if (nPos == 0 || nPos > m_nCount)
	{
		cout << "无法找到指定结点" << endl;
		throw;
	}

	ListNode* FindNodeData = FindNodeData = this->m_pHeadNode;
	int Index = 0;
	while (FindNodeData->m_pNextNode != this->m_pHeadNode)
	{

		if (Index == nPos)
		{
			return FindNodeData;
		}
		Index++;
		FindNodeData = FindNodeData->m_pNextNode;


	}

	cout << "无法找到指定结点" << endl;
	return 0;
}

template<typename T>
void  CMyList<T>::InitWatch()
{
	//添加哨兵结点
	m_pHeadNode = new ListNode<T>(0);
	m_pTailNode = new ListNode<T>(0);

	m_pHeadNode->m_pNextNode = m_pTailNode;
	m_pTailNode->m_pPreNode = m_pHeadNode;

}
template<typename T>
typename CMyList<T>& CMyList<T>::operator=(const CMyList& obj)
{
	//清除已有数据
	Clear();

	//拷贝数据
	Cat(obj);

	return *this;
}
template<typename T>
void  CMyList<T>::Cat(const CMyList& obj)
{
	ListNode* pNode = obj.m_pHeadNode->m_pNextNode;

	for (int i = 0; i < obj.m_nCount; i++)
	{
		AddTail(pNode->m_nval);

		pNode = pNode->m_pNextNode;
	}
}
template<typename T>
typename CMyList<T>& CMyList<T>::Append(const  CMyList& obj)
{
	Cat(obj);
	return *this;
}
template<typename T>
typename CMyList<T>& CMyList<T>::operator+=(const CMyList& obj)
{
	Cat(obj);

	return *this;
}