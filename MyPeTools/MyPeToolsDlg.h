
// MyPeToolsDlg.h: 头文件
//

#pragma once

#include "CFileInfo.h"
// CMyPeToolsDlg 对话框
class CMyPeToolsDlg : public CDialogEx
{
// 构造
public:
	CMyPeToolsDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CFileInfo m_PeFileInfo;
	void ShowFileHeaderInfo();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPETOOLS_DIALOG };
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
	afx_msg void OnBnClickedAnalysis();
	CMFCEditBrowseCtrl m_File;
};
