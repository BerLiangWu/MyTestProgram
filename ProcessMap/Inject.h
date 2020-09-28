#pragma once


// Inject 对话框

class Inject : public CDialogEx
{
	DECLARE_DYNAMIC(Inject)

public:
	Inject(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Inject();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

public:
	HANDLE hWnd=NULL;
	LPVOID pDllBuff;
	DWORD dwID;
	CString  DllPath;
public:
	void InjectObject();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMFCEditBrowseCtrl m_DllName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit m_Name;
};
