#pragma once
#include <tlhelp32.h>

// CModList 对话框

class CModList : public CDialogEx
{
	DECLARE_DYNAMIC(CModList)

public:
	CModList(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CModList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIALOG1
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	PROCESSENTRY32 Modepe32 = { 0 };
	MODULEENTRY32 me32 = { 0 };
	
public:
	void InitModList();
	BOOL GetProcessModule(DWORD dwPID, DWORD dwModuleID, LPMODULEENTRY32 lpMe32, DWORD cbMe32);
	virtual BOOL OnInitDialog();
	CListCtrl m_Mod;
	bool KillProcess(DWORD dwPid);
};
