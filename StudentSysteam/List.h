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
		T m_nval; //������
		ListNode<T>* m_pPreNode = nullptr;//ǰ���
		ListNode<T>* m_pNextNode = nullptr;//����
	};
public:
	CMyList(const CMyList& obj);
	CMyList();
	~CMyList();

	//��������
	CMyList& operator=(const CMyList& obj);
	CMyList& operator+=(const CMyList& obj);
	CMyList& Append(const CMyList& obj);
	void Cat(const CMyList& obj);


	void AddTail(T nval);//��β���������
	void AddHead(T nval);//��ͷ���������
	void Insert(ListNode<T>* pNode, T nval, bool chose);//����λ��
	void Insert(ListNode<T>* pNode, T nval);
	void Delete(ListNode<T>* pNode);//ɾ��ָ��λ������
	void Updata(ListNode<T>* pNode, T nval); //�޸�ָ��λ��

	T GetVal(ListNode<T>* pNode);
	ListNode<T>* Find(T nval);//��������

	int GetLength()const; //ȡ������Ԫ�صĸ���
	void Clear();   //�������
	bool IsEmpty(); //�ж��Ƿ�Ϊ�ձ�

	ListNode<T>* GetHeapNode();
	ListNode<T>* GetTailNode();
	ListNode<T>* TagNode(int nPos);

	T GetHeapData() const;
	T GetTailData() const;

private:
	void InitWatch();
	void Copy(const CMyList& obj);

private:
	ListNode<T>* m_pHeadNode = nullptr;//ָ��ͷ���
	ListNode<T>* m_pTailNode = nullptr; //ָ��β���
	int m_nCount = 0; //Ԫ�ظ���

public:
	class CPosition
	{
	public:
		friend class CMyList<T>;
		T operator*()
		{
			return m_pNode->m_nval;
		}
		CPosition& operator++() //λ����������ƶ�
		{
			//��飬λ���Ƿ���β���ڱ�
			if (m_pNode->m_pNextNode != nullptr)
			{
				m_pNode = m_pNode->m_pNextNode;
			}
			return *this;
		}
		CPosition operator++(int)//λ������ƶ�
		{
			//�����ڱ�
			ListNode* pOld = m_pNode;
			if (m_pNode->m_pNextNode == nullptr)
			{
				return *this;
			}

			//û�е��ڱ�
			++(*this);
			return CPosition(pOld, m_pHeadNode, m_pTailNode);
		}
		CPosition& operator--()//λ����ǰ���ƶ�
		{
			//���λ���Ƿ���ͷ���ڱ�
			m_pNode = m_pNode->m_pPreNode;
			if (m_pNode == m_pHeadNode)
			{
				m_pNode = m_pNode->m_pNextNode;
			}
			return *this;
		}
		CPosition operator--(int)//λ����ǰ���ƶ�
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
	//��ʼ�������ڱ����
	InitWatch();
}

