#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neax61.h"
#include "main.h"

using namespace std;

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

char *DurSec(char *dur)
{
	char min[5], sek[3], *buf;
	min[0]=dur[0];min[1]=dur[1];min[2]=dur[2];min[3]=dur[3];min[4]=0;
	sek[0]=dur[4];sek[1]=dur[5];sek[2]=0;
	int m=atoi(min);
	int s=atoi(sek);
	int d=m*60+s;

	if ((buf = (char *) malloc(256*sizeof(char))) == NULL)
	{
	cout << "not enougth space for malloc buf\n" ;
	} 
	memset((void*)buf,0,256);
	snprintf(buf,32,"%d",d);
	// printf("itoa=%s\n",buf); 

	return buf;
}

char * InSQLDataFormat(char * amadata)
{
	char year[5], month[3], day[3],*date;
	year[0]='2';year[1]='0',year[2]=amadata[0];year[3]=amadata[1];year[4]=0;
	if(CdrFileParams.firstRecordYear[0] == 0)
		strcpy(CdrFileParams.firstRecordYear, year);
	month[0]=amadata[2];month[1]=amadata[3];month[2]=0;
	if(CdrFileParams.firstRecordMonth[0] == 0)
		strcpy(CdrFileParams.firstRecordMonth, month);
	day[0]=amadata[4];day[1]=amadata[5];day[2]=0;
	if ((date = (char *) malloc(256*sizeof(char))) == NULL)
	{
		cout << "not enougth space for malloc buf\n" ;
	} 
	strcpy(date,year);strcat(date,"-");strcat(date,month);strcat(date,"-");
	strcat(date,day);
	return date;
}

char * InSQLTimeFormat(char * amatime)
{
	char hour[3], min[3], sec[3], *time;
	hour[0]=amatime[0];hour[1]=amatime[1];hour[2]=0;
	min[0]=amatime[2];min[1]=amatime[3];min[2]=0;
	sec[0]=amatime[4];sec[1]=amatime[5];sec[2]=0; 
	if ((time = (char *) malloc(256*sizeof(char))) == NULL)
	{
		cout << "not enougth space for malloc buf\n" ;
	}

	strcpy(time,hour);strcat(time,":");strcat(time,min);strcat(time,":");
	strcat(time,sec);
	return time;
}

char * RejectAllSpaces(char * buf)
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
	if ((buf = (char *) malloc(22 + j * sizeof(char))) == NULL)
	{
		cout << "not enougth space for malloc buf\n" ;
	}
	strcpy(buf,str);
	buf[j]=0;
	return buf;
}

void FillAmaMyStruct(AMA_FORMAT *pAmaRec, AMA_FORMAT_MY * AmaMy)
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

void PrintRec(AMA_FORMAT_MY *pAmaRecMy)
{
	AMA_FORMAT_MY AmaMy;
	memset((void*)&AmaMy, 0, sizeof(AMA_FORMAT_MY));
	memcpy((void*)&AmaMy, (void*)pAmaRecMy, sizeof(AmaMy));
	char * anomb   = RejectAllSpaces((char*)AmaMy.Anomber);
	if(strlen(anomb) == 0)
		strcat(anomb,"undefined");
	char * catA    = RejectAllSpaces((char*)AmaMy.AnomberCategory);
	char * bnomb   = RejectAllSpaces((char*)AmaMy.Bnomber);
	char * amadate = RejectAllSpaces((char*)AmaMy.date);
	char * date    = InSQLDataFormat(amadate);
	free(amadate);
	char * amatime = RejectAllSpaces((char*)AmaMy.time);
	char * time    = InSQLTimeFormat(amatime);
	free(amatime);
	char * dur     = RejectAllSpaces((char*)AmaMy.duration);
	char * durat   = DurSec(dur);
	free(dur);
	char * incr    = RejectAllSpaces((char*)AmaMy.IncomingRouteName);
	if(strlen(incr) == 0)
		strcat(incr,"undefined");
	char * inccn   = RejectAllSpaces((char*)AmaMy.IncCircNomb);
	char * outr    = RejectAllSpaces((char*)AmaMy.OutgoingRouteName);
	if(strlen(outr) == 0)
		strcat(outr,"undefined");
	char * outcn   = RejectAllSpaces((char*)AmaMy.OutCircNomb);
	char * chrgm   = RejectAllSpaces((char*)AmaMy.ChargeMeter);
	char * mbi     = RejectAllSpaces((char*)AmaMy.MBI);
	char * rate    = RejectAllSpaces((char*)AmaMy.RATE);
	char * callt   = RejectAllSpaces((char*)AmaMy.CALL_TYPE);
	char * svcat   = RejectAllSpaces((char*)AmaMy.ServiceCategory);  
	//printf("%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s\n",anomb,catA,bnomb,date,time,durat,incr,inccn,outr,outcn,chrgm,mbi,rate,callt,svcat);
	fprintf(globalArgs.dstFile, "%s %s %s %s undefined %s %s %s\n", anomb, bnomb, date, time, durat, incr, outr);
	free(anomb);
	free(catA);
	free(bnomb);
	free(date);
	free(time);
	free(durat);
	free(incr);
	free(inccn);
	free(outr);
	free(outcn);
	free(chrgm);
	free(mbi);
	free(rate);
	free(callt);
	free(svcat);
}

void GetRecordsFromBuf(char * buffer)
{
    	AMA_FORMAT *pAmaRec = (AMA_FORMAT*)buffer;
	AMA_FORMAT_MY AmaRecMy; 
	memset((void*)&AmaRecMy,0,sizeof(AMA_FORMAT_MY));
	FillAmaMyStruct(pAmaRec, &AmaRecMy);
	PrintRec(&AmaRecMy);
}
