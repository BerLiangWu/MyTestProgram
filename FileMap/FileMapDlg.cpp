
// FileMapDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FileMap.h"
#include "FileMapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileMapDlg 对话框



CFileMapDlg::CFileMapDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combox);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CFileMapDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFileMapDlg::OnBnClickedButton1)
//	ON_WM_LBUTTONDBLCLK()
//ON_WM_MBUTTONDBLCLK()
//ON_NOTIFY(NM_CLICK, IDC_LIST1, &CFileMapDlg::OnClickList1)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFileMapDlg::OnDblclkList1)
END_MESSAGE_MAP()


// CFileMapDlg 消息处理程序

BOOL CFileMapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//初始化
	InitMainDialog();
	//ReleaseCapture();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileMapDlg::OnPaint()
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
HCURSOR CFileMapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CFileMapDlg::InitMainDialog()
{		
	RootFlag = TRUE;
	int nItemIdx = 0;
	int  nSubItemIdx = 1;
	int nIdx = 0;
	if (!FileHistroy.IsEmpty())
	{
		for (int i = 0; i < FileHistroy.GetSize(); i++)
		{
			m_combox.AddString(FileHistroy.GetAt(i));
		}
	}

	m_list.InsertColumn(nIdx++, "磁盘名");




	char szBuff[0x256] = { 0 };
	CString filename;
	CString filenames;
	CFileFind finder;
	CString Path;
	size_t  dwBytes = ::GetLogicalDriveStrings(0x256, szBuff);
	for (int i = 0; i < dwBytes; i++)
	{
		if (szBuff[i] != '\0')
		{
			filename += szBuff[i];
		}
		else
		{	
			RootName.Add(filename.Left(1));
			//添加内容
			filenames = filename;
			filenames = filenames + "*.*";
			finder.FindFile(filenames);

			filename = filename + "盘";
			m_list.InsertItem(nItemIdx, filename, 0);
			nItemIdx++;
			filename = "";
			filename.Delete(0);
			filenames = "";
			filenames.Delete(0);

		}
	}



	DWORD dwStyle = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

	//设置所有的列根据内容自动调整宽度
	int nCntOfConlums = m_list.GetHeaderCtrl()->GetItemCount();
	for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
	{
		m_list.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
	}
}


void CFileMapDlg::OnBnClickedButton1()
{
	CString  file;
	CString  FindName;
	bool flag=0;
	m_combox.GetWindowText(file);
	int nlen = file.GetLength();
	if (nlen > 1)
	{
		MessageBox("输入格式不符,请重新修改");

		return;
	}

	int nlenR= RootName.GetSize();
	for (int i = 0; i < nlenR; i++)
	{
		if (file == RootName.GetAt(i))
		{
			flag = 1;
		}
	}

	if (flag == 1)
	{
		FileHistroy.Add(file);
	}
	else
	{
		MessageBox("您的计算机不存在该磁盘");

		return;
	}
	file = file + ":\\*.*";
	FindName = file;
	SearchOK(FindName);
}


void CFileMapDlg::SearchOK(CString Buff)
{	
	

	CFileFind finder;
	
	bool FindOk=finder.FindFile(Buff);
	int cnItemIdx =0;
	if (FindOk)
	{
		ChilTapInit();
		while (finder.FindNextFile())
		{
			CString csFileTitle = finder.GetFileTitle();
			CString Path = finder.GetFilePath();

			cnItemIdx++;
			m_list.InsertItem(cnItemIdx, csFileTitle, 0);
			m_list.SetItemText(cnItemIdx, 1, Path);
		}
	}
	else
	{
		MessageBox("该路径无法进入");
	}
	
}

void CFileMapDlg::ChilTapInit()
{	
	RootFlag = FALSE;
	ViewCler();
	m_list.InsertColumn(0, "文件名");
	m_list.InsertColumn(1, "路径");
	m_list.InsertItem(0, "返回上层目录", 0);

	DWORD dwStyle = m_list.GetExtendedStyle();
	m_list.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT);

	//设置所有的列根据内容自动调整宽度
	int nCntOfConlums = m_list.GetHeaderCtrl()->GetItemCount();
	for (int nIdx = 0; nIdx < nCntOfConlums; ++nIdx)
	{
		m_list.SetColumnWidth(nIdx, LVSCW_AUTOSIZE_USEHEADER);
	}
}



void CFileMapDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	int  nIdx = m_list.GetSelectionMark();
	CString csName = m_list.GetItemText(nIdx, 0);
	CString Path= m_list.GetItemText(nIdx, 1);
	CString proname;
	int nLen = FileHistroy.GetSize();
	CFileFind finder;
	CString Root;
	//FileHistroy.Add(Path);
	if (csName == "返回上层目录")
	{
		proname = FileHistroy.GetAt(nLen - 1);

		//如果是盘符界面
		for (size_t i = 0; i < RootName.GetSize(); i++)
		{
			if (proname == RootName.GetAt(i))
			{	
				FileHistroy.RemoveAt(nLen - 1);
				ViewCler();
				InitMainDialog();
				return;
			}
		}
		//不是盘符界面
		FileHistroy.RemoveAt(nLen - 1);
		proname=proname + "*.*";
		SearchOK(proname);
	}
	//如果不是返回上层
	//则获取路径
	else
	{	
		if (RootFlag == TRUE)
		{
			Root = csName.Left(1);
			FileHistroy.Add(Root);
			Root = Root + ":\\*.*";
			SearchOK(Root);
			return;
		}
		



		csName = Path + "\\*.*";
		//记录一下当前根目录
		int StrLen = Path.GetLength();
		for (int i = StrLen; ; i--)
		{
			if (Path[i] == '\\')
			{
				break;
			}
			else
			{
				Path.Delete(i);
			}
		}
		FileHistroy.Add(Path);
		
		SearchOK(csName);
	}

}
