#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include "main.h"
#include "neax61.h"

using namespace std;

globalArgs_t globalArgs;		// declare in main.h
CdrFileParams_t CdrFileParams;	// declare in main.h

int job()
{
	int count=0;
	char buf[256] = {0}; 
	char buffer[128] = {0};

	CdrFileParams.firstRecordYear[0] = 0;
	CdrFileParams.firstRecordMonth[0] = 0;

	if( globalArgs.dstFileName != NULL )
	{
		if ( (globalArgs.dstFile = fopen(globalArgs.dstFileName, "a")) == NULL)
		{
			printf("Error open file: \"%s\"\n", globalArgs.dstFileName);
			exit(1);
		}
	}			
	
	if ((globalArgs.srcFile = fopen(globalArgs.srcFileName, "rb")) == NULL)
	{
		printf("Error open file: \"%s\"\n", globalArgs.srcFileName);
		exit(1);
	}
	if(globalArgs.verbose == 1)
		printf("[%s] File: \"%s\" open sucsessfule\n",gettime(),globalArgs.srcFileName);
	while (!feof(globalArgs.srcFile))
	{
		int col = fread((void*)(buffer), sizeof(unsigned char), 128, globalArgs.srcFile);
		if (col<128) break;
		GetRecordsFromBuf(buffer);
		count++;
	} 
	if(globalArgs.sortDirName != NULL)
	{
		char curdirname[1024] = {0};
		char newfilename[256] = {0};
		FILE *newfile;
		int a;
		int errnum;

		getcwd(curdirname,sizeof(curdirname));
		mkdir(globalArgs.sortDirName);
		chdir(globalArgs.sortDirName);
		mkdir(CdrFileParams.firstRecordYear);
		chdir(CdrFileParams.firstRecordYear);
		mkdir(CdrFileParams.firstRecordMonth);
		chdir(CdrFileParams.firstRecordMonth);
		fseek(globalArgs.srcFile, 0, SEEK_SET);
		strcpy(buf,globalArgs.srcFileName);
		strcpy(newfilename, basename(buf));
		newfile = fopen(newfilename, "w");
		if(newfile != NULL)
			while (!feof(globalArgs.srcFile))
			{
				a  =  fgetc(globalArgs.srcFile);	
				fputc(a, newfile);
			}
		else
		{
			printf("error open file for remove orig file CDR\n");
			errnum = errno;
			fprintf(stderr, "Value of errno: %d\n", errno);
			perror("Error printed by perror");
			fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
		}
		chdir(curdirname);
		if(globalArgs.srcFile != stdin)
		{
			fclose(globalArgs.srcFile);
			globalArgs.srcFile = stdin;
		}	
		if(unlink(globalArgs.srcFileName) != 0)
			fprintf(stderr, "Error deleting file %s.\n", globalArgs.srcFileName);
	}
	if(globalArgs.srcFile != stdin) fclose(globalArgs.srcFile);
	if(globalArgs.dstFile != stdout) fclose(globalArgs.dstFile);
	if(globalArgs.verbose == 1)
		printf("[%s] Records in TT file: %d\n", gettime(), count);

	return 0;
}

int main (int argc, char **argv)
{
	int index;
	int c;

	opterr = 0;
	globalArgs.verbose = 0;
	globalArgs.srcFileName = NULL;
	globalArgs.srcDirName = NULL;
	globalArgs.dstFileName = NULL;
	globalArgs.sortDirName = NULL;
	globalArgs.srcFile = stdin;
	globalArgs.dstFile = stdout;

	while ((c = getopt (argc, argv, "i:o:vhd:s:")) != -1)
	 switch (c)
	   {
	   case 'i':
			globalArgs.srcFileName = optarg;
			break;
	   case 'd':
			globalArgs.srcDirName = optarg;
			break;
	   case 'o':
			globalArgs.dstFileName = optarg;
			break;
	   case 's':
			globalArgs.sortDirName = optarg;
			break;
	   case 'v':
			globalArgs.verbose = 1;
			break;
	   case 'h':
	   		printf("\n");
			printf("%-20s %s"," -i filename","CDR file name\n");
			printf("%-20s %s"," -d directory name","directory with CDR files\n");
	   		printf("%-20s %s"," -o filename","file name for output result\n");
	   		printf("%-20s %s","","if the file exists the result will be attached to it\n");
	   		printf("\n");
			printf("%-20s %s"," -s","the base directory in which directories are created form\n");
			printf("%-20s %s","","year/month to move the CDR files. Month and year are taken\n");
			printf("%-20s %s","","from the first record CDR file\n");
	   		printf("\n");
			printf("%-20s %s"," -v","verbose output\n");
	   		printf("%-20s %s"," -h","print this help\n");
	   		printf("\n");
	   		printf("Example:\n");
	   		printf("\n");
	   		printf("\tneaxcdr -i 00TT5721\n");
	   		printf("\tneaxcdr -i 00TT5721 -o simple_database.txt\n");
	   		printf("\tneaxcdr -d d:\\CDRFILE\\IN\\ -s d:\\CDRFILE\\ARCHIVE\\AXE10\\\n");
	   		printf("\n");
			printf("Trailing slash or backslash is required because platform-dependent\n");
			printf("For Windows is \\ for Unix like it /\n");
			return 1;
	   case '?':
		 if (optopt == 'i')
		   fprintf (stderr, "Option -%c requires AXE10 CDR file name as argument.\n", optopt);
		 else if (optopt == 'd')
		   fprintf (stderr, "Option -%c requires directory name with AXE10 CDR files as argument.\n", optopt);
		 else if (isprint (optopt))
		   fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		 else
		   fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
		 return 1;
	   default:
		 abort ();
	   }

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	if(globalArgs.srcFileName != NULL)
	{
		job();
		exit(0);
	}
	else if (globalArgs.srcDirName != NULL)
	{
		DIR *dp;
		struct dirent *ep;
		dp = opendir (globalArgs.srcDirName);
		if (dp != NULL)
        {
			while (ep = readdir (dp))
			{
				if(ep->d_name[0] != '.')
				{
					char fname[1024] = {0};
					strcpy(fname, globalArgs.srcDirName);
					strcat(fname, ep->d_name);
					globalArgs.srcFileName = fname;
					job();
				}
			}
			(void) closedir (dp);
        }
		else
			perror ("Couldn't open the directory");	
		exit(0);
	}
	else printf("enter -h for help.\n");

	return 0;
}
