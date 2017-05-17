
// BWTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BWT.h"
#include "BWTDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//_CRT_SECURE_NO_DEPRECATE
//_CRT_NONSTDC_NO_DEPRECATE

struct BWTObj {
	char str[MAX]; //BWT矩阵
	int index;
};
BWTObj BWTMatrix[MAX];

bool compare(const BWTObj &tmp1, const BWTObj &tmp2) {
	return strcmp(tmp1.str, tmp2.str)<0 ? true : false;
}

struct ErrStep {
	int from;
	int to;
	int now;
	ErrStep(int a, int b, int c) { from = a; to = b; now = c; }
};

//字符串ch循环右移steps位
void CBWTDlg::loopMove(char *ch, int steps)
{
	char temp[MAX];
	char*p;
	int n = strlen(ch) - steps;
	p = ch + n;
	memcpy(temp, p, steps);
	memcpy(temp + steps, ch, n);
	memcpy(ch, temp, strlen(ch));
}

//查询site位点前（不包含site，从0开数）有多少个base碱基
int CBWTDlg::OccSearch(char base, int site) {
	int num = OccFlag[site/occStep][base];
	for (int i = site / occStep * occStep; i < site; i++) {
		if (BWTSeq[i] == base) {
			num++;
		}
	}
	return num;
}

void CBWTDlg::setBWT() {
	int numA = 0, numT = 0, numG = 0, numC = 0;
	int len = strlen(seq);
	for (int i = 0; i < len; i++) {
		order[i] = BWTMatrix[i].index;
		BWTSeq[i] = BWTMatrix[i].str[len - 1];
		if (siteMapFrom.find(BWTMatrix[i].str[0]) == siteMapFrom.end()) {
			siteMapFrom[BWTMatrix[i].str[0]] = i;
			if (i > 0) {
				siteMapTo[BWTMatrix[i - 1].str[0]] = i;
			}
		}
		if (i%occStep == 0) {
			//OccFlag[i / occStep]['A'] = numA;
			//OccFlag[i / occStep]['T'] = numT;
			//OccFlag[i / occStep]['G'] = numG;
			//OccFlag[i / occStep]['C'] = numC;
			OccFlag[i / occStep]['a'] = numA;
			OccFlag[i / occStep]['t'] = numT;
			OccFlag[i / occStep]['g'] = numG;
			OccFlag[i / occStep]['c'] = numC;
		}
		switch (BWTSeq[i])
		{
		case 'A':
		case 'a':
			numA++;
			break;
		case 'T':
		case 't':
			numT++;
			break;
		case 'G':
		case 'g':
			numG++;
			break;
		case 'C':
		case 'c':
			numC++;
			break;
		default:
			break;
		}
		
	}
	//siteMapTo['T'] = len - 1;
	siteMapTo['t'] = len;
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBWTDlg 对话框

CBWTDlg::CBWTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BWT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBWTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBWTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBWTDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CBWTDlg::OnOpenFile2)
	ON_BN_CLICKED(IDOK3, &CBWTDlg::OnOpenFile1)
END_MESSAGE_MAP()


// CBWTDlg 消息处理程序

