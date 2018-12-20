/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andrey.seredin
 *
 * Created on August 16, 2016, 3:37 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include "main.h"
#include "axecdr.h"
#include "ocilib.hpp"
#include "cdrstodb.h"
#include "md5sum.h"

using namespace std;

globalArgs_t globalArgs; // declare in main.h
CdrFileParams_t CdrFileParams; // declare in main.h

int main(int argc, char** argv) {
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
  globalArgs.srcFilenameBasename[0] = 0;

  while ((c = getopt(argc, argv, "i:l:p:d:vh?")) != -1) {
    switch (c) {
      case 'i':
        globalArgs.srcFileName = optarg;
        strcpy(globalArgs.srcFilenameBasename, basename(optarg));
        break;
      case 'l':
        globalArgs.dblogin = optarg;
        break;
      case 'p':
        globalArgs.dbpassword = optarg;
        break;
      case 'd':
        globalArgs.dbname = optarg;
        break;
      case 'v':
        globalArgs.verbose = 1;
        break;
      case 'h':
        printf("\n");
        printf("%-20s %s", " -i filename", "CDR file name\n");
        printf("%-20s %s", " -l", "databse login\n");
        printf("%-20s %s", " -p", "databse password\n");
        printf("%-20s %s", " -d", "databse name\n");
        printf("%-20s %s", " -v", "verbose output\n");
        printf("%-20s %s", " -h", "print this help\n");
        printf("\n");
        printf("Example:\n");
        printf("\n");
        printf("\taxecdr -i 00TT5721 -l dblogin -p dbpass -d dbname\n");
        return 1;
      case '?':
        if (optopt == 'i')
          fprintf(stderr, "Option -%c requires AXE10 CDR file name as argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
    }
  }

    for (index = optind; index < argc; index++)
      printf("Non-option argument %s\n", argv[index]);

    if (globalArgs.srcFileName != NULL) {
      calcMD5sum();
      prepareDataBatchLoading();
      loadCDRsToOraDb();
    } else {
      printf("enter -h for help.\n");
    }

    return 0;
}

