// TariffInBaseAXEView.h : interface of the CTariffInBaseAXEView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "msdgridctrl.h"
//}}AFX_INCLUDES

#if !defined(AFX_TARIFFINBASEAXEVIEW_H__55DDE55E_8C66_4D01_86C4_D5BC288D6295__INCLUDED_)
#define AFX_TARIFFINBASEAXEVIEW_H__55DDE55E_8C66_4D01_86C4_D5BC288D6295__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//**************************************************************************************
typedef struct _TTFILE_AXE10_FORMAT_TYPEALL
	{
		BYTE n1_RecType[2];
		BYTE n2_CauseForOutput;
		BYTE n3_RecordNumber[2];
		BYTE n4_CallIdenificationNumber[8];
		BYTE n6_RecordSequenceNumber[8];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n17_AnumberType[3];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n19_AsubscrType[2];
		BYTE n20_LengthIndicatorForBsubscr[2];
		BYTE n21_Bnumber[18];
		BYTE n23_Bcategory[2];
		BYTE n24_BsubscrNumberType[3];
		BYTE n25_BsubscrNumberingPlanIndicator[2];
		BYTE n26_LengthIndicatorForCallingPartyNumber[2];
		BYTE n27_CallingPartyNumber[20];
		BYTE n28_LengthIndicatorForRedirectingNumber[2];
		BYTE n29_RedirectingNumber[20];
		BYTE n30_LengthIndicatorForCalledPartyNumber[2];
		BYTE n31_CalledPartyNumber[18];
		BYTE n32_LengthIndicatorForOriginallyCalledNumber[2];
		BYTE n33_OriginallyPartyNumber[20];
		BYTE n34_FaultCode[5];
		BYTE n35_CallStatus;
		BYTE n36_AbnormalReleaseIndicator;
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n43_TimeForStopOfCharging[6];
		BYTE n44_TimeRegisterSizureStartCharging[6];
		BYTE n45_ChargeableDuration[6];
		BYTE n46_InterruptionTime[6];
		BYTE n47_ChargedParty;
		BYTE n48_ImmediateServiceIndicator;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n54_TariffSwitchingIndicator;
		BYTE n57_CallAttemptIndicator;
		BYTE n58_CallAttemptState[2];
		BYTE n59_CauseCode[3];
		BYTE n60_LocationCode[2];
		BYTE n61_TypeOfCalledSubscriber;
		BYTE n62_TypeOfSignalling;
		BYTE n63_LengthIndicatorForAbbreviatedNumber;
		BYTE n64_AbbreviatedNumber[4];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n68_SubscrServiceIndicator[2];
		BYTE n72_ConferenceCallIndicator;
		BYTE n76_ExchngeIdentity[15];
		BYTE n78_OutgouingRoute[7];
		BYTE n80_IncomingRoute[7];
		BYTE n82_ReroutingIndicator;
		BYTE n83_OriginatingCode;
		BYTE n84_DestinationCode;
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
		BYTE n88_NetvorkConversionType[2];
		BYTE n89_NumberOfUserToUserMessagesDuringCall[4];
		BYTE n90_NumberOfUserToUser;
		BYTE n91_SubscrServiceForISDNSuplimentaryServices[16];
		BYTE n92_EndToEndAccessDataMap[8];
		BYTE n93_EndToEndAccessDataIndicator;
		BYTE n94_EndToEndAccessDataCounter[3];
		BYTE n108_ForcedDisconnectionInformation;
		BYTE n109_CarrierAccessCode[6];
		BYTE n111_PresentationIndicator;
		BYTE n112_DateOfExecutionOfCommand[6];
		BYTE n113_TimeOfExecutionOfComand[6];
		BYTE n114_CommandName[5];
	} TTFILE_AXE10_FORMAT_TYPEALL;

