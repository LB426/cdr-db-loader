#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "axecdr.h"
#include "main.h"

using namespace std;

char *DurSec(char *dur)
{
 char hh[3],mm[3],ss[3];
 hh[0]=dur[0];hh[1]=dur[1];hh[2]=0;
 mm[0]=dur[2];mm[1]=dur[3];mm[2]=0;
 ss[0]=dur[4];ss[1]=dur[5];ss[2]=0;
 int h=atoi(hh);
 int m=atoi(mm);
 int s=atoi(ss);
 int d=h*3600+m*60+s;
 snprintf(dur,11,"%d",d);
// printf("itoa=%s\n",buf); 

 return dur;
}

char * InSQLDataFormat(char * dt)
{
	char year[5], month[3], day[3];
	year[0]='2';
	year[1]='0';
	year[2]=dt[0];
	year[3]=dt[1];
	year[4]=0;
	if(CdrFileParams.firstRecordYear[0] == 0)
		strcpy(CdrFileParams.firstRecordYear, year);
	month[0]=dt[2];
	month[1]=dt[3];
	month[2]=0;
	if(CdrFileParams.firstRecordMonth[0] == 0)
		strcpy(CdrFileParams.firstRecordMonth, month);
	day[0]=dt[4];
	day[1]=dt[5];
	day[2]=0;
	strcpy(dt,year);
	strcat(dt,"-");
	strcat(dt,month);
	strcat(dt,"-");
	strcat(dt,day);
	return dt;
}

char * InSQLTimeFormat(char * tm)
{
 char hour[3], min[3], sec[3];
 hour[0]=tm[0];hour[1]=tm[1];hour[2]=0;
 min[0]=tm[2];min[1]=tm[3];min[2]=0;
 sec[0]=tm[4];sec[1]=tm[5];sec[2]=0; 
 strcpy(tm,hour);strcat(tm,":");strcat(tm,min);strcat(tm,":");strcat(tm,sec);
 return tm;
}

char * RejectAllSpaces(char * buf)
{
	char str[256];
	int i=0;
	int j=0;
	for ( i=0; i<strlen(buf); i++ )
	{
		if ( buf[i] != ' ' ) 
		{
			str[j]=buf[i];
			j++;
		}
	}
	str[j]=0;
	strcpy(buf,str);
	buf[j]=0;
	return buf;
}

char * gettime()
{
 time_t now;
 struct tm *ptr;
 char *c;
 time(&now);
 ptr=localtime(&now);
 c=asctime(ptr);
 c[strlen(c)-1]=0;
 return c;
}

void FillRecordTypeMy(RECORD_TYPE00 *pRec, RECORD_TYPE00MY *pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	memcpy((void*)pRecMy->n4_CallIdenificationNumber,(void*)pRec->n4_CallIdenificationNumber,sizeof(pRec->n4_CallIdenificationNumber));
	memcpy((void*)pRecMy->n6_RecordSequenceNumber,(void*)pRec->n6_RecordSequenceNumber,sizeof(pRec->n6_RecordSequenceNumber));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
}

void FillRecordTypeMy(RECORD_TYPE02 * pRec, RECORD_TYPE02MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	memcpy((void*)pRecMy->n4_CallIdenificationNumber,(void*)pRec->n4_CallIdenificationNumber,sizeof(pRec->n4_CallIdenificationNumber));
	memcpy((void*)pRecMy->n6_RecordSequenceNumber,(void*)pRec->n6_RecordSequenceNumber,sizeof(pRec->n6_RecordSequenceNumber));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	memcpy((void*)pRecMy->n58_CallAttemptState,(void*)pRec->n58_CallAttemptState,sizeof(pRec->n58_CallAttemptState));
	memcpy((void*)pRecMy->n59_CauseCode,(void*)pRec->n59_CauseCode,sizeof(pRec->n59_CauseCode));
	memcpy((void*)pRecMy->n60_LocationCode,(void*)pRec->n60_LocationCode,sizeof(pRec->n60_LocationCode));
	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	memcpy((void*)pRecMy->n88_NetvorkConversionType,(void*)pRec->n88_NetvorkConversionType,sizeof(pRec->n88_NetvorkConversionType));
	memcpy((void*)pRecMy->n89_NumberOfUserToUserMessagesDuringCall,(void*)pRec->n89_NumberOfUserToUserMessagesDuringCall,sizeof(pRec->n89_NumberOfUserToUserMessagesDuringCall));
	pRecMy->n90_NumberOfUserToUser[0] = pRec->n90_NumberOfUserToUser;
	memcpy((void*)pRecMy->n91_SubscrServiceForISDNSuplimentaryServices,(void*)pRec->n91_SubscrServiceForISDNSuplimentaryServices,sizeof(pRec->n91_SubscrServiceForISDNSuplimentaryServices));
	memcpy((void*)pRecMy->n92_EndToEndAccessDataMap,(void*)pRec->n92_EndToEndAccessDataMap,sizeof(pRec->n92_EndToEndAccessDataMap));
	pRecMy->n93_EndToEndAccessDataIndicator[0] = pRec->n93_EndToEndAccessDataIndicator;
	memcpy((void*)pRecMy->n94_EndToEndAccessDataCounter,(void*)pRec->n94_EndToEndAccessDataCounter,sizeof(pRec->n94_EndToEndAccessDataCounter));
	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
}

