
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication9.h"
#include "ChildView.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_time = 0;
	m_hour = 0;
	m_min = 0;
	m_sec = 0;
	m_flag = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTON_S, &CChildView::OnButtonS)
	ON_COMMAND(ID_BUTTON_M, &CChildView::OnButtonM)
	ON_COMMAND(ID_BUTTON_H, &CChildView::OnButtonH)
	ON_COMMAND(ID_BUTTON_DIGITS, &CChildView::OnButtonDigits)
	ON_COMMAND(ID_BUTTON_ANALOG, &CChildView::OnButtonAnalog)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);

	dc.TextOutW(0, 0, _T("16013093 박상우"));

	CFont f;
	f.CreatePointFont(1000, _T("Malgun Gothic"));
	dc.SelectObject(f);

	m_sec = m_time % 60;
	m_min = m_time / 60 % 60;
	m_hour = m_time / 60 / 60 % 60;

	double x;
	double y;

	if (m_flag == 0)
	{
		CString str;
		str.Format(_T("%02d : %02d : %02d"), m_hour, m_min, m_sec);
		dc.TextOutW(20, 20, str);
	}

	if (m_flag == 1)
	{
		dc.Ellipse(0, 0, 600, 600);
		CFont fd;
		fd.CreatePointFont(100, _T("Malgun Gothic"));
		dc.SelectObject(fd);

		for (int i = 1; i < 13; i++)
		{
			x = cos(-3.14 / 2 + (3.14 / 180 * 30 * i)) * 270;
			y = sin(-3.14 / 2 + (3.14 / 180 * 30 * i)) * 270;
			CString str;
			str.Format(_T("%d"), i);
			dc.SetTextAlign(TA_CENTER | TA_BASELINE);
			dc.TextOutW(300 + (int)x, 300 + (int)y, str);
		}

		CPen ps(PS_SOLID, 1, RGB(255, 0, 0));
		dc.SelectObject(ps);

		x = cos(-3.14 / 2 + (3.14 / 180 * 6 * m_sec)) * 280;
		y = sin(-3.14 / 2 + (3.14 / 180 * 6 * m_sec)) * 280;

		dc.MoveTo(300, 300);
		dc.LineTo(300 + (int)x, 300 + (int)y);

		CPen pm(PS_SOLID, 2, RGB(0, 255, 0));
		dc.SelectObject(pm);
	
		x = cos(-3.14 / 2 + (3.14 / 180 * 6 * m_min)) * 240;
		y = sin(-3.14 / 2 + (3.14 / 180 * 6 * m_min)) * 240;

		dc.MoveTo(300, 300);
		dc.LineTo(300 + (int)x, 300 + (int)y);

		CPen ph(PS_SOLID, 3, RGB(0, 0, 255));
		dc.SelectObject(ph);

		x = cos(-3.14 / 2 + (3.14 / 180 * 30 * m_hour)) * 180;
		y = sin(-3.14 / 2 + (3.14 / 180 * 30 * m_hour)) * 180;

		dc.MoveTo(300, 300);
		dc.LineTo(300 + (int)x, 300 + (int)y);
	}
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 1000, NULL);

	return 0;
}




void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		m_time++;
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnButtonS()
{
	m_time++;
	Invalidate();
}



void CChildView::OnButtonM()
{
	m_time += 60;
	Invalidate();
}


void CChildView::OnButtonH()
{
	m_time += 60 * 60;
	Invalidate();
}


void CChildView::OnButtonDigits()
{
	m_flag = 0;
	Invalidate();
}


void CChildView::OnButtonAnalog()
{
	m_flag = 1;
	Invalidate();
}
