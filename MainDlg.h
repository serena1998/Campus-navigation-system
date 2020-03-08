
// MainDlg.h: 头文件
//

#pragma once

#include "Drawer.h"
#include "DialogDetail.h"
#include "DialogNav.h"
#include "DialogClassroom.h"
#include "Common.h"

// CMainDlg 对话框
class CMainDlg : public CDialogEx
{
// 构造
public:
	CMainDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HBUTSYSTEM_DIALOG };
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
	afx_msg void OnBnClickedRadioDetail();
	afx_msg void OnBnClickedRadioNav();
	afx_msg void OnBnClickedRadioClassroom();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:

	// 初始化子窗体
	void InitSubWindow();

	// 切换子窗体
	void SwitchSubWindow(const WND_TYPE nType);

	// 加载数据文件
	bool LoadData();

protected:

	CDialogDetail		m_DialogDetail;						
	CDialogNav			m_DialogNav;
	CDialogClassroom	m_DialogClass;						// 教室查询对话框

	CStatic				m_StaticTitle;

	CWnd*				m_Pages[WND_COUNT];					// 各个子窗体
	
};
