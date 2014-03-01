//---------------------------------------------------------------------------

#ifndef module_5H
#define module_5H
//---------------------------------------------------------------------------

#include <fstream>
#include <istream>

using namespace std;

const int MAX_READ_CHARS = 1048576; //1 MB
const char HUFFMAN_FILE_EXT[] = "HUF";
const char NONISOMORPHIC_FILE_EXT[] = "NIF";
const char REPETITION_FILE_EXT[] = "RFF";
const char PARTITION_FILE_EXT[] = "PIF";
const char COMPRESSION_GAIN_FILE_EXT[] = "CGF";

char* getLine_FromFile(const char*, unsigned int);

#endif
