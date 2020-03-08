#pragma once
#include "Common.h"

class CDrawer
{
public:
	CDrawer();
	~CDrawer();

public:

	// ���Ʊ����Լ�����
	void Draw(CDC* pDC);

protected:

	// ���Ʊ���ͼ
	void DrawMap();

protected:

	CDC*			m_pDC;				

	CRect			m_rcBk;				  // �����߿�
	CImage			m_imgBk;			  // ����ͼ
	CPen			m_penBk;			  // ���ڻ��Ʊ߿�ı�
};

