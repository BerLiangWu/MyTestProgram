#define _CRT_SECURE_NO_WARNINGS


#include "AVLT.h"
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;



bool CAVLTree::Insert(Student& stuobj)
{
	//�½����
	AVLNode* pNewNode = new AVLNode(stuobj);

	//����ǿ���,���½��ֱ��Ϊ�����
	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
		return true;
	}

	//������ǿ���, ����,ֱ������Ҷ�ӽڵ�, ���½����뵽����
	AVLNode* pNode = m_pRoot;
	while (true)
	{
		//��������ֵС�ڱȽϽ��,��ȡ�ȽϽ�������
		if (strcmp(stuobj.SzName.GetBuff(),pNode->stu->SzName.GetBuff())<0)
		{
			//����ȽϽ��û������,���½����Ϊ���ӽ�����
			if (pNode->m_pLeft == nullptr)
			{
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pLeft;
		}
		//��������ֵ���ڱȽϽ��,��ȡ�ȽϽ����Һ���
		else if (strcmp(stuobj.SzName.GetBuff(), pNode->stu->SzName.GetBuff()) >0)
		{
			//����ȽϽ��û���Һ���,���½����Ϊ�Һ��ӽ�����
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
				//�������һ�����
				pNewNode->SameName = nullptr;
				pNode->SameName = pNewNode;
			}
			
			break;
		}
	}

	//�����߶�
	AdjustHeight(pNewNode);
	return true;
}

