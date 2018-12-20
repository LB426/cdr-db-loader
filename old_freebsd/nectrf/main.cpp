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

char *DurSec(char *dur)
{
 char min[5], sek[3];
 min[0]=dur[0];min[1]=dur[1];min[2]=dur[2];min[3]=dur[3];min[4]=0;
 sek[0]=dur[4];sek[1]=dur[5];sek[2]=0;
 int m=atoi(min);
 int s=atoi(sek);
 int d=m*60+s;
 memset((void*)dur,0,32);
 snprintf(dur,32,"%d",d);
 return dur;
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
 char str[128];
 int i=0; int j=0;
 int k=strlen(buf);
 for (i=0;i<k;i++)
 {
  if(buf[i] != ' ') 
  {
   str[j]=buf[i];
   j++;
  }
 }
 str[j]=0;
 strcpy(buf,str);
 //buf[j]=0;
 return buf;
}

void AddRecIntoBase(AMA_FORMAT *pAmaRec)
{
//printf("\n*****************************************************************************\n");
 AMA_FORMAT_MY AmaMy; 
 memset((void*)&AmaMy,0,sizeof(AMA_FORMAT_MY));
 FillAmaMyStruct(pAmaRec, &AmaMy);
 char * anomb= RejectAllSimbols(AmaMy.Anomber);
 char * catA = RejectAllSimbols((char*)AmaMy.AnomberCategory);
 char * bnomb= RejectAllSimbols((char*)AmaMy.Bnomber);
 char bfdt[64],bftm[64],bfdr[64];
 memset((void*)bfdt,0,sizeof(bfdt));
 memset((void*)bftm,0,sizeof(bftm));
 memset((void*)bfdr,0,sizeof(bfdr));
 strcpy(bfdt,RejectAllSimbols((char*)AmaMy.date));
 char * date    = InSQLDataFormat(bfdt);
 strcpy(bftm,RejectAllSimbols((char*)AmaMy.time));
 char * time = InSQLTimeFormat(bftm);
 strcpy(bfdr,RejectAllSimbols((char*)AmaMy.duration));
 char * durat= DurSec(bfdr);
 char * incr = RejectAllSimbols((char*)AmaMy.IncomingRouteName);
 char * inccn= RejectAllSimbols((char*)AmaMy.IncCircNomb);
 char * outr = RejectAllSimbols((char*)AmaMy.OutgoingRouteName);
 char * outcn= RejectAllSimbols((char*)AmaMy.OutCircNomb);
 char * chrgm= RejectAllSimbols((char*)AmaMy.ChargeMeter);
 char * mbi  = RejectAllSimbols((char*)AmaMy.MBI);
 char * rate = RejectAllSimbols((char*)AmaMy.RATE);
 char * callt= RejectAllSimbols((char*)AmaMy.CALL_TYPE);
 char * svcat= RejectAllSimbols((char*)AmaMy.ServiceCategory);  
 //printf("%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s\n",anomb,catA,bnomb,
//	 date,time,durat,incr,inccn,outr,outcn,chrgm,mbi,rate,callt,svcat);

char fields[1024];memset((void*)fields,0,sizeof(fields));
char values[1024];memset((void*)values,0,sizeof(values));    
if(strlen(anomb)==0){strcpy(anomb,"nomerNEopred");};
if(strlen(anomb)!=0){strcat(fields,"anomb");strcat(values,"'");strcat(values,anomb);strcat(values,"'");};
if(strlen(catA)!=0){strcat(fields,",cata");strcat(values,",");strcat(values,catA);};
if(strlen(bnomb)!=0){strcat(fields,",bnomb");strcat(values,",'");strcat(values,bnomb);strcat(values,"'");};
if(strlen(date)==10){strcat(fields,",dt");strcat(values,",'");strcat(values,date);strcat(values,"'");};
if(strlen(time)==8){strcat(fields,",tm");strcat(values,",'");strcat(values,time);strcat(values,"'");};
if(strlen(durat)!=0){strcat(fields,",dur");strcat(values,",");strcat(values,durat);};
if(strlen(incr)!=0){strcat(fields,",incrt");strcat(values,",'");strcat(values,incr);strcat(values,"'");};
if(strlen(inccn)!=0){strcat(fields,",inccn");strcat(values,",");strcat(values,inccn);};
if(strlen(outr)!=0){strcat(fields,",outrt");strcat(values,",'");strcat(values,outr);strcat(values,"'");};
if(strlen(outcn)!=0){strcat(fields,",outcn");strcat(values,",");strcat(values,outcn);};
if(strlen(chrgm)!=0){strcat(fields,",chrgm");strcat(values,",");strcat(values,chrgm);};
if(strlen(mbi)!=0){strcat(fields,",mbi");strcat(values,",");strcat(values,mbi);};
if(strlen(rate)!=0){strcat(fields,",rate");strcat(values,",");strcat(values,rate);};
if(strlen(callt)!=0){strcat(fields,",calltp");strcat(values,",");strcat(values,callt);};
if(strlen(svcat)!=0){strcat(fields,",svcat");strcat(values,",");strcat(values,svcat);};

if(fields[0]==',')fields[0]=' ';
if(values[0]==',')values[0]=' ';
char sql[4096];memset((void*)sql,0,sizeof(sql));
strcpy(sql,"INSERT INTO nec (");
strcat(sql,fields);
strcat(sql,") VALUES (");
strcat(sql,values);
strcat(sql,");");
//printf("%s\n",sql);

 res = PQexec(conn, sql);
 if (PQresultStatus(res) != PGRES_COMMAND_OK){
  printf("Command failed: %sSQL:\n%s", PQerrorMessage(conn),sql);
  PQclear(res);
  return;
 }
 PQclear(res);
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

int GetFilePeriod(FILE * f,char * period,char * filename)
{
	AMA_FORMAT AmaRec;
	AMA_FORMAT_MY AmaMy;
	fread((void*)(&AmaRec), sizeof(BYTE), (sizeof(AMA_FORMAT)), f);
	FillAmaMyStruct(&AmaRec, &AmaMy);
	strcat(filename,"-");strcat(filename,(char*)AmaMy.date);strcat(filename,(char*)AmaMy.time);
	char dt1[16];dt1[15]=0; strcpy(dt1,(char*)AmaMy.date);InSQLDataFormat(dt1);
	char tm1[16];tm1[15]=0; strcpy(tm1,(char*)AmaMy.time);InSQLTimeFormat(tm1);
	int rs = fseek(f,-128,SEEK_END);
	if (rs!=0)printf("fseek error=%d\n",rs);
	fread((void*)(&AmaRec), sizeof(BYTE), (sizeof(AMA_FORMAT)), f);
	FillAmaMyStruct(&AmaRec, &AmaMy);
	strcat(filename,"-");strcat(filename,(char*)AmaMy.date);strcat(filename,(char*)AmaMy.time);
	char dt2[16];dt2[15]=0; strcpy(dt2,(char*)AmaMy.date);InSQLDataFormat(dt2);
	char tm2[16];tm2[15]=0; strcpy(tm2,(char*)AmaMy.time);InSQLTimeFormat(tm2);
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
	char sql[128];sql[127]=0;
	strcpy(sql,"SELECT * FROM amalog WHERE firstrec='");
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
  strcpy(coninfo,argv[1]);
  conn = PQconnectdb(coninfo);
  if (PQstatus(conn) != CONNECTION_OK)
  {
   printf("Connection to database failed: %s",PQerrorMessage(conn));
   exit_nicely(conn);
  } 
  else
  {
   printf("[%s] Connection to database open.\n",gettime());
  }
 }else{
	printf("Enter DB connect parameters.\n");
 	printf("hostaddr=127.0.0.1 port=5432 dbname=tariff user=postgres password=postgres\n");
	exit(1);
 }
 int count=0;
 char buf[256]; 
 buf[255]=0;
 while (!feof(stdin))
 {
  fgets(buf,255,stdin);
  if ((strlen(buf) != NULL) && (strstr(buf,"cdr")!=NULL)) 
  {
   if(strstr(buf,"-")!=NULL) continue; 
   buf[strlen(buf)-1]=0;
  
   FILE * amaf;
   if ((amaf = fopen(buf, "rb"))==NULL){
	printf("Error open file: \"%s\"\n",buf);
   }
   else
    printf("[%s] File: \"%s\" open sucsessfule\n",gettime(),buf);

   char period[64];period[63]=0; 
   char NewFname[320];NewFname[0]=0;strcpy(NewFname,buf);
   int resultGFP=GetFilePeriod(amaf,period,NewFname);
   if (resultGFP==0){
//	printf("period=%s\n",period);
//	printf("The file NOT in base\n");

	while (!feof(amaf)){
		AMA_FORMAT AmaRec;
		AMA_FORMAT *pAmaRec = &AmaRec;
		int col = fread((void*)(pAmaRec), sizeof(BYTE), (sizeof(AMA_FORMAT)), amaf);
		if (col<128) break;
		AddRecIntoBase(pAmaRec);
		count++;
	}

	char sqlcmd[128];sqlcmd[127]=0;
	strcpy(sqlcmd,"INSERT INTO amalog VALUES ('");
	strcat(sqlcmd,buf);
	strcat(sqlcmd,"','");
	strncat(sqlcmd,period,19);		
	strcat(sqlcmd,"','");
	strncat(sqlcmd,period+20,19);
	strcat(sqlcmd,"');");
	//printf("sqlcmd=%s\n",sqlcmd);
 	res = PQexec(conn, sqlcmd);
	if (PQresultStatus(res) != PGRES_COMMAND_OK){
		printf("res: %s\n", PQerrorMessage(conn));
	}
  	PQclear(res);
   }else{
	printf("[%s] The file: %s has been alredy is in base\n",gettime(),buf);
   }
   fclose(amaf);
   if (resultGFP==0)RenameFile(buf,NewFname);
  }
  buf[0]=0;
 }

 PQfinish(conn);
 printf("[%s] Records in cdr files: %d\n",gettime(),count);
 printf("[%s] Connection to database close\n",gettime()); 
 printf("[%s] Data from cdr files sucessfull insert in base. View error in log file.\n",gettime());

 return 0;
}