typedef struct 
	{
		BYTE n1_RecType[2];
		BYTE n2_CauseForOutput;
		BYTE n3_RecordNumber[2];
		BYTE n4_CallIdenificationNumber[8];
		BYTE n6_RecordSequenceNumber[8];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n17_AnumberType[3];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n19_AsubscrType[2];
		BYTE n20_LengthIndicatorForBsubscr[2];
		BYTE n21_Bnumber[18];
		BYTE n23_Bcategory[2];
		BYTE n24_BsubscrNumberType[3];
		BYTE n25_BsubscrNumberingPlanIndicator[2];
		BYTE n26_LengthIndicatorForCallingPartyNumber[2];
		BYTE n27_CallingPartyNumber[20];
		BYTE n30_LengthIndicatorForCalledPartyNumber[2];
		BYTE n31_CalledPartyNumber[18];
		BYTE n34_FaultCode[5];
		BYTE n35_CallStatus;
		BYTE n36_AbnormalReleaseIndicator;
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n43_TimeForStopOfCharging[6];
		BYTE n44_TimeRegisterSizureStartCharging[6];
		BYTE n45_ChargeableDuration[6];
		BYTE n46_InterruptionTime[6];
		BYTE n47_ChargedParty;
		BYTE n48_ImmediateServiceIndicator;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n54_TariffSwitchingIndicator;
		BYTE n57_CallAttemptIndicator;
		BYTE n61_TypeOfCalledSubscriber;
		BYTE n62_TypeOfSignalling;
		BYTE n63_LengthIndicatorForAbbreviatedNumber;
		BYTE n64_AbbreviatedNumber[4];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n68_SubscrServiceIndicator[2];
		BYTE n72_ConferenceCallIndicator;
		BYTE n76_ExchngeIdentity[15];
		BYTE n78_OutgouingRoute[7];
		BYTE n80_IncomingRoute[7];
		BYTE n82_ReroutingIndicator;
		BYTE n83_OriginatingCode;
		BYTE n84_DestinationCode;
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
		BYTE n108_ForcedDisconnectionInformation;
		BYTE n109_CarrierAccessCode[6];
		BYTE n111_PresentationIndicator;
	} RECORD_TYPE00;

typedef struct
	{
		BYTE n1_RecType[2];
		BYTE n2_CauseForOutput;
		BYTE n3_RecordNumber[2];
		BYTE n4_CallIdenificationNumber[8];
		BYTE n6_RecordSequenceNumber[8];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n17_AnumberType[3];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n19_AsubscrType[2];
		BYTE n20_LengthIndicatorForBsubscr[2];
		BYTE n21_Bnumber[18];
		BYTE n23_Bcategory[2];
		BYTE n24_BsubscrNumberType[3];
		BYTE n25_BsubscrNumberingPlanIndicator[2];
		BYTE n26_LengthIndicatorForCallingPartyNumber[2];
		BYTE n27_CallingPartyNumber[20];
		BYTE n30_LengthIndicatorForCalledPartyNumber[2];
		BYTE n31_CalledPartyNumber[18];
		BYTE n34_FaultCode[5];
		BYTE n35_CallStatus;
		BYTE n36_AbnormalReleaseIndicator;
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n43_TimeForStopOfCharging[6];
		BYTE n44_TimeRegisterSizureStartCharging[6];
		BYTE n45_ChargeableDuration[6];
		BYTE n46_InterruptionTime[6];
		BYTE n47_ChargedParty;
		BYTE n48_ImmediateServiceIndicator;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n54_TariffSwitchingIndicator;
		BYTE n57_CallAttemptIndicator;
		BYTE n58_CallAttemptState[2];
		BYTE n59_CauseCode[3];
		BYTE n60_LocationCode[2];
		BYTE n61_TypeOfCalledSubscriber;
		BYTE n62_TypeOfSignalling;
		BYTE n63_LengthIndicatorForAbbreviatedNumber;
		BYTE n64_AbbreviatedNumber[4];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n68_SubscrServiceIndicator[2];
		BYTE n72_ConferenceCallIndicator;
		BYTE n76_ExchngeIdentity[15];
		BYTE n78_OutgouingRoute[7];
		BYTE n80_IncomingRoute[7];
		BYTE n82_ReroutingIndicator;
		BYTE n83_OriginatingCode;
		BYTE n84_DestinationCode;
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
		BYTE n88_NetvorkConversionType[2];
		BYTE n89_NumberOfUserToUserMessagesDuringCall[4];
		BYTE n90_NumberOfUserToUser;
		BYTE n91_SubscrServiceForISDNSuplimentaryServices[16];
		BYTE n92_EndToEndAccessDataMap[8];
		BYTE n93_EndToEndAccessDataIndicator;
		BYTE n94_EndToEndAccessDataCounter[3];
		BYTE n108_ForcedDisconnectionInformation;
		BYTE n109_CarrierAccessCode[6];
		BYTE n111_PresentationIndicator;
	} RECORD_TYPE02;

