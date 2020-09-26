#include "Student.h"


struct AVLNode
{
	Student stu;
	AVLNode* m_pParent = nullptr; //指向父结点
	AVLNode* m_pLeft = nullptr;   //指向左结点
	AVLNode* m_pRight = nullptr;  //指向右结点
};
