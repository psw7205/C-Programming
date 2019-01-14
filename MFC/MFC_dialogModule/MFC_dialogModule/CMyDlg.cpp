// CMyDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_dialogModule.h"
#include "CMyDlg.h"
#include "afxdialogex.h"


// CMyDlg 대화 상자

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_editstr(_T(""))
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_editstr);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
END_MESSAGE_MAP()


// CMyDlg 메시지 처리기
