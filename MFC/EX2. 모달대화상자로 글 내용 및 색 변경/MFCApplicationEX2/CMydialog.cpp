// CMydialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplicationEX2.h"
#include "CMydialog.h"
#include "afxdialogex.h"


// CMydialog 대화 상자

IMPLEMENT_DYNAMIC(CMydialog, CDialogEx)

CMydialog::CMydialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, editStr(_T(""))
	, editRed(0)
	, editGreen(0)
	, editBlue(0)
{

}

CMydialog::~CMydialog()
{
}

void CMydialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, editStr);
	DDX_Text(pDX, IDC_EDIT2, editRed);
	DDV_MinMaxInt(pDX, editRed, 0, 255);
	DDX_Text(pDX, IDC_EDIT3, editGreen);
	DDV_MinMaxInt(pDX, editGreen, 0, 255);
	DDX_Text(pDX, IDC_EDIT4, editBlue);
	DDV_MinMaxInt(pDX, editBlue, 0, 255);
}


BEGIN_MESSAGE_MAP(CMydialog, CDialogEx)

END_MESSAGE_MAP()


// CMydialog 메시지 처리기

