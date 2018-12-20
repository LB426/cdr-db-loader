// TariffInBaseAXEView.cpp : implementation of the CTariffInBaseAXEView class
//

#include "stdafx.h"
#include "TariffInBaseAXE.h"

#include "TariffInBaseAXESet.h"
#include "TariffInBaseAXEDoc.h"
#include "TariffInBaseAXEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTariffInBaseAXEView

IMPLEMENT_DYNCREATE(CTariffInBaseAXEView, CRecordView)

BEGIN_MESSAGE_MAP(CTariffInBaseAXEView, CRecordView)
	//{{AFX_MSG_MAP(CTariffInBaseAXEView)
	ON_COMMAND(ID_SELECT_TTFILES, OnSelectTtfiles)
	ON_UPDATE_COMMAND_UI(ID_SELECT_TTFILES, OnUpdateSelectTtfiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTariffInBaseAXEView construction/destruction

CTariffInBaseAXEView::CTariffInBaseAXEView()
	: CRecordView(CTariffInBaseAXEView::IDD)
{
	//{{AFX_DATA_INIT(CTariffInBaseAXEView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_bOnSelectFile = TRUE;
}

CTariffInBaseAXEView::~CTariffInBaseAXEView()
{
}

void CTariffInBaseAXEView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTariffInBaseAXEView)
	DDX_Control(pDX, IDC_TIMESTARTRECORD, m_cTimeGetRecFromFile);
	DDX_Control(pDX, IDC_RECORD_COUNT, m_cRecCount);
	DDX_Control(pDX, IDC_BUFFER, m_cBuffer);
	DDX_Control(pDX, IDC_STATIC2, m_cEnd);
	DDX_Control(pDX, IDC_STATIC1, m_cBegin);
	DDX_Control(pDX, IDC_PROGRESS2, m_cProgress2);
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress1);
	DDX_FieldText(pDX, IDC_EDIT2, m_pSet->m_n14, m_pSet);
	DDX_FieldText(pDX, IDC_EDIT3, m_pSet->m_n21, m_pSet);
	DDX_Control(pDX, IDC_TIMESETRECINBASE, m_cTimeSetRecInBase);
	//}}AFX_DATA_MAP
}

BOOL CTariffInBaseAXEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CTariffInBaseAXEView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_tariffInBaseAXESet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CTariffInBaseAXEView diagnostics

#ifdef _DEBUG
void CTariffInBaseAXEView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CTariffInBaseAXEView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CTariffInBaseAXEDoc* CTariffInBaseAXEView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTariffInBaseAXEDoc)));
	return (CTariffInBaseAXEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTariffInBaseAXEView database support
CRecordset* CTariffInBaseAXEView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CTariffInBaseAXEView message handlers

void CTariffInBaseAXEView::OnSelectTtfiles() 
{
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
			FILE * ttf;
			CString str;
			str = fileSelectDlg.GetNextPathName(ps);
			if ((ttf = fopen((LPCTSTR)str, "rb")) == NULL)
			{
				str = "Error open file: " + str ;
				AfxMessageBox(str);
			}
	
			LogLineAdd(str);
		
			m_cProgress2.SetRange(0, 500);
			m_cProgress2.SetPos(0);
			int k = 0;
			char buffer[2048];
			CString s;
			while (!feof(ttf))
			{
				GetDataTime(&Time);
				m_cTimeGetRecFromFile.SetWindowText(Time);
				k++;
				fread((void*)(buffer), sizeof(BYTE), 2048, ttf);
				GetRecordsFromBuf(buffer);
				s.Format("%d",k);
				m_cRecCount.SetWindowText(s);
				m_cProgress2.SetPos(k);
				GetDataTime(&Time);
				m_cTimeSetRecInBase.SetWindowText(Time);
			}
			k = 0;
			fclose(ttf);
			i++;
			m_cProgress1.SetPos(i);
		}
		i = 0;
	}
	delete []cNewBuffer;// освобождаем выделенную память

	GetDataTime(&Time);
	m_cEnd.SetWindowText(Time);

	m_bOnSelectFile = FALSE;	
}

void CTariffInBaseAXEView::OnUpdateSelectTtfiles(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bOnSelectFile);	
}

void CTariffInBaseAXEView::GetDataTime(CString *datatime)
{
	CString dt;
	time_t now;
	struct tm * ptr;
	
	time(&now);
	ptr = localtime(&now);
	* datatime = asctime(ptr);
}

int CTariffInBaseAXEView::LogLineAdd(CString line)
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

CString CTariffInBaseAXEView::RejectAllSimbols(CString linewithsimb)
{
	CString str;
	int i = 0;
	for (i = 0; i < linewithsimb.GetLength(); i++)
	{
		if (linewithsimb[i] != ' ') str = str + linewithsimb[i];
	}
	return str;
}

