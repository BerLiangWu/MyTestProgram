#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "CMyString.h"
#include "MyStack.h"

# define Left_H 1 
# define EH 0   //平衡
# define Right_H -1
# define TRUE 1
# define FALSE 0
# define MAX  1000
bool Taller = 0;   //插入时反映树是否长高0不长高  1长高
bool Shorter;    //删除时时反映树是否长高0不长高  1长高


using namespace std;
typedef struct AVLNode
{	
	Student stu;
	int bf=0;//balance factor平衡判断因素
	struct AVLNode* m_pLeft = nullptr;   //指向左结点
	struct AVLNode* m_pRight = nullptr;  //指向右结点

}AVLNode,* AVLTree;

void Delete(AVLTree& T);
AVLTree LeftBalance(AVLTree T);
AVLTree RightBalance(AVLTree T);
void Delete_LeftBalance(AVLTree& T);
void Delete_RightBalance(AVLTree& T);
//对以 p为跟根结点的二叉树进行右旋
//处理左子树的根节点
AVLTree R_rotate(AVLTree p)
{
	AVLNode* Lc; //左孩子结点
	
	Lc = p->m_pLeft; 
	p->m_pLeft = Lc->m_pRight;

	Lc->m_pRight = p;
	p = Lc;

	return p;
}

//对以 p为跟根结点的二叉树进行左旋
//处理右子树的根节点
AVLTree L_Rotate(AVLTree p)
{
	AVLNode* Rc;//右孩子结点
	Rc = p->m_pRight;
	p->m_pRight = Rc->m_pLeft;
	Rc->m_pLeft = p;
	p = Rc;
	return p;
}
//左结点平衡判断
AVLTree LeftBalance(AVLTree T)
{
	//对以T所指向结点为根的二叉树进行左旋
	
	
	AVLNode* Lc;//创建左孩子结点
	AVLNode* Rc;//创建右孩子结点
	Lc = T->m_pLeft;
	//检查平衡度
	//进行平衡度处理
	switch (Lc->bf)
	{
	
	//当为1左高时
		//新结点插入在T的左孩子的左叶子上，作右旋
	case Left_H:
		T->bf = Lc->bf = EH;
		T = R_rotate(T);
		break;
		//当为-1右高时
		//新结点插在左的右子树上，作双旋
	case Right_H:
		Rc = Lc->m_pRight;
		switch (Rc->bf)
		{
		case Left_H:
			T->bf = Right_H;
			Lc->bf = EH;
			break;
		case EH:
			T->bf = Lc->bf = EH;
			break;
		case Right_H:
			T->bf = EH;
			Lc->bf = Left_H;
			break;
		
		}
		//指针T指向新的根结点
		Rc->bf = EH;
		T->m_pLeft = L_Rotate(T->m_pLeft);
		T = R_rotate(T);
	}

	return T;
}

