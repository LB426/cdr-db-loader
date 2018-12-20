#include <iostream>
#include <stdlib.h>
#include <fstream>  
#include <string>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1                                                            
#include "hex.h"                                                                                    
#include "md5.h" 
#include "main.h"
#include "md5sum.h"

int calcMD5sum() {
  byte digest[ CryptoPP::Weak::MD5::DIGESTSIZE ];
  CryptoPP::Weak::MD5 hash;
  CryptoPP::HexEncoder encoder(NULL, false, 0, ":", "");
  std::string output;
  std::streamsize size;
  char * memblock;
  
  std::ifstream file(globalArgs.srcFileName, std::ios::binary | std::ios::ate | std::ios::in);
  if (file.is_open()) {
    size = file.tellg();
    memblock = new char [size];
    file.seekg(0, std::ios::beg);
    file.read(memblock, size);
    file.close();
    
    hash.CalculateDigest(digest, (const byte*) memblock, size);
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof (digest));
    encoder.MessageEnd();
    
    delete[] memblock;
  } else {
    std::cout << "calcMD5sum() - error open file " << globalArgs.srcFileName << std::endl;
    exit (EXIT_FAILURE);
  }
  globalArgs.md5sum = output;
  
  return 0;
}