void FillRecordTypeMy(RECORD_TYPE04 * pRec, RECORD_TYPE04MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	memcpy((void*)pRecMy->n28_LengthIndicatorForRedirectingNumber,(void*)pRec->n28_LengthIndicatorForRedirectingNumber,sizeof(pRec->n28_LengthIndicatorForRedirectingNumber));
	memcpy((void*)pRecMy->n29_RedirectingNumber,(void*)pRec->n29_RedirectingNumber,sizeof(pRec->n29_RedirectingNumber));
	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	memcpy((void*)pRecMy->n32_LengthIndicatorForOriginallyCalledNumber,(void*)pRec->n32_LengthIndicatorForOriginallyCalledNumber,sizeof(pRec->n32_LengthIndicatorForOriginallyCalledNumber));
	memcpy((void*)pRecMy->n33_OriginallyPartyNumber,(void*)pRec->n33_OriginallyPartyNumber,sizeof(pRec->n33_OriginallyPartyNumber));
	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	memcpy((void*)pRecMy->n89_NumberOfUserToUserMessagesDuringCall,(void*)pRec->n89_NumberOfUserToUserMessagesDuringCall,sizeof(pRec->n89_NumberOfUserToUserMessagesDuringCall));
	pRecMy->n90_NumberOfUserToUser[0] = pRec->n90_NumberOfUserToUser;
	memcpy((void*)pRecMy->n91_SubscrServiceForISDNSuplimentaryServices,(void*)pRec->n91_SubscrServiceForISDNSuplimentaryServices,sizeof(pRec->n91_SubscrServiceForISDNSuplimentaryServices));
	memcpy((void*)pRecMy->n92_EndToEndAccessDataMap,(void*)pRec->n92_EndToEndAccessDataMap,sizeof(pRec->n92_EndToEndAccessDataMap));
	pRecMy->n93_EndToEndAccessDataIndicator[0] = pRec->n93_EndToEndAccessDataIndicator;
	memcpy((void*)pRecMy->n94_EndToEndAccessDataCounter,(void*)pRec->n94_EndToEndAccessDataCounter,sizeof(pRec->n94_EndToEndAccessDataCounter));
	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
}

void FillRecordTypeMy(RECORD_TYPE06 * pRec, RECORD_TYPE06MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
}

void FillRecordTypeMy(RECORD_TYPE07 * pRec, RECORD_TYPE07MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
}

void FillRecordTypeMy(RECORD_TYPE08 * pRec, RECORD_TYPE08MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n112_DateOfExecutionOfCommand,(void*)pRec->n112_DateOfExecutionOfCommand,sizeof(pRec->n112_DateOfExecutionOfCommand));
	memcpy((void*)pRecMy->n113_TimeOfExecutionOfComand,(void*)pRec->n113_TimeOfExecutionOfComand,sizeof(pRec->n113_TimeOfExecutionOfComand));
	memcpy((void*)pRecMy->n114_CommandName,(void*)pRec->n114_CommandName,sizeof(pRec->n114_CommandName));
}