bool CAVLTree::InsertMain(Student& stuobj)
{	
	AVLNode* pNewNode = new AVLNode(stuobj);

	//����ǿ���,���½��ֱ��Ϊ�����
	if (m_pRoot == nullptr)
	{
		m_pRoot = pNewNode;
		return true;
	}

	//������ǿ���, ����,ֱ������Ҷ�ӽڵ�, ���½����뵽����
	AVLNode* pNode = m_pRoot;

	while (true)
	{
		//��������ֵС�ڱȽϽ��,��ȡ�ȽϽ�������
		if (stuobj.Student_ID<pNode->stu->Student_ID)
		{
			//����ȽϽ��û������,���½����Ϊ���ӽ�����
			if (pNode->m_pLeft == nullptr)
			{
				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				break;
			}

			pNode = pNode->m_pLeft;
		}
		//��������ֵ���ڱȽϽ��,��ȡ�ȽϽ����Һ���
		else if (stuobj.Student_ID >pNode->stu->Student_ID)
		{
			//����ȽϽ��û���Һ���,���½����Ϊ�Һ��ӽ�����
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
			cout << "��ֵ�Ѿ�����" << endl;
			system("pause");
			return false;
		}
	}

	//�����߶�
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
		cout << "�����ڸ���ѧ��" << endl;
		system("pause");
		return false;
	}
	//������ͬ��ʱ
	//���ù�ϣ��ķ�ʽ ��ͬ�������������ѧ�����ԣ���ǰһ�������ݽ��� ɾ��ǰһ��
	//��Ϊ�����ƻ�������̬�ṹ
	AVLNode* SameStu = pNode->SameName;

	//���ʱ����ͬ��
	if (SameStu != nullptr)
	{
		//�鿴�ĸ�����

		//����ý�����Ҫɾ����
		//��Ϊͷ���
		if (pNode->stu->Student_ID == StuId)
		{
			//�ͺ�һ����������

			AVLNode* Next = SameStu->SameName; //��һ������һ��

			//�����һ��Ҳ��Ϊ��
			if (Next!=nullptr)
			{
				pNode->stu = SameStu->stu;   //����һ�ν���

				//��ʱSameStu�Ѿ����洢
				while (Next != nullptr)
				{	
					//�Ѻ�������������
					SameStu->stu = Next->SameName->stu;

					//�����������ƶ�
					Next = Next->SameName;
					SameStu = SameStu->SameName;
				}
				//������û�к������һ�ν���
				SameStu->stu = Next->stu;

				delete Next;
				SameStu->SameName = nullptr;//����ſ�
				return true;
			}
			//�����һ���ǿյ�
			else
			{	
				//������
				pNode->stu = SameStu->stu;

				//ɾ������
				delete SameStu;
				pNode->SameName = nullptr;//����ſ�
				return true;
			}
			
			
		}
		//ͷ��㲢����Ҫɾ��������
		else
		{
			//�ƶ�nextָ��
			while (1)
			{	
				if (SameStu->stu->Student_ID == StuId)
				{
					break;
				}
				else if (SameStu->SameName == nullptr)
				{	
					cout << "�Ҳ�������ѧ��" << endl;
					system("pause");
					return false;
				}
				pNode = SameStu;
				SameStu = SameStu->SameName;

			}

			//�ҵ��� samestu����Ҫɾ����
			AVLNode* Next = SameStu->SameName; //��һ������һ��
			//�����һ��Ҳ��Ϊ��
			if (Next != nullptr)
			{
				SameStu->stu = Next->stu;   //����һ�ν���
				//��ʱNext�Ѿ����洢
				
				//1 ,2(SAmStu),3(Next)
				//      pre
				//     SameName        Next
				//1,2(Next->stu),3(SameName->same)

				AVLNode* pre = SameStu;  //�ƶ�ǰ��¼һ��λ��
				
				SameStu->SameName = Next;
				Next = Next->SameName;  //4
				SameStu = SameStu->SameName;//3
				pre->SameName = SameStu;  //2
				//3���治Ϊ��
				if (Next != nullptr)
				{
					while (Next != nullptr)
					{
						//�Ѻ�������������
						SameStu->stu = Next->stu;

						//�����������ƶ�
						Next = Next->SameName;
						SameStu = SameStu->SameName;
						pre = pre->SameName;
					}

					delete Next;
					pre->SameName = SameStu;
					SameStu->SameName = nullptr;//����ſ�
					return true;
				}
				else
				{
					 ///����ǿյ� ����ʱ3����SameStu
					pre->SameName = nullptr;
					delete SameStu;
					return true;

				}
				
			}
			//�����һ���ǿյ�  SameStu����Ҫɾ����

			else
			{	
				pNode->SameName =nullptr;  //����ſ�
				
				delete SameStu;
				return true;

			}
		}
	}



	

	//��������ͬ��ʱ
	//�����Ҷ�ӽڵ�
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DeleteLeaf(pNode);
	}
	//ֻ��һ������
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DeleteSingleChild(pNode);
	}
	//����������
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

	
	//�����Ҷ�ӽڵ�
	if (pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
	{
		DeleteLeaf(pNode);
	}
	//ֻ��һ������
	else if (pNode->m_pLeft == nullptr || pNode->m_pRight == nullptr)
	{
		DeleteSingleChild(pNode);
	}
	//����������
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
	//���Ÿ��ڵ��·�ߣ��������и��ڵ�ĸ߶�
	AVLNode* pNodeToAdjust = pNode;
	while (pNodeToAdjust != nullptr)
	{
		pNodeToAdjust->m_nHeight = GetHeightByChilds(pNodeToAdjust);

		//�����߶ȵĹ����У��жϽڵ��Ƿ�ƽ��
		int nLeftHeight = GetHeight(pNodeToAdjust->m_pLeft);
		int nRightHeight = GetHeight(pNodeToAdjust->m_pRight);

		//�Һ��ӵĸ߶������ӵĸ߶Ȳ����1,����
		if (nRightHeight - nLeftHeight > 1)
		{
			AVLNode* pA = pNodeToAdjust;
			AVLNode* pB = pA->m_pRight;

			int nHeightOfBLeft = GetHeight(pB->m_pLeft);
			int nHeightOfBRight = GetHeight(pB->m_pRight);

			/*����
			  A                 B
				B        -->  A   C
				  C
			*/
			if (nHeightOfBRight > nHeightOfBLeft)
			{
				LeftSingleRotate(pNodeToAdjust);
			}
			/*������, ������
				A             A                    C
					B  -->       C      -->      A   B
				 C                  B

			 ˫��: ��������B����, ������A����
		   */
			else
			{
				RightSingleRotate(pB);
				LeftSingleRotate(pA);
			}
		}
		//���ӵĸ߶����Һ��ӵĸ߶Ȳ����1,����
		else if (nLeftHeight - nRightHeight > 1)
		{
			AVLNode* pA = pNodeToAdjust;
			AVLNode* pB = pA->m_pLeft;

			int nHeightOfBLeft = GetHeight(pB->m_pLeft);
			int nHeightOfRight = GetHeight(pB->m_pRight);

			/* �ҵ���
				   A
				 B
			  C
			*/
			if (nHeightOfBLeft > nHeightOfRight)
			{
				RightSingleRotate(pA);
			}
			/* ������ת
				 A               A              C
			  B         -->    C       -->    B   A
				 C           B

			 ��ת����: ��ʾ����B����,��������A����
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
	//���ڵ�ĸ߶ȣ�Ϊ���Ӻ��Һ��Ӹ߶Ƚϴ��ֵ + 1
	int nHeightOfLeft = GetHeight(pNode->m_pLeft);
	int nHeightOfRight = GetHeight(pNode->m_pRight);

	return		nHeightOfLeft > nHeightOfRight
		? (nHeightOfLeft + 1)
		: (nHeightOfRight + 1);
}

void CAVLTree::LeftSingleRotate(AVLNode* pNode)
{
	/* ����

	 F                        F
	     A                        B
	  k1     B                 A     C
		   k2   C            k1  k2
	*/

	AVLNode* pA = pNode; //��ƽ��Ľڵ�
	AVLNode* pF = pNode->m_pParent;
	AVLNode* pK1 = pA->m_pLeft;
	AVLNode* pB = pA->m_pRight;
	AVLNode* pK2 = pB->m_pLeft;

	//�޸�B
	pB->m_pParent = pF;
	pB->m_pLeft = pA;

	//�޸�A
	pA->m_pParent = pB;
	pA->m_pRight = pK2;

	//�޸�F, ���ڵ�
	if (pF == nullptr)
	{
		//A�Ľڵ�Ϊ�գ�˵��Aԭ���Ǹ��ڵ㣬��ת��B��Ϊ�µĸ��ڵ�
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


	//�޸�k2
	if (pK2 != nullptr)
	{
		pK2->m_pParent = pA;
	}

	//���µ����߶�
	pA->m_nHeight = GetHeightByChilds(pA);
	pB->m_nHeight = GetHeightByChilds(pB);
}



void CAVLTree::RightSingleRotate(AVLNode* pNode)
{
	/* �ҵ���

	   F                        F
	      A                        B
	   B     K1                C      A
	 C  K2	                        K2   K1 
	*/

	AVLNode* pA = pNode; //��ƽ��Ľڵ�
	AVLNode* pF = pA->m_pParent;
	AVLNode* pK1 = pA->m_pRight;
	AVLNode* pB = pA->m_pLeft;
	AVLNode* pK2 = pB->m_pRight;


	
	//�޸�A
	pA->m_pParent = pB;
	pA->m_pLeft = pK2;
	//�޸�B
	pB->m_pParent = pF;
	pB->m_pRight = pA;
	
	
	//�޸�pk2
	if (pK2 != nullptr)
	{
		pK2->m_pParent = pA;
	}
	


	//�޸�F, ���ڵ�
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


	//���µ����߶�
	pA->m_nHeight = GetHeightByChilds(pA);
	pB->m_nHeight = GetHeightByChilds(pB);

}

void CAVLTree::DeleteLeaf(AVLNode* pNodeToDel)
{
	//������ֻ��һ���ڵ�
	if (pNodeToDel == m_pRoot)
	{
		m_pRoot = nullptr;
		delete pNodeToDel;
		return;
	}

	//���ɾ�������Һ���, �����û���Һ���
	AVLNode* pParent = pNodeToDel->m_pParent;
	if (pParent->m_pRight == pNodeToDel)
	{
		pParent->m_pRight = nullptr;
	}
	//���ɾ����������, �����û������
	if (pParent->m_pLeft == pNodeToDel)
	{
		pParent->m_pLeft = nullptr;
	}

	//ɾ�����
	delete pNodeToDel;

	//�Ӹ���㿪ʼ, �����߶�
	AdjustHeight(pParent);
}

void CAVLTree::DeleteSingleChild(AVLNode* pNodeToDel)
{
	//�õ��ӽڵ�
	AVLNode* pChildNode =
		pNodeToDel->m_pLeft == nullptr
		? pNodeToDel->m_pRight
		: pNodeToDel->m_pLeft;

	//����Ǹ����Ļ�
	if (pNodeToDel == m_pRoot)
	{
		m_pRoot = pChildNode;
		pChildNode->m_pParent = nullptr;
		delete pNodeToDel;
		return;
	}

	//���ɾ�������Һ���, �ӽڵ���Ϊ�������Һ���
	AVLNode* pParent = pNodeToDel->m_pParent;
	if (pParent->m_pRight == pNodeToDel)
	{
		pParent->m_pRight = pChildNode;
	}
	//���ɾ����������, �ӽڵ���Ϊ����������
	if (pParent->m_pLeft == pNodeToDel)
	{
		pParent->m_pLeft = pChildNode;
	}

	pChildNode->m_pParent = pParent;

	//ɾ�����
	delete pNodeToDel;

	//�Ӹ���㿪ʼ, �����߶�
	AdjustHeight(pParent);
}

void CAVLTree::DeleteDoubleChilds(AVLNode* pNodeToDel)
{
	//�ұ߲�����Сֵ�Ľ��
	AVLNode* pRight = pNodeToDel->m_pRight;
	while (pRight->m_pLeft != nullptr)
	{
		pRight = pRight->m_pLeft;
	}

	//����ֵ
	pNodeToDel->stu = pRight->stu;

	//ɾ�����
	if (pRight->m_pLeft == nullptr && pRight->m_pRight == nullptr)
	{
		//ɾ��Ҷ�ӽڵ�
		DeleteLeaf(pRight);
	}
	else
	{
		//ɾ����֧���
		DeleteSingleChild(pRight);
	}
}



void CAVLTree::CreateStudentData()
{
	char StudentName[10] = { '\0' }; //����
	unsigned int yearsOfBirth;		//�������
	unsigned int dataOfBirth;		//��������
	char Gend[4] = { '0' };  //�Ա�
	char RandCHose = 0;
	int StudentId = 1;//ѧ�� ��ʼֵΪ1

	srand((unsigned)time(NULL));

	ofstream CreaFile("MinStudent.bin", ios::out | ios::app );

	//ѭ������ѧ������
	for (int IdCount = 0; IdCount < 1000000; IdCount++)
	{
		char SzName;
		memset(StudentName, '\0', sizeof(StudentName));
		//�������
		for (int RandF = 0; RandF < (rand() % 9 + 1); RandF++)
		{
			SzName = (rand() % 2) ? ('a' + rand() % 26) : ('A' + rand() % 26);
			StudentName[RandF] = SzName;
		}

		yearsOfBirth = rand() % (1201) + 1800; //1800-3000 n-m+1 +m
		dataOfBirth = rand() % (1131) + 0101;//0101-1231


		//�����Ա�
		RandCHose = rand() % (2) + 1;
		if (RandCHose == 1)
		{
			strcpy(Gend, "��");
		}
		else
		{
			strcpy(Gend, "Ů");
		}

		//�½�һ�������

		Student* StudentInfo = new Student;
		StudentInfo->Student_ID = StudentId;
		StudentInfo->SzName = CMyString(StudentName);
		StudentInfo->YearsOfBirth = yearsOfBirth;
		StudentInfo->DataOfBirth = dataOfBirth;
		StudentInfo->Gender = CMyString(Gend);
		CreaFile << StudentInfo->Student_ID << " " << StudentInfo->SzName.GetBuff() << " " << StudentInfo->YearsOfBirth << " " << StudentInfo->DataOfBirth << " " << StudentInfo->Gender.GetBuff() << endl;

		StudentId++;
	}
	cout << "�������" << endl;
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
	//����ݹ����д���ļ�
	while (Root != nullptr || sta.IsEmpaty() != 1)
	{	//��Ϊ�� ��ջ
		while (Root != nullptr)
		{
			sta.Push(Root);
			Root = Root->m_pLeft;
		}

		if (sta.IsEmpaty() != 1)
		{
			Root = sta.Top();
			cout << "���:" << Root->stu->Student_ID << endl;
			cout << "����:" << Root->stu->SzName.GetBuff() << endl;
			cout << Root->stu->YearsOfBirth << "��" << Root->stu->DataOfBirth << "����" << endl;
			cout << "�Ա�" << Root->stu->Gender.GetBuff() << endl;
			GetSame = Root->SameName;
			while (GetSame!=nullptr)
			{	
				cout << "���:" << GetSame->stu->Student_ID << endl;
				cout << "����:" << GetSame->stu->SzName.GetBuff() << endl;
				cout << GetSame->stu->YearsOfBirth << "��" << Root->stu->DataOfBirth << "����" << endl;
				cout << "�Ա�" << GetSame->stu->Gender.GetBuff() << endl;
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
	//����ݹ����д���ļ�
	while (Root != nullptr || sta.IsEmpaty() != 1)
	{	//��Ϊ�� ��ջ
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
	//�ر��ļ�
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
//		cout << "������ѧ��������(������ʮ���ֽ�)" << endl;
//		scanf_s("%11s", &TempName);
//		fflush(stdin);
//		if (strlen(TempName) > 10 || strlen(TempName) == 0)
//		{
//			cout << "������������������" << endl;
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
	//����ݹ����
	while (pNode != nullptr || sta.IsEmpaty() != 1)
	{	//��Ϊ�� ��ջ
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
				cout << "���:" << pNode->stu->Student_ID << endl;
				cout << "����:" << pNode->stu->SzName.GetBuff() << endl;
				cout << pNode->stu->YearsOfBirth << "��" << pNode->stu->DataOfBirth << "����" << endl;
				cout << "�Ա�" << pNode->stu->Gender.GetBuff() << endl;
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
