
// BWTDlg.h : 头文件
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

// CBWTDlg 对话框
class CBWTDlg : public CDialogEx
{
// 构造
public:
	CBWTDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BWT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CString file1, file2;
	int order[MAX]; //记录顺序
	map<char, int> siteMapFrom;//记录BWT序列中每个字符出现的位置
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

	// 生成的消息映射函数
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