typedef struct
	{
		BYTE n1_RecType[2];
		BYTE n2_CauseForOutput;
		BYTE n3_RecordNumber[2];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n17_AnumberType[3];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n19_AsubscrType[2];
		BYTE n20_LengthIndicatorForBsubscr[2];
		BYTE n21_Bnumber[18];
		BYTE n23_Bcategory[2];
		BYTE n24_BsubscrNumberType[3];
		BYTE n25_BsubscrNumberingPlanIndicator[2];
		BYTE n26_LengthIndicatorForCallingPartyNumber[2];
		BYTE n27_CallingPartyNumber[20];
		BYTE n28_LengthIndicatorForRedirectingNumber[2];
		BYTE n29_RedirectingNumber[20];
		BYTE n30_LengthIndicatorForCalledPartyNumber[2];
		BYTE n31_CalledPartyNumber[18];
		BYTE n32_LengthIndicatorForOriginallyCalledNumber[2];
		BYTE n33_OriginallyPartyNumber[20];
		BYTE n34_FaultCode[5];
		BYTE n35_CallStatus;
		BYTE n36_AbnormalReleaseIndicator;
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n43_TimeForStopOfCharging[6];
		BYTE n44_TimeRegisterSizureStartCharging[6];
		BYTE n45_ChargeableDuration[6];
		BYTE n46_InterruptionTime[6];
		BYTE n47_ChargedParty;
		BYTE n48_ImmediateServiceIndicator;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n54_TariffSwitchingIndicator;
		BYTE n57_CallAttemptIndicator;
		BYTE n61_TypeOfCalledSubscriber;
		BYTE n62_TypeOfSignalling;
		BYTE n63_LengthIndicatorForAbbreviatedNumber;
		BYTE n64_AbbreviatedNumber[4];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n68_SubscrServiceIndicator[2];
		BYTE n72_ConferenceCallIndicator;
		BYTE n76_ExchngeIdentity[15];
		BYTE n78_OutgouingRoute[7];
		BYTE n80_IncomingRoute[7];
		BYTE n82_ReroutingIndicator;
		BYTE n83_OriginatingCode;
		BYTE n84_DestinationCode;
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
		BYTE n89_NumberOfUserToUserMessagesDuringCall[4];
		BYTE n90_NumberOfUserToUser;
		BYTE n91_SubscrServiceForISDNSuplimentaryServices[16];
		BYTE n92_EndToEndAccessDataMap[8];
		BYTE n93_EndToEndAccessDataIndicator;
		BYTE n94_EndToEndAccessDataCounter[3];
		BYTE n108_ForcedDisconnectionInformation;
		BYTE n109_CarrierAccessCode[6];
		BYTE n111_PresentationIndicator;
	} RECORD_TYPE04;

typedef struct
	{
		BYTE n1_RecType[2];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n19_AsubscrType[2];
		BYTE n20_LengthIndicatorForBsubscr[2];
		BYTE n21_Bnumber[18];
		BYTE n23_Bcategory[2];
		BYTE n34_FaultCode[5];
		BYTE n35_CallStatus;
		BYTE n36_AbnormalReleaseIndicator;
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n43_TimeForStopOfCharging[6];
		BYTE n44_TimeRegisterSizureStartCharging[6];
		BYTE n47_ChargedParty;
		BYTE n48_ImmediateServiceIndicator;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n68_SubscrServiceIndicator[2];
		BYTE n76_ExchngeIdentity[15];
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
		BYTE n108_ForcedDisconnectionInformation;
	} RECORD_TYPE06;

typedef struct
	{
		BYTE n1_RecType[2];
		BYTE n8_OutputForSubscriber[1];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n16_Acategory[2];
		BYTE n18_AsubscrNumberingPlanIndicator[2];
		BYTE n37_DateForStartOfChargingUSA[6];
		BYTE n40_TimeForStartOfCharging24hour[6];
		BYTE n47_ChargedParty;
		BYTE n49_Price[8];
		BYTE n50_PulseChargingIndicator;
		BYTE n51_NumberOfMeterPulses[6];
		BYTE n52_OriginForCharging[4];
		BYTE n53_TariffClass[3];
		BYTE n66_ResultOfSubscriberServiceProcedure;
		BYTE n67_TypeOfProcedure[2];
		BYTE n76_ExchngeIdentity[15];
		BYTE n85_TypeOfSizure[2];
		BYTE n86_TypeOfIndicator[2];
		BYTE n87_TelecommunicationServiceCode[3];
	} RECORD_TYPE07;

