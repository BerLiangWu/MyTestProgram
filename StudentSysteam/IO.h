#pragma once
#include "AVLT.h"
#include "Student.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <time.h>
#include <fstream>

using namespace std;

class IO
{
public:
	IO() 
	{
		CAVLTree* T1 = new CAVLTree;
		T = T1;
		
		CAVLTree* Main1 = new CAVLTree;
		Main = Main1;
	
	}
	~IO()
	{
		if (T!=nullptr)
		{
			delete T;
		}

		if (Main != nullptr)
		{
			delete Main;
		}
	}

public:
	bool InPutInfo(CAVLTree* T,CAVLTree* M); //����ӿ�
	bool SearchID(CAVLTree* T); //ID���ҽӿ�
	bool SearchName(CAVLTree* T);//�������ҽӿ�
	void Menu();
	bool DeteStudent(CAVLTree* T, CAVLTree* M); //ɾ���ӿ�
	bool UpData(CAVLTree* T, CAVLTree* M);//�޸����ݽӿ�
	bool SaveInFo(CAVLTree* T);//������Ϣ
	bool CreaFile(CAVLTree* T); //�����õĴ������ı�
	bool ShowMidData(CAVLTree* T);//���������������
	bool INputMiData(CAVLTree* T, CAVLTree* M); //�����������
	bool InputStu(CAVLTree* T, CAVLTree* M);//�������������ı�
	void WINR();  //���к���
private:
	CAVLTree* T;
	CAVLTree* Main;
};







