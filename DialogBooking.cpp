// DialogBooking.cpp: 实现文件
//

#include "stdafx.h"
#include "HITSystem.h"
#include "DialogBooking.h"
#include "afxdialogex.h"


// CDialogBooking 对话框

IMPLEMENT_DYNAMIC(CDialogBooking, CDialogEx)

CDialogBooking::CDialogBooking(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
	//, m_strActivity(_T(""))
	//, m_SelTime(COleDateTime::GetCurrentTime())
	, m_nID(0)
{

}

CDialogBooking::~CDialogBooking()
{
}

void CDialogBooking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_CONTENT, m_strActivity);
	//DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR, m_SelTime);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_nID);
}


BEGIN_MESSAGE_MAP(CDialogBooking, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogBooking::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogBooking 消息处理程序

/////////////////////////////////////////////////////////////
//	确定
void CDialogBooking::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_nID==0)
	{
		AfxMessageBox(_T("请输入有效的学号！"));
		return;
	}
	
	CDialogEx::OnOK();
}
