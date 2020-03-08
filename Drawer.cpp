#include "stdafx.h"
#include "Drawer.h"

extern NODES			m_Nodes;

CDrawer::CDrawer()
{
	m_penBk.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	m_imgBk.Load(_T("Data\\main.png"));
	m_rcBk.SetRect(24, 32, 27 + m_imgBk.GetWidth(), 35 + m_imgBk.GetHeight());
}


CDrawer::~CDrawer()
{
}

/////////////////////////////////////////////////
// ���Ʊ����Լ�����
void CDrawer::Draw(CDC* pDC)
{
	m_pDC = pDC;

	// ����У԰��ͼ
	DrawMap();
}

//////////////////////////////////////////////////
// ���Ʊ���ͼ
void CDrawer::DrawMap()
{
	CPen* pOldPen = m_pDC->SelectObject(&m_penBk);
	m_pDC->Rectangle(m_rcBk);

	m_imgBk.Draw(m_pDC->m_hDC, ORI_X + 2, ORI_Y + 2);

	m_pDC->SelectObject(pOldPen);
}
