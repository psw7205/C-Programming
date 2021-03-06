
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "1.h"
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
	GetClientRect(&rect);

	int w = rect.Width(); // 화면의 너비 w와
	int h = rect.Height(); // 화면의 높이 h 입니다.

	CBrush brush1(RGB(200, 200, 200)); // 회색으로 바탕색을 정하고
	dc.SelectObject(brush1);

	CPen pen1(PS_SOLID, 5, RGB(0, 0, 0));
	dc.SelectObject(&pen1); // 두꺼운 선을 설정하고

	dc.Rectangle(10, 10, w - 10, h - 10); // 배경색이 회색인 상하좌우 여백이 10인 사각형을 그립니다. 

	CBrush brush2(RGB(255, 255, 255));
	dc.SelectObject(brush2); // 다시 흰색을 바탕색으로 설정하고

	dc.Rectangle(10, 10 + (h - 20) / 3, w - 10, h - 10);
	// 회색인 1행만 제외하고 나머지 두 행 부분을 다시 덧칠합니다.

	CPen pen2(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&pen2); // 얇은 선

	dc.MoveTo(10, 10 + (h - 20) * 2 / 3);
	dc.LineTo(w - 10, 10 + (h - 20) * 2 / 3); // 얇은 선으로 그리는 가로 줄과

	for (int i = 1; i <= 7; i++) 
	// 세로줄 7개를 그립니다. 한 칸은 너비 (w-20) / 7, 높이 (h - 20) / 3 입니다.
	{
		dc.MoveTo(10 + (w - 20) * i / 7, 10);
		dc.LineTo(10 + (w - 20) * i / 7, h - 10);
	}

	CFont font1;
	font1.CreatePointFont(w*h / 1000, _T("Arial Rounded MT Bold"));
	dc.SelectObject(font1);
	// Arial 볼드체로 설정합니다. 크기는 화면을 조절해도 같은 비율로 커지고 줄어들게 설정했습니다.

	dc.SetBkMode(TRANSPARENT); // 회색이 가려지지 않게 글자 배경을 투명하게 설정합니다.

	CString num;

	for (int i = 0; i < 7; i++)
	{
		num.Format(_T("%d"), i);

		CRect textRect(10 + (w - 20) / 7 * i, 10, 10 + (w - 20) / 7 * (i + 1), 10 + (h - 20) / 3);

		if (i != 0) // 0을 제외하고 1부터 6까지 까지 칸 정중앙에 표시합니다. 
	//칸은 이미 위에서 그렸으므로 따로 사각형을 출력하진 않았습니다.
		{
			dc.DrawTextW(num, textRect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}

	CString a[] = { _T("확률"), _T("0.1"), _T("0.3"), _T("0.2"), _T("0.1"), _T("0.1"), _T("0.2") };
	// 2행의 데이터입니다.
	CString b[] = { _T("누적"), _T("0.1"), _T("0.4"), _T("0.6"), _T("0.7"), _T("0.8"), _T("1.0") };
	// 3행의 데이터입니다.

	CFont font2;
	font2.CreatePointFont(w*h / 1500, _T("Arial")); 
	// 2행과 3행은 볼드체가 아니기에 다시 폰트를 지정했습니다.
	dc.SelectObject(font2);

	//1행과 같은 방법으로 2행과 3행을 출력합니다. 
	//역시 칸은 이미 그렸으므로 그리지 않고 데이터만 정렬해 출력합니다.
	for (int i = 0; i < 7; i++)
	{
		CRect textRect( 10+(w-20)/7*i , 10+(h-20)/3 , 10+(w-20)/7*(i+1) , 10+(h-20)*2/3 );

		dc.DrawTextW(a[i], textRect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	for (int i = 0; i < 7; i++)
	{
		CRect textRect( 10+(w-20)/7*i , 10+(h-20)*2/3 , 10+(w-20)/7*(i+1) , h-10 );

		dc.DrawTextW(b[i], textRect,
			DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}