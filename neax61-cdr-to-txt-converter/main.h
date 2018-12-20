//header file for main.cpp

struct globalArgs_t {
    const char *srcFileName;    /* �������� -i */
    const char *dstFileName;    /* �������� -o */
    const char *srcDirName;     /* �������� -d */
    const char *sortDirName;     /* �������� -d */
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
