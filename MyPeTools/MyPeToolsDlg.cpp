
// MyPeToolsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyPeTools.h"
#include "MyPeToolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMyPeToolsDlg 对话框



CMyPeToolsDlg::CMyPeToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYPETOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyPeToolsDlg::ShowFileHeaderInfo()
{
	PIMAGE_FILE_HEADER pFileHeader = m_PeFileInfo.GetFileHeader();
	if (NULL != pFileHeader)
	{
		CString strTemp = _T("");
		m_PeFileInfo.GetTargetPlatform(strTemp);
		GetDlgItem(EDI_MA)->SetWindowText(strTemp);

		strTemp.Format(_T("%d"), pFileHeader->NumberOfSections);
		GetDlgItem(EDI_NUMO)->SetWindowText(strTemp);

		//时间戳转为具体时间
		tm p;
		errno_t err1;
		err1 = gmtime_s(&p, (time_t*)&pFileHeader->TimeDateStamp);
		TCHAR s[100] = { 0 };
		//_tcsftime(s, sizeof(s) / sizeof(TCHAR), _T("%Y-%m-%d %H:%M:%S"), &p);
		GetDlgItem(EDI_Time)->SetWindowText(s);

		strTemp.Format(_T("0x%08x"), pFileHeader->PointerToSymbolTable);
		GetDlgItem(EDI_Poiner)->SetWindowText(strTemp);

		strTemp.Format(_T("%d"), pFileHeader->NumberOfSymbols);
		GetDlgItem(EDI_NumberOfS)->SetWindowText(strTemp);

		strTemp.Format(_T("0x%08x"), pFileHeader->SizeOfOptionalHeader);
		GetDlgItem(EDI_SOOH)->SetWindowText(strTemp);
		strTemp.Format(_T("0x%08x"), pFileHeader->Characteristics);
		GetDlgItem(EDI_Chara)->SetWindowText(strTemp);
	}
	else
	{
		MessageBox(_T("显示数据错误"));
	}
}

void CMyPeToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_File);
}

BEGIN_MESSAGE_MAP(CMyPeToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_Analysis, &CMyPeToolsDlg::OnBnClickedAnalysis)
END_MESSAGE_MAP()


// CMyPeToolsDlg 消息处理程序

BOOL CMyPeToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

void CMyPeToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyPeToolsDlg::OnPaint()
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
HCURSOR CMyPeToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyPeToolsDlg::OnBnClickedAnalysis()
{
	// TODO: 在此添加控件通知处理程序代码

	m_File.GetWindowText(m_PeFileInfo.strFilePath);
	m_PeFileInfo.UnLoadFile();
	BOOL bLoadSuccess = m_PeFileInfo.LoadFile();
	if (bLoadSuccess)
	{
		//成功打开
		if (m_PeFileInfo.IsPeFile())
		{
			ShowFileHeaderInfo();
			//ShowOptionHeaderInfo();
			

		}
		else
		{
			MessageBox(_T("打开的文件不是PE文件"));
			
		}
	}
}