void FillRecordTypeMy(RECORD_TYPE09 * pRec, RECORD_TYPE09MY * pRecMy)
{
	memcpy((void*)pRecMy->n1_RecType,(void*)pRec->n1_RecType,sizeof(pRec->n1_RecType));
	pRecMy->n2_CauseForOutput[0] = pRec->n2_CauseForOutput;
	memcpy((void*)pRecMy->n3_RecordNumber,(void*)pRec->n3_RecordNumber,sizeof(pRec->n3_RecordNumber));
	memcpy((void*)pRecMy->n4_CallIdenificationNumber,(void*)pRec->n4_CallIdenificationNumber,sizeof(pRec->n4_CallIdenificationNumber));
	memcpy((void*)pRecMy->n6_RecordSequenceNumber,(void*)pRec->n6_RecordSequenceNumber,sizeof(pRec->n6_RecordSequenceNumber));
	memcpy((void*)pRecMy->n8_OutputForSubscriber,(void*)pRec->n8_OutputForSubscriber,sizeof(pRec->n8_OutputForSubscriber));
	memcpy((void*)pRecMy->n13_LengthIndicatorForAnumber,(void*)pRec->n13_LengthIndicatorForAnumber,sizeof(pRec->n13_LengthIndicatorForAnumber));
	memcpy((void*)pRecMy->n14_Anumber,(void*)pRec->n14_Anumber,sizeof(pRec->n14_Anumber));
	memcpy((void*)pRecMy->n16_Acategory,(void*)pRec->n16_Acategory,sizeof(pRec->n16_Acategory));
	memcpy((void*)pRecMy->n17_AnumberType,(void*)pRec->n17_AnumberType,sizeof(pRec->n17_AnumberType));
	memcpy((void*)pRecMy->n18_AsubscrNumberingPlanIndicator,(void*)pRec->n18_AsubscrNumberingPlanIndicator,sizeof(pRec->n18_AsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n19_AsubscrType,(void*)pRec->n19_AsubscrType,sizeof(pRec->n19_AsubscrType));
	memcpy((void*)pRecMy->n20_LengthIndicatorForBsubscr,(void*)pRec->n20_LengthIndicatorForBsubscr,sizeof(pRec->n20_LengthIndicatorForBsubscr));
	memcpy((void*)pRecMy->n21_Bnumber,(void*)pRec->n21_Bnumber,sizeof(pRec->n21_Bnumber));
	memcpy((void*)pRecMy->n23_Bcategory,(void*)pRec->n23_Bcategory,sizeof(pRec->n23_Bcategory));
	memcpy((void*)pRecMy->n24_BsubscrNumberType,(void*)pRec->n24_BsubscrNumberType,sizeof(pRec->n24_BsubscrNumberType));
	memcpy((void*)pRecMy->n25_BsubscrNumberingPlanIndicator,(void*)pRec->n25_BsubscrNumberingPlanIndicator,sizeof(pRec->n25_BsubscrNumberingPlanIndicator));
	memcpy((void*)pRecMy->n26_LengthIndicatorForCallingPartyNumber,(void*)pRec->n26_LengthIndicatorForCallingPartyNumber,sizeof(pRec->n26_LengthIndicatorForCallingPartyNumber));
	memcpy((void*)pRecMy->n27_CallingPartyNumber,(void*)pRec->n27_CallingPartyNumber,sizeof(pRec->n27_CallingPartyNumber));
	memcpy((void*)pRecMy->n30_LengthIndicatorForCalledPartyNumber,(void*)pRec->n30_LengthIndicatorForCalledPartyNumber,sizeof(pRec->n30_LengthIndicatorForCalledPartyNumber));
	memcpy((void*)pRecMy->n31_CalledPartyNumber,(void*)pRec->n31_CalledPartyNumber,sizeof(pRec->n31_CalledPartyNumber));
	memcpy((void*)pRecMy->n34_FaultCode,(void*)pRec->n34_FaultCode,sizeof(pRec->n34_FaultCode));
	pRecMy->n35_CallStatus[0] = pRec->n35_CallStatus;
	pRecMy->n36_AbnormalReleaseIndicator[0] = pRec->n36_AbnormalReleaseIndicator;
	memcpy((void*)pRecMy->n37_DateForStartOfChargingUSA,(void*)pRec->n37_DateForStartOfChargingUSA,sizeof(pRec->n37_DateForStartOfChargingUSA));
	memcpy((void*)pRecMy->n40_TimeForStartOfCharging24hour,(void*)pRec->n40_TimeForStartOfCharging24hour,sizeof(pRec->n40_TimeForStartOfCharging24hour));
	memcpy((void*)pRecMy->n43_TimeForStopOfCharging,(void*)pRec->n43_TimeForStopOfCharging,sizeof(pRec->n43_TimeForStopOfCharging));
	memcpy((void*)pRecMy->n44_TimeRegisterSizureStartCharging,(void*)pRec->n44_TimeRegisterSizureStartCharging,sizeof(pRec->n44_TimeRegisterSizureStartCharging));
	memcpy((void*)pRecMy->n45_ChargeableDuration,(void*)pRec->n45_ChargeableDuration,sizeof(pRec->n45_ChargeableDuration));
	memcpy((void*)pRecMy->n46_InterruptionTime,(void*)pRec->n46_InterruptionTime,sizeof(pRec->n46_InterruptionTime));
	pRecMy->n47_ChargedParty[0] = pRec->n47_ChargedParty;
	pRecMy->n48_ImmediateServiceIndicator[0] = pRec->n48_ImmediateServiceIndicator;
	memcpy((void*)pRecMy->n49_Price,(void*)pRec->n49_Price,sizeof(pRec->n49_Price));
	pRecMy->n50_PulseChargingIndicator[0] = pRec->n50_PulseChargingIndicator;
	memcpy((void*)pRecMy->n51_NumberOfMeterPulses,(void*)pRec->n51_NumberOfMeterPulses,sizeof(pRec->n51_NumberOfMeterPulses));
	memcpy((void*)pRecMy->n52_OriginForCharging,(void*)pRec->n52_OriginForCharging,sizeof(pRec->n52_OriginForCharging));
	memcpy((void*)pRecMy->n53_TariffClass,(void*)pRec->n53_TariffClass,sizeof(pRec->n53_TariffClass));
	pRecMy->n54_TariffSwitchingIndicator[0] = pRec->n54_TariffSwitchingIndicator;
	pRecMy->n57_CallAttemptIndicator[0] = pRec->n57_CallAttemptIndicator;
	memcpy((void*)pRecMy->n58_CallAttemptState,(void*)pRec->n58_CallAttemptState,sizeof(pRec->n58_CallAttemptState));
	memcpy((void*)pRecMy->n59_CauseCode,(void*)pRec->n59_CauseCode,sizeof(pRec->n59_CauseCode));
	memcpy((void*)pRecMy->n60_LocationCode,(void*)pRec->n60_LocationCode,sizeof(pRec->n60_LocationCode));
	pRecMy->n61_TypeOfCalledSubscriber[0] = pRec->n61_TypeOfCalledSubscriber;
	pRecMy->n62_TypeOfSignalling[0] = pRec->n62_TypeOfSignalling;
	pRecMy->n63_LengthIndicatorForAbbreviatedNumber[0] = pRec->n63_LengthIndicatorForAbbreviatedNumber;
	memcpy((void*)pRecMy->n64_AbbreviatedNumber,(void*)pRec->n64_AbbreviatedNumber,sizeof(pRec->n64_AbbreviatedNumber));
	pRecMy->n66_ResultOfSubscriberServiceProcedure[0] = pRec->n66_ResultOfSubscriberServiceProcedure;
	memcpy((void*)pRecMy->n67_TypeOfProcedure,(void*)pRec->n67_TypeOfProcedure,sizeof(pRec->n67_TypeOfProcedure));
	memcpy((void*)pRecMy->n68_SubscrServiceIndicator,(void*)pRec->n68_SubscrServiceIndicator,sizeof(pRec->n68_SubscrServiceIndicator));
	pRecMy->n72_ConferenceCallIndicator[0] = pRec->n72_ConferenceCallIndicator;
	memcpy((void*)pRecMy->n76_ExchngeIdentity,(void*)pRec->n76_ExchngeIdentity,sizeof(pRec->n76_ExchngeIdentity));
	memcpy((void*)pRecMy->n78_OutgouingRoute,(void*)pRec->n78_OutgouingRoute,sizeof(pRec->n78_OutgouingRoute));
	memcpy((void*)pRecMy->n80_IncomingRoute,(void*)pRec->n80_IncomingRoute,sizeof(pRec->n80_IncomingRoute));
	pRecMy->n82_ReroutingIndicator[0] = pRec->n82_ReroutingIndicator;
	pRecMy->n83_OriginatingCode[0] = pRec->n83_OriginatingCode;
	pRecMy->n84_DestinationCode[0] = pRec->n84_DestinationCode;
	memcpy((void*)pRecMy->n85_TypeOfSizure,(void*)pRec->n85_TypeOfSizure,sizeof(pRec->n85_TypeOfSizure));
	memcpy((void*)pRecMy->n86_TypeOfIndicator,(void*)pRec->n86_TypeOfIndicator,sizeof(pRec->n86_TypeOfIndicator));
	memcpy((void*)pRecMy->n87_TelecommunicationServiceCode,(void*)pRec->n87_TelecommunicationServiceCode,sizeof(pRec->n87_TelecommunicationServiceCode));
	memcpy((void*)pRecMy->n88_NetvorkConversionType,(void*)pRec->n88_NetvorkConversionType,sizeof(pRec->n88_NetvorkConversionType));
	memcpy((void*)pRecMy->n89_NumberOfUserToUserMessagesDuringCall,(void*)pRec->n89_NumberOfUserToUserMessagesDuringCall,sizeof(pRec->n89_NumberOfUserToUserMessagesDuringCall));
	pRecMy->n90_NumberOfUserToUser[0] = pRec->n90_NumberOfUserToUser;
	memcpy((void*)pRecMy->n91_SubscrServiceForISDNSuplimentaryServices,(void*)pRec->n91_SubscrServiceForISDNSuplimentaryServices,sizeof(pRec->n91_SubscrServiceForISDNSuplimentaryServices));
	memcpy((void*)pRecMy->n92_EndToEndAccessDataMap,(void*)pRec->n92_EndToEndAccessDataMap,sizeof(pRec->n92_EndToEndAccessDataMap));
	pRecMy->n93_EndToEndAccessDataIndicator[0] = pRec->n93_EndToEndAccessDataIndicator;
	memcpy((void*)pRecMy->n94_EndToEndAccessDataCounter,(void*)pRec->n94_EndToEndAccessDataCounter,sizeof(pRec->n94_EndToEndAccessDataCounter));
	pRecMy->n108_ForcedDisconnectionInformation[0] = pRec->n108_ForcedDisconnectionInformation;
	memcpy((void*)pRecMy->n109_CarrierAccessCode,(void*)pRec->n109_CarrierAccessCode,sizeof(pRec->n109_CarrierAccessCode));
	pRecMy->n111_PresentationIndicator[0] = pRec->n111_PresentationIndicator;
}

void PrintRec(RECORD_TYPE00MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	RejectAllSpaces((char*)pRec->n21_Bnumber);
	RejectAllSpaces((char*)pRec->n78_OutgouingRoute);
	RejectAllSpaces((char*)pRec->n80_IncomingRoute);
	fprintf(globalArgs.dstFile,"%s %s %s %s %s %s %s %s %s\n", pRec->n14_Anumber, pRec->n21_Bnumber, n37, n40, n43, n45, pRec->n78_OutgouingRoute, pRec->n80_IncomingRoute, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE02MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	RejectAllSpaces((char*)pRec->n21_Bnumber);
	RejectAllSpaces((char*)pRec->n78_OutgouingRoute);
	RejectAllSpaces((char*)pRec->n80_IncomingRoute);
	fprintf(globalArgs.dstFile,"%s %s %s %s %s %s %s %s %s\n", pRec->n14_Anumber, pRec->n21_Bnumber, n37, n40, n43, n45, pRec->n78_OutgouingRoute, pRec->n80_IncomingRoute, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE04MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	RejectAllSpaces((char*)pRec->n21_Bnumber);
	RejectAllSpaces((char*)pRec->n78_OutgouingRoute);
	RejectAllSpaces((char*)pRec->n80_IncomingRoute);
	fprintf(globalArgs.dstFile,"%s %s %s %s %s %s %s %s %s\n", pRec->n14_Anumber, pRec->n21_Bnumber, n37, n40, n43, n45, pRec->n78_OutgouingRoute, pRec->n80_IncomingRoute, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE06MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	RejectAllSpaces((char*)pRec->n21_Bnumber);
	fprintf(globalArgs.dstFile,"%s %s %s %s %s undefined undefined undefined %s\n", pRec->n14_Anumber, pRec->n21_Bnumber, n37, n40, n43, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE07MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	fprintf(globalArgs.dstFile,"%s undefined %s %s undefined undefined undefined undefined %s\n", pRec->n14_Anumber, n37, n40, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE08MY *pRec)
{
	RejectAllSpaces((char*)pRec->n14_Anumber);
	fprintf(globalArgs.dstFile,"%s undefined undefined undefined undefined undefined undefined undefined %s\n", pRec->n14_Anumber, globalArgs.srcFilenameBasename);
}

void PrintRec(RECORD_TYPE09MY *pRec)
{
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	RejectAllSpaces((char*)pRec->n14_Anumber);
	RejectAllSpaces((char*)pRec->n21_Bnumber);
	RejectAllSpaces((char*)pRec->n78_OutgouingRoute);
	RejectAllSpaces((char*)pRec->n80_IncomingRoute);
	fprintf(globalArgs.dstFile,"%s %s %s %s %s %s %s %s %s\n", pRec->n14_Anumber, pRec->n21_Bnumber, n37, n40, n43, n45, pRec->n78_OutgouingRoute, pRec->n80_IncomingRoute, globalArgs.srcFilenameBasename);
}

void GetRecordsFromBuf(char * buffer)
{
	char * pBuffer = buffer;
	unsigned int x;
	char rectype[2] = {0};

	while ((x = (pBuffer - buffer)) < 2048)
	{
		rectype[0] = *pBuffer;
		rectype[1] = *(pBuffer + 1);
		if( memcmp(rectype,NE,sizeof(NE)) == 0 )
		{
			RECORD_TYPE00 * pRecType00 = (RECORD_TYPE00*)pBuffer;
			RECORD_TYPE00MY RecType00My = {0};
			FillRecordTypeMy(pRecType00, &RecType00My);
			PrintRec(&RecType00My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE00);
			continue;
		}
		else if( memcmp(rectype,NEI,sizeof(NEI)) == 0 )
		{
			RECORD_TYPE02 * pRecType02 = (RECORD_TYPE02*)pBuffer;
			RECORD_TYPE02MY RecType02My = {0};
			FillRecordTypeMy(pRecType02, &RecType02My);
			PrintRec(&RecType02My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE02);
			continue;
		}
		else if( memcmp(rectype,CDE,sizeof(CDE)) == 0 )
		{
			RECORD_TYPE04 * pRecType04 = (RECORD_TYPE04*)pBuffer;
			RECORD_TYPE04MY RecType04My = {0};
			FillRecordTypeMy(pRecType04, &RecType04My);
			PrintRec(&RecType04My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE04);
			continue;
		}
		else if( memcmp(rectype,SP,sizeof(SP)) == 0 )
		{
			RECORD_TYPE06 * pRecType06 = (RECORD_TYPE06*)pBuffer;
			RECORD_TYPE06MY RecType06My = {0};
			FillRecordTypeMy(pRecType06, &RecType06My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE06);
			continue;
		}
		else if( memcmp(rectype,NC,sizeof(NC)) == 0 )
		{
			RECORD_TYPE07 * pRecType07 = (RECORD_TYPE07*)pBuffer;
			RECORD_TYPE07MY RecType07My = {0};
			FillRecordTypeMy(pRecType07, &RecType07My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE07);
			continue;
		}
		else if( memcmp(rectype,SSC,sizeof(SSC)) == 0 )
		{
			RECORD_TYPE08 * pRecType08 = (RECORD_TYPE08*)pBuffer;
			RECORD_TYPE08MY RecType08My = {0};
			FillRecordTypeMy(pRecType08, &RecType08My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE08);
			continue;
		}
		else if( memcmp(rectype,NEIE,sizeof(NEIE)) == 0 )
		{
			RECORD_TYPE09 * pRecType09 = (RECORD_TYPE09*)pBuffer;
			RECORD_TYPE09MY RecType09My = {0};
			FillRecordTypeMy(pRecType09, &RecType09My);
			pBuffer = pBuffer + sizeof(RECORD_TYPE09);
			continue;
		}
		else if (*pBuffer == 0)
		{
			pBuffer++;
		}
		else
		{
			fprintf(globalArgs.dstFile,"Unknown Record Type: %c%c\n",*pBuffer,*(pBuffer+1));
			break;
		}
	}
}
