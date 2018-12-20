typedef struct _AMA_FORMAT
	{
		unsigned char HEADER;
		unsigned char Anomber[15];
		unsigned char AnomberCategory[2];
		unsigned char spare0[4];
		unsigned char Bnomber[32];
		unsigned char date[6];
		unsigned char time[6];
		unsigned char duration[6];
		unsigned char IncomingRouteName[8];
		unsigned char IncCircNomb[4];
		unsigned char OutgoingRouteName[8];
		unsigned char OutCircNomb[4];
		unsigned char ChargeMeter[7];
		unsigned char MBI[3];
		unsigned char RATE;
		unsigned char CALL_TYPE;
		unsigned char spare1[2];
		unsigned char ServiceCategory[2];
		unsigned char spare2;
		unsigned char spare3[2];
		unsigned char spare4;
		unsigned char spare5[12];
	} AMA_FORMAT;

typedef struct __AMA_FORMAT
	{
		unsigned char HEADER[2];
		unsigned char Anomber[16];
		unsigned char AnomberCategory[3];
		unsigned char spare0[5];
		unsigned char Bnomber[33];
		unsigned char date[7];
		unsigned char time[7];
		unsigned char duration[7];
		unsigned char IncomingRouteName[9];
		unsigned char IncCircNomb[5];
		unsigned char OutgoingRouteName[9];
		unsigned char OutCircNomb[5];
		unsigned char ChargeMeter[8];
		unsigned char MBI[4];
		unsigned char RATE[2];
		unsigned char CALL_TYPE[2];
		unsigned char spare1[3];
		unsigned char ServiceCategory[4];
		unsigned char spare2[2];
		unsigned char spare3[3];
		unsigned char spare4[2];
		unsigned char spare5[13];
		unsigned char END[2];
	} AMA_FORMAT_MY;

char * gettime();
void GetRecordsFromBuf(char * buffer);
void prepareDataBatchLoading();
