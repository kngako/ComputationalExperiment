//COMPRESSION PROJECT: MODULE 4 ENCODING & COMPRESSION GAIN : module_4.h
//Created by Mathys Ellis 26/02/2014
//---------------------------------------------------------------------------

#ifndef module_4H
#define module_4H


#include<vector>
#include <iostream>

#include "module_0.h"
#include "module_1.h"
#include "module_7.h"

using namespace std;

void calculateCompressionGain_FromPartitionFile(char* str, const char* partitionFilename, const char* outputFilename, const char* huffmanTablesPath);
void calculateAndStoreCompressionGain(char* str, partitionedString& partitionedStr, const char* huffmanTableFilename, fstream& file);

compressionInfo* getOptimumCompressionGainForString(const char* CGIFilename);

void saveCompressionGainInfoToFile(compressionInfo* info, fstream& file);

double getOptimumAverageOfCompressionGainFor(vector<compressionInfo*>& list);

compressionInfo* getCompressionGainInfo_FromFile(const char* filename, unsigned long long int index);

void analysisCompressionGainInfo_ForLenN(const char* outputPath, const char* CGIpath, unsigned long long int lenIndex, unsigned long long int count);

double getCompressionGain_2Str(char* normal, int len1, char* encoded, int len2);
double getBitSizeOfStr(char* str, int len);

char* encodePartitionedStringToEncodedString(partitionedString& input, const char* huffLookupDirectory);
partitionedString decodePartitionedStringFromEncodedString(char* input, const char* huffLookupDirectory);
//---------------------------------------------------------------------------
#endif