// 对以指针T所指结点为根的二叉树作右平衡旋转处理
AVLTree RightBalance(AVLTree T)
{       
	AVLNode* Lc;//创建左孩子结点
	AVLNode* Rc;//创建右孩子结点
	Rc = T->m_pRight;
	switch (Rc->bf)
	{               // 检查*T的右子树的平衡度，并作相应平衡处理
	case Right_H:        // 新结点插入在*T的右孩子的右子树上，要作单左旋处理
		T->bf = Rc->bf = EH;
		T = L_Rotate(T);
		break;
	case Left_H:        // 新结点插入在*T的右孩子的左子树上，要作双旋处理
		Lc = Rc->m_pLeft;
		switch (Lc->bf)
		{            // 修改*T及其右孩子的平衡因子
		case Left_H:
			T->bf = Left_H;
			Rc->bf = EH;
			break;
		case EH:
			T->bf = Rc->bf = EH;
			break;
		case Right_H:
			T->bf = EH;
			Rc->bf = Right_H;
			break;
		}
		Lc->bf = EH;
		T->m_pRight = R_rotate(T->m_pRight);
		T = L_Rotate(T);
	}
	return T;
}
//插入平衡二叉树
//若在平衡的二叉树T中不存在和S右相同数据的结点
//则插入一个新结点 并且返回1否则返回0
//插入后判断是否平衡
AVLTree InsertAVL(AVLTree T, AVLTree S)
{
	AVLTree p;
	//如果树是空的
	if (!T)
	{
		//插入新结点，树层数变高，让布尔标志Taller为真
		T = S;
		T->m_pLeft = T->m_pRight = nullptr;
		T->bf = EH;
		Taller = TRUE;
	}
	else
	{
		if (S->stu.Student_ID == T->stu.Student_ID)
		{
			//如果树中存在相同数据则不插入
			cout<<"存在相同学号"<<endl;
			system("pause");
			Taller = FALSE;
			return NULL;
		}
		if (S->stu.Student_ID<T->stu.Student_ID)
		{
			p = InsertAVL(T->m_pLeft, S);
			if (p)
			{
				T->m_pLeft = p;
				//检查高度
				if (Taller)
				{
					switch (T->bf)
					{
						//原左比右高，对左平衡处理
					case Left_H:
						T = LeftBalance(T);
						Taller = FALSE;
						break;
						//原本左右等高，左插入而左高了
					case EH:
						T->bf = Left_H;
						Taller = TRUE;
						break;
						//原本右高，现在等高
					case Right_H:
						T->bf = EH;
						Taller = FALSE;
						break;
					}
				}


			}
		}
		else
		{
			//继续在T中右子树搜索
			p = InsertAVL(T->m_pRight, S);
			if (p)
			{	
				T->m_pRight = p;
				if (Taller)
				{
					switch (T->bf)
					{
						//原本左比右高，现在等高
					case Left_H:
						T->bf = EH;
						Taller = FALSE;
						break;
						//原本左，右等高，现在右高
					case EH:
						T->bf = Right_H;
						Taller = FALSE;
						break;
						//原本右比左高，对右做平衡
					case Right_H:
						T = RightBalance(T);
						Taller = FALSE;
						break;
				
					}
				}
			}
		}
	}
	return T;
}

//递归中序遍历
void Midorder(AVLTree T)
{
	if (T)
	{
		Midorder(T->m_pLeft);
		T->stu.StuIF();
		Midorder(T->m_pRight);
	}
}