typedef struct
	{
		BYTE n1_RecType[2];
		BYTE n13_LengthIndicatorForAnumber[2];
		BYTE n14_Anumber[10]; //??
		BYTE n112_DateOfExecutionOfCommand[6];
		BYTE n113_TimeOfExecutionOfComand[6];
		BYTE n114_CommandName[5];
	} RECORD_TYPE08;
//******************************************************************************
typedef struct 
	{
		BYTE n1_RecType[3];
		BYTE n2_CauseForOutput[2];
		BYTE n3_RecordNumber[3];
		BYTE n4_CallIdenificationNumber[9];
		BYTE n6_RecordSequenceNumber[9];
		BYTE n8_OutputForSubscriber[2];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n16_Acategory[3];
		BYTE n17_AnumberType[4];
		BYTE n18_AsubscrNumberingPlanIndicator[3];
		BYTE n19_AsubscrType[3];
		BYTE n20_LengthIndicatorForBsubscr[3];
		BYTE n21_Bnumber[19];
		BYTE n23_Bcategory[3];
		BYTE n24_BsubscrNumberType[4];
		BYTE n25_BsubscrNumberingPlanIndicator[3];
		BYTE n26_LengthIndicatorForCallingPartyNumber[3];
		BYTE n27_CallingPartyNumber[21];
		BYTE n30_LengthIndicatorForCalledPartyNumber[3];
		BYTE n31_CalledPartyNumber[19];
		BYTE n34_FaultCode[6];
		BYTE n35_CallStatus[2];
		BYTE n36_AbnormalReleaseIndicator[2];
		BYTE n37_DateForStartOfChargingUSA[7];
		BYTE n40_TimeForStartOfCharging24hour[7];
		BYTE n43_TimeForStopOfCharging[7];
		BYTE n44_TimeRegisterSizureStartCharging[7];
		BYTE n45_ChargeableDuration[7];
		BYTE n46_InterruptionTime[7];
		BYTE n47_ChargedParty[2];
		BYTE n48_ImmediateServiceIndicator[2];
		BYTE n49_Price[9];
		BYTE n50_PulseChargingIndicator[2];
		BYTE n51_NumberOfMeterPulses[7];
		BYTE n52_OriginForCharging[5];
		BYTE n53_TariffClass[4];
		BYTE n54_TariffSwitchingIndicator[2];
		BYTE n57_CallAttemptIndicator[2];
		BYTE n61_TypeOfCalledSubscriber[2];
		BYTE n62_TypeOfSignalling[2];
		BYTE n63_LengthIndicatorForAbbreviatedNumber[2];
		BYTE n64_AbbreviatedNumber[5];
		BYTE n66_ResultOfSubscriberServiceProcedure[2];
		BYTE n67_TypeOfProcedure[3];
		BYTE n68_SubscrServiceIndicator[3];
		BYTE n72_ConferenceCallIndicator[2];
		BYTE n76_ExchngeIdentity[16];
		BYTE n78_OutgouingRoute[8];
		BYTE n80_IncomingRoute[8];
		BYTE n82_ReroutingIndicator[2];
		BYTE n83_OriginatingCode[2];
		BYTE n84_DestinationCode[2];
		BYTE n85_TypeOfSizure[3];
		BYTE n86_TypeOfIndicator[3];
		BYTE n87_TelecommunicationServiceCode[4];
		BYTE n108_ForcedDisconnectionInformation[2];
		BYTE n109_CarrierAccessCode[7];
		BYTE n111_PresentationIndicator[2];
	} RECORD_TYPE00MY;

