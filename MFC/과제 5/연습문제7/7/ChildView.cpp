
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "7.h"
#include "ChildView.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(&rect); // 클라이언트 영역의 크기를 rect에 저장합니다. 

	// 수직선을 그립니다.
	dc.MoveTo(rect.Width() / 2, 0);
	dc.LineTo(rect.Width() / 2, rect.Height());
	// 수평선을 그립니다.
	dc.MoveTo(0, rect.Height() / 2);
	dc.LineTo(rect.Width(), rect.Height() / 2);

	double y;

	for (int x = -rect.Width() / 2; x < rect.Width() / 2; x ++)
	{
		y = sin(x * 3.14 / 180);
		dc.SetPixelV(x + rect.Width() / 2, (int)(y * -100) + rect.Height() / 2, RGB(255, 0, 0));
	}

	for (int x = -rect.Width() / 2; x < rect.Width() / 2; x++)
	{
		y = cos(x * 3.14 / 180);
		dc.SetPixelV(x + rect.Width() / 2, (int)(y * -100) + rect.Height() / 2, RGB(0, 0, 255));
	}

	for (int x = -rect.Width() / 2; x < rect.Width() / 2; x++)
	{
		y = tan(x * 3.14 / 180);
		dc.SetPixelV(x + rect.Width() / 2, (int)(y * -100) + rect.Height() / 2, RGB(0, 0, 0));
	}

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_CENTER);

	int i = 0, k = 0;
	CString str[2];

	while (rect.Width() > rect.Width() / 2 + i)
	{
		str[0].Format(_T("%d"), i);
		dc.TextOutW(rect.Width() / 2 + i, rect.Height() / 2, str[0]);
		i += 90;

		str[1].Format(_T("%d"), k);
		dc.TextOutW(rect.Width() / 2 + k, rect.Height() / 2, str[1]);
		k -= 90;
	}
}

