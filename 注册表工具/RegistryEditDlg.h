
// RegistryEditDlg.h: 头文件
//

#pragma once


// CRegistryEditDlg 对话框
class CRegistryEditDlg : public CDialogEx
{
// 构造
public:
	CRegistryEditDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTRYEDIT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CTreeCtrl m_Ctree;
	CListCtrl m_CList;
	CString  GetDataByName;
	BOOL   IsOnOpen=FALSE;
	HTREEITEM m_Root;
	HTREEITEM hRoot ;
	HTREEITEM hUser ;
	HTREEITEM hMachine;
	HTREEITEM hUserS  ;
	HTREEITEM hConfit ;
	CImageList	m_ImageList_tree;
	CImageList	m_ImageList;
	

public:
	
	void InitCTreeView();
	void InitCListView();
	afx_msg void OnDRC(NMHDR* pNMHDR, LRESULT* pResult);
};
