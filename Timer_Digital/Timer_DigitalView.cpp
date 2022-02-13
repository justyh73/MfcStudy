
// Timer_DigitalView.cpp: CTimerDigitalView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Timer_Digital.h"
#endif

#include "Timer_DigitalDoc.h"
#include "Timer_DigitalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimerDigitalView

IMPLEMENT_DYNCREATE(CTimerDigitalView, CView)

BEGIN_MESSAGE_MAP(CTimerDigitalView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTimerDigitalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTimerDigitalView 생성/소멸

CTimerDigitalView::CTimerDigitalView() noexcept
	:m_bTimerRun(false)
	,m_bTimerType(true)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTimerDigitalView::~CTimerDigitalView()
{
}

BOOL CTimerDigitalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTimerDigitalView 그리기

void CTimerDigitalView::OnDraw(CDC* pDC)
{
	CTimerDigitalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CRect rect;
	GetClientRect(&rect);

	pDC->DrawText(m_strTimer, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}


// CTimerDigitalView 인쇄


void CTimerDigitalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTimerDigitalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTimerDigitalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTimerDigitalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTimerDigitalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTimerDigitalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTimerDigitalView 진단

#ifdef _DEBUG
void CTimerDigitalView::AssertValid() const
{
	CView::AssertValid();
}

void CTimerDigitalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTimerDigitalDoc* CTimerDigitalView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTimerDigitalDoc)));
	return (CTimerDigitalDoc*)m_pDocument;
}
#endif //_DEBUG


// CTimerDigitalView 메시지 처리기


int CTimerDigitalView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 1000, NULL);
	m_bTimerRun = TRUE;

	return 0;
}


void CTimerDigitalView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int hour;
	CString str;
	CTime timer;
	timer = CTime::GetTickCount();

	if (m_bTimerType) {
		m_strTimer.Format(_T("현재는 %d년 %d월 %d일 %d시 %d분 %d초"),
			timer.GetYear(), timer.GetMonth(), timer.GetDay(), timer.GetHour(), timer.GetMinute(), timer.GetSecond()
		);
	}
	else {
		hour = timer.GetTime();

		if (hour >= 12) {
			str = _T("PM");

			if (hour >= 13) {
				hour = hour - 12;
			}
		}
		else {
			str = _T("AM");
		}

		m_strTimer.Format(_T("지금은 %s %d %d %초"), str, hour,
			timer.GetMinute(), timer.GetSecond());
	}

	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CTimerDigitalView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(0);
}
