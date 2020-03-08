#pragma once

// CDialogClassroom 对话框

#include "Common.h"

class CDialogClassroom : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogClassroom)

public:
	CDialogClassroom(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogClassroom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_CLASSROOM};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedButtonSearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBook();
	DECLARE_MESSAGE_MAP()

protected:

	// 加载所有的活动信息
	void LoadAllActs();
	// 保存所有的预约信息
	void SaveAllBooking();

public:
	
	CEdit			m_EditResult;
	CComboBox		m_ComboClass;
	CListCtrl		m_List;
	
	ACTIVITIES		m_Acts;					// 活动信息
	CString			m_strID;
};
