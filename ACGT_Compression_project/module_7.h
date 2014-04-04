//COMPRESSION PROJECT: MODULE 7 REPETION PARTIONIZER: module_7.h
//Created by Mathys Ellis 26/03/2014

/* 
 * File:   module_7.h
 * Author: MoX
 *
 * Created on 26 March 2014, 9:04 AM
 */




#ifndef MODULE_7_H
#define	MODULE_7_H

#include "module_0.h"
#include "module_5.h"
#include "module_3.h"

vector<repetition*> generateRepetitionListFromFile(const char* filename, char*& string);
vector<vector<repetition*>*> repetitionListSorter(vector<repetition*>& repetitionList, char* str);
void repetitionToPartitions_mem_file(char* str, vector<vector<repetition*>*>& repetitionList, const char* filename);
void recConstructPartions_mem_file(partitionedString& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, fstream& outFile, int curPos, int strLen);

void recRepetitionPartitioner_file(char*& str, int curPos, partitionedString& currentPartitionedString, vector<vector<repetition*>*>& repetitionList, fstream& outFile);

void partitionRepetitions_FromFile(const char* sourceFilename, const char* destFilname, int mode);

#endif	/* MODULE_7_H */

