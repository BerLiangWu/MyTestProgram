#pragma once


// CFileInfo

class CFileInfo : public CWnd
{
	DECLARE_DYNAMIC(CFileInfo)
public:
	CString strFilePath; //对应PE文件所在路径
	HANDLE hFile; //打开这个文件时的文件句柄
	PVOID pImageBase; //文件在内存中的首地址
	HANDLE hMapping; //文件映射的句柄
public:
	CFileInfo();
	virtual ~CFileInfo();
	BOOL IsPeFile();   //判断是否为PE
	BOOL LoadFile();   //加载文件
	void UnLoadFile();  //卸载文件
	PIMAGE_FILE_HEADER GetFileHeader();
	void GetTargetPlatform(CString& strMachine);
protected:
	DECLARE_MESSAGE_MAP()

};


