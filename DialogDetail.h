#pragma once

#include "Common.h"

// CDialogDetail 对话框

class CDialogDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDetail)

public:
	CDialogDetail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogDetail();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLbnSelchangeListSpot();
	DECLARE_MESSAGE_MAP()


public:

	// 初始化界面
	void Init();

protected:

	// 绘制景点照片
	void DrawSpotImage(CDC* pDC);

protected:

	// 界面中的控件
	CListBox		m_ListSpot;
	CString			m_strIntro;	
public:
	CString m_strSearch;
	CString m_strResult;
	afx_msg void OnBnClickedButtonSearch();
};