void CTariffInBaseAXEView::GetRecordsFromBuf(char * buffer)
{
	char * pBuffer = buffer;
	unsigned int x;

	while ((x = (pBuffer - buffer)) < 2048)
	{
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '0'))
		{
			RECORD_TYPE00 * pRecType00 = (RECORD_TYPE00*)pBuffer;
			RECORD_TYPE00MY RecType00My;
			FillRecordTypeMy(pRecType00, &RecType00My);
			AddRecInTable(&RecType00My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE00);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '2'))
		{
			RECORD_TYPE02 * pRecType02 = (RECORD_TYPE02*)pBuffer;
			RECORD_TYPE02MY RecType02My;
			FillRecordTypeMy(pRecType02, &RecType02My);
			AddRecInTable(&RecType02My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE02);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '4'))
		{
			RECORD_TYPE04 * pRecType04 = (RECORD_TYPE04*)pBuffer;
			RECORD_TYPE04MY RecType04My;
			FillRecordTypeMy(pRecType04, &RecType04My);
			AddRecInTable(&RecType04My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE04);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '6'))
		{
			RECORD_TYPE06 * pRecType06 = (RECORD_TYPE06*)pBuffer;
			RECORD_TYPE06MY RecType06My;
			FillRecordTypeMy(pRecType06, &RecType06My);
			AddRecInTable(&RecType06My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE06);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '7'))
		{
			RECORD_TYPE07 * pRecType07 = (RECORD_TYPE07*)pBuffer;
			RECORD_TYPE07MY RecType07My;
			FillRecordTypeMy(pRecType07, &RecType07My);
			AddRecInTable(&RecType07My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE07);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '8'))
		{
			RECORD_TYPE08 * pRecType08 = (RECORD_TYPE08*)pBuffer;
			RECORD_TYPE08MY RecType08My;
			FillRecordTypeMy(pRecType08, &RecType08My);
			AddRecInTable(&RecType08My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE08);
			continue;
		}
		if (*pBuffer == 0)
		{
			pBuffer++;
		}
	}
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE00 *pRec, RECORD_TYPE00MY *pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	pRecMy->n2_CauseForOutput[1] = '\0';

	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	pRecMy->n3_RecordNumber[2] = '\0';

	memcpy((void*)pRecMy->n4_CallIdenificationNumber,(void*)pRec->n4_CallIdenificationNumber,sizeof(pRec->n4_CallIdenificationNumber));
	pRecMy->n4_CallIdenificationNumber[8] = '\0';

	memcpy((void*)pRecMy->n6_RecordSequenceNumber,(void*)pRec->n6_RecordSequenceNumber,sizeof(pRec->n6_RecordSequenceNumber));
	pRecMy->n6_RecordSequenceNumber[8] = '\0';

	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	pRecMy->n8_OutputForSubscriber[1] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	pRecMy->n16_Acategory[2] = '\0';

	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	pRecMy->n17_AnumberType[3] = '\0';

	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	pRecMy->n18_AsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	pRecMy->n19_AsubscrType[2] = '\0';

	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	pRecMy->n20_LengthIndicatorForBsubscr[2] = '\0';

	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	pRecMy->n21_Bnumber[18] = '\0';

	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	pRecMy->n23_Bcategory[2] = '\0';

	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	pRecMy->n24_BsubscrNumberType[3] = '\0';

	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	pRecMy->n25_BsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	pRecMy->n26_LengthIndicatorForCallingPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	pRecMy->n27_CallingPartyNumber[20] = '\0';

	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	pRecMy->n30_LengthIndicatorForCalledPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	pRecMy->n31_CalledPartyNumber[18] = '\0';

	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n34_FaultCode[5] = '\0';

	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n35_CallStatus[1] = '\0';

	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	pRecMy->n36_AbnormalReleaseIndicator[1] = '\0';

	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	pRecMy->n37_DateForStartOfChargingUSA[6] = '\0';

	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n40_TimeForStartOfCharging24hour[6] = '\0';

	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	pRecMy->n43_TimeForStopOfCharging[6] = '\0';

	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	pRecMy->n44_TimeRegisterSizureStartCharging[6] = '\0';

	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	pRecMy->n45_ChargeableDuration[6] = '\0';

	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n46_InterruptionTime[6] = '\0';

	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n47_ChargedParty[1] = '\0';

	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	pRecMy->n48_ImmediateServiceIndicator[1] = '\0';

	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n49_Price[8] = '\0';

	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	pRecMy->n50_PulseChargingIndicator[1] = '\0';

	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	pRecMy->n51_NumberOfMeterPulses[6] = '\0';

	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	pRecMy->n52_OriginForCharging[4] = '\0';

	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n53_TariffClass[3] = '\0';

	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n54_TariffSwitchingIndicator[1] = '\0';

	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	pRecMy->n57_CallAttemptIndicator[1] = '\0';

	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n61_TypeOfCalledSubscriber[1] = '\0';

	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n62_TypeOfSignalling[1] = '\0';

	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[1] = '\0';

	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n64_AbbreviatedNumber[4] = '\0';

	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	pRecMy->n66_ResultOfSubscriberServiceProcedure[1] = '\0';

	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	pRecMy->n67_TypeOfProcedure[2] = '\0';

	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n68_SubscrServiceIndicator[2] = '\0';

	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	pRecMy->n72_ConferenceCallIndicator[1] = '\0';

	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	pRecMy->n76_ExchngeIdentity[15] = '\0';

	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	pRecMy->n78_OutgouingRoute[7] = '\0';

	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n80_IncomingRoute[7] = '\0';

	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n82_ReroutingIndicator[1] = '\0';

	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n83_OriginatingCode[1] = '\0';

	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	pRecMy->n84_DestinationCode[1] = '\0';

	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	pRecMy->n85_TypeOfSizure[2] = '\0';

	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	pRecMy->n86_TypeOfIndicator[2] = '\0';

	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n87_TelecommunicationServiceCode[3] = '\0';

	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	pRecMy->n108_ForcedDisconnectionInformation[1] = '\0';

	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n109_CarrierAccessCode[6] = '\0';

	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
	pRecMy->n111_PresentationIndicator[1] = '\0';
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE02 * pRec, RECORD_TYPE02MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	pRecMy->n2_CauseForOutput[1] = '\0';

	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	pRecMy->n3_RecordNumber[2] = '\0';

	memcpy((void*)pRecMy->n4_CallIdenificationNumber,(void*)pRec->n4_CallIdenificationNumber,sizeof(pRec->n4_CallIdenificationNumber));
	pRecMy->n4_CallIdenificationNumber[8] = '\0';

	memcpy((void*)pRecMy->n6_RecordSequenceNumber,(void*)pRec->n6_RecordSequenceNumber,sizeof(pRec->n6_RecordSequenceNumber));
	pRecMy->n6_RecordSequenceNumber[8] = '\0';

	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	pRecMy->n8_OutputForSubscriber[1] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	pRecMy->n16_Acategory[2] = '\0';

	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	pRecMy->n17_AnumberType[3] = '\0';

	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	pRecMy->n18_AsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	pRecMy->n19_AsubscrType[2] = '\0';

	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	pRecMy->n20_LengthIndicatorForBsubscr[2] = '\0';

	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	pRecMy->n21_Bnumber[18] = '\0';

	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	pRecMy->n23_Bcategory[2] = '\0';

	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	pRecMy->n24_BsubscrNumberType[3] = '\0';

	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	pRecMy->n25_BsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	pRecMy->n26_LengthIndicatorForCallingPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	pRecMy->n27_CallingPartyNumber[20] = '\0';

	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	pRecMy->n30_LengthIndicatorForCalledPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	pRecMy->n31_CalledPartyNumber[18] = '\0';

	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n34_FaultCode[5] = '\0';

	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n35_CallStatus[1] = '\0';

	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	pRecMy->n36_AbnormalReleaseIndicator[1] = '\0';

	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	pRecMy->n37_DateForStartOfChargingUSA[6] = '\0';

	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n40_TimeForStartOfCharging24hour[6] = '\0';

	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	pRecMy->n43_TimeForStopOfCharging[6] = '\0';

	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	pRecMy->n44_TimeRegisterSizureStartCharging[6] = '\0';

	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	pRecMy->n45_ChargeableDuration[6] = '\0';

	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n46_InterruptionTime[6] = '\0';

	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n47_ChargedParty[1] = '\0';

	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	pRecMy->n48_ImmediateServiceIndicator[1] = '\0';

	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n49_Price[8] = '\0';

	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	pRecMy->n50_PulseChargingIndicator[1] = '\0';

	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	pRecMy->n51_NumberOfMeterPulses[6] = '\0';

	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	pRecMy->n52_OriginForCharging[4] = '\0';

	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n53_TariffClass[3] = '\0';

	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n54_TariffSwitchingIndicator[1] = '\0';

	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	pRecMy->n57_CallAttemptIndicator[1] = '\0';

	memcpy((void*)pRecMy->n58_CallAttemptState,(void*)pRec->n58_CallAttemptState,sizeof(pRec->n58_CallAttemptState));
	pRecMy->n58_CallAttemptState[2] = '\0';

	memcpy((void*)pRecMy->n59_CauseCode,(void*)pRec->n59_CauseCode,sizeof(pRec->n59_CauseCode));
	pRecMy->n59_CauseCode[3] = '\0';
	
	memcpy((void*)pRecMy->n60_LocationCode,(void*)pRec->n60_LocationCode,sizeof(pRec->n60_LocationCode));
	pRecMy->n60_LocationCode[2] = '\0';

	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n61_TypeOfCalledSubscriber[1] = '\0';

	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n62_TypeOfSignalling[1] = '\0';

	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[1] = '\0';

	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n64_AbbreviatedNumber[4] = '\0';

	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	pRecMy->n66_ResultOfSubscriberServiceProcedure[1] = '\0';

	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	pRecMy->n67_TypeOfProcedure[2] = '\0';

	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n68_SubscrServiceIndicator[2] = '\0';

	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	pRecMy->n72_ConferenceCallIndicator[1] = '\0';

	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	pRecMy->n76_ExchngeIdentity[15] = '\0';

	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	pRecMy->n78_OutgouingRoute[7] = '\0';

	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n80_IncomingRoute[7] = '\0';

	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n82_ReroutingIndicator[1] = '\0';

	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n83_OriginatingCode[1] = '\0';

	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	pRecMy->n84_DestinationCode[1] = '\0';

	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	pRecMy->n85_TypeOfSizure[2] = '\0';

	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	pRecMy->n86_TypeOfIndicator[2] = '\0';

	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n87_TelecommunicationServiceCode[3] = '\0';

	memcpy((void*)pRecMy->n88_NetvorkConversionType,(void*)pRec->n88_NetvorkConversionType,sizeof(pRec->n88_NetvorkConversionType));
	pRecMy->n88_NetvorkConversionType[2] = '\0';

	memcpy((void*)pRecMy->n89_NumberOfUserToUserMessagesDuringCall,(void*)pRec->n89_NumberOfUserToUserMessagesDuringCall,sizeof(pRec->n89_NumberOfUserToUserMessagesDuringCall));
	pRecMy->n89_NumberOfUserToUserMessagesDuringCall[4] = '\0';

	pRecMy->n90_NumberOfUserToUser[0] = pRec->n90_NumberOfUserToUser;
	pRecMy->n90_NumberOfUserToUser[1] = '\0';

	memcpy((void*)pRecMy->n91_SubscrServiceForISDNSuplimentaryServices,(void*)pRec->n91_SubscrServiceForISDNSuplimentaryServices,sizeof(pRec->n91_SubscrServiceForISDNSuplimentaryServices));
	pRecMy->n91_SubscrServiceForISDNSuplimentaryServices[16] = '\0';

	memcpy((void*)pRecMy->n92_EndToEndAccessDataMap,(void*)pRec->n92_EndToEndAccessDataMap,sizeof(pRec->n92_EndToEndAccessDataMap));
	pRecMy->n92_EndToEndAccessDataMap[8] = '\0';

	pRecMy->n93_EndToEndAccessDataIndicator[0] = pRec->n93_EndToEndAccessDataIndicator;
	pRecMy->n93_EndToEndAccessDataIndicator[1] = '\0';

	memcpy((void*)pRecMy->n94_EndToEndAccessDataCounter,(void*)pRec->n94_EndToEndAccessDataCounter,sizeof(pRec->n94_EndToEndAccessDataCounter));
	pRecMy->n94_EndToEndAccessDataCounter[3] = '\0';

	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	pRecMy->n108_ForcedDisconnectionInformation[1] = '\0';

	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n109_CarrierAccessCode[6] = '\0';

	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
	pRecMy->n111_PresentationIndicator[1] = '\0';
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE04 * pRec, RECORD_TYPE04MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	pRecMy->n2_CauseForOutput[1] = '\0';

	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	pRecMy->n3_RecordNumber[2] = '\0';

	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	pRecMy->n8_OutputForSubscriber[1] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	pRecMy->n16_Acategory[2] = '\0';

	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	pRecMy->n17_AnumberType[3] = '\0';

	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	pRecMy->n18_AsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	pRecMy->n19_AsubscrType[2] = '\0';

	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	pRecMy->n20_LengthIndicatorForBsubscr[2] = '\0';

	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	pRecMy->n21_Bnumber[18] = '\0';

	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	pRecMy->n23_Bcategory[2] = '\0';

	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	pRecMy->n24_BsubscrNumberType[3] = '\0';

	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	pRecMy->n25_BsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	pRecMy->n26_LengthIndicatorForCallingPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	pRecMy->n27_CallingPartyNumber[20] = '\0';

	memcpy((void*)pRecMy->n28_LengthIndicatorForRedirectingNumber,(void*)pRec->n28_LengthIndicatorForRedirectingNumber,sizeof(pRec->n28_LengthIndicatorForRedirectingNumber));
	pRecMy->n27_CallingPartyNumber[20] = '\0';

	memcpy((void*)pRecMy->n29_RedirectingNumber,(void*)pRec->n29_RedirectingNumber,sizeof(pRec->n29_RedirectingNumber));
	pRecMy->n29_RedirectingNumber[20] = '\0';

	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	pRecMy->n30_LengthIndicatorForCalledPartyNumber[2] = '\0';

	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	pRecMy->n31_CalledPartyNumber[18] = '\0';

	memcpy((void*)pRecMy->n32_LengthIndicatorForOriginallyCalledNumber,(void*)pRec->n32_LengthIndicatorForOriginallyCalledNumber,sizeof(pRec->n32_LengthIndicatorForOriginallyCalledNumber));
	pRecMy->n32_LengthIndicatorForOriginallyCalledNumber[2] = '\0';

	memcpy((void*)pRecMy->n33_OriginallyPartyNumber,(void*)pRec->n33_OriginallyPartyNumber,sizeof(pRec->n33_OriginallyPartyNumber));
	pRecMy->n33_OriginallyPartyNumber[20] = '\0';

	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n34_FaultCode[5] = '\0';

	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n35_CallStatus[1] = '\0';

	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	pRecMy->n36_AbnormalReleaseIndicator[1] = '\0';

	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	pRecMy->n37_DateForStartOfChargingUSA[6] = '\0';

	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n40_TimeForStartOfCharging24hour[6] = '\0';

	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	pRecMy->n43_TimeForStopOfCharging[6] = '\0';

	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	pRecMy->n44_TimeRegisterSizureStartCharging[6] = '\0';

	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	pRecMy->n45_ChargeableDuration[6] = '\0';

	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n46_InterruptionTime[6] = '\0';

	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n47_ChargedParty[1] = '\0';

	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	pRecMy->n48_ImmediateServiceIndicator[1] = '\0';

	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n49_Price[8] = '\0';

	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	pRecMy->n50_PulseChargingIndicator[1] = '\0';

	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	pRecMy->n51_NumberOfMeterPulses[6] = '\0';

	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	pRecMy->n52_OriginForCharging[4] = '\0';

	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n53_TariffClass[3] = '\0';

	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n54_TariffSwitchingIndicator[1] = '\0';

	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	pRecMy->n57_CallAttemptIndicator[1] = '\0';

	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n61_TypeOfCalledSubscriber[1] = '\0';

	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n62_TypeOfSignalling[1] = '\0';

	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[1] = '\0';

	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n64_AbbreviatedNumber[4] = '\0';

	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	pRecMy->n66_ResultOfSubscriberServiceProcedure[1] = '\0';

	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	pRecMy->n67_TypeOfProcedure[2] = '\0';

	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n68_SubscrServiceIndicator[2] = '\0';

	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	pRecMy->n72_ConferenceCallIndicator[1] = '\0';

	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	pRecMy->n76_ExchngeIdentity[15] = '\0';

	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	pRecMy->n78_OutgouingRoute[7] = '\0';

	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n80_IncomingRoute[7] = '\0';

	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n82_ReroutingIndicator[1] = '\0';

	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n83_OriginatingCode[1] = '\0';

	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	pRecMy->n84_DestinationCode[1] = '\0';

	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	pRecMy->n85_TypeOfSizure[2] = '\0';

	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	pRecMy->n86_TypeOfIndicator[2] = '\0';

	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n87_TelecommunicationServiceCode[3] = '\0';

	memcpy((void*)pRecMy->n89_NumberOfUserToUserMessagesDuringCall,(void*)pRec->n89_NumberOfUserToUserMessagesDuringCall,sizeof(pRec->n89_NumberOfUserToUserMessagesDuringCall));
	pRecMy->n89_NumberOfUserToUserMessagesDuringCall[4] = '\0';

	pRecMy->n90_NumberOfUserToUser[0] = pRec->n90_NumberOfUserToUser;
	pRecMy->n90_NumberOfUserToUser[1] = '\0';

	memcpy((void*)pRecMy->n91_SubscrServiceForISDNSuplimentaryServices,(void*)pRec->n91_SubscrServiceForISDNSuplimentaryServices,sizeof(pRec->n91_SubscrServiceForISDNSuplimentaryServices));
	pRecMy->n91_SubscrServiceForISDNSuplimentaryServices[16] = '\0';

	memcpy((void*)pRecMy->n92_EndToEndAccessDataMap,(void*)pRec->n92_EndToEndAccessDataMap,sizeof(pRec->n92_EndToEndAccessDataMap));
	pRecMy->n92_EndToEndAccessDataMap[8] = '\0';

	pRecMy->n93_EndToEndAccessDataIndicator[0] = pRec->n93_EndToEndAccessDataIndicator;
	pRecMy->n93_EndToEndAccessDataIndicator[1] = '\0';

	memcpy((void*)pRecMy->n94_EndToEndAccessDataCounter,(void*)pRec->n94_EndToEndAccessDataCounter,sizeof(pRec->n94_EndToEndAccessDataCounter));
	pRecMy->n94_EndToEndAccessDataCounter[3] = '\0';

	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	pRecMy->n108_ForcedDisconnectionInformation[1] = '\0';

	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n109_CarrierAccessCode[6] = '\0';

	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
	pRecMy->n111_PresentationIndicator[1] = '\0';
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE06 * pRec, RECORD_TYPE06MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	pRecMy->n8_OutputForSubscriber[1] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	pRecMy->n16_Acategory[2] = '\0';

	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	pRecMy->n18_AsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	pRecMy->n19_AsubscrType[2] = '\0';

	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	pRecMy->n20_LengthIndicatorForBsubscr[2] = '\0';

	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	pRecMy->n21_Bnumber[18] = '\0';

	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	pRecMy->n23_Bcategory[2] = '\0';

	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n34_FaultCode[5] = '\0';

	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n35_CallStatus[1] = '\0';

	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	pRecMy->n36_AbnormalReleaseIndicator[1] = '\0';

	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	pRecMy->n37_DateForStartOfChargingUSA[6] = '\0';

	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n40_TimeForStartOfCharging24hour[6] = '\0';

	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	pRecMy->n43_TimeForStopOfCharging[6] = '\0';

	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	pRecMy->n44_TimeRegisterSizureStartCharging[6] = '\0';

	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n47_ChargedParty[1] = '\0';

	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	pRecMy->n48_ImmediateServiceIndicator[1] = '\0';

	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n49_Price[8] = '\0';

	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	pRecMy->n50_PulseChargingIndicator[1] = '\0';

	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	pRecMy->n51_NumberOfMeterPulses[6] = '\0';

	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	pRecMy->n52_OriginForCharging[4] = '\0';

	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n53_TariffClass[3] = '\0';

	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	pRecMy->n66_ResultOfSubscriberServiceProcedure[1] = '\0';

	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	pRecMy->n67_TypeOfProcedure[2] = '\0';

	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n68_SubscrServiceIndicator[2] = '\0';

	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	pRecMy->n76_ExchngeIdentity[15] = '\0';

	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	pRecMy->n85_TypeOfSizure[2] = '\0';

	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	pRecMy->n86_TypeOfIndicator[2] = '\0';

	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n87_TelecommunicationServiceCode[3] = '\0';

	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	pRecMy->n108_ForcedDisconnectionInformation[1] = '\0';
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE07 * pRec, RECORD_TYPE07MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	pRecMy->n8_OutputForSubscriber[1] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	pRecMy->n16_Acategory[2] = '\0';

	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	pRecMy->n18_AsubscrNumberingPlanIndicator[2] = '\0';

	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	pRecMy->n37_DateForStartOfChargingUSA[6] = '\0';

	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n40_TimeForStartOfCharging24hour[6] = '\0';

	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n47_ChargedParty[1] = '\0';

	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n49_Price[8] = '\0';

	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	pRecMy->n50_PulseChargingIndicator[1] = '\0';

	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	pRecMy->n51_NumberOfMeterPulses[6] = '\0';

	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	pRecMy->n52_OriginForCharging[4] = '\0';

	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n53_TariffClass[3] = '\0';

	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	pRecMy->n66_ResultOfSubscriberServiceProcedure[1] = '\0';

	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	pRecMy->n67_TypeOfProcedure[2] = '\0';

	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	pRecMy->n76_ExchngeIdentity[15] = '\0';

	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	pRecMy->n85_TypeOfSizure[2] = '\0';

	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	pRecMy->n86_TypeOfIndicator[2] = '\0';

	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n87_TelecommunicationServiceCode[3] = '\0';
}

