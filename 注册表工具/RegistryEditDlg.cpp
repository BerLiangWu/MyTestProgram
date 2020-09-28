
// RegistryEditDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RegistryEdit.h"
#include "RegistryEditDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HICON m_hIcon;
CImageList	m_HeadIcon;
HKEY		hKey;			//注册表返回句柄
HKEY		MKEY;			//用于保存主键
CString		FullPath = "";
HTREEITEM	SelectNode = NULL;

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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRegistryEditDlg 对话框



CRegistryEditDlg::CRegistryEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTRYEDIT_DIALOG, pParent)
{
	
}

void CRegistryEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Ctree);
	DDX_Control(pDX, IDC_LIST1, m_CList);
}

BEGIN_MESSAGE_MAP(CRegistryEditDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CRegistryEditDlg::OnDRC)
END_MESSAGE_MAP()


// CRegistryEditDlg 消息处理程序

BOOL CRegistryEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	InitCTreeView();
	InitCListView();

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

void CRegistryEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRegistryEditDlg::OnPaint()
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
HCURSOR CRegistryEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRegistryEditDlg::InitCTreeView()
{	
	

	m_Ctree.ModifyStyle(0,
		TVS_HASLINES
		| TVS_LINESATROOT
		| TVS_HASBUTTONS
		| TVS_EDITLABELS
		| TVS_SHOWSELALWAYS
		| TVS_NOTOOLTIPS
		| TVS_DISABLEDRAGDROP
	/*|TVS_SINGLEEXPAND*/);
	DWORD	dwStyle = GetWindowLong(m_Ctree.m_hWnd, GWL_STYLE);
	SetWindowLong(m_Ctree.m_hWnd, GWL_STYLE, dwStyle);


	 m_Root = m_Ctree.InsertItem("注册表一览", 0, 0, 0,0);
	 hRoot = m_Ctree.InsertItem("HKEY_CLASSES_ROOT",1,1,m_Root,0);
	 hUser = m_Ctree.InsertItem("HKEY_CURRENT_USER", 1, 1, m_Root, 0);
	 hMachine = m_Ctree.InsertItem("HKEY_LOCAL_MACHINE", 1, 1, m_Root, 0);
	 hUserS = m_Ctree.InsertItem("HKEY_USERS", 1, 1, m_Root, 0);
	 hConfit = m_Ctree.InsertItem("HKEY_CURRENT_CONFIG", 1, 1, m_Root, 0);
	 
	 m_Ctree.Expand(m_Root, TVE_EXPAND);
}

void CRegistryEditDlg::InitCListView()
{
	int nIdx = 0;
	m_CList.InsertColumn(nIdx++, "名称");
	m_CList.InsertColumn(nIdx++, "类型");
	m_CList.InsertColumn(nIdx, "数据");

	DWORD dwStyle = m_CList.GetExtendedStyle();
	m_CList.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

	//设置所有的列根据内容自动调整宽度
	int nCntOfConlums = m_CList.GetHeaderCtrl()->GetItemCount();
	for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
	{
		m_CList.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
	}
}


