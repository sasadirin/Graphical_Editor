
// Labaratornya7View.cpp : implementation of the CLabaratornya7View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Labaratornya7.h"
#endif

#include "Labaratornya7Doc.h"
#include "Labaratornya7View.h"
#include "direct.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLabaratornya7View

IMPLEMENT_DYNCREATE(CLabaratornya7View, CView)

BEGIN_MESSAGE_MAP(CLabaratornya7View, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_NEW, &CLabaratornya7View::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CLabaratornya7View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CLabaratornya7View::OnFileSave)
	ON_COMMAND(ID_CHOSECOLOUR, &CLabaratornya7View::OnChosecolour)
	ON_COMMAND(ID_CHANGEWIDTH, &CLabaratornya7View::OnChangewidth)
	ON_COMMAND(ID_CHOSESTYLE, &CLabaratornya7View::OnChosestyle)
	ON_COMMAND(ID_CLEAR, &CLabaratornya7View::OnClear)
	ON_COMMAND(ID_FREEPEN, &CLabaratornya7View::OnFreepen)
	ON_COMMAND(ID_RECTPEN, &CLabaratornya7View::OnRectpen)
	ON_COMMAND(ID_PENLINE, &CLabaratornya7View::OnPenline)
	ON_COMMAND(ID_PENELLIPSE, &CLabaratornya7View::OnPenellipse)
	ON_COMMAND(ID_TRIANGLEPEN, &CLabaratornya7View::OnTrianglepen)
	ON_COMMAND(ID_TRIGON, &CLabaratornya7View::OnTrigon)
	ON_COMMAND(ID_POLYGONPEN, &CLabaratornya7View::OnPolygonpen)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CLabaratornya7View construction/destruction

CLabaratornya7View::CLabaratornya7View()
{
	// TODO: add construction code here
	IsDrawing=0;
	PenColor=1;
	PenWidth=1;
	PenStyle=0;
	PenMode=0;
	poly=FALSE;
}

CLabaratornya7View::~CLabaratornya7View()
{
}

BOOL CLabaratornya7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLabaratornya7View drawing

void CLabaratornya7View::OnDraw(CDC* pDC)
{
	CLabaratornya7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	HMETAFILE hmeta = pDoc->pmetaDC->Close();
	pDC->PlayMetaFile(hmeta);
	pDoc->pmetaDC->Create();
	pDoc->pmetaDC->PlayMetaFile(hmeta);
	DeleteMetaFile(hmeta);
}


// CLabaratornya7View diagnostics

#ifdef _DEBUG
void CLabaratornya7View::AssertValid() const
{
	CView::AssertValid();
}

void CLabaratornya7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLabaratornya7Doc* CLabaratornya7View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLabaratornya7Doc)));
	return (CLabaratornya7Doc*)m_pDocument;
}
#endif //_DEBUG


// CLabaratornya7View message handlers


void CLabaratornya7View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	IsDrawing=true;
	pe=point;
	begin=point;
	SetCapture();
	
	CPen Pen;
	Pen.DeleteObject();
	Pen.CreatePen(PenStyle,PenWidth,PenColor);
	
	
	
	if(PenMode==6){
		if(poly){
			end=point;
			CClientDC *pDC=new CClientDC(this);
			pDC->SelectObject(Pen);
			pDC->MoveTo(polybegin.x,polybegin.y);
			pDC->LineTo(end.x,end.y);

			CLabaratornya7Doc* pDoc=GetDocument();
			pDoc->pmetaDC->SetAttribDC(*pDC);
			pDoc->pmetaDC->SelectObject(&Pen);
			pDoc->pmetaDC->MoveTo(polybegin.x,polybegin.y);
			pDoc->pmetaDC->LineTo(end.x,end.y);
			polybegin=point;
		}
		else{
			poly=TRUE;
			polybegin=point;
		}

		
	}
}


void CLabaratornya7View::OnClear()
{
	// TODO: добавьте свой код обработчика команд
	CClientDC *pDC=new CClientDC(this);
	pDC->SelectStockObject(NULL_PEN);
	pDC->Rectangle(0,0,10000,10000);
	CLabaratornya7Doc* pDoc=GetDocument();
	pDoc->pmetaDC->Rectangle(0,0,10000,10000);

}

