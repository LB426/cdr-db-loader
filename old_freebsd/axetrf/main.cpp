#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include <libpq-fe.h>

using namespace std;

PGconn *conn; 
PGresult *res;

static void exit_nicely(PGconn *conn)
{
 PQfinish(conn);
 exit(1);
}

void InsertRec(char * sql)
{
 res = PQexec(conn, sql);
 if (PQresultStatus(res) != PGRES_COMMAND_OK)
	printf("Command failed: %sSQL:\n%s", PQerrorMessage(conn),sql);
 PQclear(res);
 //printf("%s\n",sql);
 return;
}

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
 year[0]='2';year[1]='0',year[2]=dt[0];year[3]=dt[1];year[4]=0;
 month[0]=dt[2];month[1]=dt[3];month[2]=0;
 day[0]=dt[4];day[1]=dt[5];day[2]=0;
 strcpy(dt,year);strcat(dt,"-");strcat(dt,month);strcat(dt,"-");strcat(dt,day);
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

char * RejectAllSimbols(char * buf)
{
 char str[256];
 int i=0; int j=0;
 for (i=0;i<strlen(buf);i++)
 {
  if(buf[i] != ' ') 
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

void FillRecordTypeMy(RECORD_TYPE02 * pRec, RECORD_TYPE02MY * pRecMy)
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

void FillRecordTypeMy(RECORD_TYPE04 * pRec, RECORD_TYPE04MY * pRecMy)
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
	pRecMy->n28_LengthIndicatorForRedirectingNumber[2] = '\0';

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

void FillRecordTypeMy(RECORD_TYPE06 * pRec, RECORD_TYPE06MY * pRecMy)
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

void FillRecordTypeMy(RECORD_TYPE07 * pRec, RECORD_TYPE07MY * pRecMy)
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

void FillRecordTypeMy(RECORD_TYPE08 * pRec, RECORD_TYPE08MY * pRecMy)
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

void AddRecInTable(RECORD_TYPE00MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n2 = RejectAllSimbols((char*)pRec->n2_CauseForOutput);
	char *n3 = RejectAllSimbols((char*)pRec->n3_RecordNumber);
	char *n4 = RejectAllSimbols((char*)pRec->n4_CallIdenificationNumber);
	char *n6 = RejectAllSimbols((char*)pRec->n6_RecordSequenceNumber);
	char *n8 = RejectAllSimbols((char*)pRec->n8_OutputForSubscriber);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char *n16 = RejectAllSimbols((char*)pRec->n16_Acategory);
	char *n17 = RejectAllSimbols((char*)pRec->n17_AnumberType);
	char *n18 = RejectAllSimbols((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	char *n19 = RejectAllSimbols((char*)pRec->n19_AsubscrType);
	char *n20 = RejectAllSimbols((char*)pRec->n20_LengthIndicatorForBsubscr);
	char *n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	char *n23 = RejectAllSimbols((char*)pRec->n23_Bcategory);
	char *n24 = RejectAllSimbols((char*)pRec->n24_BsubscrNumberType);
	char *n25 = RejectAllSimbols((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	char *n26 = RejectAllSimbols((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	char *n27 = RejectAllSimbols((char*)pRec->n27_CallingPartyNumber);
	char *n30 = RejectAllSimbols((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	char *n31 = RejectAllSimbols((char*)pRec->n31_CalledPartyNumber);
	char *n34 = RejectAllSimbols((char*)pRec->n34_FaultCode);
	char *n35 = RejectAllSimbols((char*)pRec->n35_CallStatus);

	char n36[2];
	n36[1]=0;
	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1){n36[0]='1';}else{n36[0] = '0';}

	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n44[12];n44[11]=0;strcpy(n44,(char*)pRec->n44_TimeRegisterSizureStartCharging);InSQLTimeFormat(n44);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	char n46[12];n46[11]=0;strcpy(n46,(char*)pRec->n46_InterruptionTime);InSQLTimeFormat(n46);

	char *n47 = RejectAllSimbols((char*)pRec->n47_ChargedParty);
	char n48[2];n48[1]=0;
	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1){n48[0] = '1';}else{n48[0] = '0';}
	 
	char *n49 = RejectAllSimbols((char*)pRec->n49_Price);
	char *n50 = RejectAllSimbols((char*)pRec->n50_PulseChargingIndicator);
	char *n51 = RejectAllSimbols((char*)pRec->n51_NumberOfMeterPulses);
	char *n52 = RejectAllSimbols((char*)pRec->n52_OriginForCharging);
	char *n53 = RejectAllSimbols((char*)pRec->n53_TariffClass);
	char *n54 = RejectAllSimbols((char*)pRec->n54_TariffSwitchingIndicator);
	char *n57 = RejectAllSimbols((char*)pRec->n57_CallAttemptIndicator);
	char *n61 = RejectAllSimbols((char*)pRec->n61_TypeOfCalledSubscriber);
	char *n62 = RejectAllSimbols((char*)pRec->n62_TypeOfSignalling);
	char *n63 = RejectAllSimbols((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	char *n64 = RejectAllSimbols((char*)pRec->n64_AbbreviatedNumber);
	char *n66 = RejectAllSimbols((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	char *n67 = RejectAllSimbols((char*)pRec->n67_TypeOfProcedure);
	char *n68 = RejectAllSimbols((char*)pRec->n68_SubscrServiceIndicator);
	
	char n72[2];n72[1]=0;	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1){n72[0] = '1';}else{n72[0] = '0';}
	
	char *n76 = RejectAllSimbols((char*)pRec->n76_ExchngeIdentity);
	char *n78 = RejectAllSimbols((char*)pRec->n78_OutgouingRoute);
	char *n80 = RejectAllSimbols((char*)pRec->n80_IncomingRoute);

	char n82[2];n82[1]=0;	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1){n82[0] = '1';}else{n82[0] = '0';}

	char *n83 = RejectAllSimbols((char*)pRec->n83_OriginatingCode);
	char *n84 = RejectAllSimbols((char*)pRec->n84_DestinationCode);
	char *n85 = RejectAllSimbols((char*)pRec->n85_TypeOfSizure);
	char *n86 = RejectAllSimbols((char*)pRec->n86_TypeOfIndicator);
	char *n87 = RejectAllSimbols((char*)pRec->n87_TelecommunicationServiceCode);
	char *n108 = RejectAllSimbols((char*)pRec->n108_ForcedDisconnectionInformation);
	char *n109 = RejectAllSimbols((char*)pRec->n109_CarrierAccessCode);

	char n111[2];n111[1]=0;
	if (atoi((char*)pRec->n111_PresentationIndicator) == 1){n111[0] = '1';}else{n111[0] = '0';}

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));

	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n2)!=0){strcat(fields,"n2,");strcat(values,n2);strcat(values,",");}
	if(strlen(n3)!=0){strcat(fields,"n3,");strcat(values,n3);strcat(values,",");}
	if(strlen(n4)!=0){strcat(fields,"n4,");strcat(values,n4);strcat(values,",");}
	if(strlen(n6)!=0){strcat(fields,"n6,");strcat(values,n6);strcat(values,",");}
	if(strlen(n8)!=0){strcat(fields,"n8,");strcat(values,n8);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n16)!=0){strcat(fields,"n16,");strcat(values,n16);strcat(values,",");}
	if(strlen(n17)!=0){strcat(fields,"n17,");strcat(values,n17);strcat(values,",");}
	if(strlen(n18)!=0){strcat(fields,"n18,");strcat(values,n18);strcat(values,",");}
	if(strlen(n19)!=0){strcat(fields,"n19,");strcat(values,n19);strcat(values,",");}
	if(strlen(n20)!=0){strcat(fields,"n20,");strcat(values,n20);strcat(values,",");}
	if(strlen(n21)!=0){strcat(fields,"n21,");strcat(values,"'");strcat(values,n21);strcat(values,"',");}
	if(strlen(n23)!=0){strcat(fields,"n23,");strcat(values,n23);strcat(values,",");}
	if(strlen(n24)!=0){strcat(fields,"n24,");strcat(values,n24);strcat(values,",");}
	if(strlen(n25)!=0){strcat(fields,"n25,");strcat(values,n25);strcat(values,",");}
	if(strlen(n26)!=0){strcat(fields,"n26,");strcat(values,n26);strcat(values,",");}
	if(strlen(n27)==0){n27="nomerNEopred";}
	if(strlen(n27)!=0){strcat(fields,"n27,");strcat(values,"'");strcat(values,n27);strcat(values,"',");}
	if(strlen(n30)!=0){strcat(fields,"n30,");strcat(values,n30);strcat(values,",");}
	if(strlen(n31)==0){n31="nomerNEopred";}
	if(strlen(n31)!=0){strcat(fields,"n31,");strcat(values,"'");strcat(values,n31);strcat(values,"',");}
	if(strlen(n34)!=0){strcat(fields,"n34,");strcat(values,n34);strcat(values,",");}
	if(strlen(n35)!=0){strcat(fields,"n35,");strcat(values,n35);strcat(values,",");}
	if(strlen(n36)!=0){strcat(fields,"n36,");strcat(values,n36);strcat(values,",");}
	if(strlen(n37)!=0){strcat(fields,"n37,");strcat(values,"'");strcat(values,n37);strcat(values,"',");}
	if(strlen(n40)!=0){strcat(fields,"n40,");strcat(values,"'");strcat(values,n40);strcat(values,"',");}
	if(strlen(n43)!=0){strcat(fields,"n43,");strcat(values,"'");strcat(values,n43);strcat(values,"',");}
	if(strlen(n44)!=0){strcat(fields,"n44,");strcat(values,"'");strcat(values,n44);strcat(values,"',");}
	if(strlen(n45)!=0){strcat(fields,"n45,");strcat(values,n45);strcat(values,",");}
	if(strlen(n46)!=0){strcat(fields,"n46,");strcat(values,"'");strcat(values,n46);strcat(values,"',");}
	if(strlen(n47)!=0){strcat(fields,"n47,");strcat(values,n47);strcat(values,",");}
	if(strlen(n48)!=0){strcat(fields,"n48,");strcat(values,n48);strcat(values,",");}
	if(strlen(n49)!=0){strcat(fields,"n49,");strcat(values,n49);strcat(values,",");}
	if(strlen(n50)!=0){strcat(fields,"n50,");strcat(values,n50);strcat(values,",");}
	if(strlen(n51)!=0){strcat(fields,"n51,");strcat(values,n51);strcat(values,",");}
	if(strlen(n52)!=0){strcat(fields,"n52,");strcat(values,n52);strcat(values,",");}
	if(strlen(n53)!=0){strcat(fields,"n53,");strcat(values,n53);strcat(values,",");}
	if(strlen(n54)!=0){strcat(fields,"n54,");strcat(values,n54);strcat(values,",");}
	if(strlen(n57)!=0){strcat(fields,"n57,");strcat(values,n57);strcat(values,",");}
	if(strlen(n61)!=0){strcat(fields,"n61,");strcat(values,n61);strcat(values,",");}
	if(strlen(n62)!=0){strcat(fields,"n62,");strcat(values,n62);strcat(values,",");}
	if(strlen(n63)!=0){strcat(fields,"n63,");strcat(values,n63);strcat(values,",");}
	if(strlen(n64)!=0){strcat(fields,"n64,");strcat(values,n64);strcat(values,",");}
	if(strlen(n66)!=0){strcat(fields,"n66,");strcat(values,"'");strcat(values,n66);strcat(values,"',");}
	if(strlen(n67)!=0){strcat(fields,"n67,");strcat(values,"'");strcat(values,n67);strcat(values,"',");}
	if(strlen(n68)!=0){strcat(fields,"n68,");strcat(values,"'");strcat(values,n68);strcat(values,"',");}
	if(strlen(n72)!=0){strcat(fields,"n72,");strcat(values,"'");strcat(values,n72);strcat(values,"',");}
	if(strlen(n76)!=0){strcat(fields,"n76,");strcat(values,"'");strcat(values,n76);strcat(values,"',");}
	if(strlen(n78)!=0){strcat(fields,"n78,");strcat(values,"'");strcat(values,n78);strcat(values,"',");}
	if(strlen(n80)!=0){strcat(fields,"n80,");strcat(values,"'");strcat(values,n80);strcat(values,"',");}
	if(strlen(n82)!=0){strcat(fields,"n82,");strcat(values,"'");strcat(values,n82);strcat(values,"',");}
	if(strlen(n83)!=0){strcat(fields,"n83,");strcat(values,"'");strcat(values,n83);strcat(values,"',");}
	if(strlen(n84)!=0){strcat(fields,"n84,");strcat(values,"'");strcat(values,n84);strcat(values,"',");}
	if(strlen(n85)!=0){strcat(fields,"n85,");strcat(values,"'");strcat(values,n85);strcat(values,"',");}
	if(strlen(n86)!=0){strcat(fields,"n86,");strcat(values,"'");strcat(values,n86);strcat(values,"',");}
	if(strlen(n87)!=0){strcat(fields,"n87,");strcat(values,"'");strcat(values,n87);strcat(values,"',");}
	if(strlen(n108)!=0){strcat(fields,"n108,");strcat(values,"'");strcat(values,n108);strcat(values,"',");}
	if(strlen(n109)!=0){strcat(fields,"n109,");strcat(values,"'");strcat(values,n109);strcat(values,"',");}
	if(strlen(n111)!=0){strcat(fields,"n111");strcat(values,"'");strcat(values,n111);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void AddRecInTable(RECORD_TYPE02MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n2 = RejectAllSimbols((char*)pRec->n2_CauseForOutput);
	char *n3 = RejectAllSimbols((char*)pRec->n3_RecordNumber);
	char *n4 = RejectAllSimbols((char*)pRec->n4_CallIdenificationNumber);
	char *n6 = RejectAllSimbols((char*)pRec->n6_RecordSequenceNumber);
	char *n8 = RejectAllSimbols((char*)pRec->n8_OutputForSubscriber);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char *n16 = RejectAllSimbols((char*)pRec->n16_Acategory);
	char *n17 = RejectAllSimbols((char*)pRec->n17_AnumberType);
	char *n18 = RejectAllSimbols((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	char *n19 = RejectAllSimbols((char*)pRec->n19_AsubscrType);
	char *n20 = RejectAllSimbols((char*)pRec->n20_LengthIndicatorForBsubscr);
	char *n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	char *n23 = RejectAllSimbols((char*)pRec->n23_Bcategory);
	char *n24 = RejectAllSimbols((char*)pRec->n24_BsubscrNumberType);
	char *n25 = RejectAllSimbols((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	char *n26 = RejectAllSimbols((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	char *n27 = RejectAllSimbols((char*)pRec->n27_CallingPartyNumber);
	char *n30 = RejectAllSimbols((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	char *n31 = RejectAllSimbols((char*)pRec->n31_CalledPartyNumber);
	char *n34 = RejectAllSimbols((char*)pRec->n34_FaultCode);
	char *n35 = RejectAllSimbols((char*)pRec->n35_CallStatus);

	char n36[2];
	n36[1]=0;
	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1){n36[0]='1';}else{n36[0] = '0';}

	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n44[12];n44[11]=0;strcpy(n44,(char*)pRec->n44_TimeRegisterSizureStartCharging);InSQLTimeFormat(n44);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	char n46[12];n46[11]=0;strcpy(n46,(char*)pRec->n46_InterruptionTime);InSQLTimeFormat(n46);

	char *n47 = RejectAllSimbols((char*)pRec->n47_ChargedParty);
	char n48[2];n48[1]=0;
	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1){n48[0] = '1';}else{n48[0] = '0';}
	 
	char *n49 = RejectAllSimbols((char*)pRec->n49_Price);
	char *n50 = RejectAllSimbols((char*)pRec->n50_PulseChargingIndicator);
	char *n51 = RejectAllSimbols((char*)pRec->n51_NumberOfMeterPulses);
	char *n52 = RejectAllSimbols((char*)pRec->n52_OriginForCharging);
	char *n53 = RejectAllSimbols((char*)pRec->n53_TariffClass);
	char *n54 = RejectAllSimbols((char*)pRec->n54_TariffSwitchingIndicator);
	char *n57 = RejectAllSimbols((char*)pRec->n57_CallAttemptIndicator);
	char *n58 = RejectAllSimbols((char*)pRec->n58_CallAttemptState);
	char *n59 = RejectAllSimbols((char*)pRec->n59_CauseCode);
	char *n60 = RejectAllSimbols((char*)pRec->n60_LocationCode);
	char *n61 = RejectAllSimbols((char*)pRec->n61_TypeOfCalledSubscriber);
	char *n62 = RejectAllSimbols((char*)pRec->n62_TypeOfSignalling);
	char *n63 = RejectAllSimbols((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	char *n64 = RejectAllSimbols((char*)pRec->n64_AbbreviatedNumber);
	char *n66 = RejectAllSimbols((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	char *n67 = RejectAllSimbols((char*)pRec->n67_TypeOfProcedure);
	char *n68 = RejectAllSimbols((char*)pRec->n68_SubscrServiceIndicator);
	
	char n72[2];n72[1]=0;	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1){n72[0] = '1';}else{n72[0] = '0';}
	
	char *n76 = RejectAllSimbols((char*)pRec->n76_ExchngeIdentity);
	char *n78 = RejectAllSimbols((char*)pRec->n78_OutgouingRoute);
	char *n80 = RejectAllSimbols((char*)pRec->n80_IncomingRoute);

	char n82[2];n82[1]=0;	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1){n82[0] = '1';}else{n82[0] = '0';}

	char *n83 = RejectAllSimbols((char*)pRec->n83_OriginatingCode);
	char *n84 = RejectAllSimbols((char*)pRec->n84_DestinationCode);
	char *n85 = RejectAllSimbols((char*)pRec->n85_TypeOfSizure);
	char *n86 = RejectAllSimbols((char*)pRec->n86_TypeOfIndicator);
	char *n87 = RejectAllSimbols((char*)pRec->n87_TelecommunicationServiceCode);
	char *n88 = RejectAllSimbols((char*)pRec->n88_NetvorkConversionType);
	char *n89 = RejectAllSimbols((char*)pRec->n89_NumberOfUserToUserMessagesDuringCall);
	char *n90 = RejectAllSimbols((char*)pRec->n90_NumberOfUserToUser);
	char *n91 = RejectAllSimbols((char*)pRec->n91_SubscrServiceForISDNSuplimentaryServices);
	char *n92 = RejectAllSimbols((char*)pRec->n92_EndToEndAccessDataMap);
	char *n93 = RejectAllSimbols((char*)pRec->n93_EndToEndAccessDataIndicator);
	char *n94 = RejectAllSimbols((char*)pRec->n94_EndToEndAccessDataCounter);
	char *n108 = RejectAllSimbols((char*)pRec->n108_ForcedDisconnectionInformation);
	char *n109 = RejectAllSimbols((char*)pRec->n109_CarrierAccessCode);

	char n111[2];n111[1]=0;
	if (atoi((char*)pRec->n111_PresentationIndicator) == 1){n111[0] = '1';}else{n111[0] = '0';}

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));
 
	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n2)!=0){strcat(fields,"n2,");strcat(values,n2);strcat(values,",");}
	if(strlen(n3)!=0){strcat(fields,"n3,");strcat(values,n3);strcat(values,",");}
	if(strlen(n4)!=0){strcat(fields,"n4,");strcat(values,n4);strcat(values,",");}
	if(strlen(n6)!=0){strcat(fields,"n6,");strcat(values,n6);strcat(values,",");}
	if(strlen(n8)!=0){strcat(fields,"n8,");strcat(values,n8);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n16)!=0){strcat(fields,"n16,");strcat(values,n16);strcat(values,",");}
	if(strlen(n17)!=0){strcat(fields,"n17,");strcat(values,n17);strcat(values,",");}
	if(strlen(n18)!=0){strcat(fields,"n18,");strcat(values,n18);strcat(values,",");}
	if(strlen(n19)!=0){strcat(fields,"n19,");strcat(values,n19);strcat(values,",");}
	if(strlen(n20)!=0){strcat(fields,"n20,");strcat(values,n20);strcat(values,",");}
	if(strlen(n21)!=0){strcat(fields,"n21,");strcat(values,"'");strcat(values,n21);strcat(values,"',");}
	if(strlen(n23)!=0){strcat(fields,"n23,");strcat(values,n23);strcat(values,",");}
	if(strlen(n24)!=0){strcat(fields,"n24,");strcat(values,n24);strcat(values,",");}
	if(strlen(n25)!=0){strcat(fields,"n25,");strcat(values,n25);strcat(values,",");}
	if(strlen(n26)!=0){strcat(fields,"n26,");strcat(values,n26);strcat(values,",");}
	if(strlen(n27)==0){n27="nomerNEopred";}
	if(strlen(n27)!=0){strcat(fields,"n27,");strcat(values,"'");strcat(values,n27);strcat(values,"',");}
	if(strlen(n30)!=0){strcat(fields,"n30,");strcat(values,n30);strcat(values,",");}
	if(strlen(n31)==0){n31="nomerNEopred";}
	if(strlen(n31)!=0){strcat(fields,"n31,");strcat(values,"'");strcat(values,n31);strcat(values,"',");}
	if(strlen(n34)!=0){strcat(fields,"n34,");strcat(values,n34);strcat(values,",");}
	if(strlen(n35)!=0){strcat(fields,"n35,");strcat(values,n35);strcat(values,",");}
	if(strlen(n36)!=0){strcat(fields,"n36,");strcat(values,n36);strcat(values,",");}
	if(strlen(n37)!=0){strcat(fields,"n37,");strcat(values,"'");strcat(values,n37);strcat(values,"',");}
	if(strlen(n40)!=0){strcat(fields,"n40,");strcat(values,"'");strcat(values,n40);strcat(values,"',");}
	if(strlen(n43)!=0){strcat(fields,"n43,");strcat(values,"'");strcat(values,n43);strcat(values,"',");}
	if(strlen(n44)!=0){strcat(fields,"n44,");strcat(values,"'");strcat(values,n44);strcat(values,"',");}
	if(strlen(n45)!=0){strcat(fields,"n45,");strcat(values,n45);strcat(values,",");}
	if(strlen(n46)!=0){strcat(fields,"n46,");strcat(values,"'");strcat(values,n46);strcat(values,"',");}
	if(strlen(n47)!=0){strcat(fields,"n47,");strcat(values,n47);strcat(values,",");}
	if(strlen(n48)!=0){strcat(fields,"n48,");strcat(values,n48);strcat(values,",");}
	if(strlen(n49)!=0){strcat(fields,"n49,");strcat(values,n49);strcat(values,",");}
	if(strlen(n50)!=0){strcat(fields,"n50,");strcat(values,n50);strcat(values,",");}
	if(strlen(n51)!=0){strcat(fields,"n51,");strcat(values,n51);strcat(values,",");}
	if(strlen(n52)!=0){strcat(fields,"n52,");strcat(values,n52);strcat(values,",");}
	if(strlen(n53)!=0){strcat(fields,"n53,");strcat(values,n53);strcat(values,",");}
	if(strlen(n54)!=0){strcat(fields,"n54,");strcat(values,n54);strcat(values,",");}
	if(strlen(n57)!=0){strcat(fields,"n57,");strcat(values,n57);strcat(values,",");}
	if(strlen(n58)!=0){strcat(fields,"n58,");strcat(values,n58);strcat(values,",");}
	if(strlen(n59)!=0){strcat(fields,"n59,");strcat(values,n59);strcat(values,",");}
	if(strlen(n60)!=0){strcat(fields,"n60,");strcat(values,n60);strcat(values,",");}
	if(strlen(n61)!=0){strcat(fields,"n61,");strcat(values,n61);strcat(values,",");}
	if(strlen(n62)!=0){strcat(fields,"n62,");strcat(values,n62);strcat(values,",");}
	if(strlen(n63)!=0){strcat(fields,"n63,");strcat(values,n63);strcat(values,",");}
	if(strlen(n64)!=0){strcat(fields,"n64,");strcat(values,n64);strcat(values,",");}
	if(strlen(n66)!=0){strcat(fields,"n66,");strcat(values,"'");strcat(values,n66);strcat(values,"',");}
	if(strlen(n67)!=0){strcat(fields,"n67,");strcat(values,"'");strcat(values,n67);strcat(values,"',");}
	if(strlen(n68)!=0){strcat(fields,"n68,");strcat(values,"'");strcat(values,n68);strcat(values,"',");}
	if(strlen(n72)!=0){strcat(fields,"n72,");strcat(values,"'");strcat(values,n72);strcat(values,"',");}
	if(strlen(n76)!=0){strcat(fields,"n76,");strcat(values,"'");strcat(values,n76);strcat(values,"',");}
	if(strlen(n78)!=0){strcat(fields,"n78,");strcat(values,"'");strcat(values,n78);strcat(values,"',");}
	if(strlen(n80)!=0){strcat(fields,"n80,");strcat(values,"'");strcat(values,n80);strcat(values,"',");}
	if(strlen(n82)!=0){strcat(fields,"n82,");strcat(values,"'");strcat(values,n82);strcat(values,"',");}
	if(strlen(n83)!=0){strcat(fields,"n83,");strcat(values,"'");strcat(values,n83);strcat(values,"',");}
	if(strlen(n84)!=0){strcat(fields,"n84,");strcat(values,"'");strcat(values,n84);strcat(values,"',");}
	if(strlen(n85)!=0){strcat(fields,"n85,");strcat(values,"'");strcat(values,n85);strcat(values,"',");}
	if(strlen(n86)!=0){strcat(fields,"n86,");strcat(values,"'");strcat(values,n86);strcat(values,"',");}
	if(strlen(n87)!=0){strcat(fields,"n87,");strcat(values,"'");strcat(values,n87);strcat(values,"',");}
	if(strlen(n88)!=0){strcat(fields,"n88,");strcat(values,n88);strcat(values,",");}
	if(strlen(n89)!=0){strcat(fields,"n89,");strcat(values,n89);strcat(values,",");}
	if(strlen(n90)!=0){strcat(fields,"n90,");strcat(values,n90);strcat(values,",");}
	if(strlen(n91)!=0){strcat(fields,"n91,");strcat(values,n91);strcat(values,",");}
	if(strlen(n92)!=0){strcat(fields,"n92,");strcat(values,n92);strcat(values,",");}
	if(strlen(n93)!=0){strcat(fields,"n93,");strcat(values,n93);strcat(values,",");}
	if(strlen(n94)!=0){strcat(fields,"n94,");strcat(values,n94);strcat(values,",");}
	if(strlen(n108)!=0){strcat(fields,"n108,");strcat(values,"'");strcat(values,n108);strcat(values,"',");}
	if(strlen(n109)!=0){strcat(fields,"n109,");strcat(values,"'");strcat(values,n109);strcat(values,"',");}
	if(strlen(n111)!=0){strcat(fields,"n111");strcat(values,"'");strcat(values,n111);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void AddRecInTable(RECORD_TYPE04MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n2 = RejectAllSimbols((char*)pRec->n2_CauseForOutput);
	char *n3 = RejectAllSimbols((char*)pRec->n3_RecordNumber);
	char *n8 = RejectAllSimbols((char*)pRec->n8_OutputForSubscriber);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char *n16 = RejectAllSimbols((char*)pRec->n16_Acategory);
	char *n17 = RejectAllSimbols((char*)pRec->n17_AnumberType);
	char *n18 = RejectAllSimbols((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	char *n19 = RejectAllSimbols((char*)pRec->n19_AsubscrType);
	char *n20 = RejectAllSimbols((char*)pRec->n20_LengthIndicatorForBsubscr);
	char *n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	char *n23 = RejectAllSimbols((char*)pRec->n23_Bcategory);
	char *n24 = RejectAllSimbols((char*)pRec->n24_BsubscrNumberType);
	char *n25 = RejectAllSimbols((char*)pRec->n25_BsubscrNumberingPlanIndicator);
	char *n26 = RejectAllSimbols((char*)pRec->n26_LengthIndicatorForCallingPartyNumber);
	char *n27 = RejectAllSimbols((char*)pRec->n27_CallingPartyNumber);
	char *n28 = RejectAllSimbols((char*)pRec->n28_LengthIndicatorForRedirectingNumber);
	char *n29 = RejectAllSimbols((char*)pRec->n29_RedirectingNumber);
	char *n30 = RejectAllSimbols((char*)pRec->n30_LengthIndicatorForCalledPartyNumber);
	char *n31 = RejectAllSimbols((char*)pRec->n31_CalledPartyNumber);
	char *n32 = RejectAllSimbols((char*)pRec->n32_LengthIndicatorForOriginallyCalledNumber);
	char *n33 = RejectAllSimbols((char*)pRec->n33_OriginallyPartyNumber);
	char *n34 = RejectAllSimbols((char*)pRec->n34_FaultCode);
	char *n35 = RejectAllSimbols((char*)pRec->n35_CallStatus);

	char n36[2];
	n36[1]=0;
	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1){n36[0]='1';}else{n36[0] = '0';}

	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n44[12];n44[11]=0;strcpy(n44,(char*)pRec->n44_TimeRegisterSizureStartCharging);InSQLTimeFormat(n44);
	char n45[12];n45[11]=0;strcpy(n45,(char*)pRec->n45_ChargeableDuration);DurSec(n45);
	char n46[12];n46[11]=0;strcpy(n46,(char*)pRec->n46_InterruptionTime);InSQLTimeFormat(n46);

	char *n47 = RejectAllSimbols((char*)pRec->n47_ChargedParty);
	char n48[2];n48[1]=0;
	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1){n48[0] = '1';}else{n48[0] = '0';}
	 
	char *n49 = RejectAllSimbols((char*)pRec->n49_Price);
	char *n50 = RejectAllSimbols((char*)pRec->n50_PulseChargingIndicator);
	char *n51 = RejectAllSimbols((char*)pRec->n51_NumberOfMeterPulses);
	char *n52 = RejectAllSimbols((char*)pRec->n52_OriginForCharging);
	char *n53 = RejectAllSimbols((char*)pRec->n53_TariffClass);
	char *n54 = RejectAllSimbols((char*)pRec->n54_TariffSwitchingIndicator);
	char *n57 = RejectAllSimbols((char*)pRec->n57_CallAttemptIndicator);
	char *n61 = RejectAllSimbols((char*)pRec->n61_TypeOfCalledSubscriber);
	char *n62 = RejectAllSimbols((char*)pRec->n62_TypeOfSignalling);
	char *n63 = RejectAllSimbols((char*)pRec->n63_LengthIndicatorForAbbreviatedNumber);
	char *n64 = RejectAllSimbols((char*)pRec->n64_AbbreviatedNumber);
	char *n66 = RejectAllSimbols((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	char *n67 = RejectAllSimbols((char*)pRec->n67_TypeOfProcedure);
	char *n68 = RejectAllSimbols((char*)pRec->n68_SubscrServiceIndicator);
	
	char n72[2];n72[1]=0;	
	if (atoi((char*)pRec->n72_ConferenceCallIndicator) == 1){n72[0] = '1';}else{n72[0] = '0';}
	
	char *n76 = RejectAllSimbols((char*)pRec->n76_ExchngeIdentity);
	char *n78 = RejectAllSimbols((char*)pRec->n78_OutgouingRoute);
	char *n80 = RejectAllSimbols((char*)pRec->n80_IncomingRoute);

	char n82[2];n82[1]=0;	
	if (atoi((char*)pRec->n82_ReroutingIndicator) == 1){n82[0] = '1';}else{n82[0] = '0';}

	char *n83 = RejectAllSimbols((char*)pRec->n83_OriginatingCode);
	char *n84 = RejectAllSimbols((char*)pRec->n84_DestinationCode);
	char *n85 = RejectAllSimbols((char*)pRec->n85_TypeOfSizure);
	char *n86 = RejectAllSimbols((char*)pRec->n86_TypeOfIndicator);
	char *n87 = RejectAllSimbols((char*)pRec->n87_TelecommunicationServiceCode);
	char *n89 = RejectAllSimbols((char*)pRec->n89_NumberOfUserToUserMessagesDuringCall);
	char *n90 = RejectAllSimbols((char*)pRec->n90_NumberOfUserToUser);
	char *n91 = RejectAllSimbols((char*)pRec->n91_SubscrServiceForISDNSuplimentaryServices);
	char *n92 = RejectAllSimbols((char*)pRec->n92_EndToEndAccessDataMap);
	char *n93 = RejectAllSimbols((char*)pRec->n93_EndToEndAccessDataIndicator);
	char *n94 = RejectAllSimbols((char*)pRec->n94_EndToEndAccessDataCounter);
	char *n108 = RejectAllSimbols((char*)pRec->n108_ForcedDisconnectionInformation);
	char *n109 = RejectAllSimbols((char*)pRec->n109_CarrierAccessCode);

	char n111[2];n111[1]=0;
	if (atoi((char*)pRec->n111_PresentationIndicator) == 1){n111[0] = '1';}else{n111[0] = '0';}

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));

	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n2)!=0){strcat(fields,"n2,");strcat(values,n2);strcat(values,",");}
	if(strlen(n3)!=0){strcat(fields,"n3,");strcat(values,n3);strcat(values,",");}
	if(strlen(n8)!=0){strcat(fields,"n8,");strcat(values,n8);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n16)!=0){strcat(fields,"n16,");strcat(values,n16);strcat(values,",");}
	if(strlen(n17)!=0){strcat(fields,"n17,");strcat(values,n17);strcat(values,",");}
	if(strlen(n18)!=0){strcat(fields,"n18,");strcat(values,n18);strcat(values,",");}
	if(strlen(n19)!=0){strcat(fields,"n19,");strcat(values,n19);strcat(values,",");}
	if(strlen(n20)!=0){strcat(fields,"n20,");strcat(values,n20);strcat(values,",");}
	if(strlen(n21)!=0){strcat(fields,"n21,");strcat(values,"'");strcat(values,n21);strcat(values,"',");}
	if(strlen(n23)!=0){strcat(fields,"n23,");strcat(values,n23);strcat(values,",");}
	if(strlen(n24)!=0){strcat(fields,"n24,");strcat(values,n24);strcat(values,",");}
	if(strlen(n25)!=0){strcat(fields,"n25,");strcat(values,n25);strcat(values,",");}
	if(strlen(n26)!=0){strcat(fields,"n26,");strcat(values,n26);strcat(values,",");}
	if(strlen(n27)==0){n27="nomerNEopred";}
	if(strlen(n27)!=0){strcat(fields,"n27,");strcat(values,"'");strcat(values,n27);strcat(values,"',");}
	if(strlen(n28)!=0){strcat(fields,"n28,");strcat(values,n28);strcat(values,",");}
	if(strlen(n29)!=0){strcat(fields,"n29,");strcat(values,"'");strcat(values,n29);strcat(values,"',");}
	if(strlen(n30)!=0){strcat(fields,"n30,");strcat(values,n30);strcat(values,",");}
	if(strlen(n31)==0){n31="nomerNEopred";}
	if(strlen(n31)!=0){strcat(fields,"n31,");strcat(values,"'");strcat(values,n31);strcat(values,"',");}
	if(strlen(n32)!=0){strcat(fields,"n32,");strcat(values,n32);strcat(values,",");}
	if(strlen(n33)!=0){strcat(fields,"n33,");strcat(values,"'");strcat(values,n33);strcat(values,"',");}
	if(strlen(n34)!=0){strcat(fields,"n34,");strcat(values,n34);strcat(values,",");}
	if(strlen(n35)!=0){strcat(fields,"n35,");strcat(values,n35);strcat(values,",");}
	if(strlen(n36)!=0){strcat(fields,"n36,");strcat(values,n36);strcat(values,",");}
	if(strlen(n37)!=0){strcat(fields,"n37,");strcat(values,"'");strcat(values,n37);strcat(values,"',");}
	if(strlen(n40)!=0){strcat(fields,"n40,");strcat(values,"'");strcat(values,n40);strcat(values,"',");}
	if(strlen(n43)!=0){strcat(fields,"n43,");strcat(values,"'");strcat(values,n43);strcat(values,"',");}
	if(strlen(n44)!=0){strcat(fields,"n44,");strcat(values,"'");strcat(values,n44);strcat(values,"',");}
	if(strlen(n45)!=0){strcat(fields,"n45,");strcat(values,n45);strcat(values,",");}
	if(strlen(n46)!=0){strcat(fields,"n46,");strcat(values,"'");strcat(values,n46);strcat(values,"',");}
	if(strlen(n47)!=0){strcat(fields,"n47,");strcat(values,n47);strcat(values,",");}
	if(strlen(n48)!=0){strcat(fields,"n48,");strcat(values,n48);strcat(values,",");}
	if(strlen(n49)!=0){strcat(fields,"n49,");strcat(values,n49);strcat(values,",");}
	if(strlen(n50)!=0){strcat(fields,"n50,");strcat(values,n50);strcat(values,",");}
	if(strlen(n51)!=0){strcat(fields,"n51,");strcat(values,n51);strcat(values,",");}
	if(strlen(n52)!=0){strcat(fields,"n52,");strcat(values,n52);strcat(values,",");}
	if(strlen(n53)!=0){strcat(fields,"n53,");strcat(values,n53);strcat(values,",");}
	if(strlen(n54)!=0){strcat(fields,"n54,");strcat(values,n54);strcat(values,",");}
	if(strlen(n57)!=0){strcat(fields,"n57,");strcat(values,n57);strcat(values,",");}
	if(strlen(n61)!=0){strcat(fields,"n61,");strcat(values,n61);strcat(values,",");}
	if(strlen(n62)!=0){strcat(fields,"n62,");strcat(values,n62);strcat(values,",");}
	if(strlen(n63)!=0){strcat(fields,"n63,");strcat(values,n63);strcat(values,",");}
	if(strlen(n64)!=0){strcat(fields,"n64,");strcat(values,n64);strcat(values,",");}
	if(strlen(n66)!=0){strcat(fields,"n66,");strcat(values,"'");strcat(values,n66);strcat(values,"',");}
	if(strlen(n67)!=0){strcat(fields,"n67,");strcat(values,"'");strcat(values,n67);strcat(values,"',");}
	if(strlen(n68)!=0){strcat(fields,"n68,");strcat(values,"'");strcat(values,n68);strcat(values,"',");}
	if(strlen(n72)!=0){strcat(fields,"n72,");strcat(values,"'");strcat(values,n72);strcat(values,"',");}
	if(strlen(n76)!=0){strcat(fields,"n76,");strcat(values,"'");strcat(values,n76);strcat(values,"',");}
	if(strlen(n78)!=0){strcat(fields,"n78,");strcat(values,"'");strcat(values,n78);strcat(values,"',");}
	if(strlen(n80)!=0){strcat(fields,"n80,");strcat(values,"'");strcat(values,n80);strcat(values,"',");}
	if(strlen(n82)!=0){strcat(fields,"n82,");strcat(values,"'");strcat(values,n82);strcat(values,"',");}
	if(strlen(n83)!=0){strcat(fields,"n83,");strcat(values,"'");strcat(values,n83);strcat(values,"',");}
	if(strlen(n84)!=0){strcat(fields,"n84,");strcat(values,"'");strcat(values,n84);strcat(values,"',");}
	if(strlen(n85)!=0){strcat(fields,"n85,");strcat(values,"'");strcat(values,n85);strcat(values,"',");}
	if(strlen(n86)!=0){strcat(fields,"n86,");strcat(values,"'");strcat(values,n86);strcat(values,"',");}
	if(strlen(n87)!=0){strcat(fields,"n87,");strcat(values,"'");strcat(values,n87);strcat(values,"',");}
	if(strlen(n89)!=0){strcat(fields,"n89,");strcat(values,n89);strcat(values,",");}
	if(strlen(n90)!=0){strcat(fields,"n90,");strcat(values,n90);strcat(values,",");}
	if(strlen(n91)!=0){strcat(fields,"n91,");strcat(values,n91);strcat(values,",");}
	if(strlen(n92)!=0){strcat(fields,"n92,");strcat(values,n92);strcat(values,",");}
	if(strlen(n93)!=0){strcat(fields,"n93,");strcat(values,n93);strcat(values,",");}
	if(strlen(n94)!=0){strcat(fields,"n94,");strcat(values,n94);strcat(values,",");}
	if(strlen(n108)!=0){strcat(fields,"n108,");strcat(values,"'");strcat(values,n108);strcat(values,"',");}
	if(strlen(n109)!=0){strcat(fields,"n109,");strcat(values,"'");strcat(values,n109);strcat(values,"',");}
	if(strlen(n111)!=0){strcat(fields,"n111");strcat(values,"'");strcat(values,n111);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void AddRecInTable(RECORD_TYPE06MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n8 = RejectAllSimbols((char*)pRec->n8_OutputForSubscriber);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char *n16 = RejectAllSimbols((char*)pRec->n16_Acategory);
	char *n18 = RejectAllSimbols((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	char *n19 = RejectAllSimbols((char*)pRec->n19_AsubscrType);
	char *n20 = RejectAllSimbols((char*)pRec->n20_LengthIndicatorForBsubscr);
	char *n21 = RejectAllSimbols((char*)pRec->n21_Bnumber);
	char *n23 = RejectAllSimbols((char*)pRec->n23_Bcategory);
	char *n34 = RejectAllSimbols((char*)pRec->n34_FaultCode);
	char *n35 = RejectAllSimbols((char*)pRec->n35_CallStatus);

	char n36[2];
	n36[1]=0;
	if (atoi((char*)pRec->n36_AbnormalReleaseIndicator) == 1){n36[0]='1';}else{n36[0] = '0';}

	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);
	char n43[12];n43[11]=0;strcpy(n43,(char*)pRec->n43_TimeForStopOfCharging);InSQLTimeFormat(n43);
	char n44[12];n44[11]=0;strcpy(n44,(char*)pRec->n44_TimeRegisterSizureStartCharging);InSQLTimeFormat(n44);

	char *n47 = RejectAllSimbols((char*)pRec->n47_ChargedParty);
	char n48[2];n48[1]=0;
	if (atoi((char*)pRec->n48_ImmediateServiceIndicator) == 1){n48[0] = '1';}else{n48[0] = '0';}
	 
	char *n49 = RejectAllSimbols((char*)pRec->n49_Price);
	char *n50 = RejectAllSimbols((char*)pRec->n50_PulseChargingIndicator);
	char *n51 = RejectAllSimbols((char*)pRec->n51_NumberOfMeterPulses);
	char *n52 = RejectAllSimbols((char*)pRec->n52_OriginForCharging);
	char *n53 = RejectAllSimbols((char*)pRec->n53_TariffClass);
	char *n66 = RejectAllSimbols((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	char *n67 = RejectAllSimbols((char*)pRec->n67_TypeOfProcedure);
	char *n68 = RejectAllSimbols((char*)pRec->n68_SubscrServiceIndicator);
	char *n76 = RejectAllSimbols((char*)pRec->n76_ExchngeIdentity);
	char *n85 = RejectAllSimbols((char*)pRec->n85_TypeOfSizure);
	char *n86 = RejectAllSimbols((char*)pRec->n86_TypeOfIndicator);
	char *n87 = RejectAllSimbols((char*)pRec->n87_TelecommunicationServiceCode);
	char *n108 = RejectAllSimbols((char*)pRec->n108_ForcedDisconnectionInformation);

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));

	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n8)!=0){strcat(fields,"n8,");strcat(values,n8);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n16)!=0){strcat(fields,"n16,");strcat(values,n16);strcat(values,",");}
	if(strlen(n18)!=0){strcat(fields,"n18,");strcat(values,n18);strcat(values,",");}
	if(strlen(n19)!=0){strcat(fields,"n19,");strcat(values,n19);strcat(values,",");}
	if(strlen(n20)!=0){strcat(fields,"n20,");strcat(values,n20);strcat(values,",");}
	if(strlen(n21)!=0){strcat(fields,"n21,");strcat(values,"'");strcat(values,n21);strcat(values,"',");}
	if(strlen(n23)!=0){strcat(fields,"n23,");strcat(values,n23);strcat(values,",");}
	if(strlen(n34)!=0){strcat(fields,"n34,");strcat(values,n34);strcat(values,",");}
	if(strlen(n35)!=0){strcat(fields,"n35,");strcat(values,n35);strcat(values,",");}
	if(strlen(n36)!=0){strcat(fields,"n36,");strcat(values,n36);strcat(values,",");}
	if(strlen(n37)!=0){strcat(fields,"n37,");strcat(values,"'");strcat(values,n37);strcat(values,"',");}
	if(strlen(n40)!=0){strcat(fields,"n40,");strcat(values,"'");strcat(values,n40);strcat(values,"',");}
	if(strlen(n43)!=0){strcat(fields,"n43,");strcat(values,"'");strcat(values,n43);strcat(values,"',");}
	if(strlen(n44)!=0){strcat(fields,"n44,");strcat(values,"'");strcat(values,n44);strcat(values,"',");}
	if(strlen(n47)!=0){strcat(fields,"n47,");strcat(values,n47);strcat(values,",");}
	if(strlen(n48)!=0){strcat(fields,"n48,");strcat(values,n48);strcat(values,",");}
	if(strlen(n49)!=0){strcat(fields,"n49,");strcat(values,n49);strcat(values,",");}
	if(strlen(n50)!=0){strcat(fields,"n50,");strcat(values,n50);strcat(values,",");}
	if(strlen(n51)!=0){strcat(fields,"n51,");strcat(values,n51);strcat(values,",");}
	if(strlen(n52)!=0){strcat(fields,"n52,");strcat(values,n52);strcat(values,",");}
	if(strlen(n53)!=0){strcat(fields,"n53,");strcat(values,n53);strcat(values,",");}
	if(strlen(n66)!=0){strcat(fields,"n66,");strcat(values,"'");strcat(values,n66);strcat(values,"',");}
	if(strlen(n67)!=0){strcat(fields,"n67,");strcat(values,"'");strcat(values,n67);strcat(values,"',");}
	if(strlen(n68)!=0){strcat(fields,"n68,");strcat(values,"'");strcat(values,n68);strcat(values,"',");}
	if(strlen(n76)!=0){strcat(fields,"n76,");strcat(values,"'");strcat(values,n76);strcat(values,"',");}
	if(strlen(n85)!=0){strcat(fields,"n85,");strcat(values,"'");strcat(values,n85);strcat(values,"',");}
	if(strlen(n86)!=0){strcat(fields,"n86,");strcat(values,"'");strcat(values,n86);strcat(values,"',");}
	if(strlen(n87)!=0){strcat(fields,"n87,");strcat(values,"'");strcat(values,n87);strcat(values,"',");}
	if(strlen(n108)!=0){strcat(fields,"n108");strcat(values,"'");strcat(values,n108);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void AddRecInTable(RECORD_TYPE07MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n8 = RejectAllSimbols((char*)pRec->n8_OutputForSubscriber);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char *n16 = RejectAllSimbols((char*)pRec->n16_Acategory);
	char *n18 = RejectAllSimbols((char*)pRec->n18_AsubscrNumberingPlanIndicator);
	
	char n37[12];n37[11]=0;strcpy(n37,(char*)pRec->n37_DateForStartOfChargingUSA);InSQLDataFormat(n37);
	char n40[12];n40[11]=0;strcpy(n40,(char*)pRec->n40_TimeForStartOfCharging24hour);InSQLTimeFormat(n40);

	char *n47 = RejectAllSimbols((char*)pRec->n47_ChargedParty);
	char *n49 = RejectAllSimbols((char*)pRec->n49_Price);
	char *n50 = RejectAllSimbols((char*)pRec->n50_PulseChargingIndicator);
	char *n51 = RejectAllSimbols((char*)pRec->n51_NumberOfMeterPulses);
	char *n52 = RejectAllSimbols((char*)pRec->n52_OriginForCharging);
	char *n53 = RejectAllSimbols((char*)pRec->n53_TariffClass);
	char *n66 = RejectAllSimbols((char*)pRec->n66_ResultOfSubscriberServiceProcedure);
	char *n67 = RejectAllSimbols((char*)pRec->n67_TypeOfProcedure);
	char *n76 = RejectAllSimbols((char*)pRec->n76_ExchngeIdentity);
	char *n85 = RejectAllSimbols((char*)pRec->n85_TypeOfSizure);
	char *n86 = RejectAllSimbols((char*)pRec->n86_TypeOfIndicator);
	char *n87 = RejectAllSimbols((char*)pRec->n87_TelecommunicationServiceCode);

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));

	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n8)!=0){strcat(fields,"n8,");strcat(values,n8);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n16)!=0){strcat(fields,"n16,");strcat(values,n16);strcat(values,",");}
	if(strlen(n18)!=0){strcat(fields,"n18,");strcat(values,n18);strcat(values,",");}
	if(strlen(n37)!=0){strcat(fields,"n37,");strcat(values,"'");strcat(values,n37);strcat(values,"',");}
	if(strlen(n40)!=0){strcat(fields,"n40,");strcat(values,"'");strcat(values,n40);strcat(values,"',");}
	if(strlen(n47)!=0){strcat(fields,"n47,");strcat(values,n47);strcat(values,",");}
	if(strlen(n49)!=0){strcat(fields,"n49,");strcat(values,n49);strcat(values,",");}
	if(strlen(n50)!=0){strcat(fields,"n50,");strcat(values,n50);strcat(values,",");}
	if(strlen(n51)!=0){strcat(fields,"n51,");strcat(values,n51);strcat(values,",");}
	if(strlen(n52)!=0){strcat(fields,"n52,");strcat(values,n52);strcat(values,",");}
	if(strlen(n53)!=0){strcat(fields,"n53,");strcat(values,n53);strcat(values,",");}
	if(strlen(n66)!=0){strcat(fields,"n66,");strcat(values,"'");strcat(values,n66);strcat(values,"',");}
	if(strlen(n67)!=0){strcat(fields,"n67,");strcat(values,"'");strcat(values,n67);strcat(values,"',");}
	if(strlen(n76)!=0){strcat(fields,"n76,");strcat(values,"'");strcat(values,n76);strcat(values,"',");}
	if(strlen(n85)!=0){strcat(fields,"n85,");strcat(values,"'");strcat(values,n85);strcat(values,"',");}
	if(strlen(n86)!=0){strcat(fields,"n86,");strcat(values,"'");strcat(values,n86);strcat(values,"',");}
	if(strlen(n87)!=0){strcat(fields,"n87");strcat(values,"'");strcat(values,n87);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void AddRecInTable(RECORD_TYPE08MY *pRec)
{
	char *n1 = RejectAllSimbols((char*)pRec->n1_RecType);
	char *n13 = RejectAllSimbols((char*)pRec->n13_LengthIndicatorForAnumber);
	char *n14 = RejectAllSimbols((char*)pRec->n14_Anumber);
	char n112[12];n112[11]=0;strcpy(n112,(char*)pRec->n112_DateOfExecutionOfCommand);InSQLDataFormat(n112);  
	char n113[12];n113[11]=0;strcpy(n113,(char*)pRec->n113_TimeOfExecutionOfComand);InSQLDataFormat(n113);
	char *n114 = RejectAllSimbols((char*)pRec->n114_CommandName);

	char fields[2048];memset((void*)fields,0,sizeof(fields));
	char values[2048];memset((void*)values,0,sizeof(values));

	if(strlen(n1)!=0){strcat(fields,"n1,");strcat(values,n1);strcat(values,",");}
	if(strlen(n13)!=0){strcat(fields,"n13,");strcat(values,n13);strcat(values,",");}
	if(strlen(n14)==0){n14="nomerNEopred";}
	if(strlen(n14)!=0){strcat(fields,"n14,");strcat(values,"'");strcat(values,n14);strcat(values,"',");}
	if(strlen(n112)!=0){strcat(fields,"n112,");strcat(values,"'");strcat(values,n112);strcat(values,"',");}
	if(strlen(n113)!=0){strcat(fields,"n113,");strcat(values,"'");strcat(values,n113);strcat(values,"',");}
	if(strlen(n114)!=0){strcat(fields,"n114");strcat(values,"'");strcat(values,n114);strcat(values,"'");}

	if(fields[0]==',')fields[0]=' ';
	if(values[0]==',')values[0]=' ';
	char sql[8192];memset((void*)sql,0,sizeof(sql));
	strcpy(sql,"INSERT INTO axe (");
	strcat(sql,fields);
	strcat(sql,") VALUES (");
	strcat(sql,values);
	strcat(sql,");");
	InsertRec(sql);
}

void GetRecordsFromBuf(char * buffer)
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

void GetFirstRecordFromBuf(char * buffer,char * ymdhmsf)
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
			strcpy(ymdhmsf,(char*)RecType00My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsf,(char*)RecType00My.n40_TimeForStartOfCharging24hour);
			return;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '2'))
		{
			RECORD_TYPE02 * pRecType02 = (RECORD_TYPE02*)pBuffer;
			RECORD_TYPE02MY RecType02My;
			FillRecordTypeMy(pRecType02, &RecType02My);
			strcpy(ymdhmsf,(char*)RecType02My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsf,(char*)RecType02My.n40_TimeForStartOfCharging24hour);
			return;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '4'))
		{
			RECORD_TYPE04 * pRecType04 = (RECORD_TYPE04*)pBuffer;
			RECORD_TYPE04MY RecType04My;
			FillRecordTypeMy(pRecType04, &RecType04My);
			strcpy(ymdhmsf,(char*)RecType04My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsf,(char*)RecType04My.n40_TimeForStartOfCharging24hour);
			return;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '6'))
		{
			RECORD_TYPE06 * pRecType06 = (RECORD_TYPE06*)pBuffer;
			RECORD_TYPE06MY RecType06My;
			FillRecordTypeMy(pRecType06, &RecType06My);
			strcpy(ymdhmsf,(char*)RecType06My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsf,(char*)RecType06My.n40_TimeForStartOfCharging24hour);
			return;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '7'))
		{
			RECORD_TYPE07 * pRecType07 = (RECORD_TYPE07*)pBuffer;
			RECORD_TYPE07MY RecType07My;
			FillRecordTypeMy(pRecType07, &RecType07My);
			strcpy(ymdhmsf,(char*)RecType07My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsf,(char*)RecType07My.n40_TimeForStartOfCharging24hour);
			return;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '8'))
		{
			RECORD_TYPE08 * pRecType08 = (RECORD_TYPE08*)pBuffer;
			RECORD_TYPE08MY RecType08My;
			FillRecordTypeMy(pRecType08, &RecType08My);
			strcpy(ymdhmsf,(char*)RecType08My.n112_DateOfExecutionOfCommand);
			strcat(ymdhmsf,(char*)RecType08My.n113_TimeOfExecutionOfComand);
			return;
		}
		strcpy(ymdhmsf,"hhmmddHHMMSS");
		return;
	}
}

