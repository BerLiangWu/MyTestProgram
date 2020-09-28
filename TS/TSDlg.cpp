
// TSDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TS.h"
#include "TSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CStdioFile file;
CStdioFile file1;
CString SrcFileName;
CString FileS;
int modeCount = 0; //选择膨胀次数

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


// CTSDlg 对话框



CTSDlg::CTSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TS_DIALOG, pParent)
	, PushModeBOX(FALSE)
	, OperModeBox(FALSE)
	, JumpModeBox(FALSE)
	, CallModeBox(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_file);
	//  DDX_Control(pDX, IDC_EDIT1, m_count);
	DDX_Check(pDX, IDC_CHECK1, PushModeBOX);
	DDX_Check(pDX, IDC_CHECK2, OperModeBox);
	DDX_Check(pDX, IDC_CHECK3, JumpModeBox);
	DDX_Check(pDX, IDC_CHECK4, CallModeBox);
}

BEGIN_MESSAGE_MAP(CTSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CTSDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_CHECK1, &CTSDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTSDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CTSDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CTSDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON1, &CTSDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTSDlg 消息处理程序

BOOL CTSDlg::OnInitDialog()
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

void CTSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTSDlg::OnPaint()
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
HCURSOR CTSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTSDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);
	GetDlgItemText(IDC_MFCEDITBROWSE1, SrcFileName);
	UpdateData(false);

}

void CTSDlg::Run()
{
	CString strrr;
	int ct = 0;
	UpdateData(true);
	CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);//获取用户名框编辑框ID
	pEdit1->GetWindowText(strrr);
	UpdateData(FALSE);
	ct = atoi(strrr);

	/*
	bool PushFlag = FALSE;  //立即数入栈
	bool Operation = FALSE;  //四则运算
	bool JumpFlag = FALSE;//跳转
	bool CallFlag = FALSE;  //调用
	*/
	for (int i = 1; i <ct+1; i++)
	{
		if (PushFlag == true)
		{
			PushMode(i);
		}
		if (Operation == true)
		{
			OperaMode(i);
		}
		if (JumpFlag == true)
		{
			JumpMode(i);
		}
		if (CallFlag == true)
		{
			CallMode(i);
		}
	}

}

void CTSDlg::PushMode(int Count)
{	
	CString str;
	CString str1;
	CString New1;
	CString New2;
	CString CountNumber;
	int RandNumber=0;
	srand(time(0));
	RandNumber = rand() % 10;
	int Flag = 1;
	bool CanWirte = TRUE;
	CountNumber.Format("%d", Count);

	//单次模式
	if (Count == 1)
	{
		file.Open(SrcFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		file1.Open("Cpoy.asm", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		while (file.ReadString(str))
		{
			if (str.Find("push") != -1)
			{

				for (int g = 0; g < 8; g++)
				{
					if (str.Find(Reg[g]) != -1)  //有该字串
					{
						Flag = 0;
					}
				}

				//没找到则看看后面有没有数字
				if (Flag == 1)
				{

					int Len = str.GetLength();


					//如果有
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							PushMode1Number += str[i];
						}

					}

					if (RandNumber % 2 == 0)
					{
						//拼合新串   模式一
						New1 = PushMode1pro + PushMode1Number + "\n";
						//写入文本
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);
						New2 = PushMode1nex + PushMode1Number + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);


						PushMode1Number = "";
						New1 = "";
						New1.Delete(0, 1);
						PushMode1Number.Delete(0, 1);
					}
					else
					{
						//拼合新串  模式二
						New1 = pushMode2pro+"\n";
						New2 = PushMode2nex + PushMode1Number + "\n";
						file1.WriteString(New1);
						file1.WriteString(New2);

						PushMode1Number = "";
						New1 = "";
						New1.Delete(0, 1);
						PushMode1Number.Delete(0, 1);
					}


					CanWirte = FALSE;
				}
			}



			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);

			}

			CanWirte = TRUE;
			Flag = 1;



	}

	}
	//多次模式
	else
	{
		if (Count == 2)
		{	
			FileS = "";
			FileS.Delete(0, 1);
			FileS = "Cpoy.asm";
			
		}
		file.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		FileS = "";
		FileS.Delete(0, 1);
		FileS = CountNumber + ".asm";
		file1.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		while (file.ReadString(str))
		{
			if (str.Find("push") != -1)
			{

				for (int g = 0; g < 8; g++)
				{
					if (str.Find(Reg[g]) != -1)  //有该字串
					{
						Flag = 0;
					}
				}

				//没找到则看看后面有没有数字
				if (Flag == 1)
				{

					int Len = str.GetLength();


					//如果有
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							PushMode1Number += str[i];
						}

					}

					if (RandNumber % 2 == 0)
					{
						//拼合新串   模式一
						New1 = PushMode1pro + PushMode1Number + "\n";
						//写入文本
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);
						New2 = PushMode1nex + PushMode1Number + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);


						PushMode1Number = "";
						New1 = "";
						New1.Delete(0, 1);
						PushMode1Number.Delete(0, 1);
					}
					else
					{
						//拼合新串  模式二
						New1 = pushMode2pro+ "\n";
						New2 = PushMode2nex + PushMode1Number + "\n";
						file1.WriteString(New1);
						file1.WriteString(New2);

						PushMode1Number = "";
						New1 = "";
						New1.Delete(0, 1);
						PushMode1Number.Delete(0, 1);
					}


					CanWirte = FALSE;
				}
			}



			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);

			}

			CanWirte = TRUE;
			Flag = 1;



		}
	}

	file.Close();
	file1.Close();
	MessageBox("立即数入栈替换完毕");
}

