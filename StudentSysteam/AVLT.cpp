#define _CRT_SECURE_NO_WARNINGS


#include "AVLT.h"
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;



bool CAVLTree::Insert(Student& stuobj)
{
	//新建结点
	AVLNode* pNewNode = new AVLNode(stuobj);

	//如果是空树,则新结点直接为根结点
	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
		return true;
	}

	//如果不是空树, 遍历,直到遇到叶子节点, 将新结点加入到树中
	AVLNode* pNode = m_pRoot;
	while (true)
	{
		//如果插入的值小于比较结点,则取比较结点的左孩子
		if (strcmp(stuobj.SzName.GetBuff(),pNode->stu->SzName.GetBuff())<0)
		{
			//如果比较结点没有左孩子,则新结点作为左孩子进入树
			if (pNode->m_pLeft == nullptr)
			{
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pLeft;
		}
		//如果插入的值大于比较结点,则取比较结点的右孩子
		else if (strcmp(stuobj.SzName.GetBuff(), pNode->stu->SzName.GetBuff()) >0)
		{
			//如果比较结点没有右孩子,则新结点作为右孩子进入树
			if (pNode->m_pRight == nullptr)
			{
				pNode->m_pRight = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pRight;
		}
		else if(strcmp(stuobj.SzName.GetBuff(), pNode->stu->SzName.GetBuff()) ==0)
		{	
			if (pNode->SameName == nullptr)
			{
				pNewNode->SameName = nullptr;
				pNode->SameName = pNewNode;
			}
			else
			{	
				pNode = pNode->SameName;
				while (1)
				{
					if (pNode->SameName == nullptr)
					{
						break;
					}
					pNode = pNode->SameName;
				}
				//链表最后一个结点
				pNewNode->SameName = nullptr;
				pNode->SameName = pNewNode;
			}
			
			break;
		}
	}

	//调整高度
	AdjustHeight(pNewNode);
	return true;
}

bool CAVLTree::InsertMain(Student& stuobj)
{	
	AVLNode* pNewNode = new AVLNode(stuobj);

	//如果是空树,则新结点直接为根结点
	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
		return true;
	}

	//如果不是空树, 遍历,直到遇到叶子节点, 将新结点加入到树中
	AVLNode* pNode = m_pRoot;

	while (true)
	{
		//如果插入的值小于比较结点,则取比较结点的左孩子
		if (stuobj.Student_ID<pNode->stu->Student_ID)
		{
			//如果比较结点没有左孩子,则新结点作为左孩子进入树
			if (pNode->m_pLeft == nullptr)
			{
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pLeft;
		}
		//如果插入的值大于比较结点,则取比较结点的右孩子
		else if (stuobj.Student_ID >pNode->stu->Student_ID)
		{
			//如果比较结点没有右孩子,则新结点作为右孩子进入树
			if (pNode->m_pRight == nullptr)
			{
				pNode->m_pRight = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pRight;
		}
		else 
		{
			cout << "该值已经存在" << endl;
			system("pause");
			return false;
		}
	}

	//调整高度
	AdjustHeight(pNewNode);
	return true;


	
}

bool CAVLTree::Update(Student& valSrc, Student& valDst)
{
	if (!Find(valSrc.Student_ID))
	{
		return false;
	}

	Delete_ID(valSrc.Student_ID);
	Insert(valDst);

}

//void CAVLTree::Update(int valSrc, int valDst)
//{
//	Delete(valSrc);
//	Insert(valDst);
//}


bool CAVLTree::Delete_Name(CMyString& stuname, int StuId)
{
	AVLNode* pNode = FindNode(stuname);
	if (pNode == nullptr)
	{	
		cout << "不存在该名学生" << endl;
		system("pause");
		return false;
	}
	//当存在同名时
	//利用哈希表的方式 将同名挂载了链表的学生属性，跟前一个做数据交换 删除前一个
	//因为不能破坏树的生态结构
	AVLNode* SameStu = pNode->SameName;

	//如果时存在同名
	if (SameStu != nullptr)
	{
		//查看哪个是他

		//假如该结点就是要删除的
		//即为头结点
		if (pNode->stu->Student_ID == StuId)
		{
			//和后一个交换数据

			AVLNode* Next = SameStu->SameName; //下一个的下一个

			//如果下一个也不为空
			if (Next!=nullptr)
			{
				pNode->stu = SameStu->stu;   //先做一次交换

				//此时SameStu已经被存储
				while (Next != nullptr)
				{	
					//把后面的逐个拿上来
					SameStu->stu = Next->SameName->stu;

					//两个都往后移动
					Next = Next->SameName;
					SameStu = SameStu->SameName;
				}
				//当后面没有后做最后一次交换
				SameStu->stu = Next->stu;

				delete Next;
				SameStu->SameName = nullptr;//后面放空
				return true;
			}
			//如果下一个是空的
			else
			{	
				//做交换
				pNode->stu = SameStu->stu;

				//删除后面
				delete SameStu;
				pNode->SameName = nullptr;//后面放空
				return true;
			}
			
			
		}
		//头结点并不是要删除的数据
		else
		{
			//移动next指针
			while (1)
			{	
				if (SameStu->stu->Student_ID == StuId)
				{
					break;
				}
				else if (SameStu->SameName == nullptr)
				{	
					cout << "找不到该名学生" << endl;
					system("pause");
					return false;
				}
				pNode = SameStu;
				SameStu = SameStu->SameName;

			}

			//找到了 samestu就是要删除的
			AVLNode* Next = SameStu->SameName; //下一个的下一个
			//如果下一个也不为空
			if (Next != nullptr)
			{
				SameStu->stu = Next->stu;   //先做一次交换
				//此时Next已经被存储
				
				//1 ,2(SAmStu),3(Next)
				//      pre
				//     SameName        Next
				//1,2(Next->stu),3(SameName->same)

				AVLNode* pre = SameStu;  //移动前记录一下位置
				
				SameStu->SameName = Next;
				Next = Next->SameName;  //4
				SameStu = SameStu->SameName;//3
				pre->SameName = SameStu;  //2
				//3后面不为空
				if (Next != nullptr)
				{
					while (Next != nullptr)
					{
						//把后面的逐个拿上来
						SameStu->stu = Next->stu;

						//两个都往后移动
						Next = Next->SameName;
						SameStu = SameStu->SameName;
						pre = pre->SameName;
					}

					delete Next;
					pre->SameName = SameStu;
					SameStu->SameName = nullptr;//后面放空
					return true;
				}
				else
				{
					 ///如果是空的 ，此时3就是SameStu
					pre->SameName = nullptr;
					delete SameStu;
					return true;

				}
				
			}
			//如果下一个是空的  SameStu就是要删除的

			else
			{	
				pNode->SameName =nullptr;  //后面放空
				
				delete SameStu;
				return true;

			}
		}
	}



	

	//当不存在同名时
	//如果是叶子节点
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DeleteLeaf(pNode);
	}
	//只有一个孩子
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DeleteSingleChild(pNode);
	}
	//有两个孩子
	else
	{
		DeleteDoubleChilds(pNode);
	}

	return true;
}

