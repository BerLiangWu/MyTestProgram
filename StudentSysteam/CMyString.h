#pragma once
class CMyString
{
public:
	CMyString();
	CMyString(const char* szStr);
	CMyString(const CMyString& strObj);
	~CMyString();
	int GetBuffLen();
	const char* GetBuff();
	CMyString&operator=(const CMyString&obj);
	CMyString operator+(const CMyString&obj);
	char operator[](int index);
	bool operator ==(CMyString& obj);
	bool operator !=(CMyString& obj);
	bool operator>(CMyString& obj);
	void SetChar(int nIdex, char ch);
	void Copy(const char* szStr);
	void Copy(CMyString& strObj);
	void Cat(const char* szStr);
	void Cat(CMyString& strObj);
	void Upper();
	void Lower();


	static CMyString ValueOf(bool b); //true ==> "true"
	static CMyString ValueOf(char c);    //a ==> "a"
	static CMyString ValueOf(double d);  //3.5 ==> "3.5"
	static CMyString ValueOf(float f);   //4.5f ==> "4.5"
	static CMyString ValueOf(int i);   //123 ==> "123"
	static CMyString ValueOf(long i);    //123 ==> "123"
	static CMyString ValueOf(short i);   //123 ==> "123"
	static CMyString ValueOf(const char* data); //char[] = "123" ==> string "123"
	static CMyString CopyValueOf(const char* data, int offset, int count); //char[] = "123" ==> string "123"
	static CMyString Format(CMyString format, ...);  //("%d", 123) ==> string "123"



	void Replace(const char* szSrc, const char* szDst); //字符串替换
	void Replace(char chSrc, char chDst); //字符替换
	int Find(const char* szStr); //查找
	int Find(int nIdx, const char* szStr); //查找
	int Find(CMyString& strObj); //查找
	int Find(int nIdx, CMyString& strObj); //查找
	int ReverseFind(const char* szStr); //反向查找
	int ReverseFind(int nIdx, const char* szStr); //反向查找
	int ReverseFind(CMyString& strObj); //反向查找
	int ReverseFind(int nIdx, CMyString& strObj); //反向查找
	int Cmp(const char* szStr);  //比较
	int Cmp(CMyString& strObj);  //比较

	//从左侧提取指定个数的字符为新字符串
	CMyString Left(int nLen);

	//提取指定索引位置之间的字符为新字符串
	CMyString Mid(int nIdxBegin, int nIdxEnd);

	//从右侧提取指定个数的字符为新字符串
	CMyString Right(int nLen);

	//格式化字符串 vsprintf
	void Formate(const char* szFmt, ...);

private:
	void SetBuff(const char* szStr);


private:
	char* m_pSuperBuff;//字符串所在的缓冲区
	int m_nBuffSize; //缓冲区大小
	int* m_pnRefCount ;
};



class CException
{
public:
	CException(const char* pFileInfo, const char* pFuncInfo, const int nLine)
	{
		m_pFileInfo = const_cast<char*>(pFileInfo);
		m_pFuncInfo = const_cast<char*>(pFuncInfo);
		m_nLine = nLine;
	}
	~CException()
	{

	}
	const char* GetErrInfo() const
	{
		return "内存分配失败";
	}
	const char* GetFileInfo()const
	{
		return m_pFileInfo;
	}
	const char* GetFuncInfo() const
	{
		return m_pFuncInfo;
	}
	const int GetLineInfo() const
	{
		return m_nLine;
	}
private:
	char* m_pFileInfo; //出错的文件
	char* m_pFuncInfo; //出错的函数名
	int m_nLine;//出错的行数
};