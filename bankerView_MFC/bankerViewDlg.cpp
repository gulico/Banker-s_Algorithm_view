// bankerViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bankerView.h"
#include "bankerViewDlg.h"
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////////////
//全局变量定义
int Available[100]; //可利用资源数组
int Max[50][100];   //最大需求矩阵
int Allocation[50][100];  //已分配矩阵
int Need[50][100];        //需求矩阵
int Request[50][100];     //M个进程还需要N类资源的资源量
int Finish[50];
int p[50];
int m,n;   //M个进程,N类资源

struct BestRequest{
	int id;
	int request[100];
	int sum;
	bool nav;

}bestRequest[50];
int MaxRequest[100];

bool camp(BestRequest a ,BestRequest b)
{
	return a.sum > b.sum ;			
}
int Safe()                      
{
    int i,j,l=0;
    int Work[100]; //可利用资源数组
    for (i=0;i<n;i++)
        Work[i]=Available[i];
    for (i=0;i<m;i++)
        Finish[i]=0;
    for (i=0;i<m;i++)
    {
        if (Finish[i]==1)
        continue;
        else
        {
            for (j=0;j<n;j++)
            {
                if (Need[i][j]>Work[j])
                    break;
            }
            if (j==n)//本进程全部需要资源都可得
            {
                Finish[i]=1;//标记本进程已经加入队列
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];//当前被本进程占用的所有已分配资源被释放，可利用资源增加。
                p[l++]=i;//本进程序号加入队列p
                i=-1;//从头寻找可执行进程
            }
            else continue;
        }
        if (l==m)//全部进程加入队列
        {
            //cout<<"系统是安全的"<<'\n';
            //cout<<"系统安全序列是:\n";
            for (i=0;i<l;i++)
            {
                //cout<<p[i];
                //if (i!=l-1)
                    //cout<<"-->";
            }
            //cout<<'\n';
            return 1;
        }
    }

	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankerViewDlg dialog

CBankerViewDlg::CBankerViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBankerViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBankerViewDlg)
	m_progessNum = 0;
	m_request1 = 0;
	m_request2 = 0;
	m_request3 = 0;
	m_request4 = 0;
	m_bestrequest1 = 0;
	m_bestrequest2 = 0;
	m_bestrequest3 = 0;
	m_bestrequest4 = 0;
	m_ansStr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBankerViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBankerViewDlg)
	DDX_Text(pDX, IDC_EDIT1, m_progessNum);
	DDX_Text(pDX, IDC_EDIT2, m_request1);
	DDX_Text(pDX, IDC_EDIT3, m_request2);
	DDX_Text(pDX, IDC_EDIT4, m_request3);
	DDX_Text(pDX, IDC_EDIT5, m_request4);
	DDX_Text(pDX, IDC_EDIT6, m_bestrequest1);
	DDX_Text(pDX, IDC_EDIT7, m_bestrequest2);
	DDX_Text(pDX, IDC_EDIT8, m_bestrequest3);
	DDX_Text(pDX, IDC_EDIT9, m_bestrequest4);
	DDX_Text(pDX, IDC_EDIT10, m_ansStr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBankerViewDlg, CDialog)
	//{{AFX_MSG_MAP(CBankerViewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBankerViewDlg message handlers