BOOL CBWTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CEdit*  pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);//获取相应的编辑框ID
	pEdit->SetWindowText(_T("欢迎使用本系统\r\n请将输入数据写入.txt文件\r\n文件一为母串，文件二为子串\r\n选择文件后点击分析即可查看计算结果")); //设置默认显示的内容

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBWTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBWTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBWTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBWTDlg::OnBnClickedOk()
{
		char ch;

        freopen(file1,"r",stdin);
        int i=0;
        while((ch=getchar())!=EOF){
            if(ch!='\n')
                seq[i++] = ch;
        }
        seq[i++] = '$';
        seq[i] = '\0';

        struct timeb startTime, endTime;
		ftime(&startTime);

		memset(order, 0x0, 10 * sizeof(int));
		memset(BWTSeq, 0x0, 10 * sizeof(char));
		siteMapFrom.clear();
		siteMapTo.clear();
		for (int i = 0; i < MAX; i++) {
			OccFlag[i].clear();
		}

		int len = strlen(seq);
		for (int i = 0; i < len; i++) {
			memcpy(BWTMatrix[i].str, seq, strlen(seq));
			loopMove(seq, 1);
			BWTMatrix[i].index = i;
		}
		sort(BWTMatrix, BWTMatrix+len, compare);

		setBWT();

        freopen(file2,"r",stdin);
		res = "";
		int j = 0;
        while((scanf("%s",seqSon))!=EOF){
			j++;
            int lenSon = strlen(seqSon);
            int from = 0;
            int to = strlen(seq);
            int step = lenSon;

			error_num = lenSon*ERROR_PERCENT / 100;
			//if (error_num)
			//{
				vector<ErrStep> vec[MAX];
				vec[0].push_back(ErrStep(from, to, 0));
				for (int i = 1; i <= lenSon; i++) 
				{
					for (int k = i-1; k>=i-1-error_num && k >= 0; k--)
					{
						for (int l = 0; l < vec[k].size(); l++)
						{
							int now = vec[k][l].now + i - k - 1;
							if (now <= error_num) {
								int ocf = OccSearch(seqSon[lenSon-i], vec[k][l].from);
								int oct = OccSearch(seqSon[lenSon - i], vec[k][l].to);
								from = ocf + siteMapFrom[seqSon[lenSon - i]];
								to = from + oct - ocf;
								
								if (from < to) {
									bool flag = true;
									for(int m=0;m<vec[i].size();m++)
										if (vec[i][m].from == from && vec[i][m].to == to) {
											if (now < vec[i][m].now)
												vec[i][m].now = now;
											flag = false;
											break;
										}
									if(flag)
										vec[i].push_back(ErrStep(from, to, now));
								}
							}
						}
					}
				}
				cout << vec[lenSon].size() << endl;
			//}

            /*while (step--) {
				int ocf = OccSearch(seqSon[step], from);
				int oct = OccSearch(seqSon[step], to);
                from = ocf + siteMapFrom[seqSon[step]];
				to = from + oct - ocf;
                if (from >= to) break;
            }*/

			char tj[256];
			sprintf(tj, "%d", j);
			res =  res + "第" + tj + "次匹配结果 : \r\n";
            if (vec[lenSon].size()==0) {
                res += "没查到\r\n" ;
            }
			else {
				map<int,int> map_res;
				map<int, int>::iterator iter;
				for (int k = 0; k < vec[lenSon].size(); k++) {
					for (int i = vec[lenSon][k].from; i < vec[lenSon][k].to; i++) {
						int key = len - order[i];
						int val = vec[lenSon][k].now;
						iter = map_res.find(key);
						if (iter == map_res.end() || iter->second > val)
							map_res[key] = val;
					}
				}
				int last = 0;
				char temp[256];
				for (iter = map_res.begin(); iter != map_res.end(); iter++) {
					if (iter->first - last > lenSon) {
						sprintf(temp, "%d", iter->first);
						res = res + "在原序列" + temp +"处,";
						sprintf(temp, "%d", iter->second);
						res = res + temp + "个错误\r\n";
					}
					last = iter->first;
				}
			}

            /*int size = sizeof(BWTMatrix)+ sizeof(order) + sizeof(siteMapFrom) + sizeof(siteMapTo) + sizeof(BWTSeq) + sizeof(OccFlag);
            int size1 = sizeof(BWTMatrix);
            int size2 = sizeof(order),size3 =sizeof(siteMapFrom), size4 = sizeof(siteMapTo), size5 = sizeof(BWTSeq), size6 = sizeof(OccFlag);
            stringstream ss;
            ss << size;
            string   s = ss.str();
            res = res + "占用内存:" + s + "\r\n";*/
            ftime(&endTime);

            stringstream ss;
            int time = (endTime.time - startTime.time) * 1000 + (endTime.millitm - startTime.millitm);
            ss << time;
            string   s = ss.str();

            res += "运行了：" + s + "毫秒\r\n" ;

        }
		CEdit*  pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);//获取相应的编辑框ID
		pEdit->SetWindowText(_T((LPCTSTR)res.c_str())); //设置默认显示的内容
	//CDialogEx::OnOK();
}


void CBWTDlg::OnOpenFile2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog opendlg(TRUE, NULL, _T("*.txt"), OFN_OVERWRITEPROMPT, _T("文本文件(*.txt)|*.*||"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		file2 = opendlg.GetPathName();
	}
}


void CBWTDlg::OnOpenFile1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog opendlg(TRUE, NULL, _T("*.txt"), OFN_OVERWRITEPROMPT, _T("文本文件(*.txt)|*.*||"), NULL);
	if (opendlg.DoModal() == IDOK)
	{
		file1 = opendlg.GetPathName();
	}
}
