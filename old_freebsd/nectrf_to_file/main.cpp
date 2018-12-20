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

char * InSQLDataFormat(char * amadata)
{
 char year[5], month[3], day[3],*date;
 year[0]='2';year[1]='0',year[2]=amadata[0];year[3]=amadata[1];year[4]=0;
 month[0]=amadata[2];month[1]=amadata[3];month[2]=0;
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
 if ((buf = (char *) malloc(22+ j * sizeof(char))) == NULL)
 {
  cout << "not enougth space for malloc buf\n" ;
 }
 strcpy(buf,str);
 buf[j]=0;
 return buf;
}

void AddRecIntoBase(AMA_FORMAT *pAmaRec)
{
 AMA_FORMAT_MY AmaMy; 
 memset((void*)&AmaMy,0,sizeof(AMA_FORMAT_MY));
 FillAmaMyStruct(pAmaRec, &AmaMy);
 char * anomb= RejectAllSimbols((char*)AmaMy.Anomber);
 char * catA = RejectAllSimbols((char*)AmaMy.AnomberCategory);
 char * bnomb= RejectAllSimbols((char*)AmaMy.Bnomber);
 char * amadate = RejectAllSimbols((char*)AmaMy.date);
 char * date    = InSQLDataFormat(amadate);
 free(amadate);
 char * amatime = RejectAllSimbols((char*)AmaMy.time);
 char * time = InSQLTimeFormat(amatime);
 free(amatime);
 char * dur  = RejectAllSimbols((char*)AmaMy.duration);
 char * durat= DurSec(dur);
 free(dur);
 char * incr = RejectAllSimbols((char*)AmaMy.IncomingRouteName);
 char * inccn= RejectAllSimbols((char*)AmaMy.IncCircNomb);
 char * outr = RejectAllSimbols((char*)AmaMy.OutgoingRouteName);
 char * outcn= RejectAllSimbols((char*)AmaMy.OutCircNomb);
 char * chrgm= RejectAllSimbols((char*)AmaMy.ChargeMeter);
 char * mbi  = RejectAllSimbols((char*)AmaMy.MBI);
 char * rate = RejectAllSimbols((char*)AmaMy.RATE);
 char * callt= RejectAllSimbols((char*)AmaMy.CALL_TYPE);
 char * svcat= RejectAllSimbols((char*)AmaMy.ServiceCategory);  
// printf("%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s:%s",anomb,catA,bnomb,
// date,time,durat,incr,inccn,outr,outcn,chrgm,mbi,rate,callt,svcat);
// printf("\n");

char fields[2048];memset((void*)fields,0,sizeof(fields));
char values[2048];memset((void*)values,0,sizeof(values));    
if(strlen(anomb)==0){strcat(anomb,"nomerNEopred");};
if(strlen(anomb)!=0){strcat(fields,"anomb");strcat(values,"'");strcat(values,anomb);strcat(values,"'");};
if(strlen(catA)!=0){strcat(fields,",cata");strcat(values,",");strcat(values,catA);};
if(strlen(bnomb)!=0){strcat(fields,",bnomb");strcat(values,",'");strcat(values,bnomb);strcat(values,"'");};
if(strlen(date)!=0){strcat(fields,",dt");strcat(values,",'");strcat(values,date);strcat(values,"'");};
if(strlen(time)!=0){strcat(fields,",tm");strcat(values,",'");strcat(values,time);strcat(values,"'");};
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
//if(values[0]=='\'')values[0]=' '; 
char sql[8192];memset((void*)sql,0,sizeof(sql));
strcpy(sql,"INSERT INTO nec (");
strcat(sql,fields);
strcat(sql,") VALUES (");
strcat(sql,values);
strcat(sql,");");
printf("%s\n",sql);

/*res = PQexec(conn, sql);
if (PQresultStatus(res) != PGRES_COMMAND_OK)
{
 //fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
 printf("\ncommand failed: %s,\nSQL:\n%s", PQerrorMessage(conn),sql);
 PQclear(res);
 //exit_nicely(conn);
}*/

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
//exit(0);
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

int main(int argc, char **argv)
{
// char coninfo[256];
// strcpy(coninfo,"hostaddr=127.0.0.1 port=5432 dbname=tariff user=postgres password=postgres");
// strcpy(coninfo,argv[1]);
/* conn = PQconnectdb(coninfo);
 if (PQstatus(conn) != CONNECTION_OK)
 {
  printf("Connection to database failed: %s",PQerrorMessage(conn));
  exit_nicely(conn);
 } 
 else
 {
  printf("[%s] Connection to database open.\n",gettime());
 }
*/ 
 int count=0;
 char buf[256]; 
 buf[255]=0;
 while (!feof(stdin))
 {
  fgets(buf,255,stdin);
  if ((strlen(buf) != NULL) && (strstr(buf,"cdr")!=NULL)) 
  {
   buf[strlen(buf)-1]=0;
//   fprintf(stdout,"%d : %s\n",strlen(buf),buf);
  
   FILE * amaf;
   if ((amaf = fopen(buf, "rb"))==NULL)
   {
    printf("Error open file: \"%s\"\n",buf);
   }
 //  else
 //   printf("[%s] File: \"%s\" open sucsessfule\n",gettime(),buf);
   while (!feof(amaf))
   {
    AMA_FORMAT AmaRec;
    AMA_FORMAT *pAmaRec = &AmaRec;
    int col = fread((void*)(pAmaRec), sizeof(BYTE), (sizeof(AMA_FORMAT)), amaf);
    if (col<128) break;
    AddRecIntoBase(pAmaRec);
    count++;
   }   
   fclose(amaf);
  }
//  else
//   printf("The folder has't cdr files\n");
  buf[0]=0;
 }

// PQfinish(conn);
// printf("[%s] Records in cdr files: %d\n",gettime(),count);
// printf("[%s] Connection to database close\n",gettime()); 

 return 0;
}
