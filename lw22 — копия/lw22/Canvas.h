#pragma once
#include <memory>

// CCanvas

class CCanvas : public CDialogEx
{
	DECLARE_DYNAMIC(CCanvas)

public:
	CCanvas();
	virtual ~CCanvas();
	afx_msg void OnPaint();
	void OpenFile(OPENFILENAME& ofn);
	double GetScalingFactor(unsigned int canvasWidth, unsigned int canvasHeight, unsigned int photoWidth, unsigned int photoHeight);
	void OnSize(UINT nType, int cx, int cy);
	void OnCreate();
	void RedrawBackBuffer();
	RECT NewRectCentralPosition(const int border);
	void ChessBackground(CRect rc);
private:
	afx_msg BOOL OnEraseBkgnd(CDC* bkgnd);
	std::auto_ptr<Gdiplus::Bitmap> m_pBitmap;
	std::auto_ptr<Gdiplus::Bitmap> m_pBackBuffer;
	std::auto_ptr<Gdiplus::Bitmap> m_pBitmapOriginal;
	UINT m_width = 0;
	UINT m_height = 0;
	UINT m_defoultWidth = 0;
	UINT m_defoultHeight = 0;
	int m_PointX = 0;
	int m_PointY = 0;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


