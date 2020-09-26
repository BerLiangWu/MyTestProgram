#define _CRT_SECURE_NO_WARNINGS
#include "CMyString.h"
#include <string.h>
#include <iostream>
#include   <stdio.h>    
#include   <conio.h>    
#include   <stdarg.h>    
using namespace std;

#define Valid 1
#define ERROR 0


CMyString::CMyString()
{	
	m_pSuperBuff = nullptr;
	m_nBuffSize = 0;
	try
	{
		m_pnRefCount = new int(0);
		if (m_pnRefCount == nullptr)
		{
			throw CException(__FILE__, "CMyString()", __LINE__);
		}
	}
	catch ( const CException & CE)
	{
		printf(" 文件：%s\n 行数：%d\n 函数：%s\n 错误信息：%s\r\n\r\n",
			CE.GetFileInfo(),
			CE.GetLineInfo(),
			CE.GetFuncInfo(),
			CE.GetErrInfo());
		system("pause");
		
	}
	(*m_pnRefCount)++;
}


CMyString::CMyString(const char* szStr)
{	
	int Len = strlen(szStr);
	this->m_pSuperBuff = new char[Len +1];
	
	strcpy(m_pSuperBuff, szStr);
	this->m_nBuffSize = Len + 1;
	m_pnRefCount = new int(0);

	(*m_pnRefCount)++;
}

CMyString::CMyString( const CMyString& strobj)
{
	m_nBuffSize = strobj.m_nBuffSize;
	m_pSuperBuff = strobj.m_pSuperBuff;
	m_pnRefCount = strobj.m_pnRefCount;

	(*m_pnRefCount)++;

}

CMyString::~CMyString()
{
	(*m_pnRefCount)--;
	
	if ((*m_pnRefCount)==0)
	{	
		if(m_pSuperBuff!=nullptr)
		{ 
		delete m_pSuperBuff;
		m_pSuperBuff = nullptr;

		delete m_pnRefCount;
		m_pnRefCount = nullptr;
		}
	}
}


void  CMyString::Formate(const char* szFmt, ...)
{
	CMyString str;
	va_list vl;
	va_start(vl, szFmt);

	const int nBuffLen = 0x10000;
	char szBuff[nBuffLen] = { 0 };
	vsprintf(szBuff, szFmt, vl);
	Copy(szBuff);
	va_end(vl);
	
}

 const char* CMyString::GetBuff()
{
	return m_pSuperBuff;
}


void CMyString::Copy(const char* szStr)
{
	SetBuff(szStr);
}

void CMyString::Copy(CMyString& strObj)
{
	SetBuff(strObj.GetBuff());
}

void CMyString::Cat(const char* szStr)
{
	if (szStr == nullptr)
	{
		return;
	}

	// 申请新内存
	int nNewLen = strlen(szStr) + m_nBuffSize;
	char* pNewBuff = new char[nNewLen];

	//拷贝和拼接字符串
	if (m_pSuperBuff != nullptr)
	{
		strcpy(pNewBuff, m_pSuperBuff);
	}
	strcat(pNewBuff, szStr);

	//释放原来的内存，保存新值
	delete[] m_pSuperBuff;
	m_pSuperBuff = pNewBuff;
	m_nBuffSize = nNewLen;
}

//拼接CMyString&，调用Cat(strObj.GetBuff());
void CMyString::Cat(CMyString& strObj)
{
	Cat(strObj.GetBuff());
}

void CMyString::SetChar(int nIdx, char ch)
{
	//写时拷贝
	(*m_pnRefCount)--;
	char* pNewBuff = new char[m_nBuffSize];
	strcpy(pNewBuff, m_pSuperBuff);
	if ((*m_pnRefCount) == 0)
	{
		delete[] m_pSuperBuff;
		delete m_pnRefCount;
		m_pnRefCount = 0;
		m_pSuperBuff = nullptr;
	}

	//新内存引用计数增加
	m_pnRefCount = new int;
	(*m_pnRefCount) = 1;

	m_pSuperBuff = pNewBuff;
	m_pSuperBuff[nIdx] = ch;
}

void CMyString::Upper()
{
	for (int i = 0; i < m_nBuffSize; i++)
	{
		if (m_pSuperBuff[i] >= 97 && m_pSuperBuff[i] <= 122)
		{
			m_pSuperBuff[i] = m_pSuperBuff[i] - 32;
		}
	}
}

