
// SynonymDictionaryAppView.cpp: реализация класса CSynonymDictionaryAppView
//
#include "resource.h"
#include <afxdlgs.h> 
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SynonymDictionaryApp.h"
#endif

#include "SynonymDictionaryAppDoc.h"
#include "SynonymDictionaryAppView.h"

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSynonymDictionaryAppView

IMPLEMENT_DYNCREATE(CSynonymDictionaryAppView, CView)

BEGIN_MESSAGE_MAP(CSynonymDictionaryAppView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSynonymDictionaryAppView::OnFilePrintPreview)
	ON_COMMAND(ID_PROCESS_FILES, &CSynonymDictionaryAppView::OnProcessFiles)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

void CSynonymDictionaryAppView::OnProcessFiles()
{
    // Выбор исходного файла
    CFileDialog dlgInput(TRUE, L".txt", nullptr,
        OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
    if (dlgInput.DoModal() != IDOK)
        return;
    CString inputPath = dlgInput.GetPathName();

    // Выбор файла синонимов
    CFileDialog dlgSyn(TRUE, L".txt", nullptr,
        OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
    if (dlgSyn.DoModal() != IDOK)
        return;
    CString synonymsPath = dlgSyn.GetPathName();

    // Выбор выходного файла
    CFileDialog dlgOutput(FALSE, L".txt", L"output.txt",
        OFN_OVERWRITEPROMPT,
        L"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||");
    if (dlgOutput.DoModal() != IDOK)
        return;
    CString outputPath = dlgOutput.GetPathName();

    // Вызов метода документа
    auto pDoc = GetDocument();
    pDoc->ProcessFiles(
        std::string(CT2A(inputPath)),
        std::string(CT2A(synonymsPath)),
        std::string(CT2A(outputPath))
    );

    AfxMessageBox(L"Обработка завершена!");
}

// Создание или уничтожение CSynonymDictionaryAppView

CSynonymDictionaryAppView::CSynonymDictionaryAppView() noexcept
{
	// TODO: добавьте код создания

}

CSynonymDictionaryAppView::~CSynonymDictionaryAppView()
{
}

BOOL CSynonymDictionaryAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSynonymDictionaryAppView

void CSynonymDictionaryAppView::OnDraw(CDC* /*pDC*/)
{
	CSynonymDictionaryAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CSynonymDictionaryAppView


void CSynonymDictionaryAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSynonymDictionaryAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSynonymDictionaryAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSynonymDictionaryAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CSynonymDictionaryAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSynonymDictionaryAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CSynonymDictionaryAppView

#ifdef _DEBUG
void CSynonymDictionaryAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSynonymDictionaryAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSynonymDictionaryAppDoc* CSynonymDictionaryAppView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSynonymDictionaryAppDoc)));
	return (CSynonymDictionaryAppDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSynonymDictionaryAppView
