// TariffInbaseView.cpp : implementation of the CTariffInbaseView class
//

#include "stdafx.h"
#include "TariffInbase.h"

#include "TariffInbaseSet.h"
#include "TTfileBase.h"
#include "TariffInbaseDoc.h"
#include "TariffInbaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTariffInbaseView

IMPLEMENT_DYNCREATE(CTariffInbaseView, CRecordView)

BEGIN_MESSAGE_MAP(CTariffInbaseView, CRecordView)
	//{{AFX_MSG_MAP(CTariffInbaseView)
	ON_COMMAND(ID_SELECT_FILE_AMA, OnSelectFileAma)
	ON_UPDATE_COMMAND_UI(ID_SELECT_FILE_AMA, OnUpdateSelectFileAma)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTariffInbaseView construction/destruction

CTariffInbaseView::CTariffInbaseView()
	: CRecordView(CTariffInbaseView::IDD)
{
	//{{AFX_DATA_INIT(CTariffInbaseView)
	m_pSet = NULL;
	m_pSetTtfile = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_bInTabAmaBtn = FALSE;
	m_bOnOffFileSelect = TRUE;
}

CTariffInbaseView::~CTariffInbaseView()
{
}

void CTariffInbaseView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTariffInbaseView)
	DDX_Control(pDX, IDC_TIMEWRITERECINBASE, m_cTimeRecInBase);
	DDX_Control(pDX, IDC_TIMEREADRECFROMFILE, m_cTimeRecFromFile);
	DDX_Control(pDX, IDC_COL_STRING, m_cNomberStrings);
	DDX_Control(pDX, IDC_TEND, m_cEnd);
	DDX_Control(pDX, IDC_TBEGIN, m_cBegin);
	DDX_Control(pDX, IDC_PROGRESS2, m_cProgress2);
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress1);
	DDX_FieldText(pDX, IDC_ANOMBER, m_pSet->m_anomber, m_pSet);
	DDV_MaxChars(pDX, m_pSet->m_anomber, 15);
	//}}AFX_DATA_MAP
	//DDX_FieldText(pDX, IDC_ANOMBER1, m_pSetTtfile->m_n14, m_pSetTtfile);
	//DDV_MaxChars(pDX, m_pSetTtfile->m_n14, 20);
	
}

BOOL CTariffInbaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CTariffInbaseView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_tariffInbaseSet;
	m_pSetTtfile = &GetDocument()->m_ttfilebaseSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CTariffInbaseView diagnostics

#ifdef _DEBUG
void CTariffInbaseView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CTariffInbaseView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CTariffInbaseDoc* CTariffInbaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTariffInbaseDoc)));
	return (CTariffInbaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTariffInbaseView database support
CRecordset* CTariffInbaseView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CTariffInbaseView message handlers

void CTariffInbaseView::OnSelectFileAma() 
{
	m_bOnOffFileSelect = FALSE;

	CString Time;
	GetDataTime(&Time);
	m_cBegin.SetWindowText(Time);
	int iBufferSize = 100000;
	CFileDialog fileSelectDlg(TRUE,NULL,"*.*",OFN_ALLOWMULTISELECT); //объект класса выбора файла
	fileSelectDlg.m_ofn.nMaxFile = iBufferSize;
	char* cNewBuffer = new char[iBufferSize];	// выделяем место
	fileSelectDlg.m_ofn.lpstrFile = cNewBuffer;	// даем указатель на новое место
	fileSelectDlg.m_ofn.lpstrFile[0] = NULL;	// ничего нет
	int result = fileSelectDlg.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		int j = 0;
		POSITION ps = fileSelectDlg.GetStartPosition();	// получить начальную позицию
		while (ps) { j++; fileSelectDlg.GetNextPathName(ps); }
		ps = fileSelectDlg.GetStartPosition();
		m_cProgress1.SetRange(0, j);
		m_cProgress1.SetPos(0);
		int i = 0;
		while (ps)
		{
			FILE * amaf;
			CString str;
			AMA_FORMAT AmaRec;
			AMA_FORMAT *pAmaRec = &AmaRec;

			str = fileSelectDlg.GetNextPathName(ps);
			if ((amaf = fopen((LPCTSTR)str, "rb")) == NULL)
			{
				str = "Error open file: " + str ;
				AfxMessageBox(str);
			}
	
			LogLineAdd(str);
		
			m_cProgress2.SetRange(0, 15625);
			m_cProgress2.SetPos(0);
			int k = 0;
			CString s;
			while (!feof(amaf))
			{
				GetDataTime(&Time);
				m_cTimeRecFromFile.SetWindowText(Time);
				k++;
				fread((void*)(pAmaRec), sizeof(BYTE), (sizeof(AMA_FORMAT)), amaf);
				AddRecIntoAMAbase(pAmaRec);
				s.Format("%d",k);
				m_cNomberStrings.SetWindowText(s);
				m_cProgress2.SetPos(k);
				GetDataTime(&Time);
				m_cTimeRecInBase.SetWindowText(Time);
			}
			k = 0;
			fclose(amaf);
			i++;
			m_cProgress1.SetPos(i);
		}
		i = 0;
	}
	delete []cNewBuffer;// освобождаем выделенную память

	GetDataTime(&Time);
	m_cEnd.SetWindowText(Time);

	m_bInTabAmaBtn = TRUE;
}

