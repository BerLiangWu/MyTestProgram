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
	bool InPutInfo(CAVLTree* T,CAVLTree* M); //输入接口
	bool SearchID(CAVLTree* T); //ID查找接口
	bool SearchName(CAVLTree* T);//姓名查找接口
	void Menu();
	bool DeteStudent(CAVLTree* T, CAVLTree* M); //删除接口
	bool UpData(CAVLTree* T, CAVLTree* M);//修改数据接口
	bool SaveInFo(CAVLTree* T);//保存信息
	bool CreaFile(CAVLTree* T); //测试用的大数据文本
	bool ShowMidData(CAVLTree* T);//中序遍历整个数据
	bool INputMiData(CAVLTree* T, CAVLTree* M); //导入百万数据
	bool InputStu(CAVLTree* T, CAVLTree* M);//导入正常数据文本
	void WINR();  //运行函数
private:
	CAVLTree* T;
	CAVLTree* Main;
};







bool IO::InPutInfo(CAVLTree* T, CAVLTree* M)
{
	//防止缓冲区输入
	fflush(stdin);
	
	int TempId = 0;
	char TempName[20] = { '\0' };
	int TempYearsOfBirth = 0;   //年份
	int TempDataOfBirth = 0; //日期
	char TempGen[20] = { '\0' };//性别


	//检查ID
	while (1)
	{
		cout << "请输入正整数作为学生的学号，不可重复" << endl;
		scanf_s("%8d", &TempId);
		fflush(stdin);
		if (TempId == 0 || TempId < 0 || TempId>9000000)
		{
			cout << "你输入的数据有误" << endl;
			getchar();
			fflush(stdin);
			system("pause");
			system("cls");
			continue;
		}
		else if(M->SearStudentId(M, TempId)==true)
		{
			cout << "你输入的数据重复，请重新输入" << endl;
			fflush(stdin);
			system("pause");
			system("cls");
			continue;
		}
		
		break;
	}

	system("pause");
	//检查姓名输入
	while (1)
	{
		cout << "请输入学生的名字（十个字节）" << endl;
		scanf("%11s",&TempName);
		fflush(stdin);
		if (strlen(TempName) > 10 || strlen(TempName) == 0)
		{
			cout << "你输入的数据有误" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//检查年份
	while (1)
	{
		cout << "请输入学生的出生年分（1800-3000）" << endl;
		scanf("%5d", &TempYearsOfBirth);
		fflush(stdin);
		if (TempYearsOfBirth <= 0 || TempYearsOfBirth < 1800 || TempYearsOfBirth>3000 )
		{
			cout << "你输入的数据有误" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//检查日期
	while (1)
	{
		cout << "请输入学生的出生日期（0101-1231）" << endl; 
		cout << "请正常输入，避免日后修改" << endl;
		scanf("%5d", &TempDataOfBirth);
		fflush(stdin);
		if (TempDataOfBirth <= 0 || TempDataOfBirth < 0101 || TempDataOfBirth>1231)
		{
			cout << "你输入的数据有误，请重新输入" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}

	system("pause");
	//检查性别
	while (1)
	{
		cout << "请输入学生的性别（男，女）" << endl;
		cout << "请正常输入，避免日后修改" << endl;
		scanf("%5s", &TempGen);
		fflush(stdin);
		if (strlen(TempGen) > 4 || strlen(TempGen) == 0)
		{
			cout << "你输入的数据有误" << endl;
			system("pause");
			system("cls");
			getchar();
			fflush(stdin);
			continue;
		}
		break;
	}


	//全部检查通过后创建学生对象
	Student* TStu = new Student;
	TStu->Student_ID = TempId;
	TStu->SzName = CMyString(TempName);
	TStu->YearsOfBirth = TempYearsOfBirth;
	TStu->DataOfBirth = TempDataOfBirth;
	TStu->Gender = CMyString(TempGen);

	//写入到树
	bool Result1 = false;
	bool Result2 = false;
	Result1= T->Insert(*TStu);
	Result2 = M->InsertMain(*TStu);
	if ((Result1 == true&& Result2==true))
	{
		cout << "创建成功" << endl;
		system("pause");
		return true;
	}
	else
	{	
		cout << "创建失败" << endl;
		system("pause");
		return false;
	}
	
}

inline bool IO::SearchID(CAVLTree* T)
{	//防止缓冲区输入
	int StuID = 0;
	fflush(stdin);
	while (1)
	{
		cout << "请输入学生的学号" << endl;
		scanf_s("%8d", &StuID);
		fflush(stdin);
		if (StuID == 0 || StuID < 0 || StuID>9000000 )
		{
			cout << "你输入的数据有误" << endl;
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
		cout << "搜索不到该学生" << endl;
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
		cout << "请输入学生的名字(不超过十个字节)" << endl;
		scanf("%11s", &TempName);
		fflush(stdin);
		if (strlen(TempName) > 10 || strlen(TempName) == 0)
		{
			cout << "长度有误" << endl;
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
			cout << "编号：" << pNode->stu->Student_ID << endl;
			cout << "姓名:" << pNode->stu->SzName.GetBuff() << endl;
			cout << pNode->stu->YearsOfBirth << "年" << pNode->stu->DataOfBirth << "出生" << endl;
			cout << "性别:" << pNode->stu->Gender.GetBuff() << endl;

			if (pNode->SameName != nullptr)
			{
				AVLNode* Next = pNode->SameName;

				while (Next!= nullptr)
				{
					cout << "编号：" << Next->stu->Student_ID << endl;
					cout << "姓名:" << Next->stu->SzName.GetBuff() << endl;
					cout << Next->stu->YearsOfBirth << "年" << Next->stu->DataOfBirth << "出生" << endl;
					cout << "性别:" << Next->stu->Gender.GetBuff() << endl;

					Next = Next->SameName;
				}



			}
				
			system("pause");
			return true;
		}
	}

	cout << "搜索不到该名学生" << endl;
	system("pause");
	return false;
}

inline void IO::Menu()
{
	
		printf(" **************************************** \n");
		printf("	 学   生   管   理   系   统   \n");
		printf(" **************************************** \n");

		printf("1.增加学生信息\n ");
		printf("2.按学号查找信息\n ");
		printf("3.按姓名查找信息\n ");
		printf("  4.删除信息 \n ");
		printf("  5.修改信息 \n ");
		printf("  6.保存数据 \n ");
		printf("  7.生成百万学生文本(测试用)\n");
		printf("  8.导入百万学生数据（(测试用)）\n");
		printf("  9.导入正常数据\n");
		printf("  10.展示当前学生数据（测试百万数据时切勿使用）\n");
		printf("0.退出系统\n");
		printf("请选择：\n");
	
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
			cout << "输入有误,请重新输入" << endl;
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
	cout << "输入需要删除的学生学号" << endl;
	while (1)
	{
		cout << "请输入正整数作为学生的学号" << endl;
		scanf("%8d", &TempId);
		fflush(stdin);
		if (TempId == 0 || TempId < 0 || TempId>9000000 )
		{
			cout << "你输入的数据有误" << endl;
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
	//根据ID号返回结点
	AVLNode* p = M->FindNode(TempId);

	if (p != nullptr)
	{	
		CMyString temp = p->stu->SzName;
		Result2 = T->Delete_Name(temp, TempId);
		Result1 = M->Delete_ID(TempId);
	}
	else
	{
		cout << "不存值该结点" << endl;
		system("pause");
		return false;
	}

	if ((Result1 == true|| Result2 == true))
	{
		cout << "删除成功" << endl;
		system("pause");
		return true;

	}
	else
	{	
		cout << "删除失败" << endl;
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
		cout << "请输入修改的数据" << endl;
		Result2 = InPutInfo(T, Main);
	}
	else
	{
		cout << "请使用功能1创建学生信息" << endl;
		system("pause");
		return false;
	}
	if (Result1 == true && Result2 == true)
	{
		cout << "修改成功" << endl;
		system("pause");
		return true;

	}
	else
	{
		cout << "修改失败" << endl;
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
		 cout << "数据保存成功" << endl;
		 system("pause");
		 return true;
	 }
	 else
	 {
		 cout << "数据保存失败" << endl;
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
		 cout << "当前树为空树" << endl;
		 system("pause");
		 return false;
	 }
	 
 }

 

 inline bool IO::InputStu(CAVLTree* T, CAVLTree* M)
 {	
	 ifstream inFile("StudentDate.bin",ios::in );
	 //文件操作缓存变量
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

		 //写入树
		 T->Insert(*TempStud);
		 Main->InsertMain(*TempStud);
	 }
	 inFile.clear();
	 inFile.close();
	 cout << "导入完成" << endl;
	 system("pause");
	 return true;
 }

 

 inline bool IO::INputMiData(CAVLTree* T, CAVLTree* M)
 {
	 ifstream CreaFile("MinStudent.bin", ios::in | ios::app);
	 //文件操作缓存变量
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

		 //写入树
		 T->Insert(*TempStud);
		 Main->InsertMain(*TempStud);
	 }
	 CreaFile.clear();
	 CreaFile.close();
	 cout << "导入成功" << endl;
	 system("pause");
	 return true;
 }