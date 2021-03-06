
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC_keyboard.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_r = 50;
	m_x = 200;
	m_y = 200;
	m_dx = 0;
	m_dy = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_TIMER()
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

	dc.Ellipse(m_x - m_r, m_y - m_r, m_x + m_r, m_y + m_r);
	dc.TextOutW(0, 0, m_str);
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) // 어떤 키보드 버튼이 눌렸는지 나타냄
{
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);

	TRACE("nChar = %d nRepCnt = %d \n", nChar, nRepCnt); // 일반적인 상황에선 무시 디버그 시 활성화 되어 출력됨, 문법은 printf()와 동일

	/*
	if (nChar == 'A') // 알파벳 버튼은 전부 대문자, 숫자키는 숫자로 대표됨
		m_r += 10;
	if (nChar == 'S')
		m_r -= 10;
	*/

	switch (nChar)
	{
	case VK_PRIOR:		m_r += 10;		break; // PgUp
	case VK_NEXT:		m_r -= 10;		break; // PgDn

	/* 한칸씩 이동
	case VK_UP:			m_y -= 10;		break;
	case VK_DOWN:		m_y += 10;		break;
	case VK_LEFT:		m_x -= 10;		break;
	case VK_RIGHT:		m_x += 10;		break;
	*/ 
	// 계속 이동
	case VK_UP:			m_dx = 0; m_dy = -10;		break;
	case VK_DOWN:		m_dx = 0; m_dy = 10;		break;
	case VK_LEFT:		m_dx = -10; m_dy = 0;		break;
	case VK_RIGHT:		m_dx = 10; m_dy = 0;		break;

	default:							break;
	}
	
	Invalidate();
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) // 어떤 글짜가 입력되었는지 나타냄
{
	CWnd::OnChar(nChar, nRepCnt, nFlags);
	
	/*
	int  a = 'a';
	string str;
	str += char(a); // 일반적인 아스키코드 영어만 기억하는 문자열
	*/

	if (nChar == VK_BACK) // 백스페이스가 들어오면
	{
		m_str.Delete(m_str.GetLength() - 1, 1); // 마지막 글자에서 한글자를 지우고
	}
	else // 아니라면 
		m_str += TCHAR(nChar); // 2바이트 형식(유니코드)로 바꿔 더해줌

	Invalidate();
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) // 이 메세지가 날라와야 실제로 차일드뷰를 사용할 준비가 된 것, 이 때 초기화함
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 30, NULL); // 0 번 타이머, 0.03초 마다 타이머가 울림 (기준 : millisecond)
	SetTimer(1, 100, NULL); // 1번 타이머

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent) // 타이머가 울리면
{
	if(nIDEvent == 0) // 0번 타이머가 울리면
	{
		m_x += m_dx;
		m_y += m_dy;

		CRect rect;
		GetClientRect(rect);

		if (m_x + m_r > rect.right)
		{
			m_x = rect.right - m_r;
			m_dx = -m_dx;
		}
		if (m_x - m_r < rect.left)
		{
			m_x = rect.left + m_r;
			m_dx = -m_dx;
		}
		if (m_y - m_r < rect.top)
		{
			m_y = rect.top + m_r;
			m_dy = -m_dy;
		}
		if (m_y + m_r > rect.bottom)
		{
			m_y = rect.bottom - m_r;
			m_dy = -m_dy;
		}

		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
