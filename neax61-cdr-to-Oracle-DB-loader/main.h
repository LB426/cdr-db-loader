//header file for main.cpp

struct globalArgs_t {
    const char *srcFileName; /* command line argument with -i key */
    const char *dstFileName; /* command line argument with -o key */
    const char *srcDirName; /* command line argument with -d key */
    const char *sortDirName; /* command line argument with -d key */
    int verbose;
    FILE *srcFile;
    FILE *dstFile;
    char srcFilenameBasename[64];
    std::string md5sum;
    std::string dblogin;
    std::string dbpassword;
    std::string dbname;
};

struct CdrFileParams_t {
    char firstRecordYear[5];
    char firstRecordMonth[3];
};

extern globalArgs_t globalArgs; // define in main.cpp
extern CdrFileParams_t CdrFileParams; // define in main.cpp


