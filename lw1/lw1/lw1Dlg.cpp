
// lw1Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "lw1.h"
#include "lw1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// Диалоговое окно Clw1Dlg



Clw1Dlg::Clw1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LW1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clw1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Clw1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Обработчики сообщений Clw1Dlg

BOOL Clw1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void Clw1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.


void Clw1Dlg::DrawTable(CDC& dc)
{
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CBrush brush(RGB(230, 0, 200));

	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	//ножки
	dc.Rectangle(300, 300, 330, 500);
	dc.Rectangle(550, 300, 580, 500);
	dc.Rectangle(400, 300, 420, 410);

	//нижнее основание
	dc.Ellipse(180, 230, 680, 350);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	CBrush brush2(RGB(250, 150, 217));

	CPen* pOldPen2 = dc.SelectObject(&pen2);
	CBrush* pOldBrush2 = dc.SelectObject(&brush2);

	//верхнее основание
	dc.Ellipse(180, 210, 680, 330);

	dc.SelectObject(pOldPen2);
	dc.SelectObject(pOldBrush2);
}


void Clw1Dlg::DrawChairs(CDC& dc)
{
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CBrush brush(RGB(230, 0, 200));

	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	//задняя ножка первого стула
	dc.Rectangle(195, 370, 180, 450);

	//объемная часть первого стула
	CPoint pts[5] = { {150, 370}, {250, 370}, {200, 340}, {150, 340}, {150, 370} };
	dc.Polygon(pts, 4);

	//задние ножки второго стула
	dc.Rectangle(605, 370, 620, 450);
	dc.Rectangle(700, 370, 715, 450);

	//объемная часть второго стула
	CPoint pts2[11] = { {780, 100}, {750, 100}, {750, 370}, {650, 370}, {650, 400}, {600, 370}, {600, 340}, {700, 340}, {700, 90}, {720, 90}, {780, 100} };
	dc.Polygon(pts2, 10);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	
	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	CBrush brush2(RGB(250, 150, 217));

	CPen* pOldPen2 = dc.SelectObject(&pen2);
	CBrush* pOldBrush2 = dc.SelectObject(&brush2);

	//спинка 1 стула
	dc.Rectangle(120, 100, 150, 370);
	//сидение 1 стула
	dc.Rectangle(120, 370, 250, 400);
	//передние ножки 1 стула
	dc.Rectangle(125, 400, 140, 480);
	dc.Rectangle(230, 400, 245, 480);

	//спинка 2 стула
	dc.Rectangle(750, 100, 780, 370);
	//сидение 2 стула
	dc.Rectangle(780, 370, 650, 400);
	//передние ножки 2 стула
	dc.Rectangle(775, 400, 760, 480);
	dc.Rectangle(655, 400, 670, 480);

	dc.SelectObject(pOldPen2);
	dc.SelectObject(pOldBrush2);

}


void Clw1Dlg::DrawTableware(CDC& dc)
{
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brush(RGB(255, 255, 255));

	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	//ваза
	dc.Ellipse(390, 200, 450, 260);
	dc.Rectangle(410, 160, 430, 220);

	//тарелки
	dc.Ellipse(250, 270, 320, 290);
	dc.Ellipse(530, 250, 600, 270);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}


void Clw1Dlg::DrawFlowers(CDC& dc)
{
	CPen pen(PS_SOLID, 1, RGB(198, 0, 66));
	CBrush brush(RGB(240, 0, 80));

	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	dc.Ellipse(410, 150, 430, 170);
	dc.Ellipse(425, 135, 455, 165);
	dc.Ellipse(421, 170, 441, 190);
	dc.Ellipse(395, 105, 425, 135);
	dc.Ellipse(375, 140, 405, 170);
	dc.Ellipse(400, 130, 420, 150);
	dc.Ellipse(400, 170, 420, 190);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}


void Clw1Dlg::DrawShadow(CDC& dc)
{
	CPen pen(PS_SOLID, 2, RGB(230, 0, 200));
	CBrush brush(RGB(230, 0, 200));



	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	//тень от вазы
	dc.Ellipse(390, 250, 450, 270);

	//тень от тарелок
	dc.Ellipse(260, 280, 310, 295);
	dc.Ellipse(540, 260, 590, 275);

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

void Clw1Dlg::OnPaint()
{
	CPaintDC dc(this); 

	DrawTable(dc); //стол
	DrawChairs(dc); //стул
	DrawShadow(dc); //тень под вазой и тарелками
	DrawTableware(dc); //посуда
	DrawFlowers(dc); //цветы

}


// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR Clw1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

