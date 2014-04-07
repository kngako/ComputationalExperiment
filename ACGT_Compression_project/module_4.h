//COMPRESSION PROJECT: MODULE 4 ENCODING & COMPRESSION GAIN : module_4.h
//Created by Mathys Ellis 26/02/2014
//---------------------------------------------------------------------------

#ifndef module_4H
#define module_4H


#include<vector>
#include <iostream>

#include "module_0.h"
#include "module_1.h"

using namespace std;

double getCompressionGain_2Str(char* normal, int len1, char* encoded, int len2);
double getBitSizeOfStr(char* str, int len);
char* encodePartitionedStringToEncodedString(partitionedString& input, const char* huffLookupDirectory);
partitionedString decodePartitionedStringFromEncodedString(char* input, const char* huffLookupDirectory);
//---------------------------------------------------------------------------
#endif
