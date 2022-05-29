
// lw2_2View.cpp: реализация класса Clw22View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "lw2_2.h"
#endif

#include "lw2_2Doc.h"
#include "lw2_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clw22View

IMPLEMENT_DYNCREATE(Clw22View, CView)

BEGIN_MESSAGE_MAP(Clw22View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Clw22View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение Clw22View

Clw22View::Clw22View() noexcept
{
	// TODO: добавьте код создания

}

Clw22View::~Clw22View()
{
}

BOOL Clw22View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование Clw22View

void Clw22View::OnDraw(CDC* /*pDC*/)
{
	Clw22Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать Clw22View


void Clw22View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Clw22View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void Clw22View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void Clw22View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void Clw22View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Clw22View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика Clw22View

#ifdef _DEBUG
void Clw22View::AssertValid() const
{
	CView::AssertValid();
}

void Clw22View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clw22Doc* Clw22View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clw22Doc)));
	return (Clw22Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений Clw22View