template<typename T>
CMyList<T>::CMyList(const CMyList& obj)
{
	//��ʼ�������ڱ����
	InitWatch();

	//��ͷ����Ŀ������
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
	chose=true ѡ��ָ��Ŀ��ǰ��ģʽ��
	chose=false ѡ��ָ��Ŀ����ģʽ
*/
template<typename T>
void  CMyList<T>::Insert(ListNode<T>* pNode, T nval, bool chose)
{
	int flag = IsEmpty();
	if (flag)
	{
		cout << "������Ϊ��" << endl;
		throw;
	}
	if (pNode == m_pHeadNode || pNode == m_pTailNode)
	{
		cout << "�ڱ���ʥ�����ַ�" << endl;
	}

	if (chose == true)
	{
		//ǰ�� pNodemĿ������

		//�����½��
		ListNode* pNewNode = new ListNode(nval);

		//����ָ������ǰһ������
		//��ǰһ�����ݵ�next
		ListNode* pOldPreNode = pNode->m_pPreNode;

		//ԭ���ݵ�ǰ����next�������������
		pOldPreNode->m_pNextNode = pNewNode;

		//�½���ǰ������Ӿɽ���ǰ���
		pNewNode->m_pPreNode = pOldPreNode;

		//�½���next���������
		pNewNode->m_pNextNode = pNode;

		//�����ݵ�ǰ���Ϊ������
		pNode->m_pPreNode = pNewNode;

		//����Ԫ������
		m_nCount++;
	}
	else if (chose == false)
	{
		//�����½��
		ListNode* pNewNode = new ListNode(nval);

		//����ָ�����ĺ�һ������
		ListNode* pOldPreNode = pNode->m_pNextNode;

		//ԭ���ݵ�ǰ���������������
		pOldPreNode->m_pPreNode = pNewNode;

		//�½��ĺ�������ǰ����
		//ǰ�������Ŀ������

		pNewNode->m_pNextNode = pOldPreNode;
		pNewNode->m_pPreNode = pNode;

		//ָ�����ĺ�������������
		pNode->m_pNextNode = pNewNode;

		//��������Ԫ�ظ���
		m_nCount++;

	}
}

template<typename T>
void  CMyList<T>::Insert(ListNode<T>* pNode, T nval)
{

	//ǰ�� pNodemĿ������

	//�����½��
	ListNode<T>* pNewNode = new ListNode<T>(nval);

	//����ָ������ǰһ������
	//��ǰһ�����ݵ�next
	ListNode<T>* pOldPreNode = pNode->m_pPreNode;

	//ԭ���ݵ�ǰ����next�������������
	pOldPreNode->m_pNextNode = pNewNode;

	//�½���ǰ������Ӿɽ���ǰ���
	pNewNode->m_pPreNode = pOldPreNode;

	//�½���next���������
	pNewNode->m_pNextNode = pNode;

	//�����ݵ�ǰ���Ϊ������
	pNode->m_pPreNode = pNewNode;

	//����Ԫ������
	m_nCount++;

}

//ɾ��ָ���������
template<typename T>
typename void CMyList<T>::Delete(ListNode<T>* pNode)
{
	if (pNode == nullptr)
	{
		throw "��ָ��";
	}
	//����ͷ��㱣��ָ��Ŀ���ǰ�����
	ListNode<T>* pOldPreNode;
	pOldPreNode = pNode->m_pPreNode;

	//����β��㱣��ָ��Ŀ��ĺ�̽��
	ListNode<T>* pOldNexNode;
	pOldNexNode = pNode->m_pNextNode;


	//ɾ�����
	delete pNode;

	//ǰ���ݵ�next���Ӻ����ݣ������ݵ�pre����ǰ����
	pOldPreNode->m_pNextNode = pOldNexNode;
	pOldNexNode->m_pPreNode = pOldPreNode;
	m_nCount--;
}
template<typename T>
void CMyList<T>::Updata(ListNode<T>* pNode, T NvalNew)
{
	if (pNode == nullptr)
	{
		cout << "��Ч" << endl;
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
	//ɾ�����н��
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
		return 0;//���ǿձ�
	}
}
template<typename T>
CMyList<T>::ListNode<T>*  CMyList<T>::Find(T nval)
{
	//��ͷ�����
	ListNode* FindNodeData = this->m_pHeadNode;
	int Index = 0;
	while (FindNodeData->m_pNextNode != this->m_pTailNode)
	{
		Index++;
		FindNodeData = FindNodeData->m_pNextNode;
		if (FindNodeData->m_nval == nval)
		{
			cout << "����������ĵ�" << Index << "Ԫ��" << endl;
			return FindNodeData;
		}

	}
	cout << "û�и�����" << endl;
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

//��ȡָ����Ŀ����
template<typename T>
 CMyList<T>::ListNode<T>* CMyList<T>::TagNode(int nPos)
{
	if (IsEmpty())
	{
		cout << "������Ϊ��" << endl;
		throw;
	}



	if (nPos == 0 || nPos > m_nCount)
	{
		cout << "�޷��ҵ�ָ�����" << endl;
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

	cout << "�޷��ҵ�ָ�����" << endl;
	return 0;
}

template<typename T>
void  CMyList<T>::InitWatch()
{
	//����ڱ����
	m_pHeadNode = new ListNode<T>(0);
	m_pTailNode = new ListNode<T>(0);

	m_pHeadNode->m_pNextNode = m_pTailNode;
	m_pTailNode->m_pPreNode = m_pHeadNode;

}
template<typename T>
typename CMyList<T>& CMyList<T>::operator=(const CMyList& obj)
{
	//�����������
	Clear();

	//��������
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