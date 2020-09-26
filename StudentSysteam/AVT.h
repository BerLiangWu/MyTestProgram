#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "CMyString.h"
#include "MyStack.h"

# define Left_H 1 
# define EH 0   //ƽ��
# define Right_H -1
# define TRUE 1
# define FALSE 0
# define MAX  1000
bool Taller = 0;   //����ʱ��ӳ���Ƿ񳤸�0������  1����
bool Shorter;    //ɾ��ʱʱ��ӳ���Ƿ񳤸�0������  1����


using namespace std;
typedef struct AVLNode
{	
	Student stu;
	int bf=0;//balance factorƽ���ж�����
	struct AVLNode* m_pLeft = nullptr;   //ָ������
	struct AVLNode* m_pRight = nullptr;  //ָ���ҽ��

}AVLNode,* AVLTree;

void Delete(AVLTree& T);
AVLTree LeftBalance(AVLTree T);
AVLTree RightBalance(AVLTree T);
void Delete_LeftBalance(AVLTree& T);
void Delete_RightBalance(AVLTree& T);
//���� pΪ�������Ķ�������������
//�����������ĸ��ڵ�
AVLTree R_rotate(AVLTree p)
{
	AVLNode* Lc; //���ӽ��
	
	Lc = p->m_pLeft; 
	p->m_pLeft = Lc->m_pRight;

	Lc->m_pRight = p;
	p = Lc;

	return p;
}

//���� pΪ�������Ķ�������������
//�����������ĸ��ڵ�
AVLTree L_Rotate(AVLTree p)
{
	AVLNode* Rc;//�Һ��ӽ��
	Rc = p->m_pRight;
	p->m_pRight = Rc->m_pLeft;
	Rc->m_pLeft = p;
	p = Rc;
	return p;
}
//����ƽ���ж�
AVLTree LeftBalance(AVLTree T)
{
	//����T��ָ����Ϊ���Ķ�������������
	
	
	AVLNode* Lc;//�������ӽ��
	AVLNode* Rc;//�����Һ��ӽ��
	Lc = T->m_pLeft;
	//���ƽ���
	//����ƽ��ȴ���
	switch (Lc->bf)
	{
	
	//��Ϊ1���ʱ
		//�½�������T�����ӵ���Ҷ���ϣ�������
	case Left_H:
		T->bf = Lc->bf = EH;
		T = R_rotate(T);
		break;
		//��Ϊ-1�Ҹ�ʱ
		//�½���������������ϣ���˫��
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
		//ָ��Tָ���µĸ����
		Rc->bf = EH;
		T->m_pLeft = L_Rotate(T->m_pLeft);
		T = R_rotate(T);
	}

	return T;
}

// ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
AVLTree RightBalance(AVLTree T)
{       
	AVLNode* Lc;//�������ӽ��
	AVLNode* Rc;//�����Һ��ӽ��
	Rc = T->m_pRight;
	switch (Rc->bf)
	{               // ���*T����������ƽ��ȣ�������Ӧƽ�⴦��
	case Right_H:        // �½�������*T���Һ��ӵ��������ϣ�Ҫ������������
		T->bf = Rc->bf = EH;
		T = L_Rotate(T);
		break;
	case Left_H:        // �½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������
		Lc = Rc->m_pLeft;
		switch (Lc->bf)
		{            // �޸�*T�����Һ��ӵ�ƽ������
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
//����ƽ�������
//����ƽ��Ķ�����T�в����ں�S����ͬ���ݵĽ��
//�����һ���½�� ���ҷ���1���򷵻�0
//������ж��Ƿ�ƽ��
AVLTree InsertAVL(AVLTree T, AVLTree S)
{
	AVLTree p;
	//������ǿյ�
	if (!T)
	{
		//�����½�㣬��������ߣ��ò�����־TallerΪ��
		T = S;
		T->m_pLeft = T->m_pRight = nullptr;
		T->bf = EH;
		Taller = TRUE;
	}
	else
	{
		if (S->stu.Student_ID == T->stu.Student_ID)
		{
			//������д�����ͬ�����򲻲���
			cout<<"������ͬѧ��"<<endl;
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
				//���߶�
				if (Taller)
				{
					switch (T->bf)
					{
						//ԭ����Ҹߣ�����ƽ�⴦��
					case Left_H:
						T = LeftBalance(T);
						Taller = FALSE;
						break;
						//ԭ�����ҵȸߣ������������
					case EH:
						T->bf = Left_H;
						Taller = TRUE;
						break;
						//ԭ���Ҹߣ����ڵȸ�
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
			//������T������������
			p = InsertAVL(T->m_pRight, S);
			if (p)
			{	
				T->m_pRight = p;
				if (Taller)
				{
					switch (T->bf)
					{
						//ԭ������Ҹߣ����ڵȸ�
					case Left_H:
						T->bf = EH;
						Taller = FALSE;
						break;
						//ԭ�����ҵȸߣ������Ҹ�
					case EH:
						T->bf = Right_H;
						Taller = FALSE;
						break;
						//ԭ���ұ���ߣ�������ƽ��
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

//�ݹ��������
void Midorder(AVLTree T)
{
	if (T)
	{
		Midorder(T->m_pLeft);
		T->stu.StuIF();
		Midorder(T->m_pRight);
	}
}

//��֤ɾ�����֮������Ȼƽ��
int DeleteAVL(AVLTree& T, int id)
{
	if (T==nullptr)
	{
		cout << "��Ҫɾ���ı�Ų�����" << endl;
		system("pause");
		return 0;
	}
	else
	{
		if (id == T->stu.Student_ID)
		{
			Delete(T);
			cout << "��ɾ��Ŀ��ѧ��" << endl;
			system("pause");
		}
		//����Ҳ���
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
//ɾ����㣬�Ӷ�������ɾ����㣬�������½���������
void Delete(AVLTree& T)
{
	AVLTree p;  //��ɾ�����
	AVLTree q;
	int number;  //�½����
	p = T;
	//������Ϊ�����½�������
	if (!T->m_pRight)
	{
		T = T->m_pLeft;
		free(p);
		Shorter = true;
	}
	//������Ϊ�����½�������
	else if (!T->m_pLeft)
	{
		T = T->m_pRight;
		free(p);
		Shorter = true;
	}
	//���������������Ϊ����
	else
	{
		q = T->m_pLeft;
		while (q->m_pRight)
		{
			//������Ȼ�󻻵��ұ�
			p = q;
			q = q->m_pRight;
		}
		number = q->stu.Student_ID;
		T->stu.Student_ID = number;
	}
}
//ɾ��֮���ұ�ʧ����Ҵ���
void Delete_RightBalance(AVLTree& T)
{
	//����������ʱ��
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
		//���t��ƽ�����
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
//ɾ��֮�����ʧ�������
void Delete_LeftBalance(AVLTree& T)
{
	//����������ʱ��
	AVLTree p1;
	AVLTree p2;
	p1 = T->m_pLeft;
	switch (p1->bf)
	{
		//�����ʧ��
	case Left_H:
		T->m_pLeft = p1->m_pRight;
		p1->m_pRight = T;
		p1->bf = T->bf = EH;
		T = p1;
		Shorter = true;
		break;
		//���ƽ��
	case EH:
		T->m_pLeft = p1->m_pRight;
		p1->m_pRight = T;
		p1->bf = Right_H;
		T->bf = Left_H;
		T = p1;
		Shorter = false;
		break;
		////�����ʧ��
	case Right_H:
		p2 = p1->m_pRight;
		p1->m_pRight = p2->m_pLeft;
		p2->m_pLeft = p1;
		T->m_pLeft = p2->m_pRight;
		p2->m_pRight = T;
		//�ж�p2
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
	//��ʱ���
	AVLTree p;
	if (T==nullptr)
	{
		cout << "�����������ѧ��" << endl;
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
		cout << "�����������ѧ��" << endl;
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
	//��ʱ���
	AVLTree p;
	if (T == nullptr)
	{
		cout << "�����������ѧ��" << endl;
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




//��������
void Save(AVLTree T, const char*a)
{
	ofstream outFile(a, ios::out|ios::binary);
	MyStack<AVLTree> sta;
	//����ݹ����д���ļ�
	while (T!=nullptr||sta.IsEmpaty()!=1)
	{	//��Ϊ�� ��ջ
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
	//�ر��ļ�
	outFile.clear();
	outFile.close();
}

//�������ѧ���ļ�
void CreateStudentData()
{
	 char StudentName[10] = { '\0' }; //����
	 unsigned int yearsOfBirth;		//�������
	 unsigned int dataOfBirth;		//��������
	 char Gend[4] = { '0' };  //�Ա�
	 char RandCHose = 0;
	 int StudentId = 1;//ѧ�� ��ʼֵΪ1

	 srand((unsigned)time(NULL));

	 ofstream CreaFile("MinStudent.bin", ios::out |ios::app| ios::binary);

	 //ѭ������ѧ������
	 for (int IdCount = 0; IdCount<100000; IdCount++)
	 {
		 char SzName;
		 memset(StudentName, '\0', sizeof(StudentName));
		 //�������
		 for (int  RandF = 0; RandF <(rand()%9+1); RandF++)
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

		 AVLTree SD = new AVLNode;
		 SD->stu.Student_ID = StudentId;
		 SD->stu.SzName = CMyString(StudentName);
		 SD->stu.YearsOfBirth = yearsOfBirth;
		 SD->stu.DataOfBirth = dataOfBirth;
		 SD->stu.Gender = CMyString(Gend);
		 CreaFile << SD->stu.Student_ID << " " << SD->stu.SzName.GetBuff() << " " << SD->stu.YearsOfBirth << " " << SD->stu.DataOfBirth << " " << SD->stu.Gender.GetBuff() << endl;
		 
		 StudentId++;
	 }
	 cout << "�������" << endl;
	 system("pause");
	 CreaFile.clear();
	 CreaFile.close();
	 

}