void CTSDlg::OperaMode(int Count)
{
	CString str;
	CString str1;
	CString CountNumber;
	int Flag = 0;
	bool CanWirte = TRUE;
	int CoomNumber = 0;

	CountNumber.Format("%d", Count);

	if (Count == 1)
	{
		file.Open(SrcFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		file1.Open("Cpoy.asm", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		while (file.ReadString(str))
		{

			//模式一
			if (str.Find("add") != -1)
			{
				for (int g = 0; g < 8; g++)
				{
					if (str.Find(Reg[g]) != -1)  //有该字串
					{
						Flag = 1;
					}
				}

				//找到后则看看后面有没有数字
				if (Flag == 1)
				{

					int Len = str.GetLength();



					OperaModeNumber = "";
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}

					}
					//如果有
					if (OperaModeNumber != "")
					{
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;
						CString REG;

						REG = GetRandReg();
						New1 = OperaMode1_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);
						New2 = Operamode1_2 + REG+ "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);
						New3 = Operamode1_3 + OperaModeNumber + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);
						New4 = Operamode1_4 + REG + "," + " eax" + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);
						New5 = Operamode1_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						REG = "";
						REG.Delete(0, 1);



						CanWirte = FALSE;
					}
					//如果没有，则不造写入的字符串
				}
			}
			//模式二
			else if (str.Find("mov") != -1)
			{
				//继续判断有没有eax
				if (str.Find("eax") != -1)
				{
					//继续满足
					int Len = str.GetLength();
					OperaModeNumber = "";
					//找数字
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}
					}
					//有数字
					if (OperaModeNumber != "")
					{
						int Val = 0;
						Val = atoi(OperaModeNumber);
						int rea = 0;
						rea = IscCommNumber(Val);
						int Cao = 0;
						Cao = Val - rea;
						CString Number1;
						CString Number2;
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;

						Number1.Format("%d", rea);
						Number2.Format("%d", Cao);

						New1 = OperaMode2_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);

						New2 = OperaMode2_2 + Number1 + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);

						New3 = OperaMode2_3 + Number2 + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);

						New4 = OperaMode2_4 + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);

						New5 = OperaMode2_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);

						Number1 = "";
						Number1.Delete(0, 1);
						Number2 = "";
						Number1.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						CanWirte = FALSE;
					}

				}

			}
			//模式三
			else if (str.Find("sub") != -1)
			{
				//如果有继续判断
				if (str.Find("eax") != -1)
				{
					int Len = str.GetLength();
					OperaModeNumber = "";
					//找数字
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}
					}

					if (OperaModeNumber != "")
					{
						int Val = 0;
						Val = atoi(OperaModeNumber);
						int rea = 0;
						rea = IscCommNumber(Val);
						int Cao = 0;
						Cao = Val - rea;
						CString Number1;
						CString Number2;
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;
						CString New6;
						CString New7;

						Number1.Format("%d", rea);
						Number2.Format("%d", Cao);
						New1 = OperaMode3_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);

						New2 = OperaMode3_2 + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);

						New3 = OperaMode3_3 + Number1 + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);

						New4 = OperaMode3_4 + Number2 + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);

						New5 = OperaMode3_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);

						New6 = OperaMode3_6 + "\n";
						file1.WriteString(New6);
						New6 = "";
						New6.Delete(0, 1);

						New7 = OperaMode3_7 + "\n";
						file1.WriteString(New7);
						New7 = "";
						New7.Delete(0, 1);

						Number1 = "";
						Number1.Delete(0, 1);
						Number2 = "";
						Number1.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						CanWirte = FALSE;

					}
				}
			}
			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);

			}

			CanWirte = TRUE;
			Flag = 0;
		}

	}
	else
	{
		if (Count == 2)
		{
			FileS = "";
			FileS.Delete(0, 1);
			FileS = "Cpoy.asm";

		}
		file.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		FileS = "";
		FileS.Delete(0, 1);
		FileS = CountNumber + ".asm";
		file1.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);

		while (file.ReadString(str))
		{

			//模式一
			if (str.Find("add") != -1)
			{
				for (int g = 0; g < 8; g++)
				{
					if (str.Find(Reg[g]) != -1)  //有该字串
					{
						Flag = 1;
					}
				}

				//找到后则看看后面有没有数字
				if (Flag == 1)
				{

					int Len = str.GetLength();



					OperaModeNumber = "";
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}

					}
					//如果有
					if (OperaModeNumber != "")
					{
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;
						CString REG;
						REG = GetRandReg();

						New1 = OperaMode1_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);
						New2 = Operamode1_2 + REG + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);
						New3 = Operamode1_3 + OperaModeNumber + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);
						New4 = Operamode1_4 + REG+ "," + " eax" + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);
						New5 = Operamode1_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						REG = "";
						REG.Delete(0, 1);

						CanWirte = FALSE;
					}
					//如果没有，则不造写入的字符串
				}
			}
			//模式二
			else if (str.Find("mov") != -1)
			{
				//继续判断有没有eax
				if (str.Find("eax") != -1)
				{
					//继续满足
					int Len = str.GetLength();
					OperaModeNumber = "";
					//找数字
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}
					}
					//有数字
					if (OperaModeNumber != "")
					{
						int Val = 0;
						Val = atoi(OperaModeNumber);
						int rea = 0;
						rea = IscCommNumber(Val);
						int Cao = 0;
						Cao = Val - rea;
						CString Number1;
						CString Number2;
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;

						Number1.Format("%d", rea);
						Number2.Format("%d", Cao);

						New1 = OperaMode2_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);

						New2 = OperaMode2_2 + Number1 + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);

						New3 = OperaMode2_3 + Number2 + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);

						New4 = OperaMode2_4 + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);

						New5 = OperaMode2_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);

						Number1 = "";
						Number1.Delete(0, 1);
						Number2 = "";
						Number1.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						CanWirte = FALSE;
					}

				}

			}
			//模式三
			else if (str.Find("sub") != -1)
			{
				//如果有继续判断
				if (str.Find("eax") != -1)
				{
					int Len = str.GetLength();
					OperaModeNumber = "";
					//找数字
					for (int i = 0; i < Len; i++)
					{
						//提取数字
						if (str.GetAt(i) == ';')
						{
							break;
						}

						if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
						{
							OperaModeNumber += str[i];
						}
					}

					if (OperaModeNumber != "")
					{
						int Val = 0;
						Val = atoi(OperaModeNumber);
						int rea = 0;
						rea = IscCommNumber(Val);
						int Cao = 0;
						Cao = Val - rea;
						CString Number1;
						CString Number2;
						CString New1;
						CString New2;
						CString New3;
						CString New4;
						CString New5;
						CString New6;
						CString New7;

						Number1.Format("%d", rea);
						Number2.Format("%d", Cao);
						New1 = OperaMode3_1 + "\n";
						file1.WriteString(New1);
						New1 = "";
						New1.Delete(0, 1);

						New2 = OperaMode3_2 + "\n";
						file1.WriteString(New2);
						New2 = "";
						New2.Delete(0, 1);

						New3 = OperaMode3_3 + Number1 + "\n";
						file1.WriteString(New3);
						New3 = "";
						New3.Delete(0, 1);

						New4 = OperaMode3_4 + Number2 + "\n";
						file1.WriteString(New4);
						New4 = "";
						New4.Delete(0, 1);

						New5 = OperaMode3_5 + "\n";
						file1.WriteString(New5);
						New5 = "";
						New5.Delete(0, 1);

						New6 = OperaMode3_6 + "\n";
						file1.WriteString(New6);
						New6 = "";
						New6.Delete(0, 1);

						New7 = OperaMode3_7 + "\n";
						file1.WriteString(New7);
						New7 = "";
						New7.Delete(0, 1);

						Number1 = "";
						Number1.Delete(0, 1);
						Number2 = "";
						Number1.Delete(0, 1);
						OperaModeNumber = "";
						OperaModeNumber.Delete(0, 1);
						CanWirte = FALSE;

					}
				}
			}
			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);

			}

			CanWirte = TRUE;
			Flag = 0;
		}

	}
	file.Close();
	file1.Close();
	MessageBox("四则运算替换完毕");
}