void CMyString::Lower()
{
	for (int i = 0; i < m_nBuffSize; i++)
	{
		if (m_pSuperBuff[i] >= 65 && m_pSuperBuff[i] <= 90)
		{
			m_pSuperBuff[i] = m_pSuperBuff[i] + 32;
		}
	}
}

void CMyString::Replace(const char* szSrc, const char* szDst)
{
	if (strlen(szSrc) != strlen(szDst))
	{
		printf("替换与被替换内容不等长,操作无效");
		return;
	}

	char* pcTemp = 0;

	while (1)
	{
		pcTemp = strstr(m_pSuperBuff, szSrc);
		if (pcTemp == 0)
		{
			break;
		}
		strncpy(pcTemp, szDst, strlen(szSrc));
	}
}

void CMyString::Replace(char chSrc, char chDst)
{
		int i = 0;
		while (*(m_pSuperBuff + i) != '\0')
		{
			if (*(m_pSuperBuff + i) == chSrc)
			{
				*(m_pSuperBuff + i) = chDst;
			}
			i++;
		}
}


void CMyString::SetBuff(const char* szStr)
{
	int nLen = strlen(szStr);
	m_pSuperBuff = new char[nLen + 1];
	strcpy(m_pSuperBuff, szStr);
	m_nBuffSize = nLen + 1;
}

int CMyString::GetBuffLen()
{
	return m_nBuffSize;
}



int CMyString::Find(const char* szStr)
{
	if (strstr(m_pSuperBuff, szStr) == 0)
	{
		return -100;
	}
	return strstr(m_pSuperBuff, szStr) - m_pSuperBuff;
}
int  CMyString::Find(int nIdx, const char* szStr)
{
	if (strstr(m_pSuperBuff + nIdx, szStr) == 0)
	{
		return -100;
	}
	return strstr(m_pSuperBuff + nIdx, szStr) - m_pSuperBuff;
}

int CMyString::Find(CMyString& strObj)
{
	if (strstr(m_pSuperBuff, strObj.m_pSuperBuff) == 0)
	{
		return -100;
	}
	return strstr(m_pSuperBuff, strObj.m_pSuperBuff) - m_pSuperBuff;

}

int  CMyString::Find(int nIdx, CMyString& strObj)
{

	if (strstr(m_pSuperBuff + nIdx, strObj.m_pSuperBuff) == 0)
	{
		return -100;
	}
	return strstr(m_pSuperBuff + nIdx, strObj.m_pSuperBuff) - m_pSuperBuff;

}

int CMyString::ReverseFind(const char* szStr)
{
	int nLength = strlen(m_pSuperBuff);
	int i = 0;
	char* pcTemp = 0;

	while (1)
	{
		pcTemp = strstr(m_pSuperBuff + nLength - i, szStr);
		if (pcTemp != 0)
		{
			return pcTemp - m_pSuperBuff;
		}
		i++;

		if (nLength - i < 0)
		{
			return -100;
		}
	}

}

int CMyString::ReverseFind(int nIdx, const char* szStr)
{
	int i = 0;
	char* pcTemp = 0;

	while (1)
	{
		pcTemp = strstr(m_pSuperBuff + nIdx - i, szStr);
		if (pcTemp != 0 && pcTemp - m_pSuperBuff <= nIdx - strlen(szStr) + 1)
		{
			return pcTemp - m_pSuperBuff;
		}
		i++;

		if (nIdx - i < 0)
		{
			return -100;
		}
	}
}

int CMyString::ReverseFind(CMyString& strObj)
{
	int nLength = strlen(m_pSuperBuff);
	int i = 0;
	char* pcTemp = 0;

	while (1)
	{
		pcTemp = strstr(m_pSuperBuff + nLength - i, strObj.m_pSuperBuff);
		if (pcTemp != 0)
		{
			return pcTemp - m_pSuperBuff;
		}
		i++;

		if (nLength - i < 0)
		{
			return -100;
		}
	}
}

int CMyString::ReverseFind(int nIdx, CMyString& strObj)
{

	int i = 0;
	char* pcTemp = 0;

	while (1)
	{
		pcTemp = strstr(m_pSuperBuff + nIdx - i, strObj.m_pSuperBuff);
		if (pcTemp != 0)
		{
			return pcTemp - m_pSuperBuff;
		}
		i++;

		if (nIdx - i < 0)
		{
			return -100;
		}
	}
}

int CMyString::Cmp(const char* szStr)
{
	int ret = 0;
	char* tmp = m_pSuperBuff;
	while (!(ret = *(unsigned char*)tmp - *(unsigned char*)szStr))
	{
		tmp++;
		szStr++;
	}
	if (ret < 0)
	{
		ret = -1;
	}
	else if (ret > 0) {
		ret = 1;
	}

	return ret;
}

