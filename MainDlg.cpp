
// MainDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "HITSystem.h"
#include "MainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

NODES			m_Nodes;
CMainDlg*		m_pMain = NULL;
CDrawer			m_Drawer;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 对话框



CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HBUTSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_StaticTitle);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RADIO_DETAIL, &CMainDlg::OnBnClickedRadioDetail)
	ON_BN_CLICKED(IDC_RADIO_NAV, &CMainDlg::OnBnClickedRadioNav)
	ON_BN_CLICKED(IDC_RADIO_TEACHER, &CMainDlg::OnBnClickedRadioClassroom)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMainDlg 消息处理程序

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 初始化子窗体
	InitSubWindow();

	// 加载数据
	if (!LoadData())
	{
		OnCancel();
	}

	m_pMain = this;

	m_DialogDetail.Init();

	m_DialogNav.Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	m_Drawer.Draw(&dc);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////
// 初始化子窗体
void CMainDlg::InitSubWindow()
{
	m_DialogDetail.Create(IDD_DIALOG_DETAIL, this);
	m_DialogNav.Create(IDD_DIALOG_NAV, this);
	m_DialogClass.Create(IDD_DIALOG_TEACHER, this);

	CRect rc;
	GetClientRect(rc);

	rc.top += 165;
	rc.bottom -= 24;
	rc.left += 580;
	rc.right -= 24;

	m_DialogDetail.MoveWindow(rc);
	m_DialogNav.MoveWindow(rc);
	m_DialogClass.MoveWindow(rc);

	m_Pages[WND_DETAIL] = &m_DialogDetail;
	m_Pages[WND_NAV] = &m_DialogNav;
	m_Pages[WND_CLASSROOM] = &m_DialogClass;

	SwitchSubWindow(WND_DETAIL);

	((CButton*)GetDlgItem(IDC_RADIO_DETAIL))->SetCheck(TRUE);
}

////////////////////////////////////////////////////
// 切换子界面
void CMainDlg::SwitchSubWindow(const WND_TYPE nType)
{
	m_Pages[nType]->ShowWindow(SW_SHOW);

	for (int i = 0; i < WND_COUNT; i++)
	{
		if (i != nType)
		{
			m_Pages[i]->ShowWindow(SW_HIDE);
		}
	}
}

////////////////////////////////////////////////////
//	景点介绍
void CMainDlg::OnBnClickedRadioDetail()
{
	SwitchSubWindow(WND_DETAIL);

	m_StaticTitle.SetWindowText("景点介绍");
}

////////////////////////////////////////////////////
//	景点导航
void CMainDlg::OnBnClickedRadioNav()
{
	SwitchSubWindow(WND_NAV);

	m_StaticTitle.SetWindowText("景点导航");
}

///////////////////////////////////////////////////
//	教室预约
void CMainDlg::OnBnClickedRadioClassroom()
{
	SwitchSubWindow(WND_CLASSROOM);

	m_StaticTitle.SetWindowText("教室预约");
}

/////////////////////////////////////////////////////
//	鼠标移动时显示当前位置（仅用于测试使用）
void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// For Debug

	//CString strText;
	//strText.Format("(%d,%d)", point.x, point.y);	
	// this->SetWindowText(strText);

	CDialogEx::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////
// 加载数据文件
bool CMainDlg::LoadData()
{
	// 打开文件准备读取
	ifstream in(FILE_SPOT, ios::binary | ios::in);
	if (!in.is_open())
	{
		AfxMessageBox(_T("加载数据文件失败，程序无法启动！"));
		in.close();
		return false;
	}

	m_Nodes.clear();

	// 加载景点数量
	int nCount = 0;
	in >> nCount;

	for (int i = 0; i < nCount; i++)
	{
		NODE newNode;

		// 读取景点信息
		in >> newNode.nIndex;
		in >> newNode.strName;
		
		//TRACE(_T("Node:%d - "), newNode.nIndex);
		
		in >> newNode.strDescription;

		m_Nodes.push_back(newNode);

		//TRACE(_T("\n"));
	}

	in.close();

	return true;
}
