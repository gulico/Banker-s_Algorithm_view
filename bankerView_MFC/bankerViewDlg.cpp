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
//ȫ�ֱ�������
int Available[100]; //��������Դ����
int Max[50][100];   //����������
int Allocation[50][100];  //�ѷ������
int Need[50][100];        //�������
int Request[50][100];     //M�����̻���ҪN����Դ����Դ��
int Finish[50];
int p[50];
int m,n;   //M������,N����Դ

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
    int Work[100]; //��������Դ����
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
            if (j==n)//������ȫ����Ҫ��Դ���ɵ�
            {
                Finish[i]=1;//��Ǳ������Ѿ��������
                for(int k=0;k<n;k++)
                    Work[k]+=Allocation[i][k];//��ǰ��������ռ�õ������ѷ�����Դ���ͷţ���������Դ���ӡ�
                p[l++]=i;//��������ż������p
                i=-1;//��ͷѰ�ҿ�ִ�н���
            }
            else continue;
        }
        if (l==m)//ȫ�����̼������
        {
            //cout<<"ϵͳ�ǰ�ȫ��"<<'\n';
            //cout<<"ϵͳ��ȫ������:\n";
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
	
	//CDialog::OnOK();//�˳�
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
                //cout<<"��������Դ���������̵���������\n";
                break;
            }
            if (Request[mi][i]>Available[i])
            {
				flag=0;
                //cout<<"��������Դ������ϵͳ���е���Դ����\n";
                break;
            }
        }
		
        for (i=0;i<n;i++)
        {
            Available[i]-=Request[mi][i];//ϵͳ�ɷ������
            Allocation[mi][i]+=Request[mi][i];//�ѷ�������
            Need[mi][i]-=Request[mi][i];//����������������
        }
        if (Safe()&&flag){
            //cout<<"ͬ���������\n";
			m_ansStr = "��ȫ��ͬ���������";
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
			sort(bestRequest,bestRequest+m,camp);//����
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
				//printf("������������Ϊ��\n");
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
			//	printf("�������޷�����\n");
			}
		}
        else
        {
			m_ansStr = "����ȫ��������󱻾ܾ�";
            //cout<<"������󱻾ܾ���\n";
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
			sort(bestRequest,bestRequest+m,camp);//����
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
				//printf("������������Ϊ��\n");
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
			//	printf("�������޷�����\n");
			}
			
        }

        for (i=0;i<m;i++) 
            Finish[i]=0;
	UpdateData(FALSE);
}
