// DialogNav.cpp: 实现文件
//

#include "stdafx.h"
#include "HITSystem.h"
#include "DialogNav.h"
#include "afxdialogex.h"
#include "MainDlg.h"

extern NODES			m_Nodes;
extern CMainDlg*		m_pMain;
extern CDrawer			m_Drawer;



// CDialogNav 对话框

IMPLEMENT_DYNAMIC(CDialogNav, CDialogEx)

CDialogNav::CDialogNav(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NAV, pParent)
	, m_strResult(_T(""))
	, m_strStart(_T(""))
	, m_strEnd(_T(""))
	, m_strMulti(_T(""))
{
}

CDialogNav::~CDialogNav()
{
}

void CDialogNav::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_START, m_strStart);
	DDX_Text(pDX, IDC_EDIT_END, m_strEnd);
	DDX_Control(pDX, IDC_LIST_SPOT, m_ListSpot);
	DDX_Control(pDX, IDC_EDIT_START, m_EditStart);
	DDX_Control(pDX, IDC_EDIT_END, m_EditEnd);
	DDX_Text(pDX, IDC_EDIT_MULTI, m_strMulti);
}


BEGIN_MESSAGE_MAP(CDialogNav, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDialogNav::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_MULTI, &CDialogNav::OnBnClickedButtonMulti)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHALL, &CDialogNav::OnBnClickedButtonSearchall)
END_MESSAGE_MAP()


// CDialogNav 消息处理程序


BOOL CDialogNav::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

FILE* fp;
char na[100];
char str1[100], str3[100];
int N = 10, M = 10;
int a[100][100];
int visited[100];

MGraph g;
ALGraph* G;

//将文本文件打开并输出文件中的内容
void ReadData1(MGraph& g)
{
	M = N;
	FILE* fp;
	int i = 0, j;
	if ((fp = fopen(FILE_PATH, "r")) == NULL)
	{
		printf("error open!");
		// exit(0);
	}
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			fscanf(fp, "%d", &g.edges[i][j]);
		}
	}
	fclose(fp);
}

//将邻接矩阵改为邻接表
void MatToList(MGraph g, ALGraph*& G)
{
	int i, j;
	ArcNode* p;
	G = (ALGraph*)malloc(sizeof(ALGraph));
	for (i = 0; i < g.n; i++)
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < g.n; i++)
		for (j = g.n - 1; j >= 0; j--)
		{
			if (g.edges[i][j] != MAXINF)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	G->n = g.n;
	G->e = g.e;
}

//////////////////////////////////////////////////////////
//	查找两顶点间的最短路径
void CDialogNav::FindMinPath(MGraph& g, int u, int v)
{
	int A[100][100], path[100][100];
	int i, j, k;
	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < MAXINF)
				path[i][j] = i;
			else
				path[i][j] = -1;
		}
	}
	for (k = 0; k < g.n; k++)
	{
		for (i = 0; i < g.n; i++)
		{
			for (j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[k][j] + A[i][k])
				{
					A[i][j] = A[k][j] + A[i][k];
					path[i][j] = path[k][j];
				}
			}
		}
	}
	Dispath(g, A, path, u ,v);
}

////////////////////////////////////////////////////////////
//	查找两顶点间的所有路径
void CDialogNav::FindaPath(MGraph& g, ALGraph* G, int u, int v, int path[], int d)
{
	int w, i;
	ArcNode* p;
	visited[u] = 1;
	d++;
	path[d] = u;
	if (u == v && d >= 1)
	{
		//TRACE(" ");
		for (i = 0; i < d; i++)
		{
			//TRACE("%s->", g.vex[path[i]].strName);
			m_strResult.AppendFormat("%s->", g.vex[path[i]].strName);
		}
			
		m_strResult.AppendFormat("%s\r\n", g.vex[path[d]].strName);
		//TRACE("%s", g.vex[path[d]].strName);
		//TRACE("\n");
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL)
	{
		w = p->adjvex;
		if (visited[w] == 0)
			FindaPath(g, G, w, v, path, d);
		p = p->nextarc;
	}
	visited[u] = 0;
}


