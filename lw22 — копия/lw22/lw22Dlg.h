#pragma once
//#include "Canvas.h"
#include "resource.h"
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

// Диалоговое окно Clw22Dlg
class Clw22Dlg : public CDialogEx
{
// Создание
public:
	Clw22Dlg(CDialogEx* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LW22_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


private:
	CStatic m_canvas;
// Реализация
protected:
	HICON m_hIcon;

	//CCanvas m_canvas;
	//BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	void RedrawBackBuffer();
	BOOL OnEraseBkgnd(CDC* bkgnd);
	//BOOL OnEraseBkgnd(CDC* bkgnd);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileOpen();
	std::wstring GetFileExtension(std::wstring const& fileName);
	afx_msg	void InitFileNameStructure(OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);
	//void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);
	void OnFileSaveas();
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnNewFile();
	CMenu m_menu;
	std::auto_ptr<Gdiplus::Bitmap> m_pBitmap;
	std::auto_ptr<Gdiplus::Bitmap> m_pBackBuffer;
	std::auto_ptr<Gdiplus::Bitmap> m_pBitmapOriginal;
	std::auto_ptr<Gdiplus::Bitmap> m_pB;
	int m_PointX = 0;
	int m_PointY = 0;
	int m_size = 0;
	HINSTANCE g_hInstance;
	CMFCColorButton m_color;
	//afx_msg void OnEnChangeEdit1();
	int thick;
	afx_msg void OnEnKillfocusEdit1();
	bool m_fileOpen = false;
};