typedef struct
	{
		BYTE n1_RecType[3];
		BYTE n2_CauseForOutput[2];
		BYTE n3_RecordNumber[3];
		BYTE n4_CallIdenificationNumber[9];
		BYTE n6_RecordSequenceNumber[9];
		BYTE n8_OutputForSubscriber[2];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n16_Acategory[3];
		BYTE n17_AnumberType[4];
		BYTE n18_AsubscrNumberingPlanIndicator[3];
		BYTE n19_AsubscrType[3];
		BYTE n20_LengthIndicatorForBsubscr[3];
		BYTE n21_Bnumber[19];
		BYTE n23_Bcategory[3];
		BYTE n24_BsubscrNumberType[4];
		BYTE n25_BsubscrNumberingPlanIndicator[3];
		BYTE n26_LengthIndicatorForCallingPartyNumber[3];
		BYTE n27_CallingPartyNumber[21];
		BYTE n30_LengthIndicatorForCalledPartyNumber[3];
		BYTE n31_CalledPartyNumber[19];
		BYTE n34_FaultCode[6];
		BYTE n35_CallStatus[2];
		BYTE n36_AbnormalReleaseIndicator[2];
		BYTE n37_DateForStartOfChargingUSA[7];
		BYTE n40_TimeForStartOfCharging24hour[7];
		BYTE n43_TimeForStopOfCharging[7];
		BYTE n44_TimeRegisterSizureStartCharging[7];
		BYTE n45_ChargeableDuration[7];
		BYTE n46_InterruptionTime[7];
		BYTE n47_ChargedParty[2];
		BYTE n48_ImmediateServiceIndicator[2];
		BYTE n49_Price[9];
		BYTE n50_PulseChargingIndicator[2];
		BYTE n51_NumberOfMeterPulses[7];
		BYTE n52_OriginForCharging[5];
		BYTE n53_TariffClass[4];
		BYTE n54_TariffSwitchingIndicator[2];
		BYTE n57_CallAttemptIndicator[2];
		BYTE n58_CallAttemptState[3];
		BYTE n59_CauseCode[4];
		BYTE n60_LocationCode[3];
		BYTE n61_TypeOfCalledSubscriber[2];
		BYTE n62_TypeOfSignalling[2];
		BYTE n63_LengthIndicatorForAbbreviatedNumber[2];
		BYTE n64_AbbreviatedNumber[5];
		BYTE n66_ResultOfSubscriberServiceProcedure[2];
		BYTE n67_TypeOfProcedure[3];
		BYTE n68_SubscrServiceIndicator[3];
		BYTE n72_ConferenceCallIndicator[2];
		BYTE n76_ExchngeIdentity[16];
		BYTE n78_OutgouingRoute[8];
		BYTE n80_IncomingRoute[8];
		BYTE n82_ReroutingIndicator[2];
		BYTE n83_OriginatingCode[2];
		BYTE n84_DestinationCode[2];
		BYTE n85_TypeOfSizure[3];
		BYTE n86_TypeOfIndicator[3];
		BYTE n87_TelecommunicationServiceCode[4];
		BYTE n88_NetvorkConversionType[3];
		BYTE n89_NumberOfUserToUserMessagesDuringCall[5];
		BYTE n90_NumberOfUserToUser[2];
		BYTE n91_SubscrServiceForISDNSuplimentaryServices[17];
		BYTE n92_EndToEndAccessDataMap[9];
		BYTE n93_EndToEndAccessDataIndicator[2];
		BYTE n94_EndToEndAccessDataCounter[4];
		BYTE n108_ForcedDisconnectionInformation[2];
		BYTE n109_CarrierAccessCode[7];
		BYTE n111_PresentationIndicator[2];
	} RECORD_TYPE02MY;

