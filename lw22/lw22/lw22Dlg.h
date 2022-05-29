#pragma once
#include "Canvas.h"
#include "resource.h"
#include <memory>

// Диалоговое окно Clw22Dlg
class Clw22Dlg : public CDialogEx
{
// Создание
public:
	Clw22Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LW22_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	CCanvas m_canvas;
	//BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//BOOL OnEraseBkgnd(CDC* bkgnd);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveas();
	CMenu m_menu;
};
