// TariffInbaseView.h : interface of the CTariffInbaseView class
//
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_TARIFFINBASEVIEW_H__6CDB62DA_43E6_44FD_ABEE_347EA2552F89__INCLUDED_)
#define AFX_TARIFFINBASEVIEW_H__6CDB62DA_43E6_44FD_ABEE_347EA2552F89__INCLUDED_

#include "TTfileBase.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct _AMA_FORMAT
	{
		BYTE HEADER;
		BYTE Anomber[15];
		BYTE AnomberCategory[2];
		BYTE spare0[4];
		BYTE Bnomber[32];
		BYTE date[6];
		BYTE time[6];
		BYTE duration[6];
		BYTE IncomingRouteName[8];
		BYTE IncCircNomb[4];
		BYTE OutgoingRouteName[8];
		BYTE OutCircNomb[4];
		BYTE ChargeMeter[7];
		BYTE MBI[3];
		BYTE RATE;
		BYTE CALL_TYPE;
		BYTE spare1[2];
		BYTE ServiceCategory[2];
		BYTE spare2;
		BYTE spare3[2];
		BYTE spare4;
		BYTE spare5[12];
	} AMA_FORMAT;

typedef struct __AMA_FORMAT
	{
		BYTE HEADER[2];
		BYTE Anomber[16];
		BYTE AnomberCategory[3];
		BYTE spare0[5];
		BYTE Bnomber[33];
		BYTE date[7];
		BYTE time[7];
		BYTE duration[7];
		BYTE IncomingRouteName[9];
		BYTE IncCircNomb[5];
		BYTE OutgoingRouteName[9];
		BYTE OutCircNomb[5];
		BYTE ChargeMeter[8];
		BYTE MBI[4];
		BYTE RATE[2];
		BYTE CALL_TYPE[2];
		BYTE spare1[3];
		BYTE ServiceCategory[4];
		BYTE spare2[2];
		BYTE spare3[3];
		BYTE spare4[2];
		BYTE spare5[13];
		BYTE END[2];
	} AMA_FORMAT_MY;

class CTariffInbaseSet;

class CTariffInbaseView : public CRecordView
{
protected: // create from serialization only
	CTariffInbaseView();
	DECLARE_DYNCREATE(CTariffInbaseView)

public:
	//{{AFX_DATA(CTariffInbaseView)
	enum { IDD = IDD_TARIFFINBASE_FORM };
	CStatic	m_cTimeRecInBase;
	CStatic	m_cTimeRecFromFile;
	CStatic	m_cNomberStrings;
	CStatic	m_cEnd;
	CStatic	m_cBegin;
	CProgressCtrl	m_cProgress2;
	CProgressCtrl	m_cProgress1;
	CTariffInbaseSet* m_pSet;
	CTTfileBase* m_pSetTtfile;
	//}}AFX_DATA

// Attributes
public:
	CTariffInbaseDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTariffInbaseView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	int LogLineAdd(CString line);
	CString RejectAllSimbols(CString linewithsimb);
	void GetDataTime(CString * datatime);
	unsigned int FillDurationSecunds(CString duration);
	CString InSQLDataTimeFormat(CString amadate, CString amatime);
	void FillAmaMyStruct(AMA_FORMAT * pAmaRec, AMA_FORMAT_MY * AmaMy);
	void AddRecIntoAMAbase(AMA_FORMAT *pAmaRec);
	BOOL m_bOnOffFileSelect;
	BOOL m_bInTabAmaBtn;
	virtual ~CTariffInbaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTariffInbaseView)
	afx_msg void OnSelectFileAma();
	afx_msg void OnUpdateSelectFileAma(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TariffInbaseView.cpp
inline CTariffInbaseDoc* CTariffInbaseView::GetDocument()
   { return (CTariffInbaseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARIFFINBASEVIEW_H__6CDB62DA_43E6_44FD_ABEE_347EA2552F89__INCLUDED_)
