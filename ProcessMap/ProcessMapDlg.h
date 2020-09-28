
// ProcessMapDlg.h: 头文件
//

#pragma once
#include "CModList.h"
#include "Inject.h"
#include <stack>
// CProcessMapDlg 对话框
class CProcessMapDlg : public CDialogEx
{
// 构造
public:
	CProcessMapDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSMAP_DIALOG };
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
	CModList ClistMod;
	Inject   CInject;
public:
	

	
public:
	void InitList();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	bool KillProcess(DWORD dwPid);
	afx_msg void OnChek();
	CListCtrl m_PROList;
	afx_msg void Kill();
	afx_msg void OnInjectThread();
};

struct UesDll
{
	CString DllName;
	HANDLE LoadProcess;
	DWORD  LoadProcessId;
	LPVOID DllBuff;
};