//双击关闭或者打开目录
void CRegistryEditDlg::OnDRC(NMHDR* pNMHDR, LRESULT* pResult)
{	
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: 在此添加控件通知处理程序代码
	
	TVITEM item = pNMTreeView->itemNew;

	m_CList.DeleteAllItems();

	SelectNode = m_Ctree.GetSelectedItem();			//保存用户打开的子树节点句柄

	if (item.hItem == m_Root)
	{
		return;
	}


	HTREEITEM CurrentNode = m_Ctree.GetSelectedItem();//得到当前子树句柄

	CString Temp;
	CString FullPath = "";
	while (CurrentNode != m_Root)
	{
		Temp = m_Ctree.GetItemText(CurrentNode);
		if (Temp.Right(1) != "\\")
		{
			Temp += "\\";
		}
		FullPath = Temp + FullPath;
		CurrentNode = m_Ctree.GetParentItem(CurrentNode);
	}


	if (!FullPath.Find("HKEY_CLASSES_ROOT"))	//判断主键
	{
		MKEY = HKEY_CLASSES_ROOT;
		FullPath.Delete(0, sizeof("HKEY_CLASSES_ROOT"));
	}
	else
		if (!FullPath.Find("HKEY_CURRENT_USER"))
		{
			MKEY = HKEY_CURRENT_USER;
			FullPath.Delete(0, sizeof("HKEY_CURRENT_USER"));

		}
		else
			if (!FullPath.Find("HKEY_LOCAL_MACHINE"))
			{
				MKEY = HKEY_LOCAL_MACHINE;
				FullPath.Delete(0, sizeof("HKEY_LOCAL_MACHINE"));

			}
			else
				if (!FullPath.Find("HKEY_USERS"))
				{
					MKEY = HKEY_USERS;
					FullPath.Delete(0, sizeof("HKEY_USERS"));

				}
				else
					if (!FullPath.Find("HKEY_CURRENT_CONFIG"))
					{
						MKEY = HKEY_CURRENT_CONFIG;
						FullPath.Delete(0, sizeof("HKEY_CURRENT_CONFIG"));

					}

	if (RegOpenKeyEx(MKEY, FullPath.LockBuffer(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)//打开
	{

		char* szValueName;		//键值名称
		char* szKeyName;			//子键名称
		LPBYTE	szValueDate;		//键值数据

		DWORD dwIndex = 0, NameSize, NameCnt, NameMaxLen, Type;
		DWORD KeySize, KeyCnt, KeyMaxLen, DateSize, MaxDateLen;

		if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &KeyCnt, &KeyMaxLen, NULL, &NameCnt, &NameMaxLen, &MaxDateLen, NULL, NULL) != ERROR_SUCCESS)
		{
			AfxMessageBox("RegQueryInfoKey错误");
			return;
		}

		int nitem = m_CList.InsertItem(0, "(默认)", 0);
		m_CList.SetItemText(nitem, 1, "REG_SZ");
		m_CList.SetItemText(nitem, 2, "(数据未设置)");


		for (dwIndex = 0; dwIndex < NameCnt; dwIndex++)	//枚举键值
		{
			DateSize = MaxDateLen + 1;
			NameSize = NameMaxLen + 100;
			szValueName = (char*)malloc(NameSize);
			szValueDate = (LPBYTE)malloc(DateSize);
			RegEnumValue(hKey, dwIndex, szValueName, &NameSize, NULL, &Type, szValueDate, &DateSize);//读取键值


			if (Type == REG_SZ)
			{
				int nitem = m_CList.InsertItem(0, szValueName, 0);
				m_CList.SetItemText(nitem, 1, "REG_SZ");
				m_CList.SetItemText(nitem, 2, (char*)szValueDate);
			}
			if (Type == REG_DWORD)
			{
				char ValueDate[256];
				sprintf(ValueDate, "%wd", szValueDate);

				int nitem = m_CList.InsertItem(0, szValueName, 1);
				m_CList.SetItemText(nitem, 1, "REG_DWORD");
				m_CList.SetItemText(nitem, 2, ValueDate);
			}
			if (Type == REG_BINARY)
			{
				char ValueDate[256];
				sprintf(ValueDate, "%wd", szValueDate);

				int nitem = m_CList.InsertItem(0, szValueName, 1);
				m_CList.SetItemText(nitem, 1, "REG_BINARY");
				m_CList.SetItemText(nitem, 2, ValueDate);
			}
			if (Type == REG_EXPAND_SZ)
			{
				int nitem = m_CList.InsertItem(0, szValueName, 0);
				m_CList.SetItemText(nitem, 1, "REG_EXPAND_SZ");
				m_CList.SetItemText(nitem, 2, (char*)szValueDate);
			}

		}


		for (dwIndex = 0; dwIndex < KeyCnt; dwIndex++)		//枚举子键
		{
			KeySize = KeyMaxLen + 1;
			szKeyName = (char*)malloc(KeySize);
			RegEnumKeyEx(hKey, dwIndex, szKeyName, &KeySize, NULL, NULL, NULL, NULL);

			m_Ctree.InsertItem(szKeyName, 1, 1, SelectNode, 0);//插入子键名称
			DWORD dwStyle = m_CList.GetExtendedStyle();
			m_CList.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

			//设置所有的列根据内容自动调整宽度
			int nCntOfConlums = m_CList.GetHeaderCtrl()->GetItemCount();
			for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
			{
				m_CList.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
			}
			m_Ctree.Expand(SelectNode, TVE_EXPAND);

		}
		RegCloseKey(hKey);
	}
	else
	{
		AfxMessageBox("打开注册表失败 或者 权限不够");
	}
	
	*pResult = 0;
}
