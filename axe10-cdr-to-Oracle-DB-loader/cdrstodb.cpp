#include <iostream>
#include "ocilib.hpp"
#include "main.h"
#include "cdrstodb.h"

using namespace ocilib;

#ifdef _WINDOWS                   
#define sleep(x) Sleep(x*1000)    
#endif                            
                                  
#define WaitForEvents()   sleep(5)

static Connection con;
const ostring format = "YYYY-MM-DD HH24:MI:SS";

std::vector<ostring> aNmbrs;
std::vector<ostring> bNmbrs;
std::vector<ostring> begTms;
std::vector<int> durs;
std::vector<ostring> incRts;
std::vector<ostring> outRts;
std::vector<ostring> recTypes;

unsigned long long int FileID = 0;

void writeToLog_FileLoadAttempt(){
  Statement st(con);

  st.Prepare("INSERT INTO LOADFILELOGS "
             "(FILENAME,LDSTART,MD5SUM,NOTE) "
             "VALUES(:fn,:lds,:md5,:note)");

  ostring fn = globalArgs.srcFilenameBasename;
  ostring md5 = globalArgs.md5sum.c_str();
  ocilib::Date date = Date::SysDate();
  ostring note = "попытка загрузить данные из файла";
  
  //std::cout << "fn=" << fn << " date=" << date.ToString(format) << " md5=" << md5 << " note=" << note << std::endl;
  
  st.Bind(":fn", fn, 100, BindInfo::In);
  st.Bind(":lds", date, BindInfo::In);
  st.Bind(":md5", md5, 50, BindInfo::In);
  st.Bind(":note", note, 100, BindInfo::In);
  st.ExecutePrepared();
  con.Commit();
}

void writeToLog_FileLoadSuccess(){
  Statement st(con);

  st.Prepare("INSERT INTO LOADFILELOGS "
             "(filename,LDSTART,MD5SUM,NOTE) "
             "VALUES(:fn,:lds,:md5,:note)");

  ostring fn = globalArgs.srcFilenameBasename;
  st.Bind(":fn", fn, 100, BindInfo::In);
  ocilib::Date date1 = Date::SysDate();
  st.Bind(":lds", date1, BindInfo::In);
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  ostring note = "данные из файла загружены успешно";
  st.Bind(":note", note, 100, BindInfo::In);

  st.ExecutePrepared();
  con.Commit();
}

void writeToLog_FileExistInBase(){
  Statement st(con);

  st.Prepare("INSERT INTO LOADFILELOGS "
             "(filename,LDSTART,MD5SUM,NOTE) "
             "VALUES(:fn,:lds,:md5,:note)");

  ostring fn = globalArgs.srcFilenameBasename;
  st.Bind(":fn", fn, 100, BindInfo::In);
  ocilib::Date date1 = Date::SysDate();
  st.Bind(":lds", date1, BindInfo::In);
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  ostring note = "данные из файла уже загружены раньше";
  st.Bind(":note", note, 200, BindInfo::In);

  st.ExecutePrepared();
  con.Commit();
}

void writeToLog_LoadCDRfromFileBEGIN(){
  Statement st(con);

  st.Prepare("INSERT INTO LOADFILELOGS "
             "(filename,LDSTART,MD5SUM,NOTE) "
             "VALUES(:fn,:lds,:md5,:note)");

  ostring fn = globalArgs.srcFilenameBasename;
  st.Bind(":fn", fn, 100, BindInfo::In);
  ocilib::Date date1 = Date::SysDate();
  st.Bind(":lds", date1, BindInfo::In);
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  ostring note = "начало загрузки данных из файла";
  st.Bind(":note", note, 200, BindInfo::In);
  st.ExecutePrepared();
  con.Commit();
}

void setIdAfter_LoadCDRfromFileBEGIN(){
  Statement st(con);
  st.Prepare("select * from loadfilelogs where "
             "(md5sum = :md5) AND (note = 'начало загрузки данных из файла')");
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  st.ExecutePrepared();
  Resultset rs = st.GetResultset();
  while (rs++)
  {
    FileID = rs.Get<int>("id");
    //std::cout << "id=" << FileID << std::endl;
  }
}