bool CAVLTree::Delete_ID(int StuId)
{	
	AVLNode* pNode = FindNode(StuId);

	if (pNode == nullptr)
	{
		return false;
	}

	
	//如果是叶子节点
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DeleteLeaf(pNode);
	}
	//只有一个孩子
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DeleteSingleChild(pNode);
	}
	//有两个孩子
	else
	{
		DeleteDoubleChilds(pNode);
	}

	return true;
}

bool CAVLTree::Find(CMyString& stuname)
{
	if (FindNode(stuname) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CAVLTree::Find(int id)
{
	if (FindNode(id) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//void CAVLTree::Leveloader(AVLNode* pNode)
//{
//	queue<AVLNode*> que;
//
//	AVLNode* front;
//
//	if (pNode == nullptr)
//	{
//		return;
//	}
//
//	que.push(pNode);
//
//	while (!que.empty())
//	{
//		front = que.front();
//		que.pop();
//
//		if (front->m_pLeft != nullptr)
//		{
//			que.push(front->m_pLeft);
//		}
//
//
//		if (front->m_pRight != nullptr)
//		{
//			que.push(front->m_pRight);
//		}
//
//		cout << front->m_val <<endl;
//	}
//}




void CAVLTree::AdjustHeight(AVLNode* pNode)
{
	//沿着父节点的路线，调整所有父节点的高度
	AVLNode* pNodeToAdjust = pNode;
	while (pNodeToAdjust != nullptr)
	{
		pNodeToAdjust->m_nHeight = GetHeightByChilds(pNodeToAdjust);

		//调整高度的过程中，判断节点是否平衡
		int nLeftHeight = GetHeight(pNodeToAdjust->m_pLeft);
		int nRightHeight = GetHeight(pNodeToAdjust->m_pRight);

		//右孩子的高度与左孩子的高度差大于1,左旋
		if (nRightHeight - nLeftHeight > 1)
		{
			AVLNode* pA = pNodeToAdjust;
			AVLNode* pB = pA->m_pRight;

			int nHeightOfBLeft = GetHeight(pB->m_pLeft);
			int nHeightOfBRight = GetHeight(pB->m_pRight);

			/*左单旋
			  A                 B
				B        -->  A   C
				  C
			*/
			if (nHeightOfBRight > nHeightOfBLeft)
			{
				LeftSingleRotate(pNodeToAdjust);
			}
			/*先右旋, 再左旋
				A             A                    C
					B  -->       C      -->      A   B
				 C                  B

			 双旋: 先是沿着B右旋, 再沿着A左旋
		   */
			else
			{
				RightSingleRotate(pB);
				LeftSingleRotate(pA);
			}
		}
		//左孩子的高度与右孩子的高度差大于1,右旋
		else if (nLeftHeight - nRightHeight > 1)
		{
			AVLNode* pA = pNodeToAdjust;
			AVLNode* pB = pA->m_pLeft;

			int nHeightOfBLeft = GetHeight(pB->m_pLeft);
			int nHeightOfRight = GetHeight(pB->m_pRight);

			/* 右单旋
				   A
				 B
			  C
			*/
			if (nHeightOfBLeft > nHeightOfRight)
			{
				RightSingleRotate(pA);
			}
			/* 两次旋转
				 A               A              C
			  B         -->    C       -->    B   A
				 C           B

			 旋转过程: 显示沿着B左旋,接着沿着A右旋
			*/
			else
			{
				LeftSingleRotate(pB);
				RightSingleRotate(pA);
			}
		}


		pNodeToAdjust = pNodeToAdjust->m_pParent;
	}
}

int CAVLTree::GetHeight(AVLNode* pNode)
{
	return pNode == nullptr ? 0 : pNode->m_nHeight;
}

int  CAVLTree::GetHeightByChilds(AVLNode* pNode)
{
	//父节点的高度，为左孩子和右孩子高度较大的值 + 1
	int nHeightOfLeft = GetHeight(pNode->m_pLeft);
	int nHeightOfRight = GetHeight(pNode->m_pRight);

	return		nHeightOfLeft > nHeightOfRight
		? (nHeightOfLeft + 1)
		: (nHeightOfRight + 1);
}

void CAVLTree::LeftSingleRotate(AVLNode* pNode)
{
	/* 左单旋

	 F                        F
	     A                        B
	  k1     B                 A     C
		   k2   C            k1  k2
	*/

	AVLNode* pA = pNode; //不平衡的节点
	AVLNode* pF = pNode->m_pParent;
	AVLNode* pK1 = pA->m_pLeft;
	AVLNode* pB = pA->m_pRight;
	AVLNode* pK2 = pB->m_pLeft;

	//修改B
	pB->m_pParent = pF;
	pB->m_pLeft = pA;

	//修改A
	pA->m_pParent = pB;
	pA->m_pRight = pK2;

	//修改F, 父节点
	if (pF == nullptr)
	{
		//A的节点为空，说明A原来是根节点，旋转后，B成为新的根节点
		m_pRoot = pB;
	}
	else
	{
		if (pF->m_pLeft == pA)
		{
			pF->m_pLeft = pB;
		}
		else
		{
			pF->m_pRight = pB;
		}
	}


	//修改k2
	if (pK2 != nullptr)
	{
		pK2->m_pParent = pA;
	}

	//重新调整高度
	pA->m_nHeight = GetHeightByChilds(pA);
	pB->m_nHeight = GetHeightByChilds(pB);
}



void CAVLTree::RightSingleRotate(AVLNode* pNode)
{
	/* 右单旋

	   F                        F
	      A                        B
	   B     K1                C      A
	 C  K2	                        K2   K1 
	*/

	AVLNode* pA = pNode; //不平衡的节点
	AVLNode* pF = pA->m_pParent;
	AVLNode* pK1 = pA->m_pRight;
	AVLNode* pB = pA->m_pLeft;
	AVLNode* pK2 = pB->m_pRight;


	
	//修改A
	pA->m_pParent = pB;
	pA->m_pLeft = pK2;
	//修改B
	pB->m_pParent = pF;
	pB->m_pRight = pA;
	
	
	//修改pk2
	if (pK2 != nullptr)
	{
		pK2->m_pParent = pA;
	}
	


	//修改F, 父节点
	if (pA == m_pRoot)
	{
		
		m_pRoot = pB;
	}
	else
	{
		if (pF->m_pLeft== pA)
		{
			pF->m_pLeft = pB;
		}
		else
		{
			pF->m_pRight =pB;
		}
	}


	//重新调整高度
	pA->m_nHeight = GetHeightByChilds(pA);
	pB->m_nHeight = GetHeightByChilds(pB);

}

void CAVLTree::DeleteLeaf(AVLNode* pNodeToDel)
{
	//整棵树只有一个节点
	if (pNodeToDel == m_pRoot)
	{
		m_pRoot = nullptr;
		delete pNodeToDel;
		return;
	}

	//如果删除的是右孩子, 父结点没有右孩子
	AVLNode* pParent = pNodeToDel->m_pParent;
	if (pParent->m_pRight == pNodeToDel)
	{
		pParent->m_pRight = nullptr;
	}
	//如果删除的是左孩子, 父结点没有左孩子
	if (pParent->m_pLeft == pNodeToDel)
	{
		pParent->m_pLeft = nullptr;
	}

	//删除结点
	delete pNodeToDel;

	//从父结点开始, 调整高度
	AdjustHeight(pParent);
}

void CAVLTree::DeleteSingleChild(AVLNode* pNodeToDel)
{
	//拿到子节点
	AVLNode* pChildNode =
		pNodeToDel->m_pLeft == nullptr
		? pNodeToDel->m_pRight
		: pNodeToDel->m_pLeft;

	//如果是根结点的话
	if (pNodeToDel == m_pRoot)
	{
		m_pRoot = pChildNode;
		pChildNode->m_pParent = nullptr;
		delete pNodeToDel;
		return;
	}

	//如果删除的是右孩子, 子节点作为父结点的右孩子
	AVLNode* pParent = pNodeToDel->m_pParent;
	if (pParent->m_pRight == pNodeToDel)
	{
		pParent->m_pRight = pChildNode;
	}
	//如果删除的是左孩子, 子节点作为父结点的左孩子
	if (pParent->m_pLeft == pNodeToDel)
	{
		pParent->m_pLeft = pChildNode;
	}

	pChildNode->m_pParent = pParent;

	//删除结点
	delete pNodeToDel;

	//从父结点开始, 调整高度
	AdjustHeight(pParent);
}

void CAVLTree::DeleteDoubleChilds(AVLNode* pNodeToDel)
{
	//右边查找最小值的结点
	AVLNode* pRight = pNodeToDel->m_pRight;
	while (pRight->m_pLeft != nullptr)
	{
		pRight = pRight->m_pLeft;
	}

	//交换值
	pNodeToDel->stu = pRight->stu;

	//删除结点
	if (pRight->m_pLeft == nullptr && pRight->m_pRight == nullptr)
	{
		//删除叶子节点
		DeleteLeaf(pRight);
	}
	else
	{
		//删除分支结点
		DeleteSingleChild(pRight);
	}
}



void CAVLTree::CreateStudentData()
{
	char StudentName[10] = { '\0' }; //名字
	unsigned int yearsOfBirth;		//出生年份
	unsigned int dataOfBirth;		//出生日月
	char Gend[4] = { '0' };  //性别
	char RandCHose = 0;
	int StudentId = 1;//学号 初始值为1

	srand((unsigned)time(NULL));

	ofstream CreaFile("MinStudent.bin", ios::out | ios::app );

	//循环生成学生数据
	for (int IdCount = 0; IdCount < 1000000; IdCount++)
	{
		char SzName;
		memset(StudentName, '\0', sizeof(StudentName));
		//随机因子
		for (int RandF = 0; RandF < (rand() % 9 + 1); RandF++)
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

		Student* StudentInfo = new Student;
		StudentInfo->Student_ID = StudentId;
		StudentInfo->SzName = CMyString(StudentName);
		StudentInfo->YearsOfBirth = yearsOfBirth;
		StudentInfo->DataOfBirth = dataOfBirth;
		StudentInfo->Gender = CMyString(Gend);
		CreaFile << StudentInfo->Student_ID << " " << StudentInfo->SzName.GetBuff() << " " << StudentInfo->YearsOfBirth << " " << StudentInfo->DataOfBirth << " " << StudentInfo->Gender.GetBuff() << endl;

		StudentId++;
	}
	cout << "创建完成" << endl;
	system("pause");
	CreaFile.clear();
	CreaFile.close();


}

bool CAVLTree::MidOrder()
{	
	MyStack<AVLNode*> sta;

	AVLNode* Root = m_pRoot;
	AVLNode* GetSame = nullptr;
	if (Root == nullptr)
	{
		return false;
	}
	//中序递归遍历写入文件
	while (Root != nullptr || sta.IsEmpaty() != 1)
	{	//不为空 入栈
		while (Root != nullptr)
		{
			sta.Push(Root);
			Root = Root->m_pLeft;
		}

		if (sta.IsEmpaty() != 1)
		{
			Root = sta.Top();
			cout << "编号:" << Root->stu->Student_ID << endl;
			cout << "姓名:" << Root->stu->SzName.GetBuff() << endl;
			cout << Root->stu->YearsOfBirth << "年" << Root->stu->DataOfBirth << "出生" << endl;
			cout << "性别：" << Root->stu->Gender.GetBuff() << endl;
			GetSame = Root->SameName;
			while (GetSame!=nullptr)
			{	
				cout << "编号:" << GetSame->stu->Student_ID << endl;
				cout << "姓名:" << GetSame->stu->SzName.GetBuff() << endl;
				cout << GetSame->stu->YearsOfBirth << "年" << Root->stu->DataOfBirth << "出生" << endl;
				cout << "性别：" << GetSame->stu->Gender.GetBuff() << endl;
				GetSame = GetSame->SameName;
			}
			
			sta.Pop();
			Root = Root->m_pRight;
		}

	}
	return true;
}

bool CAVLTree::SaveData( const char* FileName)
{
	ofstream outFile(FileName, ios::out | ios::binary);

	MyStack<AVLNode*> sta;

	AVLNode* Root = m_pRoot;
	//中序递归遍历写入文件
	while (Root != nullptr || sta.IsEmpaty() != 1)
	{	//不为空 入栈
		while (Root != nullptr)
		{
			sta.Push(Root);
			Root = Root->m_pLeft;
		}

		if (sta.IsEmpaty() != 1)
		{
			Root = sta.Top();
			outFile <<Root->stu->Student_ID<< " " << Root->stu->SzName.GetBuff() << " " <<Root->stu->YearsOfBirth << " " << Root->stu->DataOfBirth << " " << Root->stu->Gender.GetBuff() << endl;
			sta.Pop();
			Root = Root->m_pRight;
		}

	}
	//关闭文件
	outFile.clear();
	outFile.close();
	return true;
}


//bool CAVLTree::SearStudentName(CAVLTree* T)
//{
//	int flag = 0;
//	char TempName[11] = { '\0' };
//	while (1)
//	{
//		cout << "请输入学生的名字(不超过十个字节)" << endl;
//		scanf_s("%11s", &TempName);
//		fflush(stdin);
//		if (strlen(TempName) > 10 || strlen(TempName) == 0)
//		{
//			cout << "长度有误，请重新输入" << endl;
//			continue;
//		}
//		break;
//	}
//
//
//
//	if (flag == 1)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool CAVLTree::SearStudentId(CAVLTree* T,int id)
{
	int flag = 0;
	MyStack<AVLNode*> sta;
	AVLNode* pNode;
	if (T->m_pRoot == nullptr)
	{
		return false;
	}

	else
	{
		pNode = T->GetRootNode();
	}
	
	if (pNode == nullptr)
	{
		return false;
	}
	//中序递归遍历
	while (pNode != nullptr || sta.IsEmpaty() != 1)
	{	//不为空 入栈
		while (pNode != nullptr)
		{
			sta.Push(pNode);
			pNode = pNode->m_pLeft;
		}

		if (sta.IsEmpaty() != 1)
		{
			pNode = sta.Top();
			if (pNode->stu->Student_ID == id)
			{
				flag = 1;
				cout << "编号:" << pNode->stu->Student_ID << endl;
				cout << "姓名:" << pNode->stu->SzName.GetBuff() << endl;
				cout << pNode->stu->YearsOfBirth << "年" << pNode->stu->DataOfBirth << "出生" << endl;
				cout << "性别：" << pNode->stu->Gender.GetBuff() << endl;
			}
			sta.Pop();
			pNode = pNode->m_pRight;
		}

	}

	if (flag == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
