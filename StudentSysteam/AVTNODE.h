#include "Student.h"


struct AVLNode
{
	Student stu;
	AVLNode* m_pParent = nullptr; //ָ�򸸽��
	AVLNode* m_pLeft = nullptr;   //ָ������
	AVLNode* m_pRight = nullptr;  //ָ���ҽ��
};