void GetLastRecordFromBuf(char * buffer,char * ymdhmsl)
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
			strcpy(ymdhmsl,(char*)RecType00My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsl,(char*)RecType00My.n40_TimeForStartOfCharging24hour);
			pBuffer = pBuffer + sizeof(RECORD_TYPE00);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '2'))
		{
			RECORD_TYPE02 * pRecType02 = (RECORD_TYPE02*)pBuffer;
			RECORD_TYPE02MY RecType02My;
			FillRecordTypeMy(pRecType02, &RecType02My);
			strcpy(ymdhmsl,(char*)RecType02My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsl,(char*)RecType02My.n40_TimeForStartOfCharging24hour);
			pBuffer = pBuffer + sizeof(RECORD_TYPE02);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '4'))
		{
			RECORD_TYPE04 * pRecType04 = (RECORD_TYPE04*)pBuffer;
			RECORD_TYPE04MY RecType04My;
			FillRecordTypeMy(pRecType04, &RecType04My);
			strcpy(ymdhmsl,(char*)RecType04My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsl,(char*)RecType04My.n40_TimeForStartOfCharging24hour);
			pBuffer = pBuffer + sizeof(RECORD_TYPE04);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '6'))
		{
			RECORD_TYPE06 * pRecType06 = (RECORD_TYPE06*)pBuffer;
			RECORD_TYPE06MY RecType06My;
			FillRecordTypeMy(pRecType06, &RecType06My);
			strcpy(ymdhmsl,(char*)RecType06My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsl,(char*)RecType06My.n40_TimeForStartOfCharging24hour);
			pBuffer = pBuffer + sizeof(RECORD_TYPE06);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '7'))
		{
			RECORD_TYPE07 * pRecType07 = (RECORD_TYPE07*)pBuffer;
			RECORD_TYPE07MY RecType07My;
			FillRecordTypeMy(pRecType07, &RecType07My);
			strcpy(ymdhmsl,(char*)RecType07My.n37_DateForStartOfChargingUSA);
			strcat(ymdhmsl,(char*)RecType07My.n40_TimeForStartOfCharging24hour);
			pBuffer = pBuffer + sizeof(RECORD_TYPE07);
			continue;
		}
		if ((*pBuffer == '0') && (*(pBuffer + 1) == '8'))
		{
			RECORD_TYPE08 * pRecType08 = (RECORD_TYPE08*)pBuffer;
			RECORD_TYPE08MY RecType08My;
			FillRecordTypeMy(pRecType08, &RecType08My);
			strcpy(ymdhmsl,(char*)RecType08My.n112_DateOfExecutionOfCommand);
			strcat(ymdhmsl,(char*)RecType08My.n113_TimeOfExecutionOfComand);
			pBuffer = pBuffer + sizeof(RECORD_TYPE08);
			continue;
		}
		if (*pBuffer == 0)
		{
			pBuffer++;
		}
	}
}