void CLabaratornya7View::OnLButtonUp(UINT nFlags, CPoint point)
{
		end=point;
		CClientDC dc(this);
		
		Pen.DeleteObject();
		Pen.CreatePen(PenStyle,PenWidth,PenColor);
		CPen *pOldPen=dc.SelectObject(&Pen);		
		CLabaratornya7Doc* pDoc=GetDocument();
		
		pDoc->pmetaDC->SetAttribDC(dc);
		pDoc->pmetaDC->SelectObject(&Pen);

		if(PenMode==1){
			pDoc->pmetaDC->Rectangle(begin.x,begin.y,point.x,point.y);
			dc.Rectangle(begin.x,begin.y,point.x,point.y);

		}
		if(PenMode==3){
			pDoc->pmetaDC->Ellipse(begin.x,begin.y,point.x,point.y);
			dc.Ellipse(begin.x,begin.y,point.x,point.y);
		}
		if(PenMode==2){
			dc.MoveTo(begin.x,begin.y);
			dc.LineTo(end.x,end.y);
			pDoc->pmetaDC->MoveTo(begin.x,begin.y);
			pDoc->pmetaDC->LineTo(end.x,end.y);
		}
		if(PenMode==4){
			dc.MoveTo(begin.x,begin.y);
			dc.LineTo(end.x,end.y);
			dc.MoveTo(end.x,end.y);
			dc.LineTo(begin.x,end.y);
			dc.MoveTo(begin.x,end.y);
			dc.LineTo(begin.x,begin.y);

			pDoc->pmetaDC->MoveTo(begin.x,begin.y);
			pDoc->pmetaDC->LineTo(end.x,end.y);
			pDoc->pmetaDC->MoveTo(end.x,end.y);
			pDoc->pmetaDC->LineTo(begin.x,end.y);
			pDoc->pmetaDC->MoveTo(begin.x,end.y);
			pDoc->pmetaDC->LineTo(begin.x,begin.y);
		}
		if(PenMode==5){

			//To Screen
			dc.MoveTo(begin.x,begin.y);
			dc.LineTo(end.x,end.y);
			dc.MoveTo(end.x,end.y);
			if(begin.x<end.x){
				dc.LineTo(end.x+abs(begin.x-end.x),begin.y);
				dc.MoveTo(end.x+abs(begin.x-end.x),begin.y);
				dc.LineTo(begin.x,begin.y);
			}
			else if(begin.x>end.x){
				dc.LineTo(end.x-abs(begin.x-end.x),begin.y);
				dc.MoveTo(end.x-abs(begin.x-end.x),begin.y);
				dc.LineTo(begin.x,begin.y);
			}

			//To Meta
			pDoc->pmetaDC->MoveTo(begin.x,begin.y);
			pDoc->pmetaDC->LineTo(end.x,end.y);
			pDoc->pmetaDC->MoveTo(end.x,end.y);
			if(begin.x<end.x){
				pDoc->pmetaDC->LineTo(end.x+abs(begin.x-end.x),begin.y);
				pDoc->pmetaDC->MoveTo(end.x+abs(begin.x-end.x),begin.y);
				pDoc->pmetaDC->LineTo(begin.x,begin.y);
			}
			else if(begin.x>end.x){
				pDoc->pmetaDC->LineTo(end.x-abs(begin.x-end.x),begin.y);
				pDoc->pmetaDC->MoveTo(end.x-abs(begin.x-end.x),begin.y);
				pDoc->pmetaDC->LineTo(begin.x,begin.y);
			}
		
		}
		dc.SelectObject(pOldPen);
		Pen.DeleteObject();
		if(PenMode!=6){	IsDrawing=false;}
		ReleaseCapture();
		begin=end;
		this->Invalidate();

}


void CLabaratornya7View::OnMouseMove(UINT nFlags, CPoint point)
{
			CClientDC dc(this);
			if( PenMode==6 && IsDrawing ){
				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(pe.x,pe.y);

				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,PenColor);
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(point.x,point.y);
				pe=point;
			}
				pb=begin;
				Pen.DeleteObject();//PenStyle,PenWidth,PenColor
				Pen.CreatePen(PenStyle,PenWidth,PenColor);
				dc.SelectObject(Pen);
				
		if(IsDrawing && (nFlags & MK_LBUTTON ) ){
			if(PenMode==0){
				dc.MoveTo(begin);
				dc.LineTo(point);
				CLabaratornya7Doc* pDoc=GetDocument();
				pDoc->pmetaDC->SetAttribDC(dc);
				pDoc->pmetaDC->SelectObject(&Pen);
				pDoc->pmetaDC->MoveTo(begin);
				pDoc->pmetaDC->LineTo(point);
				begin=point;
			}
			if(PenMode==1){
					Pen.DeleteObject();
					Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
					dc.SelectObject(Pen);
					dc.Rectangle(begin.x,begin.y,pe.x,pe.y);

					Pen.DeleteObject();
					Pen.CreatePen(PenStyle,PenWidth,PenColor);
					dc.SelectObject(Pen);
					dc.Rectangle(begin.x,begin.y,point.x,point.y);
			}
			if(PenMode==3){
					Pen.DeleteObject();
					Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
					dc.SelectObject(Pen);
					dc.Ellipse(begin.x,begin.y,pe.x,pe.y);

					Pen.DeleteObject();
					Pen.CreatePen(PenStyle,PenWidth,PenColor);
					dc.SelectObject(Pen);
					dc.Ellipse(begin.x,begin.y,point.x,point.y);

			}
			if( PenMode==2 ){
				
				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(pe.x,pe.y);
				
				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,PenColor);
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(point.x,point.y);
			}
			
			if(PenMode==4){
				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(pe.x,pe.y);
				dc.MoveTo(pe.x,pe.y);
				dc.LineTo(begin.x,pe.y);
				dc.MoveTo(begin.x,pe.y);
				dc.LineTo(begin.x,begin.y);


				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,PenColor);
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(point.x,point.y);
				dc.MoveTo(point.x,point.y);
				dc.LineTo(begin.x,point.y);
				dc.MoveTo(begin.x,point.y);
				dc.LineTo(begin.x,begin.y);
			}
			if(PenMode==5){

				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(pe.x,pe.y);
				dc.MoveTo(pe.x,pe.y);
				if(begin.x<pe.x){
					dc.LineTo(pe.x+abs(begin.x-pe.x),begin.y);
					dc.MoveTo(pe.x+abs(begin.x-pe.x),begin.y);
					dc.LineTo(begin.x,begin.y);
				}
				else if(begin.x>end.x){
					dc.LineTo(pe.x-abs(begin.x-pe.x),begin.y);
					dc.MoveTo(pe.x-abs(begin.x-pe.x),begin.y);
					dc.LineTo(begin.x,begin.y);
				}



				Pen.DeleteObject();
				Pen.CreatePen(PenStyle,PenWidth,PenColor);
				dc.SelectObject(Pen);
				dc.MoveTo(begin.x,begin.y);
				dc.LineTo(point.x,point.y);
				dc.MoveTo(point.x,point.y);
				if(begin.x<point.x){
					dc.LineTo(point.x+abs(begin.x-point.x),begin.y);
					dc.MoveTo(point.x+abs(begin.x-point.x),begin.y);
					dc.LineTo(begin.x,begin.y);
				}
				else if(begin.x>end.x){
					dc.LineTo(point.x-abs(begin.x-point.x),begin.y);
					dc.MoveTo(point.x-abs(begin.x-point.x),begin.y);
					dc.LineTo(begin.x,begin.y);
				}
			}
			pe=point;
		
		}
}


void CLabaratornya7View::OnFileNew()
{
	// TODO: добавьте свой код обработчика команд
	CLabaratornya7Doc* pDoc=GetDocument();
	file="";
	theApp.m_pMainWnd->SetWindowText(theApp.deffile);
	pDoc->pmetaDC->Close();
	pDoc->pmetaDC->Create();
	this->Invalidate();

}


void CLabaratornya7View::OnFileOpen()
{
	// TODO: добавьте свой код обработчика команд
	CLabaratornya7Doc* pDoc=GetDocument();
	CFileDialog fd(true);
	fd.m_ofn.Flags |=OFN_FILEMUSTEXIST;
	fd.m_ofn.lpstrTitle=L"Open WMF file";
	fd.m_ofn.lpstrFilter=L"Grafic files(*.wmf)\0*.wmf";
	fd.m_ofn.lpstrInitialDir=NULL;
	if(fd.DoModal()==IDCANCEL)
		return;
	file=fd.m_ofn.lpstrFile;
	CString shortfile = fd.m_ofn.lpstrFileTitle;
	shortfile+=" - ";
	shortfile+=theApp.m_pszAppName;
	theApp.m_pMainWnd->SetWindowText(shortfile);
	HMETAFILE hmeta=GetMetaFile(file);
	pDoc->pmetaDC->Close();
	pDoc->pmetaDC->Create();
	pDoc->pmetaDC->PlayMetaFile(hmeta);
	DeleteMetaFile(hmeta);
	this->Invalidate();
}


