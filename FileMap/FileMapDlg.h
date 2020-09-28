
// FileMapDlg.h: 头文件
//

#pragma once


// CFileMapDlg 对话框
class CFileMapDlg : public CDialogEx
{
// 构造
public:
	CFileMapDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG1};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox;
	CListCtrl m_list;
	CStringArray   FileHistroy;
	CStringArray   RootName;
	afx_msg void OnBnClickedButton1();
	CString RootFileName;
	void InitMainDialog();  //界面初始化的函数
	void SearchOK(CString Buff); //按下按钮搜索当前盘的函数
	void ChilTapInit(); //文件目录初始化

	
	void ViewCler()
	{
		m_list.DeleteAllItems();
		/*int ncount = m_list.GetHeaderCtrl()->GetItemCount();
		for (size_t i = 0; i < ncount; ++i)
		{
			m_list.DeleteColumn(i);
		}*/
		while (m_list.DeleteColumn(0));
	}
	BOOL  RootFlag = FALSE;  //处于盘符界面的标志
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
};
