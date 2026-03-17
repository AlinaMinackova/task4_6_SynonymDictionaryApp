
// SynonymDictionaryAppView.h: интерфейс класса CSynonymDictionaryAppView
//

#pragma once


class CSynonymDictionaryAppView : public CView
{
protected: // создать только из сериализации
	CSynonymDictionaryAppView() noexcept;
	DECLARE_DYNCREATE(CSynonymDictionaryAppView)

// Атрибуты
public:
	CSynonymDictionaryAppDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CSynonymDictionaryAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProcessFiles();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // версия отладки в SynonymDictionaryAppView.cpp
inline CSynonymDictionaryAppDoc* CSynonymDictionaryAppView::GetDocument() const
   { return reinterpret_cast<CSynonymDictionaryAppDoc*>(m_pDocument); }
#endif

