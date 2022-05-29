
// lw22Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "lw22.h"
#include "lw22Dlg.h"
#include "afxdialogex.h"

using namespace Gdiplus;

#define MAX_CFileDialog_FILE_COUNT 99
#define FILE_LIST_BUFFER_SIZE ((MAX_CFileDialog_FILE_COUNT * (MAX_PATH + 1)) + 1)

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif

using namespace Gdiplus;
// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно Clw22Dlg



Clw22Dlg::Clw22Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LW22_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clw22Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CANVAS1, m_canvas);
}

BEGIN_MESSAGE_MAP(Clw22Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_FILE_OPEN32771, &Clw22Dlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEAS, &Clw22Dlg::OnFileSaveas)
END_MESSAGE_MAP()


void Clw22Dlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(150, 200); // Установили минимальный размер
	//lpMMI->ptMaxTrackSize = CPoint(100, 1000); // Установили максимальный размер

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
// Обработчики сообщений Clw22Dlg

BOOL Clw22Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_menu);
	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	CRect rc;
	GetClientRect(&rc);
	m_canvas.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
	m_canvas.OnCreate();

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Clw22Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clw22Dlg::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	GetClientRect(&rc);
	if (m_canvas)
	{
		m_canvas.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
	}
}

void Clw22Dlg::OnPaint()
{
	CDialogEx::OnPaint();
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Clw22Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Clw22Dlg::OnFileOpen()
{
	CString fileName;
	wchar_t* p = fileName.GetBuffer(FILE_LIST_BUFFER_SIZE);
	CFileDialog dlgFile(TRUE);
	OPENFILENAME& ofn = dlgFile.GetOFN();
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	ofn.lpstrFile = p;
	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;

	dlgFile.DoModal();
	fileName.ReleaseBuffer();
	m_canvas.OpenFile(ofn);
}


void Clw22Dlg::OnFileSaveas()
{
	// TODO: добавьте свой код обработчика команд
}
