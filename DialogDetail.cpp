// DialogDetail.cpp: 实现文件
//

#include "stdafx.h"
#include "HITSystem.h"
#include "DialogDetail.h"
#include "afxdialogex.h"
#include "MainDlg.h"

extern NODES			m_Nodes;
extern CMainDlg*		m_pMain;

// CDialogDetail 对话框

IMPLEMENT_DYNAMIC(CDialogDetail, CDialogEx)

CDialogDetail::CDialogDetail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
	, m_strIntro(_T(""))
	, m_strSearch(_T(""))
	, m_strResult(_T(""))
{

}

CDialogDetail::~CDialogDetail()
{
}

void CDialogDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SPOT, m_ListSpot);
	DDX_Text(pDX, IDC_EDIT_INTRO, m_strIntro);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}


BEGIN_MESSAGE_MAP(CDialogDetail, CDialogEx)
	ON_WM_PAINT()
	ON_LBN_SELCHANGE(IDC_LIST_SPOT, &CDialogDetail::OnLbnSelchangeListSpot)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDialogDetail::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CDialogDetail 消息处理程序


void CDialogDetail::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	DrawSpotImage(&dc);
}

BOOL CDialogDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_strIntro = "景点简介";
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


///////////////////////////////////////
// 初始化界面
void CDialogDetail::Init()
{
	// 为景点列表添加所有的景点
	for (unsigned int i = 0; i < m_Nodes.size(); i++)
	{
		m_ListSpot.AddString(m_Nodes[i].strName);
	}

	m_ListSpot.SetCurSel(0);
	OnLbnSelchangeListSpot();
}

////////////////////////////////////////////////////////
// 绘制景点照片
void CDialogDetail::DrawSpotImage(CDC* pDC)
{
	CString strImagePath;
	strImagePath.Format("Data\\%d.png", m_ListSpot.GetCurSel());

	CImage im;
	if (im.Load(strImagePath) == S_OK)
	{
		im.Draw(pDC->m_hDC, 275, 40);
	}
}

////////////////////////////////////////////////////////
//	列表中选项更改时，在界面中显示对应标记
void CDialogDetail::OnLbnSelchangeListSpot()
{
	int nSel = m_ListSpot.GetCurSel();

	m_strIntro = m_Nodes[nSel].strDescription;

	UpdateData(FALSE);

	m_pMain->Invalidate(TRUE);
}

////////////////////////////////////////////////////////
//	搜索结果
void CDialogDetail::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	if (m_strSearch.IsEmpty())
	{
		AfxMessageBox(_T("请输入有效的查询条件！"));
		return;
	}

	// 模糊查询
	m_strResult.Empty();
	for (int i = 0; i < (int)m_Nodes.size(); i++)
	{
		if (CString(m_Nodes[i].strName).Find(m_strSearch.GetString())>=0)
		{
			m_strResult += m_Nodes[i].strName;
			m_strResult += "\r\n";
		}
	}

	UpdateData(FALSE);
}
