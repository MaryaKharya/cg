
// lw1Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно Clw1Dlg
class Clw1Dlg : public CDialogEx
{
// Создание
public:
	Clw1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LW1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	void DrawTable(CDC& dc);
	void DrawChairs(CDC& dc);
	void DrawTableware(CDC& dc);
	void DrawFlowers(CDC& dc);
	void DrawShadow(CDC& dc);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