///////////////////////////////////////////////////////////
//	输出两个顶点间的最短路径
void CDialogNav::Dispath(MGraph& g, int A[][100], int path[][100], int u, int v)
{
	int i, j, k, s;

	int apath[100], d;
	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != MAXINF && i != j && u == i && v == j)
			{
				m_strResult.Format("\r\n从 %s 到 %s 的最短路径为:\r\n\r\n======================================\r\n\r\n", g.vex[i].strName, g.vex[j].strName);

				k = path[i][j];
				d = 0;
				apath[d] = j;
				while (k != -1 && k != i)
				{
					d++;
					apath[d] = k;
					k = path[i][k];
				}
				d++;
				apath[d] = i;
				TRACE("\t%s\r\n", g.vex[apath[d]].strName);
				m_strResult.AppendFormat("\t%s\r\n", g.vex[apath[d]].strName);

				for (s = d - 1; s >= 0; s--)
				{
					TRACE("->%s", g.vex[apath[s]].strName);
					m_strResult.AppendFormat("\t-> %s\r\n", g.vex[apath[s]].strName);
				}

				m_strResult.AppendFormat("\r\n======================================\r\n总长度为：%d\r\n", A[i][j]);

				break;
			}
		}
	}
}

////////////////////////////////////////////
// 初始化界面
void CDialogNav::Init()
{
	int i = 0;

	// 为景点列表添加所有的景点
	for (i = 0; i < (int)m_Nodes.size(); i++)
	{
		m_ListSpot.AddString(m_Nodes[i].strName);
	}

	m_ListSpot.SetCurSel(0);

	g.n = 10;
	g.e = 18;
	ReadData1(g);
	for (i = 0; i < (int)m_Nodes.size(); i++)
	{
		g.vex[i].nIndex = m_Nodes[i].nIndex;
		strcpy(g.vex[i].strName, m_Nodes[i].strName);
		strcpy(g.vex[i].strDescription, m_Nodes[i].strDescription);
	}
	MatToList(g, G);
}

////////////////////////////////////////////////
//	多点最短路径
void CDialogNav::shortest(int dist[][100], int n, int v0, int v, vector<int>& path, int & dis) 
{
	int* ds = new int[n];
	int* p = new int[n];
	int* s = new int[n];
	int MIN, i, j, u, w;
	for (i = 0; i < n; i++)
	{
		ds[i] = dist[v0][i];//距离初始化
		s[i] = 0;        //S[ ]置空
		if (dist[v0][i] < MAXINF)//路径初始化
			p[i] = v0;
		else
			p[i] = -1;
	}
	s[v0] = 1; p[v0] = 0;//源点编号 V放入S中
	for (i = 0; i < n; i++)//循环直到所有顶点的最短路径都求出
	{
		MIN = MAXINF;
		u = -1;
		for (j = 0; j < n; j++)//选取不在S中且具有最小距离的顶点U
			if (s[j] == 0 && ds[j] < MIN)
			{
				u = j;
				MIN = ds[j];
			}
		if (u != -1)//找到最小距离的顶点U
		{
			s[u] = 1;//将顶点U加入S中
			for (j = 0; j < n; j++)//修改不在S中的顶点的距离
				if (s[j] == 0)
					if (dist[u][j] < MAXINF &&ds[u] + dist[u][j] < ds[j])
					{
						ds[j] = ds[u] + dist[u][j];
						p[j] = u;
					}
		}
	}

	w = v;

	//一直加溯到初始顶点
	while (w != v0)
	{
		path.push_back(w + 1);
		w = p[w];
	}
	path.push_back(w + 1);

	dis += ds[v];

	delete s;
	delete p;
	delete ds;
}