void CTariffInBaseAXEView::FillRecordTypeMy(RECORD_TYPE08 * pRec, RECORD_TYPE08MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n1_RecType[2] = '\0';

	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	pRecMy->n13_LengthIndicatorForAnumber[2] = '\0';

	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	pRecMy->n14_Anumber[10] = '\0';

	memcpy((void*)pRecMy->n112_DateOfExecutionOfCommand,(void*)pRec->n112_DateOfExecutionOfCommand,sizeof(pRec->n112_DateOfExecutionOfCommand));
	pRecMy->n112_DateOfExecutionOfCommand[6] = '\0';

	memcpy((void*)pRecMy->n113_TimeOfExecutionOfComand,(void*)pRec->n113_TimeOfExecutionOfComand,sizeof(pRec->n113_TimeOfExecutionOfComand));
	pRecMy->n113_TimeOfExecutionOfComand[6] = '\0';

	memcpy((void*)pRecMy->n114_CommandName,(void*)pRec->n114_CommandName,sizeof(pRec->n114_CommandName));
	pRecMy->n114_CommandName[5] = '\0';
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE00MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n2 = atoi((char*)pRec->n2_CauseForOutput);
	m_pSet->m_n3 = atoi((char*)pRec->n3_RecordNumber);
	m_pSet->m_n4 = atoi((char*)pRec->n4_CallIdenificationNumber);
	m_pSet->m_n6 = atoi((char*)pRec->n6_RecordSequenceNumber);
	m_pSet->m_n8 = atoi((char*)pRec->n8_OutputForSubscriber);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n16 = pRec->n16_Acategory;
	m_pSet->m_n17 = atoi((char*)pRec->n17_AnumberType);
	m_pSet->m_n18 = atoi((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	m_pSet->m_n19 = atoi((char*)pRec->n19_AsubscrType);
	m_pSet->m_n20 = atoi((char*)pRec->n20_LengthIndicatorForBsubscr);
	m_pSet->m_n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	m_pSet->m_n23 = atoi((char*)pRec->n23_Bcategory);
	m_pSet->m_n24 = atoi((char*)pRec->n24_BsubscrNumberType);
	m_pSet->m_n25 = atoi((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	m_pSet->m_n26 = atoi((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	m_pSet->m_n27 = RejectAllSimbols(pRec->n27_CallingPartyNumber);
	m_pSet->m_n30 = atoi((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	m_pSet->m_n31 = RejectAllSimbols(pRec->n31_CalledPartyNumber);
	m_pSet->m_n34 = atoi((char*)pRec->n34_FaultCode);
	m_pSet->m_n35 = atoi((char*)pRec->n35_CallStatus);

	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1) 
	{
		m_pSet->m_n36 = 1;
	}
	else 
		m_pSet->m_n36 = 0;

	m_pSet->m_n37 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n40 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n43 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n43_TimeForStopOfCharging);
	m_pSet->m_n44 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n44_TimeRegisterSizureStartCharging);
	m_pSet->m_n45 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n45_ChargeableDuration);
	m_pSet->m_n46 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n46_InterruptionTime);

	m_pSet->m_n47 = atoi((char*)pRec->n47_ChargedParty);

	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1) 
	{
		m_pSet->m_n48 = 1;
	}
	else 
		m_pSet->m_n48 = 0;
	 
	m_pSet->m_n49 = atoi((char*)pRec->n49_Price);
	m_pSet->m_n50 = atoi((char*)pRec->n50_PulseChargingIndicator);
	m_pSet->m_n51 = atoi((char*)pRec->n51_NumberOfMeterPulses);
	m_pSet->m_n52 = atoi((char*)pRec->n52_OriginForCharging);
	m_pSet->m_n53 = atoi((char*)pRec->n53_TariffClass);
	m_pSet->m_n54 = atoi((char*)pRec->n54_TariffSwitchingIndicator);
	m_pSet->m_n57 = atoi((char*)pRec->n57_CallAttemptIndicator);
	m_pSet->m_n61 = atoi((char*)pRec->n61_TypeOfCalledSubscriber);
	m_pSet->m_n62 = atoi((char*)pRec->n62_TypeOfSignalling);
	m_pSet->m_n63 = atoi((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	m_pSet->m_n64 = RejectAllSimbols(pRec->n64_AbbreviatedNumber);
	m_pSet->m_n66 = atoi((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	m_pSet->m_n67 = atoi((char*)pRec->n67_TypeOfProcedure);
	m_pSet->m_n68 = atoi((char*)pRec->n68_SubscrServiceIndicator);
	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1) 
	{
		m_pSet->m_n72 = 1;
	}
	else 
		m_pSet->m_n72 = 0;
	
	m_pSet->m_n76 = RejectAllSimbols(pRec->n76_ExchngeIdentity);
	m_pSet->m_n78 = RejectAllSimbols(pRec->n78_OutgouingRoute);
	m_pSet->m_n80 = RejectAllSimbols(pRec->n80_IncomingRoute);
	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1) 
	{
		m_pSet->m_n82 = 1;
	}
	else 
		m_pSet->m_n82 = 0;

	m_pSet->m_n83 = atoi((char*)pRec->n83_OriginatingCode);
	m_pSet->m_n84 = atoi((char*)pRec->n84_DestinationCode);
	m_pSet->m_n85 = atoi((char*)pRec->n85_TypeOfSizure);
	m_pSet->m_n86 = atoi((char*)pRec->n86_TypeOfIndicator);
	m_pSet->m_n87 = atoi((char*)pRec->n87_TelecommunicationServiceCode);
	m_pSet->m_n108 = atoi((char*)pRec->n108_ForcedDisconnectionInformation);
	m_pSet->m_n109 = atoi((char*)pRec->n109_CarrierAccessCode);

	if (atoi((char*)pRec->n111_PresentationIndicator) == 1) 
	{
		m_pSet->m_n111 = 1;
	}
	else 
		m_pSet->m_n111 = 0;

 	m_pSet->Update();
	UpdateData(FALSE);
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE02MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n2 = atoi((char*)pRec->n2_CauseForOutput);
	m_pSet->m_n3 = atoi((char*)pRec->n3_RecordNumber);
	m_pSet->m_n4 = atoi((char*)pRec->n4_CallIdenificationNumber);
	m_pSet->m_n6 = atoi((char*)pRec->n6_RecordSequenceNumber);
	m_pSet->m_n8 = atoi((char*)pRec->n8_OutputForSubscriber);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n16 = pRec->n16_Acategory;
	m_pSet->m_n17 = atoi((char*)pRec->n17_AnumberType);
	m_pSet->m_n18 = atoi((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	m_pSet->m_n19 = atoi((char*)pRec->n19_AsubscrType);
	m_pSet->m_n20 = atoi((char*)pRec->n20_LengthIndicatorForBsubscr);
	m_pSet->m_n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	m_pSet->m_n23 = atoi((char*)pRec->n23_Bcategory);
	m_pSet->m_n24 = atoi((char*)pRec->n24_BsubscrNumberType);
	m_pSet->m_n25 = atoi((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	m_pSet->m_n26 = atoi((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	m_pSet->m_n27 = RejectAllSimbols(pRec->n27_CallingPartyNumber);
	m_pSet->m_n30 = atoi((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	m_pSet->m_n31 = RejectAllSimbols(pRec->n31_CalledPartyNumber);
	m_pSet->m_n34 = atoi((char*)pRec->n34_FaultCode);
	m_pSet->m_n35 = atoi((char*)pRec->n35_CallStatus);

	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1) 
	{
		m_pSet->m_n36 = 1;
	}
	else 
		m_pSet->m_n36 = 0;

	m_pSet->m_n37 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n40 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n43 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n43_TimeForStopOfCharging);
	m_pSet->m_n44 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n44_TimeRegisterSizureStartCharging);
	m_pSet->m_n45 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n45_ChargeableDuration);
	m_pSet->m_n46 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n46_InterruptionTime);

	m_pSet->m_n47 = atoi((char*)pRec->n47_ChargedParty);

	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1) 
	{
		m_pSet->m_n48 = 1;
	}
	else 
		m_pSet->m_n48 = 0;
	 
	m_pSet->m_n49 = atoi((char*)pRec->n49_Price);
	m_pSet->m_n50 = atoi((char*)pRec->n50_PulseChargingIndicator);
	m_pSet->m_n51 = atoi((char*)pRec->n51_NumberOfMeterPulses);
	m_pSet->m_n52 = atoi((char*)pRec->n52_OriginForCharging);
	m_pSet->m_n53 = atoi((char*)pRec->n53_TariffClass);
	m_pSet->m_n54 = atoi((char*)pRec->n54_TariffSwitchingIndicator);
	m_pSet->m_n57 = atoi((char*)pRec->n57_CallAttemptIndicator);
	m_pSet->m_n58 = atoi((char*)pRec->n58_CallAttemptState);
	m_pSet->m_n59 = atoi((char*)pRec->n59_CauseCode);
	m_pSet->m_n60 = atoi((char*)pRec->n60_LocationCode);
	m_pSet->m_n61 = atoi((char*)pRec->n61_TypeOfCalledSubscriber);
	m_pSet->m_n62 = atoi((char*)pRec->n62_TypeOfSignalling);
	m_pSet->m_n63 = atoi((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	m_pSet->m_n64 = RejectAllSimbols(pRec->n64_AbbreviatedNumber);
	m_pSet->m_n66 = atoi((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	m_pSet->m_n67 = atoi((char*)pRec->n67_TypeOfProcedure);
	m_pSet->m_n68 = atoi((char*)pRec->n68_SubscrServiceIndicator);
	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1) 
	{
		m_pSet->m_n72 = 1;
	}
	else 
		m_pSet->m_n72 = 0;
	
	m_pSet->m_n76 = RejectAllSimbols(pRec->n76_ExchngeIdentity);
	m_pSet->m_n78 = RejectAllSimbols(pRec->n78_OutgouingRoute);
	m_pSet->m_n80 = RejectAllSimbols(pRec->n80_IncomingRoute);
	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1) 
	{
		m_pSet->m_n82 = 1;
	}
	else 
		m_pSet->m_n82 = 0;

	m_pSet->m_n83 = atoi((char*)pRec->n83_OriginatingCode);
	m_pSet->m_n84 = atoi((char*)pRec->n84_DestinationCode);
	m_pSet->m_n85 = atoi((char*)pRec->n85_TypeOfSizure);
	m_pSet->m_n86 = atoi((char*)pRec->n86_TypeOfIndicator);
	m_pSet->m_n87 = atoi((char*)pRec->n87_TelecommunicationServiceCode);
	m_pSet->m_n88 = atoi((char*)pRec->n88_NetvorkConversionType); 
	m_pSet->m_n89 = atoi((char*)pRec->n89_NumberOfUserToUserMessagesDuringCall);
	m_pSet->m_n90 = atoi((char*)pRec->n90_NumberOfUserToUser);
	m_pSet->m_n91 = atoi((char*)pRec->n91_SubscrServiceForISDNSuplimentaryServices);
	m_pSet->m_n92 = atoi((char*)pRec->n92_EndToEndAccessDataMap);
	m_pSet->m_n93 = atoi((char*)pRec->n93_EndToEndAccessDataIndicator);
	m_pSet->m_n94 = atoi((char*)pRec->n94_EndToEndAccessDataCounter);
	m_pSet->m_n108 = atoi((char*)pRec->n108_ForcedDisconnectionInformation);
	m_pSet->m_n109 = atoi((char*)pRec->n109_CarrierAccessCode);

	if (atoi((char*)pRec->n111_PresentationIndicator) == 1) 
	{
		m_pSet->m_n111 = 1;
	}
	else 
		m_pSet->m_n111 = 0;

 	m_pSet->Update();
	UpdateData(FALSE);
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE04MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n2 = atoi((char*)pRec->n2_CauseForOutput);
	m_pSet->m_n3 = atoi((char*)pRec->n3_RecordNumber);
	m_pSet->m_n8 = atoi((char*)pRec->n8_OutputForSubscriber);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n16 = pRec->n16_Acategory;
	m_pSet->m_n17 = atoi((char*)pRec->n17_AnumberType);
	m_pSet->m_n18 = atoi((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	m_pSet->m_n19 = atoi((char*)pRec->n19_AsubscrType);
	m_pSet->m_n20 = atoi((char*)pRec->n20_LengthIndicatorForBsubscr);
	m_pSet->m_n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	m_pSet->m_n23 = atoi((char*)pRec->n23_Bcategory);
	m_pSet->m_n24 = atoi((char*)pRec->n24_BsubscrNumberType);
	m_pSet->m_n25 = atoi((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	m_pSet->m_n26 = atoi((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	m_pSet->m_n27 = RejectAllSimbols(pRec->n27_CallingPartyNumber);
	m_pSet->m_n28 = atoi((char*)pRec->n28_LengthIndicatorForRedirectingNumber);
	m_pSet->m_n29 = RejectAllSimbols(pRec->n29_RedirectingNumber);
	m_pSet->m_n30 = atoi((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	m_pSet->m_n31 = RejectAllSimbols(pRec->n31_CalledPartyNumber);
	m_pSet->m_n32 = atoi((char*)pRec->n32_LengthIndicatorForOriginallyCalledNumber);
	m_pSet->m_n33 = RejectAllSimbols(pRec->n33_OriginallyPartyNumber);
	m_pSet->m_n34 = atoi((char*)pRec->n34_FaultCode);
	m_pSet->m_n35 = atoi((char*)pRec->n35_CallStatus);

	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1) 
	{
		m_pSet->m_n36 = 1;
	}
	else 
		m_pSet->m_n36 = 0;

	m_pSet->m_n37 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n40 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n43 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n43_TimeForStopOfCharging);
	m_pSet->m_n44 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n44_TimeRegisterSizureStartCharging);
	m_pSet->m_n45 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n45_ChargeableDuration);
	m_pSet->m_n46 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n46_InterruptionTime);

	m_pSet->m_n47 = atoi((char*)pRec->n47_ChargedParty);

	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1) 
	{
		m_pSet->m_n48 = 1;
	}
	else 
		m_pSet->m_n48 = 0;
	 
	m_pSet->m_n49 = atoi((char*)pRec->n49_Price);
	m_pSet->m_n50 = atoi((char*)pRec->n50_PulseChargingIndicator);
	m_pSet->m_n51 = atoi((char*)pRec->n51_NumberOfMeterPulses);
	m_pSet->m_n52 = atoi((char*)pRec->n52_OriginForCharging);
	m_pSet->m_n53 = atoi((char*)pRec->n53_TariffClass);
	m_pSet->m_n54 = atoi((char*)pRec->n54_TariffSwitchingIndicator);
	m_pSet->m_n57 = atoi((char*)pRec->n57_CallAttemptIndicator);
	m_pSet->m_n61 = atoi((char*)pRec->n61_TypeOfCalledSubscriber);
	m_pSet->m_n62 = atoi((char*)pRec->n62_TypeOfSignalling);
	m_pSet->m_n63 = atoi((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	m_pSet->m_n64 = RejectAllSimbols(pRec->n64_AbbreviatedNumber);
	m_pSet->m_n66 = atoi((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	m_pSet->m_n67 = atoi((char*)pRec->n67_TypeOfProcedure);
	m_pSet->m_n68 = atoi((char*)pRec->n68_SubscrServiceIndicator);
	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1) 
	{
		m_pSet->m_n72 = 1;
	}
	else 
		m_pSet->m_n72 = 0;
	
	m_pSet->m_n76 = RejectAllSimbols(pRec->n76_ExchngeIdentity);
	m_pSet->m_n78 = RejectAllSimbols(pRec->n78_OutgouingRoute);
	m_pSet->m_n80 = RejectAllSimbols(pRec->n80_IncomingRoute);
	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1) 
	{
		m_pSet->m_n82 = 1;
	}
	else 
		m_pSet->m_n82 = 0;

	m_pSet->m_n83 = atoi((char*)pRec->n83_OriginatingCode);
	m_pSet->m_n84 = atoi((char*)pRec->n84_DestinationCode);
	m_pSet->m_n85 = atoi((char*)pRec->n85_TypeOfSizure);
	m_pSet->m_n86 = atoi((char*)pRec->n86_TypeOfIndicator);
	m_pSet->m_n87 = atoi((char*)pRec->n87_TelecommunicationServiceCode);
	m_pSet->m_n89 = atoi((char*)pRec->n89_NumberOfUserToUserMessagesDuringCall);
	m_pSet->m_n90 = atoi((char*)pRec->n90_NumberOfUserToUser);
	m_pSet->m_n91 = atoi((char*)pRec->n91_SubscrServiceForISDNSuplimentaryServices);
	m_pSet->m_n92 = atoi((char*)pRec->n92_EndToEndAccessDataMap);
	m_pSet->m_n93 = atoi((char*)pRec->n93_EndToEndAccessDataIndicator);
	m_pSet->m_n94 = atoi((char*)pRec->n94_EndToEndAccessDataCounter);
	m_pSet->m_n108 = atoi((char*)pRec->n108_ForcedDisconnectionInformation);
	m_pSet->m_n109 = atoi((char*)pRec->n109_CarrierAccessCode);

	if (atoi((char*)pRec->n111_PresentationIndicator) == 1) 
	{
		m_pSet->m_n111 = 1;
	}
	else 
		m_pSet->m_n111 = 0;

 	m_pSet->Update();
	UpdateData(FALSE);
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE06MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n8 = atoi((char*)pRec->n8_OutputForSubscriber);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n16 = pRec->n16_Acategory;
	m_pSet->m_n18 = atoi((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	m_pSet->m_n19 = atoi((char*)pRec->n19_AsubscrType);
	m_pSet->m_n20 = atoi((char*)pRec->n20_LengthIndicatorForBsubscr);
	m_pSet->m_n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	m_pSet->m_n23 = atoi((char*)pRec->n23_Bcategory);
	m_pSet->m_n34 = atoi((char*)pRec->n34_FaultCode);
	m_pSet->m_n35 = atoi((char*)pRec->n35_CallStatus);

	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1) 
	{
		m_pSet->m_n36 = 1;
	}
	else 
		m_pSet->m_n36 = 0;

	m_pSet->m_n37 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n40 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n43 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n43_TimeForStopOfCharging);
	m_pSet->m_n44 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n44_TimeRegisterSizureStartCharging);

	m_pSet->m_n47 = atoi((char*)pRec->n47_ChargedParty);

	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1) 
	{
		m_pSet->m_n48 = 1;
	}
	else 
		m_pSet->m_n48 = 0;
	 
	m_pSet->m_n49 = atoi((char*)pRec->n49_Price);
	m_pSet->m_n50 = atoi((char*)pRec->n50_PulseChargingIndicator);
	m_pSet->m_n51 = atoi((char*)pRec->n51_NumberOfMeterPulses);
	m_pSet->m_n52 = atoi((char*)pRec->n52_OriginForCharging);
	m_pSet->m_n53 = atoi((char*)pRec->n53_TariffClass);
	m_pSet->m_n66 = atoi((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	m_pSet->m_n67 = atoi((char*)pRec->n67_TypeOfProcedure);
	m_pSet->m_n68 = atoi((char*)pRec->n68_SubscrServiceIndicator);
	m_pSet->m_n76 = RejectAllSimbols(pRec->n76_ExchngeIdentity);
	m_pSet->m_n85 = atoi((char*)pRec->n85_TypeOfSizure);
	m_pSet->m_n86 = atoi((char*)pRec->n86_TypeOfIndicator);
	m_pSet->m_n87 = atoi((char*)pRec->n87_TelecommunicationServiceCode);
	m_pSet->m_n108 = atoi((char*)pRec->n108_ForcedDisconnectionInformation);
 	m_pSet->Update();
	UpdateData(FALSE);
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE07MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n8 = atoi((char*)pRec->n8_OutputForSubscriber);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n16 = pRec->n16_Acategory;
	m_pSet->m_n18 = atoi((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	m_pSet->m_n37 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n40 = InSQLDataTimeFormat((char*)pRec->n37_DateForStartOfChargingUSA,
		(char*)pRec->n40_TimeForStartOfCharging24hour);
	m_pSet->m_n47 = atoi((char*)pRec->n47_ChargedParty);
	m_pSet->m_n49 = atoi((char*)pRec->n49_Price);
	m_pSet->m_n50 = atoi((char*)pRec->n50_PulseChargingIndicator);
	m_pSet->m_n51 = atoi((char*)pRec->n51_NumberOfMeterPulses);
	m_pSet->m_n52 = atoi((char*)pRec->n52_OriginForCharging);
	m_pSet->m_n53 = atoi((char*)pRec->n53_TariffClass);
	m_pSet->m_n66 = atoi((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	m_pSet->m_n67 = atoi((char*)pRec->n67_TypeOfProcedure);
	m_pSet->m_n76 = RejectAllSimbols(pRec->n76_ExchngeIdentity);
	m_pSet->m_n85 = atoi((char*)pRec->n85_TypeOfSizure);
	m_pSet->m_n86 = atoi((char*)pRec->n86_TypeOfIndicator);
	m_pSet->m_n87 = atoi((char*)pRec->n87_TelecommunicationServiceCode);
 	m_pSet->Update();
	UpdateData(FALSE);
}

void CTariffInBaseAXEView::AddRecInTable(RECORD_TYPE08MY *pRec)
{
	m_pSet->AddNew();
	m_pSet->m_n1 = atoi((char*)pRec->n1_RecType);
	m_pSet->m_n13 = atoi((char*)pRec->n13_LengthIndicatorForAnumber);
	m_pSet->m_n14 = RejectAllSimbols(pRec->n14_Anumber);
	m_pSet->m_n112 = InSQLDataTimeFormat((char*)pRec->n112_DateOfExecutionOfCommand,
		(char*)pRec->n113_TimeOfExecutionOfComand);
	m_pSet->m_n113 = InSQLDataTimeFormat((char*)pRec->n112_DateOfExecutionOfCommand,
		(char*)pRec->n113_TimeOfExecutionOfComand);
	m_pSet->m_n114 = RejectAllSimbols(pRec->n114_CommandName);
 	m_pSet->Update();
	UpdateData(FALSE);
}

CTime CTariffInBaseAXEView::InSQLDataTimeFormat(CString USAdate, CString time)
{
	CString year, month, day, str;
	int y,m,d;
	CString hour, minuts, secunds;
	int h,min,s;

	year = USAdate[0] ;
	year = year + USAdate[1];
	year = "20" + year;
	month = USAdate[2] ;
	month = month + USAdate[3] ;
	day = USAdate[4];
	day = day + USAdate[5];
	y = atoi((LPCTSTR)year);
	m = atoi((LPCTSTR)month);
	d = atoi((LPCTSTR)day);
	hour = time[0];
	hour = hour + time[1];
	minuts = time[2];
	minuts = minuts + time[3];
	secunds = time[4];
	secunds = secunds + time[5];
	h = atoi((LPCTSTR)hour);
	min = atoi((LPCTSTR)minuts);
	s = atoi((LPCTSTR)secunds);
	CTime t(y,m,d,h,min,s,0);
	return t;
}