int GetFilePeriod(FILE * f,char * period,char * filename)
{
	char buffer[2048];
	char ymdhmsf[32];ymdhmsf[31]=0;
	char ymdhmsl[32];ymdhmsl[31]=0;
	fread((void*)buffer, sizeof(BYTE), 2048, f);
	GetFirstRecordFromBuf(buffer,ymdhmsf);
	int rs = fseek(f,-2048,SEEK_END);
	if (rs!=0)printf("fseek error=%d\n",rs);
	fread((void*)buffer, sizeof(BYTE), 2048, f);
	GetLastRecordFromBuf(buffer,ymdhmsl);
	strcat(filename,"-");strcat(filename,ymdhmsf);strcat(filename,"-");strcat(filename,ymdhmsl);
	//printf("filename: %s\n",filename);
	char dt1[16];dt1[15]=0;strncpy(dt1,ymdhmsf,6);InSQLDataFormat(dt1);
	char tm1[16];tm1[15]=0;strncpy(tm1,ymdhmsf+6,6);InSQLTimeFormat(tm1);
	char dt2[16];dt2[15]=0;strncpy(dt2,ymdhmsl,6);InSQLDataFormat(dt2);
	char tm2[16];tm2[15]=0;strncpy(tm2,ymdhmsl+6,6);InSQLTimeFormat(tm2);
	char buf[64];buf[63]=0;
	strcpy(buf,dt1);
	strcat(buf," ");
	strcat(buf,tm1);
	strcat(buf,"$");
	strcat(buf,dt2);
	strcat(buf," ");
	strcat(buf,tm2);
	strcat(buf,"$");
	strcpy(period,buf);
	//printf("period: %s\n",period);

	char sql[128];sql[127]=0;
	strcpy(sql,"SELECT * FROM ttflog WHERE firstrec='");
	strncat(sql,buf,19);
	strcat(sql,"' AND lastrec='");
	strncat(sql,buf+20,19);
	strcat(sql,"';");
	//printf("SQL=%s\n",sql);
 	res = PQexec(conn, sql);
	if (PQresultStatus(res) != PGRES_TUPLES_OK){
		printf("res: %s\n", PQerrorMessage(conn),sql);
	}else{
		if(PQntuples(res)!=0){
			PQclear(res);
			rewind(f);
			return 1;
		}
	}
  	PQclear(res);

	rewind(f);
	return 0;
}

