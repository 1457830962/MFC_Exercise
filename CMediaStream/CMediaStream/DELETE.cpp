// DELETE.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMediaStream.h"
#include "DELETE.h"
#include "afxdialogex.h"


// CDELETE �Ի���

IMPLEMENT_DYNAMIC(CDELETE, CDialog)

CDELETE::CDELETE(CWnd* pParent /*=NULL*/)
	: CDialog(CDELETE::IDD, pParent)
{

}

CDELETE::~CDELETE()
{
}

void CDELETE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDELETE, CDialog)
	ON_BN_CLICKED(IDOK, &CDELETE::OnBnClickedOk)
END_MESSAGE_MAP()


// CDELETE ��Ϣ�������


void CDELETE::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
