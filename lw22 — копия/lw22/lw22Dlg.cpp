
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
//#define DEBUG_NEW
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
public:
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



Clw22Dlg::Clw22Dlg(CDialogEx* pParent /*=nullptr*/)
	: CDialogEx(IDD_LW22_DIALOG, pParent)
	, m_canvas()
	, thick(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clw22Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_color);
	DDX_Control(pDX, IDC_DRAW, m_canvas);
	DDX_Text(pDX, IDC_EDIT1, thick);
}

BEGIN_MESSAGE_MAP(Clw22Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	//ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	//ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//ON_WM_WINTAB
	ON_COMMAND(ID_FILE_OPEN32771, &Clw22Dlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVEAS, &Clw22Dlg::OnFileSaveas)
	ON_COMMAND(ID_NEW_FILE, &Clw22Dlg::OnNewFile)
	ON_EN_KILLFOCUS(IDC_EDIT1, &Clw22Dlg::OnEnKillfocusEdit1)
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
	//ShowWindow(SW_MAXIMIZE);
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

void Clw22Dlg::RedrawBackBuffer()
{
	Graphics g(m_pBackBuffer.get());
	//g.Clear(Color(255, 255, 255, 0));
	g.DrawImage(m_pBitmap.get(), 0, 0);
}

BOOL Clw22Dlg::OnEraseBkgnd(CDC* bkgnd)
{
	return TRUE;
}

void Clw22Dlg::OnSize(UINT nType, int cx, int cy)
{
}

void Clw22Dlg::OnPaint()
{
	CClientDC dc(&m_canvas);
	RedrawBackBuffer();
	Graphics g(dc);
	CRect rc;
	if (m_pBackBuffer.get())
	{
		g.DrawImage(m_pBackBuffer.get(), 0, 0);
	}
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
	CRect rc;
	Image img(ofn.lpstrFile);
	if (img.GetLastStatus() == Ok)
	{
		GetClientRect(&rc);
		m_pBitmap = std::auto_ptr<Bitmap>(new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB));
		m_pBackBuffer = std::auto_ptr<Bitmap>(new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB));
		m_pBitmapOriginal = std::auto_ptr<Bitmap>(new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB));
		Graphics g(m_pBitmap.get());
		g.DrawImage(&img, 0, 0, img.GetWidth(), img.GetHeight());
		m_fileOpen = true;
		RedrawWindow();
	}
	//m_canvas.OpenFile(ofn);
}

std::wstring Clw22Dlg::GetFileExtension(std::wstring const& fileName)
{
	size_t dotPos = fileName.find_last_of(L'.');
	if (dotPos != std::wstring::npos)
	{
		return fileName.substr(dotPos + 1);
	}
	else
	{
		return std::wstring();
	}
}

std::wstring WStringToLower(std::wstring const& str)
{
	std::wstring result(str);

	std::transform(result.begin(), result.end(), result.begin(), std::tolower);

	return result;
}

CLSID GetEncoderCLSID(std::wstring const& fileExtension)
{
	// Приводим разрешение к виду "*.разрешение"
	std::wstring extensionMask = L"*." + WStringToLower(fileExtension) + L";";

	// Запрашиваем у GDI+ количество кодировщиков изображений
	// и размер блока данных для хранения их описания
	UINT numEncoders;
	UINT encodersSize;
	GetImageEncodersSize(&numEncoders, &encodersSize);

	// Выделяем буфер для хранения информации о кодировщиках
	std::vector<BYTE> encodersBuffer(encodersSize);

	// Запрашиваем у GDI+ информацию обо всех кодировщиков
	ImageCodecInfo* pInstalledCodecs = 
		reinterpret_cast<ImageCodecInfo *>(&encodersBuffer[0]);
	GetImageEncoders(numEncoders, encodersSize, pInstalledCodecs);

	ImageCodecInfo * pMatchedCodec = NULL;

	// ищем подходящий кодировщик изображений
	for (unsigned i = 0; i < numEncoders; ++i)
	{
		ImageCodecInfo & codec = pInstalledCodecs[i];

		// получаем расширения файлов, поддерживаемых данным кодировщиком
		// в формате: *.jpg;*.jpe;*.jpeg;
		std::wstring extensions = WStringToLower(codec.FilenameExtension) + L";";

		// Если в списке расширений содержится маска расширения файла
		// то кодек считается найденным
		if (extensions.find(extensionMask) != std::wstring::npos)
		{
			return codec.Clsid;
		}
	}

	// не нашли подходящий кодировщик, возвращаем нулевой идентификатор
	return CLSID_NULL;
}