void RenameFile(char * fnameold, char * fnamenew)
{
	char cmd[512];cmd[0]=0;
	strcpy(cmd,"/bin/mv ");
	strcat(cmd,fnameold);
	strcat(cmd," ");
	strcat(cmd,fnamenew);
	if (system(cmd)==-1)printf("[%s] ERROR :%s\n",gettime(),cmd);
}

int main(int argc, char **argv)
{
 char coninfo[256];
 if (argc>1) {
  //printf("REJECT : \'%s\'\n",RejectAllSimbols(argv[1]));
  strcpy(coninfo,argv[1]);
  conn = PQconnectdb(coninfo);
  if (PQstatus(conn) != CONNECTION_OK)
  {
   printf("Connection to database failed: %s",PQerrorMessage(conn));
   exit_nicely(conn);
  }else{
   printf("[%s] Connection to database open.\n",gettime());
  }
 }else{
  printf("Please enter database connect parameters\n");
  printf("hostaddr=127.0.0.1 port=5432 dbname=tariff user=postgres password=postgres\n");
  exit(1);
 }
 
 int count=0;
 char buf[256]; 
 buf[255]=0;
 while (!feof(stdin))
 {
  fgets(buf,255,stdin);
  if ((strlen(buf) != NULL) && (strstr(buf,"TT")!=NULL)) 
  {
   if(strstr(buf,"-")!=NULL) continue;
   buf[strlen(buf)-1]=0;
//   fprintf(stdout,"%d : %s\n",strlen(buf),buf);
   FILE * f;
   if ((f = fopen(buf, "rb"))==NULL)
   {
    printf("Error open file: \"%s\"\n",buf);
   }
   else
    printf("[%s] File: \"%s\" open sucsessfule\n",gettime(),buf);
   char period[64];period[63]=0;
   char NewFname[320];NewFname[0]=0;strcpy(NewFname,buf);
   int resultGFP=GetFilePeriod(f,period,NewFname);
   if (resultGFP==0){
	char buffer[2048];
	//printf("begin job with file %s\n",buf);
	while (!feof(f)){
	 int col = fread((void*)(buffer), sizeof(BYTE), 2048, f);
	 if (col<2048) break;
	 GetRecordsFromBuf(buffer);
	 count++;
	 printf("records number = %d\n",count);
	} 
	//printf("end job with file %s\n",buf);
	char sqlcmd[128];sqlcmd[127]=0;
	strcpy(sqlcmd,"INSERT INTO ttflog VALUES ('");
	strcat(sqlcmd,buf);
	strcat(sqlcmd,"','");
	strncat(sqlcmd,period,19);		
	strcat(sqlcmd,"','");
	strncat(sqlcmd,period+20,19);
	strcat(sqlcmd,"');");
	printf("sqlcmd=%s\n",sqlcmd);
 	res = PQexec(conn, sqlcmd);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		printf("res: %s\n", PQerrorMessage(conn));
	}
  	PQclear(res);
   }else{
	printf("[%s] The file: %s has been alredy is in base\n",gettime(),buf);
   } 
   fclose(f);
   if (resultGFP==0)RenameFile(buf,NewFname);
  }
  buf[0]=0;
 }

 PQfinish(conn);
 printf("[%s] Records in TT files: %d\n",gettime(),count);
 printf("[%s] Connection to database close\n",gettime()); 

 return 0;
}