////////////////////////////////////////////////////////
//	路径导航
void CDialogNav::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);

	// 根据输入的名字，查找起始序号
	int nStart = -1, nEnd = -1;
	BOOL bFind = FALSE;

	// 从数据结构中搜索对应的起点和终点
	for (unsigned int i = 0; i < m_Nodes.size(); i++)
	{
		if (strcmp(m_Nodes[i].strName, m_strStart.GetString()) == 0)
		{
			nStart = i;
		}
		else if (strcmp(m_Nodes[i].strName, m_strEnd.GetString()) == 0)
		{
			nEnd = i;
		}

		if (nStart >= 0 && nEnd >= 0)
		{
			bFind = TRUE;
			break;
		}
	}

	if (bFind)
	{
		for (int i = 0; i < G->n; i++)
			visited[i] = 0;

		FindMinPath(g, nStart, nEnd);

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("请输入正确的景点名称！");
	}
}

////////////////////////////////////////////
//	查询两点之间所有路径
void CDialogNav::OnBnClickedButtonSearchall()
{
	UpdateData(TRUE);

	// 根据输入的名字，查找起始序号
	int nStart = -1, nEnd = -1;
	BOOL bFind = FALSE;

	// 从数据结构中搜索对应的起点和终点
	for (unsigned int i = 0; i < m_Nodes.size(); i++)
	{
		if (strcmp(m_Nodes[i].strName, m_strStart.GetString()) == 0)
		{
			nStart = i;
		}
		else if (strcmp(m_Nodes[i].strName, m_strEnd.GetString()) == 0)
		{
			nEnd = i;
		}

		if (nStart >= 0 && nEnd >= 0)
		{
			bFind = TRUE;
			break;
		}
	}

	if (bFind)
	{
		for (int i = 0; i < G->n; i++)
			visited[i] = 0;

		int path[100];
		m_strResult.Format("\r\n从 %s 到 %s 的所有路径为:\r\n\r\n======================================\r\n\r\n", g.vex[nStart].strName, g.vex[nEnd].strName);

		FindaPath(g, G, nStart, nEnd, path, -1);

		m_strResult.AppendFormat("\r\n======================================\r\n");

		UpdateData(FALSE);
	}
	else
	{
		AfxMessageBox("请输入正确的景点名称！");
	}
}


////////////////////////////////////////////
//	多点查询
void CDialogNav::OnBnClickedButtonMulti()
{
	// 首先取出所有的路径
	UpdateData(TRUE);

	vector<int> Spots;
	int nPos = m_strMulti.Find("\r\n");
	int nLastPos = 0;
	while (nPos >= 0)
	{
		CString strSpot = m_strMulti.Mid(nLastPos, nPos - nLastPos);

		// 查找序号
		for (unsigned int i = 0; i < m_Nodes.size(); i++)
		{
			if (strcmp(m_Nodes[i].strName, strSpot.GetString()) == 0)
			{
				Spots.push_back(i);
				break;
			}
		}

		nLastPos = nPos + 2;
		nPos = m_strMulti.Find("\r\n", nPos + 1);
	}

	if (Spots.size() < 2)
	{
		AfxMessageBox("请至少输入两个景点！");
		return;
	}
	
	// 求最短路径
	vector<int> path;
	int nDis = 0;
	shortest(g.edges, g.n, Spots[0], Spots[1], path, nDis);

	m_strResult = "\r\n最优路线为：\r\n\r\n======================================\r\n\r\n";
	m_strResult.AppendFormat("\t%s\r\n", m_Nodes[path[path.size() - 1] - 1].strName);
	for (size_t j = path.size() - 2; j > 0; j--)
	{
		m_strResult.AppendFormat("\t-> %s\r\n", m_Nodes[path[j] - 1].strName);
	}

	if (Spots.size() >= 2)
	{
		for (int i = 2; i < (int)Spots.size(); i++)
		{
			m_strResult.AppendFormat("\t-> %s\r\n", m_Nodes[path[0] - 1].strName);

			path.clear();

			shortest(g.edges, g.n, Spots[i - 1], Spots[i], path, nDis);

			for (size_t j = path.size() - 2; j > 0; j--)
			{
				m_strResult.AppendFormat("\t-> %s\r\n", m_Nodes[path[j] - 1].strName);
			}
		}
	}

	m_strResult.AppendFormat("\t-> %s\r\n", m_Nodes[Spots[Spots.size()-1]].strName);
	m_strResult.AppendFormat("\r\n======================================\r\n总长度为：%d\r\n", nDis);

	UpdateData(FALSE);
}