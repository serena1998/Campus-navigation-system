#pragma once
#include "Common.h"

// CDialogNav 对话框

typedef struct
{
	int edges[100][100];
	int n, e;
	NODE vex[100];
} MGraph;

typedef struct ANode
{
	int adjvex;
	struct ANode* nextarc;
} ArcNode;
typedef struct Vnode
{
	ArcNode* firstarc;
} VNode;
typedef VNode AdjList[100];
typedef struct
{
	AdjList adjlist;
	int n, e;
} ALGraph;

class CDialogNav : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogNav)

public:
	CDialogNav(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogNav();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAV };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonMulti();
	afx_msg void OnBnClickedButtonSearchall();

	DECLARE_MESSAGE_MAP()

public:

	// 初始化界面
	void Init();

protected:

	//	最短路径算法
	void shortest(int dist[][100], int n, int v0, int v, vector<int>& path, int & dis);

	//	输出两个顶点间的最短路径
	void Dispath(MGraph& g, int A[][100], int path[][100], int u, int v);

	//	查找两顶点间的最短路径
	void FindMinPath(MGraph& g, int u, int v);

	//查找两顶点间的所有路径
	void FindaPath(MGraph& g, ALGraph* G, int u, int v, int path[], int d);

protected:

	// 各个空间
	CString			m_strResult;
	CString			m_strStart;
	CString			m_strEnd;
	CString			m_strMulti;
	CListBox		m_ListSpot;
	CEdit			m_EditStart;
	CEdit			m_EditEnd;
	
};