//保证删除结点之后树仍然平衡
int DeleteAVL(AVLTree& T, int id)
{
	if (T==nullptr)
	{
		cout << "需要删除的编号不存在" << endl;
		system("pause");
		return 0;
	}
	else
	{
		if (id == T->stu.Student_ID)
		{
			Delete(T);
			cout << "已删除目标学生" << endl;
			system("pause");
		}
		//如果找不到
		else
		{
			if (id < T->stu.Student_ID)
			{
				DeleteAVL(T->m_pLeft, id);
				if (Shorter == true)
				{
					switch (T->bf)
					{
					case Left_H:
						T->bf = EH;
						Shorter = true;
						break;
					case EH:
						T->bf = Right_H;
						Shorter = false;
						break;
					case Right_H:
						Delete_RightBalance(T);
						Shorter = true;
						break;
					}
				}
			}
			else
			{
				DeleteAVL(T->m_pRight, id);
				if (Shorter == true)
				{
					switch (T->bf)
					{
					case Left_H:
						Delete_LeftBalance(T);
						Shorter = true;
						break;
					case EH:
						T->bf = Left_H;
						Shorter = true;
						break;
					case Right_H:
						T->bf = EH;
						Shorter = true;
						break;
					}
				}
			}
		}
	}
	return 1;
}
//删除结点，从二叉树中删除结点，并且重新接左右子树
void Delete(AVLTree& T)
{
	AVLTree p;  //待删除结点
	AVLTree q;
	int number;  //新结点编号
	p = T;
	//右子树为空重新接左子树
	if (!T->m_pRight)
	{
		T = T->m_pLeft;
		free(p);
		Shorter = true;
	}
	//右子树为空重新接右子树
	else if (!T->m_pLeft)
	{
		T = T->m_pRight;
		free(p);
		Shorter = true;
	}
	//如果左右子树都不为空树
	else
	{
		q = T->m_pLeft;
		while (q->m_pRight)
		{
			//左旋，然后换到右边
			p = q;
			q = q->m_pRight;
		}
		number = q->stu.Student_ID;
		T->stu.Student_ID = number;
	}
}
//删除之后右边失衡对右处理
void Delete_RightBalance(AVLTree& T)
{
	//创建两个临时树
	AVLTree s = T->m_pRight;
	AVLTree t;

	switch (s->bf)
	{
	case Left_H:
		t = s->m_pLeft;
		s->m_pLeft = t->m_pRight;
		t->m_pRight = s;
		T->m_pRight = t->m_pLeft;
		t->m_pLeft = T;
		//检查t树平衡情况
		switch (t->bf)
		{
		case Left_H:
			T->bf = EH;
			s->bf = Right_H;
			break;
		case EH:
			T->bf = EH;
			s->bf = EH;
			break;
		case Right_H:
			T->bf = Left_H;
			s->bf = EH;
			break;
		}
		t->bf = EH;
		T = t;
		Shorter = true;
		break;
	case EH:
		T->m_pRight = s->m_pLeft;
		s->m_pLeft= T;
		s->bf = Left_H;
		T->bf = Right_H;
		T = s;
		Shorter = EH;
		break;
	case Right_H:
		T->m_pRight = s->m_pLeft;
		s->m_pLeft = T;
		s->bf = T->bf = EH;
		T = s;

		Shorter = true;
		break;
	}

}
//删除之后左边失衡对左处理
void Delete_LeftBalance(AVLTree& T)
{
	//创建两个临时树
	AVLTree p1;
	AVLTree p2;
	p1 = T->m_pLeft;
	switch (p1->bf)
	{
		//如果左失衡
	case Left_H:
		T->m_pLeft = p1->m_pRight;
		p1->m_pRight = T;
		p1->bf = T->bf = EH;
		T = p1;
		Shorter = true;
		break;
		//如果平衡
	case EH:
		T->m_pLeft = p1->m_pRight;
		p1->m_pRight = T;
		p1->bf = Right_H;
		T->bf = Left_H;
		T = p1;
		Shorter = false;
		break;
		////如果右失衡
	case Right_H:
		p2 = p1->m_pRight;
		p1->m_pRight = p2->m_pLeft;
		p2->m_pLeft = p1;
		T->m_pLeft = p2->m_pRight;
		p2->m_pRight = T;
		//判断p2
		switch (p2->bf)
		{
		case Left_H:
			T->bf = Right_H;
			p1->bf = EH;
			break;
		case EH:
			T->bf = EH;
			p1->bf = EH;
			break;
		case Right_H:
			T->bf = EH;
			p1->bf = Left_H;
			break;
		}
		p2->bf = EH;
		T = p2;
		Shorter = true;
		break;
	}

}

int SearchAVT_Id(AVLTree T, int id)
{
	//临时结点
	AVLTree p;
	if (T==nullptr)
	{
		cout << "搜索不到相关学生" << endl;
		return 0;
	}
	else if (T->stu.Student_ID == id)
	{
		p = T;
		T->stu.StuIF();
		return 1;
	}
	else if (id < T->stu.Student_ID)
	{
		return SearchAVT_Id(T->m_pLeft, id);
	}
	else
	{
		return SearchAVT_Id(T->m_pRight, id);
	}
	return 0;
}

