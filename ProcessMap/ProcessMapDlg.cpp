
// ProcessMapDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ProcessMap.h"
#include "ProcessMapDlg.h"
#include "afxdialogex.h"

#include <tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UesDll  uDLL;
BOOL HadLoad = FALSE;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProcessMapDlg 对话框



CProcessMapDlg::CProcessMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESSMAP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_PROList);
}

BEGIN_MESSAGE_MAP(CProcessMapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CProcessMapDlg::OnRclickList1)
	ON_COMMAND(ID_32771, &CProcessMapDlg::OnChek)
	ON_COMMAND(ID_32772, &CProcessMapDlg::Kill)
	ON_COMMAND(ID_32773, &CProcessMapDlg::OnInjectThread)
END_MESSAGE_MAP()


// CProcessMapDlg 消息处理程序

BOOL CProcessMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	InitList();


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProcessMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		/*dlgAbout.DoModal();*/
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProcessMapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProcessMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProcessMapDlg::InitList()
{
	int nIdx = 0;
	m_PROList.InsertColumn(0, "进程名");
	m_PROList.InsertColumn(1, "PID");
	m_PROList.InsertColumn(2, "父PID");
	HANDLE         hProcessSnap = NULL;
	PROCESSENTRY32 pe32 ;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	char Buff[1024];
	CString str;
	CString fstr;
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return;
		}
		
		BOOL hProcess = Process32First(hProcessSnap, &pe32);
	
		while (hProcess)
		{	
				
			m_PROList.InsertItem(nIdx,pe32.szExeFile, 0);
			str.Format("%d", pe32.th32ProcessID);
			fstr.Format("%d", pe32.th32ParentProcessID);
			m_PROList.SetItemText(nIdx,1, str);
			m_PROList.SetItemText(nIdx, 2, fstr);
			str = "";
			str.Delete(0);
			fstr = "";
			fstr.Delete(0);
			nIdx++;
			hProcess = Process32Next(hProcessSnap, &pe32);
		} 

	CloseHandle(hProcessSnap);


	DWORD dwStyle = m_PROList.GetExtendedStyle();
	m_PROList.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

	//设置所有的列根据内容自动调整宽度
	int nCntOfConlums = m_PROList.GetHeaderCtrl()->GetItemCount();
	for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
	{
		m_PROList.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
	}
}



void CProcessMapDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_PROList.ClientToScreen(&pNMItemActivate->ptAction);

	/*
	* 弹出菜单
	*/
	CMenu mn;
	mn.LoadMenu(IDR_MENU1); //从资源加载菜单
	CMenu* pSubMenu = mn.GetSubMenu(0);
	pSubMenu->TrackPopupMenu(
		TPM_LEFTALIGN,
		pNMItemActivate->ptAction.x,
		pNMItemActivate->ptAction.y,
		this);
}

bool CProcessMapDlg::KillProcess(DWORD dwPid)
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


void CProcessMapDlg::OnChek()
{

	CString strPid;
	CString strName;

	UpdateData(TRUE);
	UINT pid = 0;
	int  nIdx = m_PROList.GetSelectionMark();  //获取当前选中行
	strPid = m_PROList.GetItemText(nIdx, 1);  //获取PID
	//strName= m_PROList.GetItemText(nIdx, 0);  //获取Name;

	pid = atoi(strPid);

	ClistMod.Modepe32.th32ProcessID = pid;

	UpdateData(FALSE);
	if (ClistMod.DoModal())
	{
		
	}
}


void CProcessMapDlg::Kill()
{
	// TODO: 在此添加命令处理程序代码
	CString strPid;
	int  nIdx = m_PROList.GetSelectionMark();
	strPid = m_PROList.GetItemText(nIdx, 1);
	DWORD dw1;
	dw1 = (DWORD)atoi(strPid);
	KillProcess(dw1);
	
}


void CProcessMapDlg::OnInjectThread()
{
	// TODO: 在此添加命令处理程序代码
	
	if (HadLoad == TRUE)
	{
		HadLoad = FALSE;
		UpdateData(TRUE);
		 CInject.hWnd=uDLL.LoadProcess;
		  CInject.dwID = uDLL.LoadProcessId ;
		  CInject.pDllBuff = uDLL.DllBuff ;
		  CInject.DllPath = uDLL.DllName;
		UpdateData(FALSE);

	}
	else
	{
		//获取当前选中行
		UpdateData(TRUE);
		CString strPid;
		int  nIdx = m_PROList.GetSelectionMark();
		strPid = m_PROList.GetItemText(nIdx, 1);
		DWORD dw1;
		dw1 = (DWORD)atoi(strPid);

		//得到当前句柄
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dw1);

		if (hProcess == INVALID_HANDLE_VALUE)
		{
			return;
		}

		//传入句柄
		CInject.hWnd = hProcess;

		UpdateData(FALSE);
		//打开注入对话框
	}


	
	if (CInject.DoModal())
	{
		UpdateData(TRUE);
		uDLL.LoadProcess = CInject.hWnd;
		uDLL.LoadProcessId = CInject.dwID;
		uDLL.DllBuff = CInject.pDllBuff;
		uDLL.DllName = CInject.DllPath;
		UpdateData(FALSE);
		HadLoad = TRUE;
		
	}

}