BOOL CBankerViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	SetDlgItemText(IDC_EDIT1,""); 
	SetDlgItemText(IDC_EDIT2,"");
	SetDlgItemText(IDC_EDIT3,"");
	SetDlgItemText(IDC_EDIT4,"");
	SetDlgItemText(IDC_EDIT5,"");
	SetDlgItemText(IDC_EDIT6,"");
	SetDlgItemText(IDC_EDIT7,"");
	SetDlgItemText(IDC_EDIT8,"");
	SetDlgItemText(IDC_EDIT9,"");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBankerViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBankerViewDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBankerViewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBankerViewDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();//退出
	UpdateData(TRUE);//
	FILE *fp = NULL;
	fp = fopen("in.txt", "r");
    int i,j,mi;
	fscanf(fp,"%d",&m);
	fscanf(fp,"%d",&n);

    for (i=0;i<m;i++){
        for(j=0;j<n;j++){
			fscanf(fp,"%d",&Max[i][j]);
		}
	}
    for (i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
			fscanf(fp,"%d",&Allocation[i][j]);
            Need[i][j]=Max[i][j]-Allocation[i][j];
            if (Need[i][j]<0)
            {
                j--;
                continue;
            }
        }
    }
    for (i=0;i<n;i++){
		fscanf(fp,"%d",&Available[i]);
	}
    Safe();

        mi = m_progessNum;

		Request[mi][0] = m_request1;
		Request[mi][1] = m_request2;
		Request[mi][2] = m_request3;
		Request[mi][3] = m_request4;
		int flag = 1;
        for (i=0;i<n;i++)
        {

            if (Request[mi][i]>Need[mi][i])
            {
				flag=0;
                //cout<<"所请求资源数超过进程的需求量！\n";
                break;
            }
            if (Request[mi][i]>Available[i])
            {
				flag=0;
                //cout<<"所请求资源数超过系统所有的资源数！\n";
                break;
            }
        }
		
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];//系统可分配减少
            Allocation[mi][i]+=Request[mi][i];//已分配增加
            Need[mi][i]-=Request[mi][i];//本进程需求量减少
        }
        if (Safe()&&flag){
            //cout<<"同意分配请求\n";
			m_ansStr = "安全，同意分配请求";
			for(i=0;i<m;i++){
				bestRequest[i].id = i;
				bestRequest[i].sum = 0;
				bestRequest[i].nav = false;
				for(j=0;j<n;j++){
					bestRequest[i].request[j]=Available[j]-Need[i][j];
					bestRequest[i].sum+=bestRequest[i].request[j];
					if(bestRequest[i].request[j]<0){
						bestRequest[i].nav = true;
					}
				}
			}
			sort(bestRequest,bestRequest+m,camp);//降序
			int sum=0;
			for(i=0;i<m;i++){
				int mm[100];
				int temp = 0;
				if(bestRequest[i].nav)
					continue;
				for(j=0;j<n;j++){
					if(bestRequest[i].request[j] >= Need[mi][j]){
						mm[j] = Need[mi][j];
					}
					else{
						mm[j] = bestRequest[i].request[j];
					}
					temp += mm[j];
				}
				if(temp>sum){
					sum = temp;
					for(j=0;j<n;j++){
						MaxRequest[j] = mm[j];
					}
				}
			}

			if(sum != 0){
				//printf("建议请求数组为：\n");
				//for(j=0;j<n;j++){
				//	printf("%d ",MaxRequest[j]);
				//}
				m_bestrequest1 = MaxRequest[0];
				m_bestrequest2 = MaxRequest[1];
				m_bestrequest3 = MaxRequest[2];
				m_bestrequest4 = MaxRequest[3];


				printf("\n");
			}
			else{
			//	printf("本进程无法请求\n");
			}
		}
        else
        {
			m_ansStr = "不安全，你的请求被拒绝";
            //cout<<"你的请求被拒绝…\n";
            for (i=0;i<n;i++)
            {
                Available[i]+=Request[mi][i];
                Allocation[mi][i]-=Request[mi][i];
                Need[mi][i]+=Request[mi][i];
            }
			for(i=0;i<m;i++){
				bestRequest[i].id = i;
				bestRequest[i].sum = 0;
				bestRequest[i].nav = false;
				for(j=0;j<n;j++){
					bestRequest[i].request[j]=Available[j]-Need[i][j];
					bestRequest[i].sum+=bestRequest[i].request[j];
					if(bestRequest[i].request[j]<0){
						bestRequest[i].nav = true;
					}
				}
			}
			sort(bestRequest,bestRequest+m,camp);//降序
			int sum=0;
			for(i=0;i<m;i++){
				int mm[100];
				int temp = 0;
				if(bestRequest[i].nav)
					continue;
				for(j=0;j<n;j++){
					if(bestRequest[i].request[j] >= Need[mi][j]){
						mm[j] = Need[mi][j];
					}
					else{
						mm[j] = bestRequest[i].request[j];
					}
					temp += mm[j];
				}
				if(temp>sum){
					sum = temp;
					for(j=0;j<n;j++){
						MaxRequest[j] = mm[j];
					}
				}
			}

			if(sum != 0){
				//printf("建议请求数组为：\n");
				//for(j=0;j<n;j++){
				//	printf("%d ",MaxRequest[j]);
				//}
				m_bestrequest1 = MaxRequest[0];
				m_bestrequest2 = MaxRequest[1];
				m_bestrequest3 = MaxRequest[2];
				m_bestrequest4 = MaxRequest[3];


				printf("\n");
			}
			else{
			//	printf("本进程无法请求\n");
			}
			
        }

        for (i=0;i<m;i++) 
            Finish[i]=0;
	UpdateData(FALSE);
}
