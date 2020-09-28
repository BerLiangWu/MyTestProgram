// CModList.cpp: 实现文件
//

#include "pch.h"
#include "ProcessMap.h"
#include "CModList.h"
#include "afxdialogex.h"


// CModList 对话框

IMPLEMENT_DYNAMIC(CModList, CDialogEx)

CModList::CModList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CModList::~CModList()
{
}

void CModList::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Mod);
}


BOOL CModList::GetProcessModule(DWORD dwPID, DWORD dwModuleID, LPMODULEENTRY32 lpMe32, DWORD cbMe32)
{	

	HANDLE        hModuleSnap = NULL;

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return (FALSE);

	int nIdx = 0;
	CString str;
	CString fstr;
	me32.dwSize = sizeof(MODULEENTRY32);

	BOOL hProcess = Module32First(hModuleSnap, &me32);

	while (hProcess)
	{
		
		m_Mod.InsertItem(nIdx, me32.szExePath, 0);
		str.Format("%d", me32.th32ProcessID);
		m_Mod.SetItemText(nIdx, 1, str);
		str = "";
		str.Delete(0);
		nIdx++;
		hProcess = Module32Next(hModuleSnap, &me32);
	}
	
	CloseHandle(hModuleSnap);


}


BEGIN_MESSAGE_MAP(CModList, CDialogEx)
END_MESSAGE_MAP()


// CModList 消息处理程序


BOOL CModList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitModList();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
bool CModList::KillProcess(DWORD dwPid)
{
	// 1. 打开进程
	HANDLE hProcess = OpenProcess(
		PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (hProcess == INVALID_HANDLE_VALUE)
		return false;

	// 2. 结束进程
	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);

	return true;
}
void CModList::InitModList()
{
	int nIdx = 0;
	m_Mod.InsertColumn(0, "模块名");
	m_Mod.InsertColumn(1, "模块PID");

	GetProcessModule(Modepe32.th32ProcessID,
		Modepe32.th32ModuleID, &me32, sizeof(MODULEENTRY32));


	DWORD dwStyle = m_Mod.GetExtendedStyle();
	m_Mod.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

	//设置所有的列根据内容自动调整宽度
	int nCntOfConlums = m_Mod.GetHeaderCtrl()->GetItemCount();
	for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
	{
		m_Mod.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
	}
}
