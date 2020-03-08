#pragma once


// CDialogBooking 对话框

class CDialogBooking : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBooking)

public:
	CDialogBooking(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogBooking();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:

	//CString				m_strActivity;
	//COleDateTime		m_SelTime;
	
	int m_nID;
};
