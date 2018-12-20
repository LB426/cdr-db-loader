/* 
 * File:   cdrstodb.h
 * Author: andrey.seredin
 *
 * Created on August 16, 2016, 4:36 PM
 */

int loadCDRsToOraDb();

extern std::vector<ocilib::ostring> aNmbrs;
extern std::vector<ocilib::ostring> bNmbrs;
extern std::vector<ocilib::ostring> begTms;
extern std::vector<int> durs;
extern std::vector<ocilib::ostring> incRts;
extern std::vector<ocilib::ostring> outRts;
extern std::vector<ocilib::ostring> recTypes;