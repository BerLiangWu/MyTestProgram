// Inject.cpp: 实现文件
//

#include "pch.h"
#include "ProcessMap.h"
#include "Inject.h"
#include "afxdialogex.h"


// Inject 对话框


DWORD dwHandle; 
HANDLE hThread = NULL;
IMPLEMENT_DYNAMIC(Inject, CDialogEx)

Inject::Inject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Inject::~Inject()
{
}

void Inject::InjectObject()
{	
	
	//获取DLL名字
	m_DllName.GetWindowText(DllPath);

	//获取LoadLibrary的地址
	HMODULE hMod = GetModuleHandle("kernel32");
	FARPROC pfnLoadLibrary = GetProcAddress(hMod, "LoadLibraryA");

	//Dll的Path
	 pDllBuff = VirtualAllocEx(
		hWnd,
		NULL, //系统自动分配地址
		0x1000,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE//内存可读可写
	);

	BOOL bRet = WriteProcessMemory(
		hWnd,
		pDllBuff,
		DllPath,
		DllPath.GetLength(),
		&dwID
	);

	//4. 创建远程线程，让目标进程加载dll
	 hThread = CreateRemoteThread(
		hWnd,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)pfnLoadLibrary,
		pDllBuff,
		0,
		NULL
	);

	


	if (hThread == NULL)
	{
		MessageBox("加载不成功");

	}
	else
	{
		MessageBox("加载成功");
	}

	
}

void Inject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_DllName);
	DDX_Control(pDX, IDC_EDIT1, m_Name);
}


BEGIN_MESSAGE_MAP(Inject, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Inject::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Inject::OnBnClickedButton2)
END_MESSAGE_MAP()


// Inject 消息处理程序


void Inject::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	InjectObject();
}


void Inject::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	m_DllName.GetWindowText(DllPath);
	//获取FreeLibrary的地址
	HMODULE hMod = GetModuleHandle("kernel32");
	FARPROC pfnFreeLibrary = GetProcAddress(hMod, "FreeLibrary");

	GetExitCodeThread(hThread, &dwHandle);

	VirtualFreeEx(hWnd, pDllBuff, 0x1000, MEM_DECOMMIT);

	//4. 创建远程线程，让目标进程卸载dll
	 hThread = CreateRemoteThread(
		hWnd,
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)pfnFreeLibrary,
		 (LPVOID)dwHandle,
		0,
		&dwID
	);

	 CloseHandle(hThread);



	if (hThread!=NULL)
	{
		MessageBox("卸载完毕");
	}
	else
	{
		MessageBox("卸载不成功");
	}

}
