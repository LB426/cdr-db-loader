//header file for main.cpp

struct globalArgs_t {
    const char *srcFileName;    /* параметр -i */
    const char *dstFileName;    /* параметр -o */
    const char *srcDirName;     /* параметр -d */
    const char *sortDirName;     /* параметр -d */
	int verbose;
	FILE *srcFile;
	FILE *dstFile;
};

struct CdrFileParams_t {
	char firstRecordYear[5];
	char firstRecordMonth[3];
};

extern globalArgs_t globalArgs; 		// define in main.cpp
extern CdrFileParams_t CdrFileParams; 	// define in main.cpp