typedef struct
	{
		BYTE n1_RecType[3];
		BYTE n2_CauseForOutput[2];
		BYTE n3_RecordNumber[3];
		BYTE n8_OutputForSubscriber[2];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n16_Acategory[3];
		BYTE n17_AnumberType[4];
		BYTE n18_AsubscrNumberingPlanIndicator[3];
		BYTE n19_AsubscrType[3];
		BYTE n20_LengthIndicatorForBsubscr[3];
		BYTE n21_Bnumber[19];
		BYTE n23_Bcategory[3];
		BYTE n24_BsubscrNumberType[4];
		BYTE n25_BsubscrNumberingPlanIndicator[3];
		BYTE n26_LengthIndicatorForCallingPartyNumber[3];
		BYTE n27_CallingPartyNumber[21];
		BYTE n28_LengthIndicatorForRedirectingNumber[3];
		BYTE n29_RedirectingNumber[21];
		BYTE n30_LengthIndicatorForCalledPartyNumber[3];
		BYTE n31_CalledPartyNumber[19];
		BYTE n32_LengthIndicatorForOriginallyCalledNumber[3];
		BYTE n33_OriginallyPartyNumber[21];
		BYTE n34_FaultCode[6];
		BYTE n35_CallStatus[2];
		BYTE n36_AbnormalReleaseIndicator[2];
		BYTE n37_DateForStartOfChargingUSA[7];
		BYTE n40_TimeForStartOfCharging24hour[7];
		BYTE n43_TimeForStopOfCharging[7];
		BYTE n44_TimeRegisterSizureStartCharging[7];
		BYTE n45_ChargeableDuration[7];
		BYTE n46_InterruptionTime[7];
		BYTE n47_ChargedParty[2];
		BYTE n48_ImmediateServiceIndicator[2];
		BYTE n49_Price[9];
		BYTE n50_PulseChargingIndicator[2];
		BYTE n51_NumberOfMeterPulses[7];
		BYTE n52_OriginForCharging[5];
		BYTE n53_TariffClass[4];
		BYTE n54_TariffSwitchingIndicator[2];
		BYTE n57_CallAttemptIndicator[2];
		BYTE n61_TypeOfCalledSubscriber[2];
		BYTE n62_TypeOfSignalling[2];
		BYTE n63_LengthIndicatorForAbbreviatedNumber[2];
		BYTE n64_AbbreviatedNumber[5];
		BYTE n66_ResultOfSubscriberServiceProcedure[2];
		BYTE n67_TypeOfProcedure[3];
		BYTE n68_SubscrServiceIndicator[3];
		BYTE n72_ConferenceCallIndicator[2];
		BYTE n76_ExchngeIdentity[16];
		BYTE n78_OutgouingRoute[8];
		BYTE n80_IncomingRoute[8];
		BYTE n82_ReroutingIndicator[2];
		BYTE n83_OriginatingCode[2];
		BYTE n84_DestinationCode[2];
		BYTE n85_TypeOfSizure[3];
		BYTE n86_TypeOfIndicator[3];
		BYTE n87_TelecommunicationServiceCode[4];
		BYTE n89_NumberOfUserToUserMessagesDuringCall[5];
		BYTE n90_NumberOfUserToUser[2];
		BYTE n91_SubscrServiceForISDNSuplimentaryServices[17];
		BYTE n92_EndToEndAccessDataMap[9];
		BYTE n93_EndToEndAccessDataIndicator[2];
		BYTE n94_EndToEndAccessDataCounter[4];
		BYTE n108_ForcedDisconnectionInformation[2];
		BYTE n109_CarrierAccessCode[7];
		BYTE n111_PresentationIndicator[2];
	} RECORD_TYPE04MY;

typedef struct
	{
		BYTE n1_RecType[3];
		BYTE n8_OutputForSubscriber[2];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n16_Acategory[3];
		BYTE n18_AsubscrNumberingPlanIndicator[3];
		BYTE n19_AsubscrType[3];
		BYTE n20_LengthIndicatorForBsubscr[3];
		BYTE n21_Bnumber[19];
		BYTE n23_Bcategory[3];
		BYTE n34_FaultCode[6];
		BYTE n35_CallStatus[2];
		BYTE n36_AbnormalReleaseIndicator[2];
		BYTE n37_DateForStartOfChargingUSA[7];
		BYTE n40_TimeForStartOfCharging24hour[7];
		BYTE n43_TimeForStopOfCharging[7];
		BYTE n44_TimeRegisterSizureStartCharging[7];
		BYTE n47_ChargedParty[2];
		BYTE n48_ImmediateServiceIndicator[2];
		BYTE n49_Price[9];
		BYTE n50_PulseChargingIndicator[2];
		BYTE n51_NumberOfMeterPulses[7];
		BYTE n52_OriginForCharging[5];
		BYTE n53_TariffClass[4];
		BYTE n66_ResultOfSubscriberServiceProcedure[2];
		BYTE n67_TypeOfProcedure[3];
		BYTE n68_SubscrServiceIndicator[3];
		BYTE n76_ExchngeIdentity[16];
		BYTE n85_TypeOfSizure[3];
		BYTE n86_TypeOfIndicator[3];
		BYTE n87_TelecommunicationServiceCode[4];
		BYTE n108_ForcedDisconnectionInformation[2];
	} RECORD_TYPE06MY;

