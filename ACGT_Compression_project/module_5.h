//COMPRESSION PROJECT: MODULE 5 FILE API: module_5.h
//Created by Mathys Ellis 30/02/2014
//---------------------------------------------------------------------------

#ifndef module_5H
#define module_5H
//---------------------------------------------------------------------------

#include <fstream>
#include <istream>
#include "module_0.h"

using namespace std;

const int MAX_READ_CHARS = 1048576; //1 MB
const char HUFFMAN_FILE_EXT[] = "HUF";
const char NONISOMORPHIC_FILE_EXT[] = "NIF";
const char REPETITION_FILE_EXT[] = "RFF";
const char PARTITION_FILE_EXT[] = "PWF";
const char COMPRESSION_GAIN_FILE_EXT[] = "CGF";

char* getLine_FromFile(const char*, unsigned int);

#endif