int SearchAVT_Name(AVLTree T, const char name[10])
{	
	int flag = 0;
	if (T ==nullptr)
	{	
		cout << "搜索不到相关学生" << endl;
		return 0;
	}
	AVLNode* cur1 = T;
	AVLNode* cur2 = NULL;
	while (cur1!=nullptr)
	{
		cur2 = cur1->m_pLeft;
		if (cur2 != nullptr)
		{
			while (cur2->m_pRight==nullptr&&cur2->m_pRight!=cur1)
			{
				cur2 = cur2->m_pRight;
			}
			if (cur2->m_pRight == nullptr)
			{
				cur2->m_pRight = cur1;
				cur1 = cur1->m_pLeft;
				continue;
			}
			else
			{
				cur2->m_pRight = nullptr;
			}
		}
		if (strcmp(cur1->stu.SzName.GetBuff(), name) == 0)
		{	
			cur1->stu.StuIF();
			flag = 1;
			
		}
		cur1 = cur1->m_pRight;
	}
	cout << endl;
	if (flag == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

AVLTree SearchAVT_Updata_ID(AVLTree T, int id)
{
	//临时结点
	AVLTree p;
	if (T == nullptr)
	{
		cout << "搜索不到相关学生" << endl;
		return 0;
	}
	else if (T->stu.Student_ID == id)
	{
		p = T;
		T->stu.StuIF();
		system("pause");
		return T;
	}
	else if (id < T->stu.Student_ID)
	{
		return SearchAVT_Updata_ID(T->m_pLeft, id);
	}
	else
	{
		return SearchAVT_Updata_ID(T->m_pRight, id);
	}
	return 0;
}




//保存数据
void Save(AVLTree T, const char*a)
{
	ofstream outFile(a, ios::out|ios::binary);
	MyStack<AVLTree> sta;
	//中序递归遍历写入文件
	while (T!=nullptr||sta.IsEmpaty()!=1)
	{	//不为空 入栈
		while (T != nullptr)
		{
			sta.Push(T);
			T = T->m_pLeft;
		}

		if (sta.IsEmpaty()!= 1)
		{
			T = sta.Top();
			outFile << T->stu.Student_ID <<" "<< T->stu.SzName.GetBuff()<<" " << T->stu.YearsOfBirth<< " " << T->stu.DataOfBirth <<" " << T->stu.Gender.GetBuff() << endl;

			sta.Pop();
			T = T->m_pRight;
		}

	}
	//关闭文件
	outFile.clear();
	outFile.close();
}

//创建随机学生文件
void CreateStudentData()
{
	 char StudentName[10] = { '\0' }; //名字
	 unsigned int yearsOfBirth;		//出生年份
	 unsigned int dataOfBirth;		//出生日月
	 char Gend[4] = { '0' };  //性别
	 char RandCHose = 0;
	 int StudentId = 1;//学号 初始值为1

	 srand((unsigned)time(NULL));

	 ofstream CreaFile("MinStudent.bin", ios::out |ios::app| ios::binary);

	 //循环生成学生数据
	 for (int IdCount = 0; IdCount<100000; IdCount++)
	 {
		 char SzName;
		 memset(StudentName, '\0', sizeof(StudentName));
		 //随机因子
		 for (int  RandF = 0; RandF <(rand()%9+1); RandF++)
		 {
			 SzName = (rand() % 2) ? ('a' + rand() % 26) : ('A' + rand() % 26);
			 StudentName[RandF] = SzName;
		 }

		 yearsOfBirth = rand() % (1201) + 1800; //1800-3000 n-m+1 +m
		 dataOfBirth = rand() % (1131) + 0101;//0101-1231


		 //设置性别
		 RandCHose = rand() % (2) + 1;
		 if (RandCHose == 1)
		 {
			 strcpy(Gend, "男");
		 }
		 else
		 {
			 strcpy(Gend, "女");
		 }

		 //新建一个树结点

		 AVLTree SD = new AVLNode;
		 SD->stu.Student_ID = StudentId;
		 SD->stu.SzName = CMyString(StudentName);
		 SD->stu.YearsOfBirth = yearsOfBirth;
		 SD->stu.DataOfBirth = dataOfBirth;
		 SD->stu.Gender = CMyString(Gend);
		 CreaFile << SD->stu.Student_ID << " " << SD->stu.SzName.GetBuff() << " " << SD->stu.YearsOfBirth << " " << SD->stu.DataOfBirth << " " << SD->stu.Gender.GetBuff() << endl;
		 
		 StudentId++;
	 }
	 cout << "创建完成" << endl;
	 system("pause");
	 CreaFile.clear();
	 CreaFile.close();
	 

}
