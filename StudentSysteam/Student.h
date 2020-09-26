#pragma once
#ifndef STUDENT_H_
#define STUDENT_H_

#include "CMyString.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
struct Student
{	
	Student() {}

	Student(CMyString& name,int id,int yb,int db, CMyString gen)
	{
		SzName = name;
		Student_ID = id;
		YearsOfBirth = yb;
		DataOfBirth = db;
		Gender = gen;
	}

	Student(Student& stuobj)
	{
		SzName = stuobj.SzName;
		Student_ID = stuobj.Student_ID;
		YearsOfBirth = stuobj.YearsOfBirth;
		DataOfBirth = stuobj.DataOfBirth;
		Gender = stuobj.Gender;
	}

	~Student()
	{

	}


	CMyString SzName;  //学生姓名
	int Student_ID;    //学生编号
	int YearsOfBirth;  //出生年份
	int DataOfBirth;  //出生日期
	CMyString Gender;//学生性别
};




#endif