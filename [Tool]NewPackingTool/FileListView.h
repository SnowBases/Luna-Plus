#pragma once


// CFileListView ���Դϴ�.

class CFileListView : public CListView
{
	DECLARE_DYNCREATE(CFileListView)

protected:
	CFileListView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CFileListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


