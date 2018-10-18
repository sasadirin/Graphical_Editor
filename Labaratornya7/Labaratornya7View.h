
// Labaratornya7View.h : interface of the CLabaratornya7View class
//

#pragma once


class CLabaratornya7View : public CView
{
private:
	CPen Pen;
	int PenColor;
	int PenWidth;
	int PenStyle;
	bool IsDrawing;
	int PenMode;
protected: // create from serialization only
	CLabaratornya7View();
	DECLARE_DYNCREATE(CLabaratornya7View)

// Attributes
public:
	CLabaratornya7Doc* GetDocument() const;
	CPoint begin,end,polybegin,pb,pe;
	bool poly;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CLabaratornya7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
	CString file;
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnChosecolour();
	afx_msg void OnChangewidth();
	afx_msg void OnChosestyle();
	afx_msg void OnClear();
	afx_msg void OnFreepen();
	afx_msg void OnRectpen();
	afx_msg void OnPenline();
	afx_msg void OnChangepenmodeEllipsepen();
	afx_msg void OnPenellipse();
	afx_msg void OnTrianglepen();
	afx_msg void OnTrigon();
	afx_msg void OnPolygonpen();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Labaratornya7View.cpp
inline CLabaratornya7Doc* CLabaratornya7View::GetDocument() const
   { return reinterpret_cast<CLabaratornya7Doc*>(m_pDocument); }
#endif