typedef struct
	{
		BYTE n1_RecType[3];
		BYTE n8_OutputForSubscriber[2];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n16_Acategory[3];
		BYTE n18_AsubscrNumberingPlanIndicator[3];
		BYTE n37_DateForStartOfChargingUSA[7];
		BYTE n40_TimeForStartOfCharging24hour[7];
		BYTE n47_ChargedParty[2];
		BYTE n49_Price[9];
		BYTE n50_PulseChargingIndicator[2];
		BYTE n51_NumberOfMeterPulses[7];
		BYTE n52_OriginForCharging[5];
		BYTE n53_TariffClass[4];
		BYTE n66_ResultOfSubscriberServiceProcedure[2];
		BYTE n67_TypeOfProcedure[3];
		BYTE n76_ExchngeIdentity[16];
		BYTE n85_TypeOfSizure[3];
		BYTE n86_TypeOfIndicator[3];
		BYTE n87_TelecommunicationServiceCode[4];
	} RECORD_TYPE07MY;

typedef struct
	{
		BYTE n1_RecType[3];
		BYTE n13_LengthIndicatorForAnumber[3];
		BYTE n14_Anumber[11]; //??
		BYTE n112_DateOfExecutionOfCommand[7];
		BYTE n113_TimeOfExecutionOfComand[7];
		BYTE n114_CommandName[6];
	} RECORD_TYPE08MY;
//**************************************************************************************

class CTariffInBaseAXESet;

class CTariffInBaseAXEView : public CRecordView
{
protected: // create from serialization only
	CTariffInBaseAXEView();
	DECLARE_DYNCREATE(CTariffInBaseAXEView)

public:
	//{{AFX_DATA(CTariffInBaseAXEView)
	enum { IDD = IDD_TARIFFINBASEAXE_FORM };
	CStatic	m_cTimeGetRecFromFile;
	CStatic	m_cRecCount;
	CEdit	m_cBuffer;
	CStatic	m_cEnd;
	CStatic	m_cBegin;
	CProgressCtrl	m_cProgress2;
	CProgressCtrl	m_cProgress1;
	CTariffInBaseAXESet* m_pSet;
	CStatic	m_cTimeSetRecInBase;
	//}}AFX_DATA

// Attributes
public:
	CTariffInBaseAXEDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTariffInBaseAXEView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	CTime InSQLDataTimeFormat(CString USAdate, CString time);

	void AddRecInTable(RECORD_TYPE00MY * pRec);
	void AddRecInTable(RECORD_TYPE02MY * pRec);
	void AddRecInTable(RECORD_TYPE04MY * pRec);
	void AddRecInTable(RECORD_TYPE06MY * pRec);
	void AddRecInTable(RECORD_TYPE07MY * pRec);
	void AddRecInTable(RECORD_TYPE08MY * pRec);
	void FillRecordTypeMy(RECORD_TYPE00 * pRec, RECORD_TYPE00MY * pRecMy);
	void FillRecordTypeMy(RECORD_TYPE02 * pRec, RECORD_TYPE02MY * pRecMy);
	void FillRecordTypeMy(RECORD_TYPE04 * pRec, RECORD_TYPE04MY * pRecMy);
	void FillRecordTypeMy(RECORD_TYPE06 * pRec, RECORD_TYPE06MY * pRecMy);
	void FillRecordTypeMy(RECORD_TYPE07 * pRec, RECORD_TYPE07MY * pRecMy);
	void FillRecordTypeMy(RECORD_TYPE08 * pRec, RECORD_TYPE08MY * pRecMy);

	void GetRecordsFromBuf(char * buffer);
	CString RejectAllSimbols(CString linewithsimb);
	int LogLineAdd(CString line);
	void GetDataTime(CString *datatime);
	BOOL m_bOnSelectFile;
	virtual ~CTariffInBaseAXEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTariffInBaseAXEView)
	afx_msg void OnSelectTtfiles();
	afx_msg void OnUpdateSelectTtfiles(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TariffInBaseAXEView.cpp
inline CTariffInBaseAXEDoc* CTariffInBaseAXEView::GetDocument()
   { return (CTariffInBaseAXEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TARIFFINBASEAXEVIEW_H__55DDE55E_8C66_4D01_86C4_D5BC288D6295__INCLUDED_)
