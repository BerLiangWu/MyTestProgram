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



	void Replace(const char* szSrc, const char* szDst); //�ַ����滻
	void Replace(char chSrc, char chDst); //�ַ��滻
	int Find(const char* szStr); //����
	int Find(int nIdx, const char* szStr); //����
	int Find(CMyString& strObj); //����
	int Find(int nIdx, CMyString& strObj); //����
	int ReverseFind(const char* szStr); //�������
	int ReverseFind(int nIdx, const char* szStr); //�������
	int ReverseFind(CMyString& strObj); //�������
	int ReverseFind(int nIdx, CMyString& strObj); //�������
	int Cmp(const char* szStr);  //�Ƚ�
	int Cmp(CMyString& strObj);  //�Ƚ�

	//�������ȡָ���������ַ�Ϊ���ַ���
	CMyString Left(int nLen);

	//��ȡָ������λ��֮����ַ�Ϊ���ַ���
	CMyString Mid(int nIdxBegin, int nIdxEnd);

	//���Ҳ���ȡָ���������ַ�Ϊ���ַ���
	CMyString Right(int nLen);

	//��ʽ���ַ��� vsprintf
	void Formate(const char* szFmt, ...);

private:
	void SetBuff(const char* szStr);


private:
	char* m_pSuperBuff;//�ַ������ڵĻ�����
	int m_nBuffSize; //��������С
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
		return "�ڴ����ʧ��";
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
	char* m_pFileInfo; //������ļ�
	char* m_pFuncInfo; //����ĺ�����
	int m_nLine;//���������
};