void CTSDlg::JumpMode(int Count)
{
	CString str;
	CString str1;
	CString CountNumber;
	bool CanWirte = TRUE;
	int CoomNumber = 0;

	CountNumber.Format("%d", Count);
	if (Count == 1)
	{
		file.Open(SrcFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		file1.Open("Cpoy.asm", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		while (file.ReadString(str))
		{
			if (str.Find("jmp") != -1)
			{
				//有特定串

				//查数字
				int Len = str.GetLength();

				JumpModeNumber = "";
				for (int i = 0; i < Len; i++)
				{
					//提取数字
					if (str.GetAt(i) == ';')
					{
						break;
					}

					if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
					{
						JumpModeNumber += str[i];
					}
				}
				if (JumpModeNumber != "")
				{
					CString New1;
					CString New2;
					CString New3;
					CString New4;
					CString New5;
					CString New6;


					int Rn1 = 0;
					int Rn2 = 0;
					Rn1 = GetRandNumber(20);
					Rn2 = GetRandNumber(50);
					CString Number1;
					CString Number2;


					Number1.Format("%d", Rn1);
					Number2.Format("%d", Rn2);

					New1 = JumpMode1 + "\n";
					file1.WriteString(New1);
					New1 = "";
					New1.Delete(0, 1);

					New2 = JumpMode2 + Number1 + "\n";
					file1.WriteString(New2);
					New2 = "";
					New2.Delete(0, 1);

					New3 = JumpMode3 + Number2 + "\n";
					file1.WriteString(New3);
					New3 = "";
					New3.Delete(0, 1);

					New4 = JumpMode4 + "\n";
					file1.WriteString(New4);
					New4 = "";
					New4.Delete(0, 1);

					New5 = JumpMode5 + JumpModeNumber + "\n";
					file1.WriteString(New5);
					New5 = "";
					New5.Delete(0, 1);

					New6 = JumpMode6 + JumpModeNumber + "\n";
					file1.WriteString(New6);
					New6 = "";
					New6.Delete(0, 1);

					Number1 = "";
					Number1.Delete(0, 1);
					Number2 = "";
					Number1.Delete(0, 1);
					JumpModeNumber = "";
					JumpModeNumber.Delete(0, 1);
					CanWirte = FALSE;
				}

			}

			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);
			}

			CanWirte = TRUE;

		}

	}
	else
	{
		if (Count == 2)
		{
			FileS = "";
			FileS.Delete(0, 1);
			FileS = "Cpoy.asm";

		}
		file.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		FileS = "";
		FileS.Delete(0, 1);
		FileS = CountNumber + ".asm";
		file1.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);

		while (file.ReadString(str))
		{
			if (str.Find("jmp") != -1)
			{
				//有特定串

				//查数字
				int Len = str.GetLength();

				JumpModeNumber = "";
				for (int i = 0; i < Len; i++)
				{
					//提取数字
					if (str.GetAt(i) == ';')
					{
						break;
					}

					if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
					{
						JumpModeNumber += str[i];
					}
				}
				if (JumpModeNumber != "")
				{
					CString New1;
					CString New2;
					CString New3;
					CString New4;
					CString New5;
					CString New6;


					int Rn1 = 0;
					int Rn2 = 0;
					Rn1 = GetRandNumber(20);
					Rn2 = GetRandNumber(50);
					CString Number1;
					CString Number2;


					Number1.Format("%d", Rn1);
					Number2.Format("%d", Rn2);

					New1 = JumpMode1 + "\n";
					file1.WriteString(New1);
					New1 = "";
					New1.Delete(0, 1);

					New2 = JumpMode2 + Number1 + "\n";
					file1.WriteString(New2);
					New2 = "";
					New2.Delete(0, 1);

					New3 = JumpMode3 + Number2 + "\n";
					file1.WriteString(New3);
					New3 = "";
					New3.Delete(0, 1);

					New4 = JumpMode4 + "\n";
					file1.WriteString(New4);
					New4 = "";
					New4.Delete(0, 1);

					New5 = JumpMode5 + JumpModeNumber + "\n";
					file1.WriteString(New5);
					New5 = "";
					New5.Delete(0, 1);

					New6 = JumpMode6 + JumpModeNumber + "\n";
					file1.WriteString(New6);
					New6 = "";
					New6.Delete(0, 1);

					Number1 = "";
					Number1.Delete(0, 1);
					Number2 = "";
					Number1.Delete(0, 1);
					JumpModeNumber = "";
					JumpModeNumber.Delete(0, 1);
					CanWirte = FALSE;
				}

			}

			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT"," ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);
			}

			CanWirte = TRUE;

		}
	}

	file.Close();
	file1.Close();
	MessageBox("跳转替换完毕");
}