bool IO::InPutInfo(CAVLTree* T, CAVLTree* M)
{
	//��ֹ����������
	fflush(stdin);
	
	int TempId = 0;
	char TempName[20] = { '\0' };
	int TempYearsOfBirth = 0;   //���
	int TempDataOfBirth = 0; //����
	char TempGen[20] = { '\0' };//�Ա�


	//���ID
	while (1)
	{
		cout << "��������������Ϊѧ����ѧ�ţ������ظ�" << endl;
		scanf_s("%8d", &TempId);
		fflush(stdin);
		if (TempId == 0 || TempId < 0 || TempId>9000000)
		{
			cout << "���������������" << endl;
			getchar();
			fflush(stdin);
			system("pause");
			system("cls");
			continue;
		}
		else if(M->SearStudentId(M, TempId)==true)
		{
			cout << "������������ظ�������������" << endl;
			fflush(stdin);
			system("pause");
			system("cls");
			continue;
		}
		
		break;
	}

	system("pause");
	//�����������
	while (1)
	{
		cout << "������ѧ�������֣�ʮ���ֽڣ�" << endl;
		scanf("%11s",&TempName);
		fflush(stdin);
		if (strlen(TempName) > 10 || strlen(TempName) == 0)
		{
			cout << "���������������" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//������
	while (1)
	{
		cout << "������ѧ���ĳ�����֣�1800-3000��" << endl;
		scanf("%5d", &TempYearsOfBirth);
		fflush(stdin);
		if (TempYearsOfBirth <= 0 || TempYearsOfBirth < 1800 || TempYearsOfBirth>3000 )
		{
			cout << "���������������" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//�������
	while (1)
	{
		cout << "������ѧ���ĳ������ڣ�0101-1231��" << endl; 
		cout << "���������룬�����պ��޸�" << endl;
		scanf("%5d", &TempDataOfBirth);
		fflush(stdin);
		if (TempDataOfBirth <= 0 || TempDataOfBirth < 0101 || TempDataOfBirth>1231)
		{
			cout << "�������������������������" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//����Ա�
	while (1)
	{
		cout << "������ѧ�����Ա��У�Ů��" << endl;
		cout << "���������룬�����պ��޸�" << endl;
		scanf("%5s", &TempGen);
		fflush(stdin);
		if (strlen(TempGen) > 4 || strlen(TempGen) == 0)
		{
			cout << "���������������" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}


	//ȫ�����ͨ���󴴽�ѧ������
	Student* TStu = new Student;
	TStu->Student_ID = TempId;
	TStu->SzName = CMyString(TempName);
	TStu->YearsOfBirth = TempYearsOfBirth;
	TStu->DataOfBirth = TempDataOfBirth;
	TStu->Gender = CMyString(TempGen);

	//д�뵽��
	bool Result1 = false;
	bool Result2 = false;
	Result1= T->Insert(*TStu);
	Result2 = M->InsertMain(*TStu);
	if ((Result1 == true&& Result2==true))
	{
		cout << "�����ɹ�" << endl;
		system("pause");
		return true;
	}
	else
	{	
		cout << "����ʧ��" << endl;
		system("pause");
		return false;
	}
	
}

inline bool IO::SearchID(CAVLTree* T)
{	//��ֹ����������
	int StuID = 0;
	fflush(stdin);
	while (1)
	{
		cout << "������ѧ����ѧ��" << endl;
		scanf_s("%8d", &StuID);
		fflush(stdin);
		if (StuID == 0 || StuID < 0 || StuID>9000000 )
		{
			cout << "���������������" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}
	bool Resule = false;
	Resule=T->SearStudentId(T, StuID);

	if (Resule == true)
	{
		system("pause");
		return true;
	}
	else
	{	
		cout << "����������ѧ��" << endl;
		system("pause");
		return false;
	}
	
	
}

inline bool IO::SearchName(CAVLTree* T)
{	
	int flag = 0;
	char TempName[11] = { '\0' };
	while (1)
	{
		cout << "������ѧ��������(������ʮ���ֽ�)" << endl;
		scanf("%11s", &TempName);
		fflush(stdin);
		if (strlen(TempName) > 10 || strlen(TempName) == 0)
		{
			cout << "��������" << endl;
			getchar();
			fflush(stdin);
			system("pause");
			continue;
		}
		break;
	}
	CMyString str = CMyString(TempName);
	AVLNode* pNode = T->m_pRoot;
	while (pNode != nullptr)
	{
		if (strcmp(str.GetBuff(), pNode->stu->SzName.GetBuff()) > 0)
		{
			pNode = pNode->m_pRight;
		}
		else if (strcmp(str.GetBuff(), pNode->stu->SzName.GetBuff()) < 0)
		{
			pNode = pNode->m_pLeft;
		}
		else if (strcmp(str.GetBuff(), pNode->stu->SzName.GetBuff()) == 0)
		{
			cout << "��ţ�" << pNode->stu->Student_ID << endl;
			cout << "����:" << pNode->stu->SzName.GetBuff() << endl;
			cout << pNode->stu->YearsOfBirth << "��" << pNode->stu->DataOfBirth << "����" << endl;
			cout << "�Ա�:" << pNode->stu->Gender.GetBuff() << endl;

			if (pNode->SameName != nullptr)
			{
				AVLNode* Next = pNode->SameName;

				while (Next!= nullptr)
				{
					cout << "��ţ�" << Next->stu->Student_ID << endl;
					cout << "����:" << Next->stu->SzName.GetBuff() << endl;
					cout << Next->stu->YearsOfBirth << "��" << Next->stu->DataOfBirth << "����" << endl;
					cout << "�Ա�:" << Next->stu->Gender.GetBuff() << endl;

					Next = Next->SameName;
				}



			}
				
			system("pause");
			return true;
		}
	}

	cout << "������������ѧ��" << endl;
	system("pause");
	return false;
}

inline void IO::Menu()
{
	
		printf(" **************************************** \n");
		printf("	 ѧ   ��   ��   ��   ϵ   ͳ   \n");
		printf(" **************************************** \n");

		printf("1.����ѧ����Ϣ\n ");
		printf("2.��ѧ�Ų�����Ϣ\n ");
		printf("3.������������Ϣ\n ");
		printf("  4.ɾ����Ϣ \n ");
		printf("  5.�޸���Ϣ \n ");
		printf("  6.�������� \n ");
		printf("  7.���ɰ���ѧ���ı�(������)\n");
		printf("  8.�������ѧ�����ݣ�(������)��\n");
		printf("  9.������������\n");
		printf("  10.չʾ��ǰѧ�����ݣ����԰�������ʱ����ʹ�ã�\n");
		printf("0.�˳�ϵͳ\n");
		printf("��ѡ��\n");
	
}

inline void IO::WINR()
{
	int MenuChose = 0;
	Menu();
	scanf_s("%2d", &MenuChose);
	fflush(stdin);
	while (1)
	{
		switch (MenuChose)
		{
		case 1:
			InPutInfo(T,Main);
			SaveInFo(Main);
			break;
		case 2:
			SearchID(Main);
			break;
		case 3:
			SearchName(T);
			break;
		case 4:
			DeteStudent(T,Main);
			break;
		case 5:
			UpData(T,Main);
			break;
		case 6:
			SaveInFo(Main);
			break;
		case 7:
			CreaFile(T);
			break;
		case 8:
			INputMiData(T,Main);
			break;
		case 9:
			InputStu(T,Main);
			break;
		case 10:
			ShowMidData(Main);
			break;
		case 0:
			SaveInFo(Main);
			exit(0);
		default:
			getchar();
			cout << "��������,����������" << endl;
			system("pause");
			fflush(stdin);
			break;
		}
		system("cls");
		fflush(stdin);
		Menu();
		scanf_s("%2d", &MenuChose);
		fflush(stdin);
	}
}


inline bool IO::DeteStudent(CAVLTree* T, CAVLTree* M)
{
	int TempId = 0;
	cout << "������Ҫɾ����ѧ��ѧ��" << endl;
	while (1)
	{
		cout << "��������������Ϊѧ����ѧ��" << endl;
		scanf("%8d", &TempId);
		fflush(stdin);
		if (TempId == 0 || TempId < 0 || TempId>9000000 )
		{
			cout << "���������������" << endl;
			system("pause");
			system("cls");
			fflush(stdin);
			getchar();
			continue;
		}
		break;
	}
	bool Result1 = false;
	bool Result2 = false;
	//����ID�ŷ��ؽ��
	AVLNode* p = M->FindNode(TempId);

	if (p != nullptr)
	{	
		CMyString temp = p->stu->SzName;
		Result2 = T->Delete_Name(temp, TempId);
		Result1 = M->Delete_ID(TempId);
	}
	else
	{
		cout << "����ֵ�ý��" << endl;
		system("pause");
		return false;
	}

	if ((Result1 == true|| Result2 == true))
	{
		cout << "ɾ���ɹ�" << endl;
		system("pause");
		return true;

	}
	else
	{	
		cout << "ɾ��ʧ��" << endl;
		system("pause");
		return false;
	}
	
}

inline bool IO::UpData(CAVLTree* T, CAVLTree* M)
{
	
	bool Result1 = false;
	bool Result2 = false;

	Result1= DeteStudent(T,Main);
	if (Result1 != false)
	{
		cout << "�������޸ĵ�����" << endl;
		Result2 = InPutInfo(T, Main);
	}
	else
	{
		cout << "��ʹ�ù���1����ѧ����Ϣ" << endl;
		system("pause");
		return false;
	}
	if (Result1 == true && Result2 == true)
	{
		cout << "�޸ĳɹ�" << endl;
		system("pause");
		return true;

	}
	else
	{
		cout << "�޸�ʧ��" << endl;
		system("pause");
		return false;
	}


	
}

inline bool IO::SaveInFo(CAVLTree* T)
 {
	 const char* FileName = "StudentDate.bin";
	 bool Result = false;
	 Result=T->SaveData(FileName);

	 if (Result == true)
	 {
		 cout << "���ݱ���ɹ�" << endl;
		 system("pause");
		 return true;
	 }
	 else
	 {
		 cout << "���ݱ���ʧ��" << endl;
		 system("pause");
		 return false;
	 }
	
}

 inline bool IO::CreaFile(CAVLTree* T)
 {	
	 T->CreateStudentData();
	 return true;
 }

 inline bool IO::ShowMidData(CAVLTree* T)
 {
	 bool Result = false;
	 Result=Main->MidOrder();
	 if (Result == true)
	 {	
		 system("pause");
		 return true;
	 }
	 else
	 {	
		 cout << "��ǰ��Ϊ����" << endl;
		 system("pause");
		 return false;
	 }
	 
 }

 

 inline bool IO::InputStu(CAVLTree* T, CAVLTree* M)
 {	
	 ifstream inFile("StudentDate.bin",ios::in );
	 //�ļ������������
	 char FileLine[50] = { 0 };
	 char FName[11] = { '\0' };
	 char Id[8] = { '\0' };
	 char Gen[5] = { '\0' };
	 char Years[5] = { '\0' };
	 char Data[5] = { '\0' };

	 while (inFile.getline(FileLine,sizeof(FileLine)))
	 {
		 std::stringstream Copy(FileLine);
		 Copy >> Id;
		 Copy >> FName;
		 Copy >> Years;
		 Copy >> Data;
		 Copy >> Gen;

		 Student* TempStud = new Student;
		 TempStud->Student_ID = atoi(Id);
		 TempStud->SzName = CMyString(FName);
		 TempStud->YearsOfBirth = atoi(Years);
		 TempStud->DataOfBirth = atoi(Data);
		 TempStud->Gender = CMyString(Gen);

		 //д����
		 T->Insert(*TempStud);
		 Main->InsertMain(*TempStud);
	 }
	 inFile.clear();
	 inFile.close();
	 cout << "�������" << endl;
	 system("pause");
	 return true;
 }

 

 inline bool IO::INputMiData(CAVLTree* T, CAVLTree* M)
 {
	 ifstream CreaFile("MinStudent.bin", ios::in | ios::app);
	 //�ļ������������
	 char FileLine[50] = { 0 };
	 char FName[11] = { '\0' };
	 char Id[8] = { '\0' };
	 char Gen[5] = { '\0' };
	 char Years[5] = { '\0' };
	 char Data[5] = { '\0' };

	 while (CreaFile.getline(FileLine, sizeof(FileLine)))
	 {
		 std::stringstream Copy(FileLine);
		 Copy >> Id;
		 Copy >> FName;
		 Copy >> Years;
		 Copy >> Data;
		 Copy >> Gen;

		 Student* TempStud = new Student;
		 TempStud->Student_ID = atoi(Id);
		 TempStud->SzName = CMyString(FName);
		 TempStud->YearsOfBirth = atoi(Years);
		 TempStud->DataOfBirth = atoi(Data);
		 TempStud->Gender = CMyString(Gen);

		 //д����
		 T->Insert(*TempStud);
		 Main->InsertMain(*TempStud);
	 }
	 CreaFile.clear();
	 CreaFile.close();
	 cout << "����ɹ�" << endl;
	 system("pause");
	 return true;
 }