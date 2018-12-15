// NewPackingToolView.h : iCNewPackingToolView Ŭ������ �������̽�
//


#pragma once

#include "ScriptTest.h"
#include "ScriptTestStr.h"

class CNewPackingToolView : public CEditView
{
protected: // serialization������ ��������ϴ�.
	CNewPackingToolView();
	DECLARE_DYNCREATE(CNewPackingToolView)

// Ư��
public:
	CNewPackingToolDoc* GetDocument() const;

// �۾�
public:

// ������
	public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ����
public:
	virtual ~CNewPackingToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	virtual void OnInitialUpdate();
	void	SelChange(int index);
	void	MoveLine(int line);
	int		GetCurIndex() { return m_curIndex; }

	int		CheckScript(UINT modeType);
	void	ScriptTest(UINT testType);

public:
	int		m_curIndex;
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // NewPackingToolView.cpp�� ����� ����
inline CNewPackingToolDoc* CNewPackingToolView::GetDocument() const
   { return reinterpret_cast<CNewPackingToolDoc*>(m_pDocument); }
#endif