void CTSDlg::CallMode(int Count)
{
	CString str;
	CString str1;
	CString CountNumber;
	bool CanWirte = TRUE;
	int CoomNumber = 0;

	CountNumber.Format("%d", Count);
	if (Count == 1)
	{
		file.Open(SrcFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		file1.Open("Cpoy.asm", CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		while (file.ReadString(str))
		{
			if (str.Find("jmp") != -1)
			{
				int Len = str.GetLength();

				CallModeNumber = "";
				for (int i = 0; i < Len; i++)
				{
					//提取数字
					if (str.GetAt(i) == ';')
					{
						break;
					}

					if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
					{
						CallModeNumber += str[i];
					}
				}

				if (CallModeNumber != "")
				{
					CString New1;
					CString New2;

					New1 = CallMode1 + CallModeNumber + "\n";
					file1.WriteString(New1);
					New1 = "";
					New1.Delete(0, 1);

					New2 = CallMode2 + "\n";
					file1.WriteString(New2);
					New2 = "";
					New2.Delete(0, 1);

					CallModeNumber = "";
					CallModeNumber.Delete(0, 1);
					CanWirte = FALSE;
				}

			}






			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);
			}

			CanWirte = TRUE;
		}
	}
	else
	{
		if (Count == 2)
		{
			FileS = "";
			FileS.Delete(0, 1);
			FileS = "Cpoy.asm";

		}
		file.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
		FileS = "";
		FileS.Delete(0, 1);
		FileS = CountNumber + ".asm";
		file1.Open(FileS, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);


		while (file.ReadString(str))
		{
			if (str.Find("jmp") != -1)
			{
				int Len = str.GetLength();

				CallModeNumber = "";
				for (int i = 0; i < Len; i++)
				{
					//提取数字
					if (str.GetAt(i) == ';')
					{
						break;
					}

					if ((str.GetAt(i) >= '0' && str.GetAt(i) <= '9'))
					{
						CallModeNumber += str[i];
					}
				}

				if (CallModeNumber != "")
				{
					CString New1;
					CString New2;

					New1 = CallMode1 + CallModeNumber + "\n";
					file1.WriteString(New1);
					New1 = "";
					New1.Delete(0, 1);

					New2 = CallMode2 + "\n";
					file1.WriteString(New2);
					New2 = "";
					New2.Delete(0, 1);

					CallModeNumber = "";
					CallModeNumber.Delete(0, 1);
					CanWirte = FALSE;
				}

			}






			if (CanWirte == TRUE)
			{	
				int ShFlag = 0;
				ShFlag = str.Find("SHORT"); // 查找每一行中的"Tom"
				if (ShFlag != -1)
				{
					ShFlag = str.Replace("SHORT", " ");
				}
				str1 = str + "\n";
				file1.WriteString(str1);
			}

			CanWirte = TRUE;
		}


	}
	file.Close();
	file1.Close();
	MessageBox("调回替换完毕");
}
int CTSDlg::IscCommNumber(int nval)
{
	int val[10] = {256,128,64,32,16,8,6,4,2,1};
	for (int i = 0; i <10; i++)
	{
		if (nval % val[i] == 0)
		{
			return val[i];
		}
	}


	return 1;
}

int CTSDlg::GetRandNumber(int nval)
{
	int RandNumber = 0;
	srand(time(0));
	RandNumber = rand() % nval;
	return RandNumber;
}

CString CTSDlg::GetRandReg()
{	
	return Reg2[GetRandNumber(8)];
}


void CTSDlg::OnBnClickedCheck1()
{	
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1))
	{

		// 勾选
		PushFlag = TRUE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用

	}
	else
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用
	}
	 
}


void CTSDlg::OnBnClickedCheck2()
{

	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2))
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = TRUE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用
	}
	else
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用
	}
	
}


void CTSDlg::OnBnClickedCheck3()
{
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK3))
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = TRUE;//跳转
		CallFlag = FALSE;  //调用
	}
	else
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用
	}
	
}


void CTSDlg::OnBnClickedCheck4()
{
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECK4))
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = TRUE;  //调用
	}
	else
	{
		PushFlag = FALSE;  //立即数入栈
		Operation = FALSE;  //四则运算
		JumpFlag = FALSE;//跳转
		CallFlag = FALSE;  //调用
	}
	
}


void CTSDlg::OnBnClickedButton1()
{
	Run();
}
