// CFileInfo.cpp: 实现文件
//

#include "pch.h"
#include "MyPeTools.h"
#include "CFileInfo.h"


// CFileInfo

IMPLEMENT_DYNAMIC(CFileInfo, CWnd)

CFileInfo::CFileInfo()
{

}

CFileInfo::~CFileInfo()
{
}

BOOL CFileInfo::IsPeFile()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;

	if (pImageBase == NULL)
	{
		return FALSE;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)  //MZ
	{
		return FALSE;
	}
	pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader->e_lfanew+ pDosHeader); //计算NT表头

	//无法计算出NT头？
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CFileInfo::LoadFile()
{
	if (strFilePath.IsEmpty())
	{
		return FALSE;
	}
	//按权限打开文件
	hFile = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	//创建文件映射
	hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hMapping == NULL)
	{
		CloseHandle(hFile);
		hFile = NULL;
		return FALSE;
	}
	pImageBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	if (pImageBase == NULL)
	{
		CloseHandle(hMapping);
		CloseHandle(hFile);

		hMapping = NULL;
		hFile = NULL;
		return FALSE;
	}

	return TRUE;
}

void CFileInfo::UnLoadFile()
{
	if (pImageBase != NULL)
	{
		UnmapViewOfFile(pImageBase);
	}
	if (hMapping != NULL)
	{
		CloseHandle(hMapping);
	}
	if (hFile != NULL)
	{
		CloseHandle(hFile);
	}

	pImageBase = NULL;
	hFile = NULL;
	hMapping = NULL;
}

PIMAGE_FILE_HEADER CFileInfo::GetFileHeader()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	if (NULL == pImageBase)
	{
		return NULL;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS)(pDosHeader + (LONG)(pDosHeader->e_lfanew));
	return &(pNtHeader->FileHeader);
}

void CFileInfo::GetTargetPlatform(CString& strMachine)
{
	DWORD dwMachine = 0;
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	if (NULL != pFileHeader)
	{
		dwMachine = pFileHeader->Machine;
		switch (dwMachine)
		{
		case IMAGE_FILE_MACHINE_I386:
			strMachine = _T("x86");
			break;
		case IMAGE_FILE_MACHINE_IA64:
			strMachine = _T("Intel Itanium");
			break;
		case IMAGE_FILE_MACHINE_AMD64:
			strMachine = _T("x64");
			break;
		default:
			strMachine = _T("Unknow");
			break;
		}
	}
}



BEGIN_MESSAGE_MAP(CFileInfo, CWnd)
END_MESSAGE_MAP()



// CFileInfo 消息处理程序


