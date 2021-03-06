
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "12_MFC_LINEDRAW.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bLButton = false;
	m_Num = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

	for(UINT i = 0; i < m_Num; i++)
	{
		//dc.MoveTo(m_st[i]);
		//dc.LineTo(m_ed[i]); // 선그리기 

		dc.Rectangle(m_st[i].x, m_st[i].y, m_ed[i].x, m_ed[i].y); // 사각형 그리기
	}
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point); // 오버라이딩을 하는데 CWnd::속 함수도 실행해야 하기 때문에 속에서 실행함

	m_st[m_Num] = point;
	m_Num++;
	m_bLButton = true;
	SetCapture(); // 누르는 순간 창 밖으로 나와도 마우스메세지는 계속 내가 가져감
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);

	m_ed[m_Num-1] = point;
	m_bLButton = false;
	Invalidate(); //다시 그리라고 메세지를 보냄
	ReleaseCapture(); // 떼면 더이상 메세지를 안가져옴
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);

//	if (m_bLButton == true) 멤버변수를 선언해 사용하거나
	
	if((nFlags & MK_LBUTTON) != 0) // nFlags는 버튼이 눌렸는지, ctrl, shift등이 눌렸는지에 관한 값들의 조합 들어옴 
	{// 어떤 조합으로 nFlags가 들어오던 LBUTTON이 눌리면 0이 아님 -> if문 실행
		m_ed[m_Num-1] = point;
		Invalidate();
	}
}
