
// SynonymDictionaryAppDoc.cpp: реализация класса CSynonymDictionaryAppDoc 
//

#include "pch.h"
#include "framework.h"
#include <afxdlgs.h>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SynonymDictionaryApp.h"
#endif

#include "SynonymDictionaryAppDoc.h"

#include <propkey.h>
#include "Logger.h"

#include <fstream>
#include <sstream>
#include <iterator>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSynonymDictionaryAppDoc

IMPLEMENT_DYNCREATE(CSynonymDictionaryAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CSynonymDictionaryAppDoc, CDocument)
END_MESSAGE_MAP()

void CSynonymDictionaryAppDoc::ProcessFiles(const std::string& inputFile,
	const std::string& synonymFile,
	const std::string& outputFile)
{
	try
	{
		CLogger::Instance().Log(LogLevel::Info, "Processing started");

		m_dictionary.LoadFromFile(synonymFile);

		std::ifstream input(inputFile);
		if (!input.is_open())
			throw std::runtime_error("Cannot open input file");

		std::ofstream output(outputFile);
		if (!output.is_open())
			throw std::runtime_error("Cannot open output file");

		std::string word;

		while (input >> word)
		{
			std::string replaced = m_dictionary.GetRandomSynonym(word);
			output << replaced << " ";
		}

		CLogger::Instance().Log(LogLevel::Info, "Processing finished successfully");
	}
	catch (const std::exception& ex)
	{
		CLogger::Instance().Log(LogLevel::Error, ex.what());
		AfxMessageBox(CA2W(ex.what()));
	}
}


// Создание или уничтожение CSynonymDictionaryAppDoc

CSynonymDictionaryAppDoc::CSynonymDictionaryAppDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CSynonymDictionaryAppDoc::~CSynonymDictionaryAppDoc()
{
}

BOOL CSynonymDictionaryAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CSynonymDictionaryAppDoc

void CSynonymDictionaryAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSynonymDictionaryAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSynonymDictionaryAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSynonymDictionaryAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSynonymDictionaryAppDoc

#ifdef _DEBUG
void CSynonymDictionaryAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSynonymDictionaryAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSynonymDictionaryAppDoc
