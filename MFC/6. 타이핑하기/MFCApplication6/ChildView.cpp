
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication6.h"
#include "ChildView.h"

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
	ON_WM_CHAR()
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
	dc.TextOutW(0, 0, _T("16013093 박상우"));

	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(m_str, rect, DT_LEFT);
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_BACK) // 백스페이스가 들어오면
	{
		m_str.Delete(m_str.GetLength() - 1, 1); // 마지막 글자에서 한글자를 지우고
	}
	else if (nChar == VK_RETURN)
	{
		m_str+= _T("\r\n");
	}
	else
		m_str += TCHAR(nChar); // 2바이트 형식(유니코드)로 바꿔 더해줌

	Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
