//header file for axecdr.cpp

//**************************************************************************************

typedef struct _TTFILE_AXE10_FORMAT_TYPEALL {
    unsigned char n1_RecType[2];
    unsigned char n2_CauseForOutput;
    unsigned char n3_RecordNumber[2];
    unsigned char n4_CallIdenificationNumber[8];
    unsigned char n6_RecordSequenceNumber[8];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10];
    unsigned char n16_Acategory[2];
    unsigned char n17_AnumberType[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n24_BsubscrNumberType[3];
    unsigned char n25_BsubscrNumberingPlanIndicator[2];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[2];
    unsigned char n27_CallingPartyNumber[20];
    unsigned char n28_LengthIndicatorForRedirectingNumber[2];
    unsigned char n29_RedirectingNumber[20];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[2];
    unsigned char n31_CalledPartyNumber[18];
    unsigned char n32_LengthIndicatorForOriginallyCalledNumber[2];
    unsigned char n33_OriginallyPartyNumber[20];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n45_ChargeableDuration[6];
    unsigned char n46_InterruptionTime[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n54_TariffSwitchingIndicator;
    unsigned char n57_CallAttemptIndicator;
    unsigned char n58_CallAttemptState[2];
    unsigned char n59_CauseCode[3];
    unsigned char n60_LocationCode[2];
    unsigned char n61_TypeOfCalledSubscriber;
    unsigned char n62_TypeOfSignalling;
    unsigned char n63_LengthIndicatorForAbbreviatedNumber;
    unsigned char n64_AbbreviatedNumber[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n72_ConferenceCallIndicator;
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n78_OutgouingRoute[7];
    unsigned char n80_IncomingRoute[7];
    unsigned char n82_ReroutingIndicator;
    unsigned char n83_OriginatingCode;
    unsigned char n84_DestinationCode;
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n88_NetvorkConversionType[2];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[4];
    unsigned char n90_NumberOfUserToUser;
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[16];
    unsigned char n92_EndToEndAccessDataMap[8];
    unsigned char n93_EndToEndAccessDataIndicator;
    unsigned char n94_EndToEndAccessDataCounter[3];
    unsigned char n108_ForcedDisconnectionInformation;
    unsigned char n109_CarrierAccessCode[6];
    unsigned char n111_PresentationIndicator;
    unsigned char n112_DateOfExecutionOfCommand[6];
    unsigned char n113_TimeOfExecutionOfComand[6];
    unsigned char n114_CommandName[5];
} TTFILE_AXE10_FORMAT_TYPEALL;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n2_CauseForOutput;
    unsigned char n3_RecordNumber[2];
    unsigned char n4_CallIdenificationNumber[8];
    unsigned char n6_RecordSequenceNumber[8];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n16_Acategory[2];
    unsigned char n17_AnumberType[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n24_BsubscrNumberType[3];
    unsigned char n25_BsubscrNumberingPlanIndicator[2];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[2];
    unsigned char n27_CallingPartyNumber[20];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[2];
    unsigned char n31_CalledPartyNumber[18];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n45_ChargeableDuration[6];
    unsigned char n46_InterruptionTime[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n54_TariffSwitchingIndicator;
    unsigned char n57_CallAttemptIndicator;
    unsigned char n61_TypeOfCalledSubscriber;
    unsigned char n62_TypeOfSignalling;
    unsigned char n63_LengthIndicatorForAbbreviatedNumber;
    unsigned char n64_AbbreviatedNumber[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n72_ConferenceCallIndicator;
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n78_OutgouingRoute[7];
    unsigned char n80_IncomingRoute[7];
    unsigned char n82_ReroutingIndicator;
    unsigned char n83_OriginatingCode;
    unsigned char n84_DestinationCode;
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n108_ForcedDisconnectionInformation;
    unsigned char n109_CarrierAccessCode[6];
    unsigned char n111_PresentationIndicator;
} RECORD_TYPE00;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n2_CauseForOutput;
    unsigned char n3_RecordNumber[2];
    unsigned char n4_CallIdenificationNumber[8];
    unsigned char n6_RecordSequenceNumber[8];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n16_Acategory[2];
    unsigned char n17_AnumberType[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n24_BsubscrNumberType[3];
    unsigned char n25_BsubscrNumberingPlanIndicator[2];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[2];
    unsigned char n27_CallingPartyNumber[20];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[2];
    unsigned char n31_CalledPartyNumber[18];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n45_ChargeableDuration[6];
    unsigned char n46_InterruptionTime[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n54_TariffSwitchingIndicator;
    unsigned char n57_CallAttemptIndicator;
    unsigned char n58_CallAttemptState[2];
    unsigned char n59_CauseCode[3];
    unsigned char n60_LocationCode[2];
    unsigned char n61_TypeOfCalledSubscriber;
    unsigned char n62_TypeOfSignalling;
    unsigned char n63_LengthIndicatorForAbbreviatedNumber;
    unsigned char n64_AbbreviatedNumber[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n72_ConferenceCallIndicator;
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n78_OutgouingRoute[7];
    unsigned char n80_IncomingRoute[7];
    unsigned char n82_ReroutingIndicator;
    unsigned char n83_OriginatingCode;
    unsigned char n84_DestinationCode;
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n88_NetvorkConversionType[2];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[4];
    unsigned char n90_NumberOfUserToUser;
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[16];
    unsigned char n92_EndToEndAccessDataMap[8];
    unsigned char n93_EndToEndAccessDataIndicator;
    unsigned char n94_EndToEndAccessDataCounter[3];
    unsigned char n108_ForcedDisconnectionInformation;
    unsigned char n109_CarrierAccessCode[6];
    unsigned char n111_PresentationIndicator;
} RECORD_TYPE02;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n2_CauseForOutput;
    unsigned char n3_RecordNumber[2];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n16_Acategory[2];
    unsigned char n17_AnumberType[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n24_BsubscrNumberType[3];
    unsigned char n25_BsubscrNumberingPlanIndicator[2];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[2];
    unsigned char n27_CallingPartyNumber[20];
    unsigned char n28_LengthIndicatorForRedirectingNumber[2];
    unsigned char n29_RedirectingNumber[20];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[2];
    unsigned char n31_CalledPartyNumber[18];
    unsigned char n32_LengthIndicatorForOriginallyCalledNumber[2];
    unsigned char n33_OriginallyPartyNumber[20];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n45_ChargeableDuration[6];
    unsigned char n46_InterruptionTime[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n54_TariffSwitchingIndicator;
    unsigned char n57_CallAttemptIndicator;
    unsigned char n61_TypeOfCalledSubscriber;
    unsigned char n62_TypeOfSignalling;
    unsigned char n63_LengthIndicatorForAbbreviatedNumber;
    unsigned char n64_AbbreviatedNumber[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n72_ConferenceCallIndicator;
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n78_OutgouingRoute[7];
    unsigned char n80_IncomingRoute[7];
    unsigned char n82_ReroutingIndicator;
    unsigned char n83_OriginatingCode;
    unsigned char n84_DestinationCode;
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[4];
    unsigned char n90_NumberOfUserToUser;
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[16];
    unsigned char n92_EndToEndAccessDataMap[8];
    unsigned char n93_EndToEndAccessDataIndicator;
    unsigned char n94_EndToEndAccessDataCounter[3];
    unsigned char n108_ForcedDisconnectionInformation;
    unsigned char n109_CarrierAccessCode[6];
    unsigned char n111_PresentationIndicator;
} RECORD_TYPE04;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n16_Acategory[2];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n108_ForcedDisconnectionInformation;
} RECORD_TYPE06;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n16_Acategory[2];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n47_ChargedParty;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
} RECORD_TYPE07;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10]; //??
    unsigned char n112_DateOfExecutionOfCommand[6];
    unsigned char n113_TimeOfExecutionOfComand[6];
    unsigned char n114_CommandName[5];
} RECORD_TYPE08;

typedef struct {
    unsigned char n1_RecType[2];
    unsigned char n2_CauseForOutput;
    unsigned char n3_RecordNumber[2];
    unsigned char n4_CallIdenificationNumber[8];
    unsigned char n6_RecordSequenceNumber[8];
    unsigned char n8_OutputForSubscriber[1];
    unsigned char n13_LengthIndicatorForAnumber[2];
    unsigned char n14_Anumber[10];
    unsigned char n16_Acategory[2];
    unsigned char n17_AnumberType[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[2];
    unsigned char n19_AsubscrType[2];
    unsigned char n20_LengthIndicatorForBsubscr[2];
    unsigned char n21_Bnumber[18];
    unsigned char n23_Bcategory[2];
    unsigned char n24_BsubscrNumberType[3];
    unsigned char n25_BsubscrNumberingPlanIndicator[2];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[2];
    unsigned char n27_CallingPartyNumber[20];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[2];
    unsigned char n31_CalledPartyNumber[18];
    unsigned char n34_FaultCode[5];
    unsigned char n35_CallStatus;
    unsigned char n36_AbnormalReleaseIndicator;
    unsigned char n37_DateForStartOfChargingUSA[6];
    unsigned char n40_TimeForStartOfCharging24hour[6];
    unsigned char n43_TimeForStopOfCharging[6];
    unsigned char n44_TimeRegisterSizureStartCharging[6];
    unsigned char n45_ChargeableDuration[6];
    unsigned char n46_InterruptionTime[6];
    unsigned char n47_ChargedParty;
    unsigned char n48_ImmediateServiceIndicator;
    unsigned char n49_Price[8];
    unsigned char n50_PulseChargingIndicator;
    unsigned char n51_NumberOfMeterPulses[6];
    unsigned char n52_OriginForCharging[4];
    unsigned char n53_TariffClass[3];
    unsigned char n54_TariffSwitchingIndicator;
    unsigned char n57_CallAttemptIndicator;
    unsigned char n58_CallAttemptState[2];
    unsigned char n59_CauseCode[3];
    unsigned char n60_LocationCode[2];
    unsigned char n61_TypeOfCalledSubscriber;
    unsigned char n62_TypeOfSignalling;
    unsigned char n63_LengthIndicatorForAbbreviatedNumber;
    unsigned char n64_AbbreviatedNumber[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure;
    unsigned char n67_TypeOfProcedure[2];
    unsigned char n68_SubscrServiceIndicator[2];
    unsigned char n72_ConferenceCallIndicator;
    unsigned char n76_ExchngeIdentity[15];
    unsigned char n78_OutgouingRoute[7];
    unsigned char n80_IncomingRoute[7];
    unsigned char n82_ReroutingIndicator;
    unsigned char n83_OriginatingCode;
    unsigned char n84_DestinationCode;
    unsigned char n85_TypeOfSizure[2];
    unsigned char n86_TypeOfIndicator[2];
    unsigned char n87_TelecommunicationServiceCode[3];
    unsigned char n88_NetvorkConversionType[2];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[4];
    unsigned char n90_NumberOfUserToUser;
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[16];
    unsigned char n92_EndToEndAccessDataMap[8];
    unsigned char n93_EndToEndAccessDataIndicator;
    unsigned char n94_EndToEndAccessDataCounter[3];
    unsigned char n108_ForcedDisconnectionInformation;
    unsigned char n109_CarrierAccessCode[6];
    unsigned char n111_PresentationIndicator;
} RECORD_TYPE09;

//******************************************************************************

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n2_CauseForOutput[2];
    unsigned char n3_RecordNumber[3];
    unsigned char n4_CallIdenificationNumber[9];
    unsigned char n6_RecordSequenceNumber[9];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n16_Acategory[3];
    unsigned char n17_AnumberType[4];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n19_AsubscrType[3];
    unsigned char n20_LengthIndicatorForBsubscr[3];
    unsigned char n21_Bnumber[19];
    unsigned char n23_Bcategory[3];
    unsigned char n24_BsubscrNumberType[4];
    unsigned char n25_BsubscrNumberingPlanIndicator[3];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[3];
    unsigned char n27_CallingPartyNumber[21];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[3];
    unsigned char n31_CalledPartyNumber[19];
    unsigned char n34_FaultCode[6];
    unsigned char n35_CallStatus[2];
    unsigned char n36_AbnormalReleaseIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n43_TimeForStopOfCharging[7];
    unsigned char n44_TimeRegisterSizureStartCharging[7];
    unsigned char n45_ChargeableDuration[7];
    unsigned char n46_InterruptionTime[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n48_ImmediateServiceIndicator[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n54_TariffSwitchingIndicator[2];
    unsigned char n57_CallAttemptIndicator[2];
    unsigned char n61_TypeOfCalledSubscriber[2];
    unsigned char n62_TypeOfSignalling[2];
    unsigned char n63_LengthIndicatorForAbbreviatedNumber[2];
    unsigned char n64_AbbreviatedNumber[5];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n68_SubscrServiceIndicator[3];
    unsigned char n72_ConferenceCallIndicator[2];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n78_OutgouingRoute[8];
    unsigned char n80_IncomingRoute[8];
    unsigned char n82_ReroutingIndicator[2];
    unsigned char n83_OriginatingCode[2];
    unsigned char n84_DestinationCode[2];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
    unsigned char n108_ForcedDisconnectionInformation[2];
    unsigned char n109_CarrierAccessCode[7];
    unsigned char n111_PresentationIndicator[2];
} RECORD_TYPE00MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n2_CauseForOutput[2];
    unsigned char n3_RecordNumber[3];
    unsigned char n4_CallIdenificationNumber[9];
    unsigned char n6_RecordSequenceNumber[9];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n16_Acategory[3];
    unsigned char n17_AnumberType[4];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n19_AsubscrType[3];
    unsigned char n20_LengthIndicatorForBsubscr[3];
    unsigned char n21_Bnumber[19];
    unsigned char n23_Bcategory[3];
    unsigned char n24_BsubscrNumberType[4];
    unsigned char n25_BsubscrNumberingPlanIndicator[3];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[3];
    unsigned char n27_CallingPartyNumber[21];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[3];
    unsigned char n31_CalledPartyNumber[19];
    unsigned char n34_FaultCode[6];
    unsigned char n35_CallStatus[2];
    unsigned char n36_AbnormalReleaseIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n43_TimeForStopOfCharging[7];
    unsigned char n44_TimeRegisterSizureStartCharging[7];
    unsigned char n45_ChargeableDuration[7];
    unsigned char n46_InterruptionTime[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n48_ImmediateServiceIndicator[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n54_TariffSwitchingIndicator[2];
    unsigned char n57_CallAttemptIndicator[2];
    unsigned char n58_CallAttemptState[3];
    unsigned char n59_CauseCode[4];
    unsigned char n60_LocationCode[3];
    unsigned char n61_TypeOfCalledSubscriber[2];
    unsigned char n62_TypeOfSignalling[2];
    unsigned char n63_LengthIndicatorForAbbreviatedNumber[2];
    unsigned char n64_AbbreviatedNumber[5];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n68_SubscrServiceIndicator[3];
    unsigned char n72_ConferenceCallIndicator[2];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n78_OutgouingRoute[8];
    unsigned char n80_IncomingRoute[8];
    unsigned char n82_ReroutingIndicator[2];
    unsigned char n83_OriginatingCode[2];
    unsigned char n84_DestinationCode[2];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
    unsigned char n88_NetvorkConversionType[3];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[5];
    unsigned char n90_NumberOfUserToUser[2];
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[17];
    unsigned char n92_EndToEndAccessDataMap[9];
    unsigned char n93_EndToEndAccessDataIndicator[2];
    unsigned char n94_EndToEndAccessDataCounter[4];
    unsigned char n108_ForcedDisconnectionInformation[2];
    unsigned char n109_CarrierAccessCode[7];
    unsigned char n111_PresentationIndicator[2];
} RECORD_TYPE02MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n2_CauseForOutput[2];
    unsigned char n3_RecordNumber[3];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n16_Acategory[3];
    unsigned char n17_AnumberType[4];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n19_AsubscrType[3];
    unsigned char n20_LengthIndicatorForBsubscr[3];
    unsigned char n21_Bnumber[19];
    unsigned char n23_Bcategory[3];
    unsigned char n24_BsubscrNumberType[4];
    unsigned char n25_BsubscrNumberingPlanIndicator[3];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[3];
    unsigned char n27_CallingPartyNumber[21];
    unsigned char n28_LengthIndicatorForRedirectingNumber[3];
    unsigned char n29_RedirectingNumber[21];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[3];
    unsigned char n31_CalledPartyNumber[19];
    unsigned char n32_LengthIndicatorForOriginallyCalledNumber[3];
    unsigned char n33_OriginallyPartyNumber[21];
    unsigned char n34_FaultCode[6];
    unsigned char n35_CallStatus[2];
    unsigned char n36_AbnormalReleaseIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n43_TimeForStopOfCharging[7];
    unsigned char n44_TimeRegisterSizureStartCharging[7];
    unsigned char n45_ChargeableDuration[7];
    unsigned char n46_InterruptionTime[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n48_ImmediateServiceIndicator[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n54_TariffSwitchingIndicator[2];
    unsigned char n57_CallAttemptIndicator[2];
    unsigned char n61_TypeOfCalledSubscriber[2];
    unsigned char n62_TypeOfSignalling[2];
    unsigned char n63_LengthIndicatorForAbbreviatedNumber[2];
    unsigned char n64_AbbreviatedNumber[5];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n68_SubscrServiceIndicator[3];
    unsigned char n72_ConferenceCallIndicator[2];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n78_OutgouingRoute[8];
    unsigned char n80_IncomingRoute[8];
    unsigned char n82_ReroutingIndicator[2];
    unsigned char n83_OriginatingCode[2];
    unsigned char n84_DestinationCode[2];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[5];
    unsigned char n90_NumberOfUserToUser[2];
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[17];
    unsigned char n92_EndToEndAccessDataMap[9];
    unsigned char n93_EndToEndAccessDataIndicator[2];
    unsigned char n94_EndToEndAccessDataCounter[4];
    unsigned char n108_ForcedDisconnectionInformation[2];
    unsigned char n109_CarrierAccessCode[7];
    unsigned char n111_PresentationIndicator[2];
} RECORD_TYPE04MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n16_Acategory[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n19_AsubscrType[3];
    unsigned char n20_LengthIndicatorForBsubscr[3];
    unsigned char n21_Bnumber[19];
    unsigned char n23_Bcategory[3];
    unsigned char n34_FaultCode[6];
    unsigned char n35_CallStatus[2];
    unsigned char n36_AbnormalReleaseIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n43_TimeForStopOfCharging[7];
    unsigned char n44_TimeRegisterSizureStartCharging[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n48_ImmediateServiceIndicator[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n68_SubscrServiceIndicator[3];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
    unsigned char n108_ForcedDisconnectionInformation[2];
} RECORD_TYPE06MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n16_Acategory[3];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
} RECORD_TYPE07MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11]; //??
    unsigned char n112_DateOfExecutionOfCommand[7];
    unsigned char n113_TimeOfExecutionOfComand[7];
    unsigned char n114_CommandName[6];
} RECORD_TYPE08MY;

typedef struct {
    unsigned char n1_RecType[3];
    unsigned char n2_CauseForOutput[2];
    unsigned char n3_RecordNumber[3];
    unsigned char n4_CallIdenificationNumber[9];
    unsigned char n6_RecordSequenceNumber[9];
    unsigned char n8_OutputForSubscriber[2];
    unsigned char n13_LengthIndicatorForAnumber[3];
    unsigned char n14_Anumber[11];
    unsigned char n16_Acategory[3];
    unsigned char n17_AnumberType[4];
    unsigned char n18_AsubscrNumberingPlanIndicator[3];
    unsigned char n19_AsubscrType[3];
    unsigned char n20_LengthIndicatorForBsubscr[3];
    unsigned char n21_Bnumber[19];
    unsigned char n23_Bcategory[3];
    unsigned char n24_BsubscrNumberType[4];
    unsigned char n25_BsubscrNumberingPlanIndicator[3];
    unsigned char n26_LengthIndicatorForCallingPartyNumber[3];
    unsigned char n27_CallingPartyNumber[21];
    unsigned char n30_LengthIndicatorForCalledPartyNumber[3];
    unsigned char n31_CalledPartyNumber[19];
    unsigned char n34_FaultCode[6];
    unsigned char n35_CallStatus[2];
    unsigned char n36_AbnormalReleaseIndicator[2];
    unsigned char n37_DateForStartOfChargingUSA[7];
    unsigned char n40_TimeForStartOfCharging24hour[7];
    unsigned char n43_TimeForStopOfCharging[7];
    unsigned char n44_TimeRegisterSizureStartCharging[7];
    unsigned char n45_ChargeableDuration[7];
    unsigned char n46_InterruptionTime[7];
    unsigned char n47_ChargedParty[2];
    unsigned char n48_ImmediateServiceIndicator[2];
    unsigned char n49_Price[9];
    unsigned char n50_PulseChargingIndicator[2];
    unsigned char n51_NumberOfMeterPulses[7];
    unsigned char n52_OriginForCharging[5];
    unsigned char n53_TariffClass[4];
    unsigned char n54_TariffSwitchingIndicator[2];
    unsigned char n57_CallAttemptIndicator[2];
    unsigned char n58_CallAttemptState[3];
    unsigned char n59_CauseCode[4];
    unsigned char n60_LocationCode[3];
    unsigned char n61_TypeOfCalledSubscriber[2];
    unsigned char n62_TypeOfSignalling[2];
    unsigned char n63_LengthIndicatorForAbbreviatedNumber[2];
    unsigned char n64_AbbreviatedNumber[5];
    unsigned char n66_ResultOfSubscriberServiceProcedure[2];
    unsigned char n67_TypeOfProcedure[3];
    unsigned char n68_SubscrServiceIndicator[3];
    unsigned char n72_ConferenceCallIndicator[2];
    unsigned char n76_ExchngeIdentity[16];
    unsigned char n78_OutgouingRoute[8];
    unsigned char n80_IncomingRoute[8];
    unsigned char n82_ReroutingIndicator[2];
    unsigned char n83_OriginatingCode[2];
    unsigned char n84_DestinationCode[2];
    unsigned char n85_TypeOfSizure[3];
    unsigned char n86_TypeOfIndicator[3];
    unsigned char n87_TelecommunicationServiceCode[4];
    unsigned char n88_NetvorkConversionType[3];
    unsigned char n89_NumberOfUserToUserMessagesDuringCall[5];
    unsigned char n90_NumberOfUserToUser[2];
    unsigned char n91_SubscrServiceForISDNSuplimentaryServices[17];
    unsigned char n92_EndToEndAccessDataMap[9];
    unsigned char n93_EndToEndAccessDataIndicator[2];
    unsigned char n94_EndToEndAccessDataCounter[4];
    unsigned char n108_ForcedDisconnectionInformation[2];
    unsigned char n109_CarrierAccessCode[7];
    unsigned char n111_PresentationIndicator[2];
} RECORD_TYPE09MY;

//**************************************************************************************

const char NE[2] = {'0', '0'};
const char NI[2] = {'0', '1'};
const char NEI[2] = {'0', '2'};
const char NII[2] = {'0', '3'};
const char CDE[2] = {'0', '4'};
const char CDI[2] = {'0', '5'};
const char SP[2] = {'0', '6'};
const char NC[2] = {'0', '7'};
const char SSC[2] = {'0', '8'};
const char NEIE[2] = {'0', '9'};
const char NIIE[2] = {'1', '0'};

char * gettime();
void GetRecordsFromBuf(char * buffer);
void prepareDataBatchLoading();