CMyString CMyString::Mid(int nIdxBegin, int nIdxEnd)
{

	CMyString tmp_MyString;
	if (nIdxBegin < 0 || nIdxEnd > m_nBuffSize)
	{
		return NULL;
	}
	char* tmp = m_pSuperBuff + nIdxBegin;

	char* dst = nullptr;
	dst = new char[nIdxEnd - nIdxBegin + 1];
	memset(dst, 0, nIdxEnd - nIdxBegin + 1);
	strncpy(dst, tmp, nIdxEnd - nIdxBegin);

	tmp_MyString.m_pSuperBuff = dst;
	tmp_MyString.m_nBuffSize = nIdxEnd - nIdxBegin + 1;

	return tmp_MyString;
}


//int CMyString::Cmp(CMyString& strObj)
//{
//	return strcmp(m_pSuperBuff, strObj.m_pSuperBuff);
//}

CMyString CMyString::ValueOf(bool b)
{	
	 CMyString strFmt;
	 strFmt.Formate("%s", b ? "true" : "false");
	 return strFmt;
}
	  
CMyString  CMyString::ValueOf(char c)
 {
	 CMyString strFmt;
	 strFmt.Formate("%c", c);
	 return strFmt;
 }
 CMyString  CMyString::ValueOf(double d)
 {
	 CMyString strFmt;
	 strFmt.Formate("%lf", d);
	 return strFmt;
 }

 CMyString CMyString::ValueOf(float f)
 {
	 CMyString strFmt;
	 strFmt.Formate("%f", f);
	 return strFmt;
 }

 CMyString CMyString::ValueOf(int i)
 {
	 CMyString strFmt;
	 strFmt.Formate("%d", i);
	 return strFmt;
 }

 CMyString CMyString::ValueOf(long i)
 {
	 CMyString strFmt;
	 strFmt.Formate("%d", i);

	 return strFmt;
 }

 CMyString CMyString::ValueOf(short i)
 {
	 CMyString strFmt;
	 strFmt.Formate("%hd", i);
	 return strFmt;
 }
 CMyString CMyString::ValueOf(const char* data)
 {
	 CMyString strFmt;
	 strFmt.Formate("%p", data);
	 return strFmt;
 }
 CMyString CMyString::CopyValueOf(const char* data, int offset, int count)
 {	
	 int d = 0;
	 CMyString str;
	 char* ary =nullptr;
	 for (int i=offset; i <offset+count; i++)
	 {
		 ary[d] = data[i];
		 d++;
	 }
	 str = ary;
	 return str;
 }
 CMyString&CMyString::operator=(const CMyString&obj)
 {	 
	 if (this==&obj)
	 {
		 return *this;
	 }
	 m_nBuffSize = obj.m_nBuffSize+1;
	 m_pnRefCount = obj.m_pnRefCount;
	 m_pSuperBuff = obj.m_pSuperBuff;

	 (*m_pnRefCount)++;
	 return *this;
 }
 CMyString CMyString::operator+(const CMyString& obj)
 {

	 char* ptemp = new char[obj.m_nBuffSize + this->m_nBuffSize + 1];
	 strcpy(ptemp, obj.m_pSuperBuff);
	 strcpy(ptemp, this->m_pSuperBuff);
	 CMyString tmp(ptemp);
	 return tmp;
 }


 bool CMyString::operator ==(CMyString& obj)
 {
	 return strcmp(this->m_pSuperBuff, obj.m_pSuperBuff) == 0;
 }

 bool CMyString::operator !=(CMyString& obj)
 {
	 return strcmp(this->m_pSuperBuff, obj.m_pSuperBuff) != 0;
 }

 bool  CMyString::operator>(CMyString& obj)
 {
	 return strcmp(this->m_pSuperBuff, obj.m_pSuperBuff)> 0;
 }

 char CMyString::operator[](int index)
 {
	 try
	 {
		 if (index > this->m_nBuffSize)
		 {
			 throw CException(__FILE__, "operator[]", __LINE__);
		 }
		 return this->m_pSuperBuff[index];
	 }
	 catch ( const CException & CE)
	 {
		 printf(" 文件：%s\n 行数：%d\n 函数：%s\n 错误信息：数组下标越界\r\n\r\n",
			 CE.GetFileInfo(),
			 CE.GetLineInfo(),
			 CE.GetFuncInfo()
			 );
	 }
	 
 }

