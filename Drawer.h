#pragma once
#include "Common.h"

class CDrawer
{
public:
	CDrawer();
	~CDrawer();

public:

	// 绘制背景以及景点
	void Draw(CDC* pDC);

protected:

	// 绘制背景图
	void DrawMap();

protected:

	CDC*			m_pDC;				

	CRect			m_rcBk;				  // 背景边框
	CImage			m_imgBk;			  // 背景图
	CPen			m_penBk;			  // 用于绘制边框的笔
};