void CTariffInbaseView::OnUpdateSelectFileAma(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bOnOffFileSelect);
}

void CTariffInbaseView::AddRecIntoAMAbase(AMA_FORMAT *pAmaRec)
{
	AMA_FORMAT_MY AmaMy;

	FillAmaMyStruct(pAmaRec, &AmaMy);

	m_pSet->AddNew();
	m_pSet->m_anomber = RejectAllSimbols(AmaMy.Anomber);
	m_pSet->m_acategory = atoi((char*)AmaMy.AnomberCategory);
	m_pSet->m_bnomber = RejectAllSimbols(AmaMy.Bnomber);
	m_pSet->m_date = InSQLDataTimeFormat(AmaMy.date, AmaMy.time);
	//m_pSet->m_time = AmaMy.time;
	m_pSet->m_duration = FillDurationSecunds(AmaMy.duration);
	m_pSet->m_incrout = RejectAllSimbols(AmaMy.IncomingRouteName);
	m_pSet->m_inccn = atoi((char*)AmaMy.IncCircNomb);
	m_pSet->m_outrout = RejectAllSimbols(AmaMy.OutgoingRouteName);
	m_pSet->m_outcn = atoi((char*)AmaMy.OutCircNomb);
	m_pSet->m_chargmetr = atoi((char*)AmaMy.ChargeMeter);
	m_pSet->m_mbi = atoi((char*)AmaMy.MBI);
	m_pSet->m_rate = atoi((char*)AmaMy.RATE);
	m_pSet->m_calltype = atoi((char*)AmaMy.CALL_TYPE);
	m_pSet->m_servicecategory = atoi((char*)AmaMy.ServiceCategory);

	CString str;
	str = m_pSet->m_anomber + " " +
		  m_pSet->m_bnomber + " " +
		  m_pSet->m_date ;

	m_pSet->Update();
	UpdateData(TRUE);
	//m_cList1.AddString(str);
}

