// DialogTeacher.cpp: 实现文件
//

#include "stdafx.h"
#include "HITSystem.h"
#include "DialogClassroom.h"
#include "afxdialogex.h"
#include "MainDlg.h"
#include "DialogBooking.h"

// CDialogClassroom 对话框


IMPLEMENT_DYNAMIC(CDialogClassroom, CDialogEx)

CDialogClassroom::CDialogClassroom(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEACHER, pParent)
	, m_strID(_T(""))
{

}

CDialogClassroom::~CDialogClassroom()
{
}

void CDialogClassroom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CLASSROOM, m_ComboClass);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_CBString(pDX, IDC_COMBO_CLASSROOM, m_strID);
}


BEGIN_MESSAGE_MAP(CDialogClassroom, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDialogClassroom::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_BOOK, &CDialogClassroom::OnBnClickedButtonBook)
END_MESSAGE_MAP()


// CDialogClassroom 消息处理程序


BOOL CDialogClassroom::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化List
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("教室编号"), LVCFMT_LEFT, 90);
	m_List.InsertColumn(1, _T("活动名称"), LVCFMT_LEFT, 190);
	m_List.InsertColumn(2, _T("举办时间"), LVCFMT_LEFT, 100);

	// 加载所有的活动信息
	LoadAllActs();

	// 初始化ComboBox
	for (int i = 0; i < (int)m_Acts.size(); i++)
	{
		// 剔除重复的
		bool bDup = false;
		for (int j = 0; j < i; j++)
		{
			if (strcmp(m_Acts[i].strID, m_Acts[j].strID) == 0)
			{
				bDup = true;
				break;
			}
		}

		if (!bDup)
		{
			m_ComboClass.AddString(m_Acts[i].strID);
		}		
	}

	m_ComboClass.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//////////////////////////////////////////////////
//	搜索
void CDialogClassroom::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	
	// 首先取消所有选中
	m_List.SetItemState(-1, 0, LVIS_SELECTED);

	// 高亮显示当前行
	for (int i = 0; i < m_List.GetItemCount(); i++)
	{
		CString strID = m_List.GetItemText(i, 0);

		if (strID == m_strID)
		{
			m_List.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);			
		}
	}

	m_List.SetFocus();
}


///////////////////////////////////////////////////////
//	预约
void CDialogClassroom::OnBnClickedButtonBook()
{
	// 获取当前选择的行数以及内容
	int nSelRow = m_List.GetSelectionMark();

	// 如果没有选中任何行，则不作任何操作
	if (nSelRow < 0)
	{
		AfxMessageBox(_T("请先选中一行!"));
		return;
	}
	   
	CDialogBooking dlgBooking;

	if (dlgBooking.DoModal() == IDOK)
	{
		// 保存时间和活动名称
		m_Acts[nSelRow].BookStudents.push_back(dlgBooking.m_nID);

		//m_List.SetItemText(nSelRow, 1, dlgBooking.m_strActivity);
		//m_List.SetItemText(nSelRow, 2, dlgBooking.m_SelTime.Format("%Y.%m.%d"));

		//strcpy(m_Acts[nSelRow].strContent, dlgBooking.m_strActivity.GetString());
		//strcpy(m_Acts[nSelRow].strDate, dlgBooking.m_SelTime.Format("%Y.%m.%d").GetString());

		CString strTip;
		strTip.Format(_T("教室 %s 活动预约完毕！"), m_Acts[nSelRow].strID);

		// 保存到文件中
		SaveAllBooking();

		AfxMessageBox(strTip, MB_ICONINFORMATION);
	}
}

///////////////////////////////////////////////////////
// 加载所有的教室信息
void CDialogClassroom::LoadAllActs()
{
	// 打开文件准备读取
	ifstream in(FILE_ACTIVITY, ios::binary | ios::in);
	if (!in.is_open())
	{
		return;
	}

	m_Acts.clear();
	m_List.DeleteAllItems();

	// 首先读取总的数量
	int nCount = 0;
	in >> nCount;

	// 读取，并且将所有的内容填充到List控件中
	for (int i = 0; i < nCount; i++)
	{
		ACTIVITY newRoom;

		// 读取活动信息
		in >> newRoom.strID;
		in >> newRoom.strContent;
		in >> newRoom.strDate;

		//// 读取预约人数
		//int nStd = 0;
		//in >> nStd;
		//for (int j = 0; j < nStd; j++)
		//{
		//	int nId;
		//	in >> nId;
		//	newRoom.BookStudents.push_back(nId);
		//}

		m_Acts.push_back(newRoom);

		m_List.InsertItem(i, newRoom.strID);
		m_List.SetItemText(i, 1, newRoom.strContent);
		m_List.SetItemText(i, 2, newRoom.strDate);
	}

	in.close();
}

///////////////////////////////////////////////////////
// 保存所有的预约
void CDialogClassroom::SaveAllBooking()
{
	// 打开文件准备写入
	ofstream out(FILE_BOOKING, ios::binary | ios::out | ios::trunc);
	if (!out.is_open())
	{
		return;
	}

	// 表头
	out << setw(10) << setiosflags(ios::right) << "教室编号";
	out << setw(25) << setiosflags(ios::left) << "活动内容";
	out << setw(15) << setiosflags(ios::left) << "活动时间";
	out << "\t\t预约学号";
	out << endl;

	// 表内容
	// 然后循环写入所有信息
	for (unsigned int i = 0; i < m_Acts.size(); i++)
	{
		out << setw(10) << setiosflags(ios::right) << m_Acts[i].strID;
		out << setw(25) << setiosflags(ios::left) << m_Acts[i].strContent;
		out << setw(15) << setiosflags(ios::left) << m_Acts[i].strDate << "\t\t";

		// 写入预约同学学号
		for (unsigned int j = 0; j < m_Acts[i].BookStudents.size(); j++)
		{
			out << m_Acts[i].BookStudents[j] << " ";
		}

		out << endl;
	}

}
