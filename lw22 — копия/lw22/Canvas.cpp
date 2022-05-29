// Canvas.cpp: файл реализации
//

#include "pch.h"
#include "lw22.h"
#include "Canvas.h"
#include <stdexcept>

using namespace Gdiplus;
// CCanvas

IMPLEMENT_DYNAMIC(CCanvas, CDialogEx)

CCanvas::CCanvas()
	: CDialogEx()
	, m_width(0)
	, m_height(0)
	, m_defoultWidth(0)
	, m_defoultHeight(0)
{
}

CCanvas::~CCanvas()
{
}

BEGIN_MESSAGE_MAP(CCanvas, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CCanvas::OnEraseBkgnd(CDC* bkgnd)
{
	return TRUE;
}

void CCanvas::OnCreate()
{
	m_defoultWidth = GetSystemMetrics(SM_CXSCREEN);
	m_defoultHeight = GetSystemMetrics(SM_CYSCREEN);
	m_pBackBuffer.reset(
		new Bitmap(m_defoultWidth, m_defoultHeight, PixelFormat32bppARGB));
	CRect r;
	GetClientRect(&r);
	m_defoultWidth = r.Width();
	m_defoultHeight = r.Height();

}


double CCanvas::GetScalingFactor(unsigned int canvasWidth, unsigned int canvasHeight, unsigned int photoWidth, unsigned int photoHeight)
{
	double horizontalScalingFactor = (double)(canvasWidth) / (double)photoWidth;
	double verticalScalingFactor = (double)(canvasHeight) / (double)photoHeight;
	return min(horizontalScalingFactor, verticalScalingFactor);
}

void CCanvas::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	if (m_pBitmap.get())
	{
		GetClientRect(&rc);
		unsigned canvasWidth = rc.Width();
		unsigned canvasHeight = rc.Height();
		double scalingFactor = 1;
		if ((m_defoultHeight <= canvasHeight) && (m_defoultWidth <= canvasWidth))
		{
			m_width = m_pBitmapOriginal->GetWidth();
			m_height = m_pBitmapOriginal->GetHeight();
		}
		else
		{
			if ((canvasWidth <= m_defoultWidth) || (canvasHeight <= m_defoultHeight) )
			{
				scalingFactor = GetScalingFactor(canvasWidth - 20, canvasHeight - 20, m_pBitmapOriginal->GetWidth(), m_pBitmapOriginal->GetHeight());
				m_width = m_pBitmapOriginal->GetWidth() * scalingFactor;
				m_height = m_pBitmapOriginal->GetHeight() * scalingFactor;
			}

			if ((m_width >= m_pBitmapOriginal->GetWidth()) || (m_height >= m_pBitmapOriginal->GetHeight()))
			{
				scalingFactor = 1;
				m_width = m_pBitmapOriginal->GetWidth();
				m_height = m_pBitmapOriginal->GetHeight();
			}
		}
		SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
		m_pBackBuffer.reset(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
		m_pBitmap.reset(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
		Gdiplus::Graphics graphic(m_pBitmap.get());
		graphic.Clear(Color(255, 255, 255));
		rc = NewRectCentralPosition(0);
		ChessBackground(rc);
		graphic.DrawImage(m_pBitmapOriginal.get(), rc.left, rc.top, rc.Width(), rc.Height());
		RedrawWindow();
	}
}

void CCanvas::RedrawBackBuffer()
{
	Graphics g(m_pBackBuffer.get());
	g.Clear(Color(255, 255, 255));
	g.DrawImage(m_pBitmap.get(), 0, 0);
}


void CCanvas::OnPaint()
{
	CPaintDC dc(this);
	RedrawBackBuffer();
	Graphics g(dc);
	CRect rc;
	if (m_pBitmap.get())
	{
		g.DrawImage(m_pBitmap.get(), 0, 0);
	}
}

RECT CCanvas::NewRectCentralPosition(const int border)
{
	CRect rc;
	rc.top = m_pBitmap->GetHeight() / 2 - m_height/2 + border/2;
	rc.left = m_pBitmap->GetWidth() / 2 - m_width/2 + border/ 2;
	rc.bottom = rc.top + m_height - border;
	rc.right = rc.left + m_width - border;
	return rc;
}

void CCanvas::ChessBackground(CRect rc)
{
	Graphics graphic(m_pBitmap.get());
	Gdiplus::SolidBrush brush(Gdiplus::Color(194, 194, 194));
	bool isBlack = true;
	INT w = (INT)(rc.Width() / 30), h = (INT)(rc.Width() / 30);
	INT count = 0;
	for (int i = rc.top; i < rc.bottom; i += w) 
	{
		w = (i + w > rc.bottom) ? rc.bottom - i : w;
		for (int j = rc.left; j < rc.right; j += h) {
			h = (j + h > rc.right) ? rc.right - j : h;
			if (isBlack) {
				graphic.FillRectangle(&brush, (INT)(j), (INT)(i), h, w);
				isBlack = false;
			}
			else
			{
				isBlack = true;
			}

		}
		isBlack = (count % 2 == 0) ? false : true;
		w = (INT)(rc.Width() / 30);
		h = (INT)(rc.Width() / 30);
		count++;
	}
}

void CCanvas::OpenFile(OPENFILENAME& ofn)
{
	CRect rc;
	Image img(ofn.lpstrFile);
	m_width = img.GetWidth();
	m_height = img.GetHeight();
	double scalingFactor = 1;
	double scalingFactorDefoult = 1;
	if (img.GetLastStatus() == Ok)
	{
		GetClientRect(&rc);
		SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOZORDER);
		m_pBitmap = std::auto_ptr<Bitmap>(new Bitmap(rc.Width(), rc.Height(), PixelFormat32bppARGB));
		Graphics g(m_pBitmap.get());
		g.Clear(Color(255, 255, 255));
		scalingFactor = GetScalingFactor(m_pBitmap->GetWidth(), m_pBitmap->GetHeight(), m_width, m_height);
		scalingFactorDefoult = GetScalingFactor(m_defoultWidth, m_defoultHeight, img.GetWidth(), img.GetHeight());
		if (scalingFactor > scalingFactorDefoult)
		{
			scalingFactor = scalingFactorDefoult;
		}
		m_width *= scalingFactor;
		m_height *= scalingFactor;
		rc = NewRectCentralPosition(20);
		m_width = rc.Width();
		m_height = rc.Height();
		ChessBackground(rc);
		g.DrawImage(&img, rc.left, rc.top, rc.Width(), rc.Height());
		scalingFactorDefoult = GetScalingFactor(m_defoultWidth, m_defoultHeight, img.GetWidth(), img.GetHeight());
		m_pBitmapOriginal = std::auto_ptr<Bitmap>(new Bitmap(img.GetWidth() * scalingFactorDefoult, img.GetHeight() * scalingFactor, PixelFormat32bppARGB));
		Graphics g2(m_pBitmapOriginal.get());
		g2.DrawImage(&img, 0, 0, (INT)(img.GetWidth()*scalingFactorDefoult), (INT)(img.GetHeight()*scalingFactorDefoult));
		RedrawWindow();
	}
}


void CCanvas::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON)
	{
		CPaintDC dc(this);
		CPen NewPen(PS_SOLID, 5, RGB(0, 0, 255));
		dc.SelectObject(&NewPen);
		dc.MoveTo(m_PointX, m_PointY);
		dc.LineTo(point.x, point.y);
		m_PointX = point.x;
		m_PointY = point.y;
	}
	CDialogEx::OnMouseMove(nFlags, point); //присутствует по умолчанию
}

void CCanvas::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_PointX = point.x;
	m_PointY = point.y;
	CDialogEx::OnLButtonDown(nFlags, point);
}
