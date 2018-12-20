//header file for main.cpp

typedef unsigned char BYTE;

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