void CTariffInbaseView::FillAmaMyStruct(AMA_FORMAT *pAmaRec, AMA_FORMAT_MY * AmaMy)
{
	AmaMy->HEADER[0] = pAmaRec->HEADER; 
	AmaMy->HEADER[1] = '\0';
	memcpy((void*)(AmaMy->Anomber), (void*)(pAmaRec->Anomber), sizeof(pAmaRec->Anomber));
	AmaMy->Anomber[15] = '\0';
	memcpy((void*)(AmaMy->AnomberCategory), (void*)(pAmaRec->AnomberCategory), sizeof(pAmaRec->AnomberCategory));
	AmaMy->AnomberCategory[2] = '\0';
	memcpy((void*)(AmaMy->spare0), (void*)(pAmaRec->spare0), sizeof(pAmaRec->spare0));
	AmaMy->spare0[4] = '\0';
	memcpy((void*)(AmaMy->Bnomber), (void*)(pAmaRec->Bnomber), sizeof(pAmaRec->Bnomber));
	AmaMy->Bnomber[32] = '\0';
	memcpy((void*)(AmaMy->date), (void*)(pAmaRec->date), sizeof(pAmaRec->date));
	AmaMy->date[6] = '\0';
	memcpy((void*)(AmaMy->time), (void*)(pAmaRec->time), sizeof(pAmaRec->time));
	AmaMy->time[6] = '\0';
	memcpy((void*)(AmaMy->duration), (void*)(pAmaRec->duration), sizeof(pAmaRec->duration));
	AmaMy->duration[6] = '\0';
	memcpy((void*)(AmaMy->IncomingRouteName), (void*)(pAmaRec->IncomingRouteName), sizeof(pAmaRec->IncomingRouteName));
	AmaMy->IncomingRouteName[8] = '\0';
	memcpy((void*)(AmaMy->IncCircNomb), (void*)(pAmaRec->IncCircNomb), sizeof(pAmaRec->IncCircNomb));
	AmaMy->IncCircNomb[4] = '\0';
	memcpy((void*)(AmaMy->OutgoingRouteName), (void*)(pAmaRec->OutgoingRouteName), sizeof(pAmaRec->OutgoingRouteName));
	AmaMy->OutgoingRouteName[8] = '\0';
	memcpy((void*)(AmaMy->OutCircNomb), (void*)(pAmaRec->OutCircNomb), sizeof(pAmaRec->OutCircNomb));
	AmaMy->OutCircNomb[5] = '\0';
	memcpy((void*)(AmaMy->ChargeMeter), (void*)(pAmaRec->ChargeMeter), sizeof(pAmaRec->ChargeMeter));
	AmaMy->ChargeMeter[7] = '\0';
	memcpy((void*)(AmaMy->MBI), (void*)(pAmaRec->MBI), sizeof(pAmaRec->MBI));
	AmaMy->MBI[3] = '\0';
	AmaMy->RATE[0] = pAmaRec->RATE;
	AmaMy->RATE[1] = '\0';
	AmaMy->CALL_TYPE[0] = pAmaRec->CALL_TYPE;
	AmaMy->CALL_TYPE[1] = '\0';
	memcpy((void*)(AmaMy->spare1), (void*)(pAmaRec->spare1), sizeof(pAmaRec->spare1));
	AmaMy->spare1[2] = '\0';
	memcpy((void*)(AmaMy->ServiceCategory), (void*)(pAmaRec->ServiceCategory), sizeof(pAmaRec->ServiceCategory));
	AmaMy->ServiceCategory[3] = '\0';
	AmaMy->spare2[0] = pAmaRec->spare2;
	AmaMy->spare2[1] = '\0';
	memcpy((void*)(AmaMy->spare3), (void*)(pAmaRec->spare3), sizeof(pAmaRec->spare3));
	AmaMy->spare3[2] = '\0';
	AmaMy->spare4[0] = pAmaRec->spare4;
	AmaMy->spare4[1] = '\0';
	memcpy((void*)(AmaMy->spare5), (void*)(pAmaRec->spare5), sizeof(pAmaRec->spare5));
	AmaMy->spare5[12] = '\0';
}

CString CTariffInbaseView::InSQLDataTimeFormat(CString amadate, CString amatime)
{
	CString year, month, day, hour, minuts, secunds, str;
	year = amadate[0] ;
	year = year + amadate[1];
	year = "20" + year;
	month = amadate[2] ;
	month = month + amadate[3] ;
	day = amadate[4];
	day = day + amadate[5];
	hour = amatime[0];
	hour = hour + amatime[1];
	minuts = amatime[2];
	minuts = minuts + amatime[3];
	secunds = amatime[4];
	secunds = secunds + amatime[5];
	str = year + "-" + month + "-" + day + " " 
		+ hour + ":" + minuts + ":" + secunds;

	//m_cList1.AddString(str);
	return str;
}

unsigned int CTariffInbaseView::FillDurationSecunds(CString duration)
{
	unsigned int dur, m, s;
	CString min, sek, str;

	min = duration[0];
	min = min + duration[1];
	min = min + duration[2];
	min = min + duration[3];
	sek = duration[4];
	sek = sek + duration[5];
	m = atoi((LPCTSTR)min) * 60;
	s = atoi((LPCTSTR)sek);
	dur = m + s;
	return dur;
}

void CTariffInbaseView::GetDataTime(CString *datatime)
{
	CString dt;
	time_t now;
	struct tm * ptr;
	
	time(&now);
	ptr = localtime(&now);
	* datatime = asctime(ptr);
}

CString CTariffInbaseView::RejectAllSimbols(CString linewithsimb)
{
	CString str;
	int i = 0;
	for (i = 0; i < linewithsimb.GetLength(); i++)
	{
		if (linewithsimb[i] != ' ') str = str + linewithsimb[i];
	}
	return str;
}

int CTariffInbaseView::LogLineAdd(CString line)
{
	FILE * logfile;
	CString logfilename = "server1.log";
	CString datatime;
	int error;

	if ((logfile = fopen((LPCTSTR)logfilename, "a")) == NULL)
	{
		AfxMessageBox("Error open file log");
		error = GetLastError();
		return error;
	}
	GetDataTime(&datatime);
	line = "\n" + datatime + " : " + line;
	fputs((LPCTSTR)line,logfile);
	fclose(logfile);

	return 0;
}


