
// SynonymDictionaryAppDoc.h: интерфейс класса CSynonymDictionaryAppDoc 
//


#pragma once
#include "SynonymDictionary.h"

class CSynonymDictionaryAppDoc : public CDocument
{
protected: // создать только из сериализации
	CSynonymDictionaryAppDoc() noexcept;
	DECLARE_DYNCREATE(CSynonymDictionaryAppDoc)

protected:
	CSynonymDictionary m_dictionary;

public:
	void ProcessFiles(const std::string& inputFile,
		const std::string& synonymFile,
		const std::string& outputFile);

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSynonymDictionaryAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
