
// Timer_DigitalView.h: CTimerDigitalView 클래스의 인터페이스
//

#pragma once


class CTimerDigitalView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTimerDigitalView() noexcept;
	DECLARE_DYNCREATE(CTimerDigitalView)

// 특성입니다.
public:
	CTimerDigitalDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CTimerDigitalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	bool m_bTimerRun;
	bool m_bTimerType;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CString m_strTimer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // Timer_DigitalView.cpp의 디버그 버전
inline CTimerDigitalDoc* CTimerDigitalView::GetDocument() const
   { return reinterpret_cast<CTimerDigitalDoc*>(m_pDocument); }
#endif

