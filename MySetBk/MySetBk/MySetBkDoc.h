// MySetBkDoc.h : CMySetBkDoc ��Ľӿ�
//


#pragma once


class CMySetBkDoc : public CDocument
{
protected: // �������л�����
	CMySetBkDoc();
	DECLARE_DYNCREATE(CMySetBkDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMySetBkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