void writeToLog_LoadCDRfromFileEND(){
  Statement st(con);

  st.Prepare("INSERT INTO LOADFILELOGS "
             "(filename,LDSTART,MD5SUM,NOTE) "
             "VALUES(:fn,:lds,:md5,:note)");

  ostring fn = globalArgs.srcFilenameBasename;
  st.Bind(":fn", fn, 100, BindInfo::In);
  ocilib::Date date1 = Date::SysDate();
  st.Bind(":lds", date1, BindInfo::In);
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  ostring note = "конец загрузки данных из файла";
  st.Bind(":note", note, 200, BindInfo::In);

  st.ExecutePrepared();
  con.Commit();
}

int checkfileinbase(){
  Statement st(con);
  st.Prepare("select * from loadfilelogs where "
             "(md5sum = :md5) AND (note = 'данные из файла загружены успешно')");
  ostring md5 = globalArgs.md5sum.c_str();
  st.Bind(":md5", md5, 50, BindInfo::In);
  st.ExecutePrepared();
  
  Resultset rs1 = st.GetResultset();
  int count = 0;
  while (rs1++)                                                         
  {
    ostring md5sum = rs1.Get<ostring>("md5sum");
    int id = rs1.Get<int>("id");
    count++;
  }
  return count;
}

void insert_data_to_table() {
  std::vector<ocilib::Date> begTms2;
  for (int i = 0; i < begTms.size(); i++) {
    Date date(begTms[i], format);
    begTms2.push_back(date);
  }
  std::vector<unsigned long long int> fileIds;
  for (int i = 0; i < begTms.size(); i++) {
    fileIds.push_back(FileID);
  }

  Statement st(con);
  st.Prepare("INSERT INTO AXE10 "
             "(anum,bnum,chargstart,dur,incrt,outrt,rectype,loadfilelog_id) "
             "VALUES (:anum,:bnum,:chargstart,:dur,:incrt,:outrt,:rectype,:fid)");
  st.SetBindArraySize(aNmbrs.size());
  st.Bind(":anum", aNmbrs, 20, BindInfo::In);
  st.Bind(":bnum", bNmbrs, 20, BindInfo::In);
  st.Bind(":chargstart", begTms2, BindInfo::In);
  st.Bind(":dur", durs, BindInfo::In);
  st.Bind(":incrt", incRts, 20, BindInfo::In);
  st.Bind(":outrt", outRts, 20, BindInfo::In);
  st.Bind(":rectype", recTypes, 20, BindInfo::In);
  st.Bind(":fid", fileIds, BindInfo::In);
  st.ExecutePrepared();
  con.Commit();
  if (globalArgs.verbose == 1) {
    std::cout << "insert_data_to_table() AXE10 row processed : " << st.GetAffectedRows() << std::endl;
  }
}

int loadCDRsToOraDb() {
  int err = -1;
  try {
    Environment::Initialize();
    Environment::EnableWarnings(true);
    ostring dbuser = globalArgs.dblogin.c_str();
    ostring dbpwd = globalArgs.dbpassword.c_str();
    ostring dbname = globalArgs.dbname.c_str();
    con.Open(dbname, dbuser, dbpwd, Environment::SessionDefault);
    
    writeToLog_FileLoadAttempt();
    if(checkfileinbase() == 0){
      writeToLog_LoadCDRfromFileBEGIN();
      setIdAfter_LoadCDRfromFileBEGIN();
      insert_data_to_table();
      writeToLog_LoadCDRfromFileEND();
      writeToLog_FileLoadSuccess();
    }else{
      std::cout << "loadCDRsToOraDb() - file alredy in database: " 
                << globalArgs.srcFileName << std::endl;
      writeToLog_FileExistInBase();
    }
       
    con.Close();
    err = EXIT_SUCCESS;
  } catch (std::exception &ex) {
    std::cout << "loadCDRsToOraDb() - EXCEPTION: " << ex.what() << std::endl;
    err = -1;
    con.Close();
  }
  Environment::Cleanup();
  return err;
}
