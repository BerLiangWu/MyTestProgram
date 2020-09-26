#pragma once

#ifndef AVLT_H_
#define AVLT_H_

#include "MyStack.h"
#include "Student.h"



struct AVLNode
{
	AVLNode(Student& stuobj, AVLNode* par = nullptr,
		AVLNode* pleft = nullptr, AVLNode* pright = nullptr,
		AVLNode* saname = nullptr, int hight = 1)
	{
		stu = &stuobj;
		m_pParent = par;
		m_pLeft = pleft;
		m_pRight = pright;
		SameName = saname;
	}
	~AVLNode()
	{

	}
	Student* stu;
	int m_nHeight = 1; //�ڵ�ĸ߶�
	AVLNode* m_pParent = nullptr; //ָ�򸸽��
	AVLNode* m_pLeft = nullptr;   //ָ������
	AVLNode* m_pRight = nullptr;  //ָ���ҽ��
	AVLNode* SameName = nullptr;
};



class CAVLTree
{
	
	

public:
	CAVLTree()
	{
		m_pRoot = nullptr;
	}
	//���ο�������
	CAVLTree(Student& stuobj)
	{
		m_pRoot = new AVLNode(stuobj);
	}
	
	
	~CAVLTree()
	{
	
	}

public:
	bool Insert(Student&stuobj); //��������-������ѯ��
	bool InsertMain(Student& stuobj); //�����������ݲ���
	bool Update(Student& valSrc, Student& valDst);//�޸�
	void CreateStudentData();
	bool Delete_Name(CMyString& stuname, int StuId); //����ɾ��
	bool Delete_ID(int StuId);   //���ϲ�ӿڣ�ɾ������ʽ��IDɾ��
	bool Find(CMyString& stuname); //��ѯ
	bool Find(int id);
	void Leveloader(AVLNode* pNode);  //�������
	bool MidOrder();//�������
	bool SaveData(const char *FileName);//������д���ļ�������ʽ��
	bool SearStudentName(CAVLTree* T);
	bool SearStudentId(CAVLTree*T, int id);
	
	AVLNode* GetRootNode()
	{	
		return m_pRoot;
	}

	AVLNode* FindNode(CMyString& stuname)
	{

		AVLNode* pNode = m_pRoot;
		while (pNode != nullptr)
		{
			if (strcmp(stuname.GetBuff(), pNode->stu->SzName.GetBuff()) > 0)
			{
				pNode = pNode->m_pRight;
			}
			else if (strcmp(stuname.GetBuff(), pNode->stu->SzName.GetBuff()) < 0)
			{
				pNode = pNode->m_pLeft;
			}
			else if (strcmp(stuname.GetBuff(), pNode->stu->SzName.GetBuff()) == 0)
			{
				return pNode;
			}
		}

		return nullptr;
	}


	AVLNode* FindNode(int id)
	{
		AVLNode* pNode = m_pRoot;
		//ѭ������
		while (pNode != nullptr) {
			if (id > pNode->stu->Student_ID)
			{
				pNode = pNode->m_pRight;
			}
			else if (id < pNode->stu->Student_ID)
			{
				pNode = pNode->m_pLeft;
			}
			else {
				return pNode;
			}
		}
		return nullptr;
	}



public:
	void AdjustHeight(AVLNode* pNode);  //�����߶�
	int  GetHeight(AVLNode* pNode);        //��ȡ�߶�
	int  GetHeightByChilds(AVLNode* pNode);//ͨ���ӽڵ�����ȡ�߶�
	void LeftSingleRotate(AVLNode* pNode); //���� 
public:
	void RightSingleRotate(AVLNode* pNode);
	void DeleteLeaf(AVLNode* pNodeToDel);         //ɾ��Ҷ�ӽڵ�
	void DeleteSingleChild(AVLNode* pNodeToDel);  //ɾ��ֻ��һ�����ӵĽ��
	void DeleteDoubleChilds(AVLNode* pNodeToDel); //ɾ�����������ӵĽ��
public:
	AVLNode* m_pRoot = nullptr;
};


#endif