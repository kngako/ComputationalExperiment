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

const char EXP_INFO_FILE_NAME[] = "info.DAT";

const char PRECACHE_SUFFIX_FOLDER_NAME[] = "_precache";
const char HUFFMAN_FOLDER_NAME[] = "HuffmanTable";
const char NONISOMORPHIC_FOLDER_NAME[] = "NIFStrings";

const char PARTITIONEDDATA_SUFFIX_FOLDER_NAME[] = "_partitioneddata";
const char ALLPARTITIONS_FOLDER_NAME[] = "AllPartitions";
const char REPPARTITIONS_FOLDER_NAME[] = "RepPartitions";
const char REPETITIONS_FOLDER_NAME[] = "RepetitionData";

const char COMPUTATION_FOLDER_NAME[] = "ACGT_COMPUTATION";
const char FILEMANAGER_PATH_DELIMINATOR = '/';

char* getLine_FromFile(const char* filename, unsigned long long int lineIndex);
vector<char*> getAllLines_FromFile (const char* filename);

void ceateInfoFile(const char* path, unsigned long long int h, unsigned long long int l, unsigned long long int m);

#endif