void CLabaratornya7View::OnFileSave()
{
	// TODO: добавьте свой код обработчика команд
	CLabaratornya7Doc* pDoc=GetDocument();
	static CString oldfile = L"?";
	if(oldfile!=file){
		CFileDialog fd(false,L"wmf",L"default");
		fd.m_ofn.lpstrTitle=L"Save WMF file";
		fd.m_ofn.lpstrFilter=L"Grafic files(*.wmf)\0*.wmf";
		fd.m_ofn.lpstrInitialDir=NULL;
		if(fd.DoModal()==IDCANCEL)
			return;
		file=oldfile=fd.m_ofn.lpstrFile;
		CString shortfile=fd.m_ofn.lpstrFileTitle;
		shortfile+=" - ";
		shortfile+=theApp.m_pszAppName;
		theApp.m_pMainWnd->SetWindowText(shortfile);
	}
	HMETAFILE hmeta=pDoc->pmetaDC->Close();
	hmeta=CopyMetaFile(hmeta,file);
	pDoc->pmetaDC->Create();
	pDoc->pmetaDC->PlayMetaFile(hmeta);
	DeleteMetaFile(hmeta);
	

}


void CLabaratornya7View::OnChosecolour()
{
	CColorDialog dlg(PenColor);
	if(dlg.DoModal()==IDOK){
		PenColor=dlg.GetColor();
	}
	
	// TODO: добавьте свой код обработчика команд
}


class CChangeWidthDlg : public CDialogEx
{
public:
	CChangeWidthDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_Width;
};

CChangeWidthDlg::CChangeWidthDlg() : CDialogEx(CChangeWidthDlg::IDD)
	, m_Width(0)
{
}

void CChangeWidthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Width);
}

BEGIN_MESSAGE_MAP(CChangeWidthDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CLabaratornya7App::OnChangeWidth()
{
	
}

void CLabaratornya7View::OnChangewidth()
{
	//PenWidth
	CChangeWidthDlg WidthDlg;
	if(WidthDlg.DoModal()==IDOK)
	PenWidth=WidthDlg.m_Width;
	// TODO: добавьте свой код обработчика команд
}




class CChangeStyleDlg : public CDialogEx
{
public:
	CChangeStyleDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	
//	int m_Style;
	int m_Style;
};

CChangeStyleDlg::CChangeStyleDlg() : CDialogEx(CChangeStyleDlg::IDD)

	, m_Style(0)
	
{
}

void CChangeStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Style);
	DDV_MinMaxInt(pDX, m_Style, 0, 6);
}

BEGIN_MESSAGE_MAP(CChangeStyleDlg, CDialogEx)
END_MESSAGE_MAP()

void CLabaratornya7View::OnChosestyle()
{
	CChangeStyleDlg StyleDlg;
	if(StyleDlg.DoModal()==IDOK)
	PenStyle=StyleDlg.m_Style;
}



void CLabaratornya7View::OnFreepen()
{
	PenMode=0;
}


void CLabaratornya7View::OnRectpen()
{
	PenMode=1;
}


void CLabaratornya7View::OnPenline()
{
	PenMode=2;
}




void CLabaratornya7View::OnPenellipse()
{
	PenMode=3;
}


void CLabaratornya7View::OnTrianglepen()
{
	PenMode=4;
}


void CLabaratornya7View::OnTrigon()
{
	PenMode=5;
	
}


void CLabaratornya7View::OnPolygonpen()
{
	PenMode=6;
	
}


void CLabaratornya7View::OnRButtonDown(UINT nFlags, CPoint point)
{
	poly=FALSE;
	if(PenMode==6){
		IsDrawing=FALSE;
		CClientDC dc(this);
		Pen.DeleteObject();
		Pen.CreatePen(PenStyle,PenWidth,RGB(255,255,255));
		dc.SelectObject(Pen);
		dc.MoveTo(begin.x,begin.y);
		dc.LineTo(pe.x,pe.y);
	}
}
