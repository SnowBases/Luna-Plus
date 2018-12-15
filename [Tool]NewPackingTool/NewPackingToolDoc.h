// NewPackingToolDoc.h : CNewPackingToolDoc Ŭ������ �������̽�
//


#pragma once

#include "stdafx.h"

class CNewPackingToolDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CNewPackingToolDoc();
	DECLARE_DYNCREATE(CNewPackingToolDoc)

// Ư��
public:

// �۾�
public:

// ������
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ����
public:
	virtual ~CNewPackingToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL	OnOpenDocument(LPCTSTR lpszPathName);

	afx_msg void	OnFileNew();
	afx_msg void	OnFileSave();
	afx_msg void	OnFileSaveAs();

	//void			AddOutStr(LPTSTR str);
	char*			GetData(int index);
	void			SaveData(int index, LPTSTR str);
	void			SelChange(int index, BOOL modified);

public:
	CMHFileMng		m_FileMng;
	int				m_nFileNum;

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};


