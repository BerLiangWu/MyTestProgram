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
	int m_nHeight = 1; //节点的高度
	AVLNode* m_pParent = nullptr; //指向父结点
	AVLNode* m_pLeft = nullptr;   //指向左结点
	AVLNode* m_pRight = nullptr;  //指向右结点
	AVLNode* SameName = nullptr;
};



class CAVLTree
{
	
	

public:
	CAVLTree()
	{
		m_pRoot = nullptr;
	}
	//带参拷贝构造
	CAVLTree(Student& stuobj)
	{
		m_pRoot = new AVLNode(stuobj);
	}
	
	
	~CAVLTree()
	{
	
	}

public:
	bool Insert(Student&stuobj); //插入数据-姓名查询树
	bool InsertMain(Student& stuobj); //主树，做数据操作
	bool Update(Student& valSrc, Student& valDst);//修改
	void CreateStudentData();
	bool Delete_Name(CMyString& stuname, int StuId); //姓名删除
	bool Delete_ID(int StuId);   //最上层接口，删除树方式按ID删除
	bool Find(CMyString& stuname); //查询
	bool Find(int id);
	void Leveloader(AVLNode* pNode);  //层序遍历
	bool MidOrder();//中序遍历
	bool SaveData(const char *FileName);//将数据写入文件（中序方式）
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
		//循环遍历
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
	void AdjustHeight(AVLNode* pNode);  //调整高度
	int  GetHeight(AVLNode* pNode);        //获取高度
	int  GetHeightByChilds(AVLNode* pNode);//通过子节点来获取高度
	void LeftSingleRotate(AVLNode* pNode); //左单旋 
public:
	void RightSingleRotate(AVLNode* pNode);
	void DeleteLeaf(AVLNode* pNodeToDel);         //删除叶子节点
	void DeleteSingleChild(AVLNode* pNodeToDel);  //删除只有一个孩子的结点
	void DeleteDoubleChilds(AVLNode* pNodeToDel); //删除有两个孩子的结点
public:
	AVLNode* m_pRoot = nullptr;
};


#endif