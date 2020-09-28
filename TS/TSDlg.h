
// TSDlg.h: 头文件
//

#pragma once


// CTSDlg 对话框
class CTSDlg : public CDialogEx
{
// 构造
public:
	CTSDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeMfceditbrowse1();
	CMFCEditBrowseCtrl m_file;


public:
	//膨胀模式标签
	bool PushFlag = FALSE;  //立即数入栈
	bool Operation = FALSE;  //四则运算
	bool JumpFlag = FALSE;//跳转
	bool CallFlag = FALSE;  //调用

	//膨胀进行次数
	int Count = 0;    //初始默认膨胀次数为0
	CString InFileName;  //输入得ASM文件全路径
	CString OutFileName;  //输出得ASM文件全路径

public:
	//函数实现
	void Run();  //全局同调函数
	void PushMode(int Count); //PushMode膨胀
	void OperaMode(int Count); //四则运算膨胀
	void JumpMode(int Count); //跳跃膨胀
	void CallMode(int Count);//调回膨胀
	int IscCommNumber(int nval); //求最大公约数
	int GetRandNumber(int nval); //获得一个0~9的随机数
	CString GetRandReg();//随机获得一个寄存器名字
	CString Reg[8] = { "eax","ebx","ecx","edx","esp","ebp","esi","edi" };  //Eax不替换 Esp不替换
	CString Reg2[6] = { "ebx","ecx","edx","ebp","esi","edi" };  //随机取寄存器
public:
	//模式配套语句
	
	//PushMode1
	CString PushMode1pro= "sub esp, ";
	CString PushMode1Number;
	CString PushMode1nex= "mov dword ptr[esp], ";

	//PushMode2
	CString pushMode2pro = "push eax";
	CString PushMode2nex = "mov dword ptr[esp], ";
	
	//OperaMode1
	CString OperaModeNumber;

	CString OperaMode1_1 = "push eax";
	CString Operamode1_2 = "mov eax, "; //后接REG
	CString Operamode1_3 = "add eax, ";  //接REG
	CString Operamode1_4 = "mov "; //后接{reg1},+一空字节+eax
	CString Operamode1_5 = "pop eax";

	//OperaMode2
	CString OperaMode2_1 = "push ecx";
	CString OperaMode2_2 = "mov ecx, ";//后接最大公约数
	CString OperaMode2_3 = "mov eax, ";//后接原数字减最大公约数
	CString OperaMode2_4 = "xor eax, ecx";
	CString OperaMode2_5 = "pop ecx";

	//OperaMode3
	CString OperaMode3_1 = "push ecx";
	CString OperaMode3_2 = "push ebx";
	CString OperaMode3_3 = "mov ecx, "; //后接最大公约数
	CString OperaMode3_4 = "mov eax, ";//后接原数字减最大公约数
	CString OperaMode3_5 = "sub eax, ebx";
	CString OperaMode3_6 = "pop ecx";
	CString OperaMode3_7 = "pop ebx";

	//JumpMode
	CString JumpModeNumber;
	CString JumpMode1 = "push eax";
	CString JumpMode2 = "mov eax, ";//后接任意数字
	CString JumpMode3 = "cmp eax, ";//后接任意数字
	CString JumpMode4 = "pop eax";
	CString JumpMode5 = "jne ";//后接原数字
	CString JumpMode6 = "je ";//后接原数字
	 
	//CallMode
	CString CallModeNumber;
	CString CallMode1 = "push ";//后接原数字
	CString CallMode2 = "ret ";


//	CEdit m_count;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	BOOL PushModeBOX;
	BOOL OperModeBox;
	BOOL JumpModeBox;
	BOOL CallModeBox;
	afx_msg void OnBnClickedButton1();
};