void Clw22Dlg::InitFileNameStructure(
	//HWND hwndOwner,
	OPENFILENAME* pOpenFileName,
	TCHAR* pFileName,
	DWORD maxFileName)
{
	ZeroMemory(pOpenFileName, sizeof(OPENFILENAME));

	pOpenFileName->lStructSize = sizeof(OPENFILENAME);
	//pOpenFileName->hwndOwner = hwndOwner;
	pOpenFileName->hInstance = g_hInstance;
	pOpenFileName->nMaxFile = maxFileName;
	pOpenFileName->lpstrFile = pFileName;
	pOpenFileName->lpstrFilter =
		_T("Images (BMP, PNG, JPG)\0*.bmp;*.png;*.jpg;\0")
		_T("All files\0*.*\0")
		_T("\0");

}


void Clw22Dlg::OnFileSaveas()
{
	if (!m_pBitmap.get())
	{
		return;
	}
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH + 1] = _T("");
	InitFileNameStructure(&ofn, fileName, MAX_PATH);

	if (GetSaveFileName(&ofn))
	{
		std::wstring fileExtension = GetFileExtension(fileName);
		// Получаем идентификатор по расширению файла
		CLSID codecId = GetEncoderCLSID(fileExtension);

		// Если вернули CLSID_NULL (кодек не найден), то выходим
		if (IsEqualCLSID(codecId, CLSID_NULL))
		{
			return;
		}

		// заполняем параметры кодировщика
		EncoderParameters params;
		params.Count = 1;// у нас только один параметр (степень компресии 0-100)

		// заполняем характеристики параметра качество сжатия
		EncoderParameter& param0 = params.Parameter[0];

		LONG qualityParam = 75;

		param0.Guid = EncoderCompression;	// идентификатор параметра "компрессия"
		param0.NumberOfValues = 1;	// в массиве параметров содержится одно значение
		param0.Type = EncoderParameterValueTypeLong; // тип значений LONG
		param0.Value = &qualityParam;	//

		m_pBitmap->Save(fileName, &codecId, &params);
	}

}


void Clw22Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	this->ClientToScreen(&point);
	UpdateData();
	// transform from screen coordinates to picture control coordinates
	m_canvas.ScreenToClient(&point);
	if (m_fileOpen)
	{
		m_PointX = point.x;
		m_PointY = point.y;
	}
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		Graphics g(m_pBitmap.get());
		COLORREF color = m_color.GetColor();
		SolidBrush brush(Color(GetRValue(color), GetGValue(color), GetBValue(color)));
		Pen pen(Color(GetRValue(color), GetGValue(color), GetBValue(color)), (REAL)thick);
		g.DrawLine(&pen, m_PointX, m_PointY, point.x, point.y);
		g.FillEllipse(&brush, m_PointX - (REAL)thick/2, m_PointY - (REAL)thick/2, (REAL)thick, (REAL)thick);
		m_PointX = point.x;
		m_PointY = point.y;
		//Invalidate();
	}
	m_fileOpen = false;
	CDialogEx::OnMouseMove(nFlags, point); //присутствует по умолчанию
}

void Clw22Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);

	// transform from screen coordinates to picture control coordinates
	m_canvas.ScreenToClient(&point);
	m_PointX = point.x;
	m_PointY = point.y;
	CDialogEx::OnLButtonDown(nFlags, point);
}

void Clw22Dlg::OnNewFile()
{
	CRect rc, rc2;
	m_canvas.GetClientRect(&rc);
	GetClientRect(&rc2);
	m_pBitmap = std::auto_ptr<Bitmap>(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	m_pBackBuffer = std::auto_ptr<Bitmap>(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	m_pBitmapOriginal = std::auto_ptr<Bitmap>(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
	Graphics g(m_pBitmap.get());
	g.Clear(Color(255, 255, 255));
	//g.DrawImage(&img, 0, 0, img.GetWidth(), img.GetHeight());
}


void Clw22Dlg::OnEnKillfocusEdit1()
{
	if (UpdateData())
	{
		
	}
	// TODO: добавьте свой код обработчика уведомлений
}
