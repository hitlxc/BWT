
// BWTDlg.h : ͷ�ļ�
//

#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sys/timeb.h>
#include <ctime>
#include <climits>
#define MAX 10000
#define occStep 50
#define ERROR_PERCENT 10
using namespace std;

// CBWTDlg �Ի���
class CBWTDlg : public CDialogEx
{
// ����
public:
	CBWTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BWT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	CString file1, file2;
	int order[MAX]; //��¼˳��
	map<char, int> siteMapFrom;//��¼BWT������ÿ���ַ����ֵ�λ��
	char BWTSeq[MAX];
	map<char, int> siteMapTo;
	map<char, int> OccFlag[MAX];

	char seq[MAX];
	char seqSon[MAX];
	int error_num;
	string res;

	void loopMove(char *ch, int steps);
	int OccSearch(char base, int site);
	void setBWT();

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnOpenFile2();
	afx_msg void OnOpenFile1();
